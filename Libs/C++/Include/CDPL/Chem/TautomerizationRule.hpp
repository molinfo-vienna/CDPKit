/* 
 * TautomerizationRule.hpp 
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
 * \brief Definition of class CDPL::Chem::TautomerizationRule.
 */

#ifndef CDPL_CHEM_TAUTOMERIZATIONRULE_HPP
#define CDPL_CHEM_TAUTOMERIZATIONRULE_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Molecule;

        /**
         * \brief Abstract base class for all tautomerization rule implementations used by the Chem::TautomerGenerator.
         */
        class CDPL_CHEM_API TautomerizationRule
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TautomerizationRule instances.
             */
            typedef std::shared_ptr<TautomerizationRule> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~TautomerizationRule() {}

            /**
             * \brief Sets the parent molecular graph for which the rule is to enumerate tautomers.
             * \param parent_molgraph The molecular graph to be tautomerized.
             * \return \c true if the rule applies to \a parent_molgraph and the iteration has been initialized, and \c false otherwise.
             */
            virtual bool setup(MolecularGraph& parent_molgraph) = 0;

            /**
             * \brief Returns the rule's identifier (see Chem::TautomerizationType).
             * \return The rule identifier.
             */
            virtual unsigned int getID() const = 0;

            /**
             * \brief Generates the next tautomer.
             * \param tautomer The tautomer output molecule object.
             * \return \c true if a tautomer was generated, \c false if no more tautomers are available.
             */
            virtual bool generate(Molecule& tautomer) = 0;

            /**
             * \brief Returns a deep copy of this rule instance.
             * \return A shared pointer to the cloned rule.
             */
            virtual SharedPointer clone() const = 0;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_TAUTOMERIZATIONRULE_HPP
