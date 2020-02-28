/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * EllipsePrimitive2D.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/EllipsePrimitive2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


using namespace CDPL;


void Vis::EllipsePrimitive2D::render(Renderer2D& renderer) const
{
	renderer.setPen(pen);
	renderer.setBrush(brush);

	renderer.drawEllipse(position(0), position(1), width, height);
}

void Vis::EllipsePrimitive2D::setPen(const Pen& pen)
{
	this->pen = pen;
}

const Vis::Pen& Vis::EllipsePrimitive2D::getPen() const
{
	return pen;
}

void Vis::EllipsePrimitive2D::setBrush(const Brush& brush)
{
	this->brush = brush;
}

const Vis::Brush& Vis::EllipsePrimitive2D::getBrush() const
{
	return brush;
}

void Vis::EllipsePrimitive2D::setPosition(const Math::Vector2D& pos)
{
	position = pos;
}

const Math::Vector2D& Vis::EllipsePrimitive2D::getPosition() const
{
	return position;
}

void Vis::EllipsePrimitive2D::setWidth(double width)
{
	this->width = width;
}

double Vis::EllipsePrimitive2D::getWidth() const
{
	return width;
}

void Vis::EllipsePrimitive2D::setHeight(double height)
{
	this->height = height;
}

double Vis::EllipsePrimitive2D::getHeight() const
{
	return height;
}

Vis::GraphicsPrimitive2D::SharedPointer Vis::EllipsePrimitive2D::clone() const
{
	return SharedPointer(new EllipsePrimitive2D(*this));
}

void Vis::EllipsePrimitive2D::getBounds(Rectangle2D& bounds, FontMetrics* fm) const
{
	bounds.setBounds(position(0) - width * 0.5, position(1) - height * 0.5, 
					 position(0) + width * 0.5, position(1) + height * 0.5);
	bounds.addMargin(pen.getWidth() * 0.5, pen.getWidth() * 0.5);
}
