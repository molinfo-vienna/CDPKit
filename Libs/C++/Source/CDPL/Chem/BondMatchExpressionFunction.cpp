/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondMatchExpressionFunction.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include "StaticInit.hpp"

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/ANDMatchExpressionList.hpp"
#include "CDPL/Chem/ORMatchExpressionList.hpp"
#include "CDPL/Chem/NOTMatchExpression.hpp"
#include "CDPL/Chem/BondConfigurationMatchExpression.hpp"
#include "CDPL/Chem/BondSubstituentDirectionMatchExpression.hpp"
#include "CDPL/Chem/BondDirectionMatchExpression.hpp"
#include "CDPL/Chem/BondReactionCenterStatusMatchExpression.hpp"
#include "CDPL/Chem/PropertyMatchExpression.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"


using namespace CDPL; 


namespace
{

	template <typename ValueType>
	struct SingleArgPropertyFuncWrapper
	{

		SingleArgPropertyFuncWrapper(ValueType (*func)(const Chem::Bond&)): func(func) {}

		ValueType operator()(const Chem::Bond& bond, const Chem::MolecularGraph&) const {
			return func(bond);
		}

		ValueType (*func)(const Chem::Bond&);
	};

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer
	createOrderMatchExpression(const Chem::Bond& bond, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		std::size_t order = 0;
		bool order_valid = false;

		if (!constraint.hasValue()) {
			bool aromatic_bond = getAromaticityFlag(bond);
			order = getOrder(bond);

			if (aromatic_bond) {

				switch (order) {

					case 1:
						order = BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC;
						order_valid = true;
						break;

					case 2:
						order = BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC;
						order_valid = true;
						break;

					case 3:
						order = BondMatchConstraint::TRIPLE | BondMatchConstraint::AROMATIC;
						order_valid = true;

					default:
						break;
				}
			}

		} else {
			order = constraint.getValue<unsigned int>();

			if (order == BondMatchConstraint::IGNORE_AROMATICITY) {
				order = getOrder(bond);

			} else
				order_valid = true;
		}

		if (!order_valid)
			switch (order) {
		
				case 1:
					order = BondMatchConstraint::SINGLE;
					break;

				case 2:
					order = BondMatchConstraint::DOUBLE;
					break;

				case 3:
					order = BondMatchConstraint::TRIPLE;
					
				default:
					break;	
			}

		MatchExpressionList<Bond, MolecularGraph>::SharedPointer expr_list_ptr(new ORMatchExpressionList<Bond, MolecularGraph>());

		if ((order & BondMatchConstraint::SINGLE) != 0)
			expr_list_ptr->addElement(MatchExpression<Bond, MolecularGraph>::SharedPointer(new PropertyMatchExpression<std::size_t, 
																						   std::equal_to<std::size_t>, Bond, 
																						   MolecularGraph>(1, SingleArgPropertyFuncWrapper<std::size_t>(&getOrder))));

		if ((order & BondMatchConstraint::DOUBLE) != 0)
			expr_list_ptr->addElement(MatchExpression<Bond, MolecularGraph>::SharedPointer(new PropertyMatchExpression<std::size_t, 
																						   std::equal_to<std::size_t>, Bond, 
																						   MolecularGraph>(2, SingleArgPropertyFuncWrapper<std::size_t>(&getOrder))));

		if ((order & BondMatchConstraint::TRIPLE) != 0)
			expr_list_ptr->addElement(MatchExpression<Bond, MolecularGraph>::SharedPointer(new PropertyMatchExpression<std::size_t, 
																						   std::equal_to<std::size_t>, Bond, 
																						   MolecularGraph>(3, SingleArgPropertyFuncWrapper<std::size_t>(&getOrder))));

		if ((order & BondMatchConstraint::AROMATIC) != 0)
			expr_list_ptr->addElement(MatchExpression<Bond, MolecularGraph>::SharedPointer(new PropertyMatchExpression<bool, 
																						   std::equal_to<bool>, Bond, 
																						   MolecularGraph>(true, SingleArgPropertyFuncWrapper<bool>(&getAromaticityFlag))));

		MatchExpression<Bond, MolecularGraph>::SharedPointer expr_ptr;
	
		if (expr_list_ptr->getSize() == 0)
			return expr_ptr;

		if (expr_list_ptr->getSize() == 1)
			expr_ptr = expr_list_ptr->getBase().getFirstElement();
		else
			expr_ptr = expr_list_ptr;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			expr_ptr.reset(new NOTMatchExpression<Bond, MolecularGraph>(expr_ptr));
	
		return expr_ptr;
	}

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer
	createConfigurationMatchExpression(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph,
									   const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		if (!constraint.hasValue()) {
			const StereoDescriptor& stereo_descr = calcStereoDescriptor(bond, molgraph, 0);

			if ((stereo_descr.getConfiguration() & (BondConfiguration::CIS | BondConfiguration::TRANS)) == 0)
				return MatchExpression<Bond, MolecularGraph>::SharedPointer();

			return MatchExpression<Bond, MolecularGraph>::SharedPointer(new BondConfigurationMatchExpression(stereo_descr, bond,
																											 constraint.getRelation() == 
																											 MatchConstraint::NOT_EQUAL, true));
		} else {
			const StereoDescriptor& stereo_descr = constraint.getValue<StereoDescriptor>();

			if ((stereo_descr.getConfiguration() & (BondConfiguration::NONE | BondConfiguration::CIS | BondConfiguration::TRANS | BondConfiguration::EITHER)) == 0)
				return MatchExpression<Bond, MolecularGraph>::SharedPointer();

			return MatchExpression<Bond, MolecularGraph>::SharedPointer(new BondConfigurationMatchExpression(stereo_descr, bond,
																											 constraint.getRelation() == 
																											 MatchConstraint::NOT_EQUAL, true));
		}
	}

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer
	createDirectionConfigMatchExpression(const Chem::Bond& bond, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		return MatchExpression<Bond, MolecularGraph>::SharedPointer(new BondSubstituentDirectionMatchExpression());
	}

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer
	createDirectionMatchExpression(const Chem::Bond& bond, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		unsigned int dir;

		if (!constraint.hasValue()) {
			dir = getDirection(bond);

			if (dir == BondDirection::NONE)
				return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		} else
			dir = constraint.getValue<unsigned int>();

		dir &= (BondDirection::UP | BondDirection::DOWN | BondDirection::UNSPECIFIED);

		if (dir == 0)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		return MatchExpression<Bond, MolecularGraph>::SharedPointer(new BondDirectionMatchExpression(dir, constraint.getRelation() == 
																									 MatchConstraint::NOT_EQUAL));
	}

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer
	createRxnCenterStatusMatchExpression(const Chem::Bond& bond, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		unsigned int rxn_status;

		if (!constraint.hasValue()) {
			rxn_status = getReactionCenterStatus(bond);

		} else
			rxn_status = constraint.getValue<unsigned int>();

		rxn_status &= (ReactionCenterStatus::NO_CENTER | ReactionCenterStatus::IS_CENTER | 
					   ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
					   ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::NO_CHANGE);

		if (rxn_status == 0)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		return MatchExpression<Bond, MolecularGraph>::SharedPointer(new BondReactionCenterStatusMatchExpression(rxn_status));
	}

