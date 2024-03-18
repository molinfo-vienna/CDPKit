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

#include <cstddef>
#include <cmath>
#include <utility>

#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Vis/Path2DConverter.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Math/Vector.hpp"


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

        for (std::size_t i = 0; i < sizeof(data) / sizeof(double); i++)
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

bool Vis::Path2D::hasDrawingElements() const
{
    for (const auto& elem : elements)
        switch (elem.command) {

            case Element::LINE_TO:
            case Element::ARC_TO:
                return true;
                
            default:
                continue;
        }

    return false;
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
    elements.push_back({Element::MOVE_TO, {x, y}});
}

void Vis::Path2D::moveTo(const Math::Vector2D& pos)
{
    moveTo(pos(0), pos(1));
}
            
void Vis::Path2D::arc(double cx, double cy, double rx, double ry, double start_ang, double sweep)
{
    moveTo(std::cos(start_ang / 180.0 * M_PI) * rx + cx, std::sin(start_ang / 180.0 * M_PI) * ry + cy);
    arcTo(cx, cy, rx, ry, start_ang, sweep);
}

void Vis::Path2D::arc(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep)
{
    arc(ctr(0), ctr(1), rx, ry, start_ang, sweep);
}

void Vis::Path2D::arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep)
{
    elements.push_back({Element::ARC_TO, {cx, cy, rx, ry, start_ang, sweep}});
}

void Vis::Path2D::arcTo(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep)
{
    arcTo(ctr(0), ctr(1), rx, ry, start_ang, sweep);
}

void Vis::Path2D::lineTo(double x, double y)
{
    elements.push_back({Element::LINE_TO, {x, y}});
}

void Vis::Path2D::lineTo(const Math::Vector2D& pos)
{
    lineTo(pos(0), pos(1));
}

void Vis::Path2D::closePath()
{
    elements.push_back({Element::CLOSE_PATH});
}

void Vis::Path2D::addEllipse(double x, double y, double width, double height)
{
    moveTo(x + width * 0.5, y);
    arcTo(x, y, width * 0.5, height * 0.5, 0.0, 360.0);
    closePath();
}

void Vis::Path2D::addEllipse(const Math::Vector2D& pos, double width, double height)
{
    addEllipse(pos(0), pos(1), width, height);
}

void Vis::Path2D::addRectangle(double x, double y, double width, double height)
{
    moveTo(x, y);
    lineTo(x + width, y);
    lineTo(x + width, y + height);
    lineTo(x, y + height);
    closePath();
}

void Vis::Path2D::addRectangle(const Math::Vector2D& pos, double width, double height)
{
    addRectangle(pos(0), pos(1), width, height);
}

void Vis::Path2D::getBounds(Rectangle2D& bounds) const
{
    bounds.reset();

    double start_x = 0.0, start_y = 0.0;
    bool start_pos_added = false;
    
    for (const auto& elem : elements) {
        switch (elem.command) {

            case Element::LINE_TO:
                if (!start_pos_added) {
                    bounds.addPoint(start_x, start_y);
                    start_pos_added = true;
                }

                bounds.addPoint(elem.data[0], elem.data[1]);
                continue;
                
            case Element::ARC_TO: {
                if (!start_pos_added) {
                    bounds.addPoint(start_x, start_y);
                    start_pos_added = true;
                }

                double cx = elem.data[0];
                double cy = elem.data[1];
                double rx = elem.data[2];
                double ry = elem.data[3];
                double start_ang = elem.data[4] / 180.0 * M_PI;
                double sweep = elem.data[5] / 180.0 * M_PI;
                double end_ang = start_ang + sweep;

                if (sweep < 0.0)
                    std::swap(start_ang, end_ang);
                
                bounds.addPoint(cx + std::cos(start_ang) * rx, cy + std::sin(start_ang) * ry);
                bounds.addPoint(cx + std::cos(end_ang) * rx, cy + std::sin(end_ang) * ry);

                if (start_ang < 0.0) {
                    double offs = std::ceil(-start_ang / (2.0 * M_PI)) * 2.0 * M_PI;

                    start_ang += offs;
                    end_ang += offs;
                }

                std::size_t start_quad = std::floor(start_ang / (M_PI * 0.5));
                std::size_t end_quad = std::floor(end_ang / (M_PI * 0.5));

                if ((end_quad - start_quad) > 4)
                    end_quad = start_quad + 4;

                double limits[4][2] = {
                    { cx,      cy + ry },
                    { cx - rx, cy      },
                    { cx,      cy - ry },
                    { cx + rx, cy      }
                };

                for ( ; start_quad < end_quad; start_quad++)
                    bounds.addPoint(limits[start_quad % 4][0], limits[start_quad % 4][1]);
                
                continue;
            }
                
            case Element::MOVE_TO:
                start_x = elem.data[0];
                start_y = elem.data[1];
                start_pos_added = false;

            default:
                continue;
        }
    }
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
