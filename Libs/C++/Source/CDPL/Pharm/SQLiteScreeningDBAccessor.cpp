/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLiteScreeningDBAccessor.cpp 
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

#include <vector>
#include <utility>

#include <boost/unordered_map.hpp>

#include "CDPL/Pharm/SQLiteScreeningDBAccessor.hpp"
#include "CDPL/Pharm/CDFDataReader.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Chem/CDFDataReader.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/IntTypes.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "SQLScreeningDBMetaData.hpp"
#include "SQLiteIOImplementationBase.hpp"


using namespace CDPL;


namespace
{

	const std::string MOL_DATA_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::MOL_DATA_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1;";

	const std::string PHARM_DATA_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::PHARM_DATA_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1 AND " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " = ?2;";

	const std::string MOL_ID_FROM_MOL_TABLE_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + ";";

	const std::string MOL_ID_CONF_IDX_FROM_PHARM_TABLE_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::PHARM_TABLE_NAME + ";";

	const std::string FTR_COUNT_TABLE_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::MOL_CONF_IDX_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::FTR_TYPE_COLUMN_NAME + ", " +
		Pharm::SQLScreeningDB::FTR_COUNT_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::FTR_COUNT_TABLE_NAME + ";";
}


class Pharm::SQLiteScreeningDBAccessor::Implementation : private Pharm::SQLiteIOImplementationBase
{

public:
	Implementation();

	void open(const std::string& name);

	void close();

	const std::string& getDatabaseName() const;

	std::size_t getNumMolecules();

	std::size_t getNumPharmacophores();

	void getMolecule(std::size_t mol_idx, Chem::Molecule& mol);

	void getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm);

	void getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm);

	std::size_t getMoleculeIndex(std::size_t pharm_idx);

	std::size_t getConformationIndex(std::size_t pharm_idx);

	const FeatureTypeHistogram& getFeatureCounts(std::size_t pharm_idx);

private:
	void initControlParams();

	void closeDBConnection();

	void loadPharmacophore(Base::int64 mol_id, int conf_idx, Pharmacophore& pharm);

	void initMolIdxIDMappings();
	void initPharmIdxMolIDConfIdxMappings();
	void loadFeatureCounts();
	
	typedef std::vector<FeatureTypeHistogram> FeatureCountsArray;
	typedef std::pair<Base::int64, std::size_t> MolIDConfIdxPair;
	typedef std::vector<Base::int64> MolIDArray;
	typedef std::vector<MolIDConfIdxPair> MolIDConfIdxPairArray;
	typedef boost::unordered_map<Base::int64, std::size_t> MolIDToIdxMap;
	typedef boost::unordered_map<MolIDConfIdxPair, std::size_t> MolIDConfIdxToPharmIdxMap;

	SQLite3StmtPointer               selMolDataStmt;
	SQLite3StmtPointer               selPharmDataStmt;
	SQLite3StmtPointer               selMolIDStmt;
	SQLite3StmtPointer               selMolIDConfIdxStmt;
	SQLite3StmtPointer               selFtrCountsStmt;
    FeatureCountsArray               featureCounts;
	MolIDArray                       molIdxToIDMap;
	MolIDToIdxMap                    molIDToIdxMap;
	MolIDConfIdxPairArray            pharmIdxToMolIDConfIdxMap;
    MolIDConfIdxToPharmIdxMap        molIDConfIdxToPharmIdxMap;
	Internal::ByteBuffer             byteBuffer;
	CDFDataReader                    pharmReader;
	Chem::CDFDataReader              molReader;
	Base::ControlParameterList       controlParams;
};


Pharm::SQLiteScreeningDBAccessor::SQLiteScreeningDBAccessor():
	impl(new Implementation())
{}

Pharm::SQLiteScreeningDBAccessor::SQLiteScreeningDBAccessor(const std::string& name):
	impl(new Implementation())
{
	impl->open(name);
}
	
Pharm::SQLiteScreeningDBAccessor::~SQLiteScreeningDBAccessor() {}

