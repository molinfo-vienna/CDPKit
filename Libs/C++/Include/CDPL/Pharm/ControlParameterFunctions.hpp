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

#ifndef CDPL_PHARM_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_PHARM_CONTROLPARAMETERFUNCTIONS_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/ScreeningDBCreator.hpp"


namespace CDPL
{

    namespace Base
    {

        class ControlParameterContainer;
    }

    namespace Pharm
    {

        /**
         * \brief Returns the value of the Pharm::ControlParameter::STRICT_ERROR_CHECKING parameter of \a cntnr.
         * \param cntnr The control-parameter container.
         * \return \c true if strict error checking is enabled, and \c false otherwise.
         */
        CDPL_PHARM_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the Pharm::ControlParameter::STRICT_ERROR_CHECKING parameter of \a cntnr to \a strict.
         * \param cntnr The control-parameter container.
         * \param strict \c true to enable strict error checking, and \c false to disable it.
         */
        CDPL_PHARM_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

        /**
         * \brief Tells whether \a cntnr carries an explicit Pharm::ControlParameter::STRICT_ERROR_CHECKING parameter.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Pharm::ControlParameter::STRICT_ERROR_CHECKING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_PHARM_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Pharm::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of \a cntnr.
         * \param cntnr The control-parameter container.
         * \return \c true if <em>CDF</em> output uses single-precision floats, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool getCDFOutputSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the Pharm::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of \a cntnr to \a single_prec.
         * \param cntnr The control-parameter container.
         * \param single_prec \c true to write single-precision floats, and \c false to write double-precision floats.
         * \since 1.2
         */
        CDPL_PHARM_API void setCDFOutputSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr, bool single_prec);

        /**
         * \brief Tells whether \a cntnr carries an explicit Pharm::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool hasCDFOutputSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Pharm::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_PHARM_API void clearCDFOutputSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Pharm::ControlParameter::PSD_CREATION_MODE parameter of \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The Pharm::ScreeningDBCreator::Mode value.
         */
        CDPL_PHARM_API ScreeningDBCreator::Mode getPSDCreationModeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the Pharm::ControlParameter::PSD_CREATION_MODE parameter of \a cntnr to \a mode.
         * \param cntnr The control-parameter container.
         * \param mode The new Pharm::ScreeningDBCreator::Mode value.
         */
        CDPL_PHARM_API void setPSDCreationModeParameter(Base::ControlParameterContainer& cntnr, ScreeningDBCreator::Mode mode);

        /**
         * \brief Tells whether \a cntnr carries an explicit Pharm::ControlParameter::PSD_CREATION_MODE parameter.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasPSDCreationModeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Pharm::ControlParameter::PSD_CREATION_MODE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_PHARM_API void clearPSDCreationModeParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Pharm::ControlParameter::PSD_ALLOW_DUPLICATES parameter of \a cntnr.
         * \param cntnr The control-parameter container.
         * \return \c true if duplicate database entries are allowed, and \c false otherwise.
         */
        CDPL_PHARM_API bool getPSDAllowDuplicatesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the Pharm::ControlParameter::PSD_ALLOW_DUPLICATES parameter of \a cntnr to \a allow.
         * \param cntnr The control-parameter container.
         * \param allow \c true to allow duplicate database entries, and \c false to reject them.
         */
        CDPL_PHARM_API void setPSDAllowDuplicatesParameter(Base::ControlParameterContainer& cntnr, bool allow);

        /**
         * \brief Tells whether \a cntnr carries an explicit Pharm::ControlParameter::PSD_ALLOW_DUPLICATES parameter.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasPSDAllowDuplicatesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Pharm::ControlParameter::PSD_ALLOW_DUPLICATES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_PHARM_API void clearPSDAllowDuplicatesParameter(Base::ControlParameterContainer& cntnr);
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_CONTROLPARAMETERFUNCTIONS_HPP
