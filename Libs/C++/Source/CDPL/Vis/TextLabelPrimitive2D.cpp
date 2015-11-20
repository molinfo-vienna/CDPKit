/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TextLabelPrimitive2D.cpp 
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

#include "CDPL/Vis/TextLabelPrimitive2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL;


Vis::TextLabelPrimitive2D::TextLabelPrimitive2D() {}

void Vis::TextLabelPrimitive2D::render(Renderer2D& renderer) const
{
	renderer.setPen(pen);
	renderer.setFont(font);

	renderer.drawText(position(0), position(1), text);
}

void Vis::TextLabelPrimitive2D::setText(const std::string& txt)
{
	text = txt;
}

const std::string& Vis::TextLabelPrimitive2D::getText() const
{
	return text;
}

void Vis::TextLabelPrimitive2D::setPosition(const Math::Vector2D& pos)
{
	position = pos;
}

void Vis::TextLabelPrimitive2D::setPosition(double x, double y)
{
	position(0) = x;
	position(1) = y;
}

const Math::Vector2D& Vis::TextLabelPrimitive2D::getPosition() const
{
	return position;
}

void Vis::TextLabelPrimitive2D::setPen(const Pen& pen)
{
	this->pen = pen;
}

const Vis::Pen& Vis::TextLabelPrimitive2D::getPen() const
{
	return pen;
}

void Vis::TextLabelPrimitive2D::setFont(const Font& font)
{
	this->font = font;
}

const Vis::Font& Vis::TextLabelPrimitive2D::getFont() const
{
	return font;
}	
