/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94TorsionParameterTable.cpp 
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

#include <boost/bind.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"
#include "CDPL/ForceField/MMFF94ParameterSet.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL; 


namespace
{
 
    ForceField::MMFF94TorsionParameterTable::SharedPointer builtinDynTable(new ForceField::MMFF94TorsionParameterTable());
    ForceField::MMFF94TorsionParameterTable::SharedPointer builtinStatTable(new ForceField::MMFF94TorsionParameterTable());
    ForceField::MMFF94TorsionParameterTable::SharedPointer builtinStatRefTable(new ForceField::MMFF94TorsionParameterTable());

	std::once_flag initBuiltinTablesFlag;

	void initBuiltinTables() 
	{
		using namespace ForceField;

		builtinDynTable->loadDefaults(MMFF94ParameterSet::DYNAMIC);
		builtinStatTable->loadDefaults(MMFF94ParameterSet::STATIC);
		builtinStatRefTable->loadDefaults(MMFF94ParameterSet::STATIC_RTOR);
	}

	std::uint64_t lookupKey(std::uint32_t tor_type_idx, std::uint32_t term_atom1_type, std::uint32_t ctr_atom1_type, std::uint32_t ctr_atom2_type, std::uint32_t term_atom2_type)
	{
		if (term_atom1_type < term_atom2_type || (term_atom1_type == term_atom2_type && ctr_atom1_type <= ctr_atom2_type)) 
			return ((std::uint64_t(term_atom1_type) << 32) + (ctr_atom1_type << 24) + (ctr_atom2_type << 16) + (term_atom2_type << 8) + tor_type_idx);

		return ((std::uint64_t(term_atom2_type) << 32) + (ctr_atom2_type << 24) + (ctr_atom1_type << 16) + (term_atom1_type << 8) + tor_type_idx);
	}

	const ForceField::MMFF94TorsionParameterTable::Entry NOT_FOUND;
}


ForceField::MMFF94TorsionParameterTable::SharedPointer ForceField::MMFF94TorsionParameterTable::defaultDynTable     = builtinDynTable;
ForceField::MMFF94TorsionParameterTable::SharedPointer ForceField::MMFF94TorsionParameterTable::defaultStatTable    = builtinStatTable;
ForceField::MMFF94TorsionParameterTable::SharedPointer ForceField::MMFF94TorsionParameterTable::defaultStatRefTable = builtinStatRefTable;


ForceField::MMFF94TorsionParameterTable::Entry::Entry():
	torTypeIdx(0), termAtom1Type(0), ctrAtom1Type(0), ctrAtom2Type(0), termAtom2Type(0),
	torParam1(0), torParam2(0), torParam3(0), initialized(false)
{}

ForceField::MMFF94TorsionParameterTable::Entry::Entry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
													  unsigned int term_atom2_type, double tor_param1, double tor_param2, double tor_param3):
	torTypeIdx(tor_type_idx), termAtom1Type(term_atom1_type), ctrAtom1Type(ctr_atom1_type), ctrAtom2Type(term_atom2_type), termAtom2Type(term_atom2_type),
	torParam1(tor_param1), torParam2(tor_param2), torParam3(tor_param3), initialized(true)
{}

unsigned int ForceField::MMFF94TorsionParameterTable::Entry::getTorsionTypeIndex() const
{
	return torTypeIdx;
}

unsigned int ForceField::MMFF94TorsionParameterTable::Entry::getTerminalAtom1Type() const
{
	return termAtom1Type;
}

unsigned int ForceField::MMFF94TorsionParameterTable::Entry::getCenterAtom1Type() const
{
	return ctrAtom1Type;
}

unsigned int ForceField::MMFF94TorsionParameterTable::Entry::getCenterAtom2Type() const
{
	return ctrAtom2Type;
}

unsigned int ForceField::MMFF94TorsionParameterTable::Entry::getTerminalAtom2Type() const
{
	return termAtom2Type;
}

double ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter1() const
{
	return torParam1;
}

double ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter2() const
{
	return torParam2;
}

double ForceField::MMFF94TorsionParameterTable::Entry::getTorsionParameter3() const
{
	return torParam3;
}

ForceField::MMFF94TorsionParameterTable::Entry::operator bool() const
{
	return initialized;
}


ForceField::MMFF94TorsionParameterTable::MMFF94TorsionParameterTable()
{}

void ForceField::MMFF94TorsionParameterTable::addEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
													   unsigned int term_atom2_type, double tor_param1, double tor_param2, double tor_param3)
{
    entries.insert(DataStorage::value_type(lookupKey(tor_type_idx, term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type), 
										   Entry(tor_type_idx, term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type, tor_param1, tor_param2, tor_param3)));
}

