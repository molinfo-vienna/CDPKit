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

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/IntTypes.hpp"


struct sqlite3;
struct sqlite3_stmt;


namespace CDPL 
{

	namespace Chem
	{
		
		class MolecularGraph;
		class CDFDataWriter;
	}

	namespace Internal
	{
		
		class ByteBuffer;
	}

    namespace Pharm
    {
	
		class CDFDataWriter;

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
			typedef boost::shared_ptr<sqlite3_stmt> SQLite3StmtPointer;

			SQLiteScreeningDBCreator(const SQLiteScreeningDBCreator&);

			SQLiteScreeningDBCreator& operator=(const SQLiteScreeningDBCreator&);

			void initControlParams();

			void openDBConnection(const std::string& name);
			void setupTables();

			void loadMolHashToIDMap();

			std::size_t deleteEntries(Base::uint64 mol_hash);

			Base::int64 insertMolecule(const Chem::MolecularGraph& molgraph, Base::uint64 mol_hash);

			void genAndInsertPharmData(const Chem::MolecularGraph& molgraph, Base::int64 mol_id);
			void genAndInsertPharmData(const Chem::MolecularGraph& molgraph, Base::int64 mol_id, std::size_t conf_idx);

			void insertPharmacophore(Base::int64 mol_id, std::size_t conf_idx);

			void insertFtrCounts(Base::int64 mol_id, std::size_t conf_idx);
			void insertFtrCount(Base::int64 mol_id, std::size_t conf_idx, unsigned int ftr_type, std::size_t ftr_count);

			void deleteRowsWithMolID(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, Base::int64 mol_id) const;

			void beginTransaction();
			void commitTransaction();
			void rollbackTransaction() const;

			void setupStatement(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, bool clr_bindings) const;

			sqlite3_stmt* prepareStatement(const std::string& sql_stmt) const;
		
			int evalStatement(const SQLite3StmtPointer& stmt_ptr) const;
			void execStatements(const std::string& sql_stmts) const;

			void resetStatement(const SQLite3StmtPointer& stmt_ptr, bool clr_bindings) const;

			void composeExMessage(std::string& ex_msg, const char* msg_prefix, const char* err_msg) const;

			void throwSQLiteIOError(const char* msg_prefix) const;

			typedef boost::shared_ptr<sqlite3> SQLite3DBPointer;
			typedef boost::unordered_multimap<Base::uint64, Base::int64> MolHashToIDMap;
			typedef boost::unordered_set<Base::uint64> MolHashSet;
			typedef std::auto_ptr<Internal::ByteBuffer> ByteBufferPointer;
			typedef std::auto_ptr<CDFDataWriter> CDFPharmWriterPointer;
			typedef std::auto_ptr<Chem::CDFDataWriter> CDFMolWriterPointer;

			SQLite3DBPointer              database;
			std::string                   databaseName;
			SQLite3StmtPointer            beginTransStmt;
			SQLite3StmtPointer            commitTransStmt;
			SQLite3StmtPointer            insMoleculeStmt;
			SQLite3StmtPointer            insPharmStmt;
			SQLite3StmtPointer            insFtrCountStmt;
			SQLite3StmtPointer            delMolWithMolIDStmt;
			SQLite3StmtPointer            delPharmsWithMolIDStmt;
			SQLite3StmtPointer            delFeatureCountsWithMolIDStmt;
			SQLite3StmtPointer            delTwoPointPharmsWithMolIDStmt;
			SQLite3StmtPointer            delThreePointPharmsWithMolIDStmt;
			MolHashToIDMap                molHashToIDMap;
			MolHashSet                    procMolecules;
			Chem::HashCodeCalculator      hashCalculator;
			ByteBufferPointer             byteBuffer;
			CDFPharmWriterPointer         pharmWriter;
			CDFMolWriterPointer           molWriter;
			BasicPharmacophore            pharmacophore;
			DefaultPharmacophoreGenerator pharmGenerator;
			FeatureTypeHistogram          featureCounts;
			Base::ControlParameterList    controlParams;
			Mode                          mode;
			bool                          allowDupEntries;
			std::size_t                   numProcessed;
			std::size_t                   numRejected;
			std::size_t                   numDeleted;
			std::size_t                   numInserted;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_SQLITESCREENINGDBCREATOR_HPP
