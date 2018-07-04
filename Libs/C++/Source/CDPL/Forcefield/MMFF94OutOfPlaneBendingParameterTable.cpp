/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94OutOfPlaneBendingParameterTable.cpp 
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

#include "CDPL/Forcefield/MMFF94OutOfPlaneBendingParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "Utilities.hpp"


using namespace CDPL; 


namespace
{
 
    Forcefield::MMFF94OutOfPlaneBendingParameterTable::SharedPointer builtinDynTable(new Forcefield::MMFF94OutOfPlaneBendingParameterTable());
    Forcefield::MMFF94OutOfPlaneBendingParameterTable::SharedPointer builtinStatTable(new Forcefield::MMFF94OutOfPlaneBendingParameterTable());

    struct Init
    {

		Init() {
			builtinDynTable->loadDefaults(false);
			builtinStatTable->loadDefaults(true);
		}

    } init;

	Base::uint32 lookupKey(Base::uint32 nbr_atom1_type, Base::uint32 ctr_atom_type, Base::uint32 nbr_atom2_type, Base::uint32 oop_atom_type)
	{
		if (nbr_atom1_type < nbr_atom2_type)
			return ((nbr_atom1_type << 24) + (ctr_atom_type << 16) + (nbr_atom2_type << 8) + oop_atom_type);

		return ((nbr_atom2_type << 24) + (ctr_atom_type << 16) + (nbr_atom1_type << 8) + oop_atom_type);
	}

	const Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry NOT_FOUND;
}


Forcefield::MMFF94OutOfPlaneBendingParameterTable::SharedPointer Forcefield::MMFF94OutOfPlaneBendingParameterTable::defaultDynTable  = builtinDynTable;
Forcefield::MMFF94OutOfPlaneBendingParameterTable::SharedPointer Forcefield::MMFF94OutOfPlaneBendingParameterTable::defaultStatTable = builtinStatTable;


Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::Entry():
	nbrAtom1Type(0), ctrAtomType(0), nbrAtom2Type(0), oopAtomType(0), forceConst(0), initialized(false)
{}

Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::Entry(unsigned int nbr_atom1_type, unsigned int ctr_atom_type, unsigned int nbr_atom2_type, 
																unsigned int oop_atom_type, double force_const):
	nbrAtom1Type(nbr_atom1_type), ctrAtomType(ctr_atom_type), nbrAtom2Type(nbr_atom2_type), oopAtomType(nbr_atom2_type),
	forceConst(force_const), initialized(true)
{}

unsigned int Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::getNeighborAtom1Type() const
{
	return nbrAtom1Type;
}

unsigned int Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::getCenterAtomType() const
{
	return ctrAtomType;
}

unsigned int Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::getNeighborAtom2Type() const
{
	return nbrAtom2Type;
}

unsigned int Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::getOutOfPlaneAtomType() const
{
	return oopAtomType;
}

double Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::getForceConstant() const
{
	return forceConst;
}

Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry::operator bool() const
{
	return initialized;
}


Forcefield::MMFF94OutOfPlaneBendingParameterTable::MMFF94OutOfPlaneBendingParameterTable()
{}

void Forcefield::MMFF94OutOfPlaneBendingParameterTable::addEntry(unsigned int nbr_atom1_type, unsigned int ctr_atom_type, 
																 unsigned int nbr_atom2_type, unsigned int oop_atom_type, double force_const)
{
    entries.insert(DataStorage::value_type(lookupKey(nbr_atom1_type,  ctr_atom_type, nbr_atom2_type, oop_atom_type), 
										   Entry(nbr_atom1_type, ctr_atom_type, nbr_atom2_type, oop_atom_type, force_const)));
}

