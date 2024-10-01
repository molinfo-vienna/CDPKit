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
#include <utility>
#include <mutex>
#include <functional>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/CDFGZMoleculeReader.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "ResidueDictionaryData.hpp"


using namespace CDPL;


namespace
{

    typedef std::unordered_set<std::string, Internal::CIStringHashFunc, Internal::CIStringCmpFunc>  StdResidueSet;
    typedef std::unordered_map<std::string, std::string,
                               Internal::CIStringHashFunc, Internal::CIStringCmpFunc>               SingleLetterCodeMap;
    typedef std::unordered_map<std::string, const Biomol::ResidueDictionaryData::ResidueDataEntry*,
                               Internal::CIStringHashFunc, Internal::CIStringCmpFunc>               ResCodeToDataEntryMap;
    typedef std::unordered_map<std::string, Chem::MolecularGraph::SharedPointer,
                               Internal::CIStringHashFunc, Internal::CIStringCmpFunc>               StructureCache;

    StdResidueSet stdResidueSet{
       "UNK", "ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU",
      "GLY", "HIS", "ILE", "LEU", "LYS", "MET", "PHE", "PRO",
      "SER", "THR", "TRP", "TYR", "VAL", "CSE", "SEC", "PYL",
      "ASX", "GLX", "N",   "DA",  "DC",  "DG",  "DI",  "DU",
      "DT",  "A",   "C",   "G",   "I",   "U"
    };
    
    SingleLetterCodeMap singleLetterCodeMap{
      { "ALA", "A" },
      { "ARG", "R" },
      { "ASN", "N" },
      { "ASP", "D" },
      { "CYS", "C" },
      { "GLN", "Q" },
      { "GLU", "E" },
      { "GLY", "G" },
      { "HIS", "H" },
      { "ILE", "I" },
      { "LEU", "L" },
      { "LYS", "K" },
      { "MET", "M" },
      { "PHE", "F" },
      { "PRO", "P" },
      { "SER", "S" },
      { "THR", "T" },
      { "TRP", "W" },
      { "TYR", "Y" },
      { "VAL", "V" },
      { "A", "A" },
      { "C", "C" },
      { "G", "G" },
      { "I", "I" },
      { "U", "U" }
    };
    
    ResCodeToDataEntryMap                    resCodeToDataEntryMap;
    StructureCache                           resStructureCache;
    Biomol::ResidueDictionary::SharedPointer builtinDictionary(new Biomol::ResidueDictionary());

    std::mutex     loadStructureMutex;
    std::once_flag initBuiltinDictionaryFlag;
    std::once_flag initResCodeToDataEntryMapFlag;

    const Biomol::ResidueDictionary::Entry DEF_ENTRY;
    const std::string                      NO_SINGLE_LETTER_CODE;

    void initBuiltinDictionary()
    {
        builtinDictionary->loadDefaults();
    }

    void initResCodeToDataEntryMap()
    {
        using namespace Biomol::ResidueDictionaryData;

        for (std::size_t i = 0; i < NUM_RESIDUE_ENTRIES; i++) {
            const ResidueDataEntry& entry = RESIDUE_DATA[i];

            resCodeToDataEntryMap.insert(ResCodeToDataEntryMap::value_type(entry.code, &entry));
        }
    }

    Chem::MolecularGraph::SharedPointer loadResidueStructure(const std::string& code)
    {
        using namespace Chem;
        using namespace Biomol;
        using namespace ResidueDictionaryData; 

        std::lock_guard<std::mutex> lock(loadStructureMutex);

        static std::pair<const char*, std::size_t> res_struct_data = Biomol::ResidueDictionaryData::getStructureData();
        static boost::iostreams::stream<boost::iostreams::array_source>
                                         res_struct_is(res_struct_data.first, res_struct_data.second);
        static Chem::CDFGZMoleculeReader res_struct_reader(res_struct_is);

        StructureCache::const_iterator rsc_it = resStructureCache.find(code);

        if (rsc_it != resStructureCache.end())
            return rsc_it->second;

        ResCodeToDataEntryMap::const_iterator ent_it = resCodeToDataEntryMap.find(code);

        if (ent_it == resCodeToDataEntryMap.end())
            return MolecularGraph::SharedPointer();

        const ResidueDataEntry& data_entry = *ent_it->second;
        Molecule::SharedPointer mol_ptr(new BasicMolecule());

        try {
            res_struct_reader.read(data_entry.molIndex, *mol_ptr);

        } catch (std::exception& e) {
            throw Base::IOError(
                std::string("ResidueDictionary: loading residue structure failed: ") + e.what());
        }

        for (Molecule::AtomIterator it = mol_ptr->getAtomsBegin(), end = mol_ptr->getAtomsEnd();
             it != end; ++it) {
            Atom& atom = *it;

            setResidueCode(atom, code);

            if (!getResidueLeavingAtomFlag(atom))
                continue;

            for (Atom::AtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd();
                 a_it != a_end; ++a_it) {
                Atom& nbr_atom = *a_it;

                setResidueLinkingAtomFlag(nbr_atom, !getResidueLeavingAtomFlag(nbr_atom));
            }
        }

        setName(*mol_ptr, data_entry.name);
        setAtomSymbolsFromTypes(*mol_ptr, false);
        perceiveComponents(*mol_ptr, false);
        perceiveSSSR(*mol_ptr, false);
        setRingFlags(*mol_ptr, false);
        calcImplicitHydrogenCounts(*mol_ptr, false);
        perceiveHybridizationStates(*mol_ptr, false);
        setAromaticityFlags(*mol_ptr, false);
        perceiveAtomStereoCenters(*mol_ptr, false, false);
        perceiveBondStereoCenters(*mol_ptr, false, false);
        calcAtomCIPConfigurations(*mol_ptr, false);
        calcBondCIPConfigurations(*mol_ptr, false);
        
        resStructureCache.insert(StructureCache::value_type(code, mol_ptr));

        return mol_ptr;
    }
} // namespace


