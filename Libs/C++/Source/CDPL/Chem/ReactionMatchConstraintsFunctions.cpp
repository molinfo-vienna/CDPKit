/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionMatchConstraintsFunctions.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionProperty.hpp"


using namespace CDPL; 


namespace
{

    const Chem::MatchConstraintList::SharedPointer DEF_CONSTRAINTS(new Chem::MatchConstraintList());	
}


const Chem::MatchConstraintList::SharedPointer& Chem::getMatchConstraints(const Reaction& rxn)
{
    return rxn.getPropertyOrDefault<MatchConstraintList::SharedPointer>(ReactionProperty::MATCH_CONSTRAINTS,
																		DEF_CONSTRAINTS);
}

void Chem::setMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{
	if (!overwrite && hasMatchConstraints(rxn))
		return;

	rxn.setProperty(ReactionProperty::MATCH_CONSTRAINTS, constr);
}

void Chem::clearMatchConstraints(Reaction& rxn)
{
    rxn.removeProperty(ReactionProperty::MATCH_CONSTRAINTS);
}

bool Chem::hasMatchConstraints(const Reaction& rxn)
{
    return rxn.isPropertySet(ReactionProperty::MATCH_CONSTRAINTS);
}

void Chem::setAtomMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite) 
{
	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  boost::bind(static_cast<void (*)(MolecularGraph&, const MatchConstraintList::SharedPointer&,
												   bool)>(&setAtomMatchConstraints), _1, boost::ref(constr), overwrite));
}

void Chem::setBondMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{
	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  boost::bind(static_cast<void (*)(MolecularGraph&, const MatchConstraintList::SharedPointer&,
												   bool)>(&setAtomMatchConstraints), _1, boost::ref(constr), overwrite));
}

void Chem::setComponentMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{
	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  boost::bind(static_cast<void (*)(MolecularGraph&, const MatchConstraintList::SharedPointer&,
												   bool)>(&setMatchConstraints), _1, boost::ref(constr), overwrite));
}
