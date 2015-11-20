/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AromaticityPerception.cpp 
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

#include "AromaticityPerception.hpp"

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


bool Chem::isAromatic(const MolecularGraph& molgraph, const Fragment& ring, const Util::BitSet& arom_bond_mask)
{
	std::size_t num_pi_electrons = 0;

	Fragment::ConstAtomIterator atoms_end = ring.getAtomsEnd();

	for (Fragment::ConstAtomIterator a_it = ring.getAtomsBegin(); a_it != atoms_end; ++a_it) {
		const Atom& atom = *a_it;

		std::size_t num_single_bonds = 0;
		std::size_t num_ring_double_bonds = 0;
		std::size_t num_exo_double_bonds = 0;
		std::size_t num_arom_bonds = 0;
		std::size_t num_bonds = 0;

		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it2 = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it2) {
			const Bond& bond = *b_it;

			if (!(molgraph.containsAtom(*a_it2) && molgraph.containsBond(bond)))
				continue;

			bool in_ring = ring.containsBond(bond);

			switch (getOrder(bond)) {

				case 1:
					num_single_bonds++;
					break;

				case 2:
					if (in_ring)
						num_ring_double_bonds++;
					else
						num_exo_double_bonds++;

					break;

				default:
					return false;
			}

			num_bonds++;

			if (arom_bond_mask.test(molgraph.getBondIndex(bond))) 
				num_arom_bonds++;
		}

		std::size_t impl_h_count = getImplicitHydrogenCount(atom);

		num_bonds += impl_h_count;
		num_single_bonds += impl_h_count;

		unsigned int atom_type = getType(atom);
		long charge = getFormalCharge(atom);

		switch (atom_type) {

			case AtomType::C:
			case AtomType::Si:
			case AtomType::Sn:
				switch (num_bonds) {
					/*
					case 2:
						if (num_single_bonds == 2) {
							if (charge == 0)
								continue;

							if (charge == -1) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (num_ring_double_bonds == 1 && charge == 0) {
							num_pi_electrons++;
							continue;
						}

						return false;
					*/
					case 3:
						if (num_single_bonds == 3) {
							if (charge == 1)
								continue;

							if (charge == -1) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (charge != 0)
							return false;

						if (num_single_bonds == 2 &&
							(num_ring_double_bonds == 1 || (num_arom_bonds > 0 && num_exo_double_bonds == 1))) {
							num_pi_electrons++;
							continue;
						}

					default:
						return false;
				}

				return false;

			case AtomType::N:
			case AtomType::P:
			case AtomType::As:
				switch (num_bonds) {

					case 2:
						if (num_single_bonds == 2) {
							if (charge == -1) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (num_ring_double_bonds == 1 && (charge == 0 || charge == 1)) {
							num_pi_electrons++;
							continue;
						}

						return false;

					case 3:
						if (num_single_bonds == 3) {
							if (charge == 0) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (charge != 1)
							return false;

						if (num_single_bonds == 2 && 
							(num_ring_double_bonds == 1 || (num_arom_bonds > 0 && num_exo_double_bonds == 1))) {
							num_pi_electrons++;
							continue;
						}

					default:
						return false;
				}

				return false;

			case AtomType::O:
			case AtomType::S:
			case AtomType::Se:
				if (num_bonds == 2 && num_single_bonds == 2 && charge == 0) {
					num_pi_electrons += 2;
					continue;	
				}

			default:
				return false;
		}
	}

	return ((num_pi_electrons & 0x3) == 2);
}

bool Chem::isNotAromatic(const MolecularGraph& molgraph, const Fragment& ring)
{
	Fragment::ConstAtomIterator atoms_end = ring.getAtomsEnd();

	for (Fragment::ConstAtomIterator a_it = ring.getAtomsBegin(); a_it != atoms_end; ++a_it) {
		const Atom& atom = *a_it;

		std::size_t num_single_bonds = 0;
		std::size_t num_double_bonds = 0;
		std::size_t num_bonds = 0;

		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it2 = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it2) {
			const Bond& bond = *b_it;

			if (!(molgraph.containsAtom(*a_it2) && molgraph.containsBond(bond)))
				continue;

			switch (getOrder(bond)) {

				case 1:
					num_single_bonds++;
					break;

				case 2:
					num_double_bonds++;
					break;

				default:
					return false;
			}

			num_bonds++;
		}

		std::size_t impl_h_count = getImplicitHydrogenCount(atom);

		num_bonds += impl_h_count;
		num_single_bonds += impl_h_count;

		unsigned int atom_type = getType(atom);
		long charge = getFormalCharge(atom);

		switch (atom_type) {

			case AtomType::C:
			case AtomType::Si:
			case AtomType::Sn:
				switch (num_bonds) {
					/*
					case 2:
						if (num_single_bonds == 2) {
							if (charge == 1 || charge == -1)
								continue;

							return true;
						}

						if (num_double_bonds == 1 && charge == 0)
							continue;

						return true;
					*/
					case 3:
						if (num_single_bonds == 3) {
							if (charge == 1 || charge == -1)
								continue;

							return true;
						}

						if (charge != 0)
							return true;

						if (num_single_bonds == 2 && num_double_bonds == 1)
							continue;

					default:
						return true;
				}

				return true;

			case AtomType::N:
			case AtomType::P:
			case AtomType::As:
				switch (num_bonds) {

					case 2:
						if (num_single_bonds == 2) {
							if (charge == -1)
								continue;

							return true;
						}

						if (num_double_bonds == 1 && (charge == 0 || charge == 1)) 
							continue;

						return true;

					case 3:
						if (num_single_bonds == 3) {
							if (charge == 0) 
								continue;

							return true;
						}

						if (charge != 1)
							return true;

						if (num_single_bonds == 2 && num_double_bonds == 1)
							continue;

					default:
						return true;
				}

				return false;

			case AtomType::O:
			case AtomType::S:
			case AtomType::Se:
				if (num_bonds == 2 && num_single_bonds == 2 && charge == 0)
					continue;	

			default:
				return true;
		}
	}

	return false;
}