	template <typename PropertyFunc>
	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer 
	createBooleanPropertyMatchExpression(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, 
										 const Chem::MatchConstraint& constraint, const PropertyFunc& func)
	{
		using namespace Chem;

		MatchExpression<Bond, MolecularGraph>::SharedPointer expr_ptr;

		bool not_match = false;

		switch (constraint.getRelation()) {

			case MatchConstraint::EQUAL: 
				break;
		
			case MatchConstraint::NOT_EQUAL:
				not_match = true;
				break;
	
			default:
				return expr_ptr;
		} 

		if (!constraint.hasValue()) {
			if (not_match)
				expr_ptr.reset(new PropertyMatchExpression<bool, std::not_equal_to<bool>, Bond, MolecularGraph>(func(bond, molgraph), func));
			else
				expr_ptr.reset(new PropertyMatchExpression<bool, std::equal_to<bool>, Bond, MolecularGraph>(func(bond, molgraph), func));

		} else {
			bool value = constraint.getValue<bool>();

			if (not_match)
				expr_ptr.reset(new PropertyMatchExpression<bool, std::not_equal_to<bool>, Bond, MolecularGraph>(value, func));
			else
				expr_ptr.reset(new PropertyMatchExpression<bool, std::equal_to<bool>, Bond, MolecularGraph>(value, func));
		}

		return expr_ptr;
	}

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer 
	createMatchExpression(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, const Chem::MatchConstraintList& constr_list);

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer 
	createMatchExpressionList(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Bond, MolecularGraph>::SharedPointer();

		const MatchConstraintList& constr_list = 
			*constraint.getValue<MatchConstraintList::SharedPointer>();

		MatchExpression<Bond, MolecularGraph>::SharedPointer expr_ptr = createMatchExpression(bond, molgraph, constr_list);

		if (!expr_ptr)
			return expr_ptr;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			expr_ptr.reset(new NOTMatchExpression<Bond, MolecularGraph>(expr_ptr));

		return expr_ptr;
	}

	Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer 
	createMatchExpression(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, const Chem::MatchConstraintList& constr_list)
	{
		using namespace Chem;

		MatchExpressionList<Bond, MolecularGraph>::SharedPointer expr_list_ptr;

		if (constr_list.getType() == MatchConstraintList::AND_LIST || 
			constr_list.getType() == MatchConstraintList::NOT_AND_LIST)
			expr_list_ptr.reset(new ANDMatchExpressionList<Bond, MolecularGraph>());
		else
			expr_list_ptr.reset(new ORMatchExpressionList<Bond, MolecularGraph>());

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			MatchExpression<Bond, MolecularGraph>::SharedPointer expr_ptr;

			switch (constraint.getID()) {
						
				case BondMatchConstraint::CONSTRAINT_LIST:
					expr_ptr = createMatchExpressionList(bond, molgraph, constraint);
					break;

				case BondMatchConstraint::ORDER:
					expr_ptr = createOrderMatchExpression(bond, constraint);
					break;		

				case BondMatchConstraint::AROMATICITY:
					expr_ptr = createBooleanPropertyMatchExpression(bond, molgraph, constraint, SingleArgPropertyFuncWrapper<bool>(&getAromaticityFlag));
					break;		

				case BondMatchConstraint::RING_TOPOLOGY:
					expr_ptr = createBooleanPropertyMatchExpression(bond, molgraph, constraint, SingleArgPropertyFuncWrapper<bool>(&getRingFlag));
					break;

				case BondMatchConstraint::CONFIGURATION:
					expr_ptr = createConfigurationMatchExpression(bond, molgraph, constraint);
					break;		

				case BondMatchConstraint::DIRECTION_CONFIG:
					expr_ptr = createDirectionConfigMatchExpression(bond, constraint);
					break;		

				case BondMatchConstraint::REACTION_CENTER_STATUS:
					expr_ptr = createRxnCenterStatusMatchExpression(bond, constraint);
					break;		

				case BondMatchConstraint::DIRECTION:
					expr_ptr = createDirectionMatchExpression(bond, constraint);
					break;		

				default:
					continue;
			}

			if (expr_ptr)
				expr_list_ptr->addElement(expr_ptr);
		}

		MatchExpression<Bond, MolecularGraph>::SharedPointer expr_ptr;
	
		if (expr_list_ptr->getSize() == 0)
			return expr_ptr;

		if (expr_list_ptr->getSize() == 1)
			expr_ptr = expr_list_ptr->getBase().getFirstElement();
		else
			expr_ptr = expr_list_ptr;

		if (constr_list.getType() == MatchConstraintList::NOT_AND_LIST || 
			constr_list.getType() == MatchConstraintList::NOT_OR_LIST) 
			expr_ptr.reset(new NOTMatchExpression<Bond, MolecularGraph>(expr_ptr));
	
		return expr_ptr;
	}
}


Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer Chem::buildMatchExpression(const Bond& bond, const MolecularGraph& molgraph)
{
	MatchExpression<Bond, MolecularGraph>::SharedPointer expr_ptr = createMatchExpression(bond, molgraph, *getMatchConstraints(bond));

	if (!expr_ptr)
		expr_ptr.reset(new MatchExpression<Bond, MolecularGraph>());

	return expr_ptr; 
}
