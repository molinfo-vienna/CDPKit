/* 
 * TextLabelPrimitive2DTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Vis/TextLabelPrimitive2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


namespace
{

#ifdef HAVE_CAIRO     

    void renderBBox(const CDPL::Vis::TextLabelPrimitive2D& tlp, CDPL::Vis::CairoRenderer2D& renderer)
    {
        using namespace CDPL;
        using namespace Vis;

        Rectangle2D bbox;
        tlp.getBounds(bbox, 0);

        renderer.setPen(Color::RED);
        renderer.setBrush(Brush());
        renderer.drawRectangle(bbox.getMin()(0), bbox.getMin()(1), bbox.getWidth(), bbox.getHeight());
    }

#endif // HAVE_CAIRO 

    void checkClone(const CDPL::Vis::TextLabelPrimitive2D& prim)
    {
        using namespace CDPL;
        using namespace Vis;

        GraphicsPrimitive2D::SharedPointer gp_clone_ptr = prim.clone();
        const TextLabelPrimitive2D* prim_clone_ptr = static_cast<const TextLabelPrimitive2D*>(gp_clone_ptr.get());

        BOOST_CHECK(prim_clone_ptr->getPosition() == prim.getPosition());
        BOOST_CHECK(prim_clone_ptr->getPen() == prim.getPen());
        BOOST_CHECK(prim_clone_ptr->getFont() == prim.getFont());
        BOOST_CHECK(prim_clone_ptr->getText() == prim.getText());
    }
}


BOOST_AUTO_TEST_CASE(TextLabelPrimitive2DTest)
{
    using namespace CDPL;
    using namespace Vis;

    TextLabelPrimitive2D tlp;

    BOOST_CHECK(tlp.getText() == "");
    BOOST_CHECK(tlp.getPosition()(0) == 0.0 && tlp.getPosition()(1) == 0.0);
    BOOST_CHECK(tlp.getPen() == Pen());
    BOOST_CHECK(tlp.getFont() == Font());

    checkClone(tlp);

    tlp.setPen(Color::GREEN);

    BOOST_CHECK(tlp.getText() == "");
    BOOST_CHECK(tlp.getPosition()(0) == 0.0 && tlp.getPosition()(1) == 0.0);
    BOOST_CHECK(tlp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tlp.getFont() == Font());

    checkClone(tlp);

    tlp.setText("Test Text");

    BOOST_CHECK(tlp.getText() == "Test Text");
    BOOST_CHECK(tlp.getPosition()(0) == 0.0 && tlp.getPosition()(1) == 0.0);
    BOOST_CHECK(tlp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tlp.getFont() == Font());

    checkClone(tlp);

    tlp.setFont(Font("Times", 13.3));

    BOOST_CHECK(tlp.getText() == "Test Text");
    BOOST_CHECK(tlp.getPosition()(0) == 0.0 && tlp.getPosition()(1) == 0.0);
    BOOST_CHECK(tlp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tlp.getFont() == Font("Times", 13.3));

    checkClone(tlp);

    Math::Vector2D pos;
    
    pos(0) = 3.3;
    pos(1) = -0.2;

    tlp.setPosition(pos);

    BOOST_CHECK(tlp.getText() == "Test Text");
    BOOST_CHECK(tlp.getPosition()(0) == 3.3 && tlp.getPosition()(1) == -0.2);
    BOOST_CHECK(tlp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tlp.getFont() == Font("Times", 13.3));

    checkClone(tlp);

    tlp.setPosition(10.2, -2.3);

    BOOST_CHECK(tlp.getText() == "Test Text");
    BOOST_CHECK(tlp.getPosition()(0) == 10.2 && tlp.getPosition()(1) == -2.3);
    BOOST_CHECK(tlp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tlp.getFont() == Font("Times", 13.3));

    checkClone(tlp);

//-----

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

    CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 680, 150));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoRenderer2D renderer(ctxt_ptr);

    tlp.setText("The Quick Brown Fox...");
    tlp.setPosition(10.0, 15.0);
    tlp.setPen(Color::GREEN);
    tlp.setFont(Font());

    tlp.render(renderer);

    renderBBox(tlp, renderer);

    checkClone(tlp);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    tlp.setPosition(20.0, 35.0);
    tlp.setPen(Pen(Color::RED, Pen::NO_LINE));
    tlp.setFont(Font("Times", 15.0));

    tlp.render(renderer);

    renderBBox(tlp, renderer);

    checkClone(tlp);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    Font f("Helvetica", 20.0);

    f.setItalic(true);

    tlp.setPosition(30.0, 60.0);
    tlp.setPen(Pen(Color::BLUE));
    tlp.setFont(f);

    tlp.render(renderer);

    renderBBox(tlp, renderer);

    checkClone(tlp);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    f.setItalic(false);
    f.setBold(true);
    f.setFamily("Courier");
    f.setSize(40.0);

    tlp.setPosition(40.0, 95.0);
    tlp.setPen(Color(1.0, 1.0, 0.0, 0.7));
    tlp.setFont(f);

    tlp.render(renderer);

    renderBBox(tlp, renderer);

    checkClone(tlp);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    f.setItalic(true);
    f.setFamily("Serif");
    f.setSize(60.0);

    tlp.setPosition(50.0, 130.0);
    tlp.setPen(Color(0.0, 1.0, 0.0, 0.8));
    tlp.setFont(f);

    tlp.render(renderer);

    renderBBox(tlp, renderer);

    checkClone(tlp);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "TextLabelPrimitive2DTest.png") == CAIRO_STATUS_SUCCESS);

///    BOOST_MESSAGE(cairo_status_to_string(cairo_surface_status(surf_ptr.get())));
//    BOOST_MESSAGE(cairo_status_to_string(cairo_status(ctxt_ptr.get())));

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO

}

