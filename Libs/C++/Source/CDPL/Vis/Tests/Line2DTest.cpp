/* 
 * Line2DTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


BOOST_AUTO_TEST_CASE(Line2DTest)
{
    using namespace CDPL;
    using namespace Vis;

    Line2D l1;

    BOOST_CHECK(l1.getBegin()(0) == 0.0);
    BOOST_CHECK(l1.getBegin()(1) == 0.0);
    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    Math::Vector2D v1, v2;

    v1(0) = 2.0, v1(1) = -4.3;
    v2(0) = 3.0, v2(1) = 5.3;

    Line2D l2(v1, v2);

    BOOST_CHECK(l2.getBegin()(0) == 2.0);
    BOOST_CHECK(l2.getBegin()(1) == -4.3);
    BOOST_CHECK(l2.getEnd()(0) == 3.0);
    BOOST_CHECK(l2.getEnd()(1) == 5.3);

    Line2D l3(2.0, -4.3, 3.0, 5.3);

    BOOST_CHECK(l3.getBegin()(0) == 2.0);
    BOOST_CHECK(l3.getBegin()(1) == -4.3);
    BOOST_CHECK(l3.getEnd()(0) == 3.0);
    BOOST_CHECK(l3.getEnd()(1) == 5.3);

//-----

    l1.setBegin(v1);

    BOOST_CHECK(l1.getBegin()(0) == 2.0);
    BOOST_CHECK(l1.getBegin()(1) == -4.3);
    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(0.2, 0.3);

    BOOST_CHECK(l1.getBegin()(0) == 0.2);
    BOOST_CHECK(l1.getBegin()(1) == 0.3);
    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setEnd(v2);

    BOOST_CHECK(l1.getBegin()(0) == 0.2);
    BOOST_CHECK(l1.getBegin()(1) == 0.3);
    BOOST_CHECK(l1.getEnd()(0) == 3.0);
    BOOST_CHECK(l1.getEnd()(1) == 5.3);

    l1.setEnd(0.1, -0.2);

    BOOST_CHECK(l1.getBegin()(0) == 0.2);
    BOOST_CHECK(l1.getBegin()(1) == 0.3);
    BOOST_CHECK(l1.getEnd()(0) == 0.1);
    BOOST_CHECK(l1.getEnd()(1) == -0.2);

    l1.setPoints(v1, v2);

    BOOST_CHECK(l1.getBegin()(0) == 2.0);
    BOOST_CHECK(l1.getBegin()(1) == -4.3);
    BOOST_CHECK(l1.getEnd()(0) == 3.0);
    BOOST_CHECK(l1.getEnd()(1) == 5.3);

    l1.setPoints(0.36, -100.0, 2.67, 0.0);

    BOOST_CHECK(l1.getBegin()(0) == 0.36);
    BOOST_CHECK(l1.getBegin()(1) == -100.0);
    BOOST_CHECK(l1.getEnd()(0) == 2.67);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

//-----

    BOOST_CHECK(l1 != l2);
    BOOST_CHECK(!(l1 == l2));

    l1.setBegin(v1);

    BOOST_CHECK(l1 != l2);
    BOOST_CHECK(!(l1 == l2));

    l1.setEnd(v2);

    BOOST_CHECK(l1 == l2);
    BOOST_CHECK(!(l1 != l2));
    
//-----

    BOOST_CHECK(l1 == l1);
    BOOST_CHECK(!(l1 != l1));

    l1 = l3;

    BOOST_CHECK(l1 == l3);
    BOOST_CHECK(!(l1 != l3));

    BOOST_CHECK(l3 == l2);
    BOOST_CHECK(!(l3 != l2));

    BOOST_CHECK(l1 == l2);
    BOOST_CHECK(!(l1 != l2));

//-----

    l1.swapPoints();

    BOOST_CHECK(l1.getBegin()(0) == 3.0);
    BOOST_CHECK(l1.getBegin()(1) == 5.3);
    BOOST_CHECK(l1.getEnd()(0) == 2.0);
    BOOST_CHECK(l1.getEnd()(1) == -4.3);

    l1.swapPoints();

    BOOST_CHECK(l1.getBegin()(0) == 2.0);
    BOOST_CHECK(l1.getBegin()(1) == -4.3);
    BOOST_CHECK(l1.getEnd()(0) == 3.0);
    BOOST_CHECK(l1.getEnd()(1) == 5.3);

//-----

    Math::Vector2D tmp;

    l1.getCenter(tmp);

    BOOST_CHECK_CLOSE(tmp(0), 2.5, 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), 0.5, 0.00001);

    tmp.clear();

    tmp = l1.getCenter();

    BOOST_CHECK_CLOSE(tmp(0), 2.5, 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), 0.5, 0.00001);

//-----

    BOOST_CHECK_CLOSE(l1.getLength(), std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

//-----

    l1.getDirection(tmp);

    BOOST_CHECK_CLOSE(tmp(0), 1.0 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), 9.6 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

    tmp.clear();

    tmp = l1.getDirection();

    BOOST_CHECK_CLOSE(tmp(0), 1.0 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), 9.6 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

//-----

    l1.getCCWPerpDirection(tmp);

    BOOST_CHECK_CLOSE(tmp(0), -9.6 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), 1.0 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

    tmp.clear();

    tmp = l1.getCCWPerpDirection();

    BOOST_CHECK_CLOSE(tmp(0), -9.6 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), 1.0 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

//-----

    l1.getCWPerpDirection(tmp);

    BOOST_CHECK_CLOSE(tmp(0), 9.6 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), -1.0 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

    tmp.clear();

    tmp = l1.getCWPerpDirection();

    BOOST_CHECK_CLOSE(tmp(0), 9.6 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);
    BOOST_CHECK_CLOSE(tmp(1), -1.0 / std::sqrt(1.0 + 9.6 * 9.6), 0.00001);

//-----

    tmp(0) = 1.3;
    tmp(1) = -2.0;

    l1.translate(tmp);

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 3.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -6.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(0), 4.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 3.3, 0.00001);

    l1.translateBegin(tmp);

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 4.6, 0.00001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -8.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(0), 4.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 3.3, 0.00001);

    l1.translateEnd(tmp);

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 4.6, 0.00001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -8.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(0), 5.6, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 1.3, 0.00001);

    l1.translate(tmp);

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 5.9, 0.00001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.3, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(0), 6.9, 0.00001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -0.7, 0.00001);

//-----

    BOOST_CHECK(l1.containsPoint(l1.getBegin()));
    BOOST_CHECK(l1.containsPoint(l1.getEnd()));

    BOOST_CHECK(!l1.containsPoint(l1.getBegin() - l1.getDirection()));
    BOOST_CHECK(!l1.containsPoint(l1.getEnd() + l1.getDirection()));

    BOOST_CHECK(l1.containsPoint(l1.getBegin() + l1.getDirection() * 0.1));
    BOOST_CHECK(l1.containsPoint(l1.getEnd() - l1.getDirection() * 0.1));

    BOOST_CHECK(l1.containsPoint(l1.getBegin() - l1.getCCWPerpDirection() + l1.getDirection() * 0.01));
    BOOST_CHECK(l1.containsPoint(l1.getEnd() - l1.getCCWPerpDirection() - l1.getDirection() * 0.01));

    BOOST_CHECK(l1.containsPoint(l1.getBegin() + l1.getCCWPerpDirection() + l1.getDirection() * 0.01));
    BOOST_CHECK(l1.containsPoint(l1.getEnd() + l1.getCCWPerpDirection() - l1.getDirection() * 0.01));

    BOOST_CHECK(l1.containsPoint(l1.getCenter()));

    BOOST_CHECK(l1.containsPoint(l1.getCenter() + l1.getCCWPerpDirection() * l1.getLength() * 3.0));
    BOOST_CHECK(l1.containsPoint(l1.getCenter() - l1.getCCWPerpDirection() * l1.getLength() * 3.0));

//-----

    l2.setBegin(l1.getCenter() + tmp - l1.getDirection() * 10.0);
    l2.setEnd(l1.getCenter() - tmp + l1.getDirection() * 10.0);

    BOOST_CHECK(l1.getIntersectionPoint(l2, tmp));

    BOOST_CHECK_CLOSE(l1.getCenter()(0), tmp(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getCenter()(1), tmp(1), 0.0001);

    BOOST_CHECK(!l1.getIntersectionPoint(l1, tmp));

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection() * 5.3);
    l2.setEnd(l1.getEnd() + l1.getCCWPerpDirection() * 5.3);

    BOOST_CHECK(!l1.getIntersectionPoint(l2, tmp));

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection() - l1.getDirection() * 3.0);
    l2.setEnd(l1.getBegin() - l1.getCCWPerpDirection() - l1.getDirection() * 3.0);

    BOOST_CHECK(l1.getIntersectionPoint(l2, tmp));

    BOOST_CHECK_CLOSE((l1.getBegin() - l1.getDirection() * 3.0)(0), tmp(0), 0.0001);
    BOOST_CHECK_CLOSE((l1.getBegin() - l1.getDirection() * 3.0)(1), tmp(1), 0.0001);

    l2.setBegin(l1.getEnd() + l1.getCWPerpDirection() + l1.getDirection() * 13.0);
    l2.setEnd(l1.getEnd() - l1.getCWPerpDirection() + l1.getDirection() * 13.0);

    BOOST_CHECK(l1.getIntersectionPoint(l2, tmp));

    BOOST_CHECK_CLOSE((l1.getEnd() + l1.getDirection() * 13.0)(0), tmp(0), 0.0001);
    BOOST_CHECK_CLOSE((l1.getEnd() + l1.getDirection() * 13.0)(1), tmp(1), 0.0001);

    l2.setEnd(l2.getBegin());

    BOOST_CHECK(!l1.getIntersectionPoint(l2, tmp));

//-----

    BOOST_CHECK_SMALL(l1.getDistance(l1.getBegin()), 0.00001);
    BOOST_CHECK_SMALL(l1.getDistance(l1.getEnd()), 0.00001);
    BOOST_CHECK_SMALL(l1.getDistance(l1.getCenter()), 0.00001);
    BOOST_CHECK_SMALL(l1.getDistance(l1.getBegin() - l1.getDirection()), 0.00001);
    BOOST_CHECK_SMALL(l1.getDistance(l1.getEnd() + l1.getDirection()), 0.00001);

    BOOST_CHECK_CLOSE(l1.getDistance(l1.getBegin() + l1.getCCWPerpDirection() * 2.5), -2.5, 0.00001);
    BOOST_CHECK_CLOSE(l1.getDistance(l1.getEnd() - l1.getCCWPerpDirection() * 2.6), 2.6, 0.00001);
    BOOST_CHECK_CLOSE(l1.getDistance(l1.getCenter() + l1.getCCWPerpDirection() * -3.5), 3.5, 0.00001);
    BOOST_CHECK_CLOSE(l1.getDistance(l1.getBegin() - l1.getDirection() + l1.getCCWPerpDirection() * 2.5), -2.5, 0.00001);
    BOOST_CHECK_CLOSE(l1.getDistance(l1.getEnd() + l1.getDirection() * 4.6 - l1.getCWPerpDirection() * 12.53), -12.53, 0.00001);

//-----

    l3 = l1;

    l2.setBegin(l1.getCenter() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getCenter() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.clipBeginAgainstLineSeg(l2));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection() * 2.5 + l1.getDirection());
    l2.setEnd(l1.getBegin() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.clipBeginAgainstLineSeg(l2));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getBegin() - l1.getCCWPerpDirection() * 2.5 - l1.getDirection());

    BOOST_CHECK(!l1.clipBeginAgainstLineSeg(l2));

    BOOST_CHECK(l1.getBegin() == l3.getBegin());
    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection());
    l2.setEnd(l1.getBegin() + l1.getCCWPerpDirection() * 5.0);

    BOOST_CHECK(!l1.clipBeginAgainstLineSeg(l2));

    BOOST_CHECK(l1.getBegin() == l3.getBegin());
    BOOST_CHECK(l1.getEnd() == l3.getEnd());

//-----

    l1 = l3;

    l2.setBegin(l1.getCenter() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getCenter() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.clipEndAgainstLineSeg(l2));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getBegin() == l3.getBegin());

    l1 = l3;

    l2.setBegin(l1.getEnd() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getEnd() - l1.getCCWPerpDirection() * 2.5 - l1.getDirection());

    BOOST_CHECK(l1.clipEndAgainstLineSeg(l2));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getBegin() == l3.getBegin());

    l1 = l3;

    l2.setBegin(l1.getEnd() + l1.getCCWPerpDirection() * 2.5 + l1.getDirection());
    l2.setEnd(l1.getEnd() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(!l1.clipBeginAgainstLineSeg(l2));

    BOOST_CHECK(l1.getBegin() == l3.getBegin());
    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getEnd() + l1.getCCWPerpDirection());
    l2.setEnd(l1.getEnd() + l1.getCCWPerpDirection() * 5.0);

    BOOST_CHECK(!l1.clipEndAgainstLineSeg(l2));

    BOOST_CHECK(l1.getBegin() == l3.getBegin());
    BOOST_CHECK(l1.getEnd() == l3.getEnd());

//-----

    l3 = l1;

    l2.setBegin(l1.getCenter() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getCenter() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.setBeginToLineSegIntersection(l2));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection() * 2.5 + l1.getDirection());
    l2.setEnd(l1.getBegin() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.setBeginToLineSegIntersection(l2));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getBegin() - l1.getCCWPerpDirection() * 2.5 - l1.getDirection());

    BOOST_CHECK(l1.setBeginToLineSegIntersection(l2));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getEnd() == l3.getEnd());

    l1 = l3;

    l2.setBegin(l1.getBegin() + l1.getCCWPerpDirection());
    l2.setEnd(l1.getBegin() + l1.getCCWPerpDirection() * 5.0);

    BOOST_CHECK(!l1.setBeginToLineSegIntersection(l2));

    BOOST_CHECK(l1.getBegin() == l3.getBegin());
    BOOST_CHECK(l1.getEnd() == l3.getEnd());

//-----

    l1 = l3;

    l2.setBegin(l1.getCenter() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getCenter() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.setEndToLineSegIntersection(l2));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getBegin() == l3.getBegin());

    l1 = l3;

    l2.setBegin(l1.getEnd() + l1.getCCWPerpDirection() * 2.5 - l1.getDirection());
    l2.setEnd(l1.getEnd() - l1.getCCWPerpDirection() * 2.5 - l1.getDirection());

    BOOST_CHECK(l1.setEndToLineSegIntersection(l2));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getBegin() == l3.getBegin());

    l1 = l3;

    l2.setBegin(l1.getEnd() + l1.getCCWPerpDirection() * 2.5 + l1.getDirection());
    l2.setEnd(l1.getEnd() - l1.getCCWPerpDirection() * 2.5 + l1.getDirection());

    BOOST_CHECK(l1.setEndToLineSegIntersection(l2));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), l2.getCenter()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), l2.getCenter()(1), 0.0001);

    BOOST_CHECK(l1.getBegin() == l3.getBegin());

    l1 = l3;

    l2.setBegin(l1.getEnd() + l1.getCCWPerpDirection());
    l2.setEnd(l1.getEnd() + l1.getCCWPerpDirection() * 5.0);

    BOOST_CHECK(!l1.setEndToLineSegIntersection(l2));

    BOOST_CHECK(l1.getBegin() == l3.getBegin());
    BOOST_CHECK(l1.getEnd() == l3.getEnd());

//-----

    Rectangle2D rect(-10.0, 10.0, 10.0, -10.0);

    l1.setPoints(-20.0, 20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(0.0, 20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getBegin()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(20.0, 20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(20.0, 0.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getBegin()(1), 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(20.0, -20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(0.0, -20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getBegin()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(-20.0, -20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setBegin(-20.0, 0.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), -10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getBegin()(1), 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

//-

    l1.setPoints(-20.0, 20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == -20.0);
    BOOST_CHECK(l1.getBegin()(1) == 20.0);

    l1.setPoints(0.0, 20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getEnd()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 0.0);
    BOOST_CHECK(l1.getBegin()(1) == 20.0);

    l1.setPoints(20.0, 20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 20.0);
    BOOST_CHECK(l1.getBegin()(1) == 20.0);

    l1.setPoints(20.0, 0.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), 10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getEnd()(1), 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 20.0);
    BOOST_CHECK(l1.getBegin()(1) == 0.0);

    l1.setPoints(20.0, -20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 20.0);
    BOOST_CHECK(l1.getBegin()(1) == -20.0);

    l1.setPoints(0.0, -20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getEnd()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 0.0);
    BOOST_CHECK(l1.getBegin()(1) == -20.0);

    l1.setPoints(-20.0, -20.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == -20.0);
    BOOST_CHECK(l1.getBegin()(1) == -20.0);

    l1.setPoints(-20.0, 0.0, 0.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), -10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getEnd()(1), 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == -20.0);
    BOOST_CHECK(l1.getBegin()(1) == 0.0);

//-

    l1.setPoints(-20.0, 20.0, 20.0, -20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 20.0);
    BOOST_CHECK(l1.getEnd()(1) == -20.0);

    l1.setPoints(0.0, 20.0, 0.0, -20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getBegin()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == -20.0);

    l1.setPoints(20.0, 20.0, -20.0, -20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == -20.0);
    BOOST_CHECK(l1.getEnd()(1) == -20.0);

    l1.setPoints(20.0, 0.0, -20.0, 0.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), -10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getBegin()(1), 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == -20.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

    l1.setPoints(20.0, -20.0, -20.0, 20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == -20.0);
    BOOST_CHECK(l1.getEnd()(1) == 20.0);

    l1.setPoints(0.0, -20.0, 0.0, 20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getBegin()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 0.0);
    BOOST_CHECK(l1.getEnd()(1) == 20.0);

    l1.setPoints(-20.0, -20.0, 20.0, 20.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getBegin()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 20.0);
    BOOST_CHECK(l1.getEnd()(1) == 20.0);

    l1.setPoints(-20.0, 0.0, 20.0, 0.0);

    BOOST_CHECK(l1.clipBeginAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getBegin()(0), 10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getBegin()(1), 0.0001);

    BOOST_CHECK(l1.getEnd()(0) == 20.0);
    BOOST_CHECK(l1.getEnd()(1) == 0.0);

//-

    l1.setPoints(-20.0, 20.0, 20.0, -20.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == -20.0);
    BOOST_CHECK(l1.getBegin()(1) == 20.0);

    l1.setPoints(0.0, 20.0, 0.0, -20.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getEnd()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 0.0);
    BOOST_CHECK(l1.getBegin()(1) == 20.0);

    l1.setPoints(20.0, 20.0, -20.0, -20.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), 10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 20.0);
    BOOST_CHECK(l1.getBegin()(1) == 20.0);

    l1.setPoints(20.0, 0.0, -20.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), 10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getEnd()(1), 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 20.0);
    BOOST_CHECK(l1.getBegin()(1) == 0.0);

    l1.setPoints(20.0, -20.0, -20.0, 20.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), 10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 20.0);
    BOOST_CHECK(l1.getBegin()(1) == -20.0);

    l1.setPoints(0.0, -20.0, 0.0, 20.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_SMALL(l1.getEnd()(0), 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == 0.0);
    BOOST_CHECK(l1.getBegin()(1) == -20.0);

    l1.setPoints(-20.0, -20.0, 20.0, 20.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), -10.0, 0.0001);
    BOOST_CHECK_CLOSE(l1.getEnd()(1), -10.0, 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == -20.0);
    BOOST_CHECK(l1.getBegin()(1) == -20.0);

    l1.setPoints(-20.0, 0.0, 20.0, 0.0);

    BOOST_CHECK(l1.clipEndAgainstRectangle(rect));

    BOOST_CHECK_CLOSE(l1.getEnd()(0), -10.0, 0.0001);
    BOOST_CHECK_SMALL(l1.getEnd()(1), 0.0001);

    BOOST_CHECK(l1.getBegin()(0) == -20.0);
    BOOST_CHECK(l1.getBegin()(1) == 0.0);

//-

    l1.setPoints(0.0, 0.0, 0.0, 0.0);

    BOOST_CHECK(!l1.clipEndAgainstRectangle(rect));
    BOOST_CHECK(!l1.clipBeginAgainstRectangle(rect));

    l1.setPoints(-8.0, -8.0, 4.0, 4.0);

    BOOST_CHECK(!l1.clipEndAgainstRectangle(rect));
    BOOST_CHECK(!l1.clipBeginAgainstRectangle(rect));

    l1.setPoints(-11.0, 11.0, 4.0, 11.0);

    BOOST_CHECK(!l1.clipEndAgainstRectangle(rect));
    BOOST_CHECK(!l1.clipBeginAgainstRectangle(rect));
}
