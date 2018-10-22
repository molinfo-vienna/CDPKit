/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94SymbolicAtomTypePatternTable.cpp 
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

#include "CDPL/Config.hpp"

#include <cstring>
#include <sstream>

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/ForceField/MMFF94SymbolicAtomTypePatternTable.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMFF94ParameterData.hpp"
#include "DataIOUtilities.hpp"


using namespace CDPL; 


namespace
{
 
    ForceField::MMFF94SymbolicAtomTypePatternTable::SharedPointer builtinTable(new ForceField::MMFF94SymbolicAtomTypePatternTable());

    struct Init
    {

		Init() {
			builtinTable->loadDefaults();
		}

    } init;
}


ForceField::MMFF94SymbolicAtomTypePatternTable::SharedPointer 
ForceField::MMFF94SymbolicAtomTypePatternTable::defaultTable  = builtinTable;


ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::Entry(const Chem::MolecularGraph::SharedPointer& ptn, 
															 const std::string& sym_type, bool fallback):
	pattern(ptn), symType(sym_type), fallback(fallback)
{}

bool ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::isFallbackType() const
{
    return fallback;
}

const Chem::MolecularGraph::SharedPointer& ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::getPattern() const
{
    return pattern;
}

const std::string& ForceField::MMFF94SymbolicAtomTypePatternTable::Entry::getSymbolicType() const
{
    return symType;
}


ForceField::MMFF94SymbolicAtomTypePatternTable::MMFF94SymbolicAtomTypePatternTable()
{}

std::size_t ForceField::MMFF94SymbolicAtomTypePatternTable::getNumEntries() const
{
    return entries.size();
}

void ForceField::MMFF94SymbolicAtomTypePatternTable::addEntry(const Chem::MolecularGraph::SharedPointer& ptn, 
															  const std::string& sym_type, bool fallback)
{
    entries.push_back(Entry(ptn, sym_type, fallback));
}

const ForceField::MMFF94SymbolicAtomTypePatternTable::Entry& 
ForceField::MMFF94SymbolicAtomTypePatternTable::getEntry(std::size_t idx) const
{
	if (idx >= entries.size())
		throw Base::IndexError("MMFF94SymbolicAtomTypePatternTable: entry index out of bounds");

	return entries[idx];
}

ForceField::MMFF94SymbolicAtomTypePatternTable::ConstEntryIterator 
ForceField::MMFF94SymbolicAtomTypePatternTable::getEntriesBegin() const
{
    return entries.begin();
}

ForceField::MMFF94SymbolicAtomTypePatternTable::ConstEntryIterator 
ForceField::MMFF94SymbolicAtomTypePatternTable::getEntriesEnd() const
{
    return entries.end();
}

ForceField::MMFF94SymbolicAtomTypePatternTable::EntryIterator 
ForceField::MMFF94SymbolicAtomTypePatternTable::getEntriesBegin()
{
	return entries.begin();
}

ForceField::MMFF94SymbolicAtomTypePatternTable::EntryIterator 
ForceField::MMFF94SymbolicAtomTypePatternTable::getEntriesEnd()
{
	return entries.end();
}

void ForceField::MMFF94SymbolicAtomTypePatternTable::removeEntry(std::size_t idx)
{
	if (idx >= entries.size())
		throw Base::IndexError("MMFF94SymbolicAtomTypePatternTable: entry index out of bounds");

	entries.erase(entries.begin() + idx);
}

ForceField::MMFF94SymbolicAtomTypePatternTable::EntryIterator 
ForceField::MMFF94SymbolicAtomTypePatternTable::removeEntry(const EntryIterator& it)
{
	if (it >= entries.end())
		throw Base::IndexError("MMFF94SymbolicAtomTypePatternTable: iterator out of bounds");

	return entries.erase(it);
}

void ForceField::MMFF94SymbolicAtomTypePatternTable::clear()
{
    entries.clear();
}

void ForceField::MMFF94SymbolicAtomTypePatternTable::load(std::istream& is)
{
	using namespace Chem;

	std::string line;
	std::string pattern;
	std::string sym_type;

	while (readMMFF94DataLine(is, line, "MMFF94SymbolicAtomTypePatternTable: error while reading symbolic atom type pattern entry")) {
		std::istringstream line_iss(line);

		if (!(line_iss >> pattern))
			throw Base::IOError("MMFF94SymbolicAtomTypePatternTable: error while reading symbolic atom type pattern");
		
		if (!(line_iss >> sym_type))
			throw Base::IOError("MMFF94SymbolicAtomTypePatternTable: error while reading symbolic atom type");
	
		BasicMolecule::SharedPointer mol_ptr(new BasicMolecule());

		if (!parseSMARTS(pattern, *mol_ptr, true))
			throw Base::IOError("MMFF94SymbolicAtomTypePatternTable: error while parsing symbolic atom type SMARTS pattern");
	
		bool fb = false;

		for (BasicMolecule::AtomIterator it = mol_ptr->getAtomsBegin(), end = mol_ptr->getAtomsEnd(); it != end; ++it) {
			Atom& atom = *it;

			if (hasReactionAtomMappingID(atom)) {
				if (getReactionAtomMappingID(atom) == 2)
					fb = true;
			}
		}

		addEntry(mol_ptr, sym_type, fb);
	}
}

void ForceField::MMFF94SymbolicAtomTypePatternTable::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(MMFF94ParameterData::SYMBOLIC_ATOM_TYPE_PATTERNS, 
																std::strlen(MMFF94ParameterData::SYMBOLIC_ATOM_TYPE_PATTERNS));
#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(MMFF94ParameterData::SYMBOLIC_ATOM_TYPE_PATTERNS);

#endif // defined(HAVE_BOOST_IOSTREAMS)

    load(is);
}

void ForceField::MMFF94SymbolicAtomTypePatternTable::set(const SharedPointer& table)
{	
    defaultTable = (!table ? builtinTable : table);
}

const ForceField::MMFF94SymbolicAtomTypePatternTable::SharedPointer& ForceField::MMFF94SymbolicAtomTypePatternTable::get()
{
    return defaultTable;
}
