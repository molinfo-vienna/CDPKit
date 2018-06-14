/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94HeavyToHydrogenAtomTypeMap.cpp 
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

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/Forcefield/MMFF94HeavyToHydrogenAtomTypeMap.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94HeavyToHydrogenAtomTypeMap builtinTable;
    std::string                                  NOT_FOUND;

    struct Init
    {

	Init() {
	    builtinTable.loadDefaults();
	}

    } init;
}


const Forcefield::MMFF94HeavyToHydrogenAtomTypeMap* Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::defaultTable = &builtinTable;


Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::MMFF94HeavyToHydrogenAtomTypeMap()
{}

void Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::addEntry(const std::string& parent_type, const std::string& hyd_type)
{
    entries.insert(DataStorage::value_type(parent_type, hyd_type));
}

const std::string& Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::getHydrogenType(const std::string& parent_type) const
{
    DataStorage::const_iterator it = entries.find(parent_type);

    if (it == entries.end())
	return NOT_FOUND;

    return it->second;
}

void Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::clear()
{
    entries.clear();
}

Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::ConstEntryIterator Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::getEntriesBegin() const
{
    return entries.begin();
}

Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::ConstEntryIterator Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::getEntriesEnd() const
{
    return entries.end();
}
			
void Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::load(std::istream& is)
{
    std::string line;
    std::string parent_type;
    std::string hyd_type;

    while (readMMFF94DataLine(is, line, "MMFF94HeavyToHydrogenAtomTypeMap: error while reading hydrogen atom type definition data line")) {
	std::istringstream line_iss(line);

	if (!(line_iss >> parent_type))
	    throw Base::IOError("MMFF94HeavyToHydrogenAtomTypeMap: error while reading parent atom type");
		
	if (!(line_iss >> hyd_type))
	    throw Base::IOError("MMFF94HeavyToHydrogenAtomTypeMap: error while reading hydrogen atom type");
	
	addEntry(parent_type, hyd_type);
    }
}

void Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::loadDefaults()
{
    boost::iostreams::stream<boost::iostreams::array_source> is(Forcefield::MMFF94ParameterData::HYDROGEN_ATOM_TYPE_DEFINITIONS, 
								std::strlen(Forcefield::MMFF94ParameterData::HYDROGEN_ATOM_TYPE_DEFINITIONS));
    load(is);
}

void Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::set(const Forcefield::MMFF94HeavyToHydrogenAtomTypeMap* db)
{	
    defaultTable = (!db ? &builtinTable : db);
}

const Forcefield::MMFF94HeavyToHydrogenAtomTypeMap& Forcefield::MMFF94HeavyToHydrogenAtomTypeMap::get()
{
    return *defaultTable;
}
