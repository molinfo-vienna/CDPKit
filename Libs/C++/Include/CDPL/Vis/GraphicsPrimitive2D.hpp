/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GraphicsPrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::GraphicsPrimitive2D.
 */

#ifndef CDPL_VIS_GRAPHICSPRIMITIVE2D_HPP
#define CDPL_VIS_GRAPHICSPRIMITIVE2D_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_RENDERING_INTERFACES
		 * @{
		 */

		class Renderer2D;
		class FontMetrics;
		class Rectangle2D;

		/**
		 * \brief The abstract base class of all 2D graphics primitives.
		 *
		 * Graphics primitives are simple (atomic) geometrical objects which can be used as building blocks for
		 * larger and more complex drawings (e.g. the 2D depiction of a molecular structure). The actual
		 * type (e.g. point, line, polygon, ...) and look (e.g. color, font, ...) of an graphics primitive is defined
		 * by subclasses of \c %GraphicsPrimitive2D. Subclasses have to implement the render()
		 * method that visualizes the primitive by means of a Renderer2D implementation instance.
		 */
		class CDPL_VIS_API GraphicsPrimitive2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %GraphicsPrimitive2D instances.
			 */
			typedef boost::shared_ptr<GraphicsPrimitive2D> SharedPointer;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~GraphicsPrimitive2D() {}

			/**
			 * \brief Visualizes the graphics primitive by means of the Renderer2D instance \a renderer.
			 * \param renderer The renderer that performs the drawing operations.
			 */
			virtual void render(Renderer2D& renderer) const = 0;

			/**
			 * \brief Creates a dynamically allocated copy of the graphics primitive.
			 * \return The copy of the graphics primitive.
			 */
			virtual SharedPointer clone() const = 0;

			/**
			 * \brief Calculates the bounds of the graphics primitive.
			 * \param bounds The object storing the calculated bounding box.
			 * \param font_metrics The font metrics object to use for bounds calculation (if required).
			 */
			virtual void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics = 0) const = 0;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_GRAPHICSPRIMITIVE2D_HPP
