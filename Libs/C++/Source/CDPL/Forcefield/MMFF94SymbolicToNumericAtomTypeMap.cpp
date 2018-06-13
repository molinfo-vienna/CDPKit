/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94SymbolicToNumericAtomTypeMap.cpp 
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

#include "CDPL/Forcefield/MMFF94SymbolicToNumericAtomTypeMap.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "BuiltinMMFF94Data.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94SymbolicToNumericAtomTypeMap builtinTable;
    unsigned int                                   NOT_FOUND = 0;

    struct Init
    {

	Init() {
	    builtinTable.loadDefaults();
	}

    } init;
}


const Forcefield::MMFF94SymbolicToNumericAtomTypeMap* Forcefield::MMFF94SymbolicToNumericAtomTypeMap::defaultTable = &builtinTable;


Forcefield::MMFF94SymbolicToNumericAtomTypeMap::MMFF94SymbolicToNumericAtomTypeMap()
{}

void Forcefield::MMFF94SymbolicToNumericAtomTypeMap::addEntry(const std::string& sym_type, unsigned int num_type)
{
    entries.insert(DataStorage::value_type(sym_type, num_type));
}

unsigned int Forcefield::MMFF94SymbolicToNumericAtomTypeMap::getNumericType(const std::string& sym_type) const
{
    DataStorage::const_iterator it = entries.find(sym_type);

    if (it == entries.end())
	return NOT_FOUND;

    return it->second;
}

void Forcefield::MMFF94SymbolicToNumericAtomTypeMap::clear()
{
    entries.clear();
}

Forcefield::MMFF94SymbolicToNumericAtomTypeMap::ConstEntryIterator Forcefield::MMFF94SymbolicToNumericAtomTypeMap::getEntriesBegin() const
{
    return entries.begin();
}

Forcefield::MMFF94SymbolicToNumericAtomTypeMap::ConstEntryIterator Forcefield::MMFF94SymbolicToNumericAtomTypeMap::getEntriesEnd() const
{
    return entries.end();
}
			
void Forcefield::MMFF94SymbolicToNumericAtomTypeMap::load(std::istream& is)
{
    std::string line;
    std::string sym_type;
    unsigned int num_type;

    while (readMMFF94DataLine(is, line, "MMFF94SymbolicToNumericAtomTypeMap: error while reading numeric atom type definition data line")) {
	std::istringstream line_iss(line);

	if (!(line_iss >> sym_type))
	    throw Base::IOError("MMFF94SymbolicToNumericAtomTypeMap: error while reading symbolic atom type");
		
	if (!(line_iss >> num_type))
	    throw Base::IOError("MMFF94SymbolicToNumericAtomTypeMap: error while reading numeric atom type");
	
	addEntry(sym_type, num_type);
    }
}

void Forcefield::MMFF94SymbolicToNumericAtomTypeMap::loadDefaults()
{
    boost::iostreams::stream<boost::iostreams::array_source> is(Forcefield::BuiltinMMFF94Data::SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING, 
								std::strlen(Forcefield::BuiltinMMFF94Data::SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING));
    load(is);
}

void Forcefield::MMFF94SymbolicToNumericAtomTypeMap::set(const Forcefield::MMFF94SymbolicToNumericAtomTypeMap* db)
{	
    defaultTable = (!db ? &builtinTable : db);
}

const Forcefield::MMFF94SymbolicToNumericAtomTypeMap& Forcefield::MMFF94SymbolicToNumericAtomTypeMap::get()
{
    return *defaultTable;
}
