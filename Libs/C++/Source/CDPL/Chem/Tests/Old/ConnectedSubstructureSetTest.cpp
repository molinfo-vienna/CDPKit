/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConnectedSubstructureSetTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/ConnectedSubstructureSet.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"


BOOST_AUTO_TEST_CASE(ConnectedSubstructureSetTest)
{
	using namespace CDPL;
	using namespace Chem;

	Molecule mol1, mol2;

	std::ifstream ifs1(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/Cis-14-Dimethylcyclohexane1.jme").c_str());

	BOOST_CHECK(ifs1);

	BOOST_CHECK(JMEMoleculeReader(ifs1).read(mol1));

	std::size_t substruct_counts[] = { 0, 9, 12, 16, 21, 28, 32, 24, 9, 1, 0 };

//-----

	ConnectedSubstructureSet substruct_set1;

	BOOST_CHECK(substruct_set1.getSize() == 0);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

	substruct_set1.findSubstructures(3);
	
	BOOST_CHECK(substruct_set1.getSize() == 0);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

	substruct_set1.findSubstructures(0);
	
	BOOST_CHECK(substruct_set1.getSize() == 0);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

//-----

	substruct_set1.reset(mol1);

	BOOST_CHECK(substruct_set1.getSize() == 0);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

	substruct_set1.findSubstructures(0);
	
	BOOST_CHECK(substruct_set1.getSize() == 0);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

	substruct_set1.findSubstructures(3);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[3]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 3);

	substruct_set1.findSubstructures(0);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[3]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

	substruct_set1.findSubstructures(5);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[3] + substruct_counts[5]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 5);

	substruct_set1.clear();

	BOOST_CHECK(substruct_set1.getSize() == 0);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 5);

	substruct_set1.findSubstructures(8);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[8]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 8);

	substruct_set1.findSubstructures(9);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[8] + substruct_counts[9]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 9);

	substruct_set1.findSubstructures(10);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[8] + substruct_counts[9]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 10);

	substruct_set1.findSubstructures(0);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[8] + substruct_counts[9]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 0);

	substruct_set1.findSubstructures(1);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[1] + substruct_counts[8] + substruct_counts[9]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 1);

	substruct_set1.clear();
	substruct_set1.findSubstructures(2);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[2]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 2);

	substruct_set1.clear();
	substruct_set1.findSubstructures(7);
	
	BOOST_CHECK(substruct_set1.getSize() == substruct_counts[7]);
	BOOST_CHECK(substruct_set1.getSubstructureSize() == 7);

//-----

	ConnectedSubstructureSet substruct_set2(mol2);

	BOOST_CHECK(substruct_set2.getSize() == 0);
	BOOST_CHECK(substruct_set2.getSubstructureSize() == 0);

	substruct_set2.findSubstructures(3);
	
	BOOST_CHECK(substruct_set2.getSize() == 0);
	BOOST_CHECK(substruct_set2.getSubstructureSize() == 3);

	substruct_set2.findSubstructures(0);
	
	BOOST_CHECK(substruct_set2.getSize() == 0);
	BOOST_CHECK(substruct_set2.getSubstructureSize() == 0);

	substruct_set2.findSubstructures(5);
	
	BOOST_CHECK(substruct_set2.getSize() == 0);
	BOOST_CHECK(substruct_set2.getSubstructureSize() == 5);

//-----

	ConnectedSubstructureSet substruct_set3(mol1);

	BOOST_CHECK(substruct_set3.getSize() == 0);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 0);

	substruct_set3.findSubstructures(3);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[3]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 3);

	substruct_set3.findSubstructures(5);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[3] + substruct_counts[5]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 5);

	substruct_set3.clear();
	substruct_set3.findSubstructures(6);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 6);

	substruct_set3.findSubstructures(1);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] + substruct_counts[1]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 1);

	substruct_set3.findSubstructures(0);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] + substruct_counts[1]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 0);

	substruct_set3.findSubstructures(4);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] + substruct_counts[1] + substruct_counts[4]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 4);

//-----

	mol2 = mol1;
	mol2 += mol2;

	Fragment frag(mol2);

	substruct_set3.reset(frag);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] + substruct_counts[1] + substruct_counts[4]);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 0);

	substruct_set3.findSubstructures(7);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] + substruct_counts[1] + substruct_counts[4] + substruct_counts[7] * 2);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 7);

	substruct_set3.clear();

	BOOST_CHECK(substruct_set3.getSize() == 0);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 7);

	substruct_set3.findSubstructures(6);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] * 2);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 6);

