/* 
 * PDBData.hpp 
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

/**
 * \file
 * \brief Definition of class CDPL::Biomol::PDBData.
 */

#ifndef CDPL_BIOMOL_PDBDATA_HPP
#define CDPL_BIOMOL_PDBDATA_HPP

#include <cstddef>
#include <string>
#include <map>
#include <memory>

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief A data structure for the storage of imported PDB data records (see [\ref CTFILE]).
         */
        class CDPL_BIOMOL_API PDBData
        {

          public:
            typedef std::shared_ptr<PDBData> SharedPointer;

            enum RecordType
            {

                HEADER,
                OBSLTE,
                TITLE,
                SPLIT,
                CAVEAT,
                COMPND,
                SOURCE,
                KEYWDS,
                EXPDTA,
                AUTHOR,
                REVDAT,
                SPRSDE,
                JRNL,
                REMARK,
                DBREF,
                DBREF1,
                DBREF2,
                SEQADV,
                SEQRES,
                MODRES,
                HET,
                FORMUL,
                HETNAM,
                HETSYN,
                HELIX,
                SHEET,
                TURN,
                SSBOND,
                LINK,
                CISPEP,
                SITE,
                CRYST1,
                MTRIX1,
                MTRIX2,
                MTRIX3,
                ORIGX1,
                ORIGX2,
                ORIGX3,
                SCALE1,
                SCALE2,
                SCALE3,
                STRUCTURE_ID,
                DEPOSITION_DATE,
                RESOLUTION
            };

          private:
            typedef std::map<RecordType, std::string> TypeToDataMap;

          public:
            typedef typename TypeToDataMap::value_type Record;

            typedef typename TypeToDataMap::const_iterator ConstRecordIterator;

            typedef typename TypeToDataMap::iterator RecordIterator;

            PDBData():
                data() {}

            PDBData(const PDBData& other):
                data(other.data) {}

            void clear();

            std::size_t getNumRecords() const;

            bool isEmpty() const;

            bool containsRecord(const RecordType& type) const;

            RecordIterator getRecord(const RecordType& type);

            ConstRecordIterator getRecord(const RecordType& type) const;

            std::string& getData(const RecordType& type);

            const std::string& getData(const RecordType& type) const;

            void removeRecord(const RecordIterator& it);

            bool removeRecord(const RecordType& type);

            RecordIterator setRecord(const Record& rec);

            RecordIterator setRecord(const RecordType& type, const std::string& data);

            ConstRecordIterator getRecordsBegin() const;

            RecordIterator getRecordsBegin();

            ConstRecordIterator getRecordsEnd() const;

            RecordIterator getRecordsEnd();

            ConstRecordIterator begin() const;

            RecordIterator begin();

            ConstRecordIterator end() const;

            RecordIterator end();

          private:
            TypeToDataMap data;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_PDBDATA_HPP
