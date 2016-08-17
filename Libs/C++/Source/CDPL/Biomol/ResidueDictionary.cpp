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

#include <boost/unordered_set.hpp>
#include <boost/bind.hpp>

#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "ResidueData.hpp"


using namespace CDPL;


namespace 
{
  
    typedef boost::unordered_set<std::string> StdResidueSet;
    typedef boost::unordered_map<std::string, const ResidueDataEntry*> ResCodeToDataEntryMap;
    typedef boost::unordered_map<std::string, Chem::MolecularGraph::SharedPointer> StructureCache;

	StdResidueSet STD_RESIDUE_SET;
    ResCodeToDataEntryMap RES_CODE_TO_DATA_ENTRY_MAP;
	StructureCache RES_STRUCTURE_CACHE;
	Biomol::ResidueDictionary BUILTIN_DICTIONARY;

	const char* STD_RESIDUE_LIST[] = {
        "UNK", "ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU", "GLY", "HIS", "ILE", "LEU", "LYS", "MET",
		"PHE", "PRO", "SER", "THR", "TRP", "TYR", "VAL", "CSE", "PYL", "ASX", "GLX",
		"N", "DA", "DC", "DG", "DI", "DU", "DT", "A", "C", "G", "I", "U"
    };

	struct Init 
	{

		Init() {
			STD_RESIDUE_SET.insert(&STD_RESIDUE_LIST[0], &STD_RESIDUE_LIST[sizeof(STD_RESIDUE_LIST) / sizeof(const char*)]);
			BUILTIN_DICTIONARY.loadDefaultEntries();

			for (std::size_t i = 0; i < sizeof(residueData) / sizeof(ResidueDataEntry); i++) {
				const ResidueDataEntry& entry = residueData[i];

				RES_CODE_TO_DATA_ENTRY_MAP.insert(ResCodeToDataEntryMap::value_type(entry.code, &entry));
			}
		}

	} init;

	Chem::MolecularGraph::SharedPointer loadResidueStructure(const std::string& code)
	{
		using namespace Chem;
		using namespace Biomol;

		StructureCache::const_iterator rsc_it = RES_STRUCTURE_CACHE.find(code);

		if (rsc_it != RES_STRUCTURE_CACHE.end())
			return rsc_it->second;

		ResCodeToDataEntryMap::const_iterator ent_it = RES_CODE_TO_DATA_ENTRY_MAP.find(code);

		if (ent_it == RES_CODE_TO_DATA_ENTRY_MAP.end())
			return MolecularGraph::SharedPointer();

		const ResidueDataEntry& data_entry = *ent_it->second;
		Molecule::SharedPointer mol_ptr(new BasicMolecule());

		std::string jme_str(data_entry.jmeString);
		std::istringstream iss(jme_str);
		JMEMoleculeReader jme_reader(iss);

		setCoordinatesDimensionParameter(jme_reader, 3);

		try {
			jme_reader.read(*mol_ptr);

		} catch (std::exception& e) {
			throw Base::IOError(std::string("ResidueDictionary: loading residue structure failed: ") + e.what());
		}

		for (Molecule::AtomIterator it = mol_ptr->getAtomsBegin(), end = mol_ptr->getAtomsEnd(); it != end; ++it) {
			Atom& atom = *it;

			setResidueCode(atom, code);
		}
		
		for (std::size_t i = 0; i < data_entry.numLeavingAtoms; i++) {
			Atom& atom = mol_ptr->getAtom(data_entry.leavingAtoms[i]);

			setResidueLeavingAtomFlag(atom, true);
		}

		for (std::size_t i = 0; i < data_entry.numLeavingAtoms; i++) {
			Atom& atom = mol_ptr->getAtom(data_entry.leavingAtoms[i]);

			for (Atom::AtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it) {
				Atom& nbr_atom = *a_it;

				setResidueLinkingAtomFlag(nbr_atom, !getResidueLeavingAtomFlag(nbr_atom));
			}
		}

		for (std::size_t i = 0; i < data_entry.numAtoms; i++) {
			Atom& atom = mol_ptr->getAtom(i);

			setResidueAtomName(atom, data_entry.atomNames[i * 2]);
			setResidueAltAtomName(atom, data_entry.atomNames[i * 2 + 1]);
		}
		
		setResidueCode(*mol_ptr, code);
		setName(*mol_ptr, data_entry.name);

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

		RES_STRUCTURE_CACHE.insert(StructureCache::value_type(code, mol_ptr));

		return mol_ptr;
	}
}


const Biomol::ResidueDictionary* Biomol::ResidueDictionary::dictionary = &BUILTIN_DICTIONARY;


