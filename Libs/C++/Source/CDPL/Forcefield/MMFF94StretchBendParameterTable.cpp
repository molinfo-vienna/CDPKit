/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94StretchBendParameterTable.cpp 
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

#include "CDPL/Forcefield/MMFF94StretchBendParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94StretchBendParameterTable::SharedPointer builtinTable(new Forcefield::MMFF94StretchBendParameterTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

	Base::uint32 lookupKey(Base::uint32 sb_type_idx, Base::uint32 term_atom1_type, Base::uint32 ctr_atom_type, Base::uint32 term_atom2_type)
	{
		if (term_atom1_type < term_atom2_type)
			return ((term_atom1_type << 24) + (ctr_atom_type << 16) + (term_atom2_type << 8) + sb_type_idx);

		return ((term_atom2_type << 24) + (ctr_atom_type << 16) + (term_atom1_type << 8) + sb_type_idx);
	}

	const Forcefield::MMFF94StretchBendParameterTable::Entry NOT_FOUND;
}


Forcefield::MMFF94StretchBendParameterTable::SharedPointer Forcefield::MMFF94StretchBendParameterTable::defaultTable = builtinTable;


Forcefield::MMFF94StretchBendParameterTable::Entry::Entry():
	sbTypeIdx(0), termAtom1Type(0), ctrAtomType(0), termAtom2Type(0),
	ijkForceConst(0), kjiForceConst(0), initialized(false)
{}

Forcefield::MMFF94StretchBendParameterTable::Entry::Entry(unsigned int sb_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
														  unsigned int term_atom2_type, double force_const, double kji_force_const):
	sbTypeIdx(sb_type_idx), termAtom1Type(term_atom1_type), ctrAtomType(ctr_atom_type), termAtom2Type(term_atom2_type),
	ijkForceConst(force_const), kjiForceConst(kji_force_const), initialized(true)
{}

unsigned int Forcefield::MMFF94StretchBendParameterTable::Entry::getStretchBendTypeIndex() const
{
	return sbTypeIdx;
}

unsigned int Forcefield::MMFF94StretchBendParameterTable::Entry::getTerminalAtom1Type() const
{
	return termAtom1Type;
}

unsigned int Forcefield::MMFF94StretchBendParameterTable::Entry::getCenterAtomType() const
{
	return ctrAtomType;
}

unsigned int Forcefield::MMFF94StretchBendParameterTable::Entry::getTerminalAtom2Type() const
{
	return termAtom2Type;
}

double Forcefield::MMFF94StretchBendParameterTable::Entry::getIJKForceConstant() const
{
	return ijkForceConst;
}

double Forcefield::MMFF94StretchBendParameterTable::Entry::getKJIForceConstant() const
{
	return kjiForceConst;
}

Forcefield::MMFF94StretchBendParameterTable::Entry::operator bool() const
{
	return initialized;
}


Forcefield::MMFF94StretchBendParameterTable::MMFF94StretchBendParameterTable()
{}

void Forcefield::MMFF94StretchBendParameterTable::addEntry(unsigned int sb_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
														   unsigned int term_atom2_type, double ijk_force_const, double kji_force_const)
{
    entries.insert(DataStorage::value_type(lookupKey(sb_type_idx, term_atom1_type,  ctr_atom_type, term_atom2_type), 
										   Entry(sb_type_idx, term_atom1_type, ctr_atom_type, term_atom2_type, ijk_force_const, kji_force_const)));
}

const Forcefield::MMFF94StretchBendParameterTable::Entry& 
Forcefield::MMFF94StretchBendParameterTable::getEntry(unsigned int sb_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
													  unsigned int term_atom2_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(sb_type_idx, term_atom1_type,  ctr_atom_type, term_atom2_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t Forcefield::MMFF94StretchBendParameterTable::getNumEntries() const
{
    return entries.size();
}

void Forcefield::MMFF94StretchBendParameterTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94StretchBendParameterTable::removeEntry(unsigned int sb_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
															  unsigned int term_atom2_type)
{
	return entries.erase(lookupKey(sb_type_idx, term_atom1_type,  ctr_atom_type, term_atom2_type));
}

Forcefield::MMFF94StretchBendParameterTable::EntryIterator 
Forcefield::MMFF94StretchBendParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94StretchBendParameterTable::ConstEntryIterator 
Forcefield::MMFF94StretchBendParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94StretchBendParameterTable::ConstEntryIterator 
Forcefield::MMFF94StretchBendParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94StretchBendParameterTable::EntryIterator 
Forcefield::MMFF94StretchBendParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94StretchBendParameterTable::EntryIterator 
Forcefield::MMFF94StretchBendParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94StretchBendParameterTable::load(std::istream& is)
{
    std::string line;
	unsigned int sb_type_idx;
	unsigned int term_atom1_type;
	unsigned int ctr_atom_type;
	unsigned int term_atom2_type;
	double ijk_force_const;
	double kji_force_const;

    while (readMMFF94DataLine(is, line, "MMFF94StretchBendParameterTable: error while reading stretch bend parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> sb_type_idx))
			throw Base::IOError("MMFF94StretchBendParameterTable: error while reading stretch bend type index");

		if (!(line_iss >> term_atom1_type))
			throw Base::IOError("MMFF94StretchBendParameterTable: error while reading terminal atom 1 type");

		if (!(line_iss >> ctr_atom_type))
			throw Base::IOError("MMFF94StretchBendParameterTable: error while reading center atom type");

		if (!(line_iss >> term_atom2_type))
			throw Base::IOError("MMFF94StretchBendParameterTable: error while reading terminal atom 2 type");
	
		if (!(line_iss >> ijk_force_const))
			throw Base::IOError("MMFF94StretchBendParameterTable: error while reading IJK force constant");

		if (!(line_iss >> kji_force_const))
			throw Base::IOError("MMFF94StretchBendParameterTable: error while reading KJI force constant");

		addEntry(sb_type_idx, term_atom1_type, ctr_atom_type, term_atom2_type, ijk_force_const, kji_force_const);
    }
}

void Forcefield::MMFF94StretchBendParameterTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::STRETCH_BEND_PARAMETERS, 
																std::strlen(MMFF94ParameterData::STRETCH_BEND_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::STRETCH_BEND_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94StretchBendParameterTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94StretchBendParameterTable::SharedPointer& Forcefield::MMFF94StretchBendParameterTable::get()
{
    return defaultTable;
}
