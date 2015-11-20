/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondReactionCenterStatusMatchExpression.cpp
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


#include "StaticInit.hpp"

#include "CDPL/Chem/BondReactionCenterStatusMatchExpression.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"


using namespace CDPL;


Chem::BondReactionCenterStatusMatchExpression::BondReactionCenterStatusMatchExpression(unsigned int status): 
	rxnCtrStatus(status & (ReactionCenterStatus::NO_CENTER | ReactionCenterStatus::IS_CENTER | 
						   ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
						   ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::NO_CHANGE)) {}

bool Chem::BondReactionCenterStatusMatchExpression::operator()(const Bond&, const MolecularGraph&, 
															   const Bond& target_bond, const MolecularGraph&, 
															   const Base::Variant&) const
{
	unsigned int target_rxn_ctr_status = getReactionCenterStatus(target_bond);

	target_rxn_ctr_status &= (ReactionCenterStatus::NO_CENTER | ReactionCenterStatus::IS_CENTER | 
							  ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
							  ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::NO_CHANGE);

	switch (rxnCtrStatus) {

		case ReactionCenterStatus::NO_CENTER:
			return (target_rxn_ctr_status == ReactionCenterStatus::NO_CENTER || target_rxn_ctr_status == 0);

		case ReactionCenterStatus::IS_CENTER:
			return ((target_rxn_ctr_status & (ReactionCenterStatus::IS_CENTER | ReactionCenterStatus::BOND_MADE | 
											  ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::BOND_ORDER_CHANGE)) != 0);
	
		case ReactionCenterStatus::NO_CHANGE:
			return ((target_rxn_ctr_status & (ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
											  ReactionCenterStatus::BOND_ORDER_CHANGE)) == 0); 
		
		case ReactionCenterStatus::BOND_MADE:
		case ReactionCenterStatus::BOND_BROKEN:
		case ReactionCenterStatus::BOND_ORDER_CHANGE:
		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN:
		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_ORDER_CHANGE:
		case ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::BOND_ORDER_CHANGE:
		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::BOND_ORDER_CHANGE:
			return (rxnCtrStatus == 
					(target_rxn_ctr_status & (ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
											  ReactionCenterStatus::BOND_ORDER_CHANGE)));
		default:
			return true;
	}
}
