/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CairoFontMetricsTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <cairo.h>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/CairoFontMetrics.hpp"
#include "CDPL/Vis/CairoPointer.hpp"
#include "CDPL/Vis/CairoRenderer2D.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"


BOOST_AUTO_TEST_CASE(CairoFontMetricsTest)
{
	using namespace CDPL;
	using namespace Vis;

	CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 500, 300));

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoRenderer2D renderer(ctxt_ptr);
	CairoFontMetrics fm(ctxt_ptr);

	Rectangle2D bounds;

//-----

	double y = 40.0;

	Font font = Font();
	std::string text = "Default Font";

	renderer.setPen(Color::BLUE);
	renderer.setFont(font);

	renderer.drawText(10.0, y, text);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.setFont(font);
	fm.getBounds(text, bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::GREEN);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::YELLOW);
	renderer.drawLine(bounds.getMin()(0), y, bounds.getMin()(0) + fm.getWidth(text), y);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(50.0, y, 50.0, y - fm.getAscent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.drawLine(70.0, y, 70.0, y + fm.getDescent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(5.0, bounds.getMax()(1), 5.0, bounds.getMax()(1) - fm.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.getBounds(text[0], bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::RED);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(bounds.getMin()(0), y - 4.0, bounds.getMin()(0) + fm.getWidth(text[0]), y - 4.0);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//-----

	y += 50.0;

	font = Font("Helvetica", 35.0);
	text = "Helvetica; 35";

	renderer.setPen(Color::BLUE);
	renderer.setFont(font);

	renderer.drawText(10.0, y, text);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.setFont(font);
	fm.getBounds(text, bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::GREEN);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::YELLOW);
	renderer.drawLine(bounds.getMin()(0), y, bounds.getMin()(0) + fm.getWidth(text), y);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(50.0, y, 50.0, y - fm.getAscent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.drawLine(70.0, y, 70.0, y + fm.getDescent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(5.0, bounds.getMax()(1), 5.0, bounds.getMax()(1) - fm.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.getBounds(text[0], bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::RED);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(bounds.getMin()(0), y - 4.0, bounds.getMin()(0) + fm.getWidth(text[0]), y - 4.0);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//-----

	y += 50.0;

	font = Font("Times", 35.0);
	font.setBold(true);

	text = "Times; 35; bold";

	renderer.setPen(Color::BLUE);
	renderer.setFont(font);

	renderer.drawText(10.0, y, text);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.setFont(font);
	fm.getBounds(text, bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::GREEN);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::YELLOW);
	renderer.drawLine(bounds.getMin()(0), y, bounds.getMin()(0) + fm.getWidth(text), y);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(50.0, y, 50.0, y - fm.getAscent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.drawLine(70.0, y, 70.0, y + fm.getDescent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(5.0, bounds.getMax()(1), 5.0, bounds.getMax()(1) - fm.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.getBounds(text[0], bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::RED);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(bounds.getMin()(0), y - 4.0, bounds.getMin()(0) + fm.getWidth(text[0]), y - 4.0);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//-----

	y += 50.0;

	font = Font("Courier", 35.0);
	font.setItalic(true);

	text = "Courier; 35; italic";

	renderer.setPen(Color::BLUE);
	renderer.setFont(font);

	renderer.drawText(10.0, y, text);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.setFont(font);
	fm.getBounds(text, bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::GREEN);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::YELLOW);
	renderer.drawLine(bounds.getMin()(0), y, bounds.getMin()(0) + fm.getWidth(text), y);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(50.0, y, 50.0, y - fm.getAscent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.drawLine(70.0, y, 70.0, y + fm.getDescent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(5.0, bounds.getMax()(1), 5.0, bounds.getMax()(1) - fm.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.getBounds(text[0], bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::RED);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(bounds.getMin()(0), y - 4.0, bounds.getMin()(0) + fm.getWidth(text[0]), y - 4.0);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//-----

	y += 50.0;

	font = Font("Default", 35.0);
	font.setBold(true);
	font.setItalic(true);

	text = "Default; 35; bold; italic";

	renderer.setPen(Color::BLUE);
	renderer.setFont(font);

	renderer.drawText(10.0, y, text);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.setFont(font);
	fm.getBounds(text, bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::GREEN);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::YELLOW);
	renderer.drawLine(bounds.getMin()(0), y, bounds.getMin()(0) + fm.getWidth(text), y);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(50.0, y, 50.0, y - fm.getAscent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.drawLine(70.0, y, 70.0, y + fm.getDescent());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(5.0, bounds.getMax()(1), 5.0, bounds.getMax()(1) - fm.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	fm.getBounds(text[0], bounds);

	bounds.translate(Math::vec(10.0, y));

	renderer.setPen(Color::RED);
	renderer.drawRectangle(bounds.getMin()(0), bounds.getMin()(1), bounds.getWidth(), bounds.getHeight());

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setPen(Color::MAGENTA);
	renderer.drawLine(bounds.getMin()(0), y - 4.0, bounds.getMin()(0) + fm.getWidth(text[0]), y - 4.0);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//-----

	BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoFontMetricsTest.png") == CAIRO_STATUS_SUCCESS);
}

