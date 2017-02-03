/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDScreeningDBCreatorImpl.hpp 
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


#ifndef CDPL_PHARM_PSDSCREENINGDBCREATORIMPL_HPP
#define CDPL_PHARM_PSDSCREENINGDBCREATORIMPL_HPP

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "CDPL/Pharm/SQLiteDataIOBase.hpp"
#include "CDPL/Pharm/ScreeningDBCreator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Pharm/CDFDataWriter.hpp"
#include "CDPL/Chem/CDFDataWriter.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/IntTypes.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
    }

    namespace Pharm
    {
	
		class ScreeningDBAccessor;

		class PSDScreeningDBCreatorImpl : private SQLiteDataIOBase
		{

		public:
			PSDScreeningDBCreatorImpl();

            void open(const std::string& name, ScreeningDBCreator::Mode mode = ScreeningDBCreator::CREATE, bool allow_dup_entries = true);

			void close();

			const std::string& getDatabaseName() const;

			ScreeningDBCreator::Mode getMode() const;

			bool allowDuplicateEntries() const;

			bool process(const Chem::MolecularGraph& molgraph);

			bool merge(const ScreeningDBAccessor& db_acc, const ScreeningDBCreator::ProgressCallbackFunction& func);

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

			void genFtrCounts();
			void insertFtrCounts(Base::int64 mol_id, std::size_t conf_idx);
			void insertFtrCount(Base::int64 mol_id, std::size_t conf_idx, unsigned int ftr_type, std::size_t ftr_count);

			void deleteRowsWithMolID(SQLite3StmtPointer& stmt_ptr, const std::string& sql_stmt, Base::int64 mol_id) const;

			void beginTransaction();
			void commitTransaction();

			typedef boost::unordered_multimap<Base::uint64, Base::int64> MolHashToIDMap;
			typedef boost::unordered_set<Base::uint64> MolHashSet;

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
			ScreeningDBCreator::Mode         mode;
			bool                             allowDupEntries;
			std::size_t                      numProcessed;
			std::size_t                      numRejected;
			std::size_t                      numDeleted;
			std::size_t                      numInserted;
		};
    }
}

#endif // CDPL_PHARM_PSDSCREENINGDBCREATORIMPL_HPP
