/* 
 * Rectangle2D.cpp 
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

#include "CDPL/Vis/Rectangle2D.hpp"


using namespace CDPL;


Vis::Rectangle2D::Rectangle2D() 
{
    reset();
}

Vis::Rectangle2D::Rectangle2D(const Math::Vector2D& min, const Math::Vector2D& max): min(min), max(max) {}

Vis::Rectangle2D::Rectangle2D(double min_x, double min_y, double max_x, double max_y)
{
    min(0) = min_x;
    min(1) = min_y;

    max(0) = max_x;
    max(1) = max_y;
}

bool Vis::Rectangle2D::isDefined() const
{
    return (max(0) >= min(0) && max(1) >= min(1));
}

void Vis::Rectangle2D::addPoint(const Math::Vector2D& pt)
{
    addPoint(pt(0), pt(1));
}

void Vis::Rectangle2D::addPoint(double x, double y)
{
    if (x < min(0))
        min(0) = x;

    if (y < min(1))
        min(1) = y;

    if (x > max(0))
        max(0) = x;

    if (y > max(1))
        max(1) = y;
}

void Vis::Rectangle2D::addMargin(double width, double height)
{
    min(0) -= width;
    min(1) -= height;

    max(0) += width;
    max(1) += height;
}

void Vis::Rectangle2D::addRectangle(const Rectangle2D& rect)
{
    if (!rect.isDefined())
        return;
    
    addPoint(rect.min);
    addPoint(rect.max);
}

bool Vis::Rectangle2D::containsPoint(const Math::Vector2D& pt) const
{
    return (pt(0) >= min(0) && pt(0) <= max(0) && pt(1) >= min(1) && pt(1) <= max(1));
}

bool Vis::Rectangle2D::containsPoint(double x, double y) const
{
    return (x >= min(0) && x <= max(0) && y >= min(1) && y <= max(1));
}

bool Vis::Rectangle2D::containsRectangle(const Rectangle2D& rect) const
{
    return (containsPoint(rect.min) && containsPoint(rect.max));
}

bool Vis::Rectangle2D::intersectsRectangle(const Rectangle2D& rect) const
{
    return !(min(0) > rect.max(0) || min(1) > rect.max(1) 
             || max(0) < rect.min(0) || max(1) < rect.min(1));
}

void Vis::Rectangle2D::setMin(const Math::Vector2D& pt)
{
    min = pt;
}

void Vis::Rectangle2D::setMin(double x, double y)
{
    min(0) = x;
    min(1) = y;
}

void Vis::Rectangle2D::setMax(const Math::Vector2D& pt)
{
    max = pt;
}

void Vis::Rectangle2D::setMax(double x, double y)
{
    max(0) = x;
    max(1) = y;
}

void Vis::Rectangle2D::setBounds(double min_x, double min_y, double max_x, double max_y)
{
    min(0) = min_x;
    min(1) = min_y;

    max(0) = max_x;
    max(1) = max_y;
}

void Vis::Rectangle2D::setBounds(const Math::Vector2D& min, const Math::Vector2D& max)
{
    this->min = min;
    this->max = max;
}

const Math::Vector2D& Vis::Rectangle2D::getMin() const
{
    return min;
}

const Math::Vector2D& Vis::Rectangle2D::getMax() const
{
    return max;
}

Math::Vector2D Vis::Rectangle2D::getCenter() const
{
    return ((min + max) / 2);
}

void Vis::Rectangle2D::getCenter(Math::Vector2D& ctr) const
{
    ctr = (min + max) / 2;
}

double Vis::Rectangle2D::getWidth() const
{
    return (max(0) - min(0));
}

double Vis::Rectangle2D::getHeight() const
{
    return (max(1) - min(1));
}

double Vis::Rectangle2D::getArea() const
{
    return ((max(0) - min(0)) * (max(1) - min(1)));
}

void Vis::Rectangle2D::reset()
{
    const double dbl_max = std::numeric_limits<double>::max();

    min(0) = dbl_max;
    min(1) = dbl_max;

    max(0) = -dbl_max;
    max(1) = -dbl_max;
}

void Vis::Rectangle2D::translate(const Math::Vector2D& vec)
{
    min += vec;
    max += vec;
}

void Vis::Rectangle2D::scale(double factor)
{
    min *= factor;
    max *= factor;
}

bool Vis::Rectangle2D::operator==(const Rectangle2D& rect) const
{
    return (min == rect.min && max == rect.max);
}

bool Vis::Rectangle2D::operator!=(const Rectangle2D& rect) const
{
    return !operator==(rect);
}
