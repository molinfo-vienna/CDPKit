/* 
 * PSDScreeningDBCreatorImpl.cpp 
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


#include "StaticInit.hpp"

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomArray3DCoordinatesFunctor.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "PSDScreeningDBCreatorImpl.hpp"
#include "SQLScreeningDBMetaData.hpp"


using namespace CDPL;


namespace
{

	const std::string CREATE_MOL_TABLE_SQL = "CREATE TABLE IF NOT EXISTS " + 
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER PRIMARY KEY, " + 
		Pharm::SQLScreeningDB::MOL_HASH_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_DATA_COLUMN_NAME + " BLOB);";

	const std::string DROP_MOL_TABLE_SQL = "DROP TABLE IF EXISTS " + 
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + ";";

	const std::string CREATE_PHARM_TABLE_SQL = "CREATE TABLE IF NOT EXISTS " + 
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::PHARM_DATA_COLUMN_NAME + " BLOB, PRIMARY KEY(" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + "));";
 
	const std::string DROP_PHARM_TABLE_SQL = "DROP TABLE IF EXISTS " + 
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + ";";

	const std::string CREATE_FTR_COUNT_TABLE_SQL = "CREATE TABLE IF NOT EXISTS " + 
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + "(" + 
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR_TYPE_COLUMN_NAME + " INTEGER, " + 
		Pharm::SQLScreeningDB::FTR_COUNT_COLUMN_NAME + " INTEGER);";
	
	const std::string DROP_FTR_COUNT_TABLE_SQL = "DROP TABLE IF EXISTS " + 
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + ";";

	const std::string CREATE_TABLES_SQL = 
		CREATE_MOL_TABLE_SQL +
		CREATE_PHARM_TABLE_SQL +
		CREATE_FTR_COUNT_TABLE_SQL;
	
	const std::string DROP_TABLES_SQL = 
		DROP_MOL_TABLE_SQL +
		DROP_PHARM_TABLE_SQL +
		DROP_FTR_COUNT_TABLE_SQL;

	const std::string MOL_ID_AND_HASH_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::MOL_HASH_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME;

	const std::string DELETE_MOL_WITH_MOL_ID_SQL = "DELETE FROM " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string DELETE_PHARMS_WITH_MOL_ID_SQL = "DELETE FROM " +
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string DELETE_FTR_COUNTS_WITH_MOL_ID_SQL = "DELETE FROM " +
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string INSERT_MOL_DATA_SQL = "INSERT INTO " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + "(" +
		Pharm::SQLScreeningDB::MOL_HASH_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_DATA_COLUMN_NAME + ") VALUES (?1, ?2);";

	const std::string INSERT_PHARM_DATA_SQL = "INSERT INTO " +
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + "(" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::PHARM_DATA_COLUMN_NAME + ") VALUES (?1, ?2, ?3);";

	const std::string INSERT_FTR_COUNT_SQL = "INSERT INTO " +
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + "(" +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::FTR_TYPE_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::FTR_COUNT_COLUMN_NAME + ") VALUES (?1, ?2, ?3, ?4);";

	const std::string BEGIN_TRANSACTION_SQL    = "BEGIN TRANSACTION;";
	const std::string COMMIT_TRANSACTION_SQL   = "COMMIT TRANSACTION;";
	const std::string ROLLBACK_TRANSACTION_SQL = "ROLLBACK TRANSACTION;";
	
	const std::string SQLITE_OPEN_PRAGMAS = 
		"PRAGMA page_size = 4096;" 
		"PRAGMA cache_size = 10000;"  
		"PRAGMA locking_mode = EXCLUSIVE;" 
		"PRAGMA synchronous = NORMAL;" 
//		"PRAGMA journal_mode = WAL;" 
		"PRAGMA temp_store = MEMORY;";
/*
	const std::string SQLITE_CLOSE_PRAGMAS = 
		"PRAGMA journal_mode = DELETE;" 
*/

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


Pharm::PSDScreeningDBCreatorImpl::PSDScreeningDBCreatorImpl():
	pharmWriter(controlParams),	molWriter(controlParams), pharmGenerator(), mode(ScreeningDBCreator::CREATE),
	allowDupEntries(true), numProcessed(0), numRejected(0), numDeleted(0), numInserted(0)
{
	initControlParams();
}

