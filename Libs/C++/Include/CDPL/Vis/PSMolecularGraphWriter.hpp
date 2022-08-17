/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSMolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Vis::PSMolecularGraphWriter.
 */

#ifndef CDPL_VIS_PSMOLECULARGRAPHWRITER_HPP
#define CDPL_VIS_PSMOLECULARGRAPHWRITER_HPP

#include <iosfwd>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ImageWriter.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief Creates 2D structure diagrams of molecular graphs in the <em>PostScript (PS)</em> [\ref WPS] format. 
		 *
		 * \c %PSMolecularGraphWriter uses Vis::StructureView2D for the creation of 2D structure diagrams. All control-parameters and
		 * properties provided for the customization of Vis::StructureView2D are also supported by \c %PSMolecularGraphWriter.
		 */
		class CDPL_VIS_API PSMolecularGraphWriter : public Base::DataWriter<Chem::MolecularGraph>, private ImageWriter
		{

		public:
			/**
			 * \brief Constructs a \c %PSMolecularGraphWriter instance that will write the image data to the output stream \a os.
			 * \param os The output stream to write to.
			 * \note To ensure the validity of the written data, it is recommended to open the output stream in binary mode.
			 */
			PSMolecularGraphWriter(std::ostream& os);
		
			/**
			 * \brief Creates and outputs the 2D structure diagram of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to output the 2D structure diagram.
			 * \return A reference to itself.
			 */
			Base::DataWriter<Chem::MolecularGraph>& write(const Chem::MolecularGraph& molgraph);

			operator const void*() const;
			bool operator!() const;

		private:
			PSMolecularGraphWriter(const PSMolecularGraphWriter&);

			cairo_surface_t* createCairoSurface(double, double) const;
			cairo_surface_t* createCairoSurface() const;

			std::ostream& output;
			bool          state;
		};
	}
}

#endif // CDPL_VIS_PSMOLECULARGRAPHWRITER_HPP
