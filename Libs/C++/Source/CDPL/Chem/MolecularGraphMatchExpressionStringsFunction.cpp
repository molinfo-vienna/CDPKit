/* 
 * MolecularGraphMatchExpressionStringsFunction.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


void Chem::buildMatchExpressionStrings(MolecularGraph& molgraph, bool overwrite)
{
	std::string expr_str;

	MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
		Atom& atom = *a_it;
 
		if (!overwrite && hasMatchExpressionString(atom))
			continue;

		buildMatchExpressionString(atom, molgraph, expr_str);
		setMatchExpressionString(atom, expr_str);

		expr_str.clear();
	}

	MolecularGraph::BondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::BondIterator b_it = molgraph.getBondsBegin(); b_it != bonds_end; ++b_it) {
		Bond& bond = *b_it;
 
		if (!overwrite && hasMatchExpressionString(bond))
			continue;

		buildMatchExpressionString(bond, molgraph, expr_str);
		setMatchExpressionString(bond, expr_str);

		expr_str.clear();
	}
}
