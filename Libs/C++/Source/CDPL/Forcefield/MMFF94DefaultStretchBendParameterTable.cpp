/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94DefaultStretchBendParameterTable.cpp 
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

#include "CDPL/Forcefield/MMFF94DefaultStretchBendParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94DefaultStretchBendParameterTable::SharedPointer builtinTable(new Forcefield::MMFF94DefaultStretchBendParameterTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;

	Base::uint32 lookupKey(Base::uint32 term_atom1_pte_row, Base::uint32 ctr_atom_pte_row, Base::uint32 term_atom2_pte_row)
	{
		if (term_atom1_pte_row < term_atom2_pte_row)
			return ((term_atom1_pte_row << 16) + (ctr_atom_pte_row << 8) + term_atom2_pte_row);

		return ((term_atom2_pte_row << 16) + (ctr_atom_pte_row << 8) + term_atom1_pte_row);
	}

	const Forcefield::MMFF94DefaultStretchBendParameterTable::Entry NOT_FOUND;
}


Forcefield::MMFF94DefaultStretchBendParameterTable::SharedPointer Forcefield::MMFF94DefaultStretchBendParameterTable::defaultTable = builtinTable;


Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::Entry():
	termAtom1PTERow(0), ctrAtomPTERow(0), termAtom2PTERow(0),
	ijkForceConst(0), kjiForceConst(0), initialized(false)
{}

Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::Entry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row, 
																 unsigned int term_atom2_pte_row, double force_const, double kji_force_const):
	termAtom1PTERow(term_atom1_pte_row), ctrAtomPTERow(ctr_atom_pte_row), termAtom2PTERow(term_atom2_pte_row),
	ijkForceConst(force_const), kjiForceConst(kji_force_const), initialized(true)
{}

unsigned int Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::getTerminalAtom1PTERow() const
{
	return termAtom1PTERow;
}

unsigned int Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::getCenterAtomPTERow() const
{
	return ctrAtomPTERow;
}

unsigned int Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::getTerminalAtom2PTERow() const
{
	return termAtom2PTERow;
}

double Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::getIJKForceConstant() const
{
	return ijkForceConst;
}

double Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::getKJIForceConstant() const
{
	return kjiForceConst;
}

Forcefield::MMFF94DefaultStretchBendParameterTable::Entry::operator bool() const
{
	return initialized;
}


Forcefield::MMFF94DefaultStretchBendParameterTable::MMFF94DefaultStretchBendParameterTable()
{}

void Forcefield::MMFF94DefaultStretchBendParameterTable::addEntry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row, 
																  unsigned int term_atom2_pte_row, double ijk_force_const, double kji_force_const)
{
    entries.insert(DataStorage::value_type(lookupKey(term_atom1_pte_row,  ctr_atom_pte_row, term_atom2_pte_row), 
										   Entry(term_atom1_pte_row, ctr_atom_pte_row, term_atom2_pte_row, ijk_force_const, kji_force_const)));
}

const Forcefield::MMFF94DefaultStretchBendParameterTable::Entry& 
Forcefield::MMFF94DefaultStretchBendParameterTable::getEntry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row, 
															 unsigned int term_atom2_pte_row) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(term_atom1_pte_row,  ctr_atom_pte_row, term_atom2_pte_row));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t Forcefield::MMFF94DefaultStretchBendParameterTable::getNumEntries() const
{
    return entries.size();
}

void Forcefield::MMFF94DefaultStretchBendParameterTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94DefaultStretchBendParameterTable::removeEntry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row, 
																	 unsigned int term_atom2_pte_row)
{
	return entries.erase(lookupKey(term_atom1_pte_row,  ctr_atom_pte_row, term_atom2_pte_row));
}

Forcefield::MMFF94DefaultStretchBendParameterTable::EntryIterator 
Forcefield::MMFF94DefaultStretchBendParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94DefaultStretchBendParameterTable::ConstEntryIterator 
Forcefield::MMFF94DefaultStretchBendParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94DefaultStretchBendParameterTable::ConstEntryIterator 
Forcefield::MMFF94DefaultStretchBendParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94DefaultStretchBendParameterTable::EntryIterator 
Forcefield::MMFF94DefaultStretchBendParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94DefaultStretchBendParameterTable::EntryIterator 
Forcefield::MMFF94DefaultStretchBendParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94DefaultStretchBendParameterTable::load(std::istream& is)
{
    std::string line;
	unsigned int term_atom1_pte_row;
	unsigned int ctr_atom_pte_row;
	unsigned int term_atom2_pte_row;
	double ijk_force_const;
	double kji_force_const;

    while (readMMFF94DataLine(is, line, "MMFF94DefaultStretchBendParameterTable: error while reading default stretch bend parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> term_atom1_pte_row))
			throw Base::IOError("MMFF94DefaultStretchBendParameterTable: error while reading terminal atom 1 PTE row");

		if (!(line_iss >> ctr_atom_pte_row))
			throw Base::IOError("MMFF94DefaultStretchBendParameterTable: error while reading center atom PTE row");

		if (!(line_iss >> term_atom2_pte_row))
			throw Base::IOError("MMFF94DefaultStretchBendParameterTable: error while reading terminal atom 2 PTE row");
	
		if (!(line_iss >> ijk_force_const))
			throw Base::IOError("MMFF94DefaultStretchBendParameterTable: error while reading IJK force constant");

		if (!(line_iss >> kji_force_const))
			throw Base::IOError("MMFF94DefaultStretchBendParameterTable: error while reading KJI force constant");

		addEntry(term_atom1_pte_row, ctr_atom_pte_row, term_atom2_pte_row, ijk_force_const, kji_force_const);
    }
}

void Forcefield::MMFF94DefaultStretchBendParameterTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::DEFAULT_STRETCH_BEND_PARAMETERS, 
																std::strlen(MMFF94ParameterData::DEFAULT_STRETCH_BEND_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::DEFAULT_STRETCH_BEND_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void Forcefield::MMFF94DefaultStretchBendParameterTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const Forcefield::MMFF94DefaultStretchBendParameterTable::SharedPointer& Forcefield::MMFF94DefaultStretchBendParameterTable::get()
{
    return defaultTable;
}
