/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Renderer2D.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Vis::Renderer2D.
 */

#ifndef CDPL_VIS_RENDERER2D_HPP
#define CDPL_VIS_RENDERER2D_HPP

#include <string>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_RENDERING_INTERFACES
		 * @{
		 */

		class Pen;
		class Brush;
		class Font;

		/**
		 * \brief An interface that provides methods for low level 2D drawing operations.
		 *
		 * For the drawing of graphical primitives the following methods are provided:
		 *  - drawPoint() for drawing points
		 *  - drawLine() for drawing single line segments
		 *  - drawPolyline() for drawing connected line segments
		 *  - drawLineSegments() for drawing a set of disjoint line segments
		 *  - drawPolygon() for drawing polygons
		 *  - drawRectangle() for drawing axis aligned rectangles
		 *  - and drawText() for drawing text
		 *
		 * Coordinates of points that define the geometry of graphical primitives are normally directly mapped to the coordinate
		 * system of the drawing device (e.g. an off-screen image buffer). This 1:1 mapping can be changed by applying
		 * affine transformations to the input coordinates. 
		 *
		 * Affine coordinate transformations can be specified by calling the methods:
		 *  - setTransform()
		 *  - and transform()
		 *
		 * The former method replaces the current transformation matrix by a matrix that was provided as argument. When the latter
		 * method is called, the current matrix gets multiplied with the argument matrix to produce a combined affine transformation.
		 * To restore the 1:1 coordinate mapping, call setTransform() with a default constructed Math::AffineTransform3D instance.
		 *
		 * The style and color of lines and shape outlines is defined by the current pen which is specified by setPen(). 
		 * The current pen also defines the color of rendered text and the color and diameter of points. The fill pattern
		 * and fill color of shapes (rectangles and polygons) is defined by the current brush which is specified by setBrush().
		 *
		 * The current state of the renderer (brush, pen, font and transformation matrix) may be saved by saveState()
		 * and restored by restoreState().
		 */
		class CDPL_VIS_API Renderer2D
		{

		public:
			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Renderer2D() {}

			/**
			 * \brief Saves the current renderer state.
			 *
			 * The method saves the current pen, brush, font and transformation matrix on an internal stack.
			 * The last saved state can be restored later on by a call to restoreState().
			 *
			 * \see restoreState()
			 */
			virtual void saveState() = 0;

			/**
			 * \brief Restores the last renderer state saved by a call to saveState().
			 * \see saveState()
			 */
			virtual void restoreState() = 0;

			/**
			 * \brief Sets the applied affine transformation matrix to \a xform.
			 * \param xform The new affine transformation matrix.
			 */
			virtual void setTransform(const Math::Matrix3D& xform) = 0;

			/**
			 * \brief Multiplies the current affine transformation matrix by \a xform.
			 * \param xform The matrix by which the current affine transformation matrix is multiplied.
			 */
			virtual void transform(const Math::Matrix3D& xform) = 0;
		
			/**
			 * \brief Sets the pen to be used in subsequent drawing operations.
			 * \param pen The new pen for subsequent drawing operations.
			 * \see Vis::Pen
			 */
			virtual void setPen(const Pen& pen) = 0;

			/**
			 * \brief Sets the brush to be used in subsequent drawing operations.
			 * \param brush The new brush for subsequent drawing operations.
			 * \see Vis::Brush
			 */
			virtual void setBrush(const Brush& brush) = 0;
			
			/**
			 * \brief Sets the font to be used in subsequent text drawing operations.
			 * \param font The new font used in subsequent text drawing operations.
			 * \see Vis::Font
			 */
			virtual void setFont(const Font& font) = 0;

			/**
			 * \brief Draws an axis aligned rectangle of the specified width and height whose upper-left corner is located
			 *        at <em>(x, y)</em>.
			 *
			 * The rectangle is filled as specified by the current brush and the outline will be drawn as specified by
			 * the current pen.
			 *
			 * \param x The x-coordinate of the upper-left corner.
			 * \param y The y-coordinate of the upper-left corner.
			 * \param width The width of the rectangle.
			 * \param height The height of the rectangle.
			 * \see setPen(), setBrush()
			 */
			virtual void drawRectangle(double x, double y, double width, double height) = 0;

			/**
			 * \brief Draws the polygon defined by \a points.
			 *
			 * For a given set of \f$ N \f$ corner points \f$ p_i \f$ with \f$ i = 1, 2, \ldots, N \f$, the polygon's \f$ N \f$
			 * edges are given by \f$ (p_1, p_2), (p_2, p_3), \ldots, (p_N, p_0) \f$. The polygon is filled as specified by the
			 * current brush and the outline will be drawn as specified by the current pen.
			 *
			 * \param points An array of points specifying the corners of the polygon.
			 * \see setPen(), setBrush()
			 */
			virtual void drawPolygon(const Math::Vector2DArray& points) = 0;

			/**
			 * \brief Draws a line segment from <em>(x1, y1)</em> to <em>(x2, y2)</em>.
			 *
			 * The line style, color, cap style and line width is specified by the current pen.
			 *
			 * \param x1 The x-coordinate of the starting point.
			 * \param y1 The y-coordinate of the starting point.
			 * \param x2 The x-coordinate of the end point.
			 * \param y2 The y-coordinate of the end point.
			 * \see setPen()
			 */
			virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
	
			/**
			 * \brief Draws the polyline defined by \a points.
			 *
			 * For a given set of \f$ N \f$ points \f$ p_i \f$ with \f$ i = 1, 2, \ldots, N \f$, \f$ N - 1 \f$ connected line segments
			 * \f$ (p_1, p_2), (p_2, p_3), \ldots, (p_{N - 1}, p_N) \f$ will be drawn. The line style, color, cap style, join style
			 * and line width is specified by the current pen.
			 *
			 * \param points An array of points defining the polyline.
			 * \see setPen()
			 */
			virtual void drawPolyline(const Math::Vector2DArray& points) = 0;
	
			/**
			 * \brief Draws the sequence of disjoint line segments defined by \a points.
			 *
			 * For a given set of \f$ 2N \f$ points \f$ p_i \f$ with \f$ i = 1, 2, \ldots, 2N \f$, \f$ N \f$ disjoint line segments
			 * \f$ (p_1, p_2), (p_3, p_4), \ldots, (p_{2N - 1}, p_2N) \f$ will be drawn. The line style, color, cap style and
			 * line width is specified by the current pen.
			 *
			 * \param points An array of points defining the line segments.
			 * \see setPen()
			 */
			virtual void drawLineSegments(const Math::Vector2DArray& points) = 0;

			/**
			 * \brief Draws a point at the position <em>(x, y)</em>.
			 *
			 * The diameter and color of the point is specified by the current pen.
			 *
			 * \param x The x-coordinate of the point.
			 * \param y The y-coordinate of the point.
			 * \see setPen()
			 */
			virtual void drawPoint(double x, double y) = 0;

			/**
			 * \brief Draws an ellipse with the given width and height around the center position <em>(x, y)</em>.
			 *
			 * The ellipse is filled as specified by the current brush and the outline will be drawn as specified by
			 * the current pen.
			 *
			 * \param x The x-coordinate of the center point.
			 * \param y The y-coordinate of the center point.
			 * \param width The width of the ellipse.
			 * \param height The height of the ellipse.
			 * \see setPen(), setBrush()
			 */
			virtual void drawEllipse(double x, double y, double width, double height) = 0;
			
			/**
			 * \brief Draws the specified text at the position <em>(x, y)</em>.
			 *
			 * The text color is specified by the current pen. The font has to be specified
			 * by setFont().
			 *
			 * \param x The x-position of the drawn text.
			 * \param y The y-position of the baseline.
			 * \param txt The text to draw.
			 * \see setPen(), setFont()
			 */
			virtual void drawText(double x, double y, const std::string& txt) = 0;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_RENDERER2D_HPP
