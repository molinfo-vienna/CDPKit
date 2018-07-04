/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94FormalAtomChargeDefinitionTable.cpp 
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

#include <cstring>
#include <sstream>

#include "CDPL/Config.hpp"

#include <boost/bind.hpp>

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Forcefield/MMFF94FormalAtomChargeDefinitionTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94FormalAtomChargeDefinitionTable::SharedPointer builtinTable(new Forcefield::MMFF94FormalAtomChargeDefinitionTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

    const Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry NOT_FOUND;
}


Forcefield::MMFF94FormalAtomChargeDefinitionTable::SharedPointer Forcefield::MMFF94FormalAtomChargeDefinitionTable::defaultTable = builtinTable;


Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::Entry():
    atomType(), assMode(0), charge(0.0), typeList(), initialized(false)
{}

Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::Entry(const std::string& atom_type, std::size_t ass_mode, 
																double charge, const std::string& type_list):
    atomType(atom_type), assMode(ass_mode), charge(charge), typeList(type_list), initialized(true)
{}

const std::string& Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::getAtomType() const
{
    return atomType;
}

std::size_t Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::getAssignmentMode() const
{
    return assMode;
}

double Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::getFormalCharge() const
{
    return charge;
}

const std::string& Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::getAtomTypeList() const
{
    return typeList;
}

Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry::operator bool() const
{
    return initialized;
}


Forcefield::MMFF94FormalAtomChargeDefinitionTable::MMFF94FormalAtomChargeDefinitionTable()
{}

void Forcefield::MMFF94FormalAtomChargeDefinitionTable::addEntry(const std::string& atom_type, std::size_t ass_mode, 
																 double charge, const std::string& nbr_types)
{
    entries.insert(DataStorage::value_type(atom_type, Entry(atom_type, ass_mode, charge, nbr_types)));
}

const Forcefield::MMFF94FormalAtomChargeDefinitionTable::Entry& 
Forcefield::MMFF94FormalAtomChargeDefinitionTable::getEntry(const std::string& atom_type) const
{
    DataStorage::const_iterator it = entries.find(atom_type);

    if (it == entries.end())
		return NOT_FOUND;

    return it->second;
}

std::size_t Forcefield::MMFF94FormalAtomChargeDefinitionTable::getNumEntries() const
{
    return entries.size();
}

void Forcefield::MMFF94FormalAtomChargeDefinitionTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94FormalAtomChargeDefinitionTable::removeEntry(const std::string& atom_type)
{
    return entries.erase(atom_type);
}

Forcefield::MMFF94FormalAtomChargeDefinitionTable::EntryIterator 
Forcefield::MMFF94FormalAtomChargeDefinitionTable::removeEntry(const EntryIterator& it)
{
    return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94FormalAtomChargeDefinitionTable::ConstEntryIterator 
Forcefield::MMFF94FormalAtomChargeDefinitionTable::getEntriesBegin() const
{
    return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94FormalAtomChargeDefinitionTable::ConstEntryIterator 
Forcefield::MMFF94FormalAtomChargeDefinitionTable::getEntriesEnd() const
{
    return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94FormalAtomChargeDefinitionTable::EntryIterator 
Forcefield::MMFF94FormalAtomChargeDefinitionTable::getEntriesBegin()
{
    return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94FormalAtomChargeDefinitionTable::EntryIterator 
Forcefield::MMFF94FormalAtomChargeDefinitionTable::getEntriesEnd()
{
    return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94FormalAtomChargeDefinitionTable::load(std::istream& is)
{
    std::string line;
    std::string atom_type;
    std::size_t ass_mode;
    double charge;
    std::string type_list;

    while (readMMFF94DataLine(is, line, "MMFF94FormalAtomChargeDefinitionTable: error while reading formal atom charge definition entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> atom_type))
			throw Base::IOError("MMFF94FormalAtomChargeDefinitionTable: error while reading symbolic atom type");
	
		if (!(line_iss >> ass_mode))
			throw Base::IOError("MMFF94FormalAtomChargeDefinitionTable: error while reading formal charge assignment mode");

		if (!(line_iss >> charge))
			throw Base::IOError("MMFF94FormalAtomChargeDefinitionTable: error while reading formal atom charge");

		if (!(line_iss >> type_list))
			throw Base::IOError("MMFF94FormalAtomChargeDefinitionTable: error while reading symbolic atom type list");
		
		addEntry(atom_type, ass_mode, charge, type_list);
    }
}

void Forcefield::MMFF94FormalAtomChargeDefinitionTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::FORMAL_ATOM_CHARGE_DEFINITIONS, 
																std::strlen(MMFF94ParameterData::FORMAL_ATOM_CHARGE_DEFINITIONS));
#else // defined(HAVE_BOOST_IOSTREAMS)

    std::istringstream is(std::string(MMFF94ParameterData::FORMAL_ATOM_CHARGE_DEFINITIONS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94FormalAtomChargeDefinitionTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94FormalAtomChargeDefinitionTable::SharedPointer& Forcefield::MMFF94FormalAtomChargeDefinitionTable::get()
{
    return defaultTable;
}
