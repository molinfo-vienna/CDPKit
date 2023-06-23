/* 
 * MMFF94BondStretchingRuleParameterTable.cpp 
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

#include <sstream>
#include <mutex>
#include <functional>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL;


namespace
{

    ForceField::MMFF94BondStretchingRuleParameterTable::SharedPointer
        builtinTable(new ForceField::MMFF94BondStretchingRuleParameterTable());

    std::once_flag initBuiltinTableFlag;

    void initBuiltinTable()
    {
        builtinTable->loadDefaults();
    }

    std::uint32_t lookupKey(std::uint32_t atomic_no1, std::uint32_t atomic_no2)
    {
        if (atomic_no1 < atomic_no2)
            return ((atomic_no1 << 8) + atomic_no2);

        return ((atomic_no2 << 8) + atomic_no1);
    }

    const ForceField::MMFF94BondStretchingRuleParameterTable::Entry NOT_FOUND;
} // namespace


ForceField::MMFF94BondStretchingRuleParameterTable::SharedPointer
    ForceField::MMFF94BondStretchingRuleParameterTable::defaultTable = builtinTable;


ForceField::MMFF94BondStretchingRuleParameterTable::Entry::Entry():
    atomicNo1(0), atomicNo2(0), forceConst(0), refLength(0), initialized(false)
{}

ForceField::MMFF94BondStretchingRuleParameterTable::Entry::Entry(unsigned int atomic_no1,
                                                                 unsigned int atomic_no2,
                                                                 double       force_const,
                                                                 double       ref_length):
    atomicNo1(atomic_no1),
    atomicNo2(atomic_no2), forceConst(force_const), refLength(ref_length), initialized(true)
{}

unsigned int ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getAtomicNumber1() const
{
    return atomicNo1;
}

unsigned int ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getAtomicNumber2() const
{
    return atomicNo2;
}

double ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getForceConstant() const
{
    return forceConst;
}

double ForceField::MMFF94BondStretchingRuleParameterTable::Entry::getReferenceLength() const
{
    return refLength;
}

ForceField::MMFF94BondStretchingRuleParameterTable::Entry::operator bool() const
{
    return initialized;
}


ForceField::MMFF94BondStretchingRuleParameterTable::MMFF94BondStretchingRuleParameterTable() {}

void ForceField::MMFF94BondStretchingRuleParameterTable::addEntry(unsigned int atomic_no1,
                                                                  unsigned int atomic_no2,
                                                                  double       force_const,
                                                                  double       ref_length)
{
    entries.insert(DataStorage::value_type(lookupKey(atomic_no1, atomic_no2),
                                           Entry(atomic_no1, atomic_no2, force_const, ref_length)));
}

const ForceField::MMFF94BondStretchingRuleParameterTable::Entry&
ForceField::MMFF94BondStretchingRuleParameterTable::getEntry(unsigned int atomic_no1,
                                                             unsigned int atomic_no2) const
{
    DataStorage::const_iterator it = entries.find(lookupKey(atomic_no1, atomic_no2));

    if (it == entries.end())
        return NOT_FOUND;

    return it->second;
}

std::size_t ForceField::MMFF94BondStretchingRuleParameterTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94BondStretchingRuleParameterTable::clear()
{
    entries.clear();
}

bool ForceField::MMFF94BondStretchingRuleParameterTable::removeEntry(unsigned int atomic_no1,
                                                                     unsigned int atomic_no2)
{
    return entries.erase(lookupKey(atomic_no1, atomic_no2));
}

ForceField::MMFF94BondStretchingRuleParameterTable::EntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::removeEntry(const EntryIterator& it)
{
    return EntryIterator(entries.erase(it.base()),
                         std::bind<Entry&>(&DataStorage::value_type::second,
                                           std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::ConstEntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::getEntriesBegin() const
{
    return ConstEntryIterator(entries.begin(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::ConstEntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::getEntriesEnd() const
{
    return ConstEntryIterator(entries.end(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::EntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::getEntriesBegin()
{
    return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                            std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::EntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::getEntriesEnd()
{
    return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                          std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::ConstEntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::begin() const
{
    return ConstEntryIterator(entries.begin(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::ConstEntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::end() const
{
    return ConstEntryIterator(entries.end(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::EntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::begin()
{
    return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                            std::placeholders::_1));
}

ForceField::MMFF94BondStretchingRuleParameterTable::EntryIterator
ForceField::MMFF94BondStretchingRuleParameterTable::end()
{
    return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                          std::placeholders::_1));
}

void ForceField::MMFF94BondStretchingRuleParameterTable::load(std::istream& is)
{
    std::string  line;
    unsigned int atomic_no1;
    unsigned int atomic_no2;
    double       force_const;
    double       ref_length;

    while (readMMFF94DataLine(is, line,
                              "MMFF94BondStretchingRuleParameterTable: error while reading bond "
                              "stretchung rule parameter entry")) {
        std::istringstream line_iss(line);

        if (!(line_iss >> atomic_no1))
            throw Base::IOError("MMFF94BondStretchingRuleParameterTable: error while reading "
                                "atomic number of first atom");

        if (!(line_iss >> atomic_no2))
            throw Base::IOError("MMFF94BondStretchingRuleParameterTable: error while reading "
                                "atomic number of second atom");

        if (!(line_iss >> ref_length))
            throw Base::IOError("MMFF94BondStretchingRuleParameterTable: error while reading "
                                "reference bond length");

        if (!(line_iss >> force_const))
            throw Base::IOError(
                "MMFF94BondStretchingRuleParameterTable: error while reading force constant");

        addEntry(atomic_no1, atomic_no2, force_const, ref_length);
    }
}

void ForceField::MMFF94BondStretchingRuleParameterTable::loadDefaults()
{
    boost::iostreams::stream<boost::iostreams::array_source>
        is(MMFF94ParameterData::BOND_STRETCHING_RULE_PARAMETERS,
           MMFF94ParameterData::BOND_STRETCHING_RULE_PARAMETERS_LEN);
    load(is);
}

void ForceField::MMFF94BondStretchingRuleParameterTable::set(const SharedPointer& table)
{
    defaultTable = (!table ? builtinTable : table);
}

const ForceField::MMFF94BondStretchingRuleParameterTable::SharedPointer&
ForceField::MMFF94BondStretchingRuleParameterTable::get()
{
    std::call_once(initBuiltinTableFlag, &initBuiltinTable);

    return defaultTable;
}
