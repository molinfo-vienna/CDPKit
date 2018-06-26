/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AtomTypePropertyTable.cpp 
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

#include <boost/bind.hpp>

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Forcefield/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94AtomTypePropertyTable::SharedPointer builtinTable(new Forcefield::MMFF94AtomTypePropertyTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

	const Forcefield::MMFF94AtomTypePropertyTable::Entry NOT_FOUND;
}


Forcefield::MMFF94AtomTypePropertyTable::SharedPointer Forcefield::MMFF94AtomTypePropertyTable::defaultTable = builtinTable;


Forcefield::MMFF94AtomTypePropertyTable::Entry::Entry(unsigned int atom_type, unsigned int atomic_no, std::size_t num_nbrs, std::size_t valence, 
													  bool has_pi_lp, bool has_mb, bool is_arom, bool lin_bnd_ang, bool has_mb_or_sb):
    atomType(atom_type), atomicNo(atomic_no), numNeighbors(num_nbrs), valence(valence), hasPiLonePr(has_pi_lp),
    hasMultiBonds(has_mb), isAroType(is_arom), hasLinBondAng(lin_bnd_ang), hasMultiOrSingleBonds(has_mb_or_sb)
{}

Forcefield::MMFF94AtomTypePropertyTable::Entry::Entry():
    atomType(0), atomicNo(0), numNeighbors(0), valence(0), hasPiLonePr(false),
    hasMultiBonds(false), isAroType(false), hasLinBondAng(false), hasMultiOrSingleBonds(false)
{}

unsigned int Forcefield::MMFF94AtomTypePropertyTable::Entry::getAtomType() const
{
	return atomType;
}

unsigned int Forcefield::MMFF94AtomTypePropertyTable::Entry::getAtomicNumber() const
{
	return atomicNo;
}

std::size_t Forcefield::MMFF94AtomTypePropertyTable::Entry::getNumNeighbors() const
{
	return numNeighbors;
}

std::size_t Forcefield::MMFF94AtomTypePropertyTable::Entry::getValence() const
{
	return valence;
}

bool Forcefield::MMFF94AtomTypePropertyTable::Entry::hasPiLonePair() const
{
	return hasPiLonePr;
}

bool Forcefield::MMFF94AtomTypePropertyTable::Entry::formsMultiBonds() const
{
	return hasMultiBonds;
}

bool Forcefield::MMFF94AtomTypePropertyTable::Entry::isAromaticAtomType() const
{
	return isAroType;
}

bool Forcefield::MMFF94AtomTypePropertyTable::Entry::formsLinearBondAngle() const
{
	return hasLinBondAng;
}

bool Forcefield::MMFF94AtomTypePropertyTable::Entry::formsMultiOrSingleBonds() const
{
	return hasMultiOrSingleBonds;
}

Forcefield::MMFF94AtomTypePropertyTable::Entry::operator bool() const
{
	return (atomType > 0);
}


Forcefield::MMFF94AtomTypePropertyTable::MMFF94AtomTypePropertyTable()
{}

void Forcefield::MMFF94AtomTypePropertyTable::addEntry(unsigned int atom_type, unsigned int atomic_no, std::size_t num_nbrs, std::size_t valence, 
													   bool has_pi_lp, bool has_mb, bool is_arom, bool lin_bnd_ang, bool has_mb_or_sb)
{
    entries.insert(DataStorage::value_type(atom_type, Entry(atom_type, atomic_no, num_nbrs, valence, has_pi_lp, has_mb, is_arom, lin_bnd_ang, has_mb_or_sb)));
}

const Forcefield::MMFF94AtomTypePropertyTable::Entry& Forcefield::MMFF94AtomTypePropertyTable::getEntry(unsigned int atom_type) const
{
	DataStorage::const_iterator it = entries.find(atom_type);

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

void Forcefield::MMFF94AtomTypePropertyTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94AtomTypePropertyTable::removeEntry(unsigned int atom_type)
{
	return entries.erase(atom_type);
}

Forcefield::MMFF94AtomTypePropertyTable::EntryIterator 
Forcefield::MMFF94AtomTypePropertyTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94AtomTypePropertyTable::ConstEntryIterator 
Forcefield::MMFF94AtomTypePropertyTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94AtomTypePropertyTable::ConstEntryIterator 
Forcefield::MMFF94AtomTypePropertyTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94AtomTypePropertyTable::EntryIterator 
Forcefield::MMFF94AtomTypePropertyTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94AtomTypePropertyTable::EntryIterator 
Forcefield::MMFF94AtomTypePropertyTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94AtomTypePropertyTable::load(std::istream& is)
{
    std::string line;
    unsigned int atom_type;
	unsigned int atomic_no;
	std::size_t num_nbrs;
	std::size_t valence;
	unsigned int has_pi_lp;
	unsigned int has_mb;
	unsigned int is_arom;
	unsigned int lin_bnd_ang;
	unsigned int has_mb_or_sb;

    while (readMMFF94DataLine(is, line, "MMFF94AtomTypePropertyTable: error while reading atom type properties entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> atom_type))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading numeric atom type");
	
		if (!(line_iss >> atomic_no))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading atomic number");

		if (!(line_iss >> num_nbrs))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading number of bonded neighbors");
	
		if (!(line_iss >> valence))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading valence");
	
		if (!(line_iss >> has_pi_lp))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading pi lone-pair flag");
	
		if (!(line_iss >> has_mb))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading multiple-bond designator");
		
		if (!(line_iss >> is_arom))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading aromatic atom type flag");
	
		if (!(line_iss >> lin_bnd_ang))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading linear bond angle flag");
	
		if (!(line_iss >> has_mb_or_sb))
			throw Base::IOError("MMFF94AtomTypePropertyTable: error while reading linear single-bond multiple-bond designator");
	
		addEntry(atom_type, atomic_no, num_nbrs, valence, has_pi_lp, has_mb, is_arom, lin_bnd_ang, has_mb_or_sb);
    }
}

void Forcefield::MMFF94AtomTypePropertyTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::ATOM_TYPE_PROPERTIES, 
																std::strlen(MMFF94ParameterData::ATOM_TYPE_PROPERTIES));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::ATOM_TYPE_PROPERTIES));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94AtomTypePropertyTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94AtomTypePropertyTable::SharedPointer& Forcefield::MMFF94AtomTypePropertyTable::get()
{
    return defaultTable;
}
