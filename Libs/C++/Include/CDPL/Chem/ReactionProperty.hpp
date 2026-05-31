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
             * \brief Specifies the name of the reaction.
             *
             * \valuetype std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey NAME;

            /**
             * \brief Specifies a comment associated with the reaction.
             *
             * \valuetype std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey COMMENT;

            /**
             * \brief Specifies the timestamp of the reaction (typically the deposition or creation time).
             *
             * \valuetype std::time_t
             */
            extern CDPL_CHEM_API const Base::LookupKey TIMESTAMP;


            /**
             * \brief Specifies the match expression used for matching the reaction against query reactions.
             *
             * \valuetype Chem::MatchExpression<Chem::Reaction>::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;

            /**
             * \brief Specifies the matching constraints of the reaction.
             *
             * \valuetype Chem::MatchConstraintList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;

            /**
             * \brief Specifies the per-component groupings of the reaction's reactants and products.
             *
             * \valuetype Chem::FragmentList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUPS;

            /**
             * \brief Specifies the atom-to-atom mapping between the reactant and product molecules.
             *
             * \valuetype Chem::AtomMapping::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey ATOM_MAPPING;


            /**
             * \brief Specifies the (key, value) data block associated with the reaction (typically read from
             *        the data section of an MDL RD-File).
             *
             * \valuetype Chem::StringDataBlock::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey REACTION_DATA;


            /**
             * \brief Specifies the user initials field read from the MDL rxn file.
             *
             * \valuetype std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_USER_INITIALS;

            /**
             * \brief Specifies the program name field read from the MDL rxn file.
             *
             * \valuetype std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_PROGRAM_NAME;

            /**
             * \brief Specifies the MDL registry number of the reaction.
             *
             * \valuetype std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the embedded MDL molecule record associated with the reaction (the molecule
             *        following the reaction in an MDL RD-File).
             *
             * \valuetype Chem::Molecule::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_MOLECULE_RECORD;

            /**
             * \brief Specifies the MDL internal registry number string of the reaction.
             *
             * \valuetype std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_INTERNAL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the MDL external registry number string of the reaction.
             *
             * \valuetype std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_EXTERNAL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the version of the MDL rxn file the reaction was read from.
             *
             * \valuetype unsigned int
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_RXN_FILE_VERSION;
        } // namespace ReactionProperty
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_REACTIONPROPERTY_HPP
