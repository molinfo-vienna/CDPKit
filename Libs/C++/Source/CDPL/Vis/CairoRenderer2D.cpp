/* 
 * CairoRenderer2D.cpp 
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


#include "StaticInit.hpp"

#include <cmath>

#include <cairo.h>

#include "CDPL/Vis/CairoRenderer2D.hpp"
#include "CDPL/Vis/PointArray2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/CairoPointer.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    unsigned char dense1PatternData[] = {
          0, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255
    };

    unsigned char dense2PatternData[] = {
          0, 255, 255, 255,
        255, 255, 255, 255,
        255, 255,   0, 255,
        255, 255, 255, 255
    };

    unsigned char dense3PatternData[] = {
        255,   0, 255, 255,
          0, 255,   0, 255,
        255, 255, 255,   0,
          0, 255,   0, 255
    };

    unsigned char dense4PatternData[] = {
        255,   0, 255,   0,
          0, 255,   0, 255,
        255,   0, 255,   0,
          0, 255,   0, 255
    };

    unsigned char dense5PatternData[] = {
          0, 255,   0,   0,
        255,   0, 255,   0,
          0,   0,   0, 255,
        255,   0, 255,   0
    };

    unsigned char dense6PatternData[] = {
        255,   0,   0,   0,
          0,   0,   0,   0,
          0,   0, 255,   0,
          0,   0,   0,   0
    };

    unsigned char dense7PatternData[] = {
        255,   0,   0,   0,
          0,   0,   0,   0,
          0,   0,   0,   0,
          0,   0,   0,   0
    };

    unsigned char horPatternData[] = {
          0,   0,   0,   0,
        255, 255, 255, 255,
          0,   0,   0,   0,
          0,   0,   0,   0
    };

    unsigned char verPatternData[] = {
          0, 255,   0,   0,
          0, 255,   0,   0,
          0, 255,   0,   0,
          0, 255,   0,   0
    };
   
    unsigned char crossPatternData[] = {
          0, 255,   0,   0,
        255, 255, 255, 255,
          0, 255,   0,   0,
          0, 255,   0,   0
    };

    unsigned char leftDiagPatternData[] = {
          0,   0,   0, 255,
          0,   0, 255,   0,
          0, 255,   0,   0,
        255,   0,   0,   0
    };
    
    unsigned char rightDiagPatternData[] = {
        255,   0,   0,   0,
          0, 255,   0,   0,
          0,   0, 255,   0,
          0,   0,   0, 255
    };

    unsigned char diagCrossPatternData[] = {
          0,   0,   0, 255,   0,   0,   0,   0,
          0,   0, 255,   0, 255,   0,   0,   0,
          0, 255,   0,   0,   0, 255,   0,   0,
        255,   0,   0,   0,   0,   0, 255,   0,
          0,   0,   0,   0,   0,   0,   0, 255,
        255,   0,   0,   0,   0,   0, 255,   0,
          0, 255,   0,   0,   0, 255,   0,   0,
          0,   0, 255,   0, 255,   0,   0,   0
    };

    cairo_surface_t* dense1Pattern    = cairo_image_surface_create_for_data(dense1PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* dense2Pattern    = cairo_image_surface_create_for_data(dense2PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* dense3Pattern    = cairo_image_surface_create_for_data(dense3PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* dense4Pattern    = cairo_image_surface_create_for_data(dense4PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* dense5Pattern    = cairo_image_surface_create_for_data(dense5PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* dense6Pattern    = cairo_image_surface_create_for_data(dense6PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* dense7Pattern    = cairo_image_surface_create_for_data(dense7PatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* horPattern       = cairo_image_surface_create_for_data(horPatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* verPattern       = cairo_image_surface_create_for_data(verPatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* crossPattern     = cairo_image_surface_create_for_data(crossPatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* leftDiagPattern  = cairo_image_surface_create_for_data(leftDiagPatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* rightDiagPattern = cairo_image_surface_create_for_data(rightDiagPatternData, CAIRO_FORMAT_A8, 4, 4, 4); 
    cairo_surface_t* diagCrossPattern = cairo_image_surface_create_for_data(diagCrossPatternData, CAIRO_FORMAT_A8, 8, 8, 8); 
}


using namespace CDPL;


Vis::CairoRenderer2D::CairoRenderer2D(const CairoPointer<cairo_t>& ctxt_ptr): cairoContext(ctxt_ptr) 
{
    if (!ctxt_ptr)
        throw Base::NullPointerException("CairoRenderer2D: NULL cairo context pointer");

    penStack.push_back(Pen());
    brushStack.push_back(Brush());
    fontStack.push_back(Font());
}

Vis::CairoRenderer2D::~CairoRenderer2D() {}

void Vis::CairoRenderer2D::saveState()
{
    cairo_save(cairoContext.get());

    penStack.reserve(penStack.size() + 1);
    brushStack.reserve(brushStack.size() + 1);
    fontStack.reserve(fontStack.size() + 1);

    penStack.push_back(penStack.back());
    brushStack.push_back(brushStack.back());
    fontStack.push_back(fontStack.back());
}

void Vis::CairoRenderer2D::restoreState()
{
    if (penStack.size() > 1) {
        cairo_restore(cairoContext.get());

        penStack.pop_back();
        brushStack.pop_back();
        fontStack.pop_back();
    }
}

void Vis::CairoRenderer2D::setTransform(const Math::Matrix3D& xform)
{
    cairo_matrix_t cairo_xform;

    cairo_matrix_init(&cairo_xform, 
                      xform(0, 0), xform(1, 0),
                      xform(0, 1), xform(1, 1),
                      xform(0, 2), xform(1, 2));
                                 
    cairo_set_matrix(cairoContext.get(), &cairo_xform);
}

void Vis::CairoRenderer2D::transform(const Math::Matrix3D& xform)
{
    cairo_matrix_t cairo_xform;

    cairo_matrix_init(&cairo_xform, 
                      xform(0, 0), xform(1, 0),
                      xform(0, 1), xform(1, 1),
                      xform(0, 2), xform(1, 2));

    cairo_transform(cairoContext.get(), &cairo_xform);
}

void Vis::CairoRenderer2D::setPen(const Pen& pen)
{
    penStack.back() = pen;
}

void Vis::CairoRenderer2D::setBrush(const Brush& brush)
{
    brushStack.back() = brush;
}

void Vis::CairoRenderer2D::setFont(const Font& font)
{
    fontStack.back() = font;
}

void Vis::CairoRenderer2D::drawRectangle(double x, double y, double width, double height)
{
    cairo_new_path(cairoContext.get());

    cairo_rectangle(cairoContext.get(), x, y, width, height);

    fillPath();
    strokePath();
}

void Vis::CairoRenderer2D::drawPolygon(const Math::Vector2DArray& points)
{
    cairo_new_path(cairoContext.get());

    Math::Vector2DArray::ConstElementIterator points_end = points.getElementsEnd();

    bool move = true;

    for (Math::Vector2DArray::ConstElementIterator p_it = points.getElementsBegin(); p_it != points_end; ++p_it) {
        const Math::Vector2D& pt = *p_it;

        if (move)
            cairo_move_to(cairoContext.get(), pt(0), pt(1));
        else
            cairo_line_to(cairoContext.get(), pt(0), pt(1));

        move = false;
    }

    cairo_close_path(cairoContext.get());

    fillPath();
    strokePath();
}

void Vis::CairoRenderer2D::drawLine(double x1, double y1, double x2, double y2)
{
    cairo_new_path(cairoContext.get());

    cairo_move_to(cairoContext.get(), x1, y1);
    cairo_line_to(cairoContext.get(), x2, y2);

    strokePath();
}

void Vis::CairoRenderer2D::drawPolyline(const Math::Vector2DArray& points)
{
    cairo_new_path(cairoContext.get());

    Math::Vector2DArray::ConstElementIterator points_end = points.getElementsEnd();

    bool move = true;

    for (Math::Vector2DArray::ConstElementIterator p_it = points.getElementsBegin(); p_it != points_end; ++p_it) {
        const Math::Vector2D& pt = *p_it;

        if (move)
            cairo_move_to(cairoContext.get(), pt(0), pt(1));
        else
            cairo_line_to(cairoContext.get(), pt(0), pt(1));

        move = false;
    }

    strokePath();
}

void Vis::CairoRenderer2D::drawLineSegments(const Math::Vector2DArray& points)
{    
    cairo_new_path(cairoContext.get());

    Math::Vector2DArray::ConstElementIterator points_end = points.getElementsEnd();

    for (Math::Vector2DArray::ConstElementIterator p_it = points.getElementsBegin(); p_it != points_end; ++p_it) {
        const Math::Vector2D& pt1 = *p_it;

        if (++p_it == points_end)
            break;

        const Math::Vector2D& pt2 = *p_it;

        cairo_move_to(cairoContext.get(), pt1(0), pt1(1));
        cairo_line_to(cairoContext.get(), pt2(0), pt2(1));
    }

    strokePath();
}

void Vis::CairoRenderer2D::drawPoint(double x, double y)
{
    cairo_new_path(cairoContext.get());

    double radius = penStack.back().getWidth() * 0.5;

    const Color& color = penStack.back().getColor();

    cairo_set_source_rgba(cairoContext.get(), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

    cairo_arc(cairoContext.get(), x, y, radius, 0.0, 2.0 * M_PI);
    cairo_fill(cairoContext.get());
}

void Vis::CairoRenderer2D::drawText(double x, double y, const std::string& txt)
{
    cairo_select_font_face(cairoContext.get(), fontStack.back().getFamily().c_str(), 
                           fontStack.back().isItalic() ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                           fontStack.back().isBold() ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

    cairo_set_font_size(cairoContext.get(), fontStack.back().getSize());

    const Color& color = penStack.back().getColor();

    cairo_set_source_rgba(cairoContext.get(), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

    cairo_move_to(cairoContext.get(), x, y);

    cairo_show_text(cairoContext.get(), txt.c_str());
}

void Vis::CairoRenderer2D::drawEllipse(double x, double y, double width, double height)
{
    cairo_save(cairoContext.get());

    cairo_new_path(cairoContext.get());

    cairo_translate(cairoContext.get(), x, y);
    cairo_scale(cairoContext.get(), 1.0, height / width);
    cairo_arc(cairoContext.get(), 0.0, 0.0, width * 0.5, 0.0, 2 * M_PI);

    fillPath();
    strokePath();

    cairo_restore(cairoContext.get());
}

void Vis::CairoRenderer2D::fillPath() const
{
    std::size_t brush_style = brushStack.back().getStyle();

    if (brush_style == Brush::NO_PATTERN)
        return;

    const Color& color = brushStack.back().getColor();

    cairo_surface_t* pattern = 0;
    
    switch (brush_style) {

        case Brush::DENSE1_PATTERN:
            pattern = dense1Pattern;
            break;

        case Brush::DENSE2_PATTERN:
            pattern = dense2Pattern;
            break;

        case Brush::DENSE3_PATTERN:
            pattern = dense3Pattern;
            break;

        case Brush::DENSE4_PATTERN:
            pattern = dense4Pattern;
            break;

        case Brush::DENSE5_PATTERN:
            pattern = dense5Pattern;
            break;

        case Brush::DENSE6_PATTERN:
            pattern = dense6Pattern;
            break;

        case Brush::DENSE7_PATTERN:
            pattern = dense7Pattern;
            break;

        case Brush::H_PATTERN:
            pattern = horPattern;
            break;

        case Brush::V_PATTERN:
            pattern = verPattern;
            break;

        case Brush::CROSS_PATTERN:
            pattern = crossPattern;
            break;

        case Brush::LEFT_DIAG_PATTERN:
            pattern = leftDiagPattern;
            break;

        case Brush::RIGHT_DIAG_PATTERN:
            pattern = rightDiagPattern;
            break;

        case Brush::DIAG_CROSS_PATTERN:
            pattern = diagCrossPattern;
            break;

        default:
            cairo_set_source_rgba(cairoContext.get(), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
            cairo_fill_preserve(cairoContext.get());
            return;
    }

    int ptn_width = cairo_image_surface_get_width(pattern);
    int ptn_height = cairo_image_surface_get_height(pattern);

    CairoPointer<cairo_surface_t> src_surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, ptn_width, ptn_height));
    CairoPointer<cairo_t> src_ctxt_ptr(cairo_create(src_surf_ptr.get()));

    cairo_set_source_rgba(src_ctxt_ptr.get(), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
    cairo_mask_surface(src_ctxt_ptr.get(), pattern, 0.0, 0.0);

    CairoPointer<cairo_pattern_t> src_pattern_ptr(cairo_pattern_create_for_surface(src_surf_ptr.get()));

    cairo_pattern_set_extend(src_pattern_ptr.get(), CAIRO_EXTEND_REPEAT);

    cairo_set_source(cairoContext.get(), src_pattern_ptr.get());
    cairo_fill_preserve(cairoContext.get());
}

void Vis::CairoRenderer2D::strokePath() const
{
    double dashes[6];
    double line_width = penStack.back().getWidth();

    if (line_width == 0.0)
        cairo_set_dash(cairoContext.get(), 0, 0, 0);

    else
        switch (penStack.back().getLineStyle()) {

            case Pen::NO_LINE:
                return;
    
            case Pen::DASH_LINE:
                dashes[0] = 5.0 * line_width;

                cairo_set_dash(cairoContext.get(), dashes, 1, 0);
                break;

            case Pen::DOT_LINE:
                dashes[0] = line_width;
                dashes[1] = line_width * 1.5;

                cairo_set_dash(cairoContext.get(), dashes, 2, 0);
                break;

            case Pen::DASH_DOT_LINE:
                dashes[0] = line_width * 5.0;
                dashes[1] = line_width * 1.5;
                dashes[2] = line_width;
                dashes[3] = line_width * 1.5;

                cairo_set_dash(cairoContext.get(), dashes, 4, 0);
                break;

            case Pen::DASH_DOT_DOT_LINE:
                dashes[0] = line_width * 5.0;
                dashes[1] = line_width * 1.5;
                dashes[2] = line_width;
                dashes[3] = line_width * 1.5;
                dashes[4] = line_width;
                dashes[5] = line_width * 1.5;

                cairo_set_dash(cairoContext.get(), dashes, 6, 0);
                break;

            default:
                cairo_set_dash(cairoContext.get(), 0, 0, 0);
        }

    switch (penStack.back().getJoinStyle()) {
        
        case Pen::MITER_JOIN:
            cairo_set_line_join(cairoContext.get(), CAIRO_LINE_JOIN_MITER);
            break;

        case Pen::BEVEL_JOIN:
            cairo_set_line_join(cairoContext.get(), CAIRO_LINE_JOIN_BEVEL);
            break;

        default:
            cairo_set_line_join(cairoContext.get(), CAIRO_LINE_JOIN_ROUND);
    }

    switch (penStack.back().getCapStyle()) {
        
        case Pen::FLAT_CAP:
            cairo_set_line_cap(cairoContext.get(), CAIRO_LINE_CAP_BUTT);
            break;

        case Pen::SQUARE_CAP:
            cairo_set_line_cap(cairoContext.get(), CAIRO_LINE_CAP_SQUARE);
            break;

        default:
            cairo_set_line_cap(cairoContext.get(), CAIRO_LINE_CAP_ROUND);
    }

    cairo_set_line_width(cairoContext.get(), line_width);

    const Color& color = penStack.back().getColor();

    cairo_set_source_rgba(cairoContext.get(), color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
    
    cairo_stroke(cairoContext.get());
}
