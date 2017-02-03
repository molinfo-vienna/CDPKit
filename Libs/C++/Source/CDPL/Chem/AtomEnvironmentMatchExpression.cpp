/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomEnvironmentMatchExpression.cpp
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

#include "CDPL/Chem/AtomEnvironmentMatchExpression.hpp"


using namespace CDPL;


Chem::AtomEnvironmentMatchExpression::AtomEnvironmentMatchExpression(const MolecularGraph::SharedPointer& env_pattern, 
																	 bool not_match): 
	envPattern(env_pattern), notMatch(not_match) 
{
	if (env_pattern.get())
		substructSearch.setQuery(*env_pattern); 
} 

bool Chem::AtomEnvironmentMatchExpression::operator()(const Atom&, const MolecularGraph&, 
													  const Atom& target_atom, const MolecularGraph& target_molgraph, 
													  const Base::Variant&) const
{
	if (!envPattern || envPattern->getNumAtoms() == 0)
		return true;

	boost::lock_guard<boost::mutex> lock(mutex);

	substructSearch.clearAtomMappingConstraints();
	substructSearch.addAtomMappingConstraint(0, target_molgraph.getAtomIndex(target_atom));

	bool match = substructSearch.mappingExists(target_molgraph);

	if (notMatch)
		return !match;

	return match;
}
