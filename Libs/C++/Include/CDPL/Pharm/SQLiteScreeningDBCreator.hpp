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

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"


struct sqlite3;
struct sqlite3_stmt;


namespace CDPL 
{

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
		 *        database-file specified by \a name in the given mode.
	     * \param name The name of the database-file.
	     * \param mode Specifies whether to (re)create the database or to update/append to existing records.
		 * \param allow_duplicates Specifies whether duplicate input molecules should be ignored. 
	     */
	    SQLiteScreeningDBCreator(const std::string& name, Mode mode = CREATE, bool allow_duplicates = true);

	    /**
	     * \brief Destructor.
	     */
	    ~SQLiteScreeningDBCreator();

	    void open(const std::string& name, Mode mode = CREATE, bool allow_duplicates = true);

	    void close();

		Mode getMode() const;

		bool allowDuplicates() const;

	  private:
		SQLiteScreeningDBCreator(const SQLiteScreeningDBCreator&);

		SQLiteScreeningDBCreator& operator=(const SQLiteScreeningDBCreator&);

		void execStatements(const std::string& sql) const;

	    typedef boost::shared_ptr<sqlite3> SQLite3DBPointer;
	    typedef boost::shared_ptr<sqlite3_stmt> SQLite3StmtPointer;

	    SQLite3DBPointer database;
	    Mode             mode;
	    bool             duplicates;
	};

	/**
	 * @}
	 */
    }
}

#endif // CDPL_PHARM_SQLITESCREENINGDBCREATOR_HPP
