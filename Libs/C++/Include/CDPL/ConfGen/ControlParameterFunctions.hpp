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

#ifndef CDPL_CONFGEN_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_CONFGEN_CONTROLPARAMETERFUNCTIONS_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class ControlParameterContainer;
    }

    namespace ConfGen
    {

        /**
         * \brief Returns the value of the ConfGen::ControlParameter::STRICT_ERROR_CHECKING parameter stored in \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The current value of the STRICT_ERROR_CHECKING parameter (the ConfGen::ControlParameterDefault::STRICT_ERROR_CHECKING value if the parameter is unset).
         */
        CDPL_CONFGEN_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the ConfGen::ControlParameter::STRICT_ERROR_CHECKING parameter stored in \a cntnr.
         * \param cntnr The control-parameter container to update.
         * \param strict The new STRICT_ERROR_CHECKING value.
         */
        CDPL_CONFGEN_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

        /**
         * \brief Tells whether the ConfGen::ControlParameter::STRICT_ERROR_CHECKING parameter is set on \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_CONFGEN_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the ConfGen::ControlParameter::STRICT_ERROR_CHECKING parameter from \a cntnr.
         * \param cntnr The control-parameter container to update.
         */
        CDPL_CONFGEN_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);

    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_CONTROLPARAMETERFUNCTIONS_HPP
