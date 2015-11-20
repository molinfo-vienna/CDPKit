/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HashCodeCalculatorTest.cpp 
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
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomPropertyFlags.hpp"
#include "CDPL/Chem/BondPropertyFlags.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/BondProperties.hpp"
#include "CDPL/Chem/AtomStereoDescriptors.hpp"
#include "CDPL/Chem/BondStereoDescriptors.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Util/Permutation.hpp"
#include "CDPL/Util/AddressOf.hpp"
#include "CDPL/Util/Dereferencer.hpp"


BOOST_AUTO_TEST_CASE(HashCodeCalculatorTest)
{
	using namespace CDPL;
	using namespace Chem;

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
		bool         fragMolEquality1;
		bool         fragMolEquality2;
	};

	HashCodeTestInfo mol_hash_test_infos[] = {
		{ 0, 1, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, true, true, true },
		{ 0, 1, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 0, 2, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  false, true, true, true, true },
		{ 2, 3, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, true, true, true },
		{ 2, 3, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 0, 3, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, false, true, true },
		{ 4, 5, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, false, true, true },
		{ 6, 7, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, false, true, true },
		{ 6, 7, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  false, true, true, true, true },
		{ 6, 8, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, true, true, true },
		{ 9, 10, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, false, true, true },
		{ 9, 10, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  /*AtomPropertyFlag::CONFIGURATION |*/ AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, true, true, true },

		{ 11, 12, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, false },
		{ 11, 12, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION /*| AtomPropertyFlag::AROMATICITY*/,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },
	
		{ 11, 13, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 13, 
		  /*AtomPropertyFlag::TYPE |*/ AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },

		{ 11, 14, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 14, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 14, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |*/
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },
		
		{ 11, 15, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 15, 
		  AtomPropertyFlag::TYPE | /*AtomPropertyFlag::ISOTOPE |*/ 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },

		{ 11, 16, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 16, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  /*AtomPropertyFlag::CONFIGURATION |*/ AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },

		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, false, true, true },
		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY/* | BondPropertyFlag::CONFIGURATION*/,
		  true, false, false, true, true },
		{ 11, 17, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  /*AtomPropertyFlag::H_COUNT |*/ AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  /*BondPropertyFlag::ORDER |*/ BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY/* | BondPropertyFlag::CONFIGURATION*/,
		  true, false, true, true, true },

		{ 11, 18, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, false },
		{ 11, 18, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  /*BondPropertyFlag::AROMATICITY |*/ BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },

		{ 11, 19, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },
		{ 11, 19, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY /*| BondPropertyFlag::CONFIGURATION*/,
		  true, false, true, true, true },

		{ 11, 20, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | 
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },
		{ 11, 20, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | /*BondPropertyFlag::TOPOLOGY |*/ 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, false, true, true, true },

		{ 21, 22, 
		  AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
		  AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
		  AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY,
		  BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
		  BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION,
		  true, true, true, true, true },
	}; 

	const std::size_t num_molecules = sizeof(molecule_names) / sizeof(const char*);

	Molecule molecules[num_molecules];

	std::string data_dir(std::getenv("CDPTK_DATA_DIR"));
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

	std::vector<const Atom*> atoms;
	std::vector<const Bond*> bonds;

	for (std::size_t i = 0; i < sizeof(mol_hash_test_infos) / sizeof(HashCodeTestInfo); i++) {
		const HashCodeTestInfo& test_info = mol_hash_test_infos[i];

		Molecule& mol1 = molecules[test_info.object1Idx];
		Molecule& mol2 = molecules[test_info.object2Idx];

		Fragment frag1;
		Fragment frag2;

		HashCodeCalculator hcc;
				
		hcc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hcc, test_info.atomFlags));
		hcc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hcc, test_info.bondFlags));

		hcc.includeGlobalStereoFeatures(test_info.globalStereo);

		BOOST_CHECK(hcc.globalStereoFeaturesIncluded() == test_info.globalStereo);

		for (std::size_t j = 0; j < 2; j++) {
			Fragment& frag = (j == 0 ? frag1 : frag2);
			Molecule& mol = (j == 0 ? mol1 : mol2);
			bool result = (j == 0 ? test_info.fragMolEquality1 : test_info.fragMolEquality2);

			atoms.clear();
			bonds.clear();

			std::transform(mol.getAtomsBegin(), mol.getAtomsEnd(), std::back_inserter(atoms),
						   boost::bind(Util::AddressOf<const Atom>(), _1));
			std::transform(mol.getBondsBegin(), mol.getBondsEnd(), std::back_inserter(bonds),
						   boost::bind(Util::AddressOf<const Bond>(), _1));

			for (std::size_t k = 0; k < i + 10; k++) {
				Util::nextPermutation(atoms.begin(), atoms.end());
				Util::nextPermutation(bonds.begin(), bonds.end());
		
				frag.clear();

				std::for_each(atoms.begin(), atoms.end(), 
							  boost::bind(&Fragment::addAtom, boost::ref(frag),
										  boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1)));
				
				std::for_each(bonds.begin(), bonds.end(), 
							  boost::bind(&Fragment::addBond, boost::ref(frag),
										  boost::bind(Util::Dereferencer<const Bond*, const Bond&>(), _1)));

				BOOST_CHECK(frag.getNumAtoms() == mol.getNumAtoms());
				BOOST_CHECK(frag.getNumBonds() == mol.getNumBonds());

				BOOST_CHECK((hcc.calculate(frag) == hcc.calculate(mol)) == result);
			}
		}

		BOOST_CHECK(frag1.getNumAtoms() == mol1.getNumAtoms());
		BOOST_CHECK(frag1.getNumBonds() == mol1.getNumBonds());

		BOOST_CHECK(frag2.getNumAtoms() == mol2.getNumAtoms());
		BOOST_CHECK(frag2.getNumBonds() == mol2.getNumBonds());

		if (test_info.ordinaryHDeplete) {
			makeOrdinaryHydrogenDeplete(frag1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::ISOTOPE |
										AtomPropertyFlag::H_COUNT);
			makeOrdinaryHydrogenDeplete(frag2, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::ISOTOPE |
										AtomPropertyFlag::H_COUNT);
		}

		Base::uint64 hash1 = hcc.calculate(frag1);

		BOOST_CHECK(hcc.calculate(frag1) == hash1);
		BOOST_CHECK(hcc.getResult() == hash1);

		BOOST_CHECK(hcc.calculate(Fragment(frag1)) == hash1);
		BOOST_CHECK(hcc.getResult() == hash1);

		BOOST_CHECK(hcc.globalStereoFeaturesIncluded() == test_info.globalStereo);

		Base::uint64 hash2 = hcc.calculate(frag2);

		BOOST_CHECK(hcc.calculate(frag2) == hash2);
		BOOST_CHECK(hcc.getResult() == hash2);

		BOOST_CHECK(hcc.calculate(Fragment(frag2)) == hash2);
		BOOST_CHECK(hcc.getResult() == hash2);

		BOOST_CHECK((hash1 == hash2) == test_info.expectedTestResult);
	}

	//-----

	HashCodeCalculator hcc1;

	BOOST_CHECK(hcc1.getResult() == 0);

	BOOST_CHECK(hcc1.globalStereoFeaturesIncluded() == true);

	//-----

	Molecule mol1, mol2;

	Base::uint64 hash1 = hcc1.calculate(mol1);

	BOOST_CHECK(hash1 != 0);
	BOOST_CHECK(hcc1.calculate(mol1) == hash1);

	//-----

	HashCodeCalculator hcc2(mol2);

	Base::uint64 hash2 = hcc2.getResult();

	BOOST_CHECK(hash2 == hash1);

	BOOST_CHECK(hcc2.calculate(mol1) == hash1);

	BOOST_CHECK(hcc2.globalStereoFeaturesIncluded() == true);

	//-----

	Fragment frag1, frag2;

	Base::uint64 hash5 = hcc1.calculate(frag1);

	BOOST_CHECK(hash5 == hash1);

	BOOST_CHECK(hcc1.calculate(frag1) == hash5);

	//-----

	HashCodeCalculator hcc4(frag2);

	Base::uint64 hash6 = hcc4.getResult();

	BOOST_CHECK(hash6 == hash5);

	BOOST_CHECK(hcc4.calculate(frag1) == hash5);

	BOOST_CHECK(hcc4.globalStereoFeaturesIncluded() == true);

	//-----

	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();

	mol1.addBond(0, 1).setProperty(BondProperty::ORDER, std::size_t(1));
	mol1.addBond(1, 2).setProperty(BondProperty::ORDER, std::size_t(1));

	Base::uint64 hash7 = hcc4.calculate(mol1);

	BOOST_CHECK(hash7 != hash5);
	BOOST_CHECK(hcc4.calculate(mol1) == hash7);

	hash7 = hcc4.calculate(frag1);

	BOOST_CHECK(hash7 == hash5);
	BOOST_CHECK(hash5 == hash1);

	BOOST_CHECK(hcc4.calculate(frag1) == hash5);

	//-----

	mol1.addBond(0, 0).setProperty(BondProperty::ORDER, std::size_t(1));

	mol2 = mol1;
	
	frag1 = mol1;
	frag1 += mol2;
	frag1 += molecules[0];

	Molecule mol3(mol1);

	mol3 += mol2;
	mol3 += molecules[0];

	BOOST_CHECK(frag1.getNumAtoms() == mol3.getNumAtoms());
	BOOST_CHECK(frag1.getNumBonds() == mol3.getNumBonds());

	BOOST_CHECK(hcc4.calculate(frag1) == hcc4.calculate(mol3));
	
	frag1.removeBond(2);

	BOOST_CHECK(frag1.getNumAtoms() == mol3.getNumAtoms());
	BOOST_CHECK(frag1.getNumBonds() != mol3.getNumBonds());

	BOOST_CHECK(hcc4.calculate(frag1) != hcc4.calculate(mol3));

	mol3.removeBond(2);

	BOOST_CHECK(frag1.getNumAtoms() == mol3.getNumAtoms());
	BOOST_CHECK(frag1.getNumBonds() == mol3.getNumBonds());

	BOOST_CHECK(hcc4.calculate(frag1) == hcc4.calculate(mol3));

	//-----

	frag1 = molecules[0];
	frag2 = molecules[2];

	makeOrdinaryHydrogenDeplete(frag1, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::ISOTOPE |
								AtomPropertyFlag::H_COUNT);
	makeOrdinaryHydrogenDeplete(frag2, AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::ISOTOPE |
								AtomPropertyFlag::H_COUNT);

	hcc1.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hcc1));
	hcc1.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hcc1));

	BOOST_CHECK(hcc1.globalStereoFeaturesIncluded() == true);

	hcc2.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hcc2, HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS));
	hcc2.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hcc2, HashCodeCalculator::DEF_BOND_PROPERTY_FLAGS));

	BOOST_CHECK(hcc2.globalStereoFeaturesIncluded() == true);

	BOOST_CHECK(hcc1.calculate(frag1) != hcc2.calculate(frag2));

	//-----	

	hcc1.includeGlobalStereoFeatures(false);

	BOOST_CHECK(hcc1.globalStereoFeaturesIncluded() == false);

	BOOST_CHECK(hcc1.calculate(frag1) != hcc2.calculate(frag2));

	hcc2.includeGlobalStereoFeatures(false);

	BOOST_CHECK(hcc2.globalStereoFeaturesIncluded() == false);

	BOOST_CHECK(hcc1.calculate(frag1) == hcc2.calculate(frag2));

	//-----	

	hcc1.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hcc1, AtomPropertyFlag::TYPE));

	BOOST_CHECK(hcc1.globalStereoFeaturesIncluded() == false);

	BOOST_CHECK(hcc1.calculate(frag1) != hcc2.calculate(frag2));
}
