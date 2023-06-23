/* 
 * MMFF94OutOfPlaneBendingParameterTable.cpp 
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
#include <algorithm>
#include <mutex>
#include <functional>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ForceField/MMFF94OutOfPlaneBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94ParameterSet.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL;


namespace
{

    ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer
        builtinDynTable(new ForceField::MMFF94OutOfPlaneBendingParameterTable());
    ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer
        builtinStatTable(new ForceField::MMFF94OutOfPlaneBendingParameterTable());
    ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer
        builtinStatExtTable(new ForceField::MMFF94OutOfPlaneBendingParameterTable());

    std::once_flag initBuiltinTablesFlag;

    void initBuiltinTables()
    {
        using namespace ForceField;

        builtinDynTable->loadDefaults(MMFF94ParameterSet::DYNAMIC);
        builtinStatTable->loadDefaults(MMFF94ParameterSet::STATIC);
        builtinStatExtTable->loadDefaults(MMFF94ParameterSet::STATIC_XOOP);
    }

    std::uint32_t lookupKey(std::uint32_t term_atom1_type, std::uint32_t ctr_atom_type,
                            std::uint32_t term_atom2_type, std::uint32_t oop_atom_type)
    {
        unsigned int nbr_types[] = { term_atom1_type, term_atom2_type, oop_atom_type };

        std::sort(nbr_types, nbr_types + 3);

        return ((nbr_types[0] << 24) + (nbr_types[1] << 16) + (nbr_types[2] << 8) + ctr_atom_type);
    }

    const ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry NOT_FOUND;
} // namespace


ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer
    ForceField::MMFF94OutOfPlaneBendingParameterTable::defaultDynTable = builtinDynTable;
ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer
    ForceField::MMFF94OutOfPlaneBendingParameterTable::defaultStatTable = builtinStatTable;
ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer
    ForceField::MMFF94OutOfPlaneBendingParameterTable::defaultStatExtTable = builtinStatExtTable;


ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::Entry():
    termAtom1Type(0), ctrAtomType(0), termAtom2Type(0), oopAtomType(0), forceConst(0),
    initialized(false)
{}

ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::Entry(unsigned int term_atom1_type,
                                                                unsigned int ctr_atom_type,
                                                                unsigned int term_atom2_type,
                                                                unsigned int oop_atom_type,
                                                                double       force_const):
    termAtom1Type(term_atom1_type),
    ctrAtomType(ctr_atom_type), termAtom2Type(term_atom2_type), oopAtomType(term_atom2_type),
    forceConst(force_const), initialized(true)
{}

unsigned int ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getTerminalAtom1Type() const
{
    return termAtom1Type;
}

unsigned int ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getCenterAtomType() const
{
    return ctrAtomType;
}

unsigned int ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getTerminalAtom2Type() const
{
    return termAtom2Type;
}

unsigned int ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getOutOfPlaneAtomType() const
{
    return oopAtomType;
}

double ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::getForceConstant() const
{
    return forceConst;
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry::operator bool() const
{
    return initialized;
}


ForceField::MMFF94OutOfPlaneBendingParameterTable::MMFF94OutOfPlaneBendingParameterTable() {}

void ForceField::MMFF94OutOfPlaneBendingParameterTable::addEntry(unsigned int term_atom1_type,
                                                                 unsigned int ctr_atom_type,
                                                                 unsigned int term_atom2_type,
                                                                 unsigned int oop_atom_type,
                                                                 double       force_const)
{
    entries.insert(DataStorage::value_type(lookupKey(term_atom1_type, ctr_atom_type,
                                                     term_atom2_type, oop_atom_type),
                                           Entry(term_atom1_type, ctr_atom_type, term_atom2_type,
                                                 oop_atom_type, force_const)));
}

const ForceField::MMFF94OutOfPlaneBendingParameterTable::Entry&
ForceField::MMFF94OutOfPlaneBendingParameterTable::getEntry(unsigned int term_atom1_type,
                                                            unsigned int ctr_atom_type,
                                                            unsigned int term_atom2_type,
                                                            unsigned int oop_atom_type) const
{
    DataStorage::const_iterator it =
        entries.find(lookupKey(term_atom1_type, ctr_atom_type, term_atom2_type, oop_atom_type));

    if (it == entries.end())
        return NOT_FOUND;

    return it->second;
}

std::size_t ForceField::MMFF94OutOfPlaneBendingParameterTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94OutOfPlaneBendingParameterTable::clear()
{
    entries.clear();
}

bool ForceField::MMFF94OutOfPlaneBendingParameterTable::removeEntry(unsigned int term_atom1_type,
                                                                    unsigned int ctr_atom_type,
                                                                    unsigned int term_atom2_type,
                                                                    unsigned int oop_atom_type)
{
    return entries.erase(lookupKey(term_atom1_type, ctr_atom_type, term_atom2_type, oop_atom_type));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::EntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::removeEntry(const EntryIterator& it)
{
    return EntryIterator(entries.erase(it.base()),
                         std::bind<Entry&>(&DataStorage::value_type::second,
                                           std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::getEntriesBegin() const
{
    return ConstEntryIterator(entries.begin(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::getEntriesEnd() const
{
    return ConstEntryIterator(entries.end(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::EntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::getEntriesBegin()
{
    return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                            std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::EntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::getEntriesEnd()
{
    return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                          std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::begin() const
{
    return ConstEntryIterator(entries.begin(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::end() const
{
    return ConstEntryIterator(entries.end(),
                              std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::EntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::begin()
{
    return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                            std::placeholders::_1));
}

ForceField::MMFF94OutOfPlaneBendingParameterTable::EntryIterator
ForceField::MMFF94OutOfPlaneBendingParameterTable::end()
{
    return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second,
                                                          std::placeholders::_1));
}

void ForceField::MMFF94OutOfPlaneBendingParameterTable::load(std::istream& is)
{
    std::string  line;
    unsigned int term_atom1_type;
    unsigned int ctr_atom_type;
    unsigned int term_atom2_type;
    unsigned int oop_atom_type;
    double       force_const;

    while (readMMFF94DataLine(is, line,
                              "MMFF94OutOfPlaneBendingParameterTable: error while reading "
                              "out-of-plane bending parameter entry")) {
        std::istringstream line_iss(line);

        if (!(line_iss >> term_atom1_type))
            throw Base::IOError(
                "MMFF94OutOfPlaneBendingParameterTable: error while reading terminal atom 1 type");

        if (!(line_iss >> ctr_atom_type))
            throw Base::IOError(
                "MMFF94OutOfPlaneBendingParameterTable: error while reading center atom type");

        if (!(line_iss >> term_atom2_type))
            throw Base::IOError(
                "MMFF94OutOfPlaneBendingParameterTable: error while reading terminal atom 2 type");

        if (!(line_iss >> oop_atom_type))
            throw Base::IOError("MMFF94OutOfPlaneBendingParameterTable: error while reading "
                                "out-of-plane atom type");

        if (!(line_iss >> force_const))
            throw Base::IOError(
                "MMFF94OutOfPlaneBendingParameterTable: error while reading force constant");

        addEntry(term_atom1_type, ctr_atom_type, term_atom2_type, oop_atom_type, force_const);
    }
}

void ForceField::MMFF94OutOfPlaneBendingParameterTable::loadDefaults(unsigned int param_set)
{
    if (param_set == MMFF94ParameterSet::DYNAMIC) {
        boost::iostreams::stream<boost::iostreams::array_source>
            is(MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS,
               MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS_LEN);
        load(is);

    } else if (param_set == MMFF94ParameterSet::STATIC_XOOP ||
               param_set == MMFF94ParameterSet::STATIC_RTOR_XOOP) {
        boost::iostreams::stream<boost::iostreams::array_source>
            is(MMFF94ParameterData::STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS,
               MMFF94ParameterData::STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS_LEN);
        load(is);

    } else {
        boost::iostreams::stream<boost::iostreams::array_source>
            is(MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS,
               MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS_LEN);
        load(is);
    }
}

void ForceField::MMFF94OutOfPlaneBendingParameterTable::set(const SharedPointer& table,
                                                            unsigned int         param_set)
{
    switch (param_set) {

        case MMFF94ParameterSet::DYNAMIC:
            defaultDynTable = (!table ? builtinDynTable : table);
            return;

        case MMFF94ParameterSet::STATIC_XOOP:
        case MMFF94ParameterSet::STATIC_RTOR_XOOP:
            defaultStatExtTable = (!table ? builtinStatExtTable : table);
            return;

        default:
            defaultStatTable = (!table ? builtinStatTable : table);
    }
}

const ForceField::MMFF94OutOfPlaneBendingParameterTable::SharedPointer&
ForceField::MMFF94OutOfPlaneBendingParameterTable::get(unsigned int param_set)
{
    std::call_once(initBuiltinTablesFlag, &initBuiltinTables);

    switch (param_set) {

        case MMFF94ParameterSet::DYNAMIC:
            return defaultDynTable;

        case MMFF94ParameterSet::STATIC_XOOP:
        case MMFF94ParameterSet::STATIC_RTOR_XOOP:
            return defaultStatExtTable;

        default:
            break;
    }

    return defaultStatTable;
}
