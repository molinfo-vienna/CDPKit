/* 
 * ReactionMatchConstraintsFunctions.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>
#include <functional>

#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"


using namespace CDPL; 


void Chem::setAtomMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite) 
{
	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  std::bind(static_cast<void (*)(MolecularGraph&, const MatchConstraintList::SharedPointer&,
												 bool)>(&setAtomMatchConstraints), std::placeholders::_1, std::ref(constr), overwrite));
}

void Chem::setBondMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{
	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  std::bind(static_cast<void (*)(MolecularGraph&, const MatchConstraintList::SharedPointer&,
												 bool)>(&setAtomMatchConstraints), std::placeholders::_1, std::ref(constr), overwrite));
}

void Chem::setComponentMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{
	for (Reaction::ComponentIterator it = rxn.getComponentsBegin(), end = rxn.getComponentsEnd(); it != end; ++it) {
		MolecularGraph& molgraph = *it;

		if (!overwrite && hasMatchConstraints(molgraph))
			continue;

		setMatchConstraints(molgraph, constr);
	}
}