void Pharm::PSDScreeningDBCreatorImpl::open(const std::string& name, ScreeningDBCreator::Mode mode, bool allow_dup_entries)
{
	openDBConnection(name, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	this->mode = mode;
	allowDupEntries = allow_dup_entries;

	setupTables();
	loadMolHashToIDMap();
}

void Pharm::PSDScreeningDBCreatorImpl::close()
{
	closeDBConnection();
}

const std::string& Pharm::PSDScreeningDBCreatorImpl::getDatabaseName() const
{
	return getDBName();
}

void Pharm::PSDScreeningDBCreatorImpl::closeDBConnection()
{
	//execStatements(SQLITE_CLOSE_PRAGMAS);

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

	SQLiteDataIOBase::closeDBConnection();

	numProcessed = 0;
	numRejected = 0;
	numDeleted = 0;
	numInserted = 0;
}

Pharm::ScreeningDBCreator::Mode Pharm::PSDScreeningDBCreatorImpl::getMode() const
{
	return mode;
}

bool Pharm::PSDScreeningDBCreatorImpl::allowDuplicateEntries() const
{
	return allowDupEntries;
}

std::size_t Pharm::PSDScreeningDBCreatorImpl::getNumProcessed() const
{
	return numProcessed;
}

std::size_t Pharm::PSDScreeningDBCreatorImpl::getNumRejected() const
{
	return numRejected;
}

std::size_t Pharm::PSDScreeningDBCreatorImpl::getNumDeleted() const
{
	return numDeleted;
}

std::size_t Pharm::PSDScreeningDBCreatorImpl::getNumInserted() const
{
	return numInserted;
}

bool Pharm::PSDScreeningDBCreatorImpl::process(const Chem::MolecularGraph& molgraph)
{
	if (!getDBConnection())
		throw Base::IOError("PSDScreeningDBCreatorImpl: no open database connection");

	numProcessed++;
	std::uint64_t mol_hash = hashCalculator.calculate(molgraph);

	if (!allowDupEntries) {
		if (procMolecules.find(mol_hash) != procMolecules.end()) {
			numRejected++;
			return false;
		}

		if (mode == ScreeningDBCreator::APPEND && molHashToIDMap.find(mol_hash) != molHashToIDMap.end()) {
			numRejected++;
			return false;
		}
	}

	beginTransaction();

	TransactionRollback trb(getDBConnection().get());
	std::size_t num_del = 0;

	if (mode == ScreeningDBCreator::UPDATE)
		num_del = deleteEntries(mol_hash);

	genAndInsertPharmData(molgraph, insertMolecule(molgraph, mol_hash));

	commitTransaction();
	trb.disable();

	numDeleted += num_del;
	numInserted++;

	if (mode == ScreeningDBCreator::UPDATE)
		molHashToIDMap.erase(mol_hash);

	if (!allowDupEntries)
		procMolecules.insert(mol_hash);

	return true;
}

bool  Pharm::PSDScreeningDBCreatorImpl::merge(const ScreeningDBAccessor& db_acc, const ScreeningDBCreator::ProgressCallbackFunction& func)
{
	if (!getDBConnection())
		throw Base::IOError("PSDScreeningDBCreatorImpl: no open database connection");

	Chem::BasicMolecule mol;
	std::size_t num_mols = db_acc.getNumMolecules();
	std::size_t old_num_ins = numInserted;

	for (std::size_t i = 0; i < num_mols; i++) {
		if (func && !func(double(i) / num_mols))
			return (numInserted > old_num_ins);

		db_acc.getMolecule(i, mol);

		calcCIPPriorities(mol, false);
		numProcessed++;

		std::uint64_t mol_hash = hashCalculator.calculate(mol);
	
		if (!allowDupEntries) {
			if (procMolecules.find(mol_hash) != procMolecules.end()) {
				numRejected++;
				continue;
			}

			if (mode == ScreeningDBCreator::APPEND && molHashToIDMap.find(mol_hash) != molHashToIDMap.end()) {
				numRejected++;
				continue;
			}
		}

		beginTransaction();

		TransactionRollback trb(getDBConnection().get());
		std::size_t num_del = 0;

		if (mode == ScreeningDBCreator::UPDATE)
			num_del = deleteEntries(mol_hash);

		std::int64_t mol_id = insertMolecule(mol, mol_hash);
		std::size_t num_pharms = db_acc.getNumPharmacophores(i);

		for (std::size_t j = 0; j < num_pharms; j++) {
			pharmacophore.clear();
			db_acc.getPharmacophore(i, j, pharmacophore);

			featureCounts = db_acc.getFeatureCounts(i, j);

			insertPharmacophore(mol_id, j);
			insertFtrCounts(mol_id, j);
		}

		commitTransaction();
		trb.disable();

		numDeleted += num_del;
		numInserted++;

		if (mode == ScreeningDBCreator::UPDATE)
			molHashToIDMap.erase(mol_hash);

		if (!allowDupEntries)
			procMolecules.insert(mol_hash);
	}

	if (func)
		func(1.0);

	return (numInserted > old_num_ins);
}

void Pharm::PSDScreeningDBCreatorImpl::initControlParams()
{
	Pharm::setStrictErrorCheckingParameter(controlParams, true);
	Chem::setStrictErrorCheckingParameter(controlParams, true);

	Pharm::setCDFWriteSinglePrecisionFloatsParameter(controlParams, true);
	Chem::setCDFWriteSinglePrecisionFloatsParameter(controlParams, true);
}

void Pharm::PSDScreeningDBCreatorImpl::setupTables()
{
	execStatements(SQLITE_OPEN_PRAGMAS);

	beginTransaction();
	TransactionRollback trb(getDBConnection().get());

	if (mode == ScreeningDBCreator::CREATE)
		execStatements(DROP_TABLES_SQL);

	execStatements(CREATE_TABLES_SQL);

	commitTransaction();
	trb.disable();

	// The prepared 'BEGIN TRANSACTION' seems not to be reusable anymore if tables are dropped/created
	// Maybe this is a bug?
	beginTransStmt.reset(); 
}

void Pharm::PSDScreeningDBCreatorImpl::loadMolHashToIDMap()
{
	procMolecules.clear();
	molHashToIDMap.clear();

	if (!(mode == ScreeningDBCreator::UPDATE || (mode == ScreeningDBCreator::APPEND && !allowDupEntries)))
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
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while loading existing molecule IDs and hashes");
}

std::size_t Pharm::PSDScreeningDBCreatorImpl::deleteEntries(std::uint64_t mol_hash)
{
	std::size_t num_del = 0;
	std::pair<MolHashToIDMap::iterator, MolHashToIDMap::iterator> mols_with_hash = molHashToIDMap.equal_range(mol_hash);

	for (MolHashToIDMap::iterator it = mols_with_hash.first; it != mols_with_hash.second; ++it, num_del++) {
		std::uint64_t mol_id = it->second;
		
		deleteRowsWithMolID(delMolWithMolIDStmt, DELETE_MOL_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delPharmsWithMolIDStmt, DELETE_PHARMS_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delFeatureCountsWithMolIDStmt, DELETE_FTR_COUNTS_WITH_MOL_ID_SQL, mol_id);
	}

	return num_del;
}

std::int64_t Pharm::PSDScreeningDBCreatorImpl::insertMolecule(const Chem::MolecularGraph& molgraph, std::uint64_t mol_hash)
{
	molWriter.writeMolGraph(molgraph, byteBuffer);

	setupStatement(insMoleculeStmt, INSERT_MOL_DATA_SQL, true);

	if (sqlite3_bind_int64(insMoleculeStmt.get(), 1, mol_hash) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding molecule hashcode to prepared statement");

	if (sqlite3_bind_blob(insMoleculeStmt.get(), 2, byteBuffer.getData(), boost::numeric_cast<int>(byteBuffer.getSize()),
						  SQLITE_TRANSIENT) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding molecule data BLOB to prepared statement");

	evalStatement(insMoleculeStmt);

	return sqlite3_last_insert_rowid(getDBConnection().get());
}

void Pharm::PSDScreeningDBCreatorImpl::genAndInsertPharmData(const Chem::MolecularGraph& molgraph, std::int64_t mol_id)
{
	std::size_t num_confs = getNumConformations(molgraph);

	if (num_confs == 0) {
		if (hasCoordinates(molgraph, 3)) {
			coordinates.clear();
			get3DCoordinates(molgraph, coordinates);

			pharmGenerator.setAtom3DCoordinatesFunction(Chem::AtomArray3DCoordinatesFunctor(coordinates, molgraph));
			genAndInsertPharmData(molgraph, mol_id, 0);
		}

		return;
	}

	for (std::size_t i = 0; i < num_confs; i++) {
		coordinates.clear();
		getConformation(molgraph, i, coordinates);

		pharmGenerator.setAtom3DCoordinatesFunction(Chem::AtomArray3DCoordinatesFunctor(coordinates, molgraph));
		genAndInsertPharmData(molgraph, mol_id, i);
	}
}

void Pharm::PSDScreeningDBCreatorImpl::genAndInsertPharmData(const Chem::MolecularGraph& molgraph, std::int64_t mol_id, std::size_t conf_idx)
{
	pharmacophore.clear();
	pharmGenerator.generate(molgraph, pharmacophore);

	insertPharmacophore(mol_id, conf_idx);
	genFtrCounts();
	insertFtrCounts(mol_id, conf_idx);
}

void Pharm::PSDScreeningDBCreatorImpl::insertPharmacophore(std::int64_t mol_id, std::size_t conf_idx)
{
	pharmWriter.writeFeatureContainer(pharmacophore, byteBuffer);

	setupStatement(insPharmStmt, INSERT_PHARM_DATA_SQL, true);

	if (sqlite3_bind_int64(insPharmStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding pharmacophore molecule ID to prepared statement");

	if (sqlite3_bind_int(insPharmStmt.get(), 2, boost::numeric_cast<int>(conf_idx)) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding pharmacophore conf. index to prepared statement");

	if (sqlite3_bind_blob(insPharmStmt.get(), 3, byteBuffer.getData(), boost::numeric_cast<int>(byteBuffer.getSize()),
						  SQLITE_TRANSIENT) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding pharmacophore data BLOB to prepared statement");

	evalStatement(insPharmStmt);
}

void Pharm::PSDScreeningDBCreatorImpl::genFtrCounts()
{
	featureCounts.clear();
	buildFeatureTypeHistogram(pharmacophore, featureCounts);
}

void Pharm::PSDScreeningDBCreatorImpl::insertFtrCounts(std::int64_t mol_id, std::size_t conf_idx)
{
	for (FeatureTypeHistogram::ConstEntryIterator it = featureCounts.getEntriesBegin(), end = featureCounts.getEntriesEnd(); it != end; ++it)
		insertFtrCount(mol_id, conf_idx, it->first, it->second);
}

void Pharm::PSDScreeningDBCreatorImpl::insertFtrCount(std::int64_t mol_id, std::size_t conf_idx, unsigned int ftr_type, std::size_t ftr_count)
{
	setupStatement(insFtrCountStmt, INSERT_FTR_COUNT_SQL, true);

	if (sqlite3_bind_int64(insFtrCountStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding feature count molecule ID to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 2, boost::numeric_cast<int>(conf_idx)) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding feature count conf. index to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 3, ftr_type) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding feature type to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 4, boost::numeric_cast<int>(ftr_count)) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding feature count to prepared statement");

	evalStatement(insFtrCountStmt);
}

void Pharm::PSDScreeningDBCreatorImpl::deleteRowsWithMolID(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, std::int64_t mol_id) const
{
	setupStatement(stmt_ptr, sql_stmt, true);

	if (sqlite3_bind_int64(stmt_ptr.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreatorImpl: error while binding molecule ID to prepared statement");

	evalStatement(stmt_ptr);
}

void Pharm::PSDScreeningDBCreatorImpl::beginTransaction()
{
	setupStatement(beginTransStmt, BEGIN_TRANSACTION_SQL, false);
	evalStatement(beginTransStmt);
}

void Pharm::PSDScreeningDBCreatorImpl::commitTransaction()
{
	setupStatement(commitTransStmt, COMMIT_TRANSACTION_SQL, false);
	evalStatement(commitTransStmt);
}
