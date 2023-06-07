/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CFLDataReader.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/ControlParameterFunctions.hpp"
#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CFLDataReader.hpp"


using namespace CDPL;


ConfGen::CFLDataReader::CFLDataReader(const Base::ControlParameterContainer& ctrl_params): 
	ctrlParams(ctrl_params), smilesReader(smilesStream)
{}

bool ConfGen::CFLDataReader::hasMoreData(std::istream& is)
{
    entryReader.strictErrorChecking(ConfGen::getStrictErrorCheckingParameter(ctrlParams));

	return entryReader.hasMoreData(is);
}

bool ConfGen::CFLDataReader::readMolecule(std::istream& is, Chem::Molecule& mol)
{
	using namespace Chem;
	
	bool strict_error = ConfGen::getStrictErrorCheckingParameter(ctrlParams);

	entryReader.strictErrorChecking(strict_error);

	if (!entryReader.read(is, entry))
		return false;
	
	smilesStream.str(entry.getSMILES());
	smilesStream.seekg(std::istream::beg);

	Chem::setStrictErrorCheckingParameter(smilesReader, strict_error);

	std::size_t prev_num_atoms = mol.getNumAtoms();
	std::size_t prev_num_bonds = mol.getNumBonds();

	if (!smilesReader.read(mol, false))
		return true;
	
	if (prev_num_atoms == 0)
		setName(mol, std::to_string(entry.getHashCode()));
	else
		setName(mol, getName(mol) + '.' + std::to_string(entry.getHashCode()));
	
	MolecularGraph* molgraph = 0;

	if (prev_num_atoms == 0)
		molgraph = &mol;

	else {
		tmpFragment.clear();

		std::for_each(mol.getAtomsBegin() + prev_num_atoms, mol.getAtomsEnd(),
					  boost::bind(&Fragment::addAtom, &tmpFragment, _1));
		std::for_each(mol.getBondsBegin() + prev_num_bonds, mol.getBondsEnd(),
					  boost::bind(&Fragment::addBond, &tmpFragment, _1));
		
		molgraph = &tmpFragment;
	}

	aromAtoms.clear();
	
	for (MolecularGraph::AtomIterator it = molgraph->getAtomsBegin(), end = molgraph->getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;
		
		if (hasAromaticityFlag(atom) && getAromaticityFlag(atom))
			aromAtoms.push_back(&atom);
	}
	
	std::for_each(molgraph->getAtomsBegin(), molgraph->getAtomsEnd(),
				  boost::bind(&setImplicitHydrogenCount, _1, 0));

	setRingFlags(*molgraph, true);
	perceiveSSSR(*molgraph, true);
	setAromaticityFlags(*molgraph, true);
	perceiveHybridizationStates(*molgraph, true);

	for (AtomList::const_iterator it = aromAtoms.begin(), end = aromAtoms.end(); it != end; ++it)
		setAromaticityFlag(**it, true);
	
	canonFragment.create(*molgraph, *molgraph, false);

	if (canonFragment.getHashCode() != entry.getHashCode()) {
		if (strict_error)
			throw Base::IOError("CFLDataReader: canonical fragment hash code mismatch");

		return true;
	}

	const CanonicalFragment::AtomMapping& atom_mpg = canonFragment.getAtomMapping();

	for (std::size_t i = 0, num_atoms = molgraph->getNumAtoms(); i < num_atoms; i++) {
		Atom& atom = molgraph->getAtom(i);
		Math::Vector3DArray::SharedPointer coords_array(new Math::Vector3DArray());
		std::size_t canon_atom_idx = canonFragment.getAtomIndex(*atom_mpg[i]);

		for (FragmentLibraryEntry::ConstConformerIterator it = entry.getConformersBegin(), end = entry.getConformersEnd(); it != end; ++it) {
			const ConformerData& conf_data = *it;

			coords_array->addElement(conf_data[canon_atom_idx]);
		}
		
		set3DCoordinatesArray(atom, coords_array);
	}

	if (prev_num_atoms == 0) {
		Util::DArray::SharedPointer conf_energies(new Util::DArray());

		for (FragmentLibraryEntry::ConstConformerIterator it = entry.getConformersBegin(), end = entry.getConformersEnd(); it != end; ++it)
			conf_energies->addElement(it->getEnergy());

		setConformerEnergies(*molgraph, conf_energies);
	}
	
	return true;
}

bool ConfGen::CFLDataReader::skipMolecule(std::istream& is)
{
	entryReader.strictErrorChecking(ConfGen::getStrictErrorCheckingParameter(ctrlParams));

	return entryReader.skip(is);
}
