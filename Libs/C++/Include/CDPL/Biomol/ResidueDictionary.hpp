/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueDictionary.hpp 
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
 * \brief Definition of the class CDPL::Biomol::ResidueDictionary. 
 */

#ifndef CDPL_BIOMOL_RESIDUEDICTIONARY_HPP
#define CDPL_BIOMOL_RESIDUEDICTIONARY_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

    namespace Biomol 
    {

		/**
		 * \brief A global dictionary for the lookup of meta-data associated with the residues
		 *        in biological macromolecules.
		 */ 
		class CDPL_BIOMOL_API ResidueDictionary
		{

		  public:
			class CDPL_BIOMOL_API Entry
			{

			  public:
				typedef std::function<Chem::MolecularGraph::SharedPointer(const std::string&)> StructureRetrievalFunction;

				Entry(const std::string& code, const std::string& rep_code, const std::string& rep_by_code, bool obsolete,
					  const std::string& name, unsigned int type, const StructureRetrievalFunction& struc_ret_func);

				Entry();

				const std::string& getCode() const;

				const std::string& getReplacedCode() const;

				const std::string& getReplacedByCode() const;

				bool isObsolete() const;

				const std::string& getName() const;

				unsigned int getType() const;

				Chem::MolecularGraph::SharedPointer getStructure() const;
				
			  private:
				std::string                code;
				std::string                replacesCode;
				std::string                replacedByCode;
				bool                       obsolete;
				std::string                name;
				unsigned int               type;
				StructureRetrievalFunction structRetrievalFunc;
			};

		  private:
			typedef std::unordered_map<std::string, Entry> EntryLookupTable;

		  public:
			typedef std::shared_ptr<ResidueDictionary> SharedPointer;

			typedef boost::transform_iterator<std::function<const Entry&(const EntryLookupTable::value_type&)>, 
											  EntryLookupTable::const_iterator> ConstEntryIterator;
			
			void addEntry(const Entry& entry);

			bool containsEntry(const std::string& code) const;

			void removeEntry(const std::string& code);
			
			const Entry& getEntry(const std::string& code) const;

			void clear();

			std::size_t getNumEntries() const;
			
			ConstEntryIterator getEntriesBegin() const;

			ConstEntryIterator getEntriesEnd() const;
			
			void loadDefaults();

			static void set(const SharedPointer& dict);

			static const SharedPointer& get();

			static const std::string& getReplacedCode(const std::string& code);

			static const std::string& getReplacedByCode(const std::string& code);

			static bool isObsolete(const std::string& code);

			static const std::string& getName(const std::string& code);

			static bool isStdResidue(const std::string& code);

			static unsigned int getType(const std::string& code);

			static Chem::MolecularGraph::SharedPointer getStructure(const std::string& code);

		  private:
			static SharedPointer defaultDict;
			EntryLookupTable     entries;
		};
    }
}

#endif // CDPL_BIOMOL_RESIDUEDICTIONARY_HPP
