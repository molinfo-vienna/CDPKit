/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLiteScreeningDBCreator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::SQLiteScreeningDBCreator.
 */

#ifndef CDPL_PHARM_SQLITESCREENINGDBCREATOR_HPP
#define CDPL_PHARM_SQLITESCREENINGDBCREATOR_HPP

#include <string>
#include <cstddef>
#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{
		
		class MolecularGraph;
	}

    namespace Pharm
    {
	
		/**
		 * \addtogroup CDPL_PHARM_SCREENING
		 * @{
		 */

		/**
		 * \brief A creator for molecular graph data in the native I/O format of the <em>CDPL</em>.
		 */
		class CDPL_PHARM_API SQLiteScreeningDBCreator
		{

		  public:
			enum Mode
			{

			  CREATE,
			  UPDATE,
			  APPEND
			};

			SQLiteScreeningDBCreator();

			/**
			 * \brief Constructs a \c %SQLiteScreeningDBCreator instance that will write data to the 
			 *        database-file specified by \a name in the given insert mode.
			 * \param name The name of the database-file.
			 * \param mode Specifies whether to (re)create the database or to update/append to existing records.
			 * \param allow_dup_entries Specifies whether input molecules that are duplicates of already
			 *                          stored molecules should be discarded. 
			 */
			SQLiteScreeningDBCreator(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true);

			/**
			 * \brief Destructor.
			 */
			~SQLiteScreeningDBCreator();

			void open(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true);

			void close();

			Mode getMode() const;

			bool allowDuplicateEntries() const;

			bool process(const Chem::MolecularGraph& molgraph);

			const std::string& getDatabaseName() const;

			std::size_t getNumProcessed() const;

			std::size_t getNumRejected() const;

			std::size_t getNumDeleted() const;

			std::size_t getNumInserted() const;

		  private:
			class Implementation;

			typedef std::auto_ptr<Implementation> ImplementationPointer;

			SQLiteScreeningDBCreator(const SQLiteScreeningDBCreator&);

			SQLiteScreeningDBCreator& operator=(const SQLiteScreeningDBCreator&);
		
			ImplementationPointer impl;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_SQLITESCREENINGDBCREATOR_HPP
