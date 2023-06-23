/* 
 * MMFF94BondStretchingParameterTable.cpp 
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

#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL; 


namespace
{
 
    ForceField::MMFF94BondStretchingParameterTable::SharedPointer builtinTable(new ForceField::MMFF94BondStretchingParameterTable());

	std::once_flag initBuiltinTableFlag;

	void initBuiltinTable() 
	{
		builtinTable->loadDefaults();
	}

	std::uint32_t lookupKey(std::uint32_t bnd_type_idx, std::uint32_t atom1_type, std::uint32_t atom2_type)
	{
		if (atom1_type < atom2_type)
			return ((atom1_type << 16) + (atom2_type << 8) + bnd_type_idx);

		return ((atom2_type << 16) + (atom1_type << 8) + bnd_type_idx);
	}

	const ForceField::MMFF94BondStretchingParameterTable::Entry NOT_FOUND;
}


ForceField::MMFF94BondStretchingParameterTable::SharedPointer ForceField::MMFF94BondStretchingParameterTable::defaultTable = builtinTable;


ForceField::MMFF94BondStretchingParameterTable::Entry::Entry():
  	bondTypeIdx(0), atom1Type(0), atom2Type(0), forceConst(0), refLength(0), initialized(false)
{}

ForceField::MMFF94BondStretchingParameterTable::Entry::Entry(unsigned int bond_type_idx, unsigned int atom1_type, 
															 unsigned int atom2_type, double force_const, double ref_length):
	bondTypeIdx(bond_type_idx), atom1Type(atom1_type), atom2Type(atom2_type), 
	forceConst(force_const), refLength(ref_length), initialized(true)
{}

unsigned int ForceField::MMFF94BondStretchingParameterTable::Entry::getBondTypeIndex() const
{
	return bondTypeIdx;
}

unsigned int ForceField::MMFF94BondStretchingParameterTable::Entry::getAtom1Type() const
{
	return atom1Type;
}

unsigned int ForceField::MMFF94BondStretchingParameterTable::Entry::getAtom2Type() const
{
	return atom2Type;
}

double ForceField::MMFF94BondStretchingParameterTable::Entry::getForceConstant() const
{
	return forceConst;
}

double ForceField::MMFF94BondStretchingParameterTable::Entry::getReferenceLength() const
{
	return refLength;
}

ForceField::MMFF94BondStretchingParameterTable::Entry::operator bool() const
{
	return initialized;
}


ForceField::MMFF94BondStretchingParameterTable::MMFF94BondStretchingParameterTable()
{}

void ForceField::MMFF94BondStretchingParameterTable::addEntry(unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type,
															  double force_const, double ref_length)
{
    entries.insert(DataStorage::value_type(lookupKey(bond_type_idx, atom1_type, atom2_type), 
										   Entry(bond_type_idx, atom1_type, atom2_type, force_const, ref_length)));
}

const ForceField::MMFF94BondStretchingParameterTable::Entry& 
ForceField::MMFF94BondStretchingParameterTable::getEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
														 unsigned int atom2_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(bnd_type_idx, atom1_type, atom2_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t ForceField::MMFF94BondStretchingParameterTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94BondStretchingParameterTable::clear()
{
    entries.clear();
}

bool ForceField::MMFF94BondStretchingParameterTable::removeEntry(unsigned int bnd_type_idx, unsigned int atom1_type, 
																 unsigned int atom2_type)
{
	return entries.erase(lookupKey(bnd_type_idx, atom1_type, atom2_type));
}

ForceField::MMFF94BondStretchingParameterTable::EntryIterator 
ForceField::MMFF94BondStretchingParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingParameterTable::ConstEntryIterator 
ForceField::MMFF94BondStretchingParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingParameterTable::ConstEntryIterator 
ForceField::MMFF94BondStretchingParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}
	
ForceField::MMFF94BondStretchingParameterTable::EntryIterator 
ForceField::MMFF94BondStretchingParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingParameterTable::EntryIterator 
ForceField::MMFF94BondStretchingParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingParameterTable::ConstEntryIterator 
ForceField::MMFF94BondStretchingParameterTable::begin() const
{
	return ConstEntryIterator(entries.begin(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingParameterTable::ConstEntryIterator 
ForceField::MMFF94BondStretchingParameterTable::end() const
{
	return ConstEntryIterator(entries.end(), std::bind(&DataStorage::value_type::second, std::placeholders::_1));
}
	
ForceField::MMFF94BondStretchingParameterTable::EntryIterator 
ForceField::MMFF94BondStretchingParameterTable::begin()
{
	return EntryIterator(entries.begin(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

ForceField::MMFF94BondStretchingParameterTable::EntryIterator 
ForceField::MMFF94BondStretchingParameterTable::end()
{
	return EntryIterator(entries.end(), std::bind<Entry&>(&DataStorage::value_type::second, std::placeholders::_1));
}

void ForceField::MMFF94BondStretchingParameterTable::load(std::istream& is)
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

void ForceField::MMFF94BondStretchingParameterTable::loadDefaults()
{
    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::BOND_STRETCHING_PARAMETERS, 
																std::strlen(MMFF94ParameterData::BOND_STRETCHING_PARAMETERS));
    load(is);
}

void ForceField::MMFF94BondStretchingParameterTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const ForceField::MMFF94BondStretchingParameterTable::SharedPointer& ForceField::MMFF94BondStretchingParameterTable::get()
{
	std::call_once(initBuiltinTableFlag, &initBuiltinTable);

    return defaultTable;
}