void Pharm::SQLiteScreeningDBAccessor::open(const std::string& name)
{
	impl->open(name);
}

void Pharm::SQLiteScreeningDBAccessor::close()
{
	impl->close();
}

const std::string& Pharm::SQLiteScreeningDBAccessor::getDatabaseName() const
{
	return impl->getDatabaseName();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getNumMolecules() const
{
	return impl->getNumMolecules();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getNumPharmacophores() const
{
	return impl->getNumPharmacophores();
}

void Pharm::SQLiteScreeningDBAccessor::getMolecule(std::size_t mol_idx, Chem::Molecule& mol) const
{
	impl->getMolecule(mol_idx, mol);
}

void Pharm::SQLiteScreeningDBAccessor::getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm) const
{
	impl->getPharmacophore(pharm_idx, pharm);
}

void Pharm::SQLiteScreeningDBAccessor::getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm) const
{
	impl->getPharmacophore(mol_idx, conf_idx, pharm);
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getMoleculeIndex(std::size_t pharm_idx) const
{
	return impl->getMoleculeIndex(pharm_idx);
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getConformationIndex(std::size_t pharm_idx) const
{
	return impl->getConformationIndex(pharm_idx);
}

const Pharm::FeatureTypeHistogram& Pharm::SQLiteScreeningDBAccessor::getFeatureCounts(std::size_t pharm_idx) const
{
	return impl->getFeatureCounts(pharm_idx);
}


// Implementation

Pharm::SQLiteScreeningDBAccessor::Implementation::Implementation():
	pharmReader(controlParams), molReader(controlParams)
{
	initControlParams();
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::open(const std::string& name)
{
	openDBConnection(name, SQLITE_OPEN_READONLY);
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::close()
{
	closeDBConnection();
}

const std::string& Pharm::SQLiteScreeningDBAccessor::Implementation::getDatabaseName() const
{
	return getDBName();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getNumMolecules()
{
	if (!getDBConnection())
		return 0;

	initMolIdxIDMappings();

	return molIdxToIDMap.size();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getNumPharmacophores()
{
	if (!getDBConnection())
		return 0;

	initPharmIdxMolIDConfIdxMappings();

	return pharmIdxToMolIDConfIdxMap.size();
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::getMolecule(std::size_t mol_idx, Chem::Molecule& mol)
{
	if (!getDBConnection())
		throw Base::IOError("SQLiteScreeningDBAccessor: no open database connection");

	initMolIdxIDMappings();

	if (mol_idx >= molIdxToIDMap.size())
		throw Base::IndexError("SQLiteScreeningDBAccessor: molecule index out of bounds");

	setupStatement(selMolDataStmt, MOL_DATA_QUERY_SQL, true);

	if (sqlite3_bind_int64(selMolDataStmt.get(), 1, molIdxToIDMap[mol_idx]) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while binding molecule id to prepared statement");

	int res = sqlite3_step(selMolDataStmt.get());

	if (res != SQLITE_ROW && res != SQLITE_DONE)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while loading requested molecule");

	if (res != SQLITE_ROW)
		throw Base::IOError("SQLiteScreeningDBAccessor: requested molecule not found");

	const void* blob = sqlite3_column_blob(selMolDataStmt.get(), 0);
	std::size_t num_bytes = sqlite3_column_bytes(selMolDataStmt.get(), 0);
	
	byteBuffer.setIOPointer(0);
	byteBuffer.putBytes(reinterpret_cast<const char*>(blob), num_bytes);

	molReader.readMolecule(mol, byteBuffer);
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm)
{
	if (!getDBConnection())
		throw Base::IOError("SQLiteScreeningDBAccessor: no open database connection");

	initPharmIdxMolIDConfIdxMappings();

	if (pharm_idx >= pharmIdxToMolIDConfIdxMap.size())
		throw Base::IndexError("SQLiteScreeningDBAccessor: pharmacophore index out of bounds");

	loadPharmacophore(pharmIdxToMolIDConfIdxMap[pharm_idx].first, pharmIdxToMolIDConfIdxMap[pharm_idx].second, pharm);
} 

void Pharm::SQLiteScreeningDBAccessor::Implementation::getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm)
{
	if (!getDBConnection())
		throw Base::IOError("SQLiteScreeningDBAccessor: no open database connection");

	initMolIdxIDMappings();

	if (mol_idx >= molIdxToIDMap.size())
		throw Base::IndexError("SQLiteScreeningDBAccessor: pharmacophore molecule index out of bounds");

	loadPharmacophore(molIdxToIDMap[mol_idx], conf_idx, pharm);
} 

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getMoleculeIndex(std::size_t pharm_idx)
{
	if (!getDBConnection())
		throw Base::IOError("SQLiteScreeningDBAccessor: no open database connection");

	initPharmIdxMolIDConfIdxMappings();
	initMolIdxIDMappings();

	if (pharm_idx >= pharmIdxToMolIDConfIdxMap.size())
		throw Base::IndexError("SQLiteScreeningDBAccessor: pharmacophore index out of bounds");

	MolIDToIdxMap::const_iterator it = molIDToIdxMap.find(pharmIdxToMolIDConfIdxMap[pharm_idx].first);

	if (it == molIDToIdxMap.end())
		throw Base::IOError("SQLiteScreeningDBAccessor: requested molecule index for pharmacophore not found");

	return it->second;
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getConformationIndex(std::size_t pharm_idx)
{
	if (!getDBConnection())
		throw Base::IOError("SQLiteScreeningDBAccessor: no open database connection");

	initPharmIdxMolIDConfIdxMappings();

	if (pharm_idx >= pharmIdxToMolIDConfIdxMap.size())
		throw Base::IndexError("SQLiteScreeningDBAccessor: pharmacophore index out of bounds");

	return pharmIdxToMolIDConfIdxMap[pharm_idx].second;
}

const Pharm::FeatureTypeHistogram& Pharm::SQLiteScreeningDBAccessor::Implementation::getFeatureCounts(std::size_t pharm_idx)
{
	if (!getDBConnection())
		throw Base::IOError("SQLiteScreeningDBAccessor: no open database connection");

	loadFeatureCounts();

	if (pharm_idx >= featureCounts.size())
		throw Base::IndexError("SQLiteScreeningDBAccessor: pharmacophore index out of bounds");

	return featureCounts[pharm_idx];
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::loadPharmacophore(Base::int64 mol_id, int conf_idx, Pharmacophore& pharm)
{
	setupStatement(selPharmDataStmt, PHARM_DATA_QUERY_SQL, true);

	if (sqlite3_bind_int64(selPharmDataStmt.get(), 1, mol_id) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while binding pharmacophore molecule id to prepared statement");

	if (sqlite3_bind_int(selPharmDataStmt.get(), 2, conf_idx) != SQLITE_OK)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while binding pharmacophore molecule conformation index to prepared statement");

	int res = sqlite3_step(selPharmDataStmt.get());

	if (res != SQLITE_ROW && res != SQLITE_DONE)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while loading requested pharmacophore");

	if (res != SQLITE_ROW)
		throw Base::IOError("SQLiteScreeningDBAccessor: requested pharmacophore not found");

	const void* blob = sqlite3_column_blob(selPharmDataStmt.get(), 0);
	std::size_t num_bytes = sqlite3_column_bytes(selPharmDataStmt.get(), 0);
	
	byteBuffer.setIOPointer(0);
	byteBuffer.putBytes(reinterpret_cast<const char*>(blob), num_bytes);

	pharmReader.readPharmacophore(pharm, byteBuffer);
} 

void Pharm::SQLiteScreeningDBAccessor::Implementation::initControlParams()
{
	Pharm::setStrictErrorCheckingParameter(controlParams, true);
	Chem::setStrictErrorCheckingParameter(controlParams, true);
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::closeDBConnection()
{
	selMolDataStmt.reset();
	selPharmDataStmt.reset();
	selMolIDStmt.reset();
	selMolIDConfIdxStmt.reset();
	selFtrCountsStmt.reset();

	SQLiteIOImplementationBase::closeDBConnection();

	featureCounts.clear();
	molIdxToIDMap.clear();
	molIDToIdxMap.clear();
	pharmIdxToMolIDConfIdxMap.clear();
    molIDConfIdxToPharmIdxMap.clear();
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::initMolIdxIDMappings()
{
	if (!molIdxToIDMap.empty())
		return;

	setupStatement(selMolIDStmt, MOL_ID_FROM_MOL_TABLE_QUERY_SQL, false);

	int res;

	for (std::size_t i = 0; (res = sqlite3_step(selMolIDStmt.get())) == SQLITE_ROW; i++) {
		sqlite3_int64 mol_id = sqlite3_column_int64(selMolIDStmt.get(), 0);

		molIdxToIDMap.push_back(mol_id);
		molIDToIdxMap.insert(MolIDToIdxMap::value_type(mol_id, i));
	}

	if (res != SQLITE_DONE)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while loading molecule IDs");
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::initPharmIdxMolIDConfIdxMappings()
{
	if (!pharmIdxToMolIDConfIdxMap.empty())
		return;

	setupStatement(selMolIDConfIdxStmt, MOL_ID_CONF_IDX_FROM_PHARM_TABLE_QUERY_SQL, false);

	int res;

	for (std::size_t i = 0; (res = sqlite3_step(selMolIDConfIdxStmt.get())) == SQLITE_ROW; i++) {
		sqlite3_int64 mol_id = sqlite3_column_int64(selMolIDConfIdxStmt.get(), 0);
		int conf_idx = sqlite3_column_int(selMolIDConfIdxStmt.get(), 1);

		MolIDConfIdxPair mol_id_conf_idx(mol_id, conf_idx);

		pharmIdxToMolIDConfIdxMap.push_back(mol_id_conf_idx);
		molIDConfIdxToPharmIdxMap.insert(MolIDConfIdxToPharmIdxMap::value_type(mol_id_conf_idx, i));
	}

	if (res != SQLITE_DONE)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while loading pharmacophore molecule IDs and conformer indices");
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::loadFeatureCounts()
{
	if (!featureCounts.empty())
		return;

	initPharmIdxMolIDConfIdxMappings();
	setupStatement(selFtrCountsStmt, FTR_COUNT_TABLE_QUERY_SQL, false);

	featureCounts.resize(pharmIdxToMolIDConfIdxMap.size());
	int res;

	while ((res = sqlite3_step(selFtrCountsStmt.get())) == SQLITE_ROW) {
		sqlite3_int64 mol_id = sqlite3_column_int64(selFtrCountsStmt.get(), 0);
		int conf_idx = sqlite3_column_int(selFtrCountsStmt.get(), 1);
		int ftr_type = sqlite3_column_int(selFtrCountsStmt.get(), 2);
		int ftr_count = sqlite3_column_int(selFtrCountsStmt.get(), 3);

		MolIDConfIdxPair mol_id_conf_idx(mol_id, conf_idx);
		MolIDConfIdxToPharmIdxMap::const_iterator it = molIDConfIdxToPharmIdxMap.find(mol_id_conf_idx);

		if (it == molIDConfIdxToPharmIdxMap.end())
			throw Base::IOError("SQLiteScreeningDBAccessor: error while loading feature counts: pharmacophore index for molecule-ID/conf. index pair not found");

		std::size_t pharm_idx = it->second;

		if (pharm_idx >= featureCounts.size())
			throw Base::IndexError("SQLiteScreeningDBAccessor: error while loading feature counts: pharmacophore index out of bounds");

		featureCounts[pharm_idx].insertEntry(FeatureTypeHistogram::Entry(ftr_type, ftr_count));
	}

	if (res != SQLITE_DONE)
		throwSQLiteIOError("SQLiteScreeningDBAccessor: error while loading feature counts");
}
