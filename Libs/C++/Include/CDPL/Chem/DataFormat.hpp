/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormat.hpp 
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
 * \brief Provides the contents of namespace CDPL::Chem::DataFormat.
 */

#ifndef CDPL_CHEM_DATAFORMAT_HPP
#define CDPL_CHEM_DATAFORMAT_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

	namespace Base
	{

		class DataFormat;
	}

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_DATA_FORMATS
		 * @{
		 */
		
		/**
		 * \brief Provides preinitialized Base::DataFormat objects for all supported chemical data formats.
		 */
		namespace DataFormat
		{
	
			/**
			 * \brief Provides meta-information about the native I/O format of the <em>JME Molecular Editor</em>
			 *        [\ref JME] java applet.
			 */
			extern CDPL_CHEM_API const Base::DataFormat JME;

			/**
			 * \brief Provides meta-information about the <em>MDL Mol-File</em> [\ref CTFILE] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat MOL;

			/**
			 * \brief Provides meta-information about the <em>MDL SD-File</em> [\ref CTFILE] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat SDF;

			/**
			 * \brief Provides meta-information about the <em>MDL Rxn-File</em> [\ref CTFILE] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat RXN;

			/**
			 * \brief Provides meta-information about the <em>MDL RD-File</em> [\ref CTFILE] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat RDF;

			/**
			 * \brief Provides meta-information about the <em>Daylight SMILES</em> [\ref SMILES] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat SMILES;

			/**
			 * \brief Provides meta-information about the <em>Daylight SMARTS</em> [\ref SMARTS] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat SMARTS;

			/**
			 * \brief Provides meta-information about the <em>IUPAC International Chemical Identifier (InChI)</em>
			 *        [\ref INCHI] format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat INCHI;
	
			/**
			 * \brief Provides meta-information about the native <em>CDPL</em> format.
			 */
			extern CDPL_CHEM_API const Base::DataFormat CDF;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_DATAFORMAT_HPP
