/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * EllipsePrimitive2DTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <cstddef>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Vis/EllipsePrimitive2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Color.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


namespace
{

	void checkClone(const CDPL::Vis::EllipsePrimitive2D& prim)
	{
		using namespace CDPL;
		using namespace Vis;

		GraphicsPrimitive2D::SharedPointer gp_clone_ptr = prim.clone();
		const EllipsePrimitive2D* prim_clone_ptr = static_cast<const EllipsePrimitive2D*>(gp_clone_ptr.get());

		BOOST_CHECK(prim_clone_ptr->getPosition() == prim.getPosition());
		BOOST_CHECK(prim_clone_ptr->getPen() == prim.getPen());
		BOOST_CHECK(prim_clone_ptr->getBrush() == prim.getBrush());
		BOOST_CHECK(prim_clone_ptr->getWidth() == prim.getWidth());
		BOOST_CHECK(prim_clone_ptr->getHeight() == prim.getHeight());
	}
}


BOOST_AUTO_TEST_CASE(EllipsePrimitive2DTest)
{
	using namespace CDPL;
	using namespace Vis;

	EllipsePrimitive2D ep;

	BOOST_CHECK(ep.getPen() == Pen());
	BOOST_CHECK(ep.getBrush() == Brush());
	BOOST_CHECK(ep.getWidth() == 0.0);
	BOOST_CHECK(ep.getHeight() == 0.0);

	checkClone(ep);

	ep.setPen(Pen(Color::RED, 2.3, Pen::DOT_LINE));

	BOOST_CHECK(ep.getPen() == Pen(Color::RED, 2.3, Pen::DOT_LINE));
	BOOST_CHECK(ep.getBrush() == Brush());

	checkClone(ep);

	ep.setBrush(Brush::DENSE1_PATTERN);

	BOOST_CHECK(ep.getPen() == Pen(Color::RED, 2.3, Pen::DOT_LINE));
	BOOST_CHECK(ep.getBrush() == Brush(Brush::DENSE1_PATTERN));

	checkClone(ep);

//-----

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

	CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 500));

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoRenderer2D renderer(ctxt_ptr);

	Pen test_pens[] = {
		Pen(Color::BLACK, 0.0, Pen::NO_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN),
		Pen(Color::BLACK, 0.5, Pen::SOLID_LINE, Pen::ROUND_CAP, Pen::BEVEL_JOIN),
		Pen(Color::BLACK, 0.5, Pen::DASH_LINE, Pen::ROUND_CAP, Pen::ROUND_JOIN),
		Pen(Color::BLACK, 0.5, Pen::DOT_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN),
		Pen(Color::BLACK, 0.5, Pen::DASH_DOT_LINE, Pen::ROUND_CAP, Pen::BEVEL_JOIN),
		Pen(Color::BLACK, 0.5, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP, Pen::ROUND_JOIN),
		
		Pen(Color::RED, 1.0, Pen::NO_LINE, Pen::FLAT_CAP, Pen::BEVEL_JOIN),
		Pen(Color::RED, 1.0, Pen::SOLID_LINE, Pen::FLAT_CAP, Pen::ROUND_JOIN),
		Pen(Color::RED, 1.0, Pen::DASH_LINE, Pen::FLAT_CAP, Pen::MITER_JOIN),
		Pen(Color::RED, 1.0, Pen::DOT_LINE, Pen::FLAT_CAP, Pen::BEVEL_JOIN),
		Pen(Color::RED, 1.0, Pen::DASH_DOT_LINE, Pen::FLAT_CAP, Pen::ROUND_JOIN),
		Pen(Color::RED, 1.0, Pen::DASH_DOT_DOT_LINE, Pen::FLAT_CAP, Pen::MITER_JOIN),
		
		Pen(Color::GREEN, 1.5, Pen::NO_LINE, Pen::SQUARE_CAP, Pen::ROUND_JOIN),
		Pen(Color::GREEN, 1.5, Pen::SOLID_LINE, Pen::SQUARE_CAP, Pen::MITER_JOIN),
		Pen(Color::GREEN, 1.5, Pen::DASH_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN),
		Pen(Color::GREEN, 1.5, Pen::DOT_LINE, Pen::SQUARE_CAP, Pen::ROUND_JOIN),
		Pen(Color::GREEN, 1.5, Pen::DASH_DOT_LINE, Pen::SQUARE_CAP, Pen::MITER_JOIN),
		Pen(Color::GREEN, 1.5, Pen::DASH_DOT_DOT_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN),
		
		Pen(Color::BLUE, 2.0, Pen::NO_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN),
		Pen(Color::BLUE, 2.0, Pen::SOLID_LINE, Pen::ROUND_CAP, Pen::BEVEL_JOIN),
		Pen(Color::BLUE, 2.0, Pen::DASH_LINE, Pen::ROUND_CAP, Pen::ROUND_JOIN),
		Pen(Color::BLUE, 2.0, Pen::DOT_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN),
		Pen(Color::BLUE, 2.0, Pen::DASH_DOT_LINE, Pen::ROUND_CAP, Pen::BEVEL_JOIN),
		Pen(Color::BLUE, 2.0, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP, Pen::ROUND_JOIN),
	
		Pen(Color::MAGENTA, 3.0, Pen::NO_LINE, Pen::FLAT_CAP, Pen::BEVEL_JOIN),
		Pen(Color::MAGENTA, 3.0, Pen::SOLID_LINE, Pen::FLAT_CAP, Pen::ROUND_JOIN),
		Pen(Color::MAGENTA, 3.0, Pen::DASH_LINE, Pen::FLAT_CAP, Pen::MITER_JOIN),
		Pen(Color::MAGENTA, 3.0, Pen::DOT_LINE, Pen::FLAT_CAP, Pen::BEVEL_JOIN),
		Pen(Color::MAGENTA, 3.0, Pen::DASH_DOT_LINE, Pen::FLAT_CAP, Pen::ROUND_JOIN),
		Pen(Color::MAGENTA, 3.0, Pen::DASH_DOT_DOT_LINE, Pen::FLAT_CAP, Pen::MITER_JOIN),
		
		Pen(Color::CYAN, 5.0, Pen::NO_LINE, Pen::SQUARE_CAP, Pen::ROUND_JOIN),
		Pen(Color::CYAN, 5.0, Pen::SOLID_LINE, Pen::SQUARE_CAP, Pen::MITER_JOIN),
		Pen(Color::CYAN, 5.0, Pen::DASH_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN),
		Pen(Color::CYAN, 5.0, Pen::DOT_LINE, Pen::SQUARE_CAP, Pen::ROUND_JOIN),
		Pen(Color::CYAN, 5.0, Pen::DASH_DOT_LINE, Pen::SQUARE_CAP, Pen::MITER_JOIN),
		Pen(Color::CYAN, 5.0, Pen::DASH_DOT_DOT_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN),
		
		Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen::NO_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN),
		Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen::SOLID_LINE, Pen::ROUND_CAP, Pen::BEVEL_JOIN),
		Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen::DASH_LINE, Pen::ROUND_CAP, Pen::ROUND_JOIN),
		Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen::DOT_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN),
		Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen::DASH_DOT_LINE, Pen::ROUND_CAP, Pen::BEVEL_JOIN),
		Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP, Pen::ROUND_JOIN)
	};

	Brush test_brushes[] = {
		Brush(Color::RED, Brush::SOLID_PATTERN),
		Brush(Color(1.0, 1.0, 1.0, 0.5), Brush::DENSE1_PATTERN),
		Brush(Color::BLUE, Brush::DENSE2_PATTERN),
		Brush(Color::YELLOW, Brush::DENSE3_PATTERN),
		Brush(Color::MAGENTA, Brush::DENSE4_PATTERN),
		Brush(Color::WHITE, Brush::DENSE5_PATTERN),
		Brush(Color::GREEN, Brush::DENSE6_PATTERN),
		Brush(Color::CYAN, Brush::DENSE7_PATTERN),
		Brush(Color::DARK_MAGENTA, Brush::H_PATTERN),
		Brush(Color::DARK_GREEN, Brush::V_PATTERN),
		Brush(Color::DARK_BLUE, Brush::CROSS_PATTERN),
		Brush(Color::DARK_YELLOW, Brush::LEFT_DIAG_PATTERN),
		Brush(Color::DARK_CYAN, Brush::RIGHT_DIAG_PATTERN),
		Brush(Color::DARK_RED, Brush::DIAG_CROSS_PATTERN),
		Brush(Color::BLACK, Brush::NO_PATTERN)
	};

	ep.setWidth(80.0);
	ep.setHeight(50.0);

	BOOST_CHECK(ep.getWidth() == 80.0);
	BOOST_CHECK(ep.getHeight() == 50.0);

	double y = 35.0;

	for (std::size_t i = 0; i < 7; i++, y += 70.0) {
		double x = 50.0;

		for (std::size_t j = 0; j < 6; j++, x += 100.0) {
			ep.setPen(test_pens[i * 6 + j]);
			ep.setBrush(test_brushes[(i * 6 + j) % 15]);
			ep.setPosition(Math::vec(x, y));
			ep.render(renderer);
	   
			Rectangle2D bbox;
			ep.getBounds(bbox, 0);

			renderer.setPen(Color::RED);
			renderer.setBrush(Brush());
			renderer.drawRectangle(bbox.getMin()(0), bbox.getMin()(1), bbox.getWidth(), bbox.getHeight());

			checkClone(ep);

			BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
			BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
		}
	}

	BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "EllipsePrimitive2DTest.png") == CAIRO_STATUS_SUCCESS);

//	BOOST_MESSAGE(cairo_status_to_string(cairo_surface_status(surf_ptr.get())));
//	BOOST_MESSAGE(cairo_status_to_string(cairo_status(ctxt_ptr.get())));

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO

}