//-----

	frag = mol1;
	mol2 = mol1;

	frag += mol2;

	BOOST_CHECK(frag.getNumAtoms() == mol1.getNumAtoms() * 2);
	BOOST_CHECK(frag.getNumBonds() == mol1.getNumBonds() * 2);

	substruct_set3.reset(frag);	

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[6] * 2);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 0);
	
	substruct_set3.findSubstructures(4);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[4] * 2 + substruct_counts[6] * 2);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 4);

	substruct_set3.findSubstructures(1);

	BOOST_CHECK(substruct_set3.getSize() == substruct_counts[1] * 2 + substruct_counts[4] * 2 + substruct_counts[6] * 2);
	BOOST_CHECK(substruct_set3.getSubstructureSize() == 1);

//-----

	ConnectedSubstructureSet substruct_set4(frag);

	BOOST_CHECK(substruct_set4.getSize() == 0);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 0);
	
	substruct_set4.findSubstructures(1);

	BOOST_CHECK(substruct_set4.getSize() == substruct_counts[1] * 2);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 1);

	substruct_set4.findSubstructures(4);

	BOOST_CHECK(substruct_set4.getSize() == substruct_counts[1] * 2 + substruct_counts[4] * 2);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 4);

	substruct_set4.findSubstructures(0);

	BOOST_CHECK(substruct_set4.getSize() == substruct_counts[1] * 2 + substruct_counts[4] * 2);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 0);

//-----

	mol2.clear();

	substruct_set4.reset(mol2);

	BOOST_CHECK(substruct_set4.getSize() == substruct_counts[1] * 2 + substruct_counts[4] * 2);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 0);

	substruct_set4.findSubstructures(3);
	
	BOOST_CHECK(substruct_set4.getSize() == substruct_counts[1] * 2 + substruct_counts[4] * 2);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 3);

	substruct_set4.clear();

	BOOST_CHECK(substruct_set4.getSize() == 0);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 3);

	substruct_set4.findSubstructures(0);
	
	BOOST_CHECK(substruct_set4.getSize() == 0);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 0);

	substruct_set4.findSubstructures(5);
	
	BOOST_CHECK(substruct_set4.getSize() == 0);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 5);

	substruct_set4.findSubstructures(9);
	
	BOOST_CHECK(substruct_set4.getSize() == 0);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 9);

//-----

	mol1.clear();

	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();
	mol1.addAtom();

	mol1.addBond(0, 0);
	mol1.addBond(0, 1);
	mol1.addBond(0, 2);
	mol1.addBond(0, 3);

	mol2 = mol1;

	Molecule mol3(mol1);

	BOOST_CHECK(mol1.getNumAtoms() == 4);
	BOOST_CHECK(mol1.getNumBonds() == 4);

	BOOST_CHECK(mol2.getNumAtoms() == 4);
	BOOST_CHECK(mol2.getNumBonds() == 4);

	BOOST_CHECK(mol3.getNumAtoms() == 4);
	BOOST_CHECK(mol3.getNumBonds() == 4);

	frag = mol1;
	frag += mol2;

	BOOST_CHECK(frag.addBond(mol3.getBond(1)));
	BOOST_CHECK(frag.addBond(mol3.getBond(2)));

	BOOST_CHECK(!frag.addAtom(mol3.getAtom(0)));
	BOOST_CHECK(!frag.addAtom(mol3.getAtom(1)));

	BOOST_CHECK(frag.removeBond(mol2.getBond(3)));

	BOOST_CHECK(frag.getNumAtoms() == 11);
	BOOST_CHECK(frag.getNumBonds() == 9);

	substruct_set4.clear();

	BOOST_CHECK(substruct_set4.getSize() == 0);
	BOOST_CHECK(substruct_set4.getSubstructureSize() == 9);

	substruct_set4.reset(frag);

	BOOST_CHECK(substruct_set4.getSubstructureSize() == 0);

	substruct_set4.findSubstructures(1);

	BOOST_CHECK(substruct_set4.getSize() == 9);

	substruct_set4.clear();

	BOOST_CHECK(substruct_set4.getSize() == 0);

	substruct_set4.findSubstructures(2);

	BOOST_CHECK(substruct_set4.getSize() == 10);

	substruct_set4.clear();

	BOOST_CHECK(substruct_set4.getSize() == 0);

	substruct_set4.findSubstructures(3);

	BOOST_CHECK(substruct_set4.getSize() == 5);
	
	substruct_set4.clear();

	BOOST_CHECK(substruct_set4.getSize() == 0);

	substruct_set4.findSubstructures(4);

	BOOST_CHECK(substruct_set4.getSize() == 1);
}
