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

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Pharm/SQLiteScreeningDBCreator.hpp"
#include "CDPL/Pharm/CDFDataWriter.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/CDFDataWriter.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/AtomConformer3DCoordinatesFunctor.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

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
		Pharm::SQLScreeningDB::PHARM_DATA_COLUMN_NAME + " BLOB, PRIMARY KEY(" +
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
		Pharm::SQLScreeningDB::TWO_POINT_PHARM_DATA_COLUMN_NAME + " BLOB, PRIMARY KEY(" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + "));";
	
	const std::string DROP_TWO_POINT_PHARM_TABLE_SQL = std::string("DROP TABLE IF EXISTS ") + 
		Pharm::SQLScreeningDB::TWO_POINT_PHARM_TABLE_NAME + ";";

	const std::string CREATE_THREE_POINT_PHARM_TABLE_SQL = std::string("CREATE TABLE IF NOT EXISTS ") + 
		Pharm::SQLScreeningDB::THREE_POINT_PHARM_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::THREE_POINT_PHARM_DATA_COLUMN_NAME + " BLOB, PRIMARY KEY(" +
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

	const std::string MOL_ID_AND_HASH_QUERY_SQL = std::string("SELECT ") +
		Pharm::SQLScreeningDB::MOL_HASH_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME;

	const std::string DELETE_MOL_WITH_MOL_ID_SQL = std::string("DELETE FROM ") +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string DELETE_PHARMS_WITH_MOL_ID_SQL = std::string("DELETE FROM ") +
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string DELETE_FTR_COUNTS_WITH_MOL_ID_SQL = std::string("DELETE FROM ") +
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string DELETE_TWO_POINT_PHARMS_WITH_MOL_ID_SQL = std::string("DELETE FROM ") +
		Pharm::SQLScreeningDB::TWO_POINT_PHARM_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string DELETE_THREE_POINT_PHARMS_WITH_MOL_ID_SQL = std::string("DELETE FROM ") +
		Pharm::SQLScreeningDB::THREE_POINT_PHARM_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string INSERT_MOL_DATA_SQL = std::string("INSERT INTO ") +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + "(" +
		Pharm::SQLScreeningDB::MOL_HASH_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_DATA_COLUMN_NAME + ") VALUES (?1, ?2);";

	const std::string INSERT_PHARM_DATA_SQL = std::string("INSERT INTO ") +
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + "(" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::PHARM_DATA_COLUMN_NAME + ") VALUES (?1, ?2, ?3);";

	const std::string INSERT_FTR_COUNT_SQL = std::string("INSERT INTO ") +
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + "(" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::FTR_TYPE_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::FTR_COUNT_COLUMN_NAME + ") VALUES (?1, ?2, ?3, ?4);";

	const std::string BEGIN_TRANSACTION_SQL    = "BEGIN TRANSACTION;";
	const std::string COMMIT_TRANSACTION_SQL   = "COMMIT TRANSACTION;";
	const std::string ROLLBACK_TRANSACTION_SQL = "ROLLBACK TRANSACTION;";

	class TransactionRollback
	{
		
	public:
		TransactionRollback(sqlite3* db): database(db), disabled(false) {}

		~TransactionRollback() {
			if (!disabled)
				sqlite3_exec(database, ROLLBACK_TRANSACTION_SQL.c_str(), NULL, NULL, NULL);
		}

		void disable() {
			disabled = true;
		}

	private:
		sqlite3* database;
		bool     disabled;
	};
}


Pharm::SQLiteScreeningDBCreator::SQLiteScreeningDBCreator(): 
	byteBuffer(new Internal::ByteBuffer()), pharmWriter(new CDFDataWriter(controlParams)),
	molWriter(new Chem::CDFDataWriter(controlParams)), pharmGenerator(true), mode(CREATE),
	allowDupEntries(true), numProcessed(0), numRejected(0), numDeleted(0), numInserted(0)
{
	initControlParams();
}

Pharm::SQLiteScreeningDBCreator::SQLiteScreeningDBCreator(const std::string& name, Mode mode, bool allow_dup_entries):
	byteBuffer(new Internal::ByteBuffer()), pharmWriter(new CDFDataWriter(controlParams)),
	molWriter(new Chem::CDFDataWriter(controlParams)), pharmGenerator(true), mode(CREATE),
	allowDupEntries(true), numProcessed(0), numRejected(0), numDeleted(0), numInserted(0)
{
	initControlParams();
    open(name, mode, allow_dup_entries);
}
	
Pharm::SQLiteScreeningDBCreator::~SQLiteScreeningDBCreator() 
{
	close();
}

