/* 
 * MMFF94ParameterSet.hpp 
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
 * \brief Definition of constants in namespace CDPL::ForceField::MMFF94ParameterSet.
 */

#ifndef CDPL_FORCEFIELD_MMFF94PARAMETERSET_HPP
#define CDPL_FORCEFIELD_MMFF94PARAMETERSET_HPP


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Provides flags for the specification of the MMFF94 parameter set to use.
         */
        namespace MMFF94ParameterSet
        {

            /** \brief Original (dynamic) MMFF94 parameter set. */
            constexpr unsigned int DYNAMIC          = 0;
            /** \brief Static MMFF94s parameter set (used for energy minimization). */
            constexpr unsigned int STATIC           = 1;
            /** \brief Static MMFF94s parameter set with extended out-of-plane bending parameters. */
            constexpr unsigned int STATIC_XOOP      = 2;
            /** \brief Static MMFF94s parameter set with restricted (refined) torsion parameters. */
            constexpr unsigned int STATIC_RTOR      = 3;
            /** \brief Static MMFF94s parameter set with both extended out-of-plane bending and restricted torsion parameters. */
            constexpr unsigned int STATIC_RTOR_XOOP = 4;
        } // namespace MMFF94ParameterSet
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94PARAMETERSET_HPP
