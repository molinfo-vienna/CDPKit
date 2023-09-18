/* 
 * QtObjectFactory.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <QFont>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QString>

#include "CDPL/Vis/QtObjectFactory.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"


using namespace CDPL;


QFont Vis::QtObjectFactory::createQFont(const Font& font)
{
    QFont qt_font(QString::fromStdString(font.getFamily()));

    qt_font.setPointSizeF(font.getSize() <= 0.1 ? 0.1 : font.getSize());
    qt_font.setBold(font.isBold());
    qt_font.setItalic(font.isItalic());
    qt_font.setUnderline(font.isUnderlined());
    qt_font.setOverline(font.isOverlined());
    qt_font.setStrikeOut(font.isStrikedOut());
    qt_font.setFixedPitch(font.hasFixedPitch());

    return qt_font;
}

QColor Vis::QtObjectFactory::createQColor(const Color& color)
{
    QColor qt_color;

    qt_color.setRedF(color.getRed());
    qt_color.setGreenF(color.getGreen());
    qt_color.setBlueF(color.getBlue());
    qt_color.setAlphaF(color.getAlpha());

    return qt_color;
}

QPen Vis::QtObjectFactory::createQPen(const Pen& pen)
{
    Qt::PenStyle pen_style;

    switch (pen.getLineStyle()) {

        case Pen::DASH_LINE:
            pen_style = Qt::DashLine;
            break;

        case Pen::DOT_LINE:
            pen_style = Qt::DotLine;
            break;

        case Pen::DASH_DOT_LINE:
            pen_style = Qt::DashDotLine;
            break;

        case Pen::DASH_DOT_DOT_LINE:
            pen_style = Qt::DashDotDotLine;
            break;

        case Pen::NO_LINE:
            pen_style = Qt::NoPen;
            break;

        default:
            pen_style = Qt::SolidLine;
            break;
    }

    Qt::PenCapStyle cap_style;

    switch (pen.getCapStyle()) {

        case Pen::FLAT_CAP:
            cap_style = Qt::FlatCap;
            break;

        case Pen::SQUARE_CAP:
            cap_style = Qt::SquareCap;
            break;

        default:
            cap_style = Qt::RoundCap;
            break;
    }
    
    Qt::PenJoinStyle join_style;

    switch (pen.getJoinStyle()) {

        case Pen::MITER_JOIN:
            join_style = Qt::MiterJoin;
            break;

        case Pen::BEVEL_JOIN:
            join_style = Qt::BevelJoin;
            break;

        default:
            join_style = Qt::RoundJoin;
            break;
    }

    double width = pen.getWidth();

    QPen qt_pen(createQColor(pen.getColor()));

    qt_pen.setWidthF(width);
    qt_pen.setStyle(pen_style);
    qt_pen.setCapStyle(cap_style);
    qt_pen.setJoinStyle(join_style);

    return qt_pen;
}

QBrush Vis::QtObjectFactory::createQBrush(const Brush& brush)
{
    Qt::BrushStyle style;

    switch (brush.getStyle()) {

        case Brush::SOLID_PATTERN: 
            style = Qt::SolidPattern;
            break;

        case Brush::DENSE1_PATTERN:     
            style = Qt::Dense1Pattern;
            break;

        case Brush::DENSE2_PATTERN: 
            style = Qt::Dense2Pattern;
            break;

        case Brush::DENSE3_PATTERN: 
            style = Qt::Dense3Pattern;
            break;

        case Brush::DENSE4_PATTERN: 
            style = Qt::Dense4Pattern;
            break;

        case Brush::DENSE5_PATTERN: 
            style = Qt::Dense5Pattern;
            break;

        case Brush::DENSE6_PATTERN: 
            style = Qt::Dense6Pattern;
            break;

        case Brush::DENSE7_PATTERN: 
            style = Qt::Dense7Pattern;
            break;

        case Brush::H_PATTERN: 
            style = Qt::HorPattern;
            break;

        case Brush::V_PATTERN: 
            style = Qt::VerPattern;
            break;

        case Brush::CROSS_PATTERN: 
            style = Qt::CrossPattern;
            break;

        case Brush::LEFT_DIAG_PATTERN: 
            style = Qt::BDiagPattern;
            break;

        case Brush::RIGHT_DIAG_PATTERN: 
            style = Qt::FDiagPattern;
            break;

        case Brush::DIAG_CROSS_PATTERN:
            style = Qt::DiagCrossPattern;
            break;

        default:
            style = Qt::NoBrush;
            break;
    }

    return QBrush(createQColor(brush.getColor()), style);
}
