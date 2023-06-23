/* 
 * Rectangle2DTest.cpp 
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
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Vis/Rectangle2D.hpp"


BOOST_AUTO_TEST_CASE(Rectangle2DTest)
{
    using namespace CDPL;
    using namespace Vis;

    Rectangle2D r1;

    BOOST_CHECK(!r1.isDefined());

    Math::Vector2D v1, v2;

    v1(0) = 2.0, v1(1) = -4.3;
    v2(0) = 3.0, v2(1) = 5.3;

    Rectangle2D r2(v1, v2);

    BOOST_CHECK(r2.getMin()(0) == 2.0);
    BOOST_CHECK(r2.getMin()(1) == -4.3);
    BOOST_CHECK(r2.getMax()(0) == 3.0);
    BOOST_CHECK(r2.getMax()(1) == 5.3);

    Rectangle2D r3(2.0, -4.3, 3.0, 5.3);

    BOOST_CHECK(r3.getMin()(0) == 2.0);
    BOOST_CHECK(r3.getMin()(1) == -4.3);
    BOOST_CHECK(r3.getMax()(0) == 3.0);
    BOOST_CHECK(r3.getMax()(1) == 5.3);

    Rectangle2D r4 = Rectangle2D();

    BOOST_CHECK(!r4.isDefined());

//-----

    r1.addPoint(v1);

    BOOST_CHECK(r1.isDefined());

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 2.0);
    BOOST_CHECK(r1.getMax()(1) == -4.3);

    r1.addPoint(3.0, 5.3);

    BOOST_CHECK(r1.isDefined());

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 5.3);

    r1.addPoint(2.5, 5.0);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 5.3);

//-----

    r1.addMargin(1.3, 2.6);

    BOOST_CHECK_CLOSE(r1.getMin()(0), 0.7, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), -6.9, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 4.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 7.9, 0.00001);

    r1.addMargin(-1.3, -2.6);

    BOOST_CHECK_CLOSE(r1.getMin()(0), 2.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), -4.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 3.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 5.3, 0.00001);

    r1.addMargin(0.0, 0.0);

    BOOST_CHECK_CLOSE(r1.getMin()(0), 2.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), -4.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 3.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 5.3, 0.00001);

//-----

    r2 = Rectangle2D(2.5, -4.0, 4.0, 6.3);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK_CLOSE(r1.getMin()(1), -4.3, 0.0000000001);
    BOOST_CHECK(r1.getMax()(0) == 4.0);
    BOOST_CHECK(r1.getMax()(1) == 6.3);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(2.5, -4.0, 4.0, 5.3);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 4.0);
    BOOST_CHECK(r1.getMax()(1) == 5.3);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(2.0, -5.0, 3.9, 5.0);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -5.0);
    BOOST_CHECK(r1.getMax()(0) == 3.9);
    BOOST_CHECK(r1.getMax()(1) == 5.3);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(1.9, -5.0, 2.9, 5.0);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 1.9);
    BOOST_CHECK(r1.getMin()(1) == -5.0);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 5.3);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(1.9, -4.0, 2.9, 5.0);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 1.9);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 5.3);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(1.9, -4.0, 2.9, 6.0);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 1.9);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 6.0);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(2.1, -4.0, 2.9, 6.0);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 6.0);

    r2 = r1;

    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 6.0);

    r1.addRectangle(r1);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 3.0);
    BOOST_CHECK(r1.getMax()(1) == 6.0);

    r2.addMargin(1.0, 1.0);

    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 1.0);
    BOOST_CHECK(r1.getMin()(1) == -5.3);
    BOOST_CHECK(r1.getMax()(0) == 4.0);
    BOOST_CHECK(r1.getMax()(1) == 7.0);

    r1.addRectangle(Rectangle2D(v1, v2));

    BOOST_CHECK(r1.getMin()(0) == 1.0);
    BOOST_CHECK(r1.getMin()(1) == -5.3);
    BOOST_CHECK(r1.getMax()(0) == 4.0);
    BOOST_CHECK(r1.getMax()(1) == 7.0);

    r1 = Rectangle2D(v1, v2);

    r2 = Rectangle2D(5.1, 10.0, 6.9, 16.0);
    
    r1.addRectangle(r2);

    BOOST_CHECK(r1.getMin()(0) == 2.0);
    BOOST_CHECK(r1.getMin()(1) == -4.3);
    BOOST_CHECK(r1.getMax()(0) == 6.9);
    BOOST_CHECK(r1.getMax()(1) == 16.0);

//-----

    BOOST_CHECK(r1.containsPoint(3.0, 15.0));
    BOOST_CHECK(r1.containsPoint(2.0, -4.3));
    BOOST_CHECK(r1.containsPoint(6.9, -4.3));
    BOOST_CHECK(r1.containsPoint(6.9, 16.0));
    BOOST_CHECK(r1.containsPoint(3.0, 16.0));

    v1(0) = 3.0; v1(1) = 15.0;

    BOOST_CHECK(r1.containsPoint(v1));

    v1(0) = 2.0; v1(1) = -4.3;    

    BOOST_CHECK(r1.containsPoint(v1));

    v1(0) = 6.9; v1(1) = -4.3;

    BOOST_CHECK(r1.containsPoint(v1));

    v1(0) = 6.9; v1(1) = 16.0;

    BOOST_CHECK(r1.containsPoint(v1));

    v1(0) = 3.0; v1(1) = 16.0;

    BOOST_CHECK(r1.containsPoint(v1));

    BOOST_CHECK(!r1.containsPoint(3.0, -15.0));
    BOOST_CHECK(!r1.containsPoint(3.0, 17.0));
    BOOST_CHECK(!r1.containsPoint(1.0, -4.0));
    BOOST_CHECK(!r1.containsPoint(7.0, -4.0));
    BOOST_CHECK(!r1.containsPoint(1.0, -5.0));
    BOOST_CHECK(!r1.containsPoint(7.0, 17.0));
    BOOST_CHECK(!r1.containsPoint(7.0, -5.0));
    BOOST_CHECK(!r1.containsPoint(1.0, 17.0));

    v1(0) = 3.0; v1(1) = -15.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 3.0; v1(1) = 17.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 1.0; v1(1) = -4.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 7.0; v1(1) = -4.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 1.0; v1(1) = -5.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 7.0; v1(1) = 17.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 7.0; v1(1) = -5.0;

    BOOST_CHECK(!r1.containsPoint(v1));

    v1(0) = 1.0; v1(1) = 17.0;

    BOOST_CHECK(!r1.containsPoint(v1));

//-----

    r1 = Rectangle2D(-3.0, -3.0, 4.0, 7.0);

    BOOST_CHECK(r1.containsRectangle(r1));

    r2 = r1;

    BOOST_CHECK(r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.0, -0.2);

    BOOST_CHECK(r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.0, 0.2);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.2, -0.2);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.2, 0.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.2, 0.2);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(-0.2, -0.2);

    BOOST_CHECK(r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(-0.2, 0.0);

    BOOST_CHECK(r1.containsRectangle(r2));    

    r2 = r1;

    r2.addMargin(-0.2, 0.2);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(100.0, 100.0, 200.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-200.0, -200.0, -100.0, -100.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-200.0, -200.0, 0.0, 0.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(0.0, 0.0, 200.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(100.0, -200.0, 200.0, -100.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-200.0, 100.0, -100.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(0.0, -200.0, 100.0, 0.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-100.0, 0.0, 0.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-100.0, -200.0, 100.0, -100.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-100.0, 100.0, 100.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(-200.0, -100.0, -100.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

    r2 = Rectangle2D(100.0, -100.0, 200.0, 200.0);

    BOOST_CHECK(!r1.containsRectangle(r2));    

//-----

    r1 = Rectangle2D(-3.0, -3.0, 4.0, 7.0);

    BOOST_CHECK(r1.intersectsRectangle(r1));

    r2 = r1;

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.0, -0.2);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.0, 0.2);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.2, -0.2);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.2, 0.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(0.2, 0.2);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(-0.2, -0.2);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(-0.2, 0.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = r1;

    r2.addMargin(-0.2, 0.2);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-200.0, -200.0, 0.0, 0.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(0.0, 0.0, 200.0, 200.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(0.0, -200.0, 100.0, 0.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-100.0, 0.0, 0.0, 200.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-100.0, -200.0, 100.0, -100.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-100.0, 100.0, 100.0, 200.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-200.0, -100.0, -100.0, 200.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(100.0, -100.0, 200.0, 200.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r1 = Rectangle2D(-10.0, -10.0, 10.0, 10.0);

    r2 = Rectangle2D(10.0, -10.0, 20.0, 10.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-20.0, -10.0, -10.0, 10.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-10.0, -20.0, 10.0, -10.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-10.0, 10.0, 10.0, 20.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-20.0, -20.0, -10.0, -10.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(10.0, -20.0, 20.0, -10.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(10.0, 10.0, 20.0, 20.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-20.0, 10.0, -10.0, 20.0);

    BOOST_CHECK(r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(11.0, -10.0, 21.0, 10.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-21.0, -10.0, -11.0, 10.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-10.0, -21.0, 10.0, -11.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-10.0, 11.0, 10.0, 21.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-20.0, -20.0, -11.0, -11.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(11.0, -20.0, 20.0, -11.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(11.0, 11.0, 20.0, 20.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

    r2 = Rectangle2D(-20.0, 11.0, -11.0, 21.0);

    BOOST_CHECK(!r1.intersectsRectangle(r2));    

//-----

    r2.setMin(-15.0, 13.3);

    BOOST_CHECK(r2.getMin()(0) == -15.0);
    BOOST_CHECK(r2.getMin()(1) == 13.3);
    BOOST_CHECK(r2.getMax()(0) == -11.0);
    BOOST_CHECK(r2.getMax()(1) == 21.0);

    v1(0) = -16.0, v1(1) = 10.0;
    
    r2.setMin(v1);

    BOOST_CHECK(r2.getMin()(0) == -16.0);
    BOOST_CHECK(r2.getMin()(1) == 10.0);
    BOOST_CHECK(r2.getMax()(0) == -11.0);
    BOOST_CHECK(r2.getMax()(1) == 21.0);

//-----

    r2.setMax(15.0, 20.3);

    BOOST_CHECK(r2.getMin()(0) == -16.0);
    BOOST_CHECK(r2.getMin()(1) == 10.0);
    BOOST_CHECK(r2.getMax()(0) == 15.0);
    BOOST_CHECK(r2.getMax()(1) == 20.3);

    v2(0) = 16.0, v2(1) = 25.0;

    r2.setMax(v2);

    BOOST_CHECK(r2.getMin()(0) == -16.0);
    BOOST_CHECK(r2.getMin()(1) == 10.0);
    BOOST_CHECK(r2.getMax()(0) == 16.0);
    BOOST_CHECK(r2.getMax()(1) == 25.0);

//-----

    r2.setBounds(-10.0, -10.0, 10.0, 10.0);

    BOOST_CHECK(r2.getMin()(0) == -10.0);
    BOOST_CHECK(r2.getMin()(1) == -10.0);
    BOOST_CHECK(r2.getMax()(0) == 10.0);
    BOOST_CHECK(r2.getMax()(1) == 10.0);

    v1(0) = -11.0, v1(1) = -12.0;
    v2(0) = 13.0, v2(1) = 14.0;

    r2.setBounds(v1, v2);

    BOOST_CHECK(r2.getMin()(0) == -11.0);
    BOOST_CHECK(r2.getMin()(1) == -12.0);
    BOOST_CHECK(r2.getMax()(0) == 13.0);
    BOOST_CHECK(r2.getMax()(1) == 14.0);

//-----

    v1 = r2.getCenter();

    BOOST_CHECK_CLOSE(v1(0), (13.0 + -11.0) * 0.5, 0.00001);
    BOOST_CHECK_CLOSE(v1(1), (14.0 + -12.0) * 0.5, 0.00001);

    r2.getCenter(v2);

    BOOST_CHECK_CLOSE(v2(0), (13.0 + -11.0) * 0.5, 0.00001);
    BOOST_CHECK_CLOSE(v2(1), (14.0 + -12.0) * 0.5, 0.00001);

    r2.setBounds(0.0, 0.0, 0.0, 0.0);

    v1 = r2.getCenter();

    BOOST_CHECK_SMALL(v1(0), 0.00001);
    BOOST_CHECK_SMALL(v1(1), 0.00001);

//-----

    r1.setBounds(3.0, 4.0, 23.3, 14.8);

    BOOST_CHECK_CLOSE(r1.getWidth(), 20.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getHeight(), 10.8, 0.00001);
    BOOST_CHECK_CLOSE(r1.getArea(), 10.8 * 20.3, 0.00001);
    
    r1.setBounds(3.0, 4.0, 3.0, 14.8);

    BOOST_CHECK_SMALL(r1.getWidth(), 0.00001);
    BOOST_CHECK_CLOSE(r1.getHeight(), 10.8, 0.00001);
    BOOST_CHECK_SMALL(r1.getArea(), 0.00001);
    
    r1.setBounds(3.0, 4.0, 23.0, 4.0);

    BOOST_CHECK_SMALL(r1.getHeight(), 0.00001);
    BOOST_CHECK_CLOSE(r1.getWidth(), 20.0, 0.00001);
    BOOST_CHECK_SMALL(r1.getArea(), 0.00001);
    
    BOOST_CHECK_SMALL(r2.getHeight(), 0.00001);
    BOOST_CHECK_SMALL(r2.getWidth(), 0.00001);
    BOOST_CHECK_SMALL(r2.getArea(), 0.00001);
    
//-----

    r2.reset();

    BOOST_CHECK(!r2.isDefined());

    r2.addPoint(10.0, 11.0);

    BOOST_CHECK(r2.getMin()(0) == 10.0);
    BOOST_CHECK(r2.getMin()(1) == 11.0);
    BOOST_CHECK(r2.getMax()(0) == 10.0);
    BOOST_CHECK(r2.getMax()(1) == 11.0);

    BOOST_CHECK_SMALL(r2.getHeight(), 0.00001);
    BOOST_CHECK_SMALL(r2.getWidth(), 0.00001);
    BOOST_CHECK_SMALL(r2.getArea(), 0.00001);

//-----

    r1.setBounds(3.0, 4.0, 23.3, 14.8);    

    r1.translate(Math::vec(2.1, -0.3));

    BOOST_CHECK_CLOSE(r1.getMin()(0), 5.1, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), 3.7, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 25.4, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 14.5, 0.00001);
    
    v1(0) = -2.1, v1(1) = 0.3;

    r1.translate(v1);

    BOOST_CHECK_CLOSE(r1.getMin()(0), 3.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), 4.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 23.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 14.8, 0.00001);
    
    r1.translate(Math::vec(0, 0));

    BOOST_CHECK_CLOSE(r1.getMin()(0), 3.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), 4.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 23.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 14.8, 0.00001);
    
    v1(0) = 0.0, v1(1) = 0.0;

    r1.translate(v1);

    BOOST_CHECK_CLOSE(r1.getMin()(0), 3.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), 4.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 23.3, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 14.8, 0.00001);

//-----

    r1.setMin(-3.0, 4.0);

    r1.scale(5.0);

    BOOST_CHECK_CLOSE(r1.getMin()(0), -3.0 * 5.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), 4.0 * 5.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 23.3 * 5.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 14.8 * 5.0, 0.00001);

    r1.scale(-5.0);

    BOOST_CHECK_CLOSE(r1.getMin()(0), -3.0 * -25.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMin()(1), 4.0 * -25.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(0), 23.3 * -25.0, 0.00001);
    BOOST_CHECK_CLOSE(r1.getMax()(1), 14.8 * -25.0, 0.00001);

    r1.scale(0.0);

    BOOST_CHECK_SMALL(r1.getMin()(0), 0.00001);
    BOOST_CHECK_SMALL(r1.getMin()(1), 0.00001);
    BOOST_CHECK_SMALL(r1.getMax()(0), 0.00001);
    BOOST_CHECK_SMALL(r1.getMax()(1), 0.00001);

//-----

    r1.setBounds(3.0, 4.0, 23.3, 14.8);    
    r2.setBounds(3.0, 4.0, 23.3, 14.8);    

    BOOST_CHECK(r1 == r1);
    BOOST_CHECK(!(r1 != r1));

    BOOST_CHECK(r1 == r2);
    BOOST_CHECK(!(r1 != r2));

    r2.setBounds(3.1, 4.0, 23.3, 14.8);    

    BOOST_CHECK(r1 != r2);
    BOOST_CHECK(!(r1 == r2));

    r2.setBounds(3.0, 4.1, 23.3, 14.8);    

    BOOST_CHECK(r1 != r2);
    BOOST_CHECK(!(r1 == r2));

    r2.setBounds(3.0, 4.0, 23.4, 14.8);    

    BOOST_CHECK(r1 != r2);
    BOOST_CHECK(!(r1 == r2));

    r2.setBounds(3.0, 4.0, 23.3, 14.9);    

    BOOST_CHECK(r1 != r2);
    BOOST_CHECK(!(r1 == r2));
}
