/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SVGReactionWriter.hpp 
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
 * \brief Definition of the class CDPL::Vis::SVGReactionWriter.
 */

#ifndef CDPL_VIS_SVGREACTIONWRITER_HPP
#define CDPL_VIS_SVGREACTIONWRITER_HPP

#include <iosfwd>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ImageWriter.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_SVG_OUTPUT
		 * @{
		 */

		/**
		 * \brief Creates 2D depictions of chemical reactions in the <em>Scalable Vector Graphics (SVG)</em> [\ref WSVG] format. 
		 *
		 * \c %SVGReactionWriter uses Vis::ReactionView2D for the visualization of chemical reactions. All control-parameters and
		 * properties provided for the customization of Vis::ReactionView2D are also supported by \c %SVGReactionWriter.
		 */
		class CDPL_VIS_API SVGReactionWriter : public Base::DataWriter<Chem::Reaction>, private ImageWriter
		{

		public:
			/**
			 * \brief Constructs a \c %SVGReactionWriter instance that will write the image data to the output stream \a os.
			 * \param os The output stream to write to.
			 */
			SVGReactionWriter(std::ostream& os);

			/**
			 * \brief Creates and outputs a 2D depiction of the reaction \a rxn.
			 * \param rxn The reaction for which to output the 2D depiction.
			 * \return A reference to itself.
			 */
			Base::DataWriter<Chem::Reaction>& write(const Chem::Reaction& rxn);

			operator const void*() const;
			bool operator!() const;

		private:
			SVGReactionWriter(const SVGReactionWriter&);

			cairo_surface_t* createCairoSurface(double, double) const;
			cairo_surface_t* createCairoSurface() const;

			std::ostream& output;
			bool          state;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_SVGREACTIONWRITER_HPP
