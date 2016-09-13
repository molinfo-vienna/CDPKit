/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLiteScreeningDBCreator.cpp 
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

#include <sqlite3.h>

#include "CDPL/Pharm/SQLiteScreeningDBCreator.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "SQLScreeningDBMetaData.hpp"


using namespace CDPL;


namespace
{

	const std::string CREATE_MOL_TABLE_SQL = std::string("CREATE TABLE IF NOT EXISTS ") + 
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER PRIMARY KEY, " + 
		Pharm::SQLScreeningDB::MOL_HASH_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_DATA_COLUMN_NAME + " BLOB);";

	const std::string DROP_MOL_TABLE_SQL = std::string("DROP TABLE IF EXISTS ") + 
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + ";";

	const std::string CREATE_PHARM_TABLE_SQL = std::string("CREATE TABLE IF NOT EXISTS ") + 
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::PHARM_DATA_COLUMN_NAME + " BLOB, PRIMARY KEY (" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + "));";

	const std::string DROP_PHARM_TABLE_SQL = std::string("DROP TABLE IF EXISTS ") + 
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + ";";

	const std::string CREATE_FTR_COUNT_TABLE_SQL = std::string("CREATE TABLE IF NOT EXISTS ") + 
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR_COUNT_COLUMN_NAME + " INTEGER);";
	
	const std::string DROP_FTR_COUNT_TABLE_SQL = std::string("DROP TABLE IF EXISTS ") + 
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + ";";

	const std::string CREATE_TWO_POINT_PHARM_TABLE_SQL = std::string("CREATE TABLE IF NOT EXISTS ") + 
		Pharm::SQLScreeningDB::TWO_POINT_PHARM_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR1_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR2_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR12_DIST_COLUMN_NAME + " REAL, PRIMARY KEY (" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + "));";
	
	const std::string DROP_TWO_POINT_PHARM_TABLE_SQL = std::string("DROP TABLE IF EXISTS ") + 
		Pharm::SQLScreeningDB::TWO_POINT_PHARM_TABLE_NAME + ";";

	const std::string CREATE_THREE_POINT_PHARM_TABLE_SQL = std::string("CREATE TABLE IF NOT EXISTS ") + 
		Pharm::SQLScreeningDB::THREE_POINT_PHARM_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR1_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR2_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR3_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR12_DIST_COLUMN_NAME + " REAL, " + 
		Pharm::SQLScreeningDB::FTR23_DIST_COLUMN_NAME + " REAL, " + 
		Pharm::SQLScreeningDB::FTR31_DIST_COLUMN_NAME + " REAL, PRIMARY KEY (" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + "));";
	
	const std::string DROP_THREE_POINT_PHARM_TABLE_SQL = std::string("DROP TABLE IF EXISTS ") + 
		Pharm::SQLScreeningDB::THREE_POINT_PHARM_TABLE_NAME + ";";
		
	const std::string CREATE_TABLES_SQL = 
		CREATE_MOL_TABLE_SQL +
		CREATE_PHARM_TABLE_SQL +
		CREATE_FTR_COUNT_TABLE_SQL +
		CREATE_TWO_POINT_PHARM_TABLE_SQL +
		CREATE_THREE_POINT_PHARM_TABLE_SQL;
	
	const std::string DROP_TABLES_SQL = 
		DROP_MOL_TABLE_SQL +
		DROP_PHARM_TABLE_SQL +
		DROP_FTR_COUNT_TABLE_SQL +
		DROP_TWO_POINT_PHARM_TABLE_SQL +
		DROP_THREE_POINT_PHARM_TABLE_SQL;
}


Pharm::SQLiteScreeningDBCreator::SQLiteScreeningDBCreator(): mode(CREATE), duplicates(true)
{}

Pharm::SQLiteScreeningDBCreator::SQLiteScreeningDBCreator(const std::string& name, Mode mode, bool allow_duplicates)
{
    open(name, mode, allow_duplicates);
}
	
Pharm::SQLiteScreeningDBCreator::~SQLiteScreeningDBCreator() 
{
	close();
}

void Pharm::SQLiteScreeningDBCreator::open(const std::string& name, Mode mode, bool allow_duplicates)
{
	close();

	this->mode = mode;
	duplicates = allow_duplicates;

	sqlite3* new_db;
	int res = sqlite3_open_v2(name.c_str(), &new_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	database.reset(new_db, sqlite3_close);

	if (res != SQLITE_OK)
		throw Base::IOError("SQLiteScreeningDBCreator: could not open database '" + name + "':"+ sqlite3_errmsg(new_db));

	execStatements("BEGIN TRANSACTION;");

	try {
		if (mode == CREATE)
			execStatements(DROP_TABLES_SQL);

		execStatements(CREATE_TABLES_SQL);
		
	} catch (...) {
		execStatements("ROLLBACK TRANSACTION;");
		throw;
	}

	execStatements("COMMIT TRANSACTION");
}

void Pharm::SQLiteScreeningDBCreator::close()
{
	database.reset();
}

Pharm::SQLiteScreeningDBCreator::Mode Pharm::SQLiteScreeningDBCreator::getMode() const
{
	return mode;
}

bool Pharm::SQLiteScreeningDBCreator::allowDuplicates() const
{
	return duplicates;
}

void Pharm::SQLiteScreeningDBCreator::execStatements(const std::string& sql) const
{
	char* err_msg = 0;
	int res = sqlite3_exec(database.get(), sql.c_str(), NULL, NULL, &err_msg);
		
	if (res != SQLITE_OK && res != SQLITE_DONE && res != SQLITE_ROW) {
		std::string ex_msg = "SQLiteScreeningDBCreator: error while SQL execution";

		if (err_msg) {
			ex_msg += ": ";
			ex_msg += err_msg;

			sqlite3_free(err_msg);
		}

		throw Base::IOError(ex_msg);
	}

	if (err_msg) 
		sqlite3_free(err_msg);
}
