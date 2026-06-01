/* 
 * ControlParameterFunctions.hpp 
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
 * \brief Declaration of convenience functions for control-parameter handling.
 */

#ifndef CDPL_CHEM_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_CHEM_CONTROLPARAMETERFUNCTIONS_HPP

#include <string>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"

#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"


namespace CDPL
{

    namespace Base
    {

        class ControlParameterContainer;
    }

    namespace Chem
    {

        /** \brief Returns the value of the Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getOrdinaryHydrogenDepleteParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE parameter in \a cntnr to \a deplete.
         *  \param cntnr The control-parameter container to modify.
         *  \param deplete The new parameter value. */
        CDPL_CHEM_API void setOrdinaryHydrogenDepleteParameter(Base::ControlParameterContainer& cntnr, bool deplete);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasOrdinaryHydrogenDepleteParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearOrdinaryHydrogenDepleteParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::COORDINATES_DIMENSION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored coordinate dimensionality. */
        CDPL_CHEM_API std::size_t getCoordinatesDimensionParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::COORDINATES_DIMENSION parameter in \a cntnr to \a dim.
         *  \param cntnr The control-parameter container to modify.
         *  \param dim The new coordinate dimensionality. */
        CDPL_CHEM_API void setCoordinatesDimensionParameter(Base::ControlParameterContainer& cntnr, std::size_t dim);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::COORDINATES_DIMENSION parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasCoordinatesDimensionParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::COORDINATES_DIMENSION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearCoordinatesDimensionParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::STRICT_ERROR_CHECKING parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::STRICT_ERROR_CHECKING parameter in \a cntnr to \a strict.
         *  \param cntnr The control-parameter container to modify.
         *  \param strict The new parameter value. */
        CDPL_CHEM_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::STRICT_ERROR_CHECKING parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::STRICT_ERROR_CHECKING parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::RECORD_SEPARATOR parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored record-separator string. */
        CDPL_CHEM_API const std::string& getRecordSeparatorParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::RECORD_SEPARATOR parameter in \a cntnr to \a sep.
         *  \param cntnr The control-parameter container to modify.
         *  \param sep The new record-separator string. */
        CDPL_CHEM_API void setRecordSeparatorParameter(Base::ControlParameterContainer& cntnr, const std::string& sep);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::RECORD_SEPARATOR parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasRecordSeparatorParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::RECORD_SEPARATOR parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearRecordSeparatorParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getBondMemberSwapStereoFixParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX parameter in \a cntnr to \a fix.
         *  \param cntnr The control-parameter container to modify.
         *  \param fix The new parameter value. */
        CDPL_CHEM_API void setBondMemberSwapStereoFixParameter(Base::ControlParameterContainer& cntnr, bool fix);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasBondMemberSwapStereoFixParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearBondMemberSwapStereoFixParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::CHECK_LINE_LENGTH parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CHECK_LINE_LENGTH parameter in \a cntnr to \a check.
         *  \param cntnr The control-parameter container to modify.
         *  \param check The new parameter value. */
        CDPL_CHEM_API void setCheckLineLengthParameter(Base::ControlParameterContainer& cntnr, bool check);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CHECK_LINE_LENGTH parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CHECK_LINE_LENGTH parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearCheckLineLengthParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_CTAB_VERSION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored CTab version (see namespace Chem::MDLDataFormatVersion). */
        CDPL_CHEM_API unsigned int getMDLCTABVersionParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_CTAB_VERSION parameter in \a cntnr to \a version.
         *  \param cntnr The control-parameter container to modify.
         *  \param version The new CTab version (see namespace Chem::MDLDataFormatVersion). */
        CDPL_CHEM_API void setMDLCTABVersionParameter(Base::ControlParameterContainer& cntnr, unsigned int version);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_CTAB_VERSION parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLCTABVersionParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_CTAB_VERSION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLCTABVersionParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_IGNORE_PARITY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLIgnoreParityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_IGNORE_PARITY parameter in \a cntnr to \a ignore.
         *  \param cntnr The control-parameter container to modify.
         *  \param ignore The new parameter value. */
        CDPL_CHEM_API void setMDLIgnoreParityParameter(Base::ControlParameterContainer& cntnr, bool ignore);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_IGNORE_PARITY parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLIgnoreParityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_IGNORE_PARITY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLIgnoreParityParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_UPDATE_TIMESTAMP parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLUpdateTimestampParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_UPDATE_TIMESTAMP parameter in \a cntnr to \a update.
         *  \param cntnr The control-parameter container to modify.
         *  \param update The new parameter value. */
        CDPL_CHEM_API void setMDLUpdateTimestampParameter(Base::ControlParameterContainer& cntnr, bool update);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_UPDATE_TIMESTAMP parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLUpdateTimestampParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_UPDATE_TIMESTAMP parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLUpdateTimestampParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_TRIM_STRINGS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLTrimStringsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_TRIM_STRINGS parameter in \a cntnr to \a trim.
         *  \param cntnr The control-parameter container to modify.
         *  \param trim The new parameter value. */
        CDPL_CHEM_API void setMDLTrimStringsParameter(Base::ControlParameterContainer& cntnr, bool trim);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_TRIM_STRINGS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLTrimStringsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_TRIM_STRINGS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLTrimStringsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_TRIM_LINES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLTrimLinesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_TRIM_LINES parameter in \a cntnr to \a trim.
         *  \param cntnr The control-parameter container to modify.
         *  \param trim The new parameter value. */
        CDPL_CHEM_API void setMDLTrimLinesParameter(Base::ControlParameterContainer& cntnr, bool trim);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_TRIM_LINES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLTrimLinesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_TRIM_LINES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLTrimLinesParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_TRUNCATE_STRINGS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLTruncateStringsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_TRUNCATE_STRINGS parameter in \a cntnr to \a trunc.
         *  \param cntnr The control-parameter container to modify.
         *  \param trunc The new parameter value. */
        CDPL_CHEM_API void setMDLTruncateStringsParameter(Base::ControlParameterContainer& cntnr, bool trunc);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_TRUNCATE_STRINGS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLTruncateStringsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_TRUNCATE_STRINGS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLTruncateStringsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_TRUNCATE_LINES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_TRUNCATE_LINES parameter in \a cntnr to \a trunc.
         *  \param cntnr The control-parameter container to modify.
         *  \param trunc The new parameter value. */
        CDPL_CHEM_API void setMDLTruncateLinesParameter(Base::ControlParameterContainer& cntnr, bool trunc);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_TRUNCATE_LINES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLTruncateLinesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_TRUNCATE_LINES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLTruncateLinesParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_RXN_FILE_VERSION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored RXN-file version (see namespace Chem::MDLDataFormatVersion). */
        CDPL_CHEM_API unsigned int getMDLRXNFileVersionParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_RXN_FILE_VERSION parameter in \a cntnr to \a version.
         *  \param cntnr The control-parameter container to modify.
         *  \param version The new RXN-file version (see namespace Chem::MDLDataFormatVersion). */
        CDPL_CHEM_API void setMDLRXNFileVersionParameter(Base::ControlParameterContainer& cntnr, unsigned int version);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_RXN_FILE_VERSION parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLRXNFileVersionParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_RXN_FILE_VERSION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLRXNFileVersionParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLOutputConfEnergyToEnergyFieldParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value. */
        CDPL_CHEM_API void setMDLOutputConfEnergyToEnergyFieldParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLOutputConfEnergyToEnergyFieldParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLOutputConfEnergyToEnergyFieldParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMDLOutputConfEnergyAsSDEntryParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value. */
        CDPL_CHEM_API void setMDLOutputConfEnergyAsSDEntryParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLOutputConfEnergyAsSDEntryParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLOutputConfEnergyAsSDEntryParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::MDL_ENABLE_AROMATIC_BOND_TYPES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.3
         */
        CDPL_CHEM_API bool getMDLEnableAromaticBondTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_ENABLE_AROMATIC_BOND_TYPES parameter in \a cntnr to \a enable.
         *  \param cntnr The control-parameter container to modify.
         *  \param enable The new parameter value.
         *  \since 1.3 */
        CDPL_CHEM_API void setMDLEnableAromaticBondTypesParameter(Base::ControlParameterContainer& cntnr, bool enable);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_ENABLE_AROMATIC_BOND_TYPES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.3 */
        CDPL_CHEM_API bool hasMDLEnableAromaticBondTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_ENABLE_AROMATIC_BOND_TYPES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.3 */
        CDPL_CHEM_API void clearMDLEnableAromaticBondTypesParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MDL_CONF_ENERGY_SD_TAG parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored SD-tag string. */
        CDPL_CHEM_API const std::string& getMDLConfEnergySDTagParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MDL_CONF_ENERGY_SD_TAG parameter in \a cntnr to \a tag.
         *  \param cntnr The control-parameter container to modify.
         *  \param tag The new SD-tag string. */
        CDPL_CHEM_API void setMDLConfEnergySDTagParameter(Base::ControlParameterContainer& cntnr, const std::string& tag);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MDL_CONF_ENERGY_SD_TAG parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMDLConfEnergySDTagParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MDL_CONF_ENERGY_SD_TAG parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMDLConfEnergySDTagParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::JME_SEPARATE_COMPONENTS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getJMESeparateComponentsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::JME_SEPARATE_COMPONENTS parameter in \a cntnr to \a separate.
         *  \param cntnr The control-parameter container to modify.
         *  \param separate The new parameter value. */
        CDPL_CHEM_API void setJMESeparateComponentsParameter(Base::ControlParameterContainer& cntnr, bool separate);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::JME_SEPARATE_COMPONENTS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasJMESeparateComponentsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::JME_SEPARATE_COMPONENTS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearJMESeparateComponentsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::SMILES_RECORD_FORMAT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored record-format string. */
        CDPL_CHEM_API const std::string& getSMILESRecordFormatParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_RECORD_FORMAT parameter in \a cntnr to \a format.
         *  \param cntnr The control-parameter container to modify.
         *  \param format The new record-format string. */
        CDPL_CHEM_API void setSMILESRecordFormatParameter(Base::ControlParameterContainer& cntnr, const std::string& format);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_RECORD_FORMAT parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasSMILESRecordFormatParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_RECORD_FORMAT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearSMILESRecordFormatParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_CANONICAL_FORM parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputCanonicalFormParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_CANONICAL_FORM parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputCanonicalFormParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_CANONICAL_FORM parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputCanonicalFormParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_CANONICAL_FORM parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputCanonicalFormParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_KEKULE_FORM parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputKekuleFormParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_KEKULE_FORM parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputKekuleFormParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_KEKULE_FORM parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputKekuleFormParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_KEKULE_FORM parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputKekuleFormParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_ATOM_STEREO parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputAtomStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_ATOM_STEREO parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputAtomStereoParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_ATOM_STEREO parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputAtomStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_ATOM_STEREO parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputAtomStereoParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_BOND_STEREO parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_BOND_STEREO parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputBondStereoParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_BOND_STEREO parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_BOND_STEREO parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputBondStereoParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_RING_BOND_STEREO parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputRingBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_RING_BOND_STEREO parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputRingBondStereoParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_RING_BOND_STEREO parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputRingBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_RING_BOND_STEREO parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputRingBondStereoParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored minimum ring size. */
        CDPL_CHEM_API std::size_t getSMILESMinStereoBondRingSizeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE parameter in \a cntnr to \a min_size.
         *  \param cntnr The control-parameter container to modify.
         *  \param min_size The new minimum ring size. */
        CDPL_CHEM_API void setSMILESMinStereoBondRingSizeParameter(Base::ControlParameterContainer& cntnr, std::size_t min_size);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasSMILESMinStereoBondRingSizeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearSMILESMinStereoBondRingSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_ISOTOPE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputIsotopeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_ISOTOPE parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputIsotopeParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_ISOTOPE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputIsotopeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_ISOTOPE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputIsotopeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_HYDROGEN_COUNT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.3
         */
        CDPL_CHEM_API bool getSMILESOutputHydrogenCountParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_HYDROGEN_COUNT parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.3 */
        CDPL_CHEM_API void setSMILESOutputHydrogenCountParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_HYDROGEN_COUNT parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.3 */
        CDPL_CHEM_API bool hasSMILESOutputHydrogenCountParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_HYDROGEN_COUNT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.3 */
        CDPL_CHEM_API void clearSMILESOutputHydrogenCountParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESMolOutputAtomMappingIDParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESMolOutputAtomMappingIDParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESMolOutputAtomMappingIDParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESMolOutputAtomMappingIDParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESRxnOutputAtomMappingIDParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESRxnOutputAtomMappingIDParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESRxnOutputAtomMappingIDParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESRxnOutputAtomMappingIDParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_SINGLE_BONDS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputSingleBondsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_SINGLE_BONDS parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputSingleBondsParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_SINGLE_BONDS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputSingleBondsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_SINGLE_BONDS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputSingleBondsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::SMILES_OUTPUT_AROMATIC_BONDS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getSMILESOutputAromaticBondsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_OUTPUT_AROMATIC_BONDS parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setSMILESOutputAromaticBondsParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_OUTPUT_AROMATIC_BONDS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasSMILESOutputAromaticBondsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_OUTPUT_AROMATIC_BONDS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearSMILESOutputAromaticBondsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getSMILESNoOrganicSubsetParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET parameter in \a cntnr to \a no_subset.
         *  \param cntnr The control-parameter container to modify.
         *  \param no_subset The new parameter value. */
        CDPL_CHEM_API void setSMILESNoOrganicSubsetParameter(Base::ControlParameterContainer& cntnr, bool no_subset);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasSMILESNoOrganicSubsetParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearSMILESNoOrganicSubsetParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::INCHI_INPUT_OPTIONS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored InChI input-options string. */
        CDPL_CHEM_API const std::string& getINCHIInputOptionsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::INCHI_INPUT_OPTIONS parameter in \a cntnr to \a opts.
         *  \param cntnr The control-parameter container to modify.
         *  \param opts The new InChI input-options string. */
        CDPL_CHEM_API void setINCHIInputOptionsParameter(Base::ControlParameterContainer& cntnr, const std::string& opts);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::INCHI_INPUT_OPTIONS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasINCHIInputOptionsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::INCHI_INPUT_OPTIONS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearINCHIInputOptionsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::INCHI_OUTPUT_OPTIONS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored InChI output-options string. */
        CDPL_CHEM_API const std::string& getINCHIOutputOptionsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::INCHI_OUTPUT_OPTIONS parameter in \a cntnr to \a opts.
         *  \param cntnr The control-parameter container to modify.
         *  \param opts The new InChI output-options string. */
        CDPL_CHEM_API void setINCHIOutputOptionsParameter(Base::ControlParameterContainer& cntnr, const std::string& opts);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::INCHI_OUTPUT_OPTIONS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasINCHIOutputOptionsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::INCHI_OUTPUT_OPTIONS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearINCHIOutputOptionsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MULTI_CONF_IMPORT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMultiConfImportParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MULTI_CONF_IMPORT parameter in \a cntnr to \a multi_conf.
         *  \param cntnr The control-parameter container to modify.
         *  \param multi_conf The new parameter value. */
        CDPL_CHEM_API void setMultiConfImportParameter(Base::ControlParameterContainer& cntnr, bool multi_conf);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MULTI_CONF_IMPORT parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMultiConfImportParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MULTI_CONF_IMPORT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMultiConfImportParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MULTI_CONF_EXPORT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMultiConfExportParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MULTI_CONF_EXPORT parameter in \a cntnr to \a multi_conf.
         *  \param cntnr The control-parameter container to modify.
         *  \param multi_conf The new parameter value. */
        CDPL_CHEM_API void setMultiConfExportParameter(Base::ControlParameterContainer& cntnr, bool multi_conf);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MULTI_CONF_EXPORT parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMultiConfExportParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MULTI_CONF_EXPORT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMultiConfExportParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::OUTPUT_CONF_ENERGY_AS_COMMENT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getOutputConfEnergyAsCommentParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::OUTPUT_CONF_ENERGY_AS_COMMENT parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value. */
        CDPL_CHEM_API void setOutputConfEnergyAsCommentParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::OUTPUT_CONF_ENERGY_AS_COMMENT parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasOutputConfEnergyAsCommentParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::OUTPUT_CONF_ENERGY_AS_COMMENT parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearOutputConfEnergyAsCommentParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::CONF_INDEX_NAME_SUFFIX_PATTERN parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored suffix-pattern string. */
        CDPL_CHEM_API const std::string& getConfIndexNameSuffixPatternParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CONF_INDEX_NAME_SUFFIX_PATTERN parameter in \a cntnr to \a pattern.
         *  \param cntnr The control-parameter container to modify.
         *  \param pattern The new suffix-pattern string. */
        CDPL_CHEM_API void setConfIndexNameSuffixPatternParameter(Base::ControlParameterContainer& cntnr, const std::string& pattern);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CONF_INDEX_NAME_SUFFIX_PATTERN parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasConfIndexNameSuffixPatternParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CONF_INDEX_NAME_SUFFIX_PATTERN parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearConfIndexNameSuffixPatternParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored MultiConfMoleculeInputProcessor pointer. */
        CDPL_CHEM_API const MultiConfMoleculeInputProcessor::SharedPointer& getMultiConfInputProcessorParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR parameter in \a cntnr to \a proc.
         *  \param cntnr The control-parameter container to modify.
         *  \param proc The new MultiConfMoleculeInputProcessor pointer. */
        CDPL_CHEM_API void setMultiConfInputProcessorParameter(Base::ControlParameterContainer& cntnr, const MultiConfMoleculeInputProcessor::SharedPointer& proc);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMultiConfInputProcessorParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMultiConfInputProcessorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCDFOutputSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter in \a cntnr to \a single_prec.
         *  \param cntnr The control-parameter container to modify.
         *  \param single_prec The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCDFOutputSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr, bool single_prec);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCDFOutputSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCDFOutputSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMOL2EnableExtendedAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter in \a cntnr to \a enable.
         *  \param cntnr The control-parameter container to modify.
         *  \param enable The new parameter value. */
        CDPL_CHEM_API void setMOL2EnableExtendedAtomTypesParameter(Base::ControlParameterContainer& cntnr, bool enable);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMOL2EnableExtendedAtomTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMOL2EnableExtendedAtomTypesParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MOL2_ENABLE_AROMATIC_BOND_TYPES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMOL2EnableAromaticBondTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_ENABLE_AROMATIC_BOND_TYPES parameter in \a cntnr to \a enable.
         *  \param cntnr The control-parameter container to modify.
         *  \param enable The new parameter value. */
        CDPL_CHEM_API void setMOL2EnableAromaticBondTypesParameter(Base::ControlParameterContainer& cntnr, bool enable);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_ENABLE_AROMATIC_BOND_TYPES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMOL2EnableAromaticBondTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_ENABLE_AROMATIC_BOND_TYPES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMOL2EnableAromaticBondTypesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2.3
         */
        CDPL_CHEM_API bool getMOL2ReadPartialAsFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter in \a cntnr to \a read.
         *  \param cntnr The control-parameter container to modify.
         *  \param read The new parameter value.
         *  \since 1.2.3 */
        CDPL_CHEM_API void setMOL2ReadPartialAsFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool read);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2.3 */
        CDPL_CHEM_API bool hasMOL2ReadPartialAsFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2.3 */
        CDPL_CHEM_API void clearMOL2ReadPartialAsFormalChargesParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MOL2_CALC_FORMAL_CHARGES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMOL2CalcFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_CALC_FORMAL_CHARGES parameter in \a cntnr to \a calc.
         *  \param cntnr The control-parameter container to modify.
         *  \param calc The new parameter value. */
        CDPL_CHEM_API void setMOL2CalcFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool calc);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_CALC_FORMAL_CHARGES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMOL2CalcFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_CALC_FORMAL_CHARGES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMOL2CalcFormalChargesParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MOL2_CHARGE_TYPE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored MOL2 charge type (see namespace Chem::MOL2ChargeType). */
        CDPL_CHEM_API unsigned int getMOL2ChargeTypeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_CHARGE_TYPE parameter in \a cntnr to \a type.
         *  \param cntnr The control-parameter container to modify.
         *  \param type The new MOL2 charge type (see namespace Chem::MOL2ChargeType). */
        CDPL_CHEM_API void setMOL2ChargeTypeParameter(Base::ControlParameterContainer& cntnr, unsigned int type);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_CHARGE_TYPE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMOL2ChargeTypeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_CHARGE_TYPE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMOL2ChargeTypeParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MOL2_MOLECULE_TYPE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored MOL2 molecule type (see namespace Chem::MOL2MoleculeType). */
        CDPL_CHEM_API unsigned int getMOL2MoleculeTypeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_MOLECULE_TYPE parameter in \a cntnr to \a type.
         *  \param cntnr The control-parameter container to modify.
         *  \param type The new MOL2 molecule type (see namespace Chem::MOL2MoleculeType). */
        CDPL_CHEM_API void setMOL2MoleculeTypeParameter(Base::ControlParameterContainer& cntnr, unsigned int type);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_MOLECULE_TYPE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMOL2MoleculeTypeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_MOLECULE_TYPE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMOL2MoleculeTypeParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::MOL2_OUTPUT_SUBSTRUCTURES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value. */
        CDPL_CHEM_API bool getMOL2OutputSubstructuresParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_OUTPUT_SUBSTRUCTURES parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value. */
        CDPL_CHEM_API void setMOL2OutputSubstructuresParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_OUTPUT_SUBSTRUCTURES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise. */
        CDPL_CHEM_API bool hasMOL2OutputSubstructuresParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_OUTPUT_SUBSTRUCTURES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify. */
        CDPL_CHEM_API void clearMOL2OutputSubstructuresParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::MOL2_OUTPUT_FORMAL_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2.3
         */
        CDPL_CHEM_API bool getMOL2OutputFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::MOL2_OUTPUT_FORMAL_CHARGES parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2.3 */
        CDPL_CHEM_API void setMOL2OutputFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::MOL2_OUTPUT_FORMAL_CHARGES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2.3 */
        CDPL_CHEM_API bool hasMOL2OutputFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::MOL2_OUTPUT_FORMAL_CHARGES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2.3 */
        CDPL_CHEM_API void clearMOL2OutputFormalChargesParameter(Base::ControlParameterContainer& cntnr);
        

        /** \brief Returns the value of the Chem::ControlParameter::XYZ_COMMENT_IS_NAME parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API bool getXYZCommentIsNameParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::XYZ_COMMENT_IS_NAME parameter in \a cntnr to \a is_name.
         *  \param cntnr The control-parameter container to modify.
         *  \param is_name The new parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API void setXYZCommentIsNameParameter(Base::ControlParameterContainer& cntnr, bool is_name);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::XYZ_COMMENT_IS_NAME parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.1 */
        CDPL_CHEM_API bool hasXYZCommentIsNameParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::XYZ_COMMENT_IS_NAME parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.1 */
        CDPL_CHEM_API void clearXYZCommentIsNameParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::XYZ_PERCEIVE_CONNECTIVITY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API bool getXYZPerceiveConnectivityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::XYZ_PERCEIVE_CONNECTIVITY parameter in \a cntnr to \a perceive.
         *  \param cntnr The control-parameter container to modify.
         *  \param perceive The new parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API void setXYZPerceiveConnectivityParameter(Base::ControlParameterContainer& cntnr, bool perceive);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::XYZ_PERCEIVE_CONNECTIVITY parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.1 */
        CDPL_CHEM_API bool hasXYZPerceiveConnectivityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::XYZ_PERCEIVE_CONNECTIVITY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.1 */
        CDPL_CHEM_API void clearXYZPerceiveConnectivityParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::XYZ_PERCEIVE_BOND_ORDERS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API bool getXYZPerceiveBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::XYZ_PERCEIVE_BOND_ORDERS parameter in \a cntnr to \a perceive.
         *  \param cntnr The control-parameter container to modify.
         *  \param perceive The new parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API void setXYZPerceiveBondOrdersParameter(Base::ControlParameterContainer& cntnr, bool perceive);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::XYZ_PERCEIVE_BOND_ORDERS parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.1 */
        CDPL_CHEM_API bool hasXYZPerceiveBondOrdersParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::XYZ_PERCEIVE_BOND_ORDERS parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.1 */
        CDPL_CHEM_API void clearXYZPerceiveBondOrdersParameter(Base::ControlParameterContainer& cntnr);


        /** \brief Returns the value of the Chem::ControlParameter::XYZ_CALC_FORMAL_CHARGES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to query.
         *  \return The stored parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API bool getXYZCalcFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::XYZ_CALC_FORMAL_CHARGES parameter in \a cntnr to \a calc.
         *  \param cntnr The control-parameter container to modify.
         *  \param calc The new parameter value.
         *  \since 1.1 */
        CDPL_CHEM_API void setXYZCalcFormalChargesParameter(Base::ControlParameterContainer& cntnr, bool calc);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::XYZ_CALC_FORMAL_CHARGES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.1 */
        CDPL_CHEM_API bool hasXYZCalcFormalChargesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::XYZ_CALC_FORMAL_CHARGES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.1 */
        CDPL_CHEM_API void clearXYZCalcFormalChargesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_XML_DECLARATION parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputXMLDeclarationParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_XML_DECLARATION parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputXMLDeclarationParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_XML_DECLARATION parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputXMLDeclarationParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_XML_DECLARATION parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputXMLDeclarationParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_ELEMENT_NAMESPACE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored XML-namespace string.
         * \since 1.2
         */
        CDPL_CHEM_API const std::string& getCMLOutputElementNamespaceParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_ELEMENT_NAMESPACE parameter in \a cntnr to \a ns.
         *  \param cntnr The control-parameter container to modify.
         *  \param ns The new XML-namespace string.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputElementNamespaceParameter(Base::ControlParameterContainer& cntnr, const std::string& ns);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_ELEMENT_NAMESPACE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputElementNamespaceParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_ELEMENT_NAMESPACE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputElementNamespaceParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_ATOM_PARITY parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputAtomParityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_ATOM_PARITY parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputAtomParityParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_ATOM_PARITY parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputAtomParityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_ATOM_PARITY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputAtomParityParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_SINGLE_BOND_STEREO parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputSingleBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_SINGLE_BOND_STEREO parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputSingleBondStereoParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_SINGLE_BOND_STEREO parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputSingleBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_SINGLE_BOND_STEREO parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputSingleBondStereoParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_DOUBLE_BOND_STEREO parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputDoubleBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_DOUBLE_BOND_STEREO parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputDoubleBondStereoParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_DOUBLE_BOND_STEREO parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputDoubleBondStereoParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_DOUBLE_BOND_STEREO parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputDoubleBondStereoParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_ENABLE_AROMATIC_BOND_TYPES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.3
         */
        CDPL_CHEM_API bool getCMLEnableAromaticBondTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_ENABLE_AROMATIC_BOND_TYPES parameter in \a cntnr to \a enable.
         *  \param cntnr The control-parameter container to modify.
         *  \param enable The new parameter value.
         *  \since 1.3 */
        CDPL_CHEM_API void setCMLEnableAromaticBondTypesParameter(Base::ControlParameterContainer& cntnr, bool enable);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_ENABLE_AROMATIC_BOND_TYPES parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.3 */
        CDPL_CHEM_API bool hasCMLEnableAromaticBondTypesParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_ENABLE_AROMATIC_BOND_TYPES parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.3 */
        CDPL_CHEM_API void clearCMLEnableAromaticBondTypesParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_MOLECULE_NAME parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputMoleculeNameParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_MOLECULE_NAME parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputMoleculeNameParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_MOLECULE_NAME parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputMoleculeNameParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_MOLECULE_NAME parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputMoleculeNameParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_STRUCTURE_DATA parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputStructureDataParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_STRUCTURE_DATA parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputStructureDataParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_STRUCTURE_DATA parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputStructureDataParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_STRUCTURE_DATA parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputStructureDataParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_ISOTOPE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputIsotopeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_ISOTOPE parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputIsotopeParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_ISOTOPE parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputIsotopeParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_ISOTOPE parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputIsotopeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_SPIN_MULTIPLICITY parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputSpinMultiplicityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_SPIN_MULTIPLICITY parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputSpinMultiplicityParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_SPIN_MULTIPLICITY parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputSpinMultiplicityParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_SPIN_MULTIPLICITY parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputSpinMultiplicityParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_COMPACT_ATOM_DATA parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputCompactAtomDataParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_COMPACT_ATOM_DATA parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputCompactAtomDataParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_COMPACT_ATOM_DATA parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputCompactAtomDataParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_COMPACT_ATOM_DATA parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputCompactAtomDataParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Chem::ControlParameter::CML_OUTPUT_COMPACT_BOND_DATA parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The stored parameter value.
         * \since 1.2
         */
        CDPL_CHEM_API bool getCMLOutputCompactBondDataParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Sets the value of the Chem::ControlParameter::CML_OUTPUT_COMPACT_BOND_DATA parameter in \a cntnr to \a output.
         *  \param cntnr The control-parameter container to modify.
         *  \param output The new parameter value.
         *  \since 1.2 */
        CDPL_CHEM_API void setCMLOutputCompactBondDataParameter(Base::ControlParameterContainer& cntnr, bool output);

        /** \brief Tells whether \a cntnr carries the Chem::ControlParameter::CML_OUTPUT_COMPACT_BOND_DATA parameter.
         *  \param cntnr The control-parameter container to query.
         *  \return \c true if the parameter is set, and \c false otherwise.
         *  \since 1.2 */
        CDPL_CHEM_API bool hasCMLOutputCompactBondDataParameter(const Base::ControlParameterContainer& cntnr);

        /** \brief Removes the Chem::ControlParameter::CML_OUTPUT_COMPACT_BOND_DATA parameter from \a cntnr.
         *  \param cntnr The control-parameter container to modify.
         *  \since 1.2 */
        CDPL_CHEM_API void clearCMLOutputCompactBondDataParameter(Base::ControlParameterContainer& cntnr);
        
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CONTROLPARAMETERFUNCTIONS_HPP
