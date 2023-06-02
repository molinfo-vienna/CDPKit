/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AngleBendingParameterTable.cpp 
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

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ForceField/MMFF94AngleBendingParameterTable.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL; 


namespace
{
 
    ForceField::MMFF94AngleBendingParameterTable::SharedPointer builtinTable(new ForceField::MMFF94AngleBendingParameterTable());

	boost::once_flag initBuiltinTableFlag = BOOST_ONCE_INIT;

	void initBuiltinTable() 
	{
		builtinTable->loadDefaults();
	}

	Base::uint32 lookupKey(Base::uint32 angle_type_idx, Base::uint32 term_atom1_type, Base::uint32 ctr_atom_type, Base::uint32 term_atom2_type)
	{
		if (term_atom1_type < term_atom2_type)
			return ((term_atom1_type << 24) + (ctr_atom_type << 16) + (term_atom2_type << 8) + angle_type_idx);

		return ((term_atom2_type << 24) + (ctr_atom_type << 16) + (term_atom1_type << 8) + angle_type_idx);
	}

	const ForceField::MMFF94AngleBendingParameterTable::Entry NOT_FOUND;
}


ForceField::MMFF94AngleBendingParameterTable::SharedPointer ForceField::MMFF94AngleBendingParameterTable::defaultTable = builtinTable;


ForceField::MMFF94AngleBendingParameterTable::Entry::Entry():
	angleTypeIdx(0), termAtom1Type(0), ctrAtomType(0), termAtom2Type(0),
	forceConst(0), refAngle(0), initialized(false)
{}

ForceField::MMFF94AngleBendingParameterTable::Entry::Entry(unsigned int angle_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
														   unsigned int term_atom2_type, double force_const, double ref_angle):
	angleTypeIdx(angle_type_idx), termAtom1Type(term_atom1_type), ctrAtomType(ctr_atom_type), termAtom2Type(term_atom2_type),
	forceConst(force_const), refAngle(ref_angle), initialized(true)
{}

unsigned int ForceField::MMFF94AngleBendingParameterTable::Entry::getAngleTypeIndex() const
{
	return angleTypeIdx;
}

unsigned int ForceField::MMFF94AngleBendingParameterTable::Entry::getTerminalAtom1Type() const
{
	return termAtom1Type;
}

unsigned int ForceField::MMFF94AngleBendingParameterTable::Entry::getCenterAtomType() const
{
	return ctrAtomType;
}

unsigned int ForceField::MMFF94AngleBendingParameterTable::Entry::getTerminalAtom2Type() const
{
	return termAtom2Type;
}

double ForceField::MMFF94AngleBendingParameterTable::Entry::getForceConstant() const
{
	return forceConst;
}

double ForceField::MMFF94AngleBendingParameterTable::Entry::getReferenceAngle() const
{
	return refAngle;
}

ForceField::MMFF94AngleBendingParameterTable::Entry::operator bool() const
{
	return initialized;
}


ForceField::MMFF94AngleBendingParameterTable::MMFF94AngleBendingParameterTable()
{}

void ForceField::MMFF94AngleBendingParameterTable::addEntry(unsigned int angle_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
															unsigned int term_atom2_type, double force_const, double ref_angle)
{
    entries.insert(DataStorage::value_type(lookupKey(angle_type_idx, term_atom1_type,  ctr_atom_type, term_atom2_type), 
										   Entry(angle_type_idx, term_atom1_type, ctr_atom_type, term_atom2_type, force_const, ref_angle)));
}

const ForceField::MMFF94AngleBendingParameterTable::Entry& 
ForceField::MMFF94AngleBendingParameterTable::getEntry(unsigned int angle_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
													   unsigned int term_atom2_type) const
{
	DataStorage::const_iterator it = entries.find(lookupKey(angle_type_idx, term_atom1_type,  ctr_atom_type, term_atom2_type));

	if (it == entries.end())
		return NOT_FOUND;

	return it->second;
}

std::size_t ForceField::MMFF94AngleBendingParameterTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94AngleBendingParameterTable::clear()
{
    entries.clear();
}

bool ForceField::MMFF94AngleBendingParameterTable::removeEntry(unsigned int angle_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom_type, 
															   unsigned int term_atom2_type)
{
	return entries.erase(lookupKey(angle_type_idx, term_atom1_type,  ctr_atom_type, term_atom2_type));
}

ForceField::MMFF94AngleBendingParameterTable::EntryIterator 
ForceField::MMFF94AngleBendingParameterTable::removeEntry(const EntryIterator& it)
{
	return EntryIterator(entries.erase(it.base()), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

ForceField::MMFF94AngleBendingParameterTable::ConstEntryIterator 
ForceField::MMFF94AngleBendingParameterTable::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), boost::bind(&DataStorage::value_type::second, _1));
}

ForceField::MMFF94AngleBendingParameterTable::ConstEntryIterator 
ForceField::MMFF94AngleBendingParameterTable::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), boost::bind(&DataStorage::value_type::second, _1));
}
	
ForceField::MMFF94AngleBendingParameterTable::EntryIterator 
ForceField::MMFF94AngleBendingParameterTable::getEntriesBegin()
{
	return EntryIterator(entries.begin(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

ForceField::MMFF94AngleBendingParameterTable::EntryIterator 
ForceField::MMFF94AngleBendingParameterTable::getEntriesEnd()
{
	return EntryIterator(entries.end(), boost::bind<Entry&>(&DataStorage::value_type::second, _1));
}

void ForceField::MMFF94AngleBendingParameterTable::load(std::istream& is)
{
    std::string line;
	unsigned int angle_type_idx;
	unsigned int term_atom1_type;
	unsigned int ctr_atom_type;
	unsigned int term_atom2_type;
	double force_const;
	double ref_angle;

    while (readMMFF94DataLine(is, line, "MMFF94AngleBendingParameterTable: error while reading angle bending parameter entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> angle_type_idx))
			throw Base::IOError("MMFF94AngleBendingParameterTable: error while reading angle type index");

		if (!(line_iss >> term_atom1_type))
			throw Base::IOError("MMFF94AngleBendingParameterTable: error while reading terminal atom 1 type");

		if (!(line_iss >> ctr_atom_type))
			throw Base::IOError("MMFF94AngleBendingParameterTable: error while reading center atom type");

		if (!(line_iss >> term_atom2_type))
			throw Base::IOError("MMFF94AngleBendingParameterTable: error while reading terminal atom 2 type");
	
		if (!(line_iss >> force_const))
			throw Base::IOError("MMFF94AngleBendingParameterTable: error while reading force constant");

		if (!(line_iss >> ref_angle))
			throw Base::IOError("MMFF94AngleBendingParameterTable: error while reading reference angle");

		addEntry(angle_type_idx, term_atom1_type, ctr_atom_type, term_atom2_type, force_const, ref_angle);
    }
}

void ForceField::MMFF94AngleBendingParameterTable::loadDefaults()
{
    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::ANGLE_BENDING_PARAMETERS, 
																std::strlen(MMFF94ParameterData::ANGLE_BENDING_PARAMETERS));
    load(is);
}

void ForceField::MMFF94AngleBendingParameterTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const ForceField::MMFF94AngleBendingParameterTable::SharedPointer& ForceField::MMFF94AngleBendingParameterTable::get()
{
	boost::call_once(&initBuiltinTable, initBuiltinTableFlag);

    return defaultTable;
}
