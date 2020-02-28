/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLiteDataIOBase.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Base/Exceptions.hpp"

#include "SQLiteDataIOBase.hpp"


using namespace CDPL;


Pharm::SQLiteDataIOBase::~SQLiteDataIOBase()
{
	closeDBConnection();
}

const Pharm::SQLiteDataIOBase::SQLite3DBPointer& Pharm::SQLiteDataIOBase::getDBConnection() const
{
	return database;
}

void Pharm::SQLiteDataIOBase::openDBConnection(const std::string& name, int mode)
{
	sqlite3* new_db = 0;
	int res = sqlite3_open_v2(name.c_str(), &new_db, mode, NULL);
	SQLite3DBPointer new_db_ptr(new_db, sqlite3_close);

	if (res != SQLITE_OK)
		throwSQLiteIOError(("SQLiteDataIOBase: could not open database '" + name + "'").c_str());

	databaseName.reserve(name.length());

	closeDBConnection();

	databaseName = name;
	database = new_db_ptr;
}

void Pharm::SQLiteDataIOBase::closeDBConnection()
{
	database.reset();
	databaseName.clear();
}

const std::string& Pharm::SQLiteDataIOBase::getDBName() const
{
	return databaseName;
}

void Pharm::SQLiteDataIOBase::execStatements(const std::string& sql_stmts) const
{
	char* err_msg = 0;
	int res = sqlite3_exec(database.get(), sql_stmts.c_str(), NULL, NULL, &err_msg);
	boost::shared_ptr<char> err_msg_ptr(err_msg, sqlite3_free);

	if (res != SQLITE_OK && res != SQLITE_DONE && res != SQLITE_ROW) {
		std::string ex_msg;

		composeExMessage(ex_msg, "SQLiteDataIOBase: error while SQL execution", err_msg);

		throw Base::IOError(ex_msg);
	}
}

void Pharm::SQLiteDataIOBase::setupStatement(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, bool clr_bindings) const
{	
	if (!stmt_ptr)
		stmt_ptr.reset(prepareStatement(sql_stmt), sqlite3_finalize);
	else
		resetStatement(stmt_ptr, clr_bindings);
}

sqlite3_stmt* Pharm::SQLiteDataIOBase::prepareStatement(const std::string& sql_stmt) const
{
	sqlite3_stmt* stmt = 0;
	
	if (sqlite3_prepare(database.get(), sql_stmt.c_str(), -1, &stmt, NULL) != SQLITE_OK)
		throwSQLiteIOError("SQLiteDataIOBase: creation of prepared statement failed");

	return stmt;
}

int Pharm::SQLiteDataIOBase::evalStatement(const SQLite3StmtPointer& stmt_ptr) const
{
	int res = sqlite3_step(stmt_ptr.get());

	if (res != SQLITE_DONE && res != SQLITE_ROW && res != SQLITE_OK) {
		throwSQLiteIOError("SQLiteDataIOBase: evaluation of prepared statement failed");
	}

	return res;
}

void Pharm::SQLiteDataIOBase::resetStatement(const SQLite3StmtPointer& stmt_ptr, bool clr_bindings) const
{
	sqlite3_reset(stmt_ptr.get());

	if (clr_bindings &&	sqlite3_clear_bindings(stmt_ptr.get()) != SQLITE_OK)
		throwSQLiteIOError("SQLiteDataIOBase: clearing of prepared statement bindings failes");
}

void Pharm::SQLiteDataIOBase::composeExMessage(std::string& ex_msg, const char* msg_prefix, const char* err_msg) const
{
	ex_msg.append(msg_prefix);

	if (err_msg) {
		ex_msg.append(": ");
		ex_msg.append(err_msg);
	}
}

void Pharm::SQLiteDataIOBase::throwSQLiteIOError(const char* msg_prefix) const
{
	std::string ex_msg;

	composeExMessage(ex_msg, msg_prefix, sqlite3_errmsg(database.get()));

	throw Base::IOError(ex_msg);
}
