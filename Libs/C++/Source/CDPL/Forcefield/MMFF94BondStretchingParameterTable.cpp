/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingParameterTable.cpp 
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

#include "CDPL/Forcefield/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94BondStretchingParameterTable::SharedPointer builtinTable(new Forcefield::MMFF94BondStretchingParameterTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

	Base::uint32 lookupKey(Base::uint32 bnd_type_idx, Base::uint32 atom1_type, Base::uint32 atom2_type)
	{
		if (atom1_type < atom2_type)
			return ((atom1_type << 16) + (atom2_type << 8) + bnd_type_idx);

		return ((atom2_type << 16) + (atom1_type << 8) + bnd_type_idx);
	}

	const Forcefield::MMFF94BondStretchingParameterTable::Entry NOT_FOUND;
}


Forcefield::MMFF94BondStretchingParameterTable::SharedPointer Forcefield::MMFF94BondStretchingParameterTable::defaultTable = builtinTable;


Forcefield::MMFF94BondStretchingParameterTable::Entry::Entry():
  	bondTypeIdx(0), atom1Type(0), atom2Type(0), forceConst(0), refLength(0), initialized(false)
{}

Forcefield::MMFF94BondStretchingParameterTable::Entry::Entry(unsigned int bond_type_idx, unsigned int atom1_type, 
															 unsigned int atom2_type, double force_const, double ref_length):
	bondTypeIdx(bond_type_idx), atom1Type(atom1_type), atom2Type(atom2_type), 
	forceConst(force_const), refLength(ref_length), initialized(true)
{}

unsigned int Forcefield::MMFF94BondStretchingParameterTable::Entry::getBondTypeIndex() const
{
	return bondTypeIdx;
}

unsigned int Forcefield::MMFF94BondStretchingParameterTable::Entry::getAtom1Type() const
{
	return atom1Type;
}

unsigned int Forcefield::MMFF94BondStretchingParameterTable::Entry::getAtom2Type() const
{
	return atom2Type;
}

double Forcefield::MMFF94BondStretchingParameterTable::Entry::getForceConstant() const
{
	return forceConst;
}

double Forcefield::MMFF94BondStretchingParameterTable::Entry::getReferenceBondLength() const
{
	return refLength;
}

Forcefield::MMFF94BondStretchingParameterTable::Entry::operator bool() const
{
	return initialized;
}


Forcefield::MMFF94BondStretchingParameterTable::MMFF94BondStretchingParameterTable()
{}

void Forcefield::MMFF94BondStretchingParameterTable::addEntry(unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type,
															  double force_const, double ref_length)
{
    entries.insert(DataStorage::value_type(lookupKey(bond_type_idx, atom1_type, atom2_type), 
										   Entry(bond_type_idx, atom1_type, atom2_type, force_const, ref_length)));
}

const Forcefield::MMFF94BondStretchingParameterTable::Entry& 
Forcefield::MMFF94BondStretchingParameterTable::getEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
														 unsigned int atom2_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(bnd_type_idx, atom1_type, atom2_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t Forcefield::MMFF94BondStretchingParameterTable::getNumEntries() const
{
    return entries.size();
}

void Forcefield::MMFF94BondStretchingParameterTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94BondStretchingParameterTable::removeEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
																 unsigned int atom2_type)
{
	return entries.erase(lookupKey(bnd_type_idx, atom1_type, atom2_type));
}

Forcefield::MMFF94BondStretchingParameterTable::EntryIterator 
Forcefield::MMFF94BondStretchingParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94BondStretchingParameterTable::ConstEntryIterator 
Forcefield::MMFF94BondStretchingParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94BondStretchingParameterTable::ConstEntryIterator 
Forcefield::MMFF94BondStretchingParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94BondStretchingParameterTable::EntryIterator 
Forcefield::MMFF94BondStretchingParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94BondStretchingParameterTable::EntryIterator 
Forcefield::MMFF94BondStretchingParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94BondStretchingParameterTable::load(std::istream& is)
{
    std::string line;
	unsigned int bnd_type_idx;
	unsigned int atom1_type;
	unsigned int atom2_type;
	double force_const;
	double ref_length;

    while (readMMFF94DataLine(is, line, "MMFF94BondStretchingParameterTable: error while bond stretching parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> bnd_type_idx))
			throw Base::IOError("MMFF94BondStretchingParameterTable: error while reading bond type index");
	
		if (!(line_iss >> atom1_type))
			throw Base::IOError("MMFF94BondStretchingParameterTable: error while reading type of first atom");

		if (!(line_iss >> atom2_type))
			throw Base::IOError("MMFF94BondStretchingParameterTable: error while reading type of second atom");

		if (!(line_iss >> force_const))
			throw Base::IOError("MMFF94BondStretchingParameterTable: error while reading force constant");
	
		if (!(line_iss >> ref_length))
			throw Base::IOError("MMFF94BondStretchingParameterTable: error while reading reference bond length");
		
		addEntry(bnd_type_idx, atom1_type, atom2_type, force_const, ref_length);
    }
}

void Forcefield::MMFF94BondStretchingParameterTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::BOND_STRETCHING_PARAMETERS, 
																std::strlen(MMFF94ParameterData::BOND_STRETCHING_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::BOND_STRETCHING_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94BondStretchingParameterTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94BondStretchingParameterTable::SharedPointer& Forcefield::MMFF94BondStretchingParameterTable::get()
{
    return defaultTable;
}
