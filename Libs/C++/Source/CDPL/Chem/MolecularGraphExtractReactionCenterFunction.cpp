/* 
 * MolecularGraphExtractReactionCenterFunction.cpp 
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
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"


using namespace CDPL; 


void Chem::extractReactionCenter(const MolecularGraph& molgraph, Fragment& rxn_center)
{
	using namespace ReactionCenterStatus;

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
		unsigned int rxn_ctr_info = getReactionCenterStatus(bond);

		if (rxn_ctr_info != NO_CENTER && (rxn_ctr_info & (IS_CENTER | BOND_MADE | BOND_BROKEN | BOND_ORDER_CHANGE)) != 0)
			rxn_center.addBond(bond);
	}

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		unsigned int rxn_ctr_info = getReactionCenterStatus(atom);

		if (rxn_ctr_info != NO_CENTER && (rxn_ctr_info & (EXACT_CHANGE | STEREO_INVERSION | STEREO_RETENTION)) != 0) 
			rxn_center.addAtom(atom);
	}
}
