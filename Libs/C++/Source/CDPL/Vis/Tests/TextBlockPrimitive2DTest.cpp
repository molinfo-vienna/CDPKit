/* 
 * TextBlockPrimitive2DTest.cpp 
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

#include <string>
#include <cstddef>

#include "CDPL/Config.hpp"
#include "CDPL/Vis/TextBlockPrimitive2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Base/Exceptions.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"
# include "CDPL/Vis/CairoFontMetrics.hpp"

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


namespace
{
    
    void checkClone(const CDPL::Vis::TextBlockPrimitive2D& prim)
    {
        using namespace CDPL;
        using namespace Vis;

        GraphicsPrimitive2D::SharedPointer gp_clone_ptr = prim.clone();
        const TextBlockPrimitive2D* prim_clone_ptr = static_cast<const TextBlockPrimitive2D*>(gp_clone_ptr.get());

        BOOST_CHECK(prim_clone_ptr->getPosition() == prim.getPosition());
        BOOST_CHECK(prim_clone_ptr->getPen() == prim.getPen());
        BOOST_CHECK(prim_clone_ptr->getFont() == prim.getFont());
        BOOST_CHECK(prim_clone_ptr->getText() == prim.getText());
        BOOST_CHECK(prim_clone_ptr->getAlignment() == prim.getAlignment());
        BOOST_CHECK(prim_clone_ptr->getLineSpacing() == prim.getLineSpacing());
    }

#ifdef HAVE_CAIRO     
# ifdef HAVE_CAIRO_PNG_SUPPORT
    
    void renderBBox(const CDPL::Vis::TextBlockPrimitive2D& tbp, CDPL::Vis::CairoRenderer2D& renderer,
                    CDPL::Vis::CairoFontMetrics& font_metrics)
    {
        using namespace CDPL;
        using namespace Vis;

        Rectangle2D bbox;
        
        tbp.getBounds(bbox, &font_metrics);

        renderer.setPen(Pen(Color::RED, 1.0, Pen::DASH_LINE));
        renderer.setBrush(Brush());
        renderer.drawRectangle(bbox.getMin()(0), bbox.getMin()(1), bbox.getWidth(), bbox.getHeight());
    }

    void renderPrimitive(CDPL::Vis::TextBlockPrimitive2D& tbp, std::size_t& img_id)
    {
        using namespace CDPL;
        using namespace Vis;

        CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1000, 300));

        BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

        CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

        BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

        CairoRenderer2D renderer(ctxt_ptr);
        CairoFontMetrics font_metrics(ctxt_ptr);

        tbp.layout(font_metrics);
        tbp.render(renderer);

        renderBBox(tbp, renderer, font_metrics);

        BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
        BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), ("TextBlockPrimitive2DTest_" + std::to_string(img_id++) + ".png").c_str()) == CAIRO_STATUS_SUCCESS);

        checkClone(tbp);
    }

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO 

    const std::string STYLED_TEXT =
        "   <b>Wa\rter</b>\tis an <i>inorganic</> compound with the chemical formula <i>H<sub><color b='1.0'>2</></>O</>. "
        "<i>It</>    is a <color r='1' a='0.5'>transparent,<br/>tasteless</>, odorless,<sup>[c]</sup> <s>and nearly colorless</s> chemical substance, "
        "and it is the main constituent of Earth's hydrosphere<br></br>   and the fluids of all <u>known</> <b><i>living</i></> organisms\n"
        " (in which it acts as a solvent<sup>[19]</>). It is vital for all known <u><s><b><o><i>forms</></></></></> of <color g='1'>life, <color b='1'>despite</> not</><br/>"
        "providing food energy or organic micronutrients. Its chemical formula, <b>H<sub>2</>O</>, indicates that each of its molecules contains (5 ws follow)     <br/>"
        " one <i><color r='0.7'>oxygen</></i> and two <color r='0.5' g='0.5' b='0.5'><i>hydrogen</></color> atoms, connected by covalent bonds. <br/>"
        "<b><i>T</i>he</b> hydrogen atoms are attached to the oxygen atom at an angle of 104.45°.<sup><u>[20]</></sup> <i>In liquid form, <b>H<sub><o>2</></sub><color r='1'>O</></> "
        "is also called<br/>\"Water\"</> at standard temperature and pressure.";
}


BOOST_AUTO_TEST_CASE(TextBlockPrimitive2DTest)
{
    using namespace CDPL;
    using namespace Vis;

    TextBlockPrimitive2D tbp;

    BOOST_CHECK(tbp.getText() == "");
    BOOST_CHECK(tbp.getPosition()(0) == 0.0 && tbp.getPosition()(1) == 0.0);
    BOOST_CHECK(tbp.getPen() == Pen());
    BOOST_CHECK(tbp.getFont() == Font());
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);

    checkClone(tbp);

    tbp.setPen(Color::GREEN);

    BOOST_CHECK(tbp.getText() == "");
    BOOST_CHECK(tbp.getPosition()(0) == 0.0 && tbp.getPosition()(1) == 0.0);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font());
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);
    BOOST_CHECK(!tbp.hasText());
    
    checkClone(tbp);

    tbp.setText("<i></i>\n\r<br/>");

    BOOST_CHECK(tbp.getText() == "<i></i>\n\r<br/>");
    BOOST_CHECK(tbp.getPosition()(0) == 0.0 && tbp.getPosition()(1) == 0.0);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font());
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);
    BOOST_CHECK(!tbp.hasText());
    
    checkClone(tbp);
    
    tbp.setText("Test Text");

    BOOST_CHECK(tbp.getText() == "Test Text");
    BOOST_CHECK(tbp.getPosition()(0) == 0.0 && tbp.getPosition()(1) == 0.0);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font());
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);
    BOOST_CHECK(tbp.hasText());
    
    checkClone(tbp);

    tbp.setFont(Font("Times", 13.3));

    BOOST_CHECK(tbp.getText() == "Test Text");
    BOOST_CHECK(tbp.getPosition()(0) == 0.0 && tbp.getPosition()(1) == 0.0);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font("Times", 13.3));
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);

    checkClone(tbp);

    Math::Vector2D pos;
    
    pos(0) = 3.3;
    pos(1) = -0.2;

    tbp.setPosition(pos);

    BOOST_CHECK(tbp.getText() == "Test Text");
    BOOST_CHECK(tbp.getPosition()(0) == 3.3 && tbp.getPosition()(1) == -0.2);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font("Times", 13.3));
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);

    checkClone(tbp);

    tbp.setPosition(10.2, -2.3);

    BOOST_CHECK(tbp.getText() == "Test Text");
    BOOST_CHECK(tbp.getPosition()(0) == 10.2 && tbp.getPosition()(1) == -2.3);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font("Times", 13.3));
    BOOST_CHECK(tbp.getAlignment() == Alignment::LEFT);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);

    checkClone(tbp);

    tbp.setAlignment(Alignment::H_CENTER);

    BOOST_CHECK(tbp.getText() == "Test Text");
    BOOST_CHECK(tbp.getPosition()(0) == 10.2 && tbp.getPosition()(1) == -2.3);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font("Times", 13.3));
    BOOST_CHECK(tbp.getAlignment() == Alignment::H_CENTER);
    BOOST_CHECK(tbp.getLineSpacing() == 1.0);

    checkClone(tbp);

    tbp.setLineSpacing(1.5);

    BOOST_CHECK(tbp.getText() == "Test Text");
    BOOST_CHECK(tbp.getPosition()(0) == 10.2 && tbp.getPosition()(1) == -2.3);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font("Times", 13.3));
    BOOST_CHECK(tbp.getAlignment() == Alignment::H_CENTER);
    BOOST_CHECK(tbp.getLineSpacing() == 1.5);

    checkClone(tbp);

    tbp.clearText();

    BOOST_CHECK(tbp.getText() == "");
    BOOST_CHECK(tbp.getPosition()(0) == 10.2 && tbp.getPosition()(1) == -2.3);
    BOOST_CHECK(tbp.getPen() == Pen(Color::GREEN));
    BOOST_CHECK(tbp.getFont() == Font("Times", 13.3));
    BOOST_CHECK(tbp.getAlignment() == Alignment::H_CENTER);
    BOOST_CHECK(tbp.getLineSpacing() == 1.5);

    checkClone(tbp);

//-----

    tbp.setText("Test Text");
        
    BOOST_CHECK_THROW(tbp.setText("<adsf>X</>"), Base::ValueError);
    BOOST_CHECK(tbp.getText() == "Test Text");

    BOOST_CHECK_THROW(tbp.setText("<color>X"), Base::ValueError);
    BOOST_CHECK(tbp.getText() == "Test Text");

    BOOST_CHECK_THROW(tbp.setText("<br>X</br>"), Base::ValueError);
    BOOST_CHECK(tbp.getText() == "Test Text");
   
    BOOST_CHECK_THROW(tbp.setText("<sup><sub>X</></>"), Base::ValueError);
    BOOST_CHECK(tbp.getText() == "Test Text");

    BOOST_CHECK_THROW(tbp.setText("<sub><sup>X</></>"), Base::ValueError);
    BOOST_CHECK(tbp.getText() == "Test Text");
 
//-----

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

    std::size_t img_id = 1;
    
    tbp.setPosition(10.0, 10.0);
    tbp.setPen(Color::BLACK);
    tbp.setFont(Font());
    tbp.setAlignment(Alignment::LEFT);
    tbp.setLineSpacing(1.25);
    tbp.setText("\n>  f=Font(), c=BLACK, ls=1.25, a=LEFT, p=(10.0, 10.0)\n\r\n" + STYLED_TEXT);

    renderPrimitive(tbp, img_id);

    tbp.setPosition(20.0, 35.0);
    tbp.setPen(Pen(Color::GRAY, 1.0, Pen::NO_LINE));
    tbp.setFont(Font("Times", 12.0));
    tbp.setLineSpacing(1.0);
    tbp.setAlignment(Alignment::RIGHT);
    tbp.setText("\n>  f=('Times', 12.0), p=(GRAY, NO_LINE), ls=1.0, a=RIGHT, p=(20.0, 35.0)<br/>\n" + STYLED_TEXT);

    renderPrimitive(tbp, img_id);

    tbp.setPosition(20.0, 35.0);
    tbp.setPen(Pen(Color::GRAY, 1.0, Pen::NO_LINE));
    tbp.setFont(Font("Times", 12.0, true));
    tbp.setLineSpacing(1.0);
    tbp.setAlignment(Alignment::RIGHT);
    tbp.setText("\n>  f=('Times', 12.0, true), p=(GRAY, NO_LINE), ls=1.0, a=RIGHT, p=(20.0, 35.0)<br/>\n" + STYLED_TEXT);
    
    renderPrimitive(tbp, img_id);

    tbp.setPosition(20.0, 20.0);
    tbp.setFont(Font("Courier", 10.0, false, true));
    tbp.setAlignment(Alignment::CENTER);
    tbp.setLineSpacing(0.8);
    tbp.setText("\n>  f=('Courier', 10.0, false, true), p=(GRAY, NO_LINE), ls=0.8, a=CENTER, p=(20.0, 20.0)\n<br/>" + STYLED_TEXT);
    
    renderPrimitive(tbp, img_id);
    
    renderPrimitive(static_cast<TextBlockPrimitive2D&>(*tbp.clone()), img_id);

//-----

    CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 800, 300));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoFontMetrics font_metrics(ctxt_ptr);
    Rectangle2D bounds;

    BOOST_CHECK(!bounds.isDefined());
    
    tbp.getBounds(bounds, &font_metrics);

    BOOST_CHECK(bounds.isDefined());

    tbp.getBounds(bounds, 0);

    BOOST_CHECK(!bounds.isDefined());
    
    tbp.setText("");

    BOOST_CHECK(tbp.getText() == "");

    tbp.getBounds(bounds, &font_metrics);

    BOOST_CHECK(!bounds.isDefined());

    tbp.getBounds(bounds, 0);

    BOOST_CHECK(!bounds.isDefined());

    tbp.setText("ABC");

    BOOST_CHECK(tbp.getText() == "ABC");

    tbp.getBounds(bounds, 0);

    BOOST_CHECK(!bounds.isDefined());

    tbp.getBounds(bounds, &font_metrics);

    BOOST_CHECK(bounds.isDefined());

    tbp.clearText();

    BOOST_CHECK(tbp.getText() == "");

    tbp.getBounds(bounds, &font_metrics);

    BOOST_CHECK(!bounds.isDefined());

    tbp.getBounds(bounds, 0);

    BOOST_CHECK(!bounds.isDefined());
    
# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO
}
