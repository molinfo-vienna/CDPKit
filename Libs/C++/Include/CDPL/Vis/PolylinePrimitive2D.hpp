/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PolylinePrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::PolylinePrimitive2D.
 */

#ifndef CDPL_VIS_POLYLINEPRIMITIVE2D_HPP
#define CDPL_VIS_POLYLINEPRIMITIVE2D_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/PointArray2D.hpp"
#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Pen.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief A graphics primitive representing a set of connected line segments.
		 */
		class CDPL_VIS_API PolylinePrimitive2D : public PointArray2D, public GraphicsPrimitive2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %PolylinePrimitive2D instances.
			 */
			typedef boost::shared_ptr<PolylinePrimitive2D> SharedPointer;

			/**
			 * \brief Constructs an empty polyline primitive.
			 */
			PolylinePrimitive2D() {}

			void render(Renderer2D& renderer) const;
	
			/**
			 * \brief Sets the pen defining the color, width, line style, join style and cap style of the line segments.
			 * \param pen The pen defining the color, width, line style, join style and cap style of the line segments.
			 */
			void setPen(const Pen& pen);

			/**
			 * \brief Returns the pen defining the color, width, line style, join style and cap style of the line segments.
			 * \return The pen defining the color, width, line style, join style and cap style of the line segments.
			 */
			const Pen& getPen() const;

			GraphicsPrimitive2D::SharedPointer clone() const;

			void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics = 0) const;

		private:
			Pen   pen;
		};
	}
}

#endif // CDPL_VIS_POLYLINEPRIMITIVE2D_HPP
