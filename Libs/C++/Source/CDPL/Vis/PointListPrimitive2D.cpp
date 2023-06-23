/* 
 * PointListPrimitive2D.cpp 
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

#include "CDPL/Vis/PointListPrimitive2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


using namespace CDPL;


void Vis::PointListPrimitive2D::render(Renderer2D& renderer) const
{
    renderer.setPen(pen);

    ConstElementIterator points_end = getElementsEnd();

    for (ConstElementIterator p_it = getElementsBegin(); p_it != points_end; ++p_it) {
        const Math::Vector2D& pos = *p_it;

        renderer.drawPoint(pos(0), pos(1));
    }
}

void Vis::PointListPrimitive2D::setPen(const Pen& pen)
{
    this->pen = pen;
}

const Vis::Pen& Vis::PointListPrimitive2D::getPen() const
{
    return pen;
}

Vis::GraphicsPrimitive2D::SharedPointer Vis::PointListPrimitive2D::clone() const
{
    return SharedPointer(new PointListPrimitive2D(*this));
}

void Vis::PointListPrimitive2D::getBounds(Rectangle2D& bounds, FontMetrics* fm) const
{
    PointArray2D::getBounds(bounds);
    bounds.addMargin(pen.getWidth() * 0.5, pen.getWidth() * 0.5);
}
