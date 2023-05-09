/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94SymbolicAtomTypePatternTable.hpp 
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

/**
 * \file
 * \brief Pattern of the class CDPL::ForceField::MMFF94SymbolicAtomTypePatternTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94SYMBOLICATOMTYPEPATTERNTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94SYMBOLICATOMTYPEPATTERNTABLE_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <iosfwd>

#include <boost/shared_ptr.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94SymbolicAtomTypePatternTable
		{

		  public:
			class Entry;

		  private:
			typedef std::vector<Entry> DataStorage;

		  public:
			typedef boost::shared_ptr<MMFF94SymbolicAtomTypePatternTable> SharedPointer;

			typedef DataStorage::const_iterator ConstEntryIterator;
			typedef DataStorage::iterator EntryIterator;
	
			class CDPL_FORCEFIELD_API Entry
			{

			  public:
				Entry(const Chem::MolecularGraph::SharedPointer& ptn, const std::string& sym_type, bool fallback);

				bool isFallbackType() const;

				const Chem::MolecularGraph::SharedPointer& getPattern() const;

				const std::string& getSymbolicType() const;

			  private:
				Chem::MolecularGraph::SharedPointer pattern;
				std::string                         symType;
				bool                                fallback;
			};			

			MMFF94SymbolicAtomTypePatternTable();

			std::size_t getNumEntries() const;

			void addEntry(const Chem::MolecularGraph::SharedPointer& ptn, const std::string& sym_type, bool fallback);

			const Entry& getEntry(std::size_t idx) const;

			void clear();

			void removeEntry(std::size_t idx);

			EntryIterator removeEntry(const EntryIterator& it);

			ConstEntryIterator getEntriesBegin() const;

			ConstEntryIterator getEntriesEnd() const;
	
			EntryIterator getEntriesBegin();

			EntryIterator getEntriesEnd();

			void load(std::istream& is);

			void loadDefaults();

			static void set(const SharedPointer& table);

			static const SharedPointer& get();

		  private:
			static SharedPointer defaultTable;
			DataStorage          entries;
		};
	}
}

#endif // CDPL_FORCEFIELD_MMFF94SYMBOLICATOMTYPEPATTERNTABLE_HPP
