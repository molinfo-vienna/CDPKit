/* 
 * ControlParameterDefault.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/ControlParameterDefault.hpp"
#include "CDPL/Chem/MDLDataFormatVersion.hpp"
#include "CDPL/Chem/MOL2MoleculeType.hpp"
#include "CDPL/Chem/MOL2ChargeType.hpp"


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
            const bool MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD                               = false;
            const bool MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY                                   = false;
            const std::string MDL_CONF_ENERGY_SD_TAG                                        = "<Energy>";

            const std::string SMILES_RECORD_FORMAT                                          = "SN";
            const bool SMILES_OUTPUT_CANONICAL_FORM                                         = false;
            const bool SMILES_OUTPUT_KEKULE_FORM                                            = false;
            const bool SMILES_OUTPUT_ATOM_STEREO                                            = true;
            const bool SMILES_OUTPUT_BOND_STEREO                                            = true;
            const bool SMILES_OUTPUT_RING_BOND_STEREO                                       = true;
            const std::size_t SMILES_MIN_STEREO_BOND_RING_SIZE                              = 8;
            const bool SMILES_OUTPUT_ISOTOPE                                                = true;
            const bool SMILES_OUTPUT_HYDROGEN_COUNT                                         = true;
            const bool SMILES_RXN_OUTPUT_ATOM_MAPPING_ID                                    = true;
            const bool SMILES_MOL_OUTPUT_ATOM_MAPPING_ID                                    = false;
            const bool SMILES_OUTPUT_SINGLE_BONDS                                           = false;
            const bool SMILES_OUTPUT_AROMATIC_BONDS                                         = false;
            const bool SMILES_NO_ORGANIC_SUBSET                                             = false;

            const bool MULTI_CONF_IMPORT                                                    = true;
            const bool MULTI_CONF_EXPORT                                                    = true;
            const MultiConfMoleculeInputProcessor::SharedPointer MULTI_CONF_INPUT_PROCESSOR = MultiConfMoleculeInputProcessor::SharedPointer();
            const bool OUTPUT_CONF_ENERGY_AS_COMMENT                                        = false;
            const std::string CONF_INDEX_NAME_SUFFIX_PATTERN                                = "";

            const bool CDF_OUTPUT_SINGLE_PRECISION_FLOATS                                   = true;

            const bool MOL2_ENABLE_EXTENDED_ATOM_TYPES                                      = false;
            const bool MOL2_ENABLE_AROMATIC_BOND_TYPES                                      = false;
            const bool MOL2_READ_PARTIAL_AS_FORMAL_CHARGES                                  = false;
            const bool MOL2_CALC_FORMAL_CHARGES                                             = true;
            const unsigned int MOL2_CHARGE_TYPE                                             = MOL2ChargeType::NO_CHARGES;
            const unsigned int MOL2_MOLECULE_TYPE                                           = MOL2MoleculeType::SMALL;
            const bool MOL2_OUTPUT_SUBSTRUCTURES                                            = true;
            const bool MOL2_OUTPUT_FORMAL_CHARGES                                           = false;

            const bool XYZ_COMMENT_IS_NAME                                                  = true;
            const bool XYZ_PERCEIVE_CONNECTIVITY                                            = true;
            const bool XYZ_PERCEIVE_BOND_ORDERS                                             = true;
            const bool XYZ_CALC_FORMAL_CHARGES                                              = true;

            const bool CML_OUTPUT_XML_DECLARATION                                           = true;
            const std::string CML_OUTPUT_ELEMENT_NAMESPACE                                  = "";
            const bool CML_OUTPUT_ATOM_PARITY                                               = true;
            const bool CML_OUTPUT_SINGLE_BOND_STEREO                                        = true;
            const bool CML_OUTPUT_DOUBLE_BOND_STEREO                                        = true;
            const bool CML_OUTPUT_KEKULE_FORM                                               = true;
            const bool CML_OUTPUT_MOLECULE_NAME                                             = true;
            const bool CML_OUTPUT_STRUCTURE_DATA                                            = true;
            const bool CML_OUTPUT_ISOTOPE                                                   = true;
            const bool CML_OUTPUT_SPIN_MULTIPLICITY                                         = true;
            const bool CML_OUTPUT_COMPACT_ATOM_DATA                                         = false;
            const bool CML_OUTPUT_COMPACT_BOND_DATA                                         = false;
        }

        void initControlParameterDefaults() {}
    }
}