void Pharm::SQLiteScreeningDBCreator::open(const std::string& name, Mode mode, bool allow_dup_entries)
{
	openDBConnection(name);

	this->mode = mode;
	allowDupEntries = allow_dup_entries;

	setupTables();
	loadMolHashToIDMap();
}

void Pharm::SQLiteScreeningDBCreator::close()
{
	if (!database)
		return;

	beginTransStmt.reset();
	commitTransStmt.reset();
	insMoleculeStmt.reset();
	insPharmStmt.reset();
	insFtrCountStmt.reset();
	delMolWithMolIDStmt.reset();
	delPharmsWithMolIDStmt.reset();
	delFeatureCountsWithMolIDStmt.reset();
	delTwoPointPharmsWithMolIDStmt.reset();
	delThreePointPharmsWithMolIDStmt.reset();

	database.reset();
	databaseName.clear();

	numProcessed = 0;
	numRejected = 0;
	numDeleted = 0;
	numInserted = 0;
}

Pharm::SQLiteScreeningDBCreator::Mode Pharm::SQLiteScreeningDBCreator::getMode() const
{
	return mode;
}

bool Pharm::SQLiteScreeningDBCreator::allowDuplicateEntries() const
{
	return allowDupEntries;
}

const std::string& Pharm::SQLiteScreeningDBCreator::getDatabaseName() const
{
	return databaseName;
}

std::size_t Pharm::SQLiteScreeningDBCreator::getNumProcessed() const
{
	return numProcessed;
}

std::size_t Pharm::SQLiteScreeningDBCreator::getNumRejected() const
{
	return numRejected;
}

std::size_t Pharm::SQLiteScreeningDBCreator::getNumDeleted() const
{
	return numDeleted;
}

std::size_t Pharm::SQLiteScreeningDBCreator::getNumInserted() const
{
	return numInserted;
}

bool Pharm::SQLiteScreeningDBCreator::process(const Chem::MolecularGraph& molgraph)
{
	if (!database)
		throw Base::IOError("SQLiteScreeningDBCreator: no open database connection");

	numProcessed++;
	Base::uint64 mol_hash = hashCalculator.calculate(molgraph);

	if (!allowDupEntries) {
		if (procMolecules.find(mol_hash) != procMolecules.end()) {
			numRejected++;
			return false;
		}

		if (mode == APPEND && molHashToIDMap.find(mol_hash) != molHashToIDMap.end()) {
			numRejected++;
			return false;
		}
	}

	beginTransaction();

	TransactionRollback trb(database.get());
	std::size_t num_del = 0;

	if (mode == UPDATE)
		num_del = deleteEntries(mol_hash);

	genAndInsertPharmData(molgraph, insertMolecule(molgraph, mol_hash));

	commitTransaction();
	trb.disable();

	numDeleted += num_del;
	numInserted++;

	if (mode == UPDATE)
		molHashToIDMap.erase(mol_hash);

	if (!allowDupEntries)
		procMolecules.insert(mol_hash);

	return true;
}

void Pharm::SQLiteScreeningDBCreator::initControlParams()
{
	Pharm::setStrictErrorCheckingParameter(controlParams, true);
	Chem::setStrictErrorCheckingParameter(controlParams, true);

	Pharm::setCDFWriteSinglePrecisionFloatsParameter(controlParams, true);
	Chem::setCDFWriteSinglePrecisionFloatsParameter(controlParams, true);
}

