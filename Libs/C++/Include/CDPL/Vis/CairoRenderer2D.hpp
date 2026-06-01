/* 
 * CairoRenderer2D.hpp 
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

/**
 * \file
 * \brief Definition of class CDPL::Vis::CairoRenderer2D.
 */

#ifndef CDPL_VIS_CAIRORENDERER2D_HPP
#define CDPL_VIS_CAIRORENDERER2D_HPP

#include <vector>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/CairoPointer.hpp"


typedef struct _cairo cairo_t;


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Implements the Renderer2D interface on top of the <em>Cairo 2D Graphics Library</em>.
         *
         * For more information about the <em>Cairo 2D Graphics Library</em> see [\ref CAIRO].
         */
        class CDPL_VIS_API CairoRenderer2D : public Renderer2D
        {

          public:
            /**
             * \brief Constructs a renderer object that operates on the \e Cairo cdrawing ontext specified by \a cairo_ctxt.
             * \param cairo_ctxt The \e Cairo drawing context.
             * \throw Base::NullPointerException if \a cairo_ctxt is \e null.
             */
            CairoRenderer2D(const CairoPointer<cairo_t>& cairo_ctxt);

            /**
             * \brief Destructor.
             */
            ~CairoRenderer2D();

            /**
             * \brief Pushes the current pen, brush, font, transformation and clip path onto an internal state stack.
             */
            void saveState();

            /**
             * \brief Pops the topmost stack entry and restores the renderer to the saved state.
             */
            void restoreState();

            /**
             * \brief Replaces the current transformation matrix by \a xform.
             * \param xform The new transformation matrix.
             */
            void setTransform(const Math::Matrix3D& xform);

            /**
             * \brief Right-multiplies the current transformation matrix by \a xform.
             * \param xform The transformation matrix to append.
             */
            void transform(const Math::Matrix3D& xform);

            /**
             * \brief Sets the pen used for drawing outlines and lines.
             * \param pen The new pen.
             */
            void setPen(const Pen& pen);

            /**
             * \brief Sets the brush used for filling shapes.
             * \param brush The new brush.
             */
            void setBrush(const Brush& brush);

            /**
             * \brief Sets the font used for rendering text.
             * \param font The new font.
             */
            void setFont(const Font& font);

            /**
             * \brief Draws an axis-aligned rectangle from <em>(x1, y1)</em> to <em>(x2, y2)</em>.
             * \param x1 The x-coordinate of the first corner.
             * \param y1 The y-coordinate of the first corner.
             * \param x2 The x-coordinate of the opposing corner.
             * \param y2 The y-coordinate of the opposing corner.
             */
            void drawRectangle(double x1, double y1, double x2, double y2);

            /**
             * \brief Draws the (filled) polygon defined by the vertex sequence \a points.
             * \param points The polygon's vertex sequence.
             */
            void drawPolygon(const Math::Vector2DArray& points);

            /**
             * \brief Draws a single line segment from <em>(x1, y1)</em> to <em>(x2, y2)</em>.
             * \param x1 The x-coordinate of the line's start point.
             * \param y1 The y-coordinate of the line's start point.
             * \param x2 The x-coordinate of the line's end point.
             * \param y2 The y-coordinate of the line's end point.
             */
            void drawLine(double x1, double y1, double x2, double y2);

            /**
             * \brief Draws the open polyline defined by the vertex sequence \a points.
             * \param points The polyline's vertex sequence.
             */
            void drawPolyline(const Math::Vector2DArray& points);

            /**
             * \brief Draws the disjoint line segments defined by consecutive vertex pairs in \a points.
             * \param points The vertex sequence (size must be even).
             */
            void drawLineSegments(const Math::Vector2DArray& points);

            /**
             * \brief Draws a single point at <em>(x, y)</em>.
             * \param x The point's x-coordinate.
             * \param y The point's y-coordinate.
             */
            void drawPoint(double x, double y);

            /**
             * \brief Draws the text \a txt with its baseline starting at <em>(x, y)</em>.
             * \param x The baseline x-coordinate.
             * \param y The baseline y-coordinate.
             * \param txt The text to draw.
             */
            void drawText(double x, double y, const std::string& txt);

            /**
             * \brief Draws an axis-aligned ellipse centered at <em>(x, y)</em> with the given \a width and \a height.
             * \param x The x-coordinate of the ellipse's center.
             * \param y The y-coordinate of the ellipse's center.
             * \param width The width of the ellipse.
             * \param height The height of the ellipse.
             */
            void drawEllipse(double x, double y, double width, double height);

            /**
             * \brief Draws (strokes and fills) the 2D path \a path.
             * \param path The path to draw.
             */
            void drawPath(const Path2D& path);

            /**
             * \brief Sets the renderer's active clipping region to \a path.
             * \param path The path defining the new clipping region.
             */
            void setClipPath(const Path2D& path);

            /**
             * \brief Disables any currently active clipping region.
             */
            void clearClipPath();

          private:
            void fillPath() const;
            void strokePath() const;

            typedef std::vector<Pen>   PenStack;
            typedef std::vector<Brush> BrushStack;
            typedef std::vector<Font>  FontStack;

            CairoPointer<cairo_t> cairoContext;
            PenStack              penStack;
            BrushStack            brushStack;
            FontStack             fontStack;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_CAIRORENDERER2D_HPP
