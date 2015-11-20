/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMILESReactionWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::SMILESReactionWriter.
 */

#ifndef CDPL_CHEM_SMILESREACTIONWRITER_HPP
#define CDPL_CHEM_SMILESREACTIONWRITER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class SMILESDataWriter;
		class Reaction;

		/**
		 * \addtogroup CDPL_CHEM_SMILES_IO
		 * @{
		 */

		/**
		 * \brief A writer for reaction data in the <em>Daylight SMILES</em> [\ref SMILES] format.
		 *
		 * \c %SMILESReactionWriter supports the following control-parameters:
		 *
		 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether or not to write explicit ordinary hydrogen atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_RECORD_FORMAT</td>
		 *   <td align="center">\c "S"</td>
		 *   <td>Specifies the data record format</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_CANONICAL_FORM</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether to generate canonical \e SMILES strings</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_KEKULE_FORM</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether to output aromatic rings as \e Kekul&eacute; structures</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_ATOM_STEREO</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to output the chirality of tetrahedral stereogenic atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_BOND_STEREO</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to output directional bonds for the specification of chain double bond geometries</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_RING_BOND_STEREO</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to output directional bonds for the specification of ring double bond geometries</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE</td>
		 *   <td align="center">\c 8</td>
		 *   <td>Specifies the minimum ring size that is required for the specification of ring double bond geometries</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_ISOTOPE</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to output the mass of isotopes</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_RXN_WRITE_ATOM_MAPPING_ID</td>
		 *   <td align="center">\c true</td>
		 *   <td>Specifies whether to output reaction atom-atom mapping numbers</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_SINGLE_BONDS</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether to output single bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_WRITE_AROMATIC_BONDS</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether to output aromatic bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether ordinary <em>C, N, O, S, P, F, Cl, Br</em> and <em>I</em> atoms shall be enclosed in brackets</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_CHEM_API SMILESReactionWriter : public Base::DataWriter<Reaction>
		{

		public:
			/**
			 * \brief Constructs a \c %SMILESReactionWriter instance that will write the reaction data to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			SMILESReactionWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~SMILESReactionWriter();

			/**
			 * \brief Writes the reaction \a rxn to the output stream specified in the constructor.
			 * \param rxn The reaction to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<Reaction>& write(const Reaction& rxn);

			operator const void*() const;
			bool operator!() const;

		private:
			typedef std::auto_ptr<SMILESDataWriter> SMILESDataWriterPtr;

			SMILESReactionWriter(const SMILESReactionWriter&);

			std::ostream&       output;
			bool                state;
			SMILESDataWriterPtr writer;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SMILESREACTIONWRITER_HPP
