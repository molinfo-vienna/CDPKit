/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SmallestSetOfSmallestRingsTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <boost/bind.hpp>

#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
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

			for (Fragment::ConstBondIterator b_it = frag.getBondsBegin(),
					 b_end = frag.getBondsEnd(); b_it != b_end; ++b_it)
				bonds.insert(&*b_it);
		}

		return bonds.size();
	}

	void checkRingCount(const CDPL::Chem::FragmentList& frag_list, std::size_t size, std::size_t count)
	{
		using namespace CDPL;
		using namespace Chem;

		BOOST_CHECK(std::size_t(std::count_if(frag_list.getElementsBegin(), frag_list.getElementsEnd(), 
											  boost::bind(std::equal_to<std::size_t>(), size, 
														  boost::bind(&Fragment::getNumBonds, _1)))) == count);
	}
}


BOOST_AUTO_TEST_CASE(SmallestSetOfSmallestRingsTest)
{
	using namespace CDPL;
	using namespace Chem;
	
	Molecule mol1, mol2;

	std::ifstream ifs1(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/Fullerene2.jme").c_str());
	std::ifstream ifs2(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/Morphine.jme").c_str());

	BOOST_CHECK(ifs1);
	BOOST_CHECK(ifs2);

	BOOST_CHECK(JMEMoleculeReader(ifs1).read(mol1));
	BOOST_CHECK(JMEMoleculeReader(ifs2).read(mol2));

//-----

	SmallestSetOfSmallestRings sssr1;

	BOOST_CHECK(sssr1.getSize() == 0);

	sssr1.perceive(mol1);

	BOOST_CHECK(sssr1.getSize() == 31);

	checkRingCount(sssr1, 5, 12);
	checkRingCount(sssr1, 6, 19);

	BOOST_CHECK(getUniqueAtomCount(sssr1) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr1) == mol1.getNumBonds());

//-----

	SmallestSetOfSmallestRings sssr2(mol1);

	BOOST_CHECK(sssr2.getSize() == 31);

	checkRingCount(sssr2, 5, 12);
	checkRingCount(sssr2, 6, 19);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol1.getNumBonds());

//-----

	sssr1.perceive(mol2);

	BOOST_CHECK(sssr1.getSize() == 5);

	checkRingCount(sssr1, 5, 1);
	checkRingCount(sssr1, 6, 4);

	BOOST_CHECK(getUniqueAtomCount(sssr1) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT));
	BOOST_CHECK(getUniqueBondCount(sssr1) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT));

//-----

	sssr2.perceive(mol2);

	BOOST_CHECK(sssr2.getSize() == 5);

	checkRingCount(sssr2, 5, 1);
	checkRingCount(sssr2, 6, 4);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT));
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT));

//-----

	Molecule mol3(mol1);

	mol3 += mol2;

	sssr2.perceive(mol3);

	BOOST_CHECK(sssr2.getSize() == 36);

	checkRingCount(sssr2, 5, 13);
	checkRingCount(sssr2, 6, 23);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	Fragment frag1(mol3);

	sssr2.perceive(frag1);

	BOOST_CHECK(sssr2.getSize() == 36);

	checkRingCount(sssr2, 5, 13);
	checkRingCount(sssr2, 6, 23);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
				+ mol1.getNumBonds());

//-----

	Molecule mol4;

	sssr2.perceive(mol4);

	BOOST_CHECK(sssr2.getSize() == 0);

//-----

	Fragment frag2;

	sssr2.perceive(frag2);

	BOOST_CHECK(sssr2.getSize() == 0);

//-----

	SmallestSetOfSmallestRings sssr3(mol4);

	BOOST_CHECK(sssr3.getSize() == 0);

//-----

	SmallestSetOfSmallestRings sssr4(frag2);

	BOOST_CHECK(sssr4.getSize() == 0);

//-----

	frag2 += mol1;
	frag2 += mol2;

	sssr2.perceive(frag2);

	BOOST_CHECK(sssr2.getSize() == 36);

	checkRingCount(sssr2, 5, 13);
	checkRingCount(sssr2, 6, 23);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
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

	sssr2.perceive(frag2);

	BOOST_CHECK(sssr2.getSize() == 36);

	checkRingCount(sssr2, 5, 13);
	checkRingCount(sssr2, 6, 23);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
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

	sssr2.perceive(frag2);

	BOOST_CHECK(sssr2.getSize() == 36);

	checkRingCount(sssr2, 5, 13);
	checkRingCount(sssr2, 6, 23);

	BOOST_CHECK(getUniqueAtomCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_ATOM_COUNT) 
				+ mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr2) == mol2.getProperty<std::size_t>(MolecularGraphProperty::RING_BOND_COUNT) 
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

	sssr4.perceive(frag2);

	BOOST_CHECK(sssr4.getSize() == 31);

	checkRingCount(sssr4, 5, 12);
	checkRingCount(sssr4, 6, 19);

	BOOST_CHECK(getUniqueAtomCount(sssr4) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(sssr4) == mol1.getNumBonds());

//-----

	frag2.clear();

	frag2.addAtom(mol1.getAtom(0));
	frag2.addAtom(mol1.getAtom(2));
	frag2.addAtom(mol1.getAtom(0));
	frag2.addAtom(mol1.getAtom(3));

	BOOST_CHECK(frag2.getNumAtoms() == 3);

	sssr4.perceive(frag2);

	BOOST_CHECK(sssr4.getSize() == 0);

//-----

	frag2.clear();

	frag2.addBond(mol1.getBond(5));
	frag2.addBond(mol1.getBond(0));
	frag2.addBond(mol1.getBond(1));
	frag2.addBond(mol1.getBond(2));
	frag2.addBond(mol1.getBond(5));
	frag2.addBond(mol1.getBond(6));

	BOOST_CHECK(frag2.getNumBonds() == 5);

	sssr4.perceive(frag2);

	BOOST_CHECK(sssr4.getSize() == 0);

//-----

	mol4.addAtom();
	mol4.addAtom();
	mol4.addAtom();

	mol4.addBond(0, 1);
	mol4.addBond(0, 1);
	mol4.addBond(0, 0);
	mol4.addBond(1, 1);
	mol4.addBond(0, 2);
	mol4.addBond(1, 2);

	sssr4.perceive(mol4);

	BOOST_CHECK(sssr4.getSize() == 1);

	checkRingCount(sssr4, 3, 1);

	BOOST_CHECK(getUniqueAtomCount(sssr4) == 3);
	BOOST_CHECK(getUniqueBondCount(sssr4) == 3);
}
