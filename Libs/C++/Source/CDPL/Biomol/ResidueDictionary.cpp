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

#include <boost/unordered_set.hpp>
#include <boost/bind.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/thread.hpp>

#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/CDFMoleculeReader.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "ResidueData.hpp"


using namespace CDPL;


namespace 
{
  
    typedef boost::unordered_set<std::string> StdResidueSet;
    typedef boost::unordered_map<std::string, const ResidueDataEntry*> ResCodeToDataEntryMap;
    typedef boost::unordered_map<std::string, Chem::MolecularGraph::SharedPointer> StructureCache;

	StdResidueSet             stdResidueSet;
    ResCodeToDataEntryMap     resCodeToDataEntryMap;
	StructureCache            resStructureCache;
	Biomol::ResidueDictionary builtinDictionary;
	boost::mutex              loadStructureMutex;

	const Biomol::ResidueDictionary::Entry DEF_ENTRY;

    boost::iostreams::stream<boost::iostreams::array_source> resStructureIStream(residueStructureData, RESIDUE_STRUCTURE_DATA_LEN);
    Chem::CDFMoleculeReader                                  resStructureReader(resStructureIStream);

	const char* stdResidueList[] = {
        "UNK", "ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU", "GLY", "HIS", "ILE", "LEU", "LYS", "MET",
		"PHE", "PRO", "SER", "THR", "TRP", "TYR", "VAL", "CSE", "SEC", "PYL", "ASX", "GLX",
		"N", "DA", "DC", "DG", "DI", "DU", "DT", "A", "C", "G", "I", "U"
    };

	struct Init 
	{

		Init() {
			stdResidueSet.insert(&stdResidueList[0], &stdResidueList[sizeof(stdResidueList) / sizeof(const char*)]);
			builtinDictionary.loadDefaultEntries();

			for (std::size_t i = 0; i < sizeof(residueData) / sizeof(ResidueDataEntry); i++) {
				const ResidueDataEntry& entry = residueData[i];

				resCodeToDataEntryMap.insert(ResCodeToDataEntryMap::value_type(entry.code, &entry));
			}
		}

	} init;

	Chem::MolecularGraph::SharedPointer loadResidueStructure(const std::string& code)
	{
		using namespace Chem;
		using namespace Biomol;

		boost::lock_guard<boost::mutex> lock(loadStructureMutex);

		StructureCache::const_iterator rsc_it = resStructureCache.find(code);

		if (rsc_it != resStructureCache.end())
			return rsc_it->second;

		ResCodeToDataEntryMap::const_iterator ent_it = resCodeToDataEntryMap.find(code);

		if (ent_it == resCodeToDataEntryMap.end())
			return MolecularGraph::SharedPointer();

		const ResidueDataEntry& data_entry = *ent_it->second;
		Molecule::SharedPointer mol_ptr(new BasicMolecule());

		try {
			resStructureReader.read(data_entry.molIndex, *mol_ptr);

		} catch (std::exception& e) {
			throw Base::IOError(std::string("ResidueDictionary: loading residue structure failed: ") + e.what());
		}

		for (Molecule::AtomIterator it = mol_ptr->getAtomsBegin(), end = mol_ptr->getAtomsEnd(); it != end; ++it) {
			Atom& atom = *it;

			setResidueCode(atom, code);
	
			if (!getResidueLeavingAtomFlag(atom))
				continue;

			for (Atom::AtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it) {
				Atom& nbr_atom = *a_it;

				setResidueLinkingAtomFlag(nbr_atom, !getResidueLeavingAtomFlag(nbr_atom));
			}
		}

		setResidueCode(*mol_ptr, code);
		setName(*mol_ptr, data_entry.name);

		setAtomTypesFromSymbols(*mol_ptr, false);
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

		resStructureCache.insert(StructureCache::value_type(code, mol_ptr));

		return mol_ptr;
	}
}


const Biomol::ResidueDictionary* Biomol::ResidueDictionary::dictionary = &builtinDictionary;


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
	dictionary = (!dict ? &builtinDictionary : dict);
}

const Biomol::ResidueDictionary& Biomol::ResidueDictionary::get()
{
    return *dictionary;
}

bool Biomol::ResidueDictionary::isStdResidue(const std::string& code)
{
	return (stdResidueSet.find(code) != stdResidueSet.end());
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
