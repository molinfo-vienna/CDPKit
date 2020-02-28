/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ComponentSetTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <set>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/ComponentSet.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
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
}


BOOST_AUTO_TEST_CASE(ComponentSetTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol1, mol2, mol3;

	std::ifstream ifs1(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());
	std::ifstream ifs2(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Clique8.jme").c_str());

	BOOST_CHECK(ifs1);
	BOOST_CHECK(ifs2);

	BOOST_CHECK(JMEMoleculeReader(ifs1).read(mol1));
	BOOST_CHECK(JMEMoleculeReader(ifs2).read(mol2));

	mol2.addBond(0, 1);

//-----

	ComponentSet component_set1;

	BOOST_CHECK(component_set1.getSize() == 0);

	component_set1.perceive(mol1);

	BOOST_CHECK(component_set1.getSize() == 1);
	BOOST_CHECK(component_set1.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set1.getElement(0).getNumAtoms() == mol1.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set1) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set1) == mol1.getNumBonds());

	component_set1.perceive(mol2);

	BOOST_CHECK(component_set1.getSize() == 1);
	BOOST_CHECK(component_set1.getElement(0).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set1.getElement(0).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set1) == mol2.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set1) == mol2.getNumBonds());

//-----

	ComponentSet component_set2(mol1);

	BOOST_CHECK(component_set2.getSize() == 1);
	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol1.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol1.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol1.getNumBonds());

	component_set2.perceive(mol2);

	BOOST_CHECK(component_set2.getSize() == 1);
	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol2.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol2.getNumBonds());

//-----

	mol3 += mol1;
	mol3 += mol2;

	BOOST_CHECK(mol3.getNumBonds() == mol1.getNumBonds() + mol2.getNumBonds());
	BOOST_CHECK(mol3.getNumAtoms() == mol1.getNumAtoms() + mol2.getNumAtoms());

	component_set2.perceive(mol3);

	BOOST_CHECK(component_set2.getSize() == 2);
	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol1.getNumAtoms());
	BOOST_CHECK(component_set2.getElement(1).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set2.getElement(1).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol3.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol3.getNumBonds());

//-----

	Fragment frag1(mol3);

	BOOST_CHECK(frag1.getNumBonds() == mol1.getNumBonds() + mol2.getNumBonds());
	BOOST_CHECK(frag1.getNumAtoms() == mol1.getNumAtoms() + mol2.getNumAtoms());

	component_set2.perceive(frag1);

	BOOST_CHECK(component_set2.getSize() == 2);
	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol1.getNumAtoms());
	BOOST_CHECK(component_set2.getElement(1).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set2.getElement(1).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol3.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol3.getNumBonds());

//-----

	frag1 += frag1;

	BOOST_CHECK(!frag1.addAtom(mol3.getAtom(0)));
	BOOST_CHECK(!frag1.addAtom(mol3.getAtom(2)));
	BOOST_CHECK(!frag1.addAtom(mol3.getAtom(1)));

	BOOST_CHECK(!frag1.addBond(mol3.getBond(3)));
	BOOST_CHECK(!frag1.addBond(mol3.getBond(2)));

	component_set2.perceive(frag1);

	BOOST_CHECK(component_set2.getSize() == 2);
	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol1.getNumAtoms());
	BOOST_CHECK(component_set2.getElement(1).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set2.getElement(1).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol3.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol3.getNumBonds());

//-----

	Fragment frag2;

	frag2 = mol1;
	frag2 += mol2;

	BOOST_CHECK(frag2.getNumBonds() == mol1.getNumBonds() + mol2.getNumBonds());
	BOOST_CHECK(frag2.getNumAtoms() == mol1.getNumAtoms() + mol2.getNumAtoms());

	component_set2.perceive(frag2);

	BOOST_CHECK(component_set2.getSize() == 2);

	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol1.getNumAtoms());
	BOOST_CHECK(component_set2.getElement(1).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set2.getElement(1).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol1.getNumAtoms() + mol2.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol1.getNumBonds() + mol2.getNumBonds());

//-----

	frag2.clear();

	BOOST_CHECK(frag2.addAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.addAtom(mol2.getAtom(2)));
	BOOST_CHECK(!frag2.addAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.addAtom(mol2.getAtom(3)));

	BOOST_CHECK(frag2.getNumAtoms() == 3);

	component_set2.perceive(frag2);

	BOOST_CHECK(component_set2.getSize() == 3);

	BOOST_CHECK(getUniqueAtomCount(component_set2) == 3);
	BOOST_CHECK(getUniqueBondCount(component_set2) == 0);

//-----

	frag2.clear();

	BOOST_CHECK(frag2.addBond(mol2.getBond(5)));
	BOOST_CHECK(frag2.addBond(mol2.getBond(0)));
	BOOST_CHECK(frag2.addBond(mol2.getBond(1)));
	BOOST_CHECK(frag2.addBond(mol2.getBond(2)));
	BOOST_CHECK(!frag2.addBond(mol2.getBond(5)));
	BOOST_CHECK(frag2.addBond(mol2.getBond(6)));

	BOOST_CHECK(frag2.getNumBonds() == 5);

	component_set2.perceive(frag2);

	BOOST_CHECK(component_set2.getSize() > 1);

//-----

	component_set2.perceive(frag1);

	BOOST_CHECK(component_set2.getSize() == 2);
	BOOST_CHECK(component_set2.getElement(0).getNumBonds() == mol1.getNumBonds());
	BOOST_CHECK(component_set2.getElement(0).getNumAtoms() == mol1.getNumAtoms());
	BOOST_CHECK(component_set2.getElement(1).getNumBonds() == mol2.getNumBonds());
	BOOST_CHECK(component_set2.getElement(1).getNumAtoms() == mol2.getNumAtoms());

	BOOST_CHECK(getUniqueAtomCount(component_set2) == mol3.getNumAtoms());
	BOOST_CHECK(getUniqueBondCount(component_set2) == mol3.getNumBonds());

//-----

	Molecule mol4;

	component_set2.perceive(mol4);

	BOOST_CHECK(component_set2.getSize() == 0);

//-----

	ComponentSet component_set3(mol4);

	BOOST_CHECK(component_set3.getSize() == 0);

//-----

	Fragment frag3;

	component_set2.perceive(frag3);

	BOOST_CHECK(component_set2.getSize() == 0);

//-----

	ComponentSet component_set4(frag3);

	BOOST_CHECK(component_set4.getSize() == 0);
}
