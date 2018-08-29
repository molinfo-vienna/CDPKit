/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LinePrimitive2D.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/LinePrimitive2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


using namespace CDPL;


void Vis::LinePrimitive2D::render(Renderer2D& renderer) const
{
	const Math::Vector2D& beg = getBegin();
	const Math::Vector2D& end = getEnd();

	renderer.setPen(pen);
	renderer.drawLine(beg(0), beg(1), end(0), end(1));
}

void Vis::LinePrimitive2D::setPen(const Pen& pen)
{
	this->pen = pen;
}

const Vis::Pen& Vis::LinePrimitive2D::getPen() const
{
	return pen;
}

Vis::GraphicsPrimitive2D::SharedPointer Vis::LinePrimitive2D::clone() const
{
	return SharedPointer(new LinePrimitive2D(*this));
}

void Vis::LinePrimitive2D::getBounds(Rectangle2D& bounds, FontMetrics* fm) const
{
	bounds.addPoint(getBegin());
	bounds.addPoint(getEnd());
	bounds.addMargin(pen.getWidth() * 0.5, pen.getWidth() * 0.5);
}
