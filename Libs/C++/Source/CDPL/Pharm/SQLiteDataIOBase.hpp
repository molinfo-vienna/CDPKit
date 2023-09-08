/* 
 * SQLiteDataIOBase.hpp 
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


#ifndef CDPL_PHARM_SQLiteDATAIOBASE_HPP
#define CDPL_PHARM_SQLiteDATAIOBASE_HPP

#include <string>
#include <memory>

#include "SQLite3/sqlite3.h"


namespace CDPL
{

    namespace Pharm
    {

        class SQLiteDataIOBase
        {

          public:
            typedef std::shared_ptr<sqlite3>      SQLite3DBPointer;
            typedef std::shared_ptr<sqlite3_stmt> SQLite3StmtPointer;

            SQLiteDataIOBase() {}

            virtual ~SQLiteDataIOBase();

            void openDBConnection(const std::string& name, int mode);

            virtual void closeDBConnection();

            const std::string& getDBName() const;

            void setupStatement(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, bool clr_bindings) const;

            sqlite3_stmt* prepareStatement(const std::string& sql_stmt) const;

            int  evalStatement(const SQLite3StmtPointer& stmt_ptr) const;
            void execStatements(const std::string& sql_stmts) const;

            void resetStatement(const SQLite3StmtPointer& stmt_ptr, bool clr_bindings) const;

            void throwSQLiteIOError(const char* msg_prefix) const;

            const SQLite3DBPointer& getDBConnection() const;

          private:
            void composeExMessage(std::string& ex_msg, const char* msg_prefix, const char* err_msg) const;

            SQLiteDataIOBase(const SQLiteDataIOBase&);

            SQLiteDataIOBase& operator=(const SQLiteDataIOBase&);

            SQLite3DBPointer database;
            std::string      databaseName;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_SQLiteDATAIOBASE_HPP
