/* 
 * ReactionProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::ReactionProperty.
 */

#ifndef CDPL_CHEM_REACTIONPROPERTY_HPP
#define CDPL_CHEM_REACTIONPROPERTY_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Chem
    {

        /**
         * \brief Provides keys for built-in Chem::Reaction properties.
         */
        namespace ReactionProperty
        {

            /**
             * \brief Specifies the name (or title) of the reaction.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey NAME;

            /**
             * \brief Specifies a free-text comment associated with the reaction.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey COMMENT;

            /**
             * \brief Specifies a creation/modification timestamp associated with the reaction.
             *
             * \valuetype std::time_t
             */
            extern CDPL_CHEM_API const Base::LookupKey TIMESTAMP;

            /**
             * \brief Specifies the match expression associated with the reaction.
             *
             * \valuetype Chem::MatchExpression<Chem::Reaction>::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;

            /**
             * \brief Specifies the substructure match constraints associated with the reaction.
             *
             * \valuetype Chem::MatchConstraintList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;

            /**
             * \brief Specifies the per-component groupings of the reaction's reactants and products for substructure searching.
             *
             * \valuetype Chem::FragmentList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUPS;

            /**
             * \brief Specifies the atom-to-atom mapping between the reactant and product molecules of the reaction.
             *
             * \valuetype Chem::AtomMapping::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey ATOM_MAPPING;

            /**
             * \brief Specifies the reaction data block associated with the reaction (typically read from/written to
             *        the data section of an <em>MDL RD-File</em>).
             *
             * \valuetype Chem::StringDataBlock::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey REACTION_DATA;

            /**
             * \brief Specifies the user initials stored in the <em>MDL Rxn-File</em> header.
             * \see [\ref CTFILE]
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_USER_INITIALS;

            /**
             * \brief Specifies the program name stored in the <em>MDL Rxn-File</em> header.
             * \see [\ref CTFILE]
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_PROGRAM_NAME;

            /**
             * \brief Specifies the \e MDL registry number of the reaction.
             * \see [\ref CTFILE]
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the embedded \e MDL molecule record associated with the reaction.
             * \see [\ref CTFILE]
             * \valuetype Chem::Molecule::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_MOLECULE_RECORD;

            /**
             * \brief Specifies the \e MDL internal registry number string of the reaction.
             * \see [\ref CTFILE]
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_INTERNAL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the \e MDL external registry number string of the reaction.
             * \see [\ref CTFILE]
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_EXTERNAL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the <em>MDL Rxn-File</em> version (see namespace Chem::MDLDataFormatVersion).
             * \see [\ref CTFILE]
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_RXN_FILE_VERSION;
        } // namespace ReactionProperty
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_REACTIONPROPERTY_HPP
