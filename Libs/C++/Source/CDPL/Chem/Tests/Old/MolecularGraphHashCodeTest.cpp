/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphHashCodeTest.cpp 
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
#include <cstdlib>
#include <fstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/AtomPropertyFlags.hpp"
#include "CDPL/Chem/BondPropertyFlags.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"
#include "CDPL/Chem/AtomContainerProperties.hpp"
#include "CDPL/Chem/BondContainerProperties.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/ControlParameters.hpp"
#include "CDPL/Chem/AtomStereoDescriptors.hpp"
#include "CDPL/Chem/BondStereoDescriptors.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/PropertyKey.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/IntTypes.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataReader.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MolecularGraphHashCodeTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	const char* molecule_names[] = {
		"Cis-14-Dimethylcyclohexane1.jme",
		"Cis-14-Dimethylcyclohexane2.jme",
		"Trans-14-Dimethylcyclohexane1.jme",
		"Trans-14-Dimethylcyclohexane2.jme",
		"Cis-14-Diethylenecyclohexane.jme",
		"Trans-14-Diethylenecyclohexane.jme",
		"Hexamethylcyclohexane1.jme",
		"Hexamethylcyclohexane2.jme",
		"Hexamethylcyclohexane3.jme",
		"Morphine.jme",
		"MorphineStereoisomer.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"13-Dimethylcyclohexane.jme",
		"Trimethylcyclobutane1.mol",
		"Trimethylcyclobutane2.mol",
	};

	struct HashCodeTestInfo 
	{
		
		std::size_t  object1Idx;
		std::size_t  object2Idx;
		unsigned int atomFlags;
		unsigned int bondFlags;
		bool         globalStereo;
		bool         ordinaryHDeplete;
		bool         expectedTestResult;
	};

	HashCodeTestInfo mol_hash_test_infos[] = {
		{ 0, 1, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, true },
		{ 0, 1, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 0, 2, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  false, true, true },
		{ 2, 3, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, true },
		{ 2, 3, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 0, 3, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, false },
		{ 4, 5, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, false },
		{ 6, 7, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, false },
		{ 6, 7, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  false, true, true },
		{ 6, 8, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, true },
		{ 9, 10, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, false },
		{ 9, 10, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  /*AtomPropertyFlag::CIP_CONFIGURATION |*/ AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, true },

		{ 11, 12, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },
		{ 11, 12, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION /*| AtomPropertyFlag::AROMATICITY*/,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },
	
		{ 11, 13, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 13, 
		  /*AtomPropertyFlag::TYPE |*/ AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },

		{ 11, 14, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 14, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 14, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |*/
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },
		
		{ 11, 15, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 15, 
		  AtomPropertyFlag::TYPE | /*AtomPropertyFlag::ISOTOPE |*/ 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },

		{ 11, 16, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 16, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  /*AtomPropertyFlag::CIP_CONFIGURATION |*/ AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },

		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, false },
		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY/* | BondPropertyFlag::CIP_CONFIGURATION*/,
		  true, false, false },
		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  /*BondPropertyFlag::ORDER |*/ BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY/* | BondPropertyFlag::CIP_CONFIGURATION*/,
		  true, false, true },

		{ 11, 18, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },
		{ 11, 18, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  /*BondPropertyFlag::AROMATICITY |*/ BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },

		{ 11, 19, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },
		{ 11, 19, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY /*| BondPropertyFlag::CIP_CONFIGURATION*/,
		  true, false, true },

		{ 11, 20, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },
		{ 11, 20, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | /*BondPropertyFlag::TOPOLOGY |*/ 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, false, true },

		{ 21, 22, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION,
		  true, true, true },
	}; 

	const std::size_t num_molecules = sizeof(molecule_names) / sizeof(const char*);

	Molecule molecules[num_molecules];

	ControlParameterList::SharedPointer cpl(new ControlParameterList());

	std::string data_dir(std::getenv("CDPKIT_TEST_DATA_DIR"));
	data_dir.push_back('/');

	for (std::size_t i = 0; i < num_molecules; i++) {
		std::string mol_name(molecule_names[i]);
		std::ifstream ifs((data_dir + mol_name).c_str());

		BOOST_CHECK(ifs);

		std::string file_ext = mol_name.substr(mol_name.rfind('.') + 1);
		const Base::DataInputHandler<Molecule>* handler = Base::DataIOManager<Molecule>::getInputHandlerByFileExtension(file_ext);

		BOOST_CHECK(handler != 0);

		std::auto_ptr<Base::DataReader<Molecule> > reader_ptr(handler->createReader(ifs));
		
		BOOST_CHECK(reader_ptr.get() != 0);
		BOOST_CHECK(reader_ptr->read(molecules[i]));
	}
	
	Base::uint64 empty_hash = Molecule().getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE);
	
	molecules[12].getAtom(0).setProperty(AtomProperty::IS_AROMATIC, true);
	molecules[13].getAtom(0).setProperty(AtomProperty::SYMBOL, std::string("Si"));
	molecules[14].getAtom(0).setProperty(AtomProperty::FORMAL_CHARGE, long(1));
	molecules[15].getAtom(0).setProperty(AtomProperty::ISOTOPE, std::size_t(13));
	
	for (Molecule::AtomIterator it = molecules[16].getAtomsBegin(), end = molecules[16].getAtomsEnd(); it != end; ++it)
		if (it->getNumBonds() > 2)
			it->setProperty(AtomProperty::PARITY, AtomParity::EVEN);

	molecules[17].getBond(0).setProperty(BondProperty::ORDER, std::size_t(2));
	molecules[18].getBond(0).setProperty(BondProperty::IS_AROMATIC, true);

	for (Molecule::BondIterator it = molecules[19].getBondsBegin(), end = molecules[19].getBondsEnd(); it != end; ++it)
		it->setProperty(BondProperty::GEOMETRY, BondGeometry::TRANS);

	molecules[20].getBond(0).setProperty(BondProperty::IN_RING, false);

	//-----

	for (std::size_t i = 0; i < sizeof(mol_hash_test_infos) / sizeof(HashCodeTestInfo); i++) {
		const HashCodeTestInfo& test_info = mol_hash_test_infos[i];
		Molecule& mol1 = molecules[test_info.object1Idx];
		Molecule& mol2 = molecules[test_info.object2Idx];

		Fragment frag(mol2);

		cpl->setParameter(ControlParameter::ATOM_PROPERTY_FLAGS, test_info.atomFlags);
		cpl->setParameter(ControlParameter::BOND_PROPERTY_FLAGS, test_info.bondFlags);
		cpl->setParameter(ControlParameter::ORDINARY_HYDROGEN_DEPLETE, test_info.ordinaryHDeplete);
		cpl->setParameter(ControlParameter::GLOBAL_STEREOCHEMISTRY, test_info.globalStereo);

		mol1.setProperty(MolecularGraphProperty::HASH_CODE_PARAMETERS, cpl);
		frag.setProperty(MolecularGraphProperty::HASH_CODE_PARAMETERS, cpl);

		Base::uint64 hash1 = mol1.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE);
		Base::uint64 hash2 = frag.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE);

		BOOST_CHECK(hash1 != empty_hash);
		BOOST_CHECK(hash2 != empty_hash);

		mol1.removeProperty(MolecularGraphProperty::HASH_CODE);
		frag.removeProperty(MolecularGraphProperty::HASH_CODE);

		BOOST_CHECK_THROW(mol1.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE, false), Base::ItemNotFound);
		BOOST_CHECK_THROW(frag.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE, false), Base::ItemNotFound);

		BOOST_CHECK((hash1 == hash2) == test_info.expectedTestResult);

		cpl->setParameter(ControlParameter::ATOM_PROPERTY_FLAGS, HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS);
		cpl->setParameter(ControlParameter::BOND_PROPERTY_FLAGS, HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS);
		cpl->setParameter(ControlParameter::ORDINARY_HYDROGEN_DEPLETE, true);
		cpl->setParameter(ControlParameter::GLOBAL_STEREOCHEMISTRY, true);

		mol1.removeProperty(MolecularGraphProperty::HASH_CODE_PARAMETERS);

		hash2 = mol1.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE);

		mol1.setProperty(MolecularGraphProperty::HASH_CODE_PARAMETERS, cpl);

		hash1 = mol1.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE);

		BOOST_CHECK(hash1 == hash2);

		frag.removeProperty(MolecularGraphProperty::HASH_CODE);

		//-----

		Molecule::AtomIterator atoms_end = mol2.getAtomsEnd();

		for (Molecule::AtomIterator it = mol2.getAtomsBegin(); it != atoms_end; ++it) {
			Atom& atom = *it;

			if (!frag.containsAtom(atom))
				continue;

			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::TYPE);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::ISOTOPE);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::FORMAL_CHARGE);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::TOTAL_VALENCE);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::UNPAIRED_VALENCE_ELECTRON_COUNT);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::PARITY);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::CIP_CONFIGURATION);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::TOTAL_H_COUNT);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, AtomProperty::IS_AROMATIC);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, atom, BondContainerProperty::BOND_COUNT);
		}

		Molecule::BondIterator bonds_end = mol2.getBondsEnd();

		for (Molecule::BondIterator it = mol2.getBondsBegin(); it != bonds_end; ++it) {
			Bond& bond = *it;

			if (!frag.containsBond(bond))
				continue;

			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, bond, BondProperty::ORDER);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, bond, BondProperty::GEOMETRY);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, bond, BondProperty::CIP_CONFIGURATION);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, bond, BondProperty::IN_RING);
			TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, bond, BondProperty::IS_AROMATIC);
		}

		TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, frag, MolecularGraphProperty::TOPOLOGICAL_CIP_PRIORITIES);
		TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, frag, MolecularGraphProperty::AROMATIC_SUBSTRUCTURE);
		TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, frag, MolecularGraphProperty::SSSR);
		TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, frag, AtomContainerProperty::ATOM_COUNT);
		TestUtils::checkDependency(frag, MolecularGraphProperty::HASH_CODE, frag, BondContainerProperty::BOND_COUNT);
	}
}