void Pharm::SQLiteScreeningDBCreator::openDBConnection(const std::string& name)
{
	sqlite3* new_db = 0;
	int res = sqlite3_open_v2(name.c_str(), &new_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	SQLite3DBPointer new_db_ptr(new_db, sqlite3_close);

	if (res != SQLITE_OK)
		throwSQLiteIOError(("SQLiteScreeningDBCreator: could not open database '" + name + "'").c_str());

	databaseName.reserve(name.length());

	close();

	databaseName = name;
	database = new_db_ptr;
}

void Pharm::SQLiteScreeningDBCreator::setupTables()
{
	beginTransaction();
	TransactionRollback trb(database.get());

	if (mode == CREATE)
		execStatements(DROP_TABLES_SQL);

	execStatements(CREATE_TABLES_SQL);

	commitTransaction();
	trb.disable();

	// The prepared 'BEGIN TRANSACTION' seems not to be reusable anymore if tables are dropped/created
	// Maybe this is a bug?
	beginTransStmt.reset(); 
}

void Pharm::SQLiteScreeningDBCreator::loadMolHashToIDMap()
{
	procMolecules.clear();
	molHashToIDMap.clear();

	if (!(mode == UPDATE || (mode == APPEND && !allowDupEntries)))
		return;

	SQLite3StmtPointer stmt_ptr;
	int res;

	setupStatement(stmt_ptr, MOL_ID_AND_HASH_QUERY_SQL, false);

	while ((res = sqlite3_step(stmt_ptr.get())) == SQLITE_ROW) {
		sqlite3_int64 mol_hash = sqlite3_column_int64(stmt_ptr.get(), 0);
		sqlite3_int64 mol_id = sqlite3_column_int64(stmt_ptr.get(), 1);

		molHashToIDMap.insert(MolHashToIDMap::value_type(mol_hash, mol_id));
	}

	if (res != SQLITE_DONE)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while loading existing molecule IDs and hashes");
}

std::size_t Pharm::SQLiteScreeningDBCreator::deleteEntries(Base::uint64 mol_hash)
{
	std::size_t num_del = 0;
	std::pair<MolHashToIDMap::iterator, MolHashToIDMap::iterator> mols_with_hash = molHashToIDMap.equal_range(mol_hash);

	for (MolHashToIDMap::iterator it = mols_with_hash.first; it != mols_with_hash.second; ++it, num_del++) {
		Base::uint64 mol_id = it->second;
		
		deleteRowsWithMolID(delMolWithMolIDStmt, DELETE_MOL_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delPharmsWithMolIDStmt, DELETE_PHARMS_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delFeatureCountsWithMolIDStmt, DELETE_FTR_COUNTS_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delTwoPointPharmsWithMolIDStmt, DELETE_TWO_POINT_PHARMS_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delThreePointPharmsWithMolIDStmt, DELETE_THREE_POINT_PHARMS_WITH_MOL_ID_SQL, mol_id);
	}

	return num_del;
}

Base::int64 Pharm::SQLiteScreeningDBCreator::insertMolecule(const Chem::MolecularGraph& molgraph, Base::uint64 mol_hash)
{
	molWriter->writeMolGraph(molgraph, *byteBuffer);

	setupStatement(insMoleculeStmt, INSERT_MOL_DATA_SQL, true);

	if (sqlite3_bind_int64(insMoleculeStmt.get(), 1, mol_hash) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding molecule hashcode to prepared statement");

	if (sqlite3_bind_blob(insMoleculeStmt.get(), 2, byteBuffer->getData(), boost::numeric_cast<int>(byteBuffer->getSize()),
						  SQLITE_TRANSIENT) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding molecule data BLOB to prepared statement");

	evalStatement(insMoleculeStmt);

	return sqlite3_last_insert_rowid(database.get());
}

void Pharm::SQLiteScreeningDBCreator::genAndInsertPharmData(const Chem::MolecularGraph& molgraph, Base::int64 mol_id)
{
	std::size_t num_confs = getNumConformations(molgraph);

	if (num_confs == 0) {
		if (hasCoordinates(molgraph, 3)) {
			pharmGenerator.setAtom3DCoordinatesFunction(Chem::Atom3DCoordinatesFunctor());
			genAndInsertPharmData(molgraph, mol_id, 0);
		}

		return;
	}

	for (std::size_t i = 0; i < num_confs; i++) {
		pharmGenerator.setAtom3DCoordinatesFunction(Chem::AtomConformer3DCoordinatesFunctor(i));
		genAndInsertPharmData(molgraph, mol_id, i);
	}
}

void Pharm::SQLiteScreeningDBCreator::genAndInsertPharmData(const Chem::MolecularGraph& molgraph, Base::int64 mol_id, std::size_t conf_idx)
{
	pharmacophore.clear();
	pharmGenerator.generate(molgraph, pharmacophore);

	insertPharmacophore(mol_id, conf_idx);
	insertFtrCounts(mol_id, conf_idx);
}

void Pharm::SQLiteScreeningDBCreator::insertPharmacophore(Base::int64 mol_id, std::size_t conf_idx)
{
	pharmWriter->writePharmacophore(pharmacophore, *byteBuffer);

	setupStatement(insPharmStmt, INSERT_PHARM_DATA_SQL, true);

	if (sqlite3_bind_int64(insPharmStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding pharmacophore molecule ID to prepared statement");

	if (sqlite3_bind_int(insPharmStmt.get(), 2, boost::numeric_cast<int>(conf_idx)) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding pharmacophore conf. index to prepared statement");

	if (sqlite3_bind_blob(insPharmStmt.get(), 3, byteBuffer->getData(), boost::numeric_cast<int>(byteBuffer->getSize()),
						  SQLITE_TRANSIENT) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding pharmacophore data BLOB to prepared statement");

	evalStatement(insPharmStmt);
}

void Pharm::SQLiteScreeningDBCreator::insertFtrCounts(Base::int64 mol_id, std::size_t conf_idx)
{
	featureCounts.clear();
	buildFeatureTypeHistogram(pharmacophore, featureCounts);

	for (FeatureTypeHistogram::ConstEntryIterator it = featureCounts.getEntriesBegin(), end = featureCounts.getEntriesEnd(); it != end; ++it)
		insertFtrCount(mol_id, conf_idx, it->first, it->second);
}

void Pharm::SQLiteScreeningDBCreator::insertFtrCount(Base::int64 mol_id, std::size_t conf_idx, unsigned int ftr_type, std::size_t ftr_count)
{
	setupStatement(insFtrCountStmt, INSERT_FTR_COUNT_SQL, true);

	if (sqlite3_bind_int64(insFtrCountStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding feature count molecule ID to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 2, boost::numeric_cast<int>(conf_idx)) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding feature count conf. index to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 3, ftr_type) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding feature type to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 4, boost::numeric_cast<int>(ftr_count)) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding feature count to prepared statement");

	evalStatement(insFtrCountStmt);
}

void Pharm::SQLiteScreeningDBCreator::deleteRowsWithMolID(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, Base::int64 mol_id) const
{
	setupStatement(stmt_ptr, sql_stmt, true);

	if (sqlite3_bind_int64(stmt_ptr.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: error while binding molecule ID to prepared statement");

	evalStatement(stmt_ptr);
}

void Pharm::SQLiteScreeningDBCreator::execStatements(const std::string& sql_stmts) const
{
	char* err_msg = 0;
	int res = sqlite3_exec(database.get(), sql_stmts.c_str(), NULL, NULL, &err_msg);
	boost::shared_ptr<char> err_msg_ptr(err_msg, sqlite3_free);

	if (res != SQLITE_OK && res != SQLITE_DONE && res != SQLITE_ROW) {
		std::string ex_msg;

		composeExMessage(ex_msg, "SQLiteScreeningDBCreator: error while SQL execution", err_msg);

		throw Base::IOError(ex_msg);
	}
}

void Pharm::SQLiteScreeningDBCreator::beginTransaction()
{
	setupStatement(beginTransStmt, BEGIN_TRANSACTION_SQL, false);
	evalStatement(beginTransStmt);
}

void Pharm::SQLiteScreeningDBCreator::commitTransaction()
{
	setupStatement(commitTransStmt, COMMIT_TRANSACTION_SQL, false);
	evalStatement(commitTransStmt);
}

void Pharm::SQLiteScreeningDBCreator::setupStatement(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, bool clr_bindings) const
{	
	if (!stmt_ptr)
		stmt_ptr.reset(prepareStatement(sql_stmt), sqlite3_finalize);
	else
		resetStatement(stmt_ptr, clr_bindings);
}

sqlite3_stmt* Pharm::SQLiteScreeningDBCreator::prepareStatement(const std::string& sql_stmt) const
{
	sqlite3_stmt* stmt = 0;
	
	if (sqlite3_prepare(database.get(), sql_stmt.c_str(), -1, &stmt, NULL) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: creation of prepared statement failed");

	return stmt;
}

int Pharm::SQLiteScreeningDBCreator::evalStatement(const SQLite3StmtPointer& stmt_ptr) const
{
	int res = sqlite3_step(stmt_ptr.get());

	if (res != SQLITE_DONE && res != SQLITE_ROW && res != SQLITE_OK) {
		throwSQLiteIOError("SQLiteScreeningDBCreator: evaluation of prepared statement failed");
	}

	return res;
}

void Pharm::SQLiteScreeningDBCreator::resetStatement(const SQLite3StmtPointer& stmt_ptr, bool clr_bindings) const
{
	sqlite3_reset(stmt_ptr.get());

	if (clr_bindings &&	sqlite3_clear_bindings(stmt_ptr.get()) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBCreator: clearing of prepared statement bindings failes");
}

void Pharm::SQLiteScreeningDBCreator::composeExMessage(std::string& ex_msg, const char* msg_prefix, const char* err_msg) const
{
	ex_msg.append(msg_prefix);

	if (err_msg) {
		ex_msg.append(": ");
		ex_msg.append(err_msg);
	}
}

void Pharm::SQLiteScreeningDBCreator::throwSQLiteIOError(const char* msg_prefix) const
{
	std::string ex_msg;

	composeExMessage(ex_msg, msg_prefix, sqlite3_errmsg(database.get()));

	throw Base::IOError(ex_msg);
}
