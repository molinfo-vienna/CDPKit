/* 
 * BondReactionCenterStatusMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondReactionCenterStatusMatchExpression.
 */

#ifndef CDPL_CHEM_BONDREACTIONCENTERSTATUSMATCHEXPRESSION_HPP
#define CDPL_CHEM_BONDREACTIONCENTERSTATUSMATCHEXPRESSION_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Bond;
		class MolecularGraph;

		/**
		 * \brief BondReactionCenterStatusMatchExpression.
		 */
		class CDPL_CHEM_API BondReactionCenterStatusMatchExpression : public MatchExpression<Bond, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BondReactionCenterStatusMatchExpression
			 *        instances.
			 */
			typedef std::shared_ptr<BondReactionCenterStatusMatchExpression> SharedPointer;

			/**
			 * \brief Constructs a \c %BondReactionCenterStatusMatchExpression instance for the specified query reaction center status.
			 * \param status The query reaction center status as a (valid) bitwise OR combination of the flags defined in namespace Chem::ReactionCenterStatus.
			 *               The following flags are supported: Chem::ReactionCenterStatus::NO_CENTER, Chem::ReactionCenterStatus::IS_CENTER, 
			 *				 Chem::ReactionCenterStatus::BOND_MADE, Chem::ReactionCenterStatus::BOND_BROKEN, Chem::ReactionCenterStatus::BOND_ORDER_CHANGE 
			 *               and Chem::ReactionCenterStatus::NO_CHANGE - all other flags are ignored. For valid flag combinations see operator()().
			 */
			BondReactionCenterStatusMatchExpression(unsigned int status);

			/**
			 * \brief Checks whether the reaction center status of \a target_bond matches the query reaction center status
			 *        specified in the constructor.
			 *
			 * The following table lists all supported combinations of query reaction center status flags and the associated
			 * matching target reaction center states:
			 *
			 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
			 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
			 *   <th>Query %Reaction Center Status</th> <th>Matching Target %Reaction Center Status</th>
			 *  </tr>
			 *  <tr>
			 *   <td>None specified</td>
			 *   <td>Expression evaluates to \c true for any target reaction center status</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::ReactionCenterStatus::NO_CENTER</td>
			 *   <td>Chem::ReactionCenterStatus::NO_CENTER or Chem::ReactionCenterStatus::NONE</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::ReactionCenterStatus::IS_CENTER</td>
			 *   <td>At least one of the flags Chem::ReactionCenterStatus::IS_CENTER,<br>ReactionCenterStatus::BOND_MADE, 
			 *	     Chem::ReactionCenterStatus::BOND_BROKEN<br>or Chem::ReactionCenterStatus::BOND_ORDER_CHANGE must be set</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Chem::ReactionCenterStatus::NO_CHANGE</td>
			 *   <td>None of the flags ReactionCenterStatus::BOND_MADE,<br>Chem::ReactionCenterStatus::BOND_BROKEN and<br>
			 *       Chem::ReactionCenterStatus::BOND_ORDER_CHANGE must be set</td>
			 *  </tr>
			 *  <tr>
			 *   <td>Any combination of the flags Chem::ReactionCenterStatus::BOND_MADE,<br>Chem::ReactionCenterStatus::BOND_BROKEN
			 *       and<br>Chem::ReactionCenterStatus::BOND_ORDER_CHANGE</td>
			 *   <td>The same combination of flags must be set</td>
			 *  </tr>
			 * </table>
			 *
			 * \param query_bond The query bond (ignored).
			 * \param query_molgraph The molecular graph containing the query bond (ignored).
			 * \param target_bond The checked target bond.
			 * \param target_molgraph The molecular graph containing the target bond (ignored).
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return \c true if the reaction center status of the target bond matches the query reaction center status (see constructor),
			 *         and \c false otherwise.
			 * \note The reaction center status of \a target_bond is retrieved from the Chem::Bond property Chem::BondProperty::REACTION_CENTER_STATUS.
			 */
			bool operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, const Bond& target_bond, 
							const MolecularGraph& target_molgraph, const Base::Any& aux_data) const;

		private:
			unsigned int rxnCtrStatus;
		};
	}
}

#endif // CDPL_CHEM_BONDREACTIONCENTERSTATUSMATCHEXPRESSION_HPP
