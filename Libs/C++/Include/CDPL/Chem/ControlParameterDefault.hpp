/* 
 * ControlParameterDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::ControlParameterDefault.
 */

#ifndef CDPL_CHEM_CONTROLPARAMETERDEFAULT_HPP
#define CDPL_CHEM_CONTROLPARAMETERDEFAULT_HPP

#include <string>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides default values for built-in control-parameters.
         */
        namespace ControlParameterDefault
        {

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::STRICT_ERROR_CHECKING.
             */
            extern CDPL_CHEM_API const bool STRICT_ERROR_CHECKING;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE.
             */
            extern CDPL_CHEM_API const bool ORDINARY_HYDROGEN_DEPLETE;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX.
             */
            extern CDPL_CHEM_API const bool BOND_MEMBER_SWAP_STEREO_FIX;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::CHECK_LINE_LENGTH.
             */
            extern CDPL_CHEM_API const bool CHECK_LINE_LENGTH;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::JME_SEPARATE_COMPONENTS.
             */
            extern CDPL_CHEM_API const bool JME_SEPARATE_COMPONENTS;

            /**
             * \brief Default setting (= \c "\n") for the control-parameter Chem::ControlParameter::RECORD_SEPARATOR.
             */
            extern CDPL_CHEM_API const std::string RECORD_SEPARATOR;

            /**
             * \brief Default setting (= \c "") for the control-parameter Chem::ControlParameter::INCHI_INPUT_OPTIONS.
             */
            extern CDPL_CHEM_API const std::string INCHI_INPUT_OPTIONS;

            /**
             * \brief Default setting (= \c "/WarnOnEmptyStructure /AuxNone /NEWPSOFF") for the control-parameter Chem::ControlParameter::INCHI_OUTPUT_OPTIONS.
             */
            extern CDPL_CHEM_API const std::string INCHI_OUTPUT_OPTIONS;

            /**
             * \brief Default setting (= \c 1) for the control-parameter Chem::ControlParameter::COORDINATES_DIMENSION.
             */
            extern CDPL_CHEM_API const std::size_t COORDINATES_DIMENSION;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_IGNORE_PARITY.
             */
            extern CDPL_CHEM_API const bool MDL_IGNORE_PARITY;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::MDL_TRIM_STRINGS.
             */
            extern CDPL_CHEM_API const bool MDL_TRIM_STRINGS;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_TRIM_LINES.
             */
            extern CDPL_CHEM_API const bool MDL_TRIM_LINES;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_TRUNCATE_STRINGS.
             */
            extern CDPL_CHEM_API const bool MDL_TRUNCATE_STRINGS;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_TRUNCATE_LINES.
             */
            extern CDPL_CHEM_API const bool MDL_TRUNCATE_LINES;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_UPDATE_TIMESTAMP.
             */
            extern CDPL_CHEM_API const bool MDL_UPDATE_TIMESTAMP;

            /**
             * \brief Default setting (= \c %MDLDataFormatVersion::UNDEF) for the control-parameter Chem::ControlParameter::MDL_CTAB_VERSION.
             */
            extern CDPL_CHEM_API const unsigned int MDL_CTAB_VERSION;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD.
             */
            extern CDPL_CHEM_API const bool MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY.
             */
            extern CDPL_CHEM_API const bool MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY;

            /**
             * \brief Default setting (= \c "<Energy>") for the control-parameter Chem::ControlParameter::MDL_CONF_ENERGY_SD_TAG.
             */
            extern CDPL_CHEM_API const std::string MDL_CONF_ENERGY_SD_TAG;

            /**
             * \brief Default setting (= \c %MDLDataFormatVersion::UNDEF) for the control-parameter Chem::ControlParameter::MDL_RXN_FILE_VERSION.
             */
            extern CDPL_CHEM_API const unsigned int MDL_RXN_FILE_VERSION;

            /**
             * \brief Default setting (= \c "S") for the control-parameter Chem::ControlParameter::SMILES_RECORD_FORMAT.
             */
            extern CDPL_CHEM_API const std::string SMILES_RECORD_FORMAT;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::SMILES_WRITE_CANONICAL_FORM.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_CANONICAL_FORM;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::SMILES_WRITE_KEKULE_FORM.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_KEKULE_FORM;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::SMILES_WRITE_ATOM_STEREO.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_ATOM_STEREO;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::SMILES_WRITE_BOND_STEREO.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_BOND_STEREO;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::SMILES_WRITE_RING_BOND_STEREO.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_RING_BOND_STEREO;

            /**
             * \brief Default setting (= \c 8) for the control-parameter Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE.
             */
            extern CDPL_CHEM_API const std::size_t SMILES_MIN_STEREO_BOND_RING_SIZE;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::SMILES_WRITE_ISOTOPE.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_ISOTOPE;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::SMILES_WRITE_ATOM_MAPPING_ID
             *        on reaction SMILES output.
             */
            extern CDPL_CHEM_API const bool SMILES_RXN_WRITE_ATOM_MAPPING_ID;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::SMILES_WRITE_ATOM_MAPPING_ID
             *        on molecule SMILES output.
             */
            extern CDPL_CHEM_API const bool SMILES_MOL_WRITE_ATOM_MAPPING_ID;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::SMILES_WRITE_SINGLE_BONDS.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_SINGLE_BONDS;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::SMILES_WRITE_AROMATIC_BONDS.
             */
            extern CDPL_CHEM_API const bool SMILES_WRITE_AROMATIC_BONDS;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET.
             */
            extern CDPL_CHEM_API const bool SMILES_NO_ORGANIC_SUBSET;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::MULTI_CONF_IMPORT.
             */
            extern CDPL_CHEM_API const bool MULTI_CONF_IMPORT;

            /**
             * \brief Default setting (= \c true) for the control-parameter Chem::ControlParameter::MULTI_CONF_EXPORT.
             */
            extern CDPL_CHEM_API const bool MULTI_CONF_EXPORT;

            /**
             * \brief Default setting (= pointer to Chem::DefaultMultiConfMoleculeInputProcessor instance) for the control-parameter 
             *        Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR.
             */
            extern CDPL_CHEM_API const MultiConfMoleculeInputProcessor::SharedPointer MULTI_CONF_INPUT_PROCESSOR;

            /**
             * \brief Default setting (= \c false) for the control-parameter Chem::ControlParameter::OUTPUT_CONF_ENERGY_AS_COMMENT.
             */
            extern CDPL_CHEM_API const bool OUTPUT_CONF_ENERGY_AS_COMMENT;

            extern CDPL_CHEM_API const std::string CONF_INDEX_NAME_SUFFIX_PATTERN;

            extern CDPL_CHEM_API const bool CDF_WRITE_SINGLE_PRECISION_FLOATS;

            extern CDPL_CHEM_API const bool MOL2_ENABLE_EXTENDED_ATOM_TYPES;

            extern CDPL_CHEM_API const bool MOL2_ENABLE_AROMATIC_BOND_TYPES;

            extern CDPL_CHEM_API const bool MOL2_CALC_FORMAL_CHARGES;

            extern CDPL_CHEM_API const unsigned int MOL2_CHARGE_TYPE;

            extern CDPL_CHEM_API const unsigned int MOL2_MOLECULE_TYPE;

            extern CDPL_CHEM_API const bool MOL2_OUTPUT_SUBSTRUCTURES;

            extern CDPL_CHEM_API const bool XYZ_PERCEIVE_CONNECTIVITY;

            extern CDPL_CHEM_API const bool XYZ_PERCEIVE_BOND_ORDERS;

            extern CDPL_CHEM_API const bool XYZ_CALC_FORMAL_CHARGES;

        } // namespace ControlParameterDefault
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CONTROLPARAMETERDEFAULT_HPP
