/* 
 * CompleteRingSetTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <set>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/CompleteRingSet.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"


namespace
{

	std::size_t getUniqueAtomCount(const CDPL::Chem::FragmentList& frag_list)
	{
		using namespace CDPL;
		using namespace Chem;

		std::set<const Atom*> atoms;

		for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), end = frag_list.getElementsEnd(); it != end; ++it) {
			const Fragment& frag = *it;

			for (Fragment::ConstAtomIterator a_it = frag.getAtomsBegin(), a_end = frag.getAtomsEnd(); a_it != a_end; ++a_it)
				atoms.insert(&*a_it);
		}

		return atoms.size();
	}

	std::size_t getUniqueBondCount(const CDPL::Chem::FragmentList& frag_list)
	{
		using namespace CDPL;
		using namespace Chem;

		std::set<const Bond*> bonds;

		for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), end = frag_list.getElementsEnd(); it != end; ++it) {
			const Fragment& frag = *it;

			for (Fragment::ConstBondIterator b_it = frag.getBondsBegin(), b_end = frag.getBondsEnd(); b_it != b_end; ++b_it)
				bonds.insert(&*b_it);
		}

		return bonds.size();
	}

	void checkRingCount(const CDPL::Chem::FragmentList& frag_list, std::size_t size, std::size_t count)
	{
		using namespace CDPL;
		using namespace Chem;

		BOOST_CHECK(std::size_t(std::count_if(frag_list.getElementsBegin(), frag_list.getElementsEnd(), 
											  std::bind(std::equal_to<std::size_t>(), size, 
														std::bind(&Fragment::getNumBonds, std::placeholders::_1)))) == count);
	}
}


BOOST_AUTO_TEST_CASE(CompleteRingSetTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol1, mol2;

	std::ifstream ifs1(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Clique8.jme").c_str());
	std::ifstream ifs2(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs1);
	BOOST_CHECK(ifs2);

	BOOST_CHECK(JMEMoleculeReader(ifs1).read(mol1));
	BOOST_CHECK(JMEMoleculeReader(ifs2).read(mol2));

//-----

	CompleteRingSet rings1;

	BOOST_CHECK(rings1.getSize() == 0);

	rings1.perceive(mol1);

	BOOST_CHECK(rings1.getSize() == 8018);

	checkRingCount(rings1, 3, 56);
	checkRingCount(rings1, 4, 210);
	checkRingCount(rings1, 5, 672);
	checkRingCount(rings1, 6, 1680);
	checkRingCount(rings1, 7, 2880);
	checkRingCount(rings1, 8, 2520);

	BOOST_CHECK(getUniqueAtomCount(rings1) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings1) == mol1.getNumBonds());

//-----

	CompleteRingSet rings2(mol1);

	BOOST_CHECK(rings2.getSize() == 8018);

	checkRingCount(rings2, 3, 56);
	checkRingCount(rings2, 4, 210);
	checkRingCount(rings2, 5, 672);
	checkRingCount(rings2, 6, 1680);
	checkRingCount(rings2, 7, 2880);
	checkRingCount(rings2, 8, 2520);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings2) == mol1.getNumBonds());

//-----

	rings1.perceive(mol2);

	BOOST_CHECK(rings1.getSize() == 24);

	checkRingCount(rings1, 5, 1);
	checkRingCount(rings1, 6, 4);
	checkRingCount(rings1, 8, 1);
	checkRingCount(rings1, 9, 3);
	checkRingCount(rings1, 10, 3);
	checkRingCount(rings1, 11, 3);
	checkRingCount(rings1, 12, 1);
	checkRingCount(rings1, 13, 4);
	checkRingCount(rings1, 14, 1);
	checkRingCount(rings1, 15, 1);
	checkRingCount(rings1, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings1) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT));
	BOOST_CHECK(getUniqueBondCount(rings1) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT));

//-----

	rings2.perceive(mol2);

	BOOST_CHECK(rings2.getSize() == 24);

	checkRingCount(rings2, 5, 1);
	checkRingCount(rings2, 6, 4);
	checkRingCount(rings2, 8, 1);
	checkRingCount(rings2, 9, 3);
	checkRingCount(rings2, 10, 3);
	checkRingCount(rings2, 11, 3);
	checkRingCount(rings2, 12, 1);
	checkRingCount(rings2, 13, 4);
	checkRingCount(rings2, 14, 1);
	checkRingCount(rings2, 15, 1);
	checkRingCount(rings2, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT));
	BOOST_CHECK(getUniqueBondCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT));

//-----

	Molecule mol3(mol1);

	mol3 += mol2;

	rings2.perceive(mol3);

	BOOST_CHECK(rings2.getSize() == 8042);

	checkRingCount(rings2, 3, 56);
	checkRingCount(rings2, 4, 210);
	checkRingCount(rings2, 5, 673);
	checkRingCount(rings2, 6, 1684);
	checkRingCount(rings2, 7, 2880);
	checkRingCount(rings2, 8, 2521);
	checkRingCount(rings2, 9, 3);
	checkRingCount(rings2, 10, 3);
	checkRingCount(rings2, 11, 3);
	checkRingCount(rings2, 12, 1);
	checkRingCount(rings2, 13, 4);
	checkRingCount(rings2, 14, 1);
	checkRingCount(rings2, 15, 1);
	checkRingCount(rings2, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	Fragment frag1(mol3);

	rings2.perceive(frag1);

	BOOST_CHECK(rings2.getSize() == 8042);

	checkRingCount(rings2, 3, 56);
	checkRingCount(rings2, 4, 210);
	checkRingCount(rings2, 5, 673);
	checkRingCount(rings2, 6, 1684);
	checkRingCount(rings2, 7, 2880);
	checkRingCount(rings2, 8, 2521);
	checkRingCount(rings2, 9, 3);
	checkRingCount(rings2, 10, 3);
	checkRingCount(rings2, 11, 3);
	checkRingCount(rings2, 12, 1);
	checkRingCount(rings2, 13, 4);
	checkRingCount(rings2, 14, 1);
	checkRingCount(rings2, 15, 1);
	checkRingCount(rings2, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	Molecule mol4;

	rings2.perceive(mol4);

	BOOST_CHECK(rings2.getSize() == 0);

//-----

	Fragment frag2;

	rings2.perceive(frag2);

	BOOST_CHECK(rings2.getSize() == 0);

//-----

	CompleteRingSet rings3(mol4);

	BOOST_CHECK(rings3.getSize() == 0);

//-----

	CompleteRingSet rings4(frag2);

	BOOST_CHECK(rings4.getSize() == 0);

//-----

	frag2 += mol1;
	frag2 += mol2;

	rings2.perceive(frag2);

	BOOST_CHECK(rings2.getSize() == 8042);

	checkRingCount(rings2, 3, 56);
	checkRingCount(rings2, 4, 210);
	checkRingCount(rings2, 5, 673);
	checkRingCount(rings2, 6, 1684);
	checkRingCount(rings2, 7, 2880);
	checkRingCount(rings2, 8, 2521);
	checkRingCount(rings2, 9, 3);
	checkRingCount(rings2, 10, 3);
	checkRingCount(rings2, 11, 3);
	checkRingCount(rings2, 12, 1);
	checkRingCount(rings2, 13, 4);
	checkRingCount(rings2, 14, 1);
	checkRingCount(rings2, 15, 1);
	checkRingCount(rings2, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	BOOST_CHECK(frag2.getNumAtoms() == mol1.getNumAtoms() + mol2.getNumAtoms());

	for (std::size_t i = 0; i < frag2.getNumAtoms(); ) {
		if (!frag2.getAtom(i).getProperty<bool>(AtomProperty::IN_RING))
			frag2.removeAtom(i);
		else
			i++;
	}

	BOOST_CHECK(frag2.getNumAtoms() != mol1.getNumAtoms() + mol2.getNumAtoms());

	rings2.perceive(frag2);

	BOOST_CHECK(rings2.getSize() == 8042);

	checkRingCount(rings2, 3, 56);
	checkRingCount(rings2, 4, 210);
	checkRingCount(rings2, 5, 673);
	checkRingCount(rings2, 6, 1684);
	checkRingCount(rings2, 7, 2880);
	checkRingCount(rings2, 8, 2521);
	checkRingCount(rings2, 9, 3);
	checkRingCount(rings2, 10, 3);
	checkRingCount(rings2, 11, 3);
	checkRingCount(rings2, 12, 1);
	checkRingCount(rings2, 13, 4);
	checkRingCount(rings2, 14, 1);
	checkRingCount(rings2, 15, 1);
	checkRingCount(rings2, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	frag2.clear();

	frag2 += mol1;
	frag2 += mol2;

	BOOST_CHECK(frag2.getNumBonds() == mol1.getNumBonds() + mol2.getNumBonds());

	for (std::size_t i = 0; i < frag2.getNumBonds(); ) {
		if (!frag2.getBond(i).getProperty<bool>(BondProperty::IN_RING))
			frag2.removeBond(i);
		else
			i++;
	}

	BOOST_CHECK(frag2.getNumBonds() != mol1.getNumBonds() + mol2.getNumBonds());

	rings2.perceive(frag2);

	BOOST_CHECK(rings2.getSize() == 8042);

	checkRingCount(rings2, 3, 56);
	checkRingCount(rings2, 4, 210);
	checkRingCount(rings2, 5, 673);
	checkRingCount(rings2, 6, 1684);
	checkRingCount(rings2, 7, 2880);
	checkRingCount(rings2, 8, 2521);
	checkRingCount(rings2, 9, 3);
	checkRingCount(rings2, 10, 3);
	checkRingCount(rings2, 11, 3);
	checkRingCount(rings2, 12, 1);
	checkRingCount(rings2, 13, 4);
	checkRingCount(rings2, 14, 1);
	checkRingCount(rings2, 15, 1);
	checkRingCount(rings2, 17, 2);

	BOOST_CHECK(getUniqueAtomCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	frag2.clear();

	frag2.addAtom(mol1.getAtom(0));
	frag2.addAtom(mol1.getAtom(2));
	frag2.addAtom(mol1.getAtom(0));
	frag2.addAtom(mol1.getAtom(3));

	frag2.addBond(mol1.getBond(5));
	frag2.addBond(mol1.getBond(0));
	frag2.addBond(mol1.getBond(1));
	frag2.addBond(mol1.getBond(2));
	frag2.addBond(mol1.getBond(5));
	frag2.addBond(mol1.getBond(6));

	frag2 += mol1;

	BOOST_CHECK(frag2.getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(frag2.getNumAtoms() == mol1.getNumAtoms());

	rings4.perceive(frag2);

	BOOST_CHECK(rings4.getSize() == 8018);

	checkRingCount(rings4, 3, 56);
	checkRingCount(rings4, 4, 210);
	checkRingCount(rings4, 5, 672);
	checkRingCount(rings4, 6, 1680);
	checkRingCount(rings4, 7, 2880);
	checkRingCount(rings4, 8, 2520);

	BOOST_CHECK(getUniqueAtomCount(rings4) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(rings4) == mol1.getNumBonds());

//-----

	frag2.clear();

	frag2.addAtom(mol1.getAtom(0));
	frag2.addAtom(mol1.getAtom(2));
	frag2.addAtom(mol1.getAtom(0));
	frag2.addAtom(mol1.getAtom(3));

	BOOST_CHECK(frag2.getNumAtoms() == 3);

	rings4.perceive(frag2);

	BOOST_CHECK(rings4.getSize() == 0);

//-----

	frag2.clear();

	frag2.addBond(mol1.getBond(5));
	frag2.addBond(mol1.getBond(0));
	frag2.addBond(mol1.getBond(1));
	frag2.addBond(mol1.getBond(2));
	frag2.addBond(mol1.getBond(5));
	frag2.addBond(mol1.getBond(6));

	BOOST_CHECK(frag2.getNumBonds() == 5);

	rings4.perceive(frag2);

	BOOST_CHECK(rings4.getSize() == 0);

//-----

	mol4.addAtom();
	mol4.addAtom();

	mol4.addBond(0, 1);
	mol4.addBond(0, 1);
	mol4.addBond(0, 0);
	mol4.addBond(1, 1);

	rings4.perceive(mol4);

	BOOST_CHECK(rings4.getSize() == 0);
}
