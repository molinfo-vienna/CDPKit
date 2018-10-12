/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94TorsionParameterTable.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94TorsionParameterTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94TORSIONPARAMETERTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94TORSIONPARAMETERTABLE_HPP

#include <cstddef>
#include <iosfwd>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/function.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_PARAMETER_TABLES
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94TorsionParameterTable
		{

		  public:
			class Entry;

		  private:
			typedef boost::unordered_map<Base::uint64, Entry> DataStorage;

		  public:
			typedef boost::shared_ptr<MMFF94TorsionParameterTable> SharedPointer;
	
			class CDPL_FORCEFIELD_API Entry
			{

			  public:
				Entry();
 
				Entry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
					  unsigned int term_atom2_type, double tor_param1, double tor_param2, double tor_param3);

				unsigned int getTorsionTypeIndex() const;

				unsigned int getTerminalAtom1Type() const;

				unsigned int getCenterAtom1Type() const;

				unsigned int getCenterAtom2Type() const;

				unsigned int getTerminalAtom2Type() const;

				double getTorsionParameter1() const;

				double getTorsionParameter2() const;

				double getTorsionParameter3() const;

				operator bool() const;

			  private:
				unsigned int torTypeIdx;
				unsigned int termAtom1Type;
				unsigned int ctrAtom1Type;
				unsigned int ctrAtom2Type;
				unsigned int termAtom2Type;
				double       torParam1;
				double       torParam2;
				double       torParam3;
				bool         initialized;
			};			

			typedef boost::transform_iterator<boost::function1<const Entry&, const DataStorage::value_type&>, 
											  DataStorage::const_iterator> ConstEntryIterator;

			typedef boost::transform_iterator<boost::function1<Entry&, DataStorage::value_type&>, 
											  DataStorage::iterator> EntryIterator;
	
			MMFF94TorsionParameterTable();

			void addEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
						  unsigned int term_atom2_type, double tor_param1, double tor_param2, double tor_param3);

			const Entry& getEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
								  unsigned int term_atom2_type) const;

			std::size_t getNumEntries() const;

			void clear();

			bool removeEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
							 unsigned int term_atom2_type);

			EntryIterator removeEntry(const EntryIterator& it);

			ConstEntryIterator getEntriesBegin() const;

			ConstEntryIterator getEntriesEnd() const;
	
			EntryIterator getEntriesBegin();

			EntryIterator getEntriesEnd();

			void load(std::istream& is);

			void loadDefaults(bool mmff94s);

			static void set(const SharedPointer& table, bool mmff94s);

			static const SharedPointer& get(bool mmff94s);

		  private:
			static SharedPointer defaultDynTable;
			static SharedPointer defaultStatTable;
			DataStorage          entries;
		};
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94TORSIONPARAMETERTABLE_HPP
