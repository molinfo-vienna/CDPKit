/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94HeavyToHydrogenAtomTypeMap.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::ForceField::MMFF94HeavyToHydrogenAtomTypeMap.
 */

#ifndef CDPL_FORCEFIELD_MMFF94HEAVYTOHYDROGENATOMTYPEMAP_HPP
#define CDPL_FORCEFIELD_MMFF94HEAVYTOHYDROGENATOMTYPEMAP_HPP

#include <string>
#include <iosfwd>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

	/**
	 * \addtogroup CDPL_FORCEFIELD_PARAMETER_TABLES
	 * @{
	 */

	class CDPL_FORCEFIELD_API MMFF94HeavyToHydrogenAtomTypeMap
	{

	    typedef boost::unordered_map<std::string, std::string> DataStorage;

	  public:
	    typedef boost::shared_ptr<MMFF94HeavyToHydrogenAtomTypeMap> SharedPointer;

	    typedef DataStorage::const_iterator ConstEntryIterator;
	    typedef DataStorage::iterator EntryIterator;
		typedef DataStorage::value_type Entry;

	    MMFF94HeavyToHydrogenAtomTypeMap();

	    void addEntry(const std::string& parent_type, const std::string& hyd_type);

	    const std::string& getEntry(const std::string& parent_type) const;

		std::size_t getNumEntries() const;

	    void clear();

		bool removeEntry(const std::string& parent_type);

		EntryIterator removeEntry(const EntryIterator& it);

	    ConstEntryIterator getEntriesBegin() const;

	    ConstEntryIterator getEntriesEnd() const;

		EntryIterator getEntriesBegin();

		EntryIterator getEntriesEnd();

	    void load(std::istream& is);

	    void loadDefaults();

	    static void set(const SharedPointer& map);

	    static const SharedPointer& get();

	  private:
	    static SharedPointer defaultMap;
	    DataStorage          entries;
	};
    
	/**
	 * @}
	 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94HEAVYTOHYDROGENATOMTYPEMAP_HPP
