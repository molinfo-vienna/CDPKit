/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SDFMolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::SDFMolecularGraphWriter.
 */

#ifndef CDPL_CHEM_SDFMOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_SDFMOLECULARGRAPHWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MDLDataWriter;
		class MolecularGraph;

		/**
		 * \brief A writer for molecular graph data in the <em>MDL Mol-File</em> [\ref CTFILE] format.
		 *
		 * \c %SDFMolecularGraphWriter supports the following control-parameters:
		 *
		 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::COORDINATES_DIMENSION</td>
		 *   <td align="center">\c 0</td>
		 *   <td>Specifies the dimension of atom coordinates</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether reverse stereo bonds shall be converted to regular stereo bonds by swapping bond start and end
		 *       atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MULTI_CONF_EXPORT</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to write all molecule conformations on output</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_CTAB_VERSION</td>
		 *   <td align="center">\c 0</td>
		 *   <td>Specifies the desired connection table format</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_IGNORE_PARITY</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether the stereo parity of atoms shall be ignored</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_UPDATE_TIMESTAMP</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether the timestamp of \e Mol- and \e Rxn-File header blocks has to be updated</td>
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
		 *   <td>Chem::ControlParameter::MDL_TRUNCATE_STRINGS</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether string values that exceed the size of an output data field may be truncated</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_TRUNCATE_LINES</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether data lines that exceed the maximum allowed line length may be truncated</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::MDL_IGNORE_LINE_LENGTH_LIMIT</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to check if data lines exceed the maximum allowed line length</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_CHEM_API SDFMolecularGraphWriter : public Base::DataWriter<MolecularGraph>
		{

		public:
			/**
			 * \brief Constructs a \c %SDFMolecularGraphWriter instance that will write data of molecular graphs to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			SDFMolecularGraphWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~SDFMolecularGraphWriter();

			/**
			 * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
			 * \param molgraph The molecular graph to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<MolecularGraph>& write(const MolecularGraph& molgraph);

			operator const void*() const;
			bool operator!() const;

		private:
			SDFMolecularGraphWriter(const SDFMolecularGraphWriter&);

			SDFMolecularGraphWriter& operator=(const SDFMolecularGraphWriter&);

			typedef std::auto_ptr<MDLDataWriter> MDLDataWriterPtr;

			std::ostream&    output;
			bool             state;
			MDLDataWriterPtr writer;
		};
	}
}

#endif // CDPL_CHEM_SDFMOLECULARGRAPHWRITER_HPP
