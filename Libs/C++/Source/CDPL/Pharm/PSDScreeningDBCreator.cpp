/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDScreeningDBCreator.cpp 
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

#include <boost/numeric/conversion/cast.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/CDFDataWriter.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomArray3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/IntTypes.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "SQLScreeningDBMetaData.hpp"
#include "CDFDataWriter.hpp"
#include "PSDImplementationBase.hpp"


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


class Pharm::PSDScreeningDBCreator::Implementation : private Pharm::PSDImplementationBase
{

public:
	Implementation();

	void open(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true);

	void close();

	const std::string& getDatabaseName() const;

	Mode getMode() const;

	bool allowDuplicateEntries() const;

	bool process(const Chem::MolecularGraph& molgraph);

	std::size_t getNumProcessed() const;

	std::size_t getNumRejected() const;

	std::size_t getNumDeleted() const;

	std::size_t getNumInserted() const;

private:
	void initControlParams();

	void closeDBConnection();

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

	typedef boost::unordered_multimap<Base::uint64, Base::int64> MolHashToIDMap;
	typedef boost::unordered_set<Base::uint64> MolHashSet;
	typedef std::auto_ptr<Chem::CDFDataWriter> CDFMolWriterPointer;

	SQLite3StmtPointer               beginTransStmt;
	SQLite3StmtPointer               commitTransStmt;
	SQLite3StmtPointer               insMoleculeStmt;
	SQLite3StmtPointer               insPharmStmt;
	SQLite3StmtPointer               insFtrCountStmt;
	SQLite3StmtPointer               delMolWithMolIDStmt;
	SQLite3StmtPointer               delPharmsWithMolIDStmt;
	SQLite3StmtPointer               delFeatureCountsWithMolIDStmt;
	SQLite3StmtPointer               delTwoPointPharmsWithMolIDStmt;
	SQLite3StmtPointer               delThreePointPharmsWithMolIDStmt;
	MolHashToIDMap                   molHashToIDMap;
	MolHashSet                       procMolecules;
	Chem::HashCodeCalculator         hashCalculator;
	Internal::ByteBuffer             byteBuffer;
	Base::ControlParameterList       controlParams;
	CDFDataWriter                    pharmWriter;
	Chem::CDFDataWriter              molWriter;
	BasicPharmacophore               pharmacophore;
	DefaultPharmacophoreGenerator    pharmGenerator;
	FeatureTypeHistogram             featureCounts;
	Math::Vector3DArray              coordinates;
	Mode                             mode;
	bool                             allowDupEntries;
	std::size_t                      numProcessed;
	std::size_t                      numRejected;
	std::size_t                      numDeleted;
	std::size_t                      numInserted;
};


Pharm::PSDScreeningDBCreator::PSDScreeningDBCreator():
	impl(new Implementation())
{}

Pharm::PSDScreeningDBCreator::PSDScreeningDBCreator(const std::string& name, Mode mode, bool allow_dup_entries):
	impl(new Implementation())
{
    impl->open(name, mode, allow_dup_entries);
}
	
Pharm::PSDScreeningDBCreator::~PSDScreeningDBCreator() {}

void Pharm::PSDScreeningDBCreator::open(const std::string& name, Mode mode, bool allow_dup_entries)
{
	impl->open(name, mode, allow_dup_entries);
}

void Pharm::PSDScreeningDBCreator::close()
{
	impl->close();
}

Pharm::PSDScreeningDBCreator::Mode Pharm::PSDScreeningDBCreator::getMode() const
{
	return impl->getMode();
}

bool Pharm::PSDScreeningDBCreator::allowDuplicateEntries() const
{
	return impl->allowDuplicateEntries();
}

bool Pharm::PSDScreeningDBCreator::process(const Chem::MolecularGraph& molgraph)
{
	return impl->process(molgraph);
}