const ForceField::MMFF94TorsionParameterTable::Entry& 
ForceField::MMFF94TorsionParameterTable::getEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, 
												  unsigned int ctr_atom2_type, unsigned int term_atom2_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(tor_type_idx, term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t ForceField::MMFF94TorsionParameterTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94TorsionParameterTable::clear()
{
    entries.clear();
}

bool ForceField::MMFF94TorsionParameterTable::removeEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, 
														  unsigned int ctr_atom2_type, unsigned int term_atom2_type)
{
	return entries.erase(lookupKey(tor_type_idx, term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type));
}

ForceField::MMFF94TorsionParameterTable::EntryIterator 
ForceField::MMFF94TorsionParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

ForceField::MMFF94TorsionParameterTable::ConstEntryIterator 
ForceField::MMFF94TorsionParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

ForceField::MMFF94TorsionParameterTable::ConstEntryIterator 
ForceField::MMFF94TorsionParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
ForceField::MMFF94TorsionParameterTable::EntryIterator 
ForceField::MMFF94TorsionParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

ForceField::MMFF94TorsionParameterTable::EntryIterator 
ForceField::MMFF94TorsionParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void ForceField::MMFF94TorsionParameterTable::load(std::istream& is)
{
    std::string line;
	unsigned int tor_type_idx;
	unsigned int term_atom1_type;
	unsigned int ctr_atom1_type;
	unsigned int ctr_atom2_type;
	unsigned int term_atom2_type;
	double tor_param1;
	double tor_param2;
	double tor_param3;

    while (readMMFF94DataLine(is, line, "MMFF94TorsionParameterTable: error while reading torsion parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> tor_type_idx))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading torsion type index");

		if (!(line_iss >> term_atom1_type))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading terminal atom 1 type");

		if (!(line_iss >> ctr_atom1_type))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading center atom 1 type");

		if (!(line_iss >> ctr_atom2_type))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading center atom 2 type");

		if (!(line_iss >> term_atom2_type))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading terminal atom 2 type");

		if (!(line_iss >> tor_param1))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading torsion parameter 1");

		if (!(line_iss >> tor_param2))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading torsion parameter 2");

		if (!(line_iss >> tor_param3))
			throw Base::IOError("MMFF94TorsionParameterTable: error while reading torsion parameter 3");

		addEntry(tor_type_idx, term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type, tor_param1, tor_param2, tor_param3);
    }
}

void ForceField::MMFF94TorsionParameterTable::loadDefaults(unsigned int param_set)
{
	if (param_set == MMFF94ParameterSet::DYNAMIC) {
		boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::TORSION_PARAMETERS, 
																	std::strlen(MMFF94ParameterData::TORSION_PARAMETERS));
		load(is);

	} else if (param_set == MMFF94ParameterSet::STATIC_RTOR || param_set == MMFF94ParameterSet::STATIC_RTOR_XOOP) {
		boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::STATIC_REF_TORSION_PARAMETERS, 
																	std::strlen(MMFF94ParameterData::STATIC_REF_TORSION_PARAMETERS));
		load(is);

	} else {
		boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::STATIC_TORSION_PARAMETERS, 
																	std::strlen(MMFF94ParameterData::STATIC_TORSION_PARAMETERS));
		load(is);
	}
}

void ForceField::MMFF94TorsionParameterTable::set(const SharedPointer& table, unsigned int param_set)
{	
	switch (param_set) {
		
		case MMFF94ParameterSet::DYNAMIC:
			defaultDynTable = (!table ? builtinDynTable : table);
			return;

		case MMFF94ParameterSet::STATIC_RTOR:
		case MMFF94ParameterSet::STATIC_RTOR_XOOP:
			defaultStatRefTable = (!table ? builtinStatRefTable : table);
			return;

		default:
			defaultStatTable = (!table ? builtinStatTable : table);

	}
}

const ForceField::MMFF94TorsionParameterTable::SharedPointer& ForceField::MMFF94TorsionParameterTable::get(unsigned int param_set)
{
 	std::call_once(initBuiltinTablesFlag, &initBuiltinTables);

	switch (param_set) {
		
		case MMFF94ParameterSet::DYNAMIC:
			return defaultDynTable;

		case MMFF94ParameterSet::STATIC_RTOR:
		case MMFF94ParameterSet::STATIC_RTOR_XOOP:
			return defaultStatRefTable;

		default:
			break;
	}

	return defaultStatTable;
}
