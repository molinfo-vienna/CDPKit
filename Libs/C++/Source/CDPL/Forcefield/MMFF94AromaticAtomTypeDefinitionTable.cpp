/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AromaticAtomTypeDefinitionTable.cpp 
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

#include "CDPL/Config.hpp"

#include <cstring>
#include <sstream>

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Forcefield/MMFF94AromaticAtomTypeDefinitionTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer builtinTable(new Forcefield::MMFF94AromaticAtomTypeDefinitionTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;
}


Forcefield::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer Forcefield::MMFF94AromaticAtomTypeDefinitionTable::defaultTable = builtinTable;


Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::Entry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no, 
																std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion):
	oldType(old_type), aroType(aro_type), atomicNumber(atomic_no), ringSize(ring_size), hetAtomDist(het_atom_dist), imCation(im_cation), n5Anion(n5_anion)
{}

const std::string& Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::getOldSymbolicAtomType() const
{
	return oldType;
}
				
const std::string& Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAromSymbolicAtomType() const
{
	return aroType;
}
				
unsigned int Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::getAtomicNumber() const
{
	return atomicNumber;
}

std::size_t Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::getRingSize() const
{
	return ringSize;
}

std::size_t Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::getHeteroAtomDistance() const
{
	return hetAtomDist;
}

bool Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::isImidazoliumCation() const
{
	return imCation;
}

bool Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry::isN5RingAnion() const
{
	return n5Anion;
}


Forcefield::MMFF94AromaticAtomTypeDefinitionTable::MMFF94AromaticAtomTypeDefinitionTable()
{}

std::size_t Forcefield::MMFF94AromaticAtomTypeDefinitionTable::getNumEntries() const
{
    return entries.size();
}

void Forcefield::MMFF94AromaticAtomTypeDefinitionTable::addEntry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no, 
																 std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion)
{
    entries.push_back(Entry(old_type, aro_type, atomic_no, ring_size, het_atom_dist, im_cation, n5_anion));
}

const Forcefield::MMFF94AromaticAtomTypeDefinitionTable::Entry& Forcefield::MMFF94AromaticAtomTypeDefinitionTable::getEntry(std::size_t idx) const
{
	if (idx >= entries.size())
		throw Base::IndexError("MMFF94AromaticAtomTypeDefinitionTable: entry index out of bounds");

	return entries[idx];
}

Forcefield::MMFF94AromaticAtomTypeDefinitionTable::ConstEntryIterator 
Forcefield::MMFF94AromaticAtomTypeDefinitionTable::getEntriesBegin() const
{
    return entries.begin();
}

Forcefield::MMFF94AromaticAtomTypeDefinitionTable::ConstEntryIterator 
Forcefield::MMFF94AromaticAtomTypeDefinitionTable::getEntriesEnd() const
{
    return entries.end();
}

Forcefield::MMFF94AromaticAtomTypeDefinitionTable::EntryIterator 
Forcefield::MMFF94AromaticAtomTypeDefinitionTable::getEntriesBegin()
{
	return entries.begin();
}

Forcefield::MMFF94AromaticAtomTypeDefinitionTable::EntryIterator 
Forcefield::MMFF94AromaticAtomTypeDefinitionTable::getEntriesEnd()
{
	return entries.end();
}

void Forcefield::MMFF94AromaticAtomTypeDefinitionTable::clear()
{
    entries.clear();
}

void Forcefield::MMFF94AromaticAtomTypeDefinitionTable::removeEntry(std::size_t idx)
{
	if (idx >= entries.size())
		throw Base::IndexError("MMFF94AromaticAtomTypeDefinitionTable: entry index out of bounds");

	entries.erase(entries.begin() + idx);
}

Forcefield::MMFF94AromaticAtomTypeDefinitionTable::EntryIterator 
Forcefield::MMFF94AromaticAtomTypeDefinitionTable::removeEntry(const EntryIterator& it)
{
	if (it >= entries.end())
		throw Base::IndexError("MMFF94AromaticAtomTypeDefinitionTable: iterator out of bounds");

	return entries.erase(it);
}

void Forcefield::MMFF94AromaticAtomTypeDefinitionTable::load(std::istream& is)
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

void Forcefield::MMFF94AromaticAtomTypeDefinitionTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

	boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS, 
																std::strlen(MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

	load(is);
}

void Forcefield::MMFF94AromaticAtomTypeDefinitionTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& Forcefield::MMFF94AromaticAtomTypeDefinitionTable::get()
{
    return defaultTable;
}
