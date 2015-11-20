/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphElementalCompositionFunctions.cpp 
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

#include <map>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomTypeFunctions.hpp"


using namespace CDPL; 


void Chem::buildMolecularFormula(const MolecularGraph& molgraph, std::string& formula)
{
	typedef std::map<std::string, std::size_t> ElemCountMap;

	ElemCountMap elem_counts;
	std::size_t unknown_count = 0;
	std::size_t imp_h_count = 0;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		unsigned int atom_type = getType(atom);

		if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_ATOMIC_NO)
			unknown_count++;
		else
			elem_counts[getAtomTypeSymbol(atom_type)]++;

		imp_h_count += getImplicitHydrogenCount(atom);
	}

	elem_counts["H"] += imp_h_count;

	std::ostringstream formula_os;

	ElemCountMap::iterator it = elem_counts.find("C");

	if (it != elem_counts.end()) {
		formula_os << 'C';

		if (it->second > 1)
			formula_os << it->second;

		elem_counts.erase(it);

		it = elem_counts.find("H");

		if (it != elem_counts.end()) {
			formula_os << 'H';
			
			if (it->second > 1)
				formula_os << it->second;

			elem_counts.erase(it);
		}
	}

	for (ElemCountMap::const_iterator it = elem_counts.begin(), end = elem_counts.end(); it != end; ++it) {
		formula_os << it->first;

		if (it->second > 1)
			formula_os << boost::lexical_cast<std::string>(it->second);
	}

	if (unknown_count > 0)
		formula_os << '?';
	if (unknown_count > 1)
		formula_os << boost::lexical_cast<std::string>(unknown_count);

	formula.append(formula_os.str());
}

void Chem::buildElementHistogram(const MolecularGraph& molgraph, ElementHistogram& hist)
{
	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		unsigned int atom_type = getType(atom);

		if (atom_type > AtomType::MAX_ATOMIC_NO)
			atom_type = AtomType::UNKNOWN;

		hist[atom_type]++;
		hist[AtomType::H] += getImplicitHydrogenCount(atom);
	}
}
