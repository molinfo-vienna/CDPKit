/* 
 * SizeSpecificationTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/SizeSpecification.hpp"


BOOST_AUTO_TEST_CASE(SizeSpecificationTest)
{
    using namespace CDPL;
    using namespace Vis;

    SizeSpecification ss1;

    BOOST_CHECK(ss1.getValue() == 0.0);
    BOOST_CHECK(ss1.isRelative() == false);
    BOOST_CHECK(ss1.followsInputScaling() == false);
    BOOST_CHECK(ss1.followsOutputScaling() == false);

    SizeSpecification ss2(0.3);

    BOOST_CHECK(ss2.getValue() == 0.3);
    BOOST_CHECK(ss2.isRelative() == false);
    BOOST_CHECK(ss2.followsInputScaling() == false);
    BOOST_CHECK(ss2.followsOutputScaling() == false);

    SizeSpecification ss3(0.5, true);

    BOOST_CHECK(ss3.getValue() == 0.5);
    BOOST_CHECK(ss3.isRelative() == true);
    BOOST_CHECK(ss3.followsInputScaling() == false);
    BOOST_CHECK(ss3.followsOutputScaling() == false);

    SizeSpecification ss4(0.7, false, true);

    BOOST_CHECK(ss4.getValue() == 0.7);
    BOOST_CHECK(ss4.isRelative() == false);
    BOOST_CHECK(ss4.followsInputScaling() == true);
    BOOST_CHECK(ss4.followsOutputScaling() == false);

    SizeSpecification ss5(-0.7, true, false, true);

    BOOST_CHECK(ss5.getValue() == -0.7);
    BOOST_CHECK(ss5.isRelative() == true);
    BOOST_CHECK(ss5.followsInputScaling() == false);
    BOOST_CHECK(ss5.followsOutputScaling() == true);

//-----

    BOOST_CHECK(ss4 != ss5);
    BOOST_CHECK(!(ss4 == ss5));

    ss4.setValue(-0.7);

    BOOST_CHECK(ss4.getValue() == -0.7);
    BOOST_CHECK(ss4.isRelative() == false);
    BOOST_CHECK(ss4.followsInputScaling() == true);
    BOOST_CHECK(ss4.followsOutputScaling() == false);

    BOOST_CHECK(ss4 != ss5);
    BOOST_CHECK(!(ss4 == ss5));

    ss4.setRelative(true);

    BOOST_CHECK(ss4.getValue() == -0.7);
    BOOST_CHECK(ss4.isRelative() == true);
    BOOST_CHECK(ss4.followsInputScaling() == true);
    BOOST_CHECK(ss4.followsOutputScaling() == false);

    BOOST_CHECK(ss4 != ss5);
    BOOST_CHECK(!(ss4 == ss5));

    ss4.followInputScaling(false);

    BOOST_CHECK(ss4.getValue() == -0.7);
    BOOST_CHECK(ss4.isRelative() == true);
    BOOST_CHECK(ss4.followsInputScaling() == false);
    BOOST_CHECK(ss4.followsOutputScaling() == false);

    BOOST_CHECK(ss4 != ss5);
    BOOST_CHECK(!(ss4 == ss5));

    ss4.followOutputScaling(true);

    BOOST_CHECK(ss4.getValue() == -0.7);
    BOOST_CHECK(ss4.isRelative() == true);
    BOOST_CHECK(ss4.followsInputScaling() == false);
    BOOST_CHECK(ss4.followsOutputScaling() == true);

    BOOST_CHECK(ss4 == ss5);
    BOOST_CHECK(!(ss4 != ss5));

//-----

    BOOST_CHECK(ss4 == ss4);
    BOOST_CHECK(!(ss4 != ss4));

    ss4 = ss2;

    BOOST_CHECK(ss4 != ss5);
    BOOST_CHECK(!(ss4 == ss5));

    BOOST_CHECK(ss4 == ss2);
    BOOST_CHECK(!(ss4 != ss2));

    BOOST_CHECK(ss2 != ss5);
    BOOST_CHECK(!(ss2 == ss5));
}

