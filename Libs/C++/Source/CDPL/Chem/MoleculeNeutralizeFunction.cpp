/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeNeutralizeFunction.cpp 
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

#include <algorithm>
#include <cmath>
#include <vector>

#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

	typedef std::vector<const Chem::Atom*> AtomList;

    std::size_t calcFreeValence(const Chem::Atom& atom)
    {
		using namespace Chem;

		std::size_t heavy_val = 0;
		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) 
			if (getType(*a_it) != AtomType::H)
				heavy_val += getOrder(*b_it);
		
		const Util::STArray& val_states = AtomDictionary::getValenceStates(getType(atom));

		for (std::size_t i = 0, num_states = val_states.size(); i < num_states; i++)
			if (val_states[i] > heavy_val)
				return (val_states[i] - heavy_val);
		
		return 0;
    }

	long calcNetCharge(const Chem::Atom& atom)
	{
		using namespace Chem;

		long net_charge = getFormalCharge(atom);

		if (net_charge == 0)
			return 0;

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end && net_charge != 0; ++a_it) {
			long nbr_charge = getFormalCharge(*a_it);

			if (net_charge > 0) {
				if (nbr_charge >= 0)
					continue;

				net_charge = std::max(net_charge + nbr_charge, long(0));

			} else {
				if (nbr_charge <= 0)
					continue;
				
				net_charge = std::min(net_charge + nbr_charge, long(0));
			}
		}

		return net_charge;
	}

	std::size_t removeHydrogens(const Chem::Atom& atom, std::size_t count, AtomList& rem_hs)
	{
		using namespace Chem;

		std::size_t rem_count = 0;
		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end && rem_count < count; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;

			if (nbr_atom.getNumBonds() != 1)
				continue;

			if (getType(nbr_atom) != AtomType::H)
				continue;

			if (getOrder(*b_it) != 1)
				continue;

			rem_hs.push_back(&nbr_atom);
			rem_count++;
		}

		return rem_count;
	}

	std::size_t calcValenceExcess(const Chem::Atom& atom)
	{
		using namespace Chem;

		std::size_t exp_val = Internal::calcExplicitValence(atom, atom.getMolecule());
		const Util::STArray& val_states = AtomDictionary::getValenceStates(getType(atom));
		std::size_t max_val = 0;

		for (std::size_t i = 0, num_states = val_states.size(); i < num_states; i++)
			max_val = std::max(max_val, val_states[i]);

		if (max_val >= exp_val)
			return 0;

		return (exp_val - max_val);
	}
}


bool Chem::neutralize(Molecule& mol)
{
    bool changes = false;

    for (Molecule::BondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) {
		Bond& bond = *it;
		Atom& atom1 = bond.getBegin();
		Atom& atom2 = bond.getEnd();

		long charge1 = getFormalCharge(atom1);
		long charge2 = getFormalCharge(atom2);

		if ((charge1 <= 0 && charge2 <=0) || (charge1 >= 0 && charge2 >= 0))
			continue;
	
		long comp = std::min(std::abs(charge1), std::abs(charge2));
		long order = getOrder(bond);

		comp = std::min(3 - order, comp);
		comp = std::min(long(std::min(calcFreeValence(atom1), calcFreeValence(atom2))), comp);
	
		if (comp <= 0)
			continue;

		setOrder(bond, order + comp);

		if (charge1 < 0)
			setFormalCharge(atom1, charge1 + comp);
		else
			setFormalCharge(atom1, charge1 - comp);	    

		if (charge2 < 0)
			setFormalCharge(atom2, charge2 + comp);
		else
			setFormalCharge(atom2, charge2 - comp);	    

		changes = true;
    }

	AtomList rem_hs;

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;
		long net_charge = calcNetCharge(atom);

		if (net_charge == 0)
			continue;

		std::size_t val_xcs = calcValenceExcess(atom);

		if (val_xcs == 0) {
			setFormalCharge(atom, getFormalCharge(atom) - net_charge);
			changes = true;
			continue;
		}

		std::size_t num_rem_hs = removeHydrogens(atom, val_xcs, rem_hs);

		if (num_rem_hs == 0)
			continue;

		if (net_charge < 0)
			setFormalCharge(atom, getFormalCharge(atom) + num_rem_hs);
		else
			setFormalCharge(atom, getFormalCharge(atom) - num_rem_hs);

		changes = true;
	}

	for (AtomList::const_iterator it = rem_hs.begin(), end = rem_hs.end(); it != end; ++it)
		mol.removeAtom(mol.getAtomIndex(**it));

	if (!rem_hs.empty())
		changes = true;

    return changes;
}