const Forcefield::MMFF94OutOfPlaneBendingParameterTable::Entry& 
Forcefield::MMFF94OutOfPlaneBendingParameterTable::getEntry(unsigned int nbr_atom1_type, unsigned int ctr_atom_type, 
															unsigned int nbr_atom2_type, unsigned int oop_atom_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(nbr_atom1_type,  ctr_atom_type, nbr_atom2_type, oop_atom_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t Forcefield::MMFF94OutOfPlaneBendingParameterTable::getNumEntries() const
{
    return entries.size();
}

void Forcefield::MMFF94OutOfPlaneBendingParameterTable::clear()
{
    entries.clear();
}

bool Forcefield::MMFF94OutOfPlaneBendingParameterTable::removeEntry(unsigned int nbr_atom1_type, unsigned int ctr_atom_type, 
																	unsigned int nbr_atom2_type, unsigned int oop_atom_type)
{
	return entries.erase(lookupKey(nbr_atom1_type,  ctr_atom_type, nbr_atom2_type, oop_atom_type));
}

Forcefield::MMFF94OutOfPlaneBendingParameterTable::EntryIterator 
Forcefield::MMFF94OutOfPlaneBendingParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator 
Forcefield::MMFF94OutOfPlaneBendingParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94OutOfPlaneBendingParameterTable::ConstEntryIterator 
Forcefield::MMFF94OutOfPlaneBendingParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
Forcefield::MMFF94OutOfPlaneBendingParameterTable::EntryIterator 
Forcefield::MMFF94OutOfPlaneBendingParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

Forcefield::MMFF94OutOfPlaneBendingParameterTable::EntryIterator 
Forcefield::MMFF94OutOfPlaneBendingParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void Forcefield::MMFF94OutOfPlaneBendingParameterTable::load(std::istream& is)
{
    std::string line;
	unsigned int nbr_atom1_type;
	unsigned int ctr_atom_type;
	unsigned int nbr_atom2_type;
	unsigned int oop_atom_type;
	double force_const;

    while (readMMFF94DataLine(is, line, "MMFF94OutOfPlaneBendingParameterTable: error while reading out of plane bending parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> nbr_atom1_type))
			throw Base::IOError("MMFF94OutOfPlaneBendingParameterTable: error while reading terminal atom 1 type");

		if (!(line_iss >> ctr_atom_type))
			throw Base::IOError("MMFF94OutOfPlaneBendingParameterTable: error while reading center atom type");

		if (!(line_iss >> nbr_atom2_type))
			throw Base::IOError("MMFF94OutOfPlaneBendingParameterTable: error while reading terminal atom 2 type");
	
		if (!(line_iss >> oop_atom_type))
			throw Base::IOError("MMFF94OutOfPlaneBendingParameterTable: error while reading out of plane atom type");

		if (!(line_iss >> force_const))
			throw Base::IOError("MMFF94OutOfPlaneBendingParameterTable: error while reading force constant");

		addEntry(nbr_atom1_type, ctr_atom_type, nbr_atom2_type, oop_atom_type, force_const);
    }
}

void Forcefield::MMFF94OutOfPlaneBendingParameterTable::loadDefaults(bool mmff94s)
{
	if (mmff94s) {
#if defined(HAVE_BOOST_IOSTREAMS)

		boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS, 
																	std::strlen(MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

		std::istringstream is(std::string(MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

		load(is);

	} else {
#if defined(HAVE_BOOST_IOSTREAMS)

		boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS, 
																	std::strlen(MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS));
#else // defined(HAVE_BOOST_IOSTREAMS)

		std::istringstream is(std::string(MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS));

#endif // defined(HAVE_BOOST_IOSTREAMS)

		load(is);
	}
}

void Forcefield::MMFF94OutOfPlaneBendingParameterTable::set(const SharedPointer& table, bool mmff94s)
{	
	if (mmff94s) 
		defaultStatTable = (!table ? builtinStatTable : table);
	else
		defaultDynTable = (!table ? builtinDynTable : table);
}

const Forcefield::MMFF94OutOfPlaneBendingParameterTable::SharedPointer& Forcefield::MMFF94OutOfPlaneBendingParameterTable::get(bool mmff94s)
{
    return (mmff94s ? defaultStatTable : defaultDynTable);
}
