/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * View2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::View2D.
 */

#ifndef CDPL_VIS_VIEW2D_HPP
#define CDPL_VIS_VIEW2D_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


namespace CDPL 
{

	namespace Vis
	{

		class Renderer2D;
		class FontMetrics;
		class Rectangle2D;

		/**
		 * \addtogroup CDPL_VIS_PRESENTATION
		 * @{
		 */

		/**
		 * \brief The abstract base of classes implementing the 2D visualization of data objects.
		 *
		 * Subclasses of \c %View2D implement the generation of two-dimensional visual representations of data objects
		 * with a given type. According to the <em>Model-View-Controller</em> [\ref WMVC] concept, a \c %View2D instance
		 * thus plays the role of the \e View for a \e Model represented by the visualized data object. The rendering of a model's
		 * visual represention on a given target device is performed by the render() method, which uses a passed Vis::Renderer2DRenderer2D
		 * instance for drawing the graphical primitives constituting the overall depiction. The behaviour of a \c %View2D
		 * instance can be configured using control-parameters and properties (if the type of the data object is a direct or indirect
		 * subclass of Base::PropertyContainer). Control-parameters can be modified and queried using the methods provided by 
		 * Base::ControlParameterContainer which is a public base class of \c %View2D.
		 */
		class CDPL_VIS_API View2D : public Base::ControlParameterContainer
		{

		public:
			/**
			 * \brief Virtual destructor.
			 */
			virtual ~View2D() {}
			
			/**
			 * \brief Renders the visual representation of the model using the specified Vis::Renderer2D instance.
			 * \param renderer The Renderer2D instance.
			 */
			virtual void render(Renderer2D& renderer) = 0;

			/**
			 * \brief Specifies a font metrics object that will be used to measure the dimension of text labels.
			 * \param font_metrics A pointer to the font metrics object or \e null.
			 */
			virtual void setFontMetrics(FontMetrics* font_metrics) = 0;

			/**
			 * \brief Calculates the bounding rectangle of the visualized model.
			 * \param bounds A Rectangle2D object storing the calculated bounding rectangle.
			 */
			virtual void getModelBounds(Rectangle2D& bounds) = 0;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_VIEW2D_HPP
