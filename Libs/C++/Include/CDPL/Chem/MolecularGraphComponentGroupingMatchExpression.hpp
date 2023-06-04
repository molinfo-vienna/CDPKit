/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphComponentGroupingMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::ComponentGroupingMatchExpression.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHCOMPONENTGROUPINGMATCHEXPRESSION_HPP
#define CDPL_CHEM_MOLECULARGRAPHCOMPONENTGROUPINGMATCHEXPRESSION_HPP

#include <vector>
#include <mutex>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/FragmentList.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief MolecularGraphComponentGroupingMatchExpression.
		 * \see [\ref SMARTS]
		 */
		class CDPL_CHEM_API MolecularGraphComponentGroupingMatchExpression : public MatchExpression<MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %MolecularGraphComponentGroupingMatchExpression
			 *        instances.
			 */
			typedef boost::shared_ptr<MolecularGraphComponentGroupingMatchExpression> SharedPointer;

			/**
			 * \brief Constructs a \c %MolecularGraphComponentGroupingMatchExpression instance for the specified component-level grouping.
			 * \param comp_grouping Specifies the component-level grouping constraints that have to be fulfilled by matching target molecuar graphs.
			 */
			MolecularGraphComponentGroupingMatchExpression(const FragmentList::SharedPointer& comp_grouping);

			MolecularGraphComponentGroupingMatchExpression(const MolecularGraphComponentGroupingMatchExpression& rhs);

			/**
			 * \brief Checks whether the provided query to target atom/bond mapping candidate statisfies the component-level grouping constraints
			 *        specified in the constructor.
			 *
			 * Component-level grouping constraints are specified as a list of Chem::Fragment objects (see constructor argument
			 * \a comp_grouping). The expression evaluates to \c true only if for each of the specified fragments the provided
			 * query to target atom/bond mapping candidate is able to satisfy the following conditions: All query molecular graph atoms
			 * stored in a given Chem::Fragment object must map to atoms that are part of the same component of the target molecular
			 * graph. Query atoms in different Chem::Fragment objects must also map to atoms in different target molecular graph
			 * components. If the provided mapping candidate fails to fulfill one of these requirements, the expression evaluates
			 * to \c false.
			 *
			 * \param query_molgraph The query molecular graph (ignored).
			 * \param target_molgraph The target molecular graph.
			 * \param mapping The current query to target atom/bond mapping candidate.
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return \c true if the provided query to target atom mapping fulfills the component-level grouping constraints, and \c false
			 *         otherwise.
			 * \note If invalid component-level grouping constraints have been specified (\e null pointer or empty fragment list), the expression will always
			 *       evaluate to \c true.
			 */
			bool operator()(const MolecularGraph& query_molgraph, const MolecularGraph& target_molgraph, 
							const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			/**
			 * \brief Returns \c true to indicate that the expression requires a query to target atom/bond mapping candidate for its evaluation.
			 * \return \c true.
			 */
			bool requiresAtomBondMapping() const;

			MolecularGraphComponentGroupingMatchExpression& operator=(const MolecularGraphComponentGroupingMatchExpression& rhs);

		private:
			typedef std::vector<const Fragment*> ComponentList;

			FragmentList::SharedPointer compGrouping;
			mutable ComponentList       compList;
			mutable std::mutex          mutex;
		};
	}
}

#endif // CDPL_CHEM_MOLECULARGRAPHCOMPONENTGROUPINGMATCHEXPRESSION_HPP
