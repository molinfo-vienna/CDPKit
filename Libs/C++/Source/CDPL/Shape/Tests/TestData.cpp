/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TestData.cpp
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


#include <cstdlib>

#include <boost/unordered_map.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/SDFMoleculeReader.hpp"
#include "CDPL/Biomol/PDBMoleculeReader.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Util/FileDataReader.hpp"

#include "TestData.hpp"


using namespace CDPL;


namespace
{

	boost::unordered_map<std::string, Shape::GaussianShape::SharedPointer> nameToShapeMap;
	
	double getRadius(const Chem::Atom& atom)
	{
		using namespace Chem;
			
		unsigned int type = getType(atom);

		switch (type) {

			case AtomType::C:
				return 1.70;
				
			case AtomType::N:
				return 1.65;
				
			case AtomType::H:
				return 1.00;
				
			case AtomType::O:
				return 1.60;
				
			case AtomType::S:
				return 1.90;

			default:
				break;
		}

		return AtomDictionary::getVdWRadius(type);
	}
	
	Shape::GaussianShape::SharedPointer generateMoleculeShape(Chem::Molecule& mol)
	{
		using namespace Chem;
		using namespace Shape;

		GaussianShape::SharedPointer shape_ptr(new GaussianShape());
		
		for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
			Atom& atom = *it;

			shape_ptr->addElement(get3DCoordinates(atom), getRadius(atom));
		}

		return shape_ptr;
	}

	bool readPDBMolecule(const std::string& fname, Chem::Molecule& mol)
	{
		using namespace Biomol;
		
		Util::FileDataReader<PDBMoleculeReader> mol_reader(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/") + fname);

		if (!mol_reader.read(mol))
			return false;

		for (std::size_t i = 0; i < mol.getNumAtoms(); ) {
			if (getHeteroAtomFlag(mol.getAtom(i))) {
				mol.removeAtom(i);
				continue;
			}

			i++;
		}
/*
		calcImplicitHydrogenCounts(mol, true);
		perceiveHybridizationStates(mol, true);
		setRingFlags(mol, true);
		setAromaticityFlags(mol, true);
		makeHydrogenComplete(mol);
		generateHydrogen3DCoordinates(mol);
*/		
		return true;
	}
	
	bool readSDFMolecule(const std::string& fname, Chem::Molecule& mol)
	{
		using namespace Chem;
		
		Util::FileDataReader<SDFMoleculeReader> mol_reader(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/") + fname);

		return mol_reader.read(mol);
	}

	struct Init
	{

		Init() {
			using namespace Chem;

			BasicMolecule mol;
			
			if (readPDBMolecule("1crn.pdb", mol))
				nameToShapeMap["1crn"] = generateMoleculeShape(mol);

			if (readPDBMolecule("2ins.pdb", mol))
				nameToShapeMap["2ins"] = generateMoleculeShape(mol);

			if (readPDBMolecule("3app.pdb", mol))
				nameToShapeMap["3app"] = generateMoleculeShape(mol);

			if (readSDFMolecule("1dwc_MIT.sdf", mol))
				nameToShapeMap["1dwc_MIT"] = generateMoleculeShape(mol);

			if (readSDFMolecule("1tmn_0ZN.sdf", mol))
				nameToShapeMap["1tmn_0ZN"] = generateMoleculeShape(mol);

			if (readSDFMolecule("4phv_VAC.sdf", mol))
				nameToShapeMap["4phv_VAC"] = generateMoleculeShape(mol);
		}

	} init;
}

Shape::GaussianShape::SharedPointer TestData::getShapeData(const std::string& id, double p)
{
	Shape::GaussianShape::SharedPointer shape = nameToShapeMap[id];

	if (shape)
		for (Shape::GaussianShape::ElementIterator it = shape->getElementsBegin(), end = shape->getElementsEnd(); it != end; ++it)
			it->setHardness(p);
	
	return shape;
}