Biomol::ResidueDictionary::Entry::Entry(const std::string& code, const std::string& rep_code, const std::string& rep_by_code, bool obsolete,
										const std::string& name, unsigned int type, const StructureRetrievalFunction& struc_ret_func):
	code(code), replacesCode(rep_code), replacedByCode(rep_by_code), obsolete(obsolete), 
	name(name), type(type), structRetrievalFunc(struc_ret_func)
{}

Biomol::ResidueDictionary::Entry::Entry():
	code(), replacesCode(), replacedByCode(), obsolete(false), name(), type(ResidueType::UNKNOWN), structRetrievalFunc()
{}

const std::string& Biomol::ResidueDictionary::Entry::getCode() const
{
	return code;
}

const std::string& Biomol::ResidueDictionary::Entry::getReplacedCode() const
{
	return replacesCode;
}

const std::string& Biomol::ResidueDictionary::Entry::getReplacedByCode() const
{
	return replacedByCode;
}

bool Biomol::ResidueDictionary::Entry::isObsolete() const
{
	return obsolete;
}

const std::string& Biomol::ResidueDictionary::Entry::getName() const
{
	return name;
}

unsigned int Biomol::ResidueDictionary::Entry::getType() const
{
	return type;
}

Chem::MolecularGraph::SharedPointer Biomol::ResidueDictionary::Entry::getStructure() const
{
	if (structRetrievalFunc.empty())
		return Chem::MolecularGraph::SharedPointer();

	return structRetrievalFunc(code);
}
				

void Biomol::ResidueDictionary::addEntry(const Entry& entry)
{
	EntryLookupTable::iterator it = entries.find(entry.getCode());

	if (it == entries.end()) 
		entries.insert(EntryLookupTable::value_type(entry.getCode(), entry));
	else 
		it->second = entry;
}

bool Biomol::ResidueDictionary::containsEntry(const std::string& code) const
{
	EntryLookupTable::const_iterator it = entries.find(code);

	return (it != entries.end());
}

void Biomol::ResidueDictionary::removeEntry(const std::string& code)
{
	entries.erase(code);
}
			
const Biomol::ResidueDictionary::Entry& Biomol::ResidueDictionary::getEntry(const std::string& code) const
{
	EntryLookupTable::const_iterator it = entries.find(code);

	if (it != entries.end())
		return it->second;

	static const Entry DEF_ENTRY;

	return DEF_ENTRY;
}

void Biomol::ResidueDictionary::clear()
{
	entries.clear();
}

std::size_t Biomol::ResidueDictionary::getNumEntries() const
{
	return entries.size();
}
			
Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&EntryLookupTable::value_type::second, _1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&EntryLookupTable::value_type::second, _1));
}

void Biomol::ResidueDictionary::loadDefaultEntries()
{
	Entry::StructureRetrievalFunction struc_ret_func(&loadResidueStructure);

	for (std::size_t i = 0; i < sizeof(residueData) / sizeof(ResidueDataEntry); i++) {
		const ResidueDataEntry& res_data = residueData[i];

		Entry entry(res_data.code, res_data.replacesCode, res_data.replacedByCode, res_data.obsolete,
					res_data.name, res_data.type, struc_ret_func);

		addEntry(entry);
	}
}

void Biomol::ResidueDictionary::set(const ResidueDictionary* dict)
{
	dictionary = (!dict ? &BUILTIN_DICTIONARY : dict);
}

const Biomol::ResidueDictionary& Biomol::ResidueDictionary::get()
{
    return *dictionary;
}

bool Biomol::ResidueDictionary::isStdResidue(const std::string& code)
{
	return (STD_RESIDUE_SET.find(code) != STD_RESIDUE_SET.end());
}

unsigned int Biomol::ResidueDictionary::getType(const std::string& code)
{	
	const Entry& entry = dictionary->getEntry(code);

	return entry.getType();
}

const std::string& Biomol::ResidueDictionary::getName(const std::string& code)
{
	const Entry& entry = dictionary->getEntry(code);

	return entry.getName();
}

Chem::MolecularGraph::SharedPointer Biomol::ResidueDictionary::getStructure(const std::string& code)
{
	const Entry& entry = dictionary->getEntry(code);

	return entry.getStructure();
}

const std::string& Biomol::ResidueDictionary::getReplacedCode(const std::string& code)
{
	const Entry& entry = dictionary->getEntry(code);

	return entry.getReplacedCode();
}

const std::string& Biomol::ResidueDictionary::getReplacedByCode(const std::string& code)
{
	const Entry& entry = dictionary->getEntry(code);

	return entry.getReplacedByCode();
}

bool Biomol::ResidueDictionary::isObsolete(const std::string& code)
{
	const Entry& entry = dictionary->getEntry(code);

	return entry.isObsolete();
}
