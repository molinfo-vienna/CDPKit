/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ChEMBLStandardizer.cpp 
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

 
#include "StaticInit.hpp"

#include <cstring>
#include <utility>

#include "CDPL/Config.hpp"

#include <boost/thread.hpp>
#include <boost/unordered_set.hpp>

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#else // defined(HAVE_BOOST_IOSTREAMS)

#include <sstream>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Chem/ChEMBLStandardizer.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"


using namespace CDPL;


namespace
{

	const char* CHEMBL_SALT_STRUCTURE_LIBRARY =                 
    #include "ChEMBL-Salts.smi.str" 
	;

	const char* CHEMBL_SOLVENT_STRUCTURE_LIBRARY =                 
    #include "ChEMBL-Solvents.smi.str" 
	;

	boost::once_flag initSaltAndSolventDataFlag = BOOST_ONCE_INIT;
	
	typedef std::pair<Base::uint64, std::size_t> StructureID;
	typedef boost::unordered_set<StructureID> StructureIDSet;

	StructureIDSet chemblSaltStructureIDs;
	StructureIDSet chemblSolventStructureIDs;

	void initSaltAndSolventData()
	{
		using namespace Chem;

#if defined(HAVE_BOOST_IOSTREAMS)

		boost::iostreams::stream<boost::iostreams::array_source> salts_is(CHEMBL_SALT_STRUCTURE_LIBRARY, std::strlen(CHEMBL_SALT_STRUCTURE_LIBRARY));
		boost::iostreams::stream<boost::iostreams::array_source> solvents_is(CHEMBL_SOLVENT_STRUCTURE_LIBRARY, std::strlen(CHEMBL_SOLVENT_STRUCTURE_LIBRARY));

#else // defined(HAVE_BOOST_IOSTREAMS)

		std::istringstream salts_is(CHEMBL_SALT_STRUCTURE_LIBRARY);
		std::istringstream solvents_is(CHEMBL_SOLVENT_STRUCTURE_LIBRARY);

#endif // defined(HAVE_BOOST_IOSTREAMS)

		HashCodeCalculator hash_calc;

		hash_calc.includeGlobalStereoFeatures(false);
		hash_calc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hash_calc, AtomPropertyFlag::TYPE | AtomPropertyFlag::AROMATICITY));
		hash_calc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hash_calc, 
																					 BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | 
																					 BondPropertyFlag::AROMATICITY));
		BasicMolecule mol;
		SMILESMoleculeReader salts_reader(salts_is);

		setSMILESRecordFormatParameter(salts_reader, "NS");

		while (salts_reader.read(mol)) {
			calcImplicitHydrogenCounts(mol, makeHydrogenDeplete(mol));
			perceiveHybridizationStates(mol, false);
			perceiveSSSR(mol, false);
			setRingFlags(mol, false);
			setAromaticityFlags(mol, false);

			chemblSaltStructureIDs.insert(StructureID(hash_calc.calculate(mol), mol.getNumAtoms()));
		}

		SMILESMoleculeReader solvents_reader(solvents_is);

		setSMILESRecordFormatParameter(solvents_reader, "NS");

		while (solvents_reader.read(mol)) {
			calcImplicitHydrogenCounts(mol, makeHydrogenDeplete(mol));
			perceiveHybridizationStates(mol, false);
			perceiveSSSR(mol, false);
			setRingFlags(mol, false);
			setAromaticityFlags(mol, false);

			chemblSolventStructureIDs.insert(StructureID(hash_calc.calculate(mol), mol.getNumAtoms()));
		}
	}
}


Chem::ChEMBLStandardizer::ChEMBLStandardizer():
	procExcldMols(false)
{}

Chem::ChEMBLStandardizer::ChEMBLStandardizer(const ChEMBLStandardizer& standardizer):
	procExcldMols(standardizer.procExcldMols)
{}

void Chem::ChEMBLStandardizer::processExcludedMolecules(bool process)
{
	procExcldMols = process;
}

bool Chem::ChEMBLStandardizer::excludedMoleculesProcessed() const
{
	return procExcldMols;
}

Chem::ChEMBLStandardizer::Result Chem::ChEMBLStandardizer::standardize(Molecule& mol)
{
	Result result = NO_CHANGES;

	if (checkIfExcluded(mol)) {
		if (!procExcldMols)
			return EXCLUDED;

		result = EXCLUDED;
	}
	
	// TODO

	return result;
}

Chem::ChEMBLStandardizer::Result Chem::ChEMBLStandardizer::standardize(const Molecule& mol, Molecule& std_mol)
{
	copyMolecule(mol, std_mol);
	
	return standardize(std_mol);
}

bool Chem::ChEMBLStandardizer::getParent(Molecule& mol)
{
	boost::call_once(&initSaltAndSolventData, initSaltAndSolventDataFlag);
	
	// TODO
	
	return false;
}

bool Chem::ChEMBLStandardizer::getParent(const Molecule& mol, Molecule& parent_mol)
{
	copyMolecule(mol, parent_mol);
	
	return getParent(parent_mol);
}

Chem::ChEMBLStandardizer& Chem::ChEMBLStandardizer::operator=(const ChEMBLStandardizer& standardizer)
{
	if (&standardizer == this)
		return *this;

	procExcldMols = standardizer.procExcldMols;
	
	// TODO
	
	return *this;
}

bool Chem::ChEMBLStandardizer::checkIfExcluded(const Molecule& mol) const
{
	// TODO
	
	return false;
}

void Chem::ChEMBLStandardizer::copyMolecule(const Molecule& mol, Molecule& mol_copy) const
{
	mol_copy.copy(mol);
	mol_copy.clearProperties();

	copyAtomStereoDescriptors(mol, mol_copy);
	copyBondStereoDescriptors(mol, mol_copy);

	if (hasSSSR(mol))
		copySSSR(mol, mol_copy);
}
