/* 
 * RECAPFragmentGenerator.hpp 
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
 * \brief Definition of class CDPL::Chem::RECAPFragmentGenerator.
 */

#ifndef CDPL_CHEM_RECAPFRAGMENTGENERATOR_HPP
#define CDPL_CHEM_RECAPFRAGMENTGENERATOR_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentGenerator.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Molecular graph fragment generator implementing the \e RECAP bond-cleavage rule set.
         *
         * The rule (and exclude-pattern) set follows the original publication [\ref RECAP].
         * \e RECAP rule IDs are defined in namespace Chem::RECAPRuleID and the corresponding
         * atom label values in namespace Chem::RECAPAtomLabel.
         */
        class CDPL_CHEM_API RECAPFragmentGenerator : public FragmentGenerator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %RECAPFragmentGenerator instances.
             */
            typedef std::shared_ptr<RECAPFragmentGenerator> SharedPointer;

            /**
             * \brief Constructs the \c %RECAPFragmentGenerator instance and registers the corresponding \e RECAP fragmentation rules.
             */
            RECAPFragmentGenerator();
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RECAPFRAGMENTGENERATOR_HPP
