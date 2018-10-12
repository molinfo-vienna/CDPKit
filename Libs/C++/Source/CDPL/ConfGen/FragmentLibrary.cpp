/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibrary.cpp 
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

#include <string>
#include <cassert>

#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/CDFMolecularGraphWriter.hpp"
#include "CDPL/Chem/CDFMoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

    Chem::MolecularGraph::SharedPointer NO_ENTRY;

    ConfGen::FragmentLibrary::SharedPointer builtinFragLib(new ConfGen::FragmentLibrary());

    struct Init
    {

		Init() {
			builtinFragLib->loadDefaults();
		}

    } init;
}


ConfGen::FragmentLibrary::SharedPointer ConfGen::FragmentLibrary::defaultLib = builtinFragLib;


ConfGen::FragmentLibrary::FragmentLibrary() {}

void ConfGen::FragmentLibrary::addEntry(Base::uint64 frag_hash, const Chem::MolecularGraph::SharedPointer& frag)
{
	if (!frag)
		return;

    fragData.insert(HashToFragmentDataMap::value_type(frag_hash, frag));
}

const Chem::MolecularGraph::SharedPointer& ConfGen::FragmentLibrary::getEntry(Base::uint64 frag_hash) const
{
    ConstEntryIterator it = fragData.find(frag_hash);

    if (it == fragData.end())
		return NO_ENTRY;

    return it->second;
}

std::size_t ConfGen::FragmentLibrary::getNumEntries() const
{
    return fragData.size();
}

void ConfGen::FragmentLibrary::clear()
{
    fragData.clear();
}

bool ConfGen::FragmentLibrary::removeEntry(Base::uint64 frag_hash)
{
    return (fragData.erase(frag_hash) > 0);
}

ConfGen::FragmentLibrary::EntryIterator ConfGen::FragmentLibrary::removeEntry(const EntryIterator& it)
{
    return fragData.erase(it);
}

ConfGen::FragmentLibrary::ConstEntryIterator ConfGen::FragmentLibrary::getEntriesBegin() const
{
    return fragData.begin();
}

ConfGen::FragmentLibrary::ConstEntryIterator ConfGen::FragmentLibrary::getEntriesEnd() const
{
    return fragData.end();
}
	
ConfGen::FragmentLibrary::EntryIterator ConfGen::FragmentLibrary::getEntriesBegin()
{
    return fragData.begin();
}

ConfGen::FragmentLibrary::EntryIterator ConfGen::FragmentLibrary::getEntriesEnd()
{
    return fragData.end();
}

void ConfGen::FragmentLibrary::load(std::istream& is)
{
 	Chem::CDFMoleculeReader reader(is);

	while (true) {
		try {
			Chem::BasicMolecule::SharedPointer mol_ptr(new Chem::BasicMolecule());

			if (!reader.read(*mol_ptr))
				break;

			addEntry(getHashCode(*mol_ptr), mol_ptr);

		} catch (const std::exception& e) {
			throw Base::IOError("FragmentLibrary: error while loading fragment library: " + std::string(e.what()));
		}
	}
}

void ConfGen::FragmentLibrary::save(std::ostream& os)
{
	Chem::CDFMolecularGraphWriter writer(os);

	for (ConstEntryIterator it = fragData.begin(), end = fragData.end(); it != end; ++it) {
		try {
			assert(it->second);

			Chem::MolecularGraph& frag = *it->second;

			setHashCode(frag, it->first);

			if (!writer.write(frag))
				throw Base::IOError("FragmentLibrary: unspecified error while saving fragment library");

		} catch (const std::exception& e) {
			throw Base::IOError("FragmentLibrary: error while saving fragment library: " + std::string(e.what()));
		}
	}
}

void ConfGen::FragmentLibrary::loadDefaults()
{
    // TODO
}

void ConfGen::FragmentLibrary::set(const SharedPointer& lib)
{
    defaultLib = (!lib ? builtinFragLib : lib);
}

const ConfGen::FragmentLibrary::SharedPointer& ConfGen::FragmentLibrary::get()
{
    return defaultLib;
}
