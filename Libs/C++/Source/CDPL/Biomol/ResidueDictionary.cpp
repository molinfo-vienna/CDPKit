/* 
 * ResidueFunctions.cpp 
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

#include <unordered_set>
#include <mutex>
#include <functional>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/CDFMoleculeReader.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "ResidueDictionaryData.hpp"


using namespace CDPL;


namespace 
{
  
    typedef std::unordered_set<std::string> StdResidueSet;
    typedef std::unordered_map<std::string, const Biomol::ResidueDictionaryData::ResidueDataEntry*> ResCodeToDataEntryMap;
    typedef std::unordered_map<std::string, Chem::MolecularGraph::SharedPointer> StructureCache;

    StdResidueSet                            stdResidueSet;
    ResCodeToDataEntryMap                    resCodeToDataEntryMap;
    StructureCache                           resStructureCache;
    Biomol::ResidueDictionary::SharedPointer builtinDictionary(new Biomol::ResidueDictionary());

    std::mutex                               loadStructureMutex;
    std::once_flag                           initBuiltinDictionaryFlag;
    std::once_flag                           initResCodeToDataEntryMapFlag;

    const Biomol::ResidueDictionary::Entry   DEF_ENTRY;

    boost::iostreams::stream<boost::iostreams::array_source> resStructureIStream(Biomol::ResidueDictionaryData::residueStructureData, 
                                                                                 Biomol::ResidueDictionaryData::RESIDUE_STRUCTURE_DATA_LEN);

    Chem::CDFMoleculeReader resStructureReader(resStructureIStream);

    const char* stdResidueList[] = {
        "UNK", "ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU", "GLY", "HIS", "ILE", "LEU", "LYS", "MET",
        "PHE", "PRO", "SER", "THR", "TRP", "TYR", "VAL", "CSE", "SEC", "PYL", "ASX", "GLX",
        "N", "DA", "DC", "DG", "DI", "DU", "DT", "A", "C", "G", "I", "U"
    };

    struct Init 
    {

        Init() {
            stdResidueSet.insert(&stdResidueList[0], &stdResidueList[sizeof(stdResidueList) / sizeof(const char*)]);
        }

    } init;

    void initBuiltinDictionary()
    {
        builtinDictionary->loadDefaults();
    }

    void initResCodeToDataEntryMap()
    {
        using namespace Biomol::ResidueDictionaryData;

        for (std::size_t i = 0; i < NUM_RESIDUE_ENTRIES; i++) {
            const ResidueDataEntry& entry = residueData[i];

            resCodeToDataEntryMap.insert(ResCodeToDataEntryMap::value_type(entry.code, &entry));
        }
    }

    Chem::MolecularGraph::SharedPointer loadResidueStructure(const std::string& code)
    {
        using namespace Chem;
        using namespace Biomol;
        using namespace ResidueDictionaryData;

        std::lock_guard<std::mutex> lock(loadStructureMutex);

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


Biomol::ResidueDictionary::SharedPointer Biomol::ResidueDictionary::defaultDict = builtinDictionary;


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
    if (!structRetrievalFunc)
        return Chem::MolecularGraph::SharedPointer();

    return structRetrievalFunc(code);
}
                

void Biomol::ResidueDictionary::addEntry(const Entry& entry)
{
    entries.insert(EntryLookupTable::value_type(entry.getCode(), entry));
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
    return ConstEntryIterator(entries.begin(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::getEntriesEnd() const
{
    return ConstEntryIterator(entries.end(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::begin() const
{
    return ConstEntryIterator(entries.begin(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::end() const
{
    return ConstEntryIterator(entries.end(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

void Biomol::ResidueDictionary::loadDefaults()
{
    using namespace ResidueDictionaryData;

    std::call_once(initResCodeToDataEntryMapFlag, &initResCodeToDataEntryMap);

    Entry::StructureRetrievalFunction struc_ret_func(&loadResidueStructure);

    for (std::size_t i = 0; i < NUM_RESIDUE_ENTRIES; i++) {
        const ResidueDataEntry& res_data = residueData[i];

        Entry entry(res_data.code, res_data.replacesCode, res_data.replacedByCode, res_data.obsolete,
                    res_data.name, res_data.type, struc_ret_func);

        addEntry(entry);
    }
}

void Biomol::ResidueDictionary::set(const SharedPointer& dict)
{
    defaultDict = (!dict ? builtinDictionary : dict);
}

const Biomol::ResidueDictionary::SharedPointer& Biomol::ResidueDictionary::get()
{
    std::call_once(initBuiltinDictionaryFlag, &initBuiltinDictionary);

    return defaultDict;
}

bool Biomol::ResidueDictionary::isStdResidue(const std::string& code)
{
    return (stdResidueSet.find(code) != stdResidueSet.end());
}

unsigned int Biomol::ResidueDictionary::getType(const std::string& code)
{    
    const Entry& entry = get()->getEntry(code);

    return entry.getType();
}

const std::string& Biomol::ResidueDictionary::getName(const std::string& code)
{
    const Entry& entry = get()->getEntry(code);

    return entry.getName();
}

Chem::MolecularGraph::SharedPointer Biomol::ResidueDictionary::getStructure(const std::string& code)
{
    const Entry& entry = get()->getEntry(code);

    return entry.getStructure();
}

const std::string& Biomol::ResidueDictionary::getReplacedCode(const std::string& code)
{
    const Entry& entry = get()->getEntry(code);

    return entry.getReplacedCode();
}

const std::string& Biomol::ResidueDictionary::getReplacedByCode(const std::string& code)
{
    const Entry& entry = get()->getEntry(code);

    return entry.getReplacedByCode();
}

bool Biomol::ResidueDictionary::isObsolete(const std::string& code)
{
    const Entry& entry = get()->getEntry(code);

    return entry.isObsolete();
}