const std::string& Pharm::PSDScreeningDBCreator::getDatabaseName() const
{
	return impl->getDatabaseName();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumProcessed() const
{
	return impl->getNumProcessed();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumRejected() const
{
	return impl->getNumRejected();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumDeleted() const
{
	return impl->getNumDeleted();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumInserted() const
{
	return impl->getNumInserted();
}


// Implementation

Pharm::PSDScreeningDBCreator::Implementation::Implementation():
	pharmWriter(controlParams),	molWriter(controlParams), pharmGenerator(true), mode(CREATE),
	allowDupEntries(true), numProcessed(0), numRejected(0), numDeleted(0), numInserted(0)
{
	initControlParams();
}

void Pharm::PSDScreeningDBCreator::Implementation::open(const std::string& name, Mode mode, bool allow_dup_entries)
{
	openDBConnection(name, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	this->mode = mode;
	allowDupEntries = allow_dup_entries;

	setupTables();
	loadMolHashToIDMap();
}

void Pharm::PSDScreeningDBCreator::Implementation::close()
{
	closeDBConnection();
}

const std::string& Pharm::PSDScreeningDBCreator::Implementation::getDatabaseName() const
{
	return getDBName();
}

void Pharm::PSDScreeningDBCreator::Implementation::closeDBConnection()
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

	PSDImplementationBase::closeDBConnection();

	numProcessed = 0;
	numRejected = 0;
	numDeleted = 0;
	numInserted = 0;
}

Pharm::PSDScreeningDBCreator::Mode Pharm::PSDScreeningDBCreator::Implementation::getMode() const
{
	return mode;
}

bool Pharm::PSDScreeningDBCreator::Implementation::allowDuplicateEntries() const
{
	return allowDupEntries;
}

std::size_t Pharm::PSDScreeningDBCreator::Implementation::getNumProcessed() const
{
	return numProcessed;
}

std::size_t Pharm::PSDScreeningDBCreator::Implementation::getNumRejected() const
{
	return numRejected;
}

std::size_t Pharm::PSDScreeningDBCreator::Implementation::getNumDeleted() const
{
	return numDeleted;
}

std::size_t Pharm::PSDScreeningDBCreator::Implementation::getNumInserted() const
{
	return numInserted;
}

bool Pharm::PSDScreeningDBCreator::Implementation::process(const Chem::MolecularGraph& molgraph)
{
	if (!getDBConnection())
		throw Base::IOError("PSDScreeningDBCreator: no open database connection");

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

	TransactionRollback trb(getDBConnection().get());
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

void Pharm::PSDScreeningDBCreator::Implementation::initControlParams()
{
	Pharm::setStrictErrorCheckingParameter(controlParams, true);
	Chem::setStrictErrorCheckingParameter(controlParams, true);

	Pharm::setCDFWriteSinglePrecisionFloatsParameter(controlParams, true);
	Chem::setCDFWriteSinglePrecisionFloatsParameter(controlParams, true);
}

void Pharm::PSDScreeningDBCreator::Implementation::setupTables()
{
	execStatements(SQLITE_OPEN_PRAGMAS);

	beginTransaction();
	TransactionRollback trb(getDBConnection().get());

	if (mode == CREATE)
		execStatements(DROP_TABLES_SQL);

	execStatements(CREATE_TABLES_SQL);

	commitTransaction();
	trb.disable();

	// The prepared 'BEGIN TRANSACTION' seems not to be reusable anymore if tables are dropped/created
	// Maybe this is a bug?
	beginTransStmt.reset(); 
}

void Pharm::PSDScreeningDBCreator::Implementation::loadMolHashToIDMap()
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
		throwSQLiteIOError("PSDScreeningDBCreator: error while loading existing molecule IDs and hashes");
}

std::size_t Pharm::PSDScreeningDBCreator::Implementation::deleteEntries(Base::uint64 mol_hash)
{
	std::size_t num_del = 0;
	std::pair<MolHashToIDMap::iterator, MolHashToIDMap::iterator> mols_with_hash = molHashToIDMap.equal_range(mol_hash);

	for (MolHashToIDMap::iterator it = mols_with_hash.first; it != mols_with_hash.second; ++it, num_del++) {
		Base::uint64 mol_id = it->second;
		
		deleteRowsWithMolID(delMolWithMolIDStmt, DELETE_MOL_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delPharmsWithMolIDStmt, DELETE_PHARMS_WITH_MOL_ID_SQL, mol_id);
		deleteRowsWithMolID(delFeatureCountsWithMolIDStmt, DELETE_FTR_COUNTS_WITH_MOL_ID_SQL, mol_id);
	}

	return num_del;
}

Base::int64 Pharm::PSDScreeningDBCreator::Implementation::insertMolecule(const Chem::MolecularGraph& molgraph, Base::uint64 mol_hash)
{
	molWriter.writeMolGraph(molgraph, byteBuffer);

	setupStatement(insMoleculeStmt, INSERT_MOL_DATA_SQL, true);

	if (sqlite3_bind_int64(insMoleculeStmt.get(), 1, mol_hash) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding molecule hashcode to prepared statement");

	if (sqlite3_bind_blob(insMoleculeStmt.get(), 2, byteBuffer.getData(), boost::numeric_cast<int>(byteBuffer.getSize()),
						  SQLITE_TRANSIENT) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding molecule data BLOB to prepared statement");

	evalStatement(insMoleculeStmt);

	return sqlite3_last_insert_rowid(getDBConnection().get());
}

void Pharm::PSDScreeningDBCreator::Implementation::genAndInsertPharmData(const Chem::MolecularGraph& molgraph, Base::int64 mol_id)
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
		getConformationData(molgraph, i, coordinates);

		pharmGenerator.setAtom3DCoordinatesFunction(Chem::AtomArray3DCoordinatesFunctor(coordinates, molgraph));
		genAndInsertPharmData(molgraph, mol_id, i);
	}
}

void Pharm::PSDScreeningDBCreator::Implementation::genAndInsertPharmData(const Chem::MolecularGraph& molgraph, Base::int64 mol_id, std::size_t conf_idx)
{
	pharmacophore.clear();
	pharmGenerator.generate(molgraph, pharmacophore);

	insertPharmacophore(mol_id, conf_idx);
	insertFtrCounts(mol_id, conf_idx);
}

void Pharm::PSDScreeningDBCreator::Implementation::insertPharmacophore(Base::int64 mol_id, std::size_t conf_idx)
{
	pharmWriter.writePharmacophore(pharmacophore, byteBuffer);

	setupStatement(insPharmStmt, INSERT_PHARM_DATA_SQL, true);

	if (sqlite3_bind_int64(insPharmStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding pharmacophore molecule ID to prepared statement");

	if (sqlite3_bind_int(insPharmStmt.get(), 2, boost::numeric_cast<int>(conf_idx)) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding pharmacophore conf. index to prepared statement");

	if (sqlite3_bind_blob(insPharmStmt.get(), 3, byteBuffer.getData(), boost::numeric_cast<int>(byteBuffer.getSize()),
						  SQLITE_TRANSIENT) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding pharmacophore data BLOB to prepared statement");

	evalStatement(insPharmStmt);
}

void Pharm::PSDScreeningDBCreator::Implementation::insertFtrCounts(Base::int64 mol_id, std::size_t conf_idx)
{
	featureCounts.clear();
	buildFeatureTypeHistogram(pharmacophore, featureCounts);

	for (FeatureTypeHistogram::ConstEntryIterator it = featureCounts.getEntriesBegin(), end = featureCounts.getEntriesEnd(); it != end; ++it)
		insertFtrCount(mol_id, conf_idx, it->first, it->second);
}

void Pharm::PSDScreeningDBCreator::Implementation::insertFtrCount(Base::int64 mol_id, std::size_t conf_idx, unsigned int ftr_type, std::size_t ftr_count)
{
	setupStatement(insFtrCountStmt, INSERT_FTR_COUNT_SQL, true);

	if (sqlite3_bind_int64(insFtrCountStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding feature count molecule ID to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 2, boost::numeric_cast<int>(conf_idx)) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding feature count conf. index to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 3, ftr_type) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding feature type to prepared statement");

	if (sqlite3_bind_int(insFtrCountStmt.get(), 4, boost::numeric_cast<int>(ftr_count)) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding feature count to prepared statement");

	evalStatement(insFtrCountStmt);
}

void Pharm::PSDScreeningDBCreator::Implementation::deleteRowsWithMolID(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, Base::int64 mol_id) const
{
	setupStatement(stmt_ptr, sql_stmt, true);

	if (sqlite3_bind_int64(stmt_ptr.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("PSDScreeningDBCreator: error while binding molecule ID to prepared statement");

	evalStatement(stmt_ptr);
}

void Pharm::PSDScreeningDBCreator::Implementation::beginTransaction()
{
	setupStatement(beginTransStmt, BEGIN_TRANSACTION_SQL, false);
	evalStatement(beginTransStmt);
}

void Pharm::PSDScreeningDBCreator::Implementation::commitTransaction()
{
	setupStatement(commitTransStmt, COMMIT_TRANSACTION_SQL, false);
	evalStatement(commitTransStmt);
}
