/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * EllipsePrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::EllipsePrimitive2D.
 */

#ifndef CDPL_VIS_ELLIPSEPRIMITIVE2D_HPP
#define CDPL_VIS_ELLIPSEPRIMITIVE2D_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief A graphics primitive representing a ellipse.
		 */
		class CDPL_VIS_API EllipsePrimitive2D : public GraphicsPrimitive2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %EllipsePrimitive2D instances.
			 */
			typedef boost::shared_ptr<EllipsePrimitive2D> SharedPointer;

			/**
			 * \brief Constructs an undefined ellipse primitive.
			 */
			EllipsePrimitive2D(): width(0.0), height(0.0) {}

			/**
			 * \brief Constructs an undefined ellipse primitive.
			 */
			EllipsePrimitive2D(const Math::Vector2D& pos, double width, double height): 
				position(pos), width(width), height(height) {}

			void render(Renderer2D& renderer) const;
		
			/**
			 * \brief Sets the pen defining the color, width, line style, cap style and join style of the ellipse outline.
			 * \param pen The pen defining the color, width, line style, cap style and join style of the ellipse's outline.
			 */
			void setPen(const Pen& pen);

			/**
			 * \brief Returns the pen defining the color, width, line style, cap style and join style of the ellipse outline.
			 * \return The pen defining the color, width, line style, cap style and join style of the ellipse outline.
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

			/**
			 * \brief Sets the position of the ellipse center.
			 * \param pos The center position of the ellipse.
			 */
			void setPosition(const Math::Vector2D& pos);

			/**
			 * \brief Returns the position of the ellipse center.
			 * \return The center position of the ellipse.
			 */
			const Math::Vector2D& getPosition() const;

			/**
			 * \brief Sets the diameter of the ellipse in x-direction.
			 * \param width The width of the ellipse.
			 */
			void setWidth(double width);

			/**
			 * \brief Returns the diameter of the ellipse in x-direction.
			 * \return The width of the ellipse.
			 */
			double getWidth() const;

			/**
			 * \brief Sets the diameter of the ellipse in y-direction.
			 * \param height The height of the ellipse.
			 */
			void setHeight(double height);

			/**
			 * \brief Returns the diameter of the ellipse in y-direction.
			 * \return The height of the ellipse.
			 */
			double getHeight() const;

			GraphicsPrimitive2D::SharedPointer clone() const;

			void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics = 0) const;

		private:
			Math::Vector2D position;
			double         width;
			double         height;
			Pen            pen;
			Brush          brush;
		};
	}
}

#endif // CDPL_VIS_ELLIPSEPRIMITIVE2D_HPP
