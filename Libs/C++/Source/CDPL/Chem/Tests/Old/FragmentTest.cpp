/* 
 * FragmentTest.cpp 
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
#include <sstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/FragmentProperties.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"
#include "CDPL/Base/PropertyManager.hpp"
#include "CDPL/Base/PropertyKey.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	void checkAtomIndices(const CDPL::Chem::MolecularGraph& molgraph)
	{
		for (std::size_t i = 0; i < molgraph.getNumAtoms(); i++)
			BOOST_CHECK(molgraph.getAtomIndex(molgraph.getAtom(i)) == i);
	}

	void checkBondIndices(const CDPL::Chem::MolecularGraph& molgraph)
	{
		for (std::size_t i = 0; i < molgraph.getNumBonds(); i++)
			BOOST_CHECK(molgraph.getBondIndex(molgraph.getBond(i)) == i);
	}
}


BOOST_AUTO_TEST_CASE(FragmentTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	Fragment frag1;
	Fragment frag2;

	Molecule mol1;

	std::istringstream iss("CCCCCC");

	BOOST_CHECK(iss);
	BOOST_CHECK(SMILESMoleculeReader(iss).read(mol1));

	BOOST_CHECK(mol1.getNumAtoms() == 6);
	BOOST_CHECK(mol1.getNumBonds() == 5);

	Molecule mol2(mol1);	

	BOOST_CHECK(mol2.getNumAtoms() == 6);
	BOOST_CHECK(mol2.getNumBonds() == 5);

//-----

	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(0)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 0);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() == const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() == const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK_THROW(frag1.getAtom(0), IndexError);
	BOOST_CHECK_THROW(frag1.getAtom(1), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);
	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(frag1.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(0), IndexError);
	BOOST_CHECK_THROW(frag1.removeBond(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(frag1.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(frag1.removeBond(frag1.getBondsBegin()), RangeError);

//-----

	BOOST_CHECK(frag1.addAtom(mol1.getAtom(0)));

	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag1.getNumAtoms() == 1);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 1);

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(0));

	BOOST_CHECK_THROW(frag1.getAtom(1), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);
	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

//-----

	BOOST_CHECK(frag2.addBond(mol1.getBond(0)));

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag2.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag2.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag2.getAtomIndex(mol1.getAtom(0)) == 0);
	BOOST_CHECK_THROW(frag2.getBondIndex(mol2.getBond(0)), ItemNotFound);

	BOOST_CHECK(frag2.getNumAtoms() == 2);
	BOOST_CHECK(frag2.getNumBonds() == 1);

	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsEnd() - const_cast<Fragment&>(frag2).getBondsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsEnd() - const_cast<const Fragment&>(frag2).getBondsBegin() == 1);

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsEnd() - const_cast<Fragment&>(frag2).getAtomsBegin() == 2);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsEnd() - const_cast<const Fragment&>(frag2).getAtomsBegin() == 2);

	BOOST_CHECK(&frag2.getBond(0) == &mol1.getBond(0));

	BOOST_CHECK_THROW(frag2.getBond(1), IndexError);

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));

//-----

	BOOST_CHECK(frag1.addAtom(mol2.getAtom(0)));

	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 2);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag1).getAtomsBegin()) == &mol2.getAtom(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag1).getAtomsBegin()) == &mol2.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol2.getAtom(0));

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);
	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

//-----

	BOOST_CHECK(frag1.addBond(mol2.getBond(0)));

	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag1.getNumAtoms() == 3);
	BOOST_CHECK(frag1.getNumBonds() == 1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag1).getAtomsBegin()) == &mol2.getAtom(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag1).getAtomsBegin()) == &mol2.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol2.getAtom(0));

	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));

	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

//-----

	BOOST_CHECK(frag2.addBond(mol2.getBond(0)));

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag2.getNumAtoms() == 4);
	BOOST_CHECK(frag2.getNumBonds() == 2);

	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag2).getBondsBegin()) == &mol2.getBond(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag2).getBondsBegin()) == &mol2.getBond(0));

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsEnd() - const_cast<Fragment&>(frag2).getAtomsBegin() == 4);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsEnd() - const_cast<const Fragment&>(frag2).getAtomsBegin() == 4);

	BOOST_CHECK(&frag2.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag2.getBond(1) == &mol2.getBond(0));

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol2.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(3) == &mol2.getAtom(1));

	BOOST_CHECK_THROW(frag2.getAtom(4), IndexError);

//-----

	BOOST_CHECK(!frag2.addAtom(mol2.getAtom(0)));

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag2.getNumAtoms() == 4);
	BOOST_CHECK(frag2.getNumBonds() == 2);

	checkAtomIndices(frag2);
	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag2).getBondsBegin()) == &mol2.getBond(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag2).getBondsBegin()) == &mol2.getBond(0));

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() != const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() != const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(&frag2.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag2.getBond(1) == &mol2.getBond(0));

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol2.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(3) == &mol2.getAtom(1));

	BOOST_CHECK_THROW(frag2.getAtom(4), IndexError);

//-----

	BOOST_CHECK(frag1.addBond(mol1.getBond(0)));

	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag1.getNumAtoms() == 4);
	BOOST_CHECK(frag1.getNumBonds() == 2);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag1).getAtomsBegin()) == &mol2.getAtom(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag1).getAtomsBegin()) == &mol2.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(0));

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol2.getAtom(0));

	BOOST_CHECK_THROW(frag1.getAtom(4), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(0));

	BOOST_CHECK_THROW(frag1.getBond(2), IndexError);

//-----

	BOOST_CHECK(!frag2.addAtom(mol1.getAtom(0)));

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag2.getNumAtoms() == 4);
	BOOST_CHECK(frag2.getNumBonds() == 2);

	checkAtomIndices(frag2);
	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));

	BOOST_CHECK(&*(++const_cast<Fragment&>(frag2).getBondsBegin()) == &mol2.getBond(0));
	BOOST_CHECK(&*(++const_cast<const Fragment&>(frag2).getBondsBegin()) == &mol2.getBond(0));

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() != const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() != const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(&frag2.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag2.getBond(1) == &mol2.getBond(0));

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol2.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(3) == &mol2.getAtom(1));

	BOOST_CHECK_THROW(frag2.getAtom(4), IndexError);

//-----

	BOOST_CHECK(!frag1.addAtom(mol1.getAtom(0)));
	BOOST_CHECK(!frag1.addAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.addAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.addAtom(mol1.getAtom(3)));

	BOOST_CHECK(!frag1.addBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.addBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.addBond(mol1.getBond(2)));

	BOOST_CHECK(!frag1.addAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag1.addAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.addAtom(mol1.getAtom(5)));
	BOOST_CHECK(!frag1.addAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag1.addBond(mol1.getBond(3)));
	BOOST_CHECK(frag1.addBond(mol1.getBond(4)));
	BOOST_CHECK(!frag1.addBond(mol1.getBond(4)));

	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag1.getNumAtoms() == 8);
	BOOST_CHECK(frag1.getNumBonds() == 6);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 8);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 8);

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(2));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 6);

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 3) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 3) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 4) == &mol1.getBond(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 4) == &mol1.getBond(3));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 5) == &mol1.getBond(4));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 5) == &mol1.getBond(4));

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(2));

	BOOST_CHECK_THROW(frag1.getAtom(9), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(9), IndexError);
	BOOST_CHECK_THROW(frag1.removeAtom(frag1.getAtomsEnd()), RangeError);

	BOOST_CHECK(&frag1.getBond(3) == &mol1.getBond(2));
	BOOST_CHECK(&frag1.getBond(4) == &mol1.getBond(3));
	BOOST_CHECK(&frag1.getBond(5) == &mol1.getBond(4));
	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(0));
	BOOST_CHECK(&frag1.getBond(2) == &mol1.getBond(1));

	BOOST_CHECK_THROW(frag1.getBond(6), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(7), IndexError);
	BOOST_CHECK_THROW(frag1.removeBond(frag1.getBondsEnd()), RangeError);

//-----

	frag1.removeAtom(0);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(0)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 7);
	BOOST_CHECK(frag1.getNumBonds() == 5);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 7);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 7);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 5);

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 3) == &mol1.getBond(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 3) == &mol1.getBond(3));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 4) == &mol1.getBond(4));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 4) == &mol1.getBond(4));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(2));

	BOOST_CHECK_THROW(frag1.getAtom(8), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(9), IndexError);

	BOOST_CHECK(&frag1.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag1.getBond(4) == &mol1.getBond(4));
	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(2) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(5), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(6), IndexError);

//-----

	frag1.removeBond(4);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(0)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 7);
	BOOST_CHECK(frag1.getNumBonds() == 4);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 7);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 7);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 4);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 4);

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 3) == &mol1.getBond(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 3) == &mol1.getBond(3));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(2));

	BOOST_CHECK_THROW(frag1.getAtom(8), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(9), IndexError);

	BOOST_CHECK(&frag1.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(2) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(4), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(4), IndexError);

//-----

	frag1.removeAtom(5);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 3);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 3);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 3);

	BOOST_CHECK(&*const_cast<Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag1).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(6), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(6), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(2) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(3), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(6), IndexError);

//-----

	frag1.removeBond(0);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 2);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(5));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 2);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 2);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(2));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag1.getAtom(6), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(6), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(2), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(2), IndexError);

//-----

	frag1.removeAtom(1);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 5);
	BOOST_CHECK(frag1.getNumBonds() == 2);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 5);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(5));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 2);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 2);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(2));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag1.getAtom(5), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(5), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(2), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(2), IndexError);

//-----

	frag1.removeBond(1);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 5);
	BOOST_CHECK(frag1.getNumBonds() == 1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 5);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(5));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 1);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag1.getAtom(5), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(5), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));

	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(2), IndexError);

//-----

	BOOST_CHECK(!frag1.removeAtom(mol1.getAtom(4)));

	BOOST_CHECK(frag1.removeAtom(mol1.getAtom(3)));

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 4);
	BOOST_CHECK(frag1.getNumBonds() == 1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 4);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 4);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 1);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag1.getAtom(4), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(4), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));

	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(2), IndexError);

//-----

	BOOST_CHECK(frag1.addBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.addBond(mol1.getBond(2)));

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 3);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 3);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 3);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 2) == &mol1.getBond(2));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(5) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(7), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(6), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(0));
	BOOST_CHECK(&frag1.getBond(2) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(4), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(3), IndexError);

//-----

	BOOST_CHECK(frag1.removeBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.removeBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.removeBond(mol1.getBond(0)));

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 2);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 2);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 2);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 1) == &mol1.getBond(2));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(5) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(7), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(6), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(2));

	BOOST_CHECK_THROW(frag1.getBond(2), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(3), IndexError);

//-----

	Fragment::BondIterator b_it = frag1.removeBond(frag1.getBondsBegin() + 1);

	BOOST_CHECK(b_it == frag1.getBondsEnd());

	BOOST_CHECK(!frag1.removeBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.removeBond(mol1.getBond(2)));

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 1);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin()) == &mol1.getBond(1));

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(5) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(7), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(6), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(1));

	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(1), IndexError);

//-----

	b_it = frag1.removeBond(frag1.getBondsBegin());

	BOOST_CHECK(b_it == frag1.getBondsBegin());
	BOOST_CHECK(b_it == frag1.getBondsEnd());

	BOOST_CHECK(!frag1.removeBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.removeBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.removeBond(mol1.getBond(2)));

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(4)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 5) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 0);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 0);

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(5) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(7), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(6), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(0), IndexError);

//-----

	Fragment::AtomIterator a_it = frag1.removeAtom(++frag1.getAtomsBegin());

	BOOST_CHECK(a_it == ++frag1.getAtomsBegin());

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 5);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 5);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 0);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 0);

	BOOST_CHECK(&frag1.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(5), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(1), IndexError);

//-----

	a_it = frag1.removeAtom(frag1.getAtomsBegin());

	BOOST_CHECK(a_it == frag1.getAtomsBegin());

	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getAtomIndex(mol2.getAtom(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 4);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 4);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 4);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(3));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol1.getAtom(3));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 0);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 0);

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(3));

	BOOST_CHECK_THROW(frag1.getAtom(4), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(5), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(0), IndexError);

//-----

	a_it = frag1.removeAtom(frag1.getAtomsEnd() - 1);

	BOOST_CHECK(a_it == frag1.getAtomsEnd());

	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 3);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 3);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 3);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 0);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 0);

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(0));

	BOOST_CHECK_THROW(frag1.getAtom(3), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(3), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(0), IndexError);

//-----

	BOOST_CHECK(frag1.addAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag1.addBond(mol2.getBond(0)));

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(3)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 5);
	BOOST_CHECK(frag1.getNumBonds() == 1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 5);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 4) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 4) == &mol2.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 1);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getBondsBegin() + 0) == &mol2.getBond(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getBondsBegin() + 0) == &mol2.getBond(0));

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(3) == &mol2.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(4) == &mol2.getAtom(0));

	BOOST_CHECK_THROW(frag1.getAtom(5), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(13), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol2.getBond(0));

	BOOST_CHECK_THROW(frag1.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(1), IndexError);

//-----

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(1)));

	frag1.removeAtom(3);

	BOOST_CHECK(frag1.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag1.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(!frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(!frag1.containsBond(mol2.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(!frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK_THROW(frag1.getAtomIndex(mol1.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getAtomIndex(mol2.getAtom(1)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol2.getBond(0)), ItemNotFound);
	BOOST_CHECK_THROW(frag1.getBondIndex(mol1.getBond(4)), ItemNotFound);

	BOOST_CHECK(frag1.getNumAtoms() == 4);
	BOOST_CHECK(frag1.getNumBonds() == 0);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 4);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 4);

	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 0) == &mol1.getAtom(2));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 1) == &mol1.getAtom(5));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 2) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag1).getAtomsBegin() + 3) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag1).getAtomsBegin() + 3) == &mol2.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() == const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() == const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 0);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 0);

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(5));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(3) == &mol2.getAtom(0));

	BOOST_CHECK_THROW(frag1.getAtom(4), IndexError);

	BOOST_CHECK_THROW(frag1.removeAtom(4), IndexError);

	BOOST_CHECK_THROW(frag1.getBond(0), IndexError);

	BOOST_CHECK_THROW(frag1.removeBond(0), IndexError);

//-----

	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsBond(mol2.getBond(0)));

	frag2.removeBond(frag2.getBondsBegin());
	b_it = frag2.removeBond(frag2.getBondsBegin());

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(1)));

	BOOST_CHECK(!frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(!frag2.containsBond(mol2.getBond(0)));

	BOOST_CHECK(frag2.getNumAtoms() == 4);
	BOOST_CHECK(frag2.getNumBonds() == 0);

	checkAtomIndices(frag2);
	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() == const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() == const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() != const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() != const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 0) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 0) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 2) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 2) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 3) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 3) == &mol2.getAtom(1));

	BOOST_CHECK_THROW(frag2.getBond(0), IndexError);

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol2.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(3) == &mol2.getAtom(1));

	BOOST_CHECK_THROW(frag2.getAtom(4), IndexError);

//-----
	
	BOOST_CHECK(!frag2.addAtom(mol2.getAtom(0)));
	BOOST_CHECK(!frag2.addAtom(mol2.getAtom(1)));

	BOOST_CHECK(frag2.addBond(mol2.getBond(0)));
	BOOST_CHECK(frag2.addBond(mol2.getBond(1)));

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol2.getAtom(1)));

	BOOST_CHECK(!frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag2.containsBond(mol2.getBond(1)));

	BOOST_CHECK(frag2.getNumAtoms() == 5);
	BOOST_CHECK(frag2.getNumBonds() == 2);

	checkAtomIndices(frag2);
	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getBondsBegin() == &mol2.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getBondsBegin() == &mol2.getBond(0));

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() != const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() != const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 0) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 0) == &mol1.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 1) == &mol1.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 2) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 2) == &mol2.getAtom(0));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 3) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 3) == &mol2.getAtom(1));
	BOOST_CHECK(&*(const_cast<Fragment&>(frag2).getAtomsBegin() + 4) == &mol2.getAtom(2));
	BOOST_CHECK(&*(const_cast<const Fragment&>(frag2).getAtomsBegin() + 4) == &mol2.getAtom(2));

	BOOST_CHECK(&frag2.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag2.getBond(1) == &mol2.getBond(1));

	BOOST_CHECK_THROW(frag2.getBond(2), IndexError);
	BOOST_CHECK_THROW(frag2.removeBond(2), IndexError);

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol2.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(3) == &mol2.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(4) == &mol2.getAtom(2));

	BOOST_CHECK_THROW(frag2.getAtom(5), IndexError);
	BOOST_CHECK_THROW(frag2.removeAtom(5), IndexError);

//-----

	frag2.clear();

	BOOST_CHECK(frag2.getNumAtoms() == 0);
	BOOST_CHECK(frag2.getNumBonds() == 0);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() == const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() == const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() == const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() == const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK_THROW(frag2.getAtom(0), IndexError);

	BOOST_CHECK_THROW(frag2.getBond(0), IndexError);

	BOOST_CHECK_THROW(frag2.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(frag2.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(frag2.removeBond(0), IndexError);
	BOOST_CHECK_THROW(frag2.removeBond(1), IndexError);

	BOOST_CHECK_THROW(frag2.removeAtom(frag2.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(frag2.removeBond(frag2.getBondsBegin()), RangeError);

//-----

	BOOST_CHECK(frag2.addAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.addAtom(mol1.getAtom(1)));

	BOOST_CHECK(frag2.addBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.addBond(mol1.getBond(1)));

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(1)));

	BOOST_CHECK(frag2.getNumAtoms() == 3);
	BOOST_CHECK(frag2.getNumBonds() == 2);

	checkAtomIndices(frag2);
	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() != const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() != const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsEnd() - const_cast<Fragment&>(frag2).getAtomsBegin() == 3);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsEnd() - const_cast<const Fragment&>(frag2).getAtomsBegin() == 3);

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getAtomsBegin() == &mol1.getAtom(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getAtomsBegin() == &mol1.getAtom(0));

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsEnd() - const_cast<Fragment&>(frag2).getBondsBegin() == 2);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsEnd() - const_cast<const Fragment&>(frag2).getBondsBegin() == 2);

	BOOST_CHECK(&*const_cast<Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));
	BOOST_CHECK(&*const_cast<const Fragment&>(frag2).getBondsBegin() == &mol1.getBond(0));

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol1.getAtom(2));

	BOOST_CHECK_THROW(frag2.getAtom(3), IndexError);

	BOOST_CHECK(&frag2.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag2.getBond(1) == &mol1.getBond(1));

	BOOST_CHECK_THROW(frag2.getBond(2), IndexError);

//-----

	PropertyKey key = PropertyManager::allocPropertyKey("test key");

	mol1.setProperty(key, std::string("test 1"));
	frag1.setProperty(key, std::string("test 2"));

	BOOST_CHECK(mol1.getProperty<std::string>(key) == "test 1");
	BOOST_CHECK(frag1.getProperty<std::string>(key) == "test 2");

	frag1 = mol1;

	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag1.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag1.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag1.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag1.getNumAtoms() == 6);
	BOOST_CHECK(frag1.getNumBonds() == 5);

	checkAtomIndices(frag1);
	checkBondIndices(frag1);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsBegin() != const_cast<Fragment&>(frag1).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsBegin() != const_cast<const Fragment&>(frag1).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getAtomsEnd() - const_cast<Fragment&>(frag1).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getAtomsEnd() - const_cast<const Fragment&>(frag1).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsBegin() != const_cast<Fragment&>(frag1).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsBegin() != const_cast<const Fragment&>(frag1).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag1).getBondsEnd() - const_cast<Fragment&>(frag1).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag1).getBondsEnd() - const_cast<const Fragment&>(frag1).getBondsBegin() == 5);

	BOOST_CHECK(&frag1.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag1.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag1.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag1.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag1.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag1.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag1.getAtom(6), IndexError);

	BOOST_CHECK(&frag1.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag1.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag1.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag1.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag1.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK_THROW(frag1.getBond(5), IndexError);

	BOOST_CHECK_THROW(frag1.getProperty<std::string>(key), CalculationFailed);

//-----

	frag1.setProperty(key, std::string("test 2"));

	BOOST_CHECK(frag1.getProperty<std::string>(key) == "test 2");

	BOOST_CHECK_THROW(frag2.getProperty<std::string>(key), CalculationFailed);

	frag2 = frag1;

	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag2.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag2.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag2.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag2.getNumAtoms() == 6);
	BOOST_CHECK(frag2.getNumBonds() == 5);

	checkAtomIndices(frag2);
	checkBondIndices(frag2);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsBegin() != const_cast<Fragment&>(frag2).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsBegin() != const_cast<const Fragment&>(frag2).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getAtomsEnd() - const_cast<Fragment&>(frag2).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getAtomsEnd() - const_cast<const Fragment&>(frag2).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsBegin() != const_cast<Fragment&>(frag2).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsBegin() != const_cast<const Fragment&>(frag2).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag2).getBondsEnd() - const_cast<Fragment&>(frag2).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag2).getBondsEnd() - const_cast<const Fragment&>(frag2).getBondsBegin() == 5);

	BOOST_CHECK(&frag2.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag2.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag2.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag2.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag2.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag2.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag2.getAtom(6), IndexError);

	BOOST_CHECK(&frag2.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag2.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag2.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag2.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag2.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK_THROW(frag2.getBond(5), IndexError);

	BOOST_CHECK(frag2.getProperty<std::string>(key) == "test 2");

//-----

	frag2.clear();

	BOOST_CHECK(frag2.getNumAtoms() == 0);
	BOOST_CHECK(frag2.getNumBonds() == 0);

	BOOST_CHECK(frag2.getNumProperties() == 0);

	BOOST_CHECK_THROW(frag2.getProperty<std::string>(key), CalculationFailed);

//-----

	Fragment frag3(frag1);

	BOOST_CHECK(frag3.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag3.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag3.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag3.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag3.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag3.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag3.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag3.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag3.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag3.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag3.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag3.getNumAtoms() == 6);
	BOOST_CHECK(frag3.getNumBonds() == 5);

	checkAtomIndices(frag3);
	checkBondIndices(frag3);

	BOOST_CHECK(const_cast<Fragment&>(frag3).getAtomsBegin() != const_cast<Fragment&>(frag3).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag3).getAtomsBegin() != const_cast<const Fragment&>(frag3).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag3).getAtomsEnd() - const_cast<Fragment&>(frag3).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag3).getAtomsEnd() - const_cast<const Fragment&>(frag3).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag3).getBondsBegin() != const_cast<Fragment&>(frag3).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag3).getBondsBegin() != const_cast<const Fragment&>(frag3).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag3).getBondsEnd() - const_cast<Fragment&>(frag3).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag3).getBondsEnd() - const_cast<const Fragment&>(frag3).getBondsBegin() == 5);

	BOOST_CHECK(&frag3.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag3.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag3.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag3.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag3.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag3.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag3.getAtom(6), IndexError);

	BOOST_CHECK(&frag3.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag3.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag3.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag3.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag3.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK_THROW(frag3.getBond(5), IndexError);

	BOOST_CHECK(frag3.getProperty<std::string>(key) == "test 2");

	BOOST_CHECK(frag3.getNumProperties() == 1);

//-----

	Fragment frag4(mol2);

	BOOST_CHECK(frag4.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag4.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag4.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag4.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag4.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag4.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag4.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag4.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag4.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag4.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag4.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag4.getNumAtoms() == 6);
	BOOST_CHECK(frag4.getNumBonds() == 5);

	checkAtomIndices(frag4);
	checkBondIndices(frag4);

	BOOST_CHECK(const_cast<Fragment&>(frag4).getAtomsBegin() != const_cast<Fragment&>(frag4).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag4).getAtomsBegin() != const_cast<const Fragment&>(frag4).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag4).getAtomsEnd() - const_cast<Fragment&>(frag4).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag4).getAtomsEnd() - const_cast<const Fragment&>(frag4).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag4).getBondsBegin() != const_cast<Fragment&>(frag4).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag4).getBondsBegin() != const_cast<const Fragment&>(frag4).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag4).getBondsEnd() - const_cast<Fragment&>(frag4).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag4).getBondsEnd() - const_cast<const Fragment&>(frag4).getBondsBegin() == 5);

	BOOST_CHECK(&frag4.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag4.getAtom(1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag4.getAtom(2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag4.getAtom(3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag4.getAtom(4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag4.getAtom(5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag4.getAtom(6), IndexError);

	BOOST_CHECK(&frag4.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag4.getBond(1) == &mol2.getBond(1));
	BOOST_CHECK(&frag4.getBond(2) == &mol2.getBond(2));
	BOOST_CHECK(&frag4.getBond(3) == &mol2.getBond(3));
	BOOST_CHECK(&frag4.getBond(4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag4.getBond(5), IndexError);

	BOOST_CHECK_THROW(frag4.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag4.getNumProperties() == 0);

//-----

	Fragment frag5;

	frag5 += Fragment();

	BOOST_CHECK(frag5.getNumAtoms() == 0);
	BOOST_CHECK(frag5.getNumBonds() == 0);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() == const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() == const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() == const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() == const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK_THROW(frag5.getAtom(0), IndexError);
	BOOST_CHECK_THROW(frag5.getAtom(1), IndexError);

	BOOST_CHECK_THROW(frag5.getBond(0), IndexError);
	BOOST_CHECK_THROW(frag5.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag5.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(frag5.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(frag5.removeBond(0), IndexError);
	BOOST_CHECK_THROW(frag5.removeBond(1), IndexError);

	BOOST_CHECK_THROW(frag5.removeAtom(frag5.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(frag5.removeBond(frag5.getBondsBegin()), RangeError);

	BOOST_CHECK_THROW(frag5.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	frag5 += Molecule();

	BOOST_CHECK(frag5.getNumAtoms() == 0);
	BOOST_CHECK(frag5.getNumBonds() == 0);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() == const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() == const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() == const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() == const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK_THROW(frag5.getAtom(0), IndexError);
	BOOST_CHECK_THROW(frag5.getAtom(1), IndexError);

	BOOST_CHECK_THROW(frag5.getBond(0), IndexError);
	BOOST_CHECK_THROW(frag5.getBond(1), IndexError);

	BOOST_CHECK_THROW(frag5.removeAtom(0), IndexError);
	BOOST_CHECK_THROW(frag5.removeAtom(1), IndexError);

	BOOST_CHECK_THROW(frag5.removeBond(0), IndexError);
	BOOST_CHECK_THROW(frag5.removeBond(1), IndexError);

	BOOST_CHECK_THROW(frag5.removeAtom(frag5.getAtomsBegin()), RangeError);
	BOOST_CHECK_THROW(frag5.removeBond(frag5.getBondsBegin()), RangeError);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	frag5 += frag3;
	
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag5.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag5.getNumAtoms() == 6);
	BOOST_CHECK(frag5.getNumBonds() == 5);

	checkAtomIndices(frag5);
	checkBondIndices(frag5);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() != const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() != const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsEnd() - const_cast<Fragment&>(frag5).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsEnd() - const_cast<const Fragment&>(frag5).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() != const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() != const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsEnd() - const_cast<Fragment&>(frag5).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsEnd() - const_cast<const Fragment&>(frag5).getBondsBegin() == 5);

	BOOST_CHECK(&frag5.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK_THROW(frag5.getAtom(6), IndexError);

	BOOST_CHECK(&frag5.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag5.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag5.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag5.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag5.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK_THROW(frag5.getBond(5), IndexError);

	BOOST_CHECK_THROW(frag5.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	frag5 += frag4;

	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag5.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag5.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag5.getNumAtoms() == 12);
	BOOST_CHECK(frag5.getNumBonds() == 10);

	checkAtomIndices(frag5);
	checkBondIndices(frag5);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() != const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() != const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsEnd() - const_cast<Fragment&>(frag5).getAtomsBegin() == 12);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsEnd() - const_cast<const Fragment&>(frag5).getAtomsBegin() == 12);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() != const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() != const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsEnd() - const_cast<Fragment&>(frag5).getBondsBegin() == 10);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsEnd() - const_cast<const Fragment&>(frag5).getBondsBegin() == 10);

	BOOST_CHECK(&frag5.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK(&frag5.getAtom(6 + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(6 + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(6 + 2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(6 + 3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(6 + 4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(6 + 5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag5.getAtom(12), IndexError);

	BOOST_CHECK(&frag5.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag5.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag5.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag5.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag5.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK(&frag5.getBond(5 + 0) == &mol2.getBond(0));
	BOOST_CHECK(&frag5.getBond(5 + 1) == &mol2.getBond(1));
	BOOST_CHECK(&frag5.getBond(5 + 2) == &mol2.getBond(2));
	BOOST_CHECK(&frag5.getBond(5 + 3) == &mol2.getBond(3));
	BOOST_CHECK(&frag5.getBond(5 + 4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag5.getBond(10), IndexError);

	BOOST_CHECK_THROW(frag5.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	frag5 += mol2;

	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag5.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag5.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag5.getNumAtoms() == 12);
	BOOST_CHECK(frag5.getNumBonds() == 10);

	checkAtomIndices(frag5);
	checkBondIndices(frag5);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() != const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() != const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsEnd() - const_cast<Fragment&>(frag5).getAtomsBegin() == 12);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsEnd() - const_cast<const Fragment&>(frag5).getAtomsBegin() == 12);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() != const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() != const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsEnd() - const_cast<Fragment&>(frag5).getBondsBegin() == 10);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsEnd() - const_cast<const Fragment&>(frag5).getBondsBegin() == 10);

	BOOST_CHECK(&frag5.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK(&frag5.getAtom(6 + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(6 + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(6 + 2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(6 + 3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(6 + 4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(6 + 5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag5.getAtom(12), IndexError);

	BOOST_CHECK(&frag5.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag5.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag5.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag5.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag5.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK(&frag5.getBond(5 + 0) == &mol2.getBond(0));
	BOOST_CHECK(&frag5.getBond(5 + 1) == &mol2.getBond(1));
	BOOST_CHECK(&frag5.getBond(5 + 2) == &mol2.getBond(2));
	BOOST_CHECK(&frag5.getBond(5 + 3) == &mol2.getBond(3));
	BOOST_CHECK(&frag5.getBond(5 + 4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag5.getBond(10), IndexError);

	BOOST_CHECK_THROW(frag5.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	frag5 += frag5;

	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag5.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag5.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag5.getNumAtoms() == 12);
	BOOST_CHECK(frag5.getNumBonds() == 10);

	checkAtomIndices(frag5);
	checkBondIndices(frag5);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() != const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() != const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsEnd() - const_cast<Fragment&>(frag5).getAtomsBegin() == 12);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsEnd() - const_cast<const Fragment&>(frag5).getAtomsBegin() == 12);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() != const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() != const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsEnd() - const_cast<Fragment&>(frag5).getBondsBegin() == 10);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsEnd() - const_cast<const Fragment&>(frag5).getBondsBegin() == 10);

	BOOST_CHECK(&frag5.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK(&frag5.getAtom(6 + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(6 + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(6 + 2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(6 + 3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(6 + 4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(6 + 5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag5.getAtom(12), IndexError);

	BOOST_CHECK(&frag5.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag5.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag5.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag5.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag5.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK(&frag5.getBond(5 + 0) == &mol2.getBond(0));
	BOOST_CHECK(&frag5.getBond(5 + 1) == &mol2.getBond(1));
	BOOST_CHECK(&frag5.getBond(5 + 2) == &mol2.getBond(2));
	BOOST_CHECK(&frag5.getBond(5 + 3) == &mol2.getBond(3));
	BOOST_CHECK(&frag5.getBond(5 + 4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag5.getBond(10), IndexError);

	BOOST_CHECK_THROW(frag5.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	frag5 += mol1;

	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol1.getAtom(5)));

	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag5.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag5.containsBond(mol1.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol1.getBond(4)));

	BOOST_CHECK(frag5.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag5.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag5.getNumAtoms() == 12);
	BOOST_CHECK(frag5.getNumBonds() == 10);

	checkAtomIndices(frag5);
	checkBondIndices(frag5);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsBegin() != const_cast<Fragment&>(frag5).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsBegin() != const_cast<const Fragment&>(frag5).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getAtomsEnd() - const_cast<Fragment&>(frag5).getAtomsBegin() == 12);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getAtomsEnd() - const_cast<const Fragment&>(frag5).getAtomsBegin() == 12);

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsBegin() != const_cast<Fragment&>(frag5).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsBegin() != const_cast<const Fragment&>(frag5).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag5).getBondsEnd() - const_cast<Fragment&>(frag5).getBondsBegin() == 10);
	BOOST_CHECK(const_cast<const Fragment&>(frag5).getBondsEnd() - const_cast<const Fragment&>(frag5).getBondsBegin() == 10);

	BOOST_CHECK(&frag5.getAtom(0) == &mol1.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(1) == &mol1.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(2) == &mol1.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(3) == &mol1.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(4) == &mol1.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(5) == &mol1.getAtom(5));

	BOOST_CHECK(&frag5.getAtom(6 + 0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag5.getAtom(6 + 1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag5.getAtom(6 + 2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag5.getAtom(6 + 3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag5.getAtom(6 + 4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag5.getAtom(6 + 5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag5.getAtom(12), IndexError);

	BOOST_CHECK(&frag5.getBond(0) == &mol1.getBond(0));
	BOOST_CHECK(&frag5.getBond(1) == &mol1.getBond(1));
	BOOST_CHECK(&frag5.getBond(2) == &mol1.getBond(2));
	BOOST_CHECK(&frag5.getBond(3) == &mol1.getBond(3));
	BOOST_CHECK(&frag5.getBond(4) == &mol1.getBond(4));

	BOOST_CHECK(&frag5.getBond(5 + 0) == &mol2.getBond(0));
	BOOST_CHECK(&frag5.getBond(5 + 1) == &mol2.getBond(1));
	BOOST_CHECK(&frag5.getBond(5 + 2) == &mol2.getBond(2));
	BOOST_CHECK(&frag5.getBond(5 + 3) == &mol2.getBond(3));
	BOOST_CHECK(&frag5.getBond(5 + 4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag5.getBond(10), IndexError);

	BOOST_CHECK_THROW(frag5.getProperty<std::string>(key), CalculationFailed);

	BOOST_CHECK(frag5.getNumProperties() == 0);

//-----

	Fragment frag6;

	frag6 += mol2;

	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag6.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag6.getNumAtoms() == 6);
	BOOST_CHECK(frag6.getNumBonds() == 5);

	checkAtomIndices(frag6);
	checkBondIndices(frag6);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getAtomsBegin() != const_cast<Fragment&>(frag6).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getAtomsBegin() != const_cast<const Fragment&>(frag6).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag6).getAtomsEnd() - const_cast<Fragment&>(frag6).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getAtomsEnd() - const_cast<const Fragment&>(frag6).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getBondsBegin() != const_cast<Fragment&>(frag6).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getBondsBegin() != const_cast<const Fragment&>(frag6).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag6).getBondsEnd() - const_cast<Fragment&>(frag6).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getBondsEnd() - const_cast<const Fragment&>(frag6).getBondsBegin() == 5);

	BOOST_CHECK(&frag6.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag6.getAtom(1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag6.getAtom(2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag6.getAtom(3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag6.getAtom(4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag6.getAtom(5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag6.getAtom(6), IndexError);

	BOOST_CHECK(&frag6.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag6.getBond(1) == &mol2.getBond(1));
	BOOST_CHECK(&frag6.getBond(2) == &mol2.getBond(2));
	BOOST_CHECK(&frag6.getBond(3) == &mol2.getBond(3));
	BOOST_CHECK(&frag6.getBond(4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag6.getBond(5), IndexError);

	BOOST_CHECK_THROW(frag6.getProperty<std::string>(key), CalculationFailed);

//-----

	frag6 += Molecule();
	frag6 += Fragment();

	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(0)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(1)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(2)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(3)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(4)));
	BOOST_CHECK(frag6.containsAtom(mol2.getAtom(5)));

	BOOST_CHECK(frag6.containsBond(mol2.getBond(0)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(1)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(2)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(3)));
	BOOST_CHECK(frag6.containsBond(mol2.getBond(4)));

	BOOST_CHECK(frag6.getNumAtoms() == 6);
	BOOST_CHECK(frag6.getNumBonds() == 5);

	checkAtomIndices(frag6);
	checkBondIndices(frag6);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getAtomsBegin() != const_cast<Fragment&>(frag6).getAtomsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getAtomsBegin() != const_cast<const Fragment&>(frag6).getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag6).getAtomsEnd() - const_cast<Fragment&>(frag6).getAtomsBegin() == 6);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getAtomsEnd() - const_cast<const Fragment&>(frag6).getAtomsBegin() == 6);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getBondsBegin() != const_cast<Fragment&>(frag6).getBondsEnd());
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getBondsBegin() != const_cast<const Fragment&>(frag6).getBondsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag6).getBondsEnd() - const_cast<Fragment&>(frag6).getBondsBegin() == 5);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getBondsEnd() - const_cast<const Fragment&>(frag6).getBondsBegin() == 5);

	BOOST_CHECK(&frag6.getAtom(0) == &mol2.getAtom(0));
	BOOST_CHECK(&frag6.getAtom(1) == &mol2.getAtom(1));
	BOOST_CHECK(&frag6.getAtom(2) == &mol2.getAtom(2));
	BOOST_CHECK(&frag6.getAtom(3) == &mol2.getAtom(3));
	BOOST_CHECK(&frag6.getAtom(4) == &mol2.getAtom(4));
	BOOST_CHECK(&frag6.getAtom(5) == &mol2.getAtom(5));

	BOOST_CHECK_THROW(frag6.getAtom(6), IndexError);

	BOOST_CHECK(&frag6.getBond(0) == &mol2.getBond(0));
	BOOST_CHECK(&frag6.getBond(1) == &mol2.getBond(1));
	BOOST_CHECK(&frag6.getBond(2) == &mol2.getBond(2));
	BOOST_CHECK(&frag6.getBond(3) == &mol2.getBond(3));
	BOOST_CHECK(&frag6.getBond(4) == &mol2.getBond(4));

	BOOST_CHECK_THROW(frag6.getBond(5), IndexError);

	BOOST_CHECK_THROW(frag6.getProperty<std::string>(key), CalculationFailed);

//-----

	BOOST_CHECK(frag6.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_ATOM_COUNT) == 20);
	BOOST_CHECK(frag6.getProperty<std::size_t>(MolecularGraphProperty::TOTAL_BOND_COUNT) == 19);
	BOOST_CHECK(frag6.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 6);
	BOOST_CHECK(frag6.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 5);

	frag6.removeBond(0);

	BOOST_CHECK(frag6.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 6);
	BOOST_CHECK(frag6.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 4);

	frag6.removeAtom(0);

	BOOST_CHECK(frag6.getProperty<std::size_t>(AtomContainerProperty::ATOM_COUNT) == 5);
	BOOST_CHECK(frag6.getProperty<std::size_t>(BondContainerProperty::BOND_COUNT) == 4);

//-----

	frag6.clear();

	BOOST_CHECK(frag6.getNumAtoms() == 0);
	BOOST_CHECK(frag6.getNumBonds() == 0);

	BOOST_CHECK(frag6.addAtom(mol1.getAtom(0)));
	BOOST_CHECK(frag6.addAtom(mol1.getAtom(1)));
	BOOST_CHECK(frag6.addAtom(mol1.getAtom(2)));
	BOOST_CHECK(!frag6.addAtom(mol1.getAtom(0)));

	BOOST_CHECK(frag6.addBond(mol1.getBond(1)));
	BOOST_CHECK(frag6.addBond(mol1.getBond(0)));
	BOOST_CHECK(!frag6.addBond(mol1.getBond(1)));
	BOOST_CHECK(frag6.addBond(mol1.getBond(2)));

	BOOST_CHECK(frag6.getNumAtoms() == 4);
	BOOST_CHECK(frag6.getNumBonds() == 3);

	checkAtomIndices(frag6);
	checkBondIndices(frag6);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getBondsEnd() - const_cast<Fragment&>(frag6).getBondsBegin() == 3);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getBondsEnd() - const_cast<const Fragment&>(frag6).getBondsBegin() == 3);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getAtomsEnd() - const_cast<Fragment&>(frag6).getAtomsBegin() == 4);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getAtomsEnd() - const_cast<const Fragment&>(frag6).getAtomsBegin() == 4);

	a_it = frag6.removeAtom(frag6.getAtomsBegin());

	BOOST_CHECK(a_it == frag6.getAtomsBegin());

	a_it = frag6.removeAtom(frag6.getAtomsBegin() + 1);

	BOOST_CHECK(a_it == frag6.getAtomsBegin() + 1);

	a_it = frag6.removeAtom(--frag6.getAtomsEnd());

	BOOST_CHECK(a_it == frag6.getAtomsEnd());

	BOOST_CHECK(const_cast<Fragment&>(frag6).getBondsEnd() - const_cast<Fragment&>(frag6).getBondsBegin() == 0);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getBondsEnd() - const_cast<const Fragment&>(frag6).getBondsBegin() == 0);

	BOOST_CHECK(const_cast<Fragment&>(frag6).getAtomsEnd() - const_cast<Fragment&>(frag6).getAtomsBegin() == 1);
	BOOST_CHECK(const_cast<const Fragment&>(frag6).getAtomsEnd() - const_cast<const Fragment&>(frag6).getAtomsBegin() == 1);

	BOOST_CHECK(frag6.getNumAtoms() == 1);
	BOOST_CHECK(frag6.getNumBonds() == 0);
}
