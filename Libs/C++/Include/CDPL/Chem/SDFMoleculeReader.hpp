/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SDFMoleculeReader.hpp 
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
 * \brief Definition of the class CDPL::Chem::SDFMoleculeReader.
 */

#ifndef CDPL_CHEM_SDFMOLECULEREADER_HPP
#define CDPL_CHEM_SDFMOLECULEREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MDLDataReader;
		class Molecule;

		/**
		 * \addtogroup CDPL_CHEM_SDF_IO
		 * @{
		 */

		/**
		 * \brief A Reader for molecule data in the <em>MDL SD-File</em> [\ref CTFILE] format.
		 *
		 * \c %SDFMoleculeReader supports the following control-parameters:
		 *
		 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MULTI_CONF_IMPORT</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to check for and import multi-conformer molecules</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR</td>
		 *   <td align="center">pointer to a Chem::DefaultMultiConfMoleculeInputProcessor instance</td>
		 *   <td>Specifies an instance of Chem::MultiConfMoleculeInputProcessor that implements the logic of
		 *       multi-conformer molecule detection and conformational data processing</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_IGNORE_PARITY</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether the stereo parity of atoms shall be ignored</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_TRIM_STRINGS</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to remove leading and trailing whitespace from string values</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_TRIM_LINES</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether to remove leading and trailing whitespace from data lines</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_IGNORE_LINE_LENGTH_LIMIT</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to check if data lines exceed the maximum allowed line length</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_CHEM_API SDFMoleculeReader : public Util::StreamDataReader<Molecule, SDFMoleculeReader>
		{

		public:
			/**
			 * \brief Constructs a \c %SDFMoleculeReader instance that will read the molecule data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			SDFMoleculeReader(std::istream& is);

			/**
			 * \brief Destructor.
			 */
			~SDFMoleculeReader();

		private:
			friend class Util::StreamDataReader<Molecule, SDFMoleculeReader>;

			SDFMoleculeReader(const SDFMoleculeReader&);

			SDFMoleculeReader& operator=(const SDFMoleculeReader&);

			bool readData(std::istream&, Molecule&, bool overwrite);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			typedef std::auto_ptr<MDLDataReader> MDLDataReaderPtr;

			MDLDataReaderPtr reader;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SDFMOLECULEREADER_HPP
