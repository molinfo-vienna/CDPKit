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

#ifndef CDPL_GRID_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_GRID_CONTROLPARAMETERFUNCTIONS_HPP

#include "CDPL/Grid/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class ControlParameterContainer;
    }

    namespace Grid
    {

        /**
         * \brief Returns the value of the Grid::ControlParameter::STRICT_ERROR_CHECKING parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return \c true if strict error checking is enabled, and \c false otherwise.
         */
        CDPL_GRID_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Grid::ControlParameter::STRICT_ERROR_CHECKING parameter of \a cntnr to \a strict.
         * \param cntnr The control-parameter container.
         * \param strict \c true to enable strict error checking, and \c false to disable it.
         */
        CDPL_GRID_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

        /**
         * \brief Tells whether the Grid::ControlParameter::STRICT_ERROR_CHECKING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_GRID_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Grid::ControlParameter::STRICT_ERROR_CHECKING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_GRID_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Grid::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return \c true if <em>CDF</em> output uses single-precision floats, and \c false otherwise.
         * \since 1.2
         */
        CDPL_GRID_API bool getCDFOutputSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Grid::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of \a cntnr to \a single_prec.
         * \param cntnr The control-parameter container.
         * \param single_prec \c true to write single-precision floats, and \c false to write double-precision floats.
         * \since 1.2
         */
        CDPL_GRID_API void setCDFOutputSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr, bool single_prec);

        /**
         * \brief Tells whether the Grid::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_GRID_API bool hasCDFOutputSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Grid::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_GRID_API void clearCDFOutputSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Grid::ControlParameter::CUBE_COMMENT_IS_NAME parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return \c true if the <em>Gaussian CUBE</em> comment line is interpreted as the grid name, and \c false otherwise.
         * \since 1.4
         */
        CDPL_GRID_API bool getCUBECommentIsNameParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Grid::ControlParameter::CUBE_COMMENT_IS_NAME parameter of \a cntnr to \a is_name.
         * \param cntnr The control-parameter container.
         * \param is_name \c true to interpret the <em>Gaussian CUBE</em> comment line as the grid name, and \c false to treat it as a regular comment.
         * \since 1.4
         */
        CDPL_GRID_API void setCUBECommentIsNameParameter(Base::ControlParameterContainer& cntnr, bool is_name);

        /**
         * \brief Tells whether the Grid::ControlParameter::CUBE_COMMENT_IS_NAME parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.4
         */
        CDPL_GRID_API bool hasCUBECommentIsNameParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Grid::ControlParameter::CUBE_COMMENT_IS_NAME parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.4
         */
        CDPL_GRID_API void clearCUBECommentIsNameParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Grid::ControlParameter::CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The input distance scaling factor.
         * \since 1.4
         */
        CDPL_GRID_API double getCUBEInputDistanceScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Grid::ControlParameter::CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter of \a cntnr to \a factor.
         * \param cntnr The control-parameter container.
         * \param factor The new input distance scaling.
         * \since 1.4
         */
        CDPL_GRID_API void setCUBEInputDistanceScalingFactorParameter(Base::ControlParameterContainer& cntnr, double factor);

        /**
         * \brief Tells whether the Grid::ControlParameter::CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.4
         */
        CDPL_GRID_API bool hasCUBEInputDistanceScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Grid::ControlParameter::CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.4
         */
        CDPL_GRID_API void clearCUBEInputDistanceScalingFactorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Grid::ControlParameter::CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter stored in \a cntnr.
         * \param cntnr The control-parameter container.
         * \return The output distance scaling factor.
         * \since 1.4
         */
        CDPL_GRID_API double getCUBEOutputDistanceScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Grid::ControlParameter::CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter of \a cntnr to \a factor.
         * \param cntnr The control-parameter container.
         * \param factor The new output distance scaling factor.
         * \since 1.4
         */
        CDPL_GRID_API void setCUBEOutputDistanceScalingFactorParameter(Base::ControlParameterContainer& cntnr, double factor);

        /**
         * \brief Tells whether the Grid::ControlParameter::CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.4
         */
        CDPL_GRID_API bool hasCUBEOutputDistanceScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Grid::ControlParameter::CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.4
         */
        CDPL_GRID_API void clearCUBEOutputDistanceScalingFactorParameter(Base::ControlParameterContainer& cntnr);
        
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_CONTROLPARAMETERFUNCTIONS_HPP
