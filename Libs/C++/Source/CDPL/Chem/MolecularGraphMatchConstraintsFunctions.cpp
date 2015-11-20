/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphMatchConstraintsFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"


using namespace CDPL; 


const Chem::MatchConstraintList::SharedPointer& Chem::getMatchConstraints(const MolecularGraph& molgraph)
{
    static const MatchConstraintList::SharedPointer DEF_CONSTRAINTS(new MatchConstraintList());

    return molgraph.getPropertyOrDefault<MatchConstraintList::SharedPointer>(MolecularGraphProperty::MATCH_CONSTRAINTS,
																			 DEF_CONSTRAINTS);
}

void Chem::setMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr, bool overwrite)
{
	if (overwrite || !hasMatchConstraints(molgraph))
		molgraph.setProperty(MolecularGraphProperty::MATCH_CONSTRAINTS, constr);
}

void Chem::clearMatchConstraints(MolecularGraph& molgraph)
{
    molgraph.removeProperty(MolecularGraphProperty::MATCH_CONSTRAINTS);
}

bool Chem::hasMatchConstraints(const MolecularGraph& molgraph)
{
    return molgraph.isPropertySet(MolecularGraphProperty::MATCH_CONSTRAINTS);
}

void Chem::setAtomMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr, 
								   bool overwrite)
{
	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
				  boost::bind(static_cast<void (*)(Atom&, const MatchConstraintList::SharedPointer&,
												   bool)>(&setMatchConstraints), _1, boost::ref(constr), overwrite));
}

void Chem::setBondMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr, 
								   bool overwrite)
{
	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
				  boost::bind(static_cast<void (*)(Bond&, const MatchConstraintList::SharedPointer&,
												   bool)>(&setMatchConstraints), _1, boost::ref(constr), overwrite));
}
