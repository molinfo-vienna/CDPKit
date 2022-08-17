/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PolygonPrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::PolygonPrimitive2D.
 */

#ifndef CDPL_VIS_POLYGONPRIMITIVE2D_HPP
#define CDPL_VIS_POLYGONPRIMITIVE2D_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/PointArray2D.hpp"
#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief A graphics primitive representing a polygon.
		 */
		class CDPL_VIS_API PolygonPrimitive2D : public PointArray2D, public GraphicsPrimitive2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %PolygonPrimitive2D instances.
			 */
			typedef boost::shared_ptr<PolygonPrimitive2D> SharedPointer;

			/**
			 * \brief Constructs an undefined polygon primitive.
			 */
			PolygonPrimitive2D() {}

			void render(Renderer2D& renderer) const;
		
			/**
			 * \brief Sets the pen defining the color, width, line style, cap style and join style of the polygon outline.
			 * \param pen The pen defining the color, width, line style, cap style and join style of the polygon's outline.
			 */
			void setPen(const Pen& pen);

			/**
			 * \brief Returns the pen defining the color, width, line style, cap style and join style of the polygon outline.
			 * \return The pen defining the color, width, line style, cap style and join style of the polygon outline.
			 */
			const Pen& getPen() const;

			/**
			 * \brief Sets the brush defining the fill color and fill pattern.
			 * \param brush The brush defining the fill color and fill pattern.
			 */
			void setBrush(const Brush& brush);

			/**
			 * \brief Returns the brush defining the fill color and fill pattern.
			 * \return The brush defining the fill color and fill pattern.
			 */
			const Brush& getBrush() const;

			GraphicsPrimitive2D::SharedPointer clone() const;

			void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics = 0) const;

		private:
			Pen   pen;
			Brush brush;
		};
	}
}

#endif // CDPL_VIS_POLYGONPRIMITIVE2D_HPP
