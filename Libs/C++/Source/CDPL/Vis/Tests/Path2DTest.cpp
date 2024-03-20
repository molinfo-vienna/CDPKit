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


#include <cmath>
#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Vis/Path2DConverter.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


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
        "MT 7.197851 5.000000\n"
        "AT 4.000000 5.000000 3.200000 0.000000 2.100000 -3.200000\n"
        "MT 4.000000 8.200000\n"
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
        "LT -3.200000 15.000000\n"
        "CP\n"
        "MT -3.200000 5.000000\n"
        "LT 2.800000 5.000000\n"
        "LT 2.800000 15.000000\n"
        "LT -3.200000 15.000000\n"
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

    BOOST_CHECK(!path1.hasDrawingElements());

    path1.moveTo(2.0, 3.0);

    BOOST_CHECK(!path1.isEmpty());
    BOOST_CHECK(!path1.hasDrawingElements());
    
    path1.moveTo({ 3.0, 4.0 });

    BOOST_CHECK(!path1.isEmpty());
    BOOST_CHECK(!path1.hasDrawingElements());
   
    path1.arc(4.0, 5.0, 3.2, 0.0, 2.1, -3.2);

    BOOST_CHECK(!path1.isEmpty());
    BOOST_CHECK(path1.hasDrawingElements());
     
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
    BOOST_CHECK(path2.hasDrawingElements());
 
    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == PATH_STRING);

//--------

    path2.clear();
    
    BOOST_CHECK(path2.isEmpty());
    BOOST_CHECK(!path2.hasDrawingElements());
    
    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == "FREO\n");

//--------

    path2.setFillRule(Path2D::WINDING);
    
    path2 += Path2D();

    BOOST_CHECK(path2.isEmpty());
    BOOST_CHECK(!path2.hasDrawingElements());
    
    path_conv.convert(path2);

    BOOST_CHECK(path_conv.pathString == "FRW\n");

    path2 += path1;

    BOOST_CHECK(!path2.isEmpty());
    BOOST_CHECK(path2.hasDrawingElements());
    
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

    path2.closePath();
    
    BOOST_CHECK(path2 != path1);

