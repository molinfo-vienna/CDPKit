/* 
 * Path2D.cpp 
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

#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Vis/Path2DConverter.hpp"


using namespace CDPL;


struct Vis::Path2D::Element
{

    enum Command
    {

        MOVE_TO,
        LINE_TO,
        ARC_TO,
        CLOSE_PATH
    };

    bool operator==(const Element& elem) const
    {
        if (command != elem.command)
            return false;

        for (unsigned int i = 0; i < sizeof(data) / sizeof(double); i++)
            if (data[i] != elem.data[i])
                return false;

        return true;
    }

    Command command;
    double  data[6];
};


Vis::Path2D::Path2D():
    fillRule(EVEN_ODD)
{}

Vis::Path2D::Path2D(const Path2D& path):
    fillRule(path.fillRule), elements(path.elements)
{}

Vis::Path2D::~Path2D() {}

bool Vis::Path2D::isEmpty() const
{
    return elements.empty();
}

void Vis::Path2D::clear()
{
    fillRule = EVEN_ODD;
    elements.clear();
}
        
void Vis::Path2D::setFillRule(FillRule rule)
{
    fillRule = rule;
}

Vis::Path2D::FillRule Vis::Path2D::getFillRule() const
{
    return fillRule;
}

void Vis::Path2D::moveTo(double x, double y)
{
    elements.push_back({Element::MOVE_TO, x, y});
}

void Vis::Path2D::moveTo(const Math::Vector2D& pos)
{
    moveTo(pos(0), pos(1));
}
            
void Vis::Path2D::arc(double cx, double cy, double rx, double ry, double start_ang, double sweep)
{
    moveTo(std::cos(start_ang) * rx + cx, std::sin(start_ang) * ry + cy);
    arcTo(cx, cy, rx, ry, start_ang, sweep);
}

void Vis::Path2D::arc(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep)
{
    arc(ctr(0), ctr(1), rx, ry, start_ang, sweep);
}

void Vis::Path2D::arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep)
{
    elements.push_back({Element::ARC_TO, cx, cy, rx, ry, start_ang, sweep});
}

void Vis::Path2D::arcTo(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep)
{
    arcTo(ctr(0), ctr(1), rx, ry, start_ang, sweep);
}

void Vis::Path2D::lineTo(double x, double y)
{
    elements.push_back({Element::LINE_TO, x, y});
}

void Vis::Path2D::lineTo(const Math::Vector2D& pos)
{
    lineTo(pos(0), pos(1));
}

void Vis::Path2D::closePath()
{
    elements.push_back({Element::CLOSE_PATH});
}

void Vis::Path2D::convert(Path2DConverter& conv) const
{
    for (const auto& elem : elements) {

        switch (elem.command) {

            case Element::MOVE_TO:
                conv.moveTo(elem.data[0], elem.data[1]);
                continue;
                
            case Element::LINE_TO:
                conv.lineTo(elem.data[0], elem.data[1]);
                continue;
                
            case Element::ARC_TO:
                conv.arcTo(elem.data[0], elem.data[1], elem.data[2],
                           elem.data[3], elem.data[4], elem.data[5]);
                continue;
                
            case Element::CLOSE_PATH:
                conv.closePath();
                
            default:
                continue;
        }
    }
}

bool Vis::Path2D::operator==(const Path2D& path) const
{
    if (fillRule != path.fillRule)
        return false;

    return (elements == path.elements);
}

bool Vis::Path2D::operator!=(const Path2D& path) const
{
    return !operator==(path);
}

Vis::Path2D& Vis::Path2D::operator+=(const Path2D& path)
{
    if (this == &path)
        elements.reserve(path.elements.size() * 2);
    
    elements.insert(elements.end(), path.elements.begin(), path.elements.end());

    return *this;
}

Vis::Path2D& Vis::Path2D::operator=(const Path2D& path)
{
    if (this == &path)
        return *this;

    fillRule = path.fillRule;
    elements = path.elements;

    return *this;
}
