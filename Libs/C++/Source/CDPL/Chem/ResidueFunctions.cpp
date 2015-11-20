/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <sstream>
#include <vector>
#include <map>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/ResidueFunctions.hpp"
#include "CDPL/Chem/ResidueType.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "ResidueData.hpp"


using namespace CDPL;


namespace 
{

	struct ResidueDictionaryEntry 
	{

		Chem::Molecule::SharedPointer structure;
		std::string                   name;
		const ResidueDataEntry*       data;
	};

    const char* stdResidues[] = {
        "UNK", "ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU", "GLY", "HIS", "ILE", "LEU", "LYS", "MET",
		"PHE", "PRO", "SER", "THR", "TRP", "TYR", "VAL", "CSE", "PYL", "ASX", "GLX",
		"N", "DA", "DC", "DG", "DI", "DU", "DT", "A", "C", "G", "I", "U"
    };

    typedef boost::unordered_map<std::string, ResidueDictionaryEntry> ResidueDictionary;
    typedef boost::unordered_map<std::string, const ResidueDataEntry*> ResCodeToDataEntryMap;
    typedef boost::unordered_set<std::string> StdResidueSet;

    ResCodeToDataEntryMap resCodeToDataEntryMap;
	StdResidueSet stdResidueSet;
	ResidueDictionary residueDictionary;

    void initLookupTables()
    {
		static bool initialized = false;

		if (initialized)
			return;

		stdResidueSet.insert(&stdResidues[0], &stdResidues[sizeof(stdResidues) / sizeof(const char*)]);

		for (std::size_t i = 0; i < sizeof(residueData) / sizeof(ResidueDataEntry); i++) {
			const ResidueDataEntry& entry = residueData[i];

			resCodeToDataEntryMap.insert(ResCodeToDataEntryMap::value_type(entry.code, &entry));
		}
			
		initialized = true;
    }

	ResidueDictionaryEntry* getDictionaryEntry(const std::string& code) 
	{
		initLookupTables();

		ResidueDictionary::iterator it1 = residueDictionary.find(code);

		if (it1 != residueDictionary.end())
			return &it1->second;

		ResCodeToDataEntryMap::const_iterator it2 = resCodeToDataEntryMap.find(code);

		if (it2 == resCodeToDataEntryMap.end())
			return 0;

		ResidueDictionaryEntry entry;

		entry.data = it2->second;

		return &residueDictionary.insert(ResidueDictionary::value_type(code, entry)).first->second;
	}

	void loadResidueStructure(ResidueDictionaryEntry* entry)
	{
		using namespace CDPL;
		using namespace Chem;

		Molecule::SharedPointer& mol_ptr = entry->structure;

		mol_ptr.reset(new BasicMolecule());

		std::string jme_str(entry->data->jmeString);
		std::istringstream iss(jme_str);
		JMEMoleculeReader jme_reader(iss);

		setCoordinatesDimensionParameter(jme_reader, 3);

		try {
			jme_reader.read(*mol_ptr);

		} catch (std::exception& e) {
			throw Base::IOError(std::string("ResidueDictionary: loading residue structure failed: ") + e.what());
		}

		std::string res_code(entry->data->code);

		for (Molecule::AtomIterator it = mol_ptr->getAtomsBegin(), end = mol_ptr->getAtomsEnd(); it != end; ++it) {
			Atom& atom = *it;

			setResidueCode(atom, res_code);
		}
		
		for (std::size_t i = 0; i < entry->data->numLeavingAtoms; i++) {
			Atom& atom = mol_ptr->getAtom(entry->data->leavingAtoms[i]);

			setResidueLeavingAtomFlag(atom, true);
		}

		for (std::size_t i = 0; i < entry->data->numLeavingAtoms; i++) {
			Atom& atom = mol_ptr->getAtom(entry->data->leavingAtoms[i]);

			for (Atom::AtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it) {
				Atom& nbr_atom = *a_it;

				setResidueLinkingAtomFlag(nbr_atom, !getResidueLeavingAtomFlag(nbr_atom));
			}
		}

		for (std::size_t i = 0; i < entry->data->numAtoms; i++) {
			Atom& atom = mol_ptr->getAtom(i);

			setResidueAtomName(atom, entry->data->atomNames[i * 2]);
			setResidueAltAtomName(atom, entry->data->atomNames[i * 2 + 1]);
		}
		
		setResidueCode(*mol_ptr, res_code);
		setName(*mol_ptr, entry->data->name);

		perceiveComponents(*mol_ptr, false);
		perceiveComponentGroups(*mol_ptr, false);
		perceiveSSSR(*mol_ptr, false);
		setRingFlags(*mol_ptr, false);
		calcTopologicalDistanceMatrix(*mol_ptr, false);
		calcImplicitHydrogenCounts(*mol_ptr, false);
		perceiveHybridizationStates(*mol_ptr, false);
		setAromaticityFlags(*mol_ptr, false);
		calcAtomStereoDescriptors(*mol_ptr, false, 3);
		calcBondStereoDescriptors(*mol_ptr, false, 3);
	}
}


using namespace CDPL;


bool Chem::isStandardResidue(const std::string& code)
{
	initLookupTables();

	return (stdResidueSet.find(code) != stdResidueSet.end());
}

unsigned int Chem::getResidueType(const std::string& code)
{	
	ResidueDictionaryEntry* entry = getDictionaryEntry(code);
	
	if (!entry)
		return ResidueType::UNKNOWN;
	
	return entry->data->type;
}

const std::string& Chem::getResidueName(const std::string& code)
{
	static std::string NO_NAME;

	ResidueDictionaryEntry* entry = getDictionaryEntry(code);
	
	if (!entry)
		return NO_NAME;
	
	if (entry->name.empty())
		entry->name = entry->data->name;

	return entry->name;
}

const Chem::MolecularGraph* Chem::getResidueStructure(const std::string& code)
{
	ResidueDictionaryEntry* entry = getDictionaryEntry(code);
	
	if (!entry)
		return 0;

	if (!entry->structure)
		loadResidueStructure(entry);

	return entry->structure.get();
}
