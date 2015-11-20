/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CairoFontMetrics.cpp 
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

#include <cairo.h>

#include "CDPL/Vis/CairoFontMetrics.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


struct Vis::CairoFontMetrics::CairoExtents
{

	cairo_font_extents_t fontExtents;
	cairo_text_extents_t textExtents;
};


Vis::CairoFontMetrics::CairoFontMetrics(const CairoPointer<cairo_t>& ctxt_ptr): 
	cairoContext(ctxt_ptr), cairoExtents(new CairoExtents()) 
{
	if (!ctxt_ptr)
		throw Base::NullPointerException("CairoFontMetrics: NULL cairo context pointer");
}

Vis::CairoFontMetrics::~CairoFontMetrics() {}

void Vis::CairoFontMetrics::setFont(const Font& font)
{
	cairo_select_font_face(cairoContext.get(), font.getFamily().c_str(), 
						   font.isItalic() ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
						   font.isBold() ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

	cairo_set_font_size(cairoContext.get(), font.getSize());

	cairo_font_extents(cairoContext.get(), &cairoExtents->fontExtents);
}

double Vis::CairoFontMetrics::getAscent() const
{
	return cairoExtents->fontExtents.ascent;
}

double Vis::CairoFontMetrics::getDescent() const
{
	return cairoExtents->fontExtents.descent;
} 

double Vis::CairoFontMetrics::getHeight() const
{
	return (cairoExtents->fontExtents.ascent + cairoExtents->fontExtents.descent + 1.0);
}

double Vis::CairoFontMetrics::getLeading() const
{
	return (cairoExtents->fontExtents.height - getHeight());
} 

double Vis::CairoFontMetrics::getWidth(const std::string& str) const
{
	cairo_text_extents(cairoContext.get(), str.c_str(), &cairoExtents->textExtents);

	return cairoExtents->textExtents.x_advance;
} 

double Vis::CairoFontMetrics::getWidth(char ch) const
{
	const char str[] = { ch, 0 };

	cairo_text_extents(cairoContext.get(), str, &cairoExtents->textExtents);

	return cairoExtents->textExtents.x_advance;
} 

void Vis::CairoFontMetrics::getBounds(const std::string& str, Rectangle2D& bounds) const
{
	cairo_text_extents_t& text_extents = cairoExtents->textExtents;

	cairo_text_extents(cairoContext.get(), str.c_str(), &text_extents);

	bounds.setBounds(text_extents.x_bearing, text_extents.y_bearing, 
					 text_extents.width + text_extents.x_bearing, 
					 text_extents.height + text_extents.y_bearing);
} 

void Vis::CairoFontMetrics::getBounds(char ch, Rectangle2D& bounds) const
{
	const char str[] = { ch, 0 };

	cairo_text_extents_t& text_extents = cairoExtents->textExtents;

	cairo_text_extents(cairoContext.get(), str, &text_extents);

	bounds.setBounds(text_extents.x_bearing, text_extents.y_bearing, 
					 text_extents.width + text_extents.x_bearing, 
					 text_extents.height + text_extents.y_bearing);
} 
