/* 
 * BRICSFragmentGenerator.hpp 
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
 * \brief Definition of class CDPL::Chem::BRICSFragmentGenerator.
 */

#ifndef CDPL_CHEM_BRICSFRAGMENTGENERATOR_HPP
#define CDPL_CHEM_BRICSFRAGMENTGENERATOR_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentGenerator.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Chem::FragmentGenerator preconfigured with the 16 <em>BRICS</em> bond-cleavage rules and the associated
         *        exclude patterns for combinatorial fragmentation of organic molecules.
         *
         * The rule and exclude-pattern set follows the original <em>Breaking of Retrosynthetically Interesting Chemical
         * Substructures</em> publication. Each rule has the corresponding Chem::BRICSRuleID value.
         *
         * \see [\ref BRICS]
         */
        class CDPL_CHEM_API BRICSFragmentGenerator : public FragmentGenerator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BRICSFragmentGenerator instances.
             */
            typedef std::shared_ptr<BRICSFragmentGenerator> SharedPointer;

            /**
             * \brief Constructs the \c %BRICSFragmentGenerator instance with the full BRICS rule and exclude-pattern set registered.
             */
            BRICSFragmentGenerator();
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BRICSFRAGMENTGENERATOR_HPP
