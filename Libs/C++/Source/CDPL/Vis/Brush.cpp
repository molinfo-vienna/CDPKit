/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Brush.cpp 
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

#include "CDPL/Vis/Brush.hpp"


using namespace CDPL;


Vis::Brush::Brush(): style(NO_PATTERN), color(Color::BLACK) {}

Vis::Brush::Brush(Style style): style(style), color(Color::BLACK) {}

Vis::Brush::Brush(const Color& color, Style style): style(style), color(color) {} 

void Vis::Brush::setStyle(Style style)
{
	this->style = style;
}

Vis::Brush::Style Vis::Brush::getStyle() const
{
	return style;
} 

void Vis::Brush::setColor(const Color& color)
{
	this->color = color;
} 

const Vis::Color& Vis::Brush::getColor() const
{
	return color;
} 

bool Vis::Brush::operator==(const Brush& brush) const
{
	return (color == brush.color && style == brush.style);
}

bool Vis::Brush::operator!=(const Brush& brush) const
{
	return !operator==(brush);
}
