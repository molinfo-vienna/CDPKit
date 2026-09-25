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
 * \brief Definition of class CDPL::Chem::ComponentGroupingMatchExpression.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHCOMPONENTGROUPINGMATCHEXPRESSION_HPP
#define CDPL_CHEM_MOLECULARGRAPHCOMPONENTGROUPINGMATCHEXPRESSION_HPP

#include <vector>
#include <mutex>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/FragmentList.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Chem::MatchExpression implementation that constrains the substructure mapping by the query's component-level groupings.
         *
         * Required component groupings are passed as a Chem::FragmentList instance: query atoms inside the same fragment must
         * map to a single target component, and query atoms in different fragments must map to different target
         * components.
         * Component groupings are typically specified via parenthesization of dot-separated <em>Daylight SMARTS</em> pattern sequences [\ref SMARTS].
         */
        class CDPL_CHEM_API MolecularGraphComponentGroupingMatchExpression : public MatchExpression<MolecularGraph>
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MolecularGraphComponentGroupingMatchExpression
             *        instances.
             */
            typedef std::shared_ptr<MolecularGraphComponentGroupingMatchExpression> SharedPointer;

            /**
             * \brief Constructs the \c %MolecularGraphComponentGroupingMatchExpression instance for the specified component-level grouping.
             * \param comp_grouping Specifies the component-level grouping constraints that have to be fulfilled by matching target molecular graphs.
             */
            MolecularGraphComponentGroupingMatchExpression(const FragmentList::SharedPointer& comp_grouping);

            /**
             * \brief Constructs a copy of the \c %MolecularGraphComponentGroupingMatchExpression instance \a rhs.
             * \param rhs The expression to copy.
             */
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
             * \param query_molgraph The query molecular graph.
             * \param target_molgraph The target molecular graph.
             * \param mapping The current query to target atom/bond mapping candidate.
             * \param aux_data Auxiliary information for expression evaluation (ignored).
             * \return \c true if the provided query to target atom mapping fulfills the component-level grouping constraints, and \c false
             *         otherwise.
             * \note If invalid component-level grouping constraints have been specified (\c nullptr or empty fragment list), the expression will always
             *       evaluate to \c true.
             */
            bool operator()(const MolecularGraph& query_molgraph, const MolecularGraph& target_molgraph,
                            const AtomBondMapping& mapping, const Base::Any& aux_data) const;

            /**
             * \brief Returns \c true to indicate that the expression requires a query to target atom/bond mapping candidate for its evaluation.
             * \return \c true.
             */
            bool requiresAtomBondMapping() const;

            /**
             * \brief Replaces the current component-level grouping constraints with the ones of the expression \a rhs.
             * \param rhs The expression to copy from.
             * \return A reference to itself.
             */
            MolecularGraphComponentGroupingMatchExpression& operator=(const MolecularGraphComponentGroupingMatchExpression& rhs);

          private:
            typedef std::vector<const Fragment*> ComponentList;

            FragmentList::SharedPointer compGrouping;
            mutable ComponentList       compList;
            mutable std::mutex          mutex;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPHCOMPONENTGROUPINGMATCHEXPRESSION_HPP
