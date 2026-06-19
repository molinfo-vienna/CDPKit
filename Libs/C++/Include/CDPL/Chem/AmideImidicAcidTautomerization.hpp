/* 
 * AmideImidicAcidTautomerization.hpp 
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
 * \brief Definition of class CDPL::Chem::AmideImidicAcidTautomerization.
 */

#ifndef CDPL_CHEM_AMIDEIMIDICACIDTAUTOMERIZATION_HPP
#define CDPL_CHEM_AMIDEIMIDICACIDTAUTOMERIZATION_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/PatternBasedTautomerizationRule.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Implementation of the amide &harr; imidic-acid tautomerization rule.
         *
         * The rule is registered with TautomerizationType::AMIDE_IMIDIC_ACID and uses
         * PatternBasedTautomerizationRule to encode the match patterns and bond order
         * transformations required for the interconversion of amide and imidic-acid tautomers.
         */
        class CDPL_CHEM_API AmideImidicAcidTautomerization : public PatternBasedTautomerizationRule
        {

          public:
            /**
             * \brief Constructs the \c %AmideImidicAcidTautomerization instance and registers the
             *        match patterns and bond order changes of the rule.
             */
            AmideImidicAcidTautomerization();
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_AMIDEIMIDICACIDTAUTOMERIZATION_HPP
