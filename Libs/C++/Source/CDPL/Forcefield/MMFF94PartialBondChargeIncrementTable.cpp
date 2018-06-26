/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94PartialBondChargeIncrementTable.cpp 
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

#include "CDPL/Forcefield/MMFF94PartialBondChargeIncrementTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94PartialBondChargeIncrementTable::SharedPointer builtinTable(new Forcefield::MMFF94PartialBondChargeIncrementTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

	const Forcefield::MMFF94PartialBondChargeIncrementTable::Entry NOT_FOUND;
}


Forcefield::MMFF94PartialBondChargeIncrementTable::SharedPointer 
Forcefield::MMFF94PartialBondChargeIncrementTable::defaultTable   = builtinTable;


Forcefield::MMFF94PartialBondChargeIncrementTable::Entry::Entry():
  	atomType(0), partChargeIncr(0), formChargeAdjFactor(0)
{}

Forcefield::MMFF94PartialBondChargeIncrementTable::Entry::Entry(unsigned int atom_type, double part_bond_chg_inc, double form_chg_adj_factor):
	atomType(atom_type), partChargeIncr(part_bond_chg_inc), formChargeAdjFactor(form_chg_adj_factor)
{}

unsigned int Forcefield::MMFF94PartialBondChargeIncrementTable::Entry::getAtomType() const
{
	return atomType;
}

double Forcefield::MMFF94PartialBondChargeIncrementTable::Entry::getPartialChargeIncrement() const
{
	return partChargeIncr;
}

double Forcefield::MMFF94PartialBondChargeIncrementTable::Entry::getFormalChargeAdjustmentFactor() const
{
	return formChargeAdjFactor;
}

Forcefield::MMFF94PartialBondChargeIncrementTable::Entry::operator bool() const
{
	return (atomType > 0);
}


Forcefield::MMFF94PartialBondChargeIncrementTable::MMFF94PartialBondChargeIncrementTable()
{}

void Forcefield::MMFF94PartialBondChargeIncrementTable::addEntry(unsigned int atom_type, double part_bond_chg_inc, double form_chg_adj_factor)
{
    entries.insert(DataStorage::value_type(atom_type, Entry(atom_type, part_bond_chg_inc, form_chg_adj_factor)));
}

const Forcefield::MMFF94PartialBondChargeIncrementTable::Entry& 
Forcefield::MMFF94PartialBondChargeIncrementTable::getEntry(unsigned int atom_type) const
{
	DataStorage::const_iterator it = entries.find(atom_type);

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

void Forcefield::MMFF94PartialBondChargeIncrementTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94PartialBondChargeIncrementTable::removeEntry(unsigned int atom_type)
{
	return entries.erase(atom_type);
}

Forcefield::MMFF94PartialBondChargeIncrementTable::EntryIterator 
Forcefield::MMFF94PartialBondChargeIncrementTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94PartialBondChargeIncrementTable::ConstEntryIterator 
Forcefield::MMFF94PartialBondChargeIncrementTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94PartialBondChargeIncrementTable::ConstEntryIterator 
Forcefield::MMFF94PartialBondChargeIncrementTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94PartialBondChargeIncrementTable::EntryIterator 
Forcefield::MMFF94PartialBondChargeIncrementTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94PartialBondChargeIncrementTable::EntryIterator 
Forcefield::MMFF94PartialBondChargeIncrementTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94PartialBondChargeIncrementTable::load(std::istream& is)
{
    std::string line;
	unsigned int atom_type;
	double part_bond_chg_inc;
	double form_chg_adj_factor;

    while (readMMFF94DataLine(is, line, "MMFF94PartialBondChargeIncrementTable: error while reading partial bond charge increment parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> atom_type))
			throw Base::IOError("MMFF94PartialBondChargeIncrementTable: error while reading partial bond charge increment parameter entry");

		if (!(line_iss >> atom_type))
			throw Base::IOError("MMFF94PartialBondChargeIncrementTable: error while reading numeric atom type");

		if (!(line_iss >> part_bond_chg_inc))
			throw Base::IOError("MMFF94PartialBondChargeIncrementTable: error while reading partial bond charge increment");

		if (!(line_iss >> form_chg_adj_factor))
			throw Base::IOError("MMFF94PartialBondChargeIncrementTable: error while reading formal charge adjustment factor");
		
		addEntry(atom_type, part_bond_chg_inc, form_chg_adj_factor);
    }
}

void Forcefield::MMFF94PartialBondChargeIncrementTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS, 
																std::strlen(MMFF94ParameterData::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94PartialBondChargeIncrementTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94PartialBondChargeIncrementTable::SharedPointer& Forcefield::MMFF94PartialBondChargeIncrementTable::get()
{
    return defaultTable;
}
