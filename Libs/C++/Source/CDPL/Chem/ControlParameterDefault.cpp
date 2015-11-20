/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterDefault.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/ControlParameterDefault.hpp"
#include "CDPL/Chem/MDLDataFormatVersion.hpp"
#include "CDPL/Chem/DefaultMultiConfMoleculeInputProcessor.hpp"


namespace CDPL
{

	namespace Chem
	{

		namespace ControlParameterDefault
		{

			const bool STRICT_ERROR_CHECKING                                                = false;
			const bool ORDINARY_HYDROGEN_DEPLETE                                            = true;
			const bool BOND_MEMBER_SWAP_STEREO_FIX                                          = true;
			const bool CHECK_LINE_LENGTH                                                    = false;
			const std::string RECORD_SEPARATOR                                              = "\n";
			const std::size_t COORDINATES_DIMENSION                                         = 1;

			const bool JME_SEPARATE_COMPONENTS                                              = true;

			const std::string INCHI_INPUT_OPTIONS                                           = "";
			const std::string INCHI_OUTPUT_OPTIONS                                          = "/WarnOnEmptyStructure /AuxNone /NEWPSOFF";

			const bool MDL_IGNORE_PARITY                                                    = false;
			const bool MDL_TRIM_STRINGS                                                     = true;
			const bool MDL_TRIM_LINES                                                       = false;
			const bool MDL_TRUNCATE_STRINGS                                                 = false;
			const bool MDL_TRUNCATE_LINES                                                   = false;
			const bool MDL_UPDATE_TIMESTAMP                                                 = false;
			const unsigned int MDL_CTAB_VERSION                                             = MDLDataFormatVersion::UNDEF;
			const unsigned int MDL_RXN_FILE_VERSION                                         = MDLDataFormatVersion::UNDEF;

			const std::string SMILES_RECORD_FORMAT                                          = "S";
			const bool SMILES_WRITE_CANONICAL_FORM                                          = false;
			const bool SMILES_WRITE_KEKULE_FORM                                             = false;
			const bool SMILES_WRITE_ATOM_STEREO                                             = true;
			const bool SMILES_WRITE_BOND_STEREO                                             = true;
			const bool SMILES_WRITE_RING_BOND_STEREO                                        = true;
			const std::size_t SMILES_MIN_STEREO_BOND_RING_SIZE                              = 8;
			const bool SMILES_WRITE_ISOTOPE                                                 = true;
			const bool SMILES_RXN_WRITE_ATOM_MAPPING_ID                                     = true;
			const bool SMILES_MOL_WRITE_ATOM_MAPPING_ID                                     = false;
			const bool SMILES_WRITE_SINGLE_BONDS                                            = false;
			const bool SMILES_WRITE_AROMATIC_BONDS                                          = false;
			const bool SMILES_NO_ORGANIC_SUBSET                                             = false;

			const bool MULTI_CONF_IMPORT                                                    = true;
			const bool MULTI_CONF_EXPORT                                                    = true;
			const MultiConfMoleculeInputProcessor::SharedPointer MULTI_CONF_INPUT_PROCESSOR = MultiConfMoleculeInputProcessor::SharedPointer(new DefaultMultiConfMoleculeInputProcessor());
		}

		void initControlParameterDefaults() {}
	}
}
