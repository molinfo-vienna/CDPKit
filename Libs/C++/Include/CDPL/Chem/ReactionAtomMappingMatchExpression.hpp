/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionAtomMappingMatchExpression.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::ReactionAtomMappingMatchExpression.
 */

#ifndef CDPL_CHEM_REACTIONATOMMAPPINGMATCHEXPRESSION_HPP
#define CDPL_CHEM_REACTIONATOMMAPPINGMATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/AtomMapping.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Reaction;

		/**
		 * \addtogroup CDPL_CHEM_REACTION_MATCH_EXPRESSIONS
		 * @{
		 */

		/**
		 * \brief ReactionAtomMappingMatchExpression.
		 */
		class CDPL_CHEM_API ReactionAtomMappingMatchExpression : public MatchExpression<Reaction>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %ReactionAtomMappingMatchExpression
			 *        instances.
			 */
			typedef boost::shared_ptr<ReactionAtomMappingMatchExpression> SharedPointer;

			/**
			 * \brief Constructs a \c %ReactionAtomMappingMatchExpression instance for the specified reactant to product atom mapping.
			 * \param atom_mapping Specifies the reactant to product atom mapping constraint that has to be fulfilled by matching target
			 *                     reactions.
			 */
			ReactionAtomMappingMatchExpression(const AtomMapping::SharedPointer& atom_mapping);

			/**
			 * \brief Checks whether the reactant to product atom mapping of the target reaction matches the query atom mapping 
			 *        specified in the constructor.
			 *
			 * The query reactant to product atom mapping that was specified at construction time (see constructor) restricts the allowed
			 * correspondences between reactant and product atoms of the evaluated target reaction.
			 * The atom mapping of the target reaction is considered to match the query mapping only if each reactant/product atom pair
			 * of the query mapping matches a pair of target reactant/product atoms that belong to the same atom class (according to the target
			 * reaction's atom mapping retrieved from the property Chem::ReactionProperty::ATOM_MAPPING). If the mapping of a query reactant atom
			 * is not unique (i.e. maps to multiple product atoms of the same class), then the target reaction has to match only one of the specified
			 * mappings for that query atom.
			 *
			 * \param query_rxn The query reaction (ignored).
			 * \param target_rxn The checked target reaction.
			 * \param mapping The current query to target atom/bond mapping candidate.
			 * \param matched_rxn_roles Holds a bitwise OR combination of the flags defined in namespace Chem::ReactionRole specifying
			 *                          the reaction roles that were considered in the performed reaction substructure search.
			 * \return \c true if the reactant to product atom mapping of the target reaction matches the query atom mapping, and \c false
			 *         otherwise.
			 * \note If an invalid query reactant to product atom mapping has been specified (\e null pointer or empty mapping) or the reaction substructure
			 *       matching is incomplete (the RSSS did not consider both the reactants and products of the query reaction - see argument \a matched_rxn_roles),
			 *       the expression will evaluate to \c true.
			 */
			bool operator()(const Reaction& query_rxn, const Reaction& target_rxn,
							const AtomBondMapping& mapping, const Base::Variant& matched_rxn_roles) const;

			/**
			 * \brief Returns \c true to indicate that the expression requires a query to target atom/bond mapping candidate for its evaluation.
			 * \return \c true.
			 */
			bool requiresAtomBondMapping() const;

		private:
			AtomMapping::SharedPointer atomMapping;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_REACTIONATOMMAPPINGMATCHEXPRESSION_HPP
