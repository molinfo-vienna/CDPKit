/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94PrimaryToParameterAtomTypeMap.cpp 
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

#include <cstring>
#include <sstream>
#include <mutex>
#include <functional>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL; 


namespace
{
 
    ForceField::MMFF94PrimaryToParameterAtomTypeMap::SharedPointer builtinMap(new ForceField::MMFF94PrimaryToParameterAtomTypeMap());

 	std::once_flag initBuiltinMapFlag;

	void initBuiltinMap() 
	{
		builtinMap->loadDefaults();
	}

	const ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry NOT_FOUND;
}


ForceField::MMFF94PrimaryToParameterAtomTypeMap::SharedPointer ForceField::MMFF94PrimaryToParameterAtomTypeMap::defaultMap = builtinMap;


constexpr std::size_t ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES;


ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::Entry(unsigned int atom_type, unsigned int param_types[]): 
	atomType(atom_type), initialized(true)
{
	for (std::size_t i = 0; i < NUM_TYPES; i++)
		paramTypes[i] = param_types[i];
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::Entry(): atomType(0), initialized(false)
{}

unsigned int ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::getAtomType() const
{
	return atomType;
}

const unsigned int* ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::getParameterTypes() const
{
	if (!initialized)
		return 0;

	return &paramTypes[0];
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry::operator bool() const
{
	return initialized;
}


ForceField::MMFF94PrimaryToParameterAtomTypeMap::MMFF94PrimaryToParameterAtomTypeMap()
{}

void ForceField::MMFF94PrimaryToParameterAtomTypeMap::addEntry(unsigned int atom_type, unsigned int param_types[])
{
    entries.insert(DataStorage::value_type(atom_type, Entry(atom_type, param_types)));
}

const ForceField::MMFF94PrimaryToParameterAtomTypeMap::Entry& ForceField::MMFF94PrimaryToParameterAtomTypeMap::getEntry(unsigned int atom_type) const
{
	DataStorage::const_iterator it = entries.find(atom_type);

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t ForceField::MMFF94PrimaryToParameterAtomTypeMap::getNumEntries() const
{
	return entries.size();
}

void ForceField::MMFF94PrimaryToParameterAtomTypeMap::clear()
{
    entries.clear();
}

bool ForceField::MMFF94PrimaryToParameterAtomTypeMap::removeEntry(unsigned int atom_type)
{
	return entries.erase(atom_type);
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::EntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::ConstEntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::ConstEntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}
	
ForceField::MMFF94PrimaryToParameterAtomTypeMap::EntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::getEntriesBegin()
{
	return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::EntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::getEntriesEnd()
{
	return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::ConstEntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::begin() const
{
	return ConstEntryIterator(entries.begin(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::ConstEntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::end() const
{
	return ConstEntryIterator(entries.end(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}
	
ForceField::MMFF94PrimaryToParameterAtomTypeMap::EntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::begin()
{
	return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94PrimaryToParameterAtomTypeMap::EntryIterator 
ForceField::MMFF94PrimaryToParameterAtomTypeMap::end()
{
	return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

void ForceField::MMFF94PrimaryToParameterAtomTypeMap::load(std::istream& is)
{
    std::string line;
	std::string tmp;
	unsigned int atom_type;
	unsigned int param_types[Entry::NUM_TYPES];

    while (readMMFF94DataLine(is, line, "MMFF94PrimaryToParameterAtomTypeMap: error while reading primary to parameter atom type mapping entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> tmp))
			throw Base::IOError("MMFF94PrimaryToParameterAtomTypeMap: error while reading primary symbolic atom type");

		if (!(line_iss >> atom_type))
			throw Base::IOError("MMFF94PrimaryToParameterAtomTypeMap: error while reading primary atom type");

		for (std::size_t i = 0; i < Entry::NUM_TYPES; i++)
			if (!(line_iss >> param_types[i]))
				throw Base::IOError("MMFF94PrimaryToParameterAtomTypeMap: error while reading parameter atom type");
	
		addEntry(atom_type, param_types);
    }
}

void ForceField::MMFF94PrimaryToParameterAtomTypeMap::loadDefaults()
{
    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING, 
																std::strlen(MMFF94ParameterData::NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING));
    load(is);
}

void ForceField::MMFF94PrimaryToParameterAtomTypeMap::set(const SharedPointer& table)
{	
    defaultMap = (!table ? builtinMap : table);
}

const ForceField::MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& ForceField::MMFF94PrimaryToParameterAtomTypeMap::get()
{
 	std::call_once(initBuiltinMapFlag, &initBuiltinMap);

	return defaultMap;
}
