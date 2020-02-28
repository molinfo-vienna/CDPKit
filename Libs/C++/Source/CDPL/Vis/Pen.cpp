/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Pen.cpp 
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

#include "CDPL/Vis/Pen.hpp"


using namespace CDPL;


Vis::Pen::Pen(): color(Color::BLACK), lineStyle(SOLID_LINE), capStyle(ROUND_CAP), joinStyle(ROUND_JOIN), width(1.0) {}

Vis::Pen::Pen(LineStyle line_style): color(Color::BLACK), lineStyle(line_style), capStyle(ROUND_CAP), joinStyle(ROUND_JOIN), width(1.0) {}

Vis::Pen::Pen(const Color& color, double width, LineStyle line_style, CapStyle cap_style, JoinStyle join_style): 
	color(color), lineStyle(line_style), capStyle(cap_style), joinStyle(join_style), width(width < 0.0 ? 0.0 : width) {}

void Vis::Pen::setLineStyle(LineStyle line_style)
{
	lineStyle = line_style;
} 

Vis::Pen::LineStyle Vis::Pen::getLineStyle() const 
{
	return lineStyle;
}

void Vis::Pen::setWidth(double width)
{
	this->width = (width < 0.0 ? 0.0 : width);
} 

double Vis::Pen::getWidth() const 
{
	return width;
}

void Vis::Pen::setColor(const Color& color)
{
	this->color = color;
} 

const Vis::Color& Vis::Pen::getColor() const 
{
	return color;
}

void Vis::Pen::setCapStyle(CapStyle cap_style)
{
	capStyle = cap_style;
} 

Vis::Pen::CapStyle Vis::Pen::getCapStyle() const 
{
	return capStyle;
}

void Vis::Pen::setJoinStyle(JoinStyle join_style)
{
	joinStyle = join_style;
} 

Vis::Pen::JoinStyle Vis::Pen::getJoinStyle() const
{
	return joinStyle;
} 

bool Vis::Pen::operator==(const Pen& pen) const
{
	return (width == pen.width && lineStyle == pen.lineStyle 
			&& joinStyle == pen.joinStyle && capStyle == pen.capStyle 
			&& color == pen.color); 
}

bool Vis::Pen::operator!=(const Pen& pen) const
{
	return !operator==(pen);
}
