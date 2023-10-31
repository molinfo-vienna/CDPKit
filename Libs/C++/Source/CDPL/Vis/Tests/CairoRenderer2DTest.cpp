/* 
 * CairoRenderer2DTest.cpp 
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

#include <cairo.h>

#include "CDPL/Vis/CairoPointer.hpp"
#include "CDPL/Vis/CairoRenderer2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/PointArray2D.hpp"
#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Math/AffineTransform.hpp"


BOOST_AUTO_TEST_CASE(CairoRenderer2DTest)
{
    using namespace CDPL;
    using namespace Vis;

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

    PointArray2D points;

//-----

    CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 500));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    CairoRenderer2D renderer(ctxt_ptr);

    points.resize(5);

    double y = 35.0;

    for (std::size_t i = 0; i < 7; i++, y += 70.0) {
        double x = 60.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            renderer.setPen(test_pens[i * 6 + j]);
            renderer.setBrush(test_brushes[(i * 6 + j) % 15]);

            points[0](0) = -1.0 * 30.0;
            points[0](1) = 1.0 * 30.0;

            points[1](0) = 1.0 * 30.0;
            points[1](1) = 1.0 * 30.0;

            points[2](0) = 0.5 * 30.0;
            points[2](1) = -1.0 * 30.0;
            
            points[3](0) = -1.5 * 30.0;
            points[3](1) = -0.5 * 30.0;

            points[4](0) = -1.8 * 30.0;
            points[4](1) = 0.5 * 30.0;

            points.translate(Math::vec(x, y));

            renderer.drawPolygon(points);
       
            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_1.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 310, 1300));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    points.resize(8);

    y = 140.0;

    for (std::size_t i = 0; i < 7; y += 170.0, i++) {
        for (std::size_t j = 0; j < 6; j++) {
            renderer.setPen(test_pens[i * 6 + j]);

            points[0](0) = -0.9 * 20.0 * j;
            points[0](1) = 1.0 * 20.0 * j;

            points[1](0) = 0.9 * 20.0 * j;
            points[1](1) = 1.0 * 20.0 * j;

            points[2](0) = 1.0 * 20.0 * j;
            points[2](1) = 0.9 * 20.0 * j;
            
            points[3](0) = 1.0 * 20.0 * j;
            points[3](1) = -0.9 * 20.0 * j;

            points[4](0) = 0.9 * 20.0 * j;
            points[4](1) = -1.0 * 20.0 * j;
            
            points[5](0) = -0.9 * 20.0 * j;
            points[5](1) = -1.0 * 20.0 * j;

            points[6](0) = -1.0 * 20.0 * j;
            points[6](1) = -0.9 * 20.0 * j;
            
            points[7](0) = -1.0 * 20.0 * j;
            points[7](1) = 0.9 * 20.0 * j;

            points.translate(Math::vec(160.0, y));

            renderer.drawLineSegments(points);
       
            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_2.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 310, 1300));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    points.resize(5);

    y = 140.0;

    for (std::size_t i = 0; i < 7; y += 170.0, i++) {
        for (std::size_t j = 0; j < 6; j++) {
            renderer.setPen(test_pens[i * 6 + j]);

            points[0](0) = -1.0 * 20.0 * j;
            points[0](1) = 1.0 * 20.0 * j;

            points[1](0) = 1.0 * 20.0 * j;
            points[1](1) = 1.0 * 20.0 * j;

            points[2](0) = 0.5 * 20.0 * j;
            points[2](1) = -1.0 * 20.0 * j;
            
            points[3](0) = -1.5 * 20.0 * j;
            points[3](1) = -0.5 * 20.0 * j;

            points[4](0) = -1.8 * 20.0 * j;
            points[4](1) = 0.5 * 20.0 * j;

            points.translate(Math::vec(195.0, y));

            renderer.drawPolyline(points);
       
            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_3.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 120, 150));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    y = 5.0;

    for (std::size_t i = 0; i < 6 * 7; y += 20.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, i++, x += 20.0) {
            renderer.setPen(test_pens[i]);

            renderer.drawPoint(x, y);
       
            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_4.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 160, 900));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    y = 5.0;

    for (std::size_t i = 0; i < 6 * 7 ; i++, y += 20.0) {
        renderer.setPen(test_pens[i]);

        renderer.drawLine(10.0, y, 150.0, y);
       
        BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
        BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_5.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 680, 150));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    renderer.setPen(Color::GREEN);
    renderer.setFont(Font());

    renderer.drawText(10.0, 15.0, "The Quick Brown Fox...");

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer.setPen(Pen(Color::RED, Pen::NO_LINE));
    renderer.setFont(Font("Times", 15.0));

    renderer.drawText(20.0, 35.0, "The Quick Brown Fox...");

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    Font f("Helvetica", 20.0);

    f.setItalic(true);

    renderer.setPen(Pen(Color::BLUE));
    renderer.setFont(f);

    renderer.drawText(30.0, 60.0, "The Quick Brown Fox...");

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    f.setItalic(false);
    f.setBold(true);
    f.setFamily("Courier");
    f.setSize(40.0);

    renderer.setPen(Color(1.0, 1.0, 0.0, 0.7));
    renderer.setFont(f);

    renderer.drawText(40.0, 95.0, "The Quick Brown Fox...");

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    f.setItalic(true);
    f.setFamily("Serif");
    f.setSize(60.0);

    renderer.setPen(Color(0.0, 1.0, 0.0, 0.8));
    renderer.setFont(f);

    renderer.drawText(50.0, 130.0, "The Quick Brown Fox...");

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_6.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 200, 200));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    renderer.setPen(Pen(Color::RED, 2.0));
    renderer.setBrush(Brush(Color::BLUE, Brush::CROSS_PATTERN));

    points[0](0) = -20.0;
    points[0](1) = 20.0;

    points[1](0) = 20.0;
    points[1](1) = 20.0;

    points[2](0) = 10.0;
    points[2](1) = -20.0;

    points[3](0) = -30.0;
    points[3](1) = -10.0;

    points[4](0) = -36.0;
    points[4](1) = 10.0;

    renderer.transform(Math::TranslationMatrix<double>(3, 100.0));
    renderer.transform(Math::TranslationMatrix<double>(3, 0.0, 100.0));

    renderer.saveState();

    renderer.transform(Math::TranslationMatrix<double>(3, -100.0));
    renderer.transform(Math::TranslationMatrix<double>(3, 0.0, -100.0));

    renderer.transform(Math::TranslationMatrix<double>(3, 70.0));
    renderer.transform(Math::TranslationMatrix<double>(3, 0.0, 50.0));

    renderer.transform(Math::ScalingMatrix<double>(3, 1.5));
    renderer.transform(Math::ScalingMatrix<double>(3, 1.0, 0.8));

    renderer.setPen(Pen(Color::GREEN, 5.0));
    renderer.setBrush(Brush(Color::YELLOW, Brush::DENSE3_PATTERN));

    renderer.drawPolygon(points);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer.restoreState();

    renderer.drawPolygon(points);

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_7.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 480));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    y = 15.0;

    for (std::size_t i = 0; i < 7; i++, y += 65.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            renderer.setPen(test_pens[i * 6 + j]);
            renderer.setBrush(test_brushes[(i * 6 + j) % 15]);

            renderer.drawRectangle(x, y, 70.0, 45.0);
       
            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_8.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 480));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    Path2D path;

    path.moveTo(0, -20);
    path.lineTo(50, -20);
    path.arcTo(50, 0, 20, 20, -90, 180);
    path.lineTo(0, 20);
    path.arcTo(0, 0, 15, 20, 90, -180);
    path.closePath();
    
    y = 45.0;

    for (std::size_t i = 0; i < 7; i++, y += 65.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            renderer.setPen(test_pens[i * 6 + j]);
            renderer.setBrush(test_brushes[(i * 6 + j) % 15]);

            renderer.saveState();
            renderer.setTransform({ { 1.0, 0.0, x }, { 0.0, 1.0, y }, { 0.0, 0.0, 1.0 } });
            renderer.drawPath(path);
            renderer.restoreState();

            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }
    
    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_9.png") == CAIRO_STATUS_SUCCESS);

//-----

    surf_ptr = CairoPointer<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 480));

    BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

    ctxt_ptr = CairoPointer<cairo_t>(cairo_create(surf_ptr.get()));

    BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

    renderer = CairoRenderer2D(ctxt_ptr);

    Path2D clp_path;

    clp_path.moveTo(450, 240);
    clp_path.arcTo(300, 240, 150, 90, 0, 360);
    clp_path.closePath();

    renderer.setPen(Color::BLACK);
    renderer.drawPath(clp_path);
    
    y = 45.0;

    for (std::size_t i = 0; i < 7; i++, y += 65.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            if ((i * 7 + j) % 2 == 0)
                renderer.setClipPath(clp_path);
            else
                renderer.clearClipPath();
            
            renderer.setPen(test_pens[i * 6 + j]);
            renderer.setBrush(test_brushes[(i * 6 + j) % 15]);

            renderer.saveState();
            renderer.setTransform({ { 1.0, 0.0, x }, { 0.0, 1.0, y }, { 0.0, 0.0, 1.0 } });
            renderer.drawPath(path);
            renderer.restoreState();

            BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
            BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);
        }
    }

    BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), "CairoRenderer2DTest_10.png") == CAIRO_STATUS_SUCCESS);
}