//--------

    struct TestArc
    {

        void checkBounds(const Rectangle2D& bounds) const {
            BOOST_CHECK_CLOSE(this->bounds[0], bounds.getMin()(0), 0.0001);
            BOOST_CHECK_CLOSE(this->bounds[1], bounds.getMin()(1), 0.0001);
            BOOST_CHECK_CLOSE(this->bounds[2], bounds.getMax()(0), 0.0001);
            BOOST_CHECK_CLOSE(this->bounds[3], bounds.getMax()(1), 0.0001);
            
        }
        
        double arcSpec[6];
        double bounds[4];

    } test_arcs[] = {
        {{0.0, 0.0, 10.0, 20.0, 10.0, 70.0},
         {std::cos(80.0 / 180.0 * M_PI) * 10.0, std::sin(10.0 / 180.0 * M_PI) * 20.0,
          std::cos(10.0 / 180.0 * M_PI) * 10.0, std::sin(80.0 / 180.0 * M_PI) * 20.0}},
        {{0.0, 0.0, 10.0, 20.0, 10.0, 90.0},
         {std::cos(100.0 / 180.0 * M_PI) * 10.0, std::sin(10.0 / 180.0 * M_PI) * 20.0,
          std::cos(10.0 / 180.0 * M_PI) * 10.0, 20.0}                                },
        {{0.0, 0.0, 10.0, 20.0, 80.0, -70.0},
         {std::cos(80.0 / 180.0 * M_PI) * 10.0, std::sin(10.0 / 180.0 * M_PI) * 20.0,
          std::cos(10.0 / 180.0 * M_PI) * 10.0, std::sin(80.0 / 180.0 * M_PI) * 20.0}},
        {{0.0, 0.0, 10.0, 20.0, 100.0, -90.0},
         {std::cos(100.0 / 180.0 * M_PI) * 10.0, std::sin(10.0 / 180.0 * M_PI) * 20.0,
          std::cos(10.0 / 180.0 * M_PI) * 10.0, 20.0}                                },
        {{10.0, 10.0, 20.0, 10.0, 10.0, 350},
         {-10.0, 0.0, 30.0, 20.0}                                                    },
        {{10.0, 10.0, 20.0, 10.0, 10.0, -360},
         {-10.0, 0.0, 30.0, 20.0}                                                    },
        {{10.0, 10.0, 20.0, 10.0, -1000.0, -360},
         {-10.0, 0.0, 30.0, 20.0}                                                    },
        {{10.0, 10.0, 20.0, 10.0, -1000.0, -460},
         {-10.0, 0.0, 30.0, 20.0}                                                    },
        {{10.0, 10.0, 20.0, 10.0, 0.0, 180.0},
         {-10.0, 10.0, 30.0, 20.0}                                                   },
        {{10.0, 10.0, 20.0, 10.0, 90.0, 180.0},
         {-10.0, 0.0, 10.0, 20.0}                                                    },
        {{10.0, 10.0, 20.0, 10.0, 180.0, 180.0},
         {-10.0, 0.0, 30.0, 10.0}                                                    },
        {{10.0, 10.0, 20.0, 10.0, 270.0, 180.0},
         {10.0, 0.0, 30.0, 20.0}                                                     }
    };

    Rectangle2D bounds;
    
    for (std::size_t i = 0; i < sizeof(test_arcs) / sizeof(TestArc); i++) {
        path1.clear();
        path1.arc(test_arcs[i].arcSpec[0], test_arcs[i].arcSpec[1], test_arcs[i].arcSpec[2],
                  test_arcs[i].arcSpec[3], test_arcs[i].arcSpec[4], test_arcs[i].arcSpec[5]);
        path1.getBounds(bounds);

        test_arcs[i].checkBounds(bounds);

        (path2 = path1).getBounds(bounds);

        test_arcs[i].checkBounds(bounds);

        Path2D(path2).getBounds(bounds);

        test_arcs[i].checkBounds(bounds);
    }

//--------

    path1.clear();
    path1.getBounds(bounds);

    BOOST_CHECK(!bounds.isDefined());

    path1.closePath();

    BOOST_CHECK(!bounds.isDefined());

    path1.moveTo(-20.0, 3.33);

    BOOST_CHECK(!bounds.isDefined());

    path1.moveTo(20.0, -13.33);

    BOOST_CHECK(!bounds.isDefined());

    path1.closePath();

    BOOST_CHECK(!bounds.isDefined());

//--------

    struct TestLine
    {

        double lineSpec[2];
        double bounds[4];

    } test_lines[] = {
        {{20.0, -13.33}, {20.0, -13.33, 20.0, -13.33}},
        {{0.0, -20.0},   {0.0, -20.0, 20.0, -13.33}  },
        {{0.0, 20.0},    {0.0, -20.0, 20.0, 20.0}    },
        {{50.0, 10.0},   {0.0, -20.0, 50.0, 20.0}    }
    };

    for (std::size_t i = 0; i < sizeof(test_lines) / sizeof(TestLine); i++) {
        path1.lineTo(test_lines[i].lineSpec[0], test_lines[i].lineSpec[1]);
        path1.getBounds(bounds);

        BOOST_CHECK_CLOSE(test_lines[i].bounds[0], bounds.getMin()(0), 0.0001);
        BOOST_CHECK_CLOSE(test_lines[i].bounds[1], bounds.getMin()(1), 0.0001);
        BOOST_CHECK_CLOSE(test_lines[i].bounds[2], bounds.getMax()(0), 0.0001);
        BOOST_CHECK_CLOSE(test_lines[i].bounds[3], bounds.getMax()(1), 0.0001);
    }
}
