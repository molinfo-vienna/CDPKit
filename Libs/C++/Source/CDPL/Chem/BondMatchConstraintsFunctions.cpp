/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondMatchConstraintsFunctions.cpp 
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

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondProperty.hpp"


using namespace CDPL; 


const Chem::MatchConstraintList::SharedPointer& Chem::getMatchConstraints(const Bond& bond)
{
	static const MatchConstraintList::SharedPointer DEF_CONSTRAINTS(new MatchConstraintList());

    return bond.getPropertyOrDefault<MatchConstraintList::SharedPointer>(BondProperty::MATCH_CONSTRAINTS,
																		 DEF_CONSTRAINTS);
}

void Chem::setMatchConstraints(Bond& bond, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{	
	if (!overwrite && hasMatchConstraints(bond))
		return;

    bond.setProperty(BondProperty::MATCH_CONSTRAINTS, constr);
}

void Chem::clearMatchConstraints(Bond& bond)
{
    bond.removeProperty(BondProperty::MATCH_CONSTRAINTS);
}

bool Chem::hasMatchConstraints(const Bond& bond)
{
    return bond.isPropertySet(BondProperty::MATCH_CONSTRAINTS);
}