Biomol::ResidueDictionary::SharedPointer Biomol::ResidueDictionary::defaultDict = builtinDictionary;


Biomol::ResidueDictionary::Entry::Entry(const std::string& code, const std::string& rep_code,
                                        const std::string& rep_by_code, const std::string& parent_code,
                                        bool obsolete, const std::string& name, unsigned int type,
                                        const StructureRetrievalFunction& struc_ret_func):
    code(code),
    replacesCode(rep_code), replacedByCode(rep_by_code), parentCode(parent_code), obsolete(obsolete), name(name), type(type),
    structRetrievalFunc(struc_ret_func)
{}

Biomol::ResidueDictionary::Entry::Entry():
    code(), replacesCode(), replacedByCode(), parentCode(), obsolete(false), name(), type(ResidueType::UNKNOWN),
    structRetrievalFunc()
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

const std::string& Biomol::ResidueDictionary::Entry::getParentCode() const
{
    return parentCode;
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
    entries.emplace(entry.getCode(), Entry(entry));
}

void Biomol::ResidueDictionary::addEntry(Entry&& entry)
{
    entries.emplace(entry.getCode(), std::move(entry));
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

const Biomol::ResidueDictionary::Entry&
Biomol::ResidueDictionary::getEntry(const std::string& code) const
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
    return ConstEntryIterator(entries.begin(), std::bind(&EntryLookupTable::value_type::second,
                                                         std::placeholders::_1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::getEntriesEnd() const
{
    return ConstEntryIterator(entries.end(), std::bind(&EntryLookupTable::value_type::second,
                                                       std::placeholders::_1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::begin() const
{
    return ConstEntryIterator(entries.begin(), std::bind(&EntryLookupTable::value_type::second,
                                                         std::placeholders::_1));
}

Biomol::ResidueDictionary::ConstEntryIterator Biomol::ResidueDictionary::end() const
{
    return ConstEntryIterator(entries.end(), std::bind(&EntryLookupTable::value_type::second,
                                                       std::placeholders::_1));
}

void Biomol::ResidueDictionary::loadDefaults()
{
    using namespace ResidueDictionaryData;

    std::call_once(initResCodeToDataEntryMapFlag, &initResCodeToDataEntryMap);

    Entry::StructureRetrievalFunction struc_ret_func(&loadResidueStructure);

    for (std::size_t i = 0; i < NUM_RESIDUE_ENTRIES; i++) {
        const ResidueDataEntry& res_data = RESIDUE_DATA[i];

        Entry entry(res_data.code, res_data.replacesCode, res_data.replacedByCode,
                    res_data.parentCode, res_data.obsolete, res_data.name, res_data.type,
                    struc_ret_func);

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

unsigned int Biomol::ResidueDictionary::getType(const std::string& code) const
{
    return getEntry(code).getType();
}

const std::string& Biomol::ResidueDictionary::getName(const std::string& code) const
{
    const Entry& entry = getEntry(code);

    return entry.getName();
}

Chem::MolecularGraph::SharedPointer Biomol::ResidueDictionary::getStructure(const std::string& code) const
{
    return getEntry(code).getStructure();
}

const std::string& Biomol::ResidueDictionary::getReplacedCode(const std::string& code) const
{
    return getEntry(code).getReplacedCode();
}

const std::string& Biomol::ResidueDictionary::getReplacedByCode(const std::string& code) const
{
    return getEntry(code).getReplacedByCode();
}

const std::string& Biomol::ResidueDictionary::getParentCode(const std::string& code) const
{
    return getEntry(code).getParentCode();
}

const std::string& Biomol::ResidueDictionary::getSingleLetterCode(const std::string& code)
{
    auto it = singleLetterCodeMap.find(code);

    if (it == singleLetterCodeMap.end())
        return NO_SINGLE_LETTER_CODE;

    return it->second;
}

bool Biomol::ResidueDictionary::isObsolete(const std::string& code) const
{
    const Entry& entry = getEntry(code);

    return entry.isObsolete();
}


std::size_t Biomol::ResidueDictionary::CIStringHashFunc::operator()(const std::string& str) const
{
    static const Internal::CIStringHashFunc hash_func;

    return hash_func(str);
}


bool Biomol::ResidueDictionary::CIStringCmpFunc::operator()(const std::string& str1, const std::string& str2) const
{
    static const Internal::CIStringCmpFunc cmp_func;

    return cmp_func(str1, str2);
}
