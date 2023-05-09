/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibrary.cpp 
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

#include <string>

#include "CDPL/Config.hpp"

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#else // defined(HAVE_BOOST_IOSTREAMS)

#include <sstream>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CFLFragmentLibraryEntryReader.hpp"
#include "CFLFragmentLibraryEntryWriter.hpp"


using namespace CDPL;


namespace
{

	const char BUILTIN_FRAG_LIB_DATA[] =
	 	#include "FragmentLibrary.cfl.str" 
		;

	const ConfGen::FragmentLibraryEntry::SharedPointer NO_ENTRY;

	ConfGen::FragmentLibrary::SharedPointer builtinFragLib(new ConfGen::FragmentLibrary());

	boost::once_flag initBuiltinFragLibFlag = BOOST_ONCE_INIT;
	
	void initBuiltinFragLib()
	{
		builtinFragLib->loadDefaults();
	}
}


ConfGen::FragmentLibrary::SharedPointer ConfGen::FragmentLibrary::defaultLib = builtinFragLib;


ConfGen::FragmentLibrary::FragmentLibrary() {}

ConfGen::FragmentLibrary::FragmentLibrary(const FragmentLibrary& lib): hashToEntryMap(lib.hashToEntryMap)
{}

ConfGen::FragmentLibrary::~FragmentLibrary() {}

ConfGen::FragmentLibrary& ConfGen::FragmentLibrary::operator=(const FragmentLibrary& lib)
{
	if (this == &lib)
		return *this;

	hashToEntryMap = lib.hashToEntryMap;

	return *this;
}

void ConfGen::FragmentLibrary::addEntries(const FragmentLibrary& lib)
{
	for (HashToEntryMap::iterator it = lib.hashToEntryMap.begin(), end = lib.hashToEntryMap.end(); it != end; ++it)
		hashToEntryMap.insert(*it);
}

bool ConfGen::FragmentLibrary::addEntry(const FragmentLibraryEntry::SharedPointer& entry)
{
	if (!entry)
		return false;

    return hashToEntryMap.insert(Entry(entry->getHashCode(), entry)).second;
}

const ConfGen::FragmentLibraryEntry::SharedPointer& ConfGen::FragmentLibrary::getEntry(Base::uint64 hash_code) const
{
    HashToEntryMap::iterator it = hashToEntryMap.find(hash_code);

    if (it == hashToEntryMap.end())
		return NO_ENTRY;

    return it->second;
}

bool ConfGen::FragmentLibrary::containsEntry(Base::uint64 hash_code) const
{
    return (hashToEntryMap.find(hash_code) != hashToEntryMap.end());
}

std::size_t ConfGen::FragmentLibrary::getNumEntries() const
{
    return hashToEntryMap.size();
}

void ConfGen::FragmentLibrary::clear()
{
    hashToEntryMap.clear();
}

bool ConfGen::FragmentLibrary::removeEntry(Base::uint64 hash_code)
{
   return (hashToEntryMap.erase(hash_code) > 0);
}

ConfGen::FragmentLibrary::EntryIterator ConfGen::FragmentLibrary::removeEntry(const EntryIterator& it)
{
    return hashToEntryMap.erase(it);
}

ConfGen::FragmentLibrary::ConstEntryIterator ConfGen::FragmentLibrary::getEntriesBegin() const
{
    return hashToEntryMap.begin();
}

ConfGen::FragmentLibrary::ConstEntryIterator ConfGen::FragmentLibrary::getEntriesEnd() const
{
    return hashToEntryMap.end();
}
	
ConfGen::FragmentLibrary::EntryIterator ConfGen::FragmentLibrary::getEntriesBegin()
{
    return hashToEntryMap.begin();
}

ConfGen::FragmentLibrary::EntryIterator ConfGen::FragmentLibrary::getEntriesEnd()
{
    return hashToEntryMap.end();
}

boost::mutex& ConfGen::FragmentLibrary::getMutex()
{
	return mutex;
}

void ConfGen::FragmentLibrary::load(std::istream& is)
{
	CFLFragmentLibraryEntryReader reader;

	while (true) {
		try {
			FragmentLibraryEntry::SharedPointer entry(new FragmentLibraryEntry());

			if (!reader.read(is, *entry))
				break;

			hashToEntryMap.insert(Entry(entry->getHashCode(), entry));

		} catch (const std::exception& e) {
			throw Base::IOError("FragmentLibrary: error while loading fragment library: " + std::string(e.what()));
		}
	}
}

void ConfGen::FragmentLibrary::save(std::ostream& os) const
{
	CFLFragmentLibraryEntryWriter writer;

	for (HashToEntryMap::const_iterator it = hashToEntryMap.begin(), end = hashToEntryMap.end(); it != end; ++it) {
		try {
			if (!writer.write(os, *it->second))
				throw Base::IOError("FragmentLibrary: unspecified error while saving fragment library");

		} catch (const std::exception& e) {
			throw Base::IOError("FragmentLibrary: error while saving fragment library: " + std::string(e.what()));
		}
	}
}

void ConfGen::FragmentLibrary::loadDefaults()
{
#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(BUILTIN_FRAG_LIB_DATA, sizeof(BUILTIN_FRAG_LIB_DATA) - 1);

#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(std::string(BUILTIN_FRAG_LIB_DATA, sizeof(BUILTIN_FRAG_LIB_DATA) - 1), std::ios_base::in | std::ios_base::binary);

#endif // defined(HAVE_BOOST_IOSTREAMS)

	load(is);
}

void ConfGen::FragmentLibrary::set(const SharedPointer& lib)
{
    defaultLib = (!lib ? builtinFragLib : lib);
}

const ConfGen::FragmentLibrary::SharedPointer& ConfGen::FragmentLibrary::get()
{
	boost::call_once(&initBuiltinFragLib, initBuiltinFragLibFlag);

    return defaultLib;
}
