/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyFunctionsTest.cpp 
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


#include <sstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/AtomPropertyFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomTypes.hpp"
#include "CDPL/Chem/HybridizationStates.hpp"
#include "CDPL/Chem/AtomPropertyFlags.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"


using namespace CDPL;
using namespace Chem;


namespace
{

	struct HybrTestDataEntry
	{

		const char*  atomEnvironment;
		unsigned int expectedHybrState;
	};

	HybrTestDataEntry hybrTestData[] = {
		{ "C",             HybridizationState::SP3   },
		{ "CC",            HybridizationState::SP3   },
		{ "C(F)(Cl)",      HybridizationState::SP3   },
		{ "C(C)(C)*",      HybridizationState::SP3   },
		{ "C(H)(-N)(O)Cl", HybridizationState::SP3   },
		{ "C(H)(-N)(O)Cl", HybridizationState::SP3   },
		{ "[C+]",          HybridizationState::UNKNOWN },

		{ "C=*",            HybridizationState::SP2   },
		{ "C(-H)=N",        HybridizationState::SP2   },
		{ "C(-Cl)(*)=*",    HybridizationState::SP2   },
		{ "C(=N)(-C)(-Cl)", HybridizationState::SP2   },
		{ "[C+]=N",         HybridizationState::UNKNOWN },

		{ "C#N",     HybridizationState::SP    },
		{ "C(=C)=N", HybridizationState::SP    },
		{ "[C]=O",   HybridizationState::SP    },
		{ "[C-]#O",  HybridizationState::SP    },
		{ "C(#O)=C", HybridizationState::UNKNOWN },

		{ "B",            HybridizationState::SP2   },
		{ "[BH3]",        HybridizationState::SP2   },
		{ "B(-Cl)C",      HybridizationState::SP2   },
		{ "B(*)(F)C",     HybridizationState::SP2   },
		{ "B(*)(*)(H)Cl", HybridizationState::SP3   },
		{ "[BH4]",        HybridizationState::SP3   },
		{ "[BH2]",        HybridizationState::UNKNOWN },
		{ "[BH0+]",       HybridizationState::UNKNOWN },

		{ "[Si](C)(-H)(*)H",     HybridizationState::SP3  },
		{ "[SiH2](F)(F)(F)(F)", HybridizationState::SP3D2 },

		{ "[NH4+]",     HybridizationState::SP3 },
		{ "N",          HybridizationState::SP3 },
		{ "[NH2]Cl",    HybridizationState::SP3 },
		{ "N(C)=C",     HybridizationState::SP2 },
		{ "N#C",        HybridizationState::SP  },
		{ "N(=O)(=O)C", HybridizationState::SP2 },
		{ "[N+](C)(C)=C",  HybridizationState::SP2 },
		{ "[N+](=O)=C",    HybridizationState::SP  },

		{ "P",                  HybridizationState::SP3  },
		{ "P(O)(O)(O)=O",       HybridizationState::SP3  },
		{ "P(Cl)(Cl)(Cl)(Cl)F", HybridizationState::SP3D },

		{ "[Sb](F)(F)(F)(F)F", HybridizationState::SP3D },

		{ "O",      HybridizationState::SP3 },
		{ "O=C",    HybridizationState::SP2 },
		{ "[O+]#C", HybridizationState::SP  },

		{ "S(=O)(=O)=O",   HybridizationState::SP2  },
		{ "S(=O)(=C)(C)C", HybridizationState::SP3  },
		{ "S(=C)(C)(C)",   HybridizationState::SP3  },
		{ "S(F)F",         HybridizationState::SP3  },
		{ "S(C)(C)(C)C",   HybridizationState::SP3D },

		{ "[Cl](F)(F)F", HybridizationState::SP3D },

		{ "[I-](Cl)C",             HybridizationState::DP     },
		{ "[I](F)(F)(F)(F)(F)(F)F", HybridizationState::SP3D3 },

		{ "[Hg](Cl)Cl",         HybridizationState::SP   },
		{ "[Au](Cl)F",          HybridizationState::SP   },
		{ "[Xe](F)F",           HybridizationState::DP   },
		{ "[Cr](=O)(=O)(O)O",   HybridizationState::SD3  },
		{ "[Mn](-O)(=O)(=O)=O", HybridizationState::SD3  },
		{ "[Au](Cl)(Cl)(Cl)Cl", HybridizationState::SP2D },
		{ "[Ni](*)(*)(*)*",     HybridizationState::SP2D },
		{ "[Pt](*)(*)(*)*",     HybridizationState::SP2D },
		{ "[Ta](C)(C)(C)(C)C",  HybridizationState::SP3D },
		{ "[Te](Cl)(Cl)(Cl)(Cl)(Cl)C", HybridizationState::SP3D2 }
	};
}


BOOST_AUTO_TEST_CASE(AtomPropertyFunctionsTest)
{

	Molecule mol;

	Atom* atom1 = &mol.addAtom();
	Atom* atom2 = &mol.addAtom();

	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::TYPE, AtomType::H);

	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	Bond* bond2 = &mol.addBond(mol.getAtomIndex(*atom1), mol.getAtomIndex(*atom2));

	bond2->setProperty(BondProperty::ORDER, std::size_t(0));

	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	bond2->setProperty(BondProperty::ORDER, std::size_t(2));

	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	bond2->setProperty(BondProperty::ORDER, std::size_t(1));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom2->setProperty(AtomProperty::TYPE, AtomType::H);

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom2->setProperty(AtomProperty::TYPE, AtomType::C);

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::ISOTOPE, std::size_t(0));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::ISOTOPE, std::size_t(1));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::ISOTOPE, std::size_t(0));
	atom2->setProperty(AtomProperty::ISOTOPE, std::size_t(14));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::FORMAL_CHARGE, long(1));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::FORMAL_CHARGE, long(-2));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::FORMAL_CHARGE, long(0));
	atom2->setProperty(AtomProperty::FORMAL_CHARGE, long(-1));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::IMPLICIT_H_COUNT, std::size_t(1));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::IMPLICIT_H_COUNT, std::size_t(0));
	atom2->setProperty(AtomProperty::IMPLICIT_H_COUNT, std::size_t(1));

	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
								   AtomPropertyFlag::H_COUNT, mol));

//-------

	atom1->setProperty(AtomProperty::ISOTOPE, std::size_t(3));
	atom1->setProperty(AtomProperty::IMPLICIT_H_COUNT, std::size_t(1));
	atom1->setProperty(AtomProperty::FORMAL_CHARGE, long(-2));
	
	BOOST_CHECK(isOrdinaryHydrogen(*atom1, 0, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT, mol));
	BOOST_CHECK(!isOrdinaryHydrogen(*atom1, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | 
									AtomPropertyFlag::H_COUNT, mol));

//------- Hybridization Perception Tests

	for (std::size_t i = 0; i < sizeof(hybrTestData) / sizeof(HybrTestDataEntry); i++) {
		std::istringstream iss(hybrTestData[i].atomEnvironment);

		mol.clear();

		BOOST_CHECK(SMILESMoleculeReader(iss).read(mol));

		BOOST_CHECK(perceiveHybridization(mol.getAtom(0), mol) == hybrTestData[i].expectedHybrState);
	}
}
