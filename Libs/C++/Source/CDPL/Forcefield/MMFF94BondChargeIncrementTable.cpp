/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondChargeIncrementTable.cpp 
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

#include "CDPL/Forcefield/MMFF94BondChargeIncrementTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94BondChargeIncrementTable::SharedPointer builtinTable(new Forcefield::MMFF94BondChargeIncrementTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

	std::size_t lookupKey(unsigned int bnd_type_idx, unsigned int atom1_type, unsigned int atom2_type)
	{
		if (atom1_type < atom2_type)
			return (atom1_type * 256 * 8 + atom2_type * 8 + bnd_type_idx);

		return (atom2_type * 256 * 8 + atom1_type * 8 + bnd_type_idx);
	}

	const Forcefield::MMFF94BondChargeIncrementTable::Entry NOT_FOUND;
}


Forcefield::MMFF94BondChargeIncrementTable::SharedPointer Forcefield::MMFF94BondChargeIncrementTable::defaultTable = builtinTable;


Forcefield::MMFF94BondChargeIncrementTable::Entry::Entry():
  	bondTypeIdx(0), atom1Type(0), atom2Type(0), chargeIncr(0)
{}

Forcefield::MMFF94BondChargeIncrementTable::Entry::Entry(unsigned int bond_type_idx, unsigned int atom1_type, 
														 unsigned int atom2_type, double bond_chg_inc):
	bondTypeIdx(bond_type_idx), atom1Type(atom1_type), atom2Type(atom2_type), chargeIncr(bond_chg_inc)
{}

unsigned int Forcefield::MMFF94BondChargeIncrementTable::Entry::getBondTypeIndex() const
{
	return bondTypeIdx;
}

unsigned int Forcefield::MMFF94BondChargeIncrementTable::Entry::getAtom1Type() const
{
	return atom1Type;
}

unsigned int Forcefield::MMFF94BondChargeIncrementTable::Entry::getAtom2Type() const
{
	return atom2Type;
}

double Forcefield::MMFF94BondChargeIncrementTable::Entry::getChargeIncrement() const
{
	return chargeIncr;
}

Forcefield::MMFF94BondChargeIncrementTable::Entry::operator bool() const
{
	return (atom1Type > 0 && atom2Type > 0);
}


Forcefield::MMFF94BondChargeIncrementTable::MMFF94BondChargeIncrementTable()
{}

void Forcefield::MMFF94BondChargeIncrementTable::addEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
														  unsigned int atom2_type, double bond_chg_inc)
{
    entries.insert(DataStorage::value_type(lookupKey(bnd_type_idx, atom1_type, atom2_type), 
										   Entry(bnd_type_idx, atom1_type, atom2_type, bond_chg_inc)));
}

const Forcefield::MMFF94BondChargeIncrementTable::Entry& 
Forcefield::MMFF94BondChargeIncrementTable::getEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
													 unsigned int atom2_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(bnd_type_idx, atom1_type, atom2_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

void Forcefield::MMFF94BondChargeIncrementTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94BondChargeIncrementTable::removeEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
															 unsigned int atom2_type)
{
	return entries.erase(lookupKey(bnd_type_idx, atom1_type, atom2_type));
}

Forcefield::MMFF94BondChargeIncrementTable::EntryIterator 
Forcefield::MMFF94BondChargeIncrementTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94BondChargeIncrementTable::ConstEntryIterator 
Forcefield::MMFF94BondChargeIncrementTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94BondChargeIncrementTable::ConstEntryIterator 
Forcefield::MMFF94BondChargeIncrementTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94BondChargeIncrementTable::EntryIterator 
Forcefield::MMFF94BondChargeIncrementTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94BondChargeIncrementTable::EntryIterator 
Forcefield::MMFF94BondChargeIncrementTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94BondChargeIncrementTable::load(std::istream& is)
{
    std::string line;
	unsigned int bnd_type_idx;
	unsigned int atom1_type;
	unsigned int atom2_type;
	double bond_chg_inc;

    while (readMMFF94DataLine(is, line, "MMFF94BondChargeIncrementTable: error while reading bond charge increment parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> bnd_type_idx))
			throw Base::IOError("MMFF94BondChargeIncrementTable: error while reading bond type index");
	
		if (!(line_iss >> atom1_type))
			throw Base::IOError("MMFF94BondChargeIncrementTable: error while reading numeric type of first atom");

		if (!(line_iss >> atom2_type))
			throw Base::IOError("MMFF94BondChargeIncrementTable: error while reading numeric type of second atom");

		if (!(line_iss >> bond_chg_inc))
			throw Base::IOError("MMFF94BondChargeIncrementTable: error while reading bond charge increment");
		
		addEntry(bnd_type_idx, atom1_type, atom2_type, bond_chg_inc);
    }
}

void Forcefield::MMFF94BondChargeIncrementTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::BOND_CHARGE_INCREMENT_PARAMETERS, 
																std::strlen(MMFF94ParameterData::BOND_CHARGE_INCREMENT_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::BOND_CHARGE_INCREMENT_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94BondChargeIncrementTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94BondChargeIncrementTable::SharedPointer& Forcefield::MMFF94BondChargeIncrementTable::get()
{
    return defaultTable;
}
