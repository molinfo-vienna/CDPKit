/* 
 * Path2DTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Vis/Path2DConverter.hpp"

#include <iostream>
namespace
{

    struct TestPathConverter : public CDPL::Vis::Path2DConverter
    {

        void convert(const CDPL::Vis::Path2D& path) {
            pathString.clear();
            pathString += (path.getFillRule() == CDPL::Vis::Path2D::EVEN_ODD ? "FREO\n" : "FRW\n");
            
            path.convert(*this);
        }

        void moveTo(double x, double y) {
            pathString += "MT " + std::to_string(x) + ' ' + std::to_string(y) + '\n';
        }
 
        void arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep) {
            pathString += "AT " + std::to_string(cx) + ' ' + std::to_string(cy) + ' '
                + std::to_string(rx) + ' ' + std::to_string(ry) + ' '
                + std::to_string(start_ang) + ' ' + std::to_string(sweep) + '\n';
        }

        void lineTo(double x, double y) {
            pathString += "LT " + std::to_string(x) + ' ' + std::to_string(y) + '\n';
        }

        void closePath() {
            pathString += "CP\n";
        }
        
        std::string pathString;
    };

    const std::string PATH_STRING_PART1 =
        "FRW\n";

    const std::string PATH_STRING_PART2 =
        "MT 2.000000 3.000000\n"
        "MT 3.000000 4.000000\n"
        "MT 2.384492 5.000000\n"
        "AT 4.000000 5.000000 3.200000 0.000000 2.100000 -3.200000\n"
        "MT 3.551926 7.860789\n"
        "AT 4.000000 5.000000 1.000000 3.200000 90.000000 3.200000\n"
        "AT 4.000000 5.000000 3.200000 0.000000 2.100000 -3.200000\n"
        "AT 4.000000 5.000000 1.000000 3.200000 90.000000 3.200000\n"
        "LT -10.000000 11.000000\n"
        "LT -10.000000 11.000000\n"
        "CP\n"
        "MT 4.700000 -5.000000\n"
        "AT 2.200000 -5.000000 2.500000 5.000000 0.000000 360.000000\n"
        "CP\n"
        "MT 4.700000 -5.000000\n"
        "AT 2.200000 -5.000000 2.500000 5.000000 0.000000 360.000000\n"
        "CP\n"
        "MT -3.200000 5.000000\n"
        "LT 2.800000 5.000000\n"
        "LT 2.800000 15.000000\n"
        "LT 5.000000 15.000000\n"
        "CP\n"
        "MT -3.200000 5.000000\n"
        "LT 2.800000 5.000000\n"
        "LT 2.800000 15.000000\n"
        "LT 5.000000 15.000000\n"
        "CP\n";

    const std::string PATH_STRING = PATH_STRING_PART1 + PATH_STRING_PART2;
}


BOOST_AUTO_TEST_CASE(Path2DTest)
{
    using namespace CDPL;
    using namespace Vis;

    Path2D path1;

    BOOST_CHECK(path1.isEmpty());
    BOOST_CHECK(path1.getFillRule() == Path2D::EVEN_ODD);
    
    Path2D path2(path1);

    BOOST_CHECK(path2.isEmpty());
    BOOST_CHECK(path2.getFillRule() == Path2D::EVEN_ODD);
    
//--------

    path1.setFillRule(Path2D::EVEN_ODD);

    BOOST_CHECK(path1.getFillRule() == Path2D::EVEN_ODD);
    BOOST_CHECK(path1.isEmpty());

    path1.setFillRule(Path2D::WINDING);

    BOOST_CHECK(path1.getFillRule() == Path2D::WINDING);
    BOOST_CHECK(path1.isEmpty());

//--------

    path1.moveTo(2.0, 3.0);

    BOOST_CHECK(!path1.isEmpty());
    
    path1.moveTo({ 3.0, 4.0 });
    path1.arc(4.0, 5.0, 3.2, 0.0, 2.1, -3.2);
    path1.arc({ 4.0, 5.0 }, 1.0, 3.2, 90.0, 3.2);
    path1.arcTo(4.0, 5.0, 3.2, 0.0, 2.1, -3.2);
    path1.arcTo({ 4.0, 5.0 }, 1.0, 3.2, 90.0, 3.2);
    path1.lineTo(-10.0, 11.0);
    path1.lineTo({ -10.0, 11.0 });
    path1.closePath();

    path1.addEllipse(2.2, -5.0, 5.0, 10.0);
    path1.addEllipse({ 2.2, -5.0 }, 5.0, 10.0);
    path1.addRectangle(-3.2, 5.0, 6.0, 10.0);
    path1.addRectangle({ -3.2, 5.0 }, 6.0, 10.0);

    BOOST_CHECK(!path1.isEmpty());

//--------

    TestPathConverter path_conv;
    
    path_conv.convert(path1);

    BOOST_CHECK(path_conv.pathString == PATH_STRING);

//--------

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == "FREO\n");

//--------

    Path2D path3(path1);

    BOOST_CHECK(!path3.isEmpty());

    path_conv.convert(path3);

    BOOST_CHECK(path_conv.pathString == PATH_STRING);

//--------

    path2 = path1;

    BOOST_CHECK(!path2.isEmpty());

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == PATH_STRING);

//--------

    path2.clear();
    
    BOOST_CHECK(path2.isEmpty());
    
    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == "FREO\n");

//--------

    path2.setFillRule(Path2D::WINDING);
    
    path2 += Path2D();

    BOOST_CHECK(path2.isEmpty());

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == "FRW\n");

    path2 += path1;

    BOOST_CHECK(!path2.isEmpty());

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == PATH_STRING);

    path2.setFillRule(Path2D::EVEN_ODD);
 
    path2 += path2;

    BOOST_CHECK(!path2.isEmpty());

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == ("FREO\n" + PATH_STRING_PART2 + PATH_STRING_PART2));

    path2.setFillRule(Path2D::WINDING);
 
    path2 += path1;

    BOOST_CHECK(!path2.isEmpty());

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == (PATH_STRING + PATH_STRING_PART2 + PATH_STRING_PART2));

//--------  

    path2 = Path2D();

    BOOST_CHECK(path2.isEmpty());

    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == "FREO\n");

//--------

    path2.setFillRule(Path2D::WINDING);

    Path2D path4;

    BOOST_CHECK(path2 != path4);

    path2.setFillRule(Path2D::EVEN_ODD);

    BOOST_CHECK(path2 == path4);
    BOOST_CHECK(path2 != path1);

    path2 = path1;

    BOOST_CHECK(path2 == path1);
}
