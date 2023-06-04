/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AromaticAtomTypeDefinitionTable.cpp 
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

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ForceField/MMFF94AromaticAtomTypeDefinitionTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL; 


namespace
{
 
    ForceField::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer builtinTable(new ForceField::MMFF94AromaticAtomTypeDefinitionTable());

	std::once_flag initBuiltinTableFlag;

  	void initBuiltinTable() 
	{
		builtinTable->loadDefaults();
	}
}


ForceField::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer ForceField::MMFF94AromaticAtomTypeDefinitionTable::defaultTable = builtinTable;


ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::Entry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no, 
																std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion):
	oldType(old_type), aroType(aro_type), atomicNumber(atomic_no), ringSize(ring_size), 
	hetAtomDist(het_atom_dist), imCation(im_cation), n5Anion(n5_anion)
{}

const std::string& ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getOldAtomType() const
{
	return oldType;
}
				
const std::string& ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAromAtomType() const
{
	return aroType;
}
				
unsigned int ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAtomicNumber() const
{
	return atomicNumber;
}

std::size_t ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getRingSize() const
{
	return ringSize;
}

std::size_t ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::getHeteroAtomDistance() const
{
	return hetAtomDist;
}

bool ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::isImidazoliumCation() const
{
	return imCation;
}

bool ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry::isN5RingAnion() const
{
	return n5Anion;
}


ForceField::MMFF94AromaticAtomTypeDefinitionTable::MMFF94AromaticAtomTypeDefinitionTable()
{}

std::size_t ForceField::MMFF94AromaticAtomTypeDefinitionTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94AromaticAtomTypeDefinitionTable::addEntry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no, 
																 std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion)
{
    entries.push_back(Entry(old_type, aro_type, atomic_no, ring_size, het_atom_dist, im_cation, n5_anion));
}

const ForceField::MMFF94AromaticAtomTypeDefinitionTable::Entry& ForceField::MMFF94AromaticAtomTypeDefinitionTable::getEntry(std::size_t idx) const
{
	if (idx >= entries.size())
		throw Base::IndexError("MMFF94AromaticAtomTypeDefinitionTable: entry index out of bounds");

	return entries[idx];
}

ForceField::MMFF94AromaticAtomTypeDefinitionTable::ConstEntryIterator 
ForceField::MMFF94AromaticAtomTypeDefinitionTable::getEntriesBegin() const
{
    return entries.begin();
}

ForceField::MMFF94AromaticAtomTypeDefinitionTable::ConstEntryIterator 
ForceField::MMFF94AromaticAtomTypeDefinitionTable::getEntriesEnd() const
{
    return entries.end();
}

ForceField::MMFF94AromaticAtomTypeDefinitionTable::EntryIterator 
ForceField::MMFF94AromaticAtomTypeDefinitionTable::getEntriesBegin()
{
	return entries.begin();
}

ForceField::MMFF94AromaticAtomTypeDefinitionTable::EntryIterator 
ForceField::MMFF94AromaticAtomTypeDefinitionTable::getEntriesEnd()
{
	return entries.end();
}

void ForceField::MMFF94AromaticAtomTypeDefinitionTable::clear()
{
    entries.clear();
}

void ForceField::MMFF94AromaticAtomTypeDefinitionTable::removeEntry(std::size_t idx)
{
	if (idx >= entries.size())
		throw Base::IndexError("MMFF94AromaticAtomTypeDefinitionTable: entry index out of bounds");

	entries.erase(entries.begin() + idx);
}

ForceField::MMFF94AromaticAtomTypeDefinitionTable::EntryIterator 
ForceField::MMFF94AromaticAtomTypeDefinitionTable::removeEntry(const EntryIterator& it)
{
	if (it >= entries.end())
		throw Base::IndexError("MMFF94AromaticAtomTypeDefinitionTable: iterator out of bounds");

	return entries.erase(it);
}

void ForceField::MMFF94AromaticAtomTypeDefinitionTable::load(std::istream& is)
{
	std::string line;
	std::string old_type;
	std::string aro_type;
	unsigned int atomic_no;
	std::size_t r_size;
	std::size_t het_dist;
	unsigned int im_flag;
	unsigned int n5_flag;

	while (readMMFF94DataLine(is, line, "MMFF94AromaticAtomTypeDefinitionTable: error while reading aromatic atom type definition entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> old_type))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading old symbolic type");
		
		if (!(line_iss >> aro_type))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading new symbolic aromatic type");
	
		if (!(line_iss >> atomic_no))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading atomic number");
	
		if (!(line_iss >> r_size))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading ringe size");
	
		if (!(line_iss >> het_dist))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading unique hetero atom distance");

		if (!(line_iss >> im_flag))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading imidazolium cation flag");
	
		if (!(line_iss >> n5_flag))
			throw Base::IOError("MMFF94AromaticAtomTypeDefinitionTable: error while reading N5 flag");
	
		addEntry(old_type, aro_type, atomic_no, r_size, het_dist, im_flag, n5_flag);
	}
}

void ForceField::MMFF94AromaticAtomTypeDefinitionTable::loadDefaults()
{
	boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS, 
																std::strlen(MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS));
	load(is);
}

void ForceField::MMFF94AromaticAtomTypeDefinitionTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const ForceField::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& ForceField::MMFF94AromaticAtomTypeDefinitionTable::get()
{
 	std::call_once(initBuiltinTableFlag, &initBuiltinTable);

	return defaultTable;
}
