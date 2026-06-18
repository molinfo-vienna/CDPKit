/* 
 * ReturnCode.hpp 
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
 * \brief Definition of constants in namespace CDPL::Confgen::ReturnCode.
 */

#ifndef CDPL_CONFGEN_RETURNCODE_HPP
#define CDPL_CONFGEN_RETURNCODE_HPP


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Provides constants that are used to describe the result of operations related to conformer generation.
         */
        namespace ReturnCode
        {

            /**
             * \brief Operation completed successfully.
             */
            const int SUCCESS                        = 0;

            /**
             * \brief The operation could not be carried out due to uninitialized input data.
             */
            const int UNINITIALIZED                  = 1;

            /**
             * \brief The operation was terminated because the configured wall clock time limit was exceeded.
             */
            const int TIMEOUT                        = 2;

            /**
             * \brief The operation was terminated through the registered abort callback.
             */
            const int ABORTED                        = 3;

            /**
             * \brief The MMFF94 force field parameterization step failed (typically due to missing/ambiguous parameters under strict mode).
             */
            const int FORCEFIELD_SETUP_FAILED        = 4;

            /**
             * \brief The MMFF94 energy-minimization step failed to converge or produced an invalid result.
             */
            const int FORCEFIELD_MINIMIZATION_FAILED = 5;

            /**
             * \brief No fragment library has been configured (required for fragment-based structure generation).
             */
            const int FRAGMENT_LIBRARY_NOT_SET       = 6;

            /**
             * \brief Conformer generation for at least one fragment failed.
             */
            const int FRAGMENT_CONF_GEN_FAILED       = 7;

            /**
             * \brief Conformer generation for at least one fragment timed out.
             */
            const int FRAGMENT_CONF_GEN_TIMEOUT      = 8;

            /**
             * \brief The submitted fragment has already been processed.
             */
            const int FRAGMENT_ALREADY_PROCESSED     = 9;

            /**
             * \brief The torsion-driving step failed.
             */
            const int TORSION_DRIVING_FAILED         = 10;

            /**
             * \brief The overall conformer generation pipeline failed.
             */
            const int CONF_GEN_FAILED                = 11;

            /**
             * \brief The molecule exhibits too high a symmetry to enumerate all symmetry mappings within the configured limit.
             */
            const int TOO_MUCH_SYMMETRY              = 12;

            /**
             * \brief The input molecule's rotatable bond count exceeds the configured maximum.
             */
            const int MAX_ROT_BOND_COUNT_EXCEEDED    = 13;

            /**
             * \brief A fixed substructure was specified but no 3D coordinates were supplied for it.
             */
            const int NO_FIXED_SUBSTRUCT_COORDS      = 14;
        } // namespace ReturnCode
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_RETURNCODE_HPP
