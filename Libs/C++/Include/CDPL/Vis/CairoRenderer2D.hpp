/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CairoRenderer2D.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Vis::CairoRenderer2D.
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
		 * \addtogroup CDPL_VIS_RENDERING_BACKENDS
		 * @{
		 */

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

			void saveState();
			void restoreState();

			void setTransform(const Math::Matrix3D& xform);
			void transform(const Math::Matrix3D& xform);

			void setPen(const Pen& pen);
			void setBrush(const Brush& brush);
			void setFont(const Font& font);

			void drawRectangle(double x1, double y1, double x2, double y2);
			void drawPolygon(const Math::Vector2DArray& points);
			void drawLine(double x1, double y1, double x2, double y2);
			void drawPolyline(const Math::Vector2DArray& points);
			void drawLineSegments(const Math::Vector2DArray& points);
			void drawPoint(double x, double y);
			void drawText(double x, double y, const std::string& txt);
			void drawEllipse(double x, double y, double width, double height);

		private:
			void fillPath() const;
			void strokePath() const;

			typedef std::vector<Pen> PenStack;
			typedef std::vector<Brush> BrushStack;
			typedef std::vector<Font> FontStack;

			CairoPointer<cairo_t> cairoContext;
			PenStack              penStack;
			BrushStack            brushStack;
			FontStack             fontStack;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_CAIRORENDERER2D_HPP
