/* 
 * GenericHydrogen13ShiftTautomerization.hpp 
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
 * \brief Definition of class CDPL::Chem::GenericHydrogen13ShiftTautomerization.
 */

#ifndef CDPL_CHEM_GENERICHYDROGEN13SHIFTTAUTOMERIZATION_HPP
#define CDPL_CHEM_GENERICHYDROGEN13SHIFTTAUTOMERIZATION_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/PatternBasedTautomerizationRule.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Chem::TautomerizationRule implementation that enumerates tautomers obtained by a generic
         *        1,3-hydrogen shift (a proton migrates between atoms separated by two bonds, with the corresponding
         *        single/double bond pattern flipping).
         */
        class CDPL_CHEM_API GenericHydrogen13ShiftTautomerization : public PatternBasedTautomerizationRule
        {

          public:
            /**
             * \brief Constructs the rule and registers the underlying generic 1,3-H-shift substructure pattern.
             */
            GenericHydrogen13ShiftTautomerization();
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_GENERICHYDROGEN13SHIFTTAUTOMERIZATION_HPP
