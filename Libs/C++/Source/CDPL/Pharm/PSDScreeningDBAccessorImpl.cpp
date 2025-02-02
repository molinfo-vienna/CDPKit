/* 
 * PSDScreeningDBAccessorImpl.cpp 
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

#include "PSDScreeningDBAccessorImpl.hpp"
#include "PSDTableInfo.hpp"


using namespace CDPL;


namespace
{

    const std::string MOL_DATA_QUERY_SQL = "SELECT " +
        Pharm::PSDTableInfo::MOL_DATA_COLUMN_NAME + " FROM " +
        Pharm::PSDTableInfo::MOL_TABLE_NAME + " WHERE " +
        Pharm::PSDTableInfo::MOL_ID_COLUMN_NAME + " = ?1;";

    const std::string PHARM_DATA_QUERY_SQL = "SELECT " +
        Pharm::PSDTableInfo::PHARM_DATA_COLUMN_NAME + " FROM " +
        Pharm::PSDTableInfo::PHARM_TABLE_NAME + " WHERE " +
        Pharm::PSDTableInfo::MOL_ID_COLUMN_NAME + " = ?1 AND " +
        Pharm::PSDTableInfo::MOL_CONF_IDX_COLUMN_NAME + " = ?2;";

    const std::string MOL_ID_FROM_MOL_TABLE_QUERY_SQL = "SELECT " +
        Pharm::PSDTableInfo::MOL_ID_COLUMN_NAME + " FROM " +
        Pharm::PSDTableInfo::MOL_TABLE_NAME + ";";

    const std::string MOL_ID_CONF_IDX_FROM_PHARM_TABLE_QUERY_SQL = "SELECT " +
        Pharm::PSDTableInfo::MOL_ID_COLUMN_NAME + ", " +
        Pharm::PSDTableInfo::MOL_CONF_IDX_COLUMN_NAME + " FROM " +
        Pharm::PSDTableInfo::PHARM_TABLE_NAME + ";";

    const std::string FTR_COUNT_TABLE_QUERY_SQL = "SELECT " +
        Pharm::PSDTableInfo::MOL_ID_COLUMN_NAME + ", " +
        Pharm::PSDTableInfo::MOL_CONF_IDX_COLUMN_NAME + ", " +
        Pharm::PSDTableInfo::FTR_TYPE_COLUMN_NAME + ", " +
        Pharm::PSDTableInfo::FTR_COUNT_COLUMN_NAME + " FROM " +
        Pharm::PSDTableInfo::FTR_COUNT_TABLE_NAME + ";";
}


Pharm::PSDScreeningDBAccessorImpl::PSDScreeningDBAccessorImpl()
{}

void Pharm::PSDScreeningDBAccessorImpl::open(const std::string& name)
{
    openDBConnection(name, SQLITE_OPEN_READONLY);
}

void Pharm::PSDScreeningDBAccessorImpl::close()
{
    closeDBConnection();
}

const std::string& Pharm::PSDScreeningDBAccessorImpl::getDatabaseName() const
{
    return getDBName();
}

std::size_t Pharm::PSDScreeningDBAccessorImpl::getNumMolecules()
{
    if (!getDBConnection())
        return 0;

    initMolIdxIDMappings();

    return molIdxToIDMap.size();
}

std::size_t Pharm::PSDScreeningDBAccessorImpl::getNumPharmacophores()
{
    if (!getDBConnection())
        return 0;

    initPharmIdxMolIDConfIdxMappings();

    return pharmIdxToMolIDConfIdxMap.size();
}

std::size_t Pharm::PSDScreeningDBAccessorImpl::getNumPharmacophores(std::size_t mol_idx)
{
    if (!getDBConnection())
        return 0;

    initMolIdxIDMappings();
    initPharmIdxMolIDConfIdxMappings();

    if (mol_idx >= molIdxToIDMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: molecule index out of bounds");

    return molIDConfCountMap[molIdxToIDMap[mol_idx]];
}

void Pharm::PSDScreeningDBAccessorImpl::getMolecule(std::size_t mol_idx, Chem::Molecule& mol)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    initMolIdxIDMappings();

    if (mol_idx >= molIdxToIDMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: molecule index out of bounds");

    setupStatement(selMolDataStmt, MOL_DATA_QUERY_SQL, true);

    if (sqlite3_bind_int64(selMolDataStmt.get(), 1, molIdxToIDMap[mol_idx]) != SQLITE_OK)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while binding molecule id to prepared statement");

    int res = sqlite3_step(selMolDataStmt.get());

    if (res != SQLITE_ROW && res != SQLITE_DONE)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while loading requested molecule");

    if (res != SQLITE_ROW)
        throw Base::IOError("PSDScreeningDBAccessorImpl: requested molecule not found");

    const void* blob = sqlite3_column_blob(selMolDataStmt.get(), 0);
    std::size_t num_bytes = sqlite3_column_bytes(selMolDataStmt.get(), 0);

    byteBuffer.resize(0);
    byteBuffer.setIOPointer(0);
    byteBuffer.putBytes(reinterpret_cast<const char*>(blob), num_bytes);

    molReader.readMolecule(byteBuffer, mol);
}

void Pharm::PSDScreeningDBAccessorImpl::getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    initPharmIdxMolIDConfIdxMappings();

    if (pharm_idx >= pharmIdxToMolIDConfIdxMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: pharmacophore index out of bounds");

    loadPharmacophore(pharmIdxToMolIDConfIdxMap[pharm_idx].first, pharmIdxToMolIDConfIdxMap[pharm_idx].second, pharm);
} 

void Pharm::PSDScreeningDBAccessorImpl::getPharmacophore(std::size_t mol_idx, std::size_t mol_conf_idx, Pharmacophore& pharm)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    initMolIdxIDMappings();

    if (mol_idx >= molIdxToIDMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: pharmacophore molecule index out of bounds");

    loadPharmacophore(molIdxToIDMap[mol_idx], mol_conf_idx, pharm);
} 

std::size_t Pharm::PSDScreeningDBAccessorImpl::getMoleculeIndex(std::size_t pharm_idx)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    initPharmIdxMolIDConfIdxMappings();
    initMolIdxIDMappings();

    if (pharm_idx >= pharmIdxToMolIDConfIdxMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: pharmacophore index out of bounds");

    MolIDToUIntMap::const_iterator it = molIDToIdxMap.find(pharmIdxToMolIDConfIdxMap[pharm_idx].first);

    if (it == molIDToIdxMap.end())
        throw Base::IOError("PSDScreeningDBAccessorImpl: requested molecule index for pharmacophore not found");

    return it->second;
}

std::size_t Pharm::PSDScreeningDBAccessorImpl::getConformationIndex(std::size_t pharm_idx)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    initPharmIdxMolIDConfIdxMappings();

    if (pharm_idx >= pharmIdxToMolIDConfIdxMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: pharmacophore index out of bounds");

    return pharmIdxToMolIDConfIdxMap[pharm_idx].second;
}

const Pharm::FeatureTypeHistogram& Pharm::PSDScreeningDBAccessorImpl::getFeatureCounts(std::size_t pharm_idx)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    loadFeatureCounts();

    if (pharm_idx >= featureCounts.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: pharmacophore index out of bounds");

    return featureCounts[pharm_idx];
}

const Pharm::FeatureTypeHistogram& Pharm::PSDScreeningDBAccessorImpl::getFeatureCounts(std::size_t mol_idx, std::size_t mol_conf_idx)
{
    if (!getDBConnection())
        throw Base::IOError("PSDScreeningDBAccessorImpl: no open database connection");

    loadFeatureCounts();
    initMolIdxIDMappings();

    if (mol_idx >= molIdxToIDMap.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: molecule index out of bounds");

    MolIDConfIdxPair mol_id_conf_idx(molIdxToIDMap[mol_idx], mol_conf_idx);
    MolIDConfIdxToPharmIdxMap::const_iterator it = molIDConfIdxToPharmIdxMap.find(mol_id_conf_idx);

    if (it == molIDConfIdxToPharmIdxMap.end())
        throw Base::IOError("PSDScreeningDBAccessorImpl: pharmacophore index for molecule index/conf. index pair not found");

    std::size_t pharm_idx = it->second;

    if (pharm_idx >= featureCounts.size())
        throw Base::IndexError("PSDScreeningDBAccessorImpl: pharmacophore index out of bounds");

    return featureCounts[pharm_idx];
}

void Pharm::PSDScreeningDBAccessorImpl::loadPharmacophore(std::int64_t mol_id, int mol_conf_idx, Pharmacophore& pharm)
{
    setupStatement(selPharmDataStmt, PHARM_DATA_QUERY_SQL, true);

    if (sqlite3_bind_int64(selPharmDataStmt.get(), 1, mol_id) != SQLITE_OK)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while binding pharmacophore molecule id to prepared statement");

    if (sqlite3_bind_int(selPharmDataStmt.get(), 2, mol_conf_idx) != SQLITE_OK)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while binding pharmacophore molecule conformation index to prepared statement");

    int res = sqlite3_step(selPharmDataStmt.get());

    if (res != SQLITE_ROW && res != SQLITE_DONE)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while loading requested pharmacophore");

    if (res != SQLITE_ROW)
        throw Base::IOError("PSDScreeningDBAccessorImpl: requested pharmacophore not found");

    const void* blob = sqlite3_column_blob(selPharmDataStmt.get(), 0);
    std::size_t num_bytes = sqlite3_column_bytes(selPharmDataStmt.get(), 0);

    byteBuffer.resize(0);
    byteBuffer.setIOPointer(0);
    byteBuffer.putBytes(reinterpret_cast<const char*>(blob), num_bytes);

    pharmReader.readPharmacophore(byteBuffer, pharm);
} 

void Pharm::PSDScreeningDBAccessorImpl::closeDBConnection()
{
    selMolDataStmt.reset();
    selPharmDataStmt.reset();
    selMolIDStmt.reset();
    selMolIDConfIdxStmt.reset();
    selFtrCountsStmt.reset();

    SQLiteDataIOBase::closeDBConnection();

    featureCounts.clear();
    molIdxToIDMap.clear();
    molIDToIdxMap.clear();
    molIDConfCountMap.clear();
    pharmIdxToMolIDConfIdxMap.clear();
    molIDConfIdxToPharmIdxMap.clear();
}

void Pharm::PSDScreeningDBAccessorImpl::initMolIdxIDMappings()
{
    if (!molIdxToIDMap.empty())
        return;

    setupStatement(selMolIDStmt, MOL_ID_FROM_MOL_TABLE_QUERY_SQL, false);

    int res;

    for (std::size_t i = 0; (res = sqlite3_step(selMolIDStmt.get())) == SQLITE_ROW; i++) {
        sqlite3_int64 mol_id = sqlite3_column_int64(selMolIDStmt.get(), 0);

        molIdxToIDMap.push_back(mol_id);
        molIDToIdxMap.insert(MolIDToUIntMap::value_type(mol_id, i));
    }

    if (res != SQLITE_DONE)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while loading molecule IDs");
}

void Pharm::PSDScreeningDBAccessorImpl::initPharmIdxMolIDConfIdxMappings()
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
        molIDConfCountMap[mol_id]++;
    }

    if (res != SQLITE_DONE)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while loading pharmacophore molecule IDs and conformer indices");
}

void Pharm::PSDScreeningDBAccessorImpl::loadFeatureCounts()
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
            throw Base::IOError("PSDScreeningDBAccessorImpl: error while loading feature counts: pharmacophore index for molecule-ID/conf. index pair not found");

        std::size_t pharm_idx = it->second;

        if (pharm_idx >= featureCounts.size())
            throw Base::IndexError("PSDScreeningDBAccessorImpl: error while loading feature counts: pharmacophore index out of bounds");

        featureCounts[pharm_idx].insertEntry(FeatureTypeHistogram::Entry(ftr_type, ftr_count));
    }

    if (res != SQLITE_DONE)
        throwSQLiteIOError("PSDScreeningDBAccessorImpl: error while loading feature counts");
}
