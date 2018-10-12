/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibrary.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::FragmentLibrary.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARY_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARY_HPP

#include <iosfwd>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

	/**
	 * \addtogroup CDPL_CONFGEN_DATA_STRUCTURES
	 * @{
	 */

	class CDPL_CONFGEN_API FragmentLibrary
	{

	    typedef boost::unordered_map<Base::uint64, Chem::MolecularGraph::SharedPointer> HashToFragmentDataMap;

	  public:
	    typedef boost::shared_ptr<FragmentLibrary> SharedPointer;
	
		typedef HashToFragmentDataMap::value_type Entry;
	    typedef HashToFragmentDataMap::const_iterator ConstEntryIterator;
	    typedef HashToFragmentDataMap::iterator EntryIterator;

	    FragmentLibrary();

	    void addEntry(Base::uint64 frag_hash, const Chem::MolecularGraph::SharedPointer& frag);

	    const Chem::MolecularGraph::SharedPointer& getEntry(Base::uint64 frag_hash) const;

	    std::size_t getNumEntries() const;

	    void clear();

	    bool removeEntry(Base::uint64 frag_hash);

	    EntryIterator removeEntry(const EntryIterator& it);

	    ConstEntryIterator getEntriesBegin() const;

	    ConstEntryIterator getEntriesEnd() const;
	
	    EntryIterator getEntriesBegin();

	    EntryIterator getEntriesEnd();

	    void load(std::istream& is);

	    void save(std::ostream& os);

	    void loadDefaults();

	    static void set(const SharedPointer& lib);

	    static const SharedPointer& get();

	  private:
	    static SharedPointer  defaultLib;
	    HashToFragmentDataMap fragData;
	};
    
	/**
	 * @}
	 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTLIBRARY_HPP
