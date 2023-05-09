/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LinePrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::LinePrimitive2D.
 */

#ifndef CDPL_VIS_LINEPRIMITIVE2D_HPP
#define CDPL_VIS_LINEPRIMITIVE2D_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Pen.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief A graphics primitive representing a single line.
		 */
		class CDPL_VIS_API LinePrimitive2D : public Line2D, public GraphicsPrimitive2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %LinePrimitive2D instances.
			 */
			typedef boost::shared_ptr<LinePrimitive2D> SharedPointer;

			/**
			 * \brief Constructs a line primitive whose starting and end point is set to <em>(0, 0)</em>.
			 */
			LinePrimitive2D() {}

			/**
			 * \brief Constructs a line primitive with the starting point set to \a beg and the end point set to \a end.
			 * \param beg The starting point.
			 * \param end The end point.
			 */
			LinePrimitive2D(const Math::Vector2D& beg, const Math::Vector2D& end): Line2D(beg, end) {}
		
			/**
			 * \brief Constructs a line primitive with the same starting and end point as \a line.
			 * \param line The line defining the starting and end point.
			 */
			explicit LinePrimitive2D(const Line2D& line): Line2D(line) {}

			void render(Renderer2D& renderer) const;

			/**
			 * \brief Sets the pen defining the color, width, line style and cap style of the line.
			 * \param pen The pen defining the color, width, line style and cap style.
			 */
			void setPen(const Pen& pen);

			/**
			 * \brief Returns the pen defining the color, width, line style and cap style of the line.
			 * \return The pen defining the color, width, line style and cap style of the line.
			 */
			const Pen& getPen() const;

			GraphicsPrimitive2D::SharedPointer clone() const;

			void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics = 0) const;

		private:
			Pen   pen;
		};
	}
}

#endif // CDPL_VIS_LINEPRIMITIVE2D_HPP
