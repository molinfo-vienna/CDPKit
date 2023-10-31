/* 
 * QtRenderer2DTest.cpp 
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


#include <QPainter>
#include <QImage>
#include <QApplication>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/QtRenderer2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/PointArray2D.hpp"
#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Math/AffineTransform.hpp"


BOOST_AUTO_TEST_CASE(QtRenderer2DTest)
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

    int argc = 1;
    char arg[] = "QtRenderer2DTest";
    char* argv[] = { arg };

    QApplication app(argc, argv);

    QImage image1(600, 500, QImage::Format_ARGB32);
    QPainter view1(&image1);

    view1.fillRect(0, 0, 600, 500, Qt::gray);

    QtRenderer2D renderer1(view1);

    points.resize(5);

    double y = 35.0;

    for (std::size_t i = 0; i < 7; i++, y += 70.0) {
        double x = 60.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            renderer1.setPen(test_pens[i * 6 + j]);
            renderer1.setBrush(test_brushes[(i * 6 + j) % 15]);

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

            renderer1.drawPolygon(points);
        }
    }

    view1.end();

    BOOST_CHECK(image1.save("QtRenderer2DTest_1.png", "PNG"));

//-----

    QImage image2(310, 1300, QImage::Format_ARGB32);
    QPainter view2(&image2);

    view2.fillRect(0, 0, 310, 1300, Qt::gray);

    QtRenderer2D renderer2(view2);

    points.resize(8);

    y = 140.0;

    for (std::size_t i = 0; i < 7; y += 170.0, i++) {
        for (std::size_t j = 0; j < 6; j++) {
            renderer2.setPen(test_pens[i * 6 + j]);

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

            renderer2.drawLineSegments(points);
        }
    }

    view2.end();

    BOOST_CHECK(image2.save("QtRenderer2DTest_2.png", "PNG"));

//-----

    QImage image3(310, 1300, QImage::Format_ARGB32);
    QPainter view3(&image3);

    view3.fillRect(0, 0, 310, 1300, Qt::gray);

    QtRenderer2D renderer3(view3);

    points.resize(5);

    y = 140.0;

    for (std::size_t i = 0; i < 7; y += 170.0, i++) {
        for (std::size_t j = 0; j < 6; j++) {
            renderer3.setPen(test_pens[i * 6 + j]);

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

            renderer3.drawPolyline(points);
        }
    }

    view3.end();

    BOOST_CHECK(image3.save("QtRenderer2DTest_3.png", "PNG"));

//-----

    QImage image4(120, 150, QImage::Format_ARGB32);
    QPainter view4(&image4);

    view4.fillRect(0, 0, 120, 150, Qt::gray);

    QtRenderer2D renderer4(view4);

    y = 5.0;

    for (std::size_t i = 0; i < 6 * 7; y += 20.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, i++, x += 20.0) {
            renderer4.setPen(test_pens[i]);

            renderer4.drawPoint(x, y);
        }
    }

    view4.end();

    BOOST_CHECK(image4.save("QtRenderer2DTest_4.png", "PNG"));

//-----

    QImage image5(160, 900, QImage::Format_ARGB32);
    QPainter view5(&image5);

    view5.fillRect(0, 0, 160, 900, Qt::gray);

    QtRenderer2D renderer5(view5);

    y = 5.0;

    for (std::size_t i = 0; i < 6 * 7 ; i++, y += 20.0) {
        renderer5.setPen(test_pens[i]);

        renderer5.drawLine(10.0, y, 150.0, y);
    }

    view5.end();

    BOOST_CHECK(image5.save("QtRenderer2DTest_5.png", "PNG"));

//-----

    QImage image6(680, 150, QImage::Format_ARGB32);
    QPainter view6(&image6);

    view6.fillRect(0, 0, 780, 150, Qt::gray);

    QtRenderer2D renderer6(view6);

    renderer6.setPen(Color::GREEN);
    renderer6.setFont(Font());

    renderer6.drawText(10.0, 15.0, "The Quick Brown Fox...");
    
    renderer6.setPen(Pen(Color::RED, Pen::NO_LINE));
    renderer6.setFont(Font("Times", 15.0));

    renderer6.drawText(20.0, 35.0, "The Quick Brown Fox...");

    Font f("Helvetica", 20.0);

    f.setItalic(true);

    renderer6.setPen(Pen(Color::BLUE));
    renderer6.setFont(f);

    renderer6.drawText(30.0, 60.0, "The Quick Brown Fox...");

    f.setItalic(false);
    f.setBold(true);
    f.setFamily("Courier");
    f.setSize(40.0);

    renderer6.setPen(Color(1.0, 1.0, 0.0, 0.7));
    renderer6.setFont(f);

    renderer6.drawText(40.0, 90.0, "The Quick Brown Fox...");

    f.setItalic(true);
    f.setFamily("Serif");
    f.setSize(60.0);

    renderer6.setPen(Color(0.0, 1.0, 0.0, 0.8));
    renderer6.setFont(f);

    renderer6.drawText(50.0, 130.0, "The Quick Brown Fox...");

    view6.end();

    BOOST_CHECK(image6.save("QtRenderer2DTest_6.png", "PNG"));

//-----

    QImage image7(200, 200, QImage::Format_ARGB32);
    QPainter view7(&image7);

    view7.fillRect(0, 0, 200, 200, Qt::gray);

    QtRenderer2D renderer7(view7);

    renderer7.setPen(Pen(Color::RED, 2.0));
    renderer7.setBrush(Brush(Color::BLUE, Brush::CROSS_PATTERN));

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

    renderer7.transform(Math::TranslationMatrix<double>(3, 100.0));
    renderer7.transform(Math::TranslationMatrix<double>(3, 0.0, 100.0));

    renderer7.saveState();

    renderer7.transform(Math::TranslationMatrix<double>(3, -100.0));
    renderer7.transform(Math::TranslationMatrix<double>(3, 0.0, -100.0));

    renderer7.transform(Math::TranslationMatrix<double>(3, 70.0));
    renderer7.transform(Math::TranslationMatrix<double>(3, 0.0, 50.0));

    renderer7.transform(Math::ScalingMatrix<double>(3, 1.5));
    renderer7.transform(Math::ScalingMatrix<double>(3, 1.0, 0.8));

    renderer7.setPen(Pen(Color::GREEN, 5.0));
    renderer7.setBrush(Brush(Color::YELLOW, Brush::DENSE3_PATTERN));

    renderer7.drawPolygon(points);

    renderer7.restoreState();

    renderer7.drawPolygon(points);

    view7.end();

    BOOST_CHECK(image7.save("QtRenderer2DTest_7.png", "PNG"));

//-----

    QImage image8(600, 480, QImage::Format_ARGB32);
    QPainter view8(&image8);

    view8.fillRect(0, 0, 600, 480, Qt::gray);

    QtRenderer2D renderer8(view8);

    y = 15.0;

    for (std::size_t i = 0; i < 7; i++, y += 65.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            renderer8.setPen(test_pens[i * 6 + j]);
            renderer8.setBrush(test_brushes[(i * 6 + j) % 15]);

            renderer8.drawRectangle(x, y, 70.0, 45.0);
        }
    }

    view8.end();

    BOOST_CHECK(image8.save("QtRenderer2DTest_8.png", "PNG"));

//-----

    QImage image9(600, 480, QImage::Format_ARGB32);
    QPainter view9(&image9);

    view9.fillRect(0, 0, 600, 480, Qt::gray);

    QtRenderer2D renderer9(view9);
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
            renderer9.setPen(test_pens[i * 6 + j]);
            renderer9.setBrush(test_brushes[(i * 6 + j) % 15]);

            renderer9.saveState();
            renderer9.setTransform({ { 1.0, 0.0, x }, { 0.0, 1.0, y }, { 0.0, 0.0, 1.0 } });
            renderer9.drawPath(path);
            renderer9.restoreState();

        }
    }

    view9.end();
        
    BOOST_CHECK(image9.save("QtRenderer2DTest_9.png", "PNG"));

//-----

    QImage image10(600, 480, QImage::Format_ARGB32);
    QPainter view10(&image10);

    view10.fillRect(0, 0, 600, 480, Qt::gray);

    QtRenderer2D renderer10(view10);
    Path2D clp_path;

    clp_path.moveTo(450, 240);
    clp_path.arcTo(300, 240, 150, 90, 0, 360);
    clp_path.closePath();

    renderer10.setPen(Color::BLACK);
    renderer10.drawPath(clp_path);
    
    y = 45.0;

    for (std::size_t i = 0; i < 7; i++, y += 65.0) {
        double x = 10.0;

        for (std::size_t j = 0; j < 6; j++, x += 100.0) {
            if ((i * 7 + j) % 2 == 0)
                renderer10.setClipPath(clp_path);
            else
                renderer10.clearClipPath();
            
            renderer10.setPen(test_pens[i * 6 + j]);
            renderer10.setBrush(test_brushes[(i * 6 + j) % 15]);

            renderer10.saveState();
            renderer10.setTransform({ { 1.0, 0.0, x }, { 0.0, 1.0, y }, { 0.0, 0.0, 1.0 } });
            renderer10.drawPath(path);
            renderer10.restoreState();
        }
    }

    view10.end();
        
    BOOST_CHECK(image10.save("QtRenderer2DTest_10.png", "PNG"));
}
