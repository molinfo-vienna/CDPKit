/* 
 * LinePrimitive2DTest.cpp 
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
#include "CDPL/Vis/LinePrimitive2D.hpp"
#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Pen.hpp"
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

    void checkClone(const CDPL::Vis::LinePrimitive2D& prim)
    {
        using namespace CDPL;
        using namespace Vis;

        GraphicsPrimitive2D::SharedPointer gp_clone_ptr = prim.clone();
        const LinePrimitive2D* prim_clone_ptr = static_cast<const LinePrimitive2D*>(gp_clone_ptr.get());

        BOOST_CHECK(prim_clone_ptr->getBegin() == prim.getBegin());
        BOOST_CHECK(prim_clone_ptr->getEnd() == prim.getEnd());
        BOOST_CHECK(prim_clone_ptr->getPen() == prim.getPen());
    }
}


BOOST_AUTO_TEST_CASE(LinePrimitive2DTest)
{
    using namespace CDPL;
    using namespace Vis;

    Math::Vector2D v1, v2;

    v1(0) = 0.3;
    v1(1) = 0.4;

    v2(0) = 10.3;
    v2(1) = 10.4;

    LinePrimitive2D lp1(v1, v2);

    BOOST_CHECK(lp1.getBegin() == v1);
    BOOST_CHECK(lp1.getEnd() == v2);

    checkClone(lp1);

    Line2D l(v2, v1);

    LinePrimitive2D lp2(l);

    BOOST_CHECK(lp2.getBegin() == v2);
    BOOST_CHECK(lp2.getEnd() == v1);

    checkClone(lp1);

//-----

    BOOST_CHECK(lp1.getPen() == Pen());

    lp1.setPen(Pen(Color::GREEN, Pen::DASH_LINE));

    BOOST_CHECK(lp1.getPen() == Pen(Color::GREEN, Pen::DASH_LINE));

    checkClone(lp1);

//-----

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

    CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 160, 1100));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoRenderer2D renderer(ctxt_ptr);

    Pen test_pens[] = {
        Pen(Color::BLACK, 0.0, Pen::NO_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.0, Pen::SOLID_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.0, Pen::DASH_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.0, Pen::DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.0, Pen::DASH_DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.0, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP),
        
        Pen(Color::BLACK, 0.5, Pen::NO_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.5, Pen::SOLID_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.5, Pen::DASH_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.5, Pen::DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.5, Pen::DASH_DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::BLACK, 0.5, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP),
        
        Pen(Color::RED, 1.0, Pen::NO_LINE, Pen::FLAT_CAP),
        Pen(Color::RED, 1.0, Pen::SOLID_LINE, Pen::FLAT_CAP),
        Pen(Color::RED, 1.0, Pen::DASH_LINE, Pen::FLAT_CAP),
        Pen(Color::RED, 1.0, Pen::DOT_LINE, Pen::FLAT_CAP),
        Pen(Color::RED, 1.0, Pen::DASH_DOT_LINE, Pen::FLAT_CAP),
        Pen(Color::RED, 1.0, Pen::DASH_DOT_DOT_LINE, Pen::FLAT_CAP),
        
        Pen(Color::GREEN, 1.5, Pen::NO_LINE, Pen::SQUARE_CAP),
        Pen(Color::GREEN, 1.5, Pen::SOLID_LINE, Pen::SQUARE_CAP),
        Pen(Color::GREEN, 1.5, Pen::DASH_LINE, Pen::SQUARE_CAP),
        Pen(Color::GREEN, 1.5, Pen::DOT_LINE, Pen::SQUARE_CAP),
        Pen(Color::GREEN, 1.5, Pen::DASH_DOT_LINE, Pen::SQUARE_CAP),
        Pen(Color::GREEN, 1.5, Pen::DASH_DOT_DOT_LINE, Pen::SQUARE_CAP),
        
        Pen(Color::BLUE, 2.0, Pen::NO_LINE, Pen::ROUND_CAP),
        Pen(Color::BLUE, 2.0, Pen::SOLID_LINE, Pen::ROUND_CAP),
        Pen(Color::BLUE, 2.0, Pen::DASH_LINE, Pen::ROUND_CAP),
        Pen(Color::BLUE, 2.0, Pen::DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::BLUE, 2.0, Pen::DASH_DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::BLUE, 2.0, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP),
    
        Pen(Color::MAGENTA, 3.0, Pen::NO_LINE, Pen::FLAT_CAP),
        Pen(Color::MAGENTA, 3.0, Pen::SOLID_LINE, Pen::FLAT_CAP),
        Pen(Color::MAGENTA, 3.0, Pen::DASH_LINE, Pen::FLAT_CAP),
        Pen(Color::MAGENTA, 3.0, Pen::DOT_LINE, Pen::FLAT_CAP),
        Pen(Color::MAGENTA, 3.0, Pen::DASH_DOT_LINE, Pen::FLAT_CAP),
        Pen(Color::MAGENTA, 3.0, Pen::DASH_DOT_DOT_LINE, Pen::FLAT_CAP),
        
        Pen(Color::CYAN, 5.0, Pen::NO_LINE, Pen::SQUARE_CAP),
        Pen(Color::CYAN, 5.0, Pen::SOLID_LINE, Pen::SQUARE_CAP),
        Pen(Color::CYAN, 5.0, Pen::DASH_LINE, Pen::SQUARE_CAP),
        Pen(Color::CYAN, 5.0, Pen::DOT_LINE, Pen::SQUARE_CAP),
        Pen(Color::CYAN, 5.0, Pen::DASH_DOT_LINE, Pen::SQUARE_CAP),
        Pen(Color::CYAN, 5.0, Pen::DASH_DOT_DOT_LINE, Pen::SQUARE_CAP),
        
        Pen(Color::YELLOW, 8.0, Pen::NO_LINE, Pen::ROUND_CAP),
        Pen(Color::YELLOW, 8.0, Pen::SOLID_LINE, Pen::ROUND_CAP),
        Pen(Color::YELLOW, 8.0, Pen::DASH_LINE, Pen::ROUND_CAP),
        Pen(Color::YELLOW, 8.0, Pen::DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::YELLOW, 8.0, Pen::DASH_DOT_LINE, Pen::ROUND_CAP),
        Pen(Color::YELLOW, 8.0, Pen::DASH_DOT_DOT_LINE, Pen::ROUND_CAP),

        Pen(Color::WHITE, 10.0, Pen::NO_LINE, Pen::FLAT_CAP),
        Pen(Color::WHITE, 10.0, Pen::SOLID_LINE, Pen::FLAT_CAP),
        Pen(Color::WHITE, 10.0, Pen::DASH_LINE, Pen::FLAT_CAP),
        Pen(Color::WHITE, 10.0, Pen::DOT_LINE, Pen::FLAT_CAP),
        Pen(Color::WHITE, 10.0, Pen::DASH_DOT_LINE, Pen::FLAT_CAP),
        Pen(Color::WHITE, 10.0, Pen::DASH_DOT_DOT_LINE, Pen::FLAT_CAP)
    };

    double y = 5.0;

    for (std::size_t i = 0; i < 6 * 9 ; i++, y += 20.0) {
        lp1.setPen(test_pens[i]);
        lp1.setPoints(10.0, y, 150.0, y + 10.0);

        lp1.render(renderer);

           Rectangle2D bbox;
        lp1.getBounds(bbox, 0);

        renderer.setPen(Color::RED);
        renderer.setBrush(Brush());
        renderer.drawRectangle(bbox.getMin()(0), bbox.getMin()(1), bbox.getWidth(), bbox.getHeight());

        checkClone(lp1);

        BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
        BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "LinePrimitive2DTest.png") == CAIRO_STATUS_SUCCESS);

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO

}

