/* 
 * Line2D.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "StaticInit.hpp"

#include <cmath>

#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


using namespace CDPL;


Vis::Line2D::Line2D() {}

Vis::Line2D::Line2D(const Math::Vector2D& beg, const Math::Vector2D& end): begin(beg), end(end) {}

Vis::Line2D::Line2D(double beg_x, double beg_y, double end_x, double end_y)
{
    begin(0) = beg_x;
    begin(1) = beg_y;

    end(0) = end_x;
    end(1) = end_y;
}

void Vis::Line2D::setBegin(const Math::Vector2D& pt)
{
    begin = pt;
}

void Vis::Line2D::setBegin(double x, double y)
{
    begin(0) = x;
    begin(1) = y;
}

const Math::Vector2D& Vis::Line2D::getBegin() const
{
    return begin;
}

void Vis::Line2D::setEnd(const Math::Vector2D& pt)
{
    end = pt;
}

void Vis::Line2D::setEnd(double x, double y)
{
    end(0) = x;
    end(1) = y;
}

const Math::Vector2D& Vis::Line2D::getEnd() const
{
    return end;
}

void Vis::Line2D::setPoints(const Math::Vector2D& beg, const Math::Vector2D& end)
{
    begin = beg;
    this->end = end;
}

void Vis::Line2D::setPoints(double beg_x, double beg_y, double end_x, double end_y)
{
    begin(0) = beg_x;
    begin(1) = beg_y;

    end(0) = end_x;
    end(1) = end_y;
}

void Vis::Line2D::swapPoints()
{
    begin.swap(end);
}

void Vis::Line2D::getDirection(Math::Vector2D& dir) const
{
    dir = end - begin;
    dir /= norm2(dir);
}

Math::Vector2D Vis::Line2D::getDirection() const
{
    Math::Vector2D dir;

    getDirection(dir);

    return dir;
}

void Vis::Line2D::getCCWPerpDirection(Math::Vector2D& dir) const
{
    getDirection(dir);

    double x = dir(0);

    dir(0) = -dir(1);
    dir(1) = x;
}

Math::Vector2D Vis::Line2D::getCCWPerpDirection() const
{
    Math::Vector2D dir;

    getCCWPerpDirection(dir);

    return dir;
}

void Vis::Line2D::getCWPerpDirection(Math::Vector2D& dir) const
{
    getDirection(dir);

    double x = dir(0);

    dir(0) = dir(1);
    dir(1) = -x;
}

Math::Vector2D Vis::Line2D::getCWPerpDirection() const
{
    Math::Vector2D dir;

    getCWPerpDirection(dir);

    return dir;
}

void Vis::Line2D::getCenter(Math::Vector2D& ctr) const
{
    ctr = (begin + end) * 0.5;
}

Math::Vector2D Vis::Line2D::getCenter() const
{
    return ((begin + end) * 0.5);
}

double Vis::Line2D::getLength() const
{
    return norm2(end - begin);
}

void Vis::Line2D::translate(const Math::Vector2D& vec)
{
    begin += vec;
    end += vec;
}

void Vis::Line2D::translateBegin(const Math::Vector2D& vec)
{
    begin += vec;
}

void Vis::Line2D::translateEnd(const Math::Vector2D& vec)
{
    end += vec;
}

bool Vis::Line2D::containsPoint(const Math::Vector2D& pt) const
{
    Math::Vector2D dir = getDirection();

    if (innerProd(dir, (pt - begin)) < 0.0)
        return false;

    if (innerProd(dir, (pt - end)) > 0.0)
        return false;

    return true;
}

bool Vis::Line2D::getIntersectionPoint(const Line2D& line, Math::Vector2D& pt) const
{
    double a1 = end(1) - begin(1);
    double b1 = begin(0) - end(0);

    double a2 = line.end(1) - line.begin(1);
    double b2 = line.begin(0) - line.end(0);

    double denom = a1 * b2 - a2 * b1;

    if (denom == 0.0)
        return false;

    double c1 = end(0) * begin(1) - begin(0) * end(1);
    double c2 = line.end(0) * line.begin(1) - line.begin(0) * line.end(1);

    pt(0) = (b1 * c2 - b2 * c1) / denom;
    pt(1) = (a2 * c1 - a1 * c2) / denom;

    return true;
}

bool Vis::Line2D::clipBeginAgainstLineSeg(const Line2D& line)
{
    Math::Vector2D inters_pt;

    if (!getIntersectionPoint(line, inters_pt))
        return false;

    if (line.containsPoint(inters_pt) && containsPoint(inters_pt)) {
        begin = inters_pt;

        return true;
    }

    return false;
}

bool Vis::Line2D::clipEndAgainstLineSeg(const Line2D& line)
{
    Math::Vector2D inters_pt;

    if (!getIntersectionPoint(line, inters_pt))
        return false;

    if (line.containsPoint(inters_pt) && containsPoint(inters_pt)) {
        end = inters_pt;

        return true;
    }

    return false;
}

bool Vis::Line2D::setBeginToLineSegIntersection(const Line2D& line)
{
    Math::Vector2D inters_pt;

    if (!getIntersectionPoint(line, inters_pt))
        return false;

    if (!line.containsPoint(inters_pt))
        return false;

    begin = inters_pt;

    return true;
}

bool Vis::Line2D::setEndToLineSegIntersection(const Line2D& line)
{
    Math::Vector2D inters_pt;

    if (!getIntersectionPoint(line, inters_pt))
        return false;

    if (!line.containsPoint(inters_pt))
        return false;

    end = inters_pt;

    return true;
}

bool Vis::Line2D::clipBeginAgainstRectangle(const Rectangle2D& rect)
{
    const Math::Vector2D& rect_min = rect.getMin(); 
    const Math::Vector2D& rect_max = rect.getMax(); 

    Line2D rect_side;
    Math::Vector2D inters_pt;

    rect_side.begin = rect_min;

    rect_side.end(0) = rect_max(0);
    rect_side.end(1) = rect_min(1);

    bool clipped = false;

    clipped |= clipBeginAgainstLineSeg(rect_side);

    rect_side.begin = rect_max;

    clipped |= clipBeginAgainstLineSeg(rect_side);

    rect_side.end(0) = rect_min(0);
    rect_side.end(1) = rect_max(1);

    clipped |= clipBeginAgainstLineSeg(rect_side);

    rect_side.begin = rect_min;

    clipped |= clipBeginAgainstLineSeg(rect_side);

    return clipped;
}

bool Vis::Line2D::clipEndAgainstRectangle(const Rectangle2D& rect)
{
    const Math::Vector2D& rect_min = rect.getMin(); 
    const Math::Vector2D& rect_max = rect.getMax(); 

    Line2D rect_side;
    Math::Vector2D inters_pt;

    rect_side.begin = rect_min;

    rect_side.end(0) = rect_max(0);
    rect_side.end(1) = rect_min(1);

    bool clipped = false;

    clipped |= clipEndAgainstLineSeg(rect_side);

    rect_side.begin = rect_max;

    clipped |= clipEndAgainstLineSeg(rect_side);

    rect_side.end(0) = rect_min(0);
    rect_side.end(1) = rect_max(1);

    clipped |= clipEndAgainstLineSeg(rect_side);

    rect_side.begin = rect_min;

    clipped |= clipEndAgainstLineSeg(rect_side);

    return clipped;
}

double Vis::Line2D::getDistance(const Math::Vector2D& pt) const
{
    double dx = end(0) - begin(0);
    double dy = end(1) - begin(1);

    return ((dx * (begin(1) - pt(1)) - (begin(0) - pt(0)) * dy) / std::sqrt(dx * dx + dy * dy)); 
}

bool Vis::Line2D::operator==(const Line2D& line) const
{
    return (begin == line.begin && end == line.end);
}

bool Vis::Line2D::operator!=(const Line2D& line) const
{
    return !operator==(line);
}

