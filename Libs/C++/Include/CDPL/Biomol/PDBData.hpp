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
         * \brief Data structure for the storage of preprocessed <em>Brookhaven Protein Data Bank (PDB)</em> data.
         * \see [\ref PDB]
         */
        class CDPL_BIOMOL_API PDBData
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PDBData instances.
             */
            typedef std::shared_ptr<PDBData> SharedPointer;

            /**
             * \brief Specifies the type of a stored \e PDB data record.
             */
            enum RecordType
            {

                /**
                 * \brief \c HEADER record (structure classification, deposition date, \e PDB ID).
                 */
                HEADER,
    
                /**
                 * \brief \c OBSLTE record (PDB IDs that have replaced this entry).
                 */
                OBSLTE,
    
                /**
                 * \brief \c TITLE record (title of the entry).
                 */
                TITLE,
    
                /**
                 * \brief \c SPLIT record (list of entries that together form the complete structure).
                 */
                SPLIT,
    
                /**
                 * \brief \c CAVEAT record (warns of errors and unresolved issues of the entry).
                 */
                CAVEAT,
    
                /**
                 * \brief \c COMPND record (description of the macromolecular contents).
                 */
                COMPND,
    
                /**
                 * \brief \c SOURCE record (specifies the biological and/or chemical source of each biological molecule).
                 */
                SOURCE,
    
                /**
                 * \brief \c KEYWDS record (a set of terms relevant to the entry).
                 */
                KEYWDS,
    
                /**
                 * \brief \c EXPDTA record (information about the experiment).
                 */
                EXPDTA,
    
                /**
                 * \brief \c AUTHOR record (contains the names of the people responsible for the contents of the entry).
                 */
                AUTHOR,
    
                /**
                 * \brief \c REVDAT record (revision history of the entry).
                 */
                REVDAT,
    
                /**
                 * \brief \c SPRSDE record (PDB IDs that this entry supersedes).
                 */
                SPRSDE,
    
                /**
                 * \brief \c JRNL record (literature citation associated with the entry).
                 */
                JRNL,
    
                /**
                 * \brief \c REMARK record (experimental details, annotations, comments, and information not included in other records).
                 */
                REMARK,
    
                /**
                 * \brief \c DBREF record (cross-reference links between \e PDB sequences and a corresponding database sequence).
                 */
                DBREF,
    
                /**
                 * \brief \c DBREF1 record (first part of a two-line database cross-reference).
                 */
                DBREF1,
    
                /**
                 * \brief \c DBREF2 record (second part of a two-line database cross-reference).
                 */
                DBREF2,
    
                /**
                 * \brief \c SEQADV record (differences between sequence information in the \c SEQRES record and the sequence database entry given in \c DBREF).
                 */
                SEQADV,
    
                /**
                 * \brief \c SEQRES record (residue sequence of biopolymer chains).
                 */
                SEQRES,
    
                /**
                 * \brief \c MODRES record (descriptions of modifications to protein and nucleic acid residues).
                 */
                MODRES,
    
                /**
                 * \brief \c HET record (describes non-standard residues for which coordinates are supplied).
                 */
                HET,
    
                /**
                 * \brief \c FORMUL record (chemical formula of non-standard residues).
                 */
                FORMUL,
    
                /**
                 * \brief \c HETNAM record (chemical names of non-standard residues).
                 */
                HETNAM,
    
                /**
                 * \brief \c HETSYN record (synonyms for non-standard residues).
                 */
                HETSYN,
    
                /**
                 * \brief \c HELIX record (helix secondary structure annotations).
                 */
                HELIX,
    
                /**
                 * \brief \c SHEET record (sheet secondary structure annotations).
                 */
                SHEET,
    
                /**
                 * \brief \c TURN record (locations of short loop turns that connect standard secondary structure segments).
                 */
                TURN,
    
                /**
                 * \brief \c SSBOND record (identifies disulfide bonds in protein and polypeptide structures).
                 */
                SSBOND,
    
                /**
                 * \brief \c LINK record (bonds between residues that are not implied by the primary structure).
                 */
                LINK,
    
                /**
                 * \brief \c CISPEP record (specifies prolines and other peptides found to be in the cis conformation).
                 */
                CISPEP,
    
                /**
                 * \brief \c SITE record (specifies residues of an active or binding site).
                 */
                SITE,
    
                /**
                 * \brief \c CRYST1 record (unit cell parameters, space group, and Z value).
                 */
                CRYST1,
    
                /**
                 * \brief \c MTRIX1 record (first row of a non-crystallographic symmetry transformation matrix).
                 */
                MTRIX1,
    
                /**
                 * \brief \c MTRIX2 record (second row of a non-crystallographic symmetry transformation matrix).
                 */
                MTRIX2,
    
                /**
                 * \brief \c MTRIX3 record (third row of a non-crystallographic symmetry transformation matrix).
                 */
                MTRIX3,
    
                /**
                 * \brief \c ORIGX1 record (first row of the orthogonal to submitted coordinates transformation).
                 */
                ORIGX1,
    
                /**
                 * \brief \c ORIGX2 record (second row of the orthogonal to submitted coordinates transformation).
                 */
                ORIGX2,
    
                /**
                 * \brief \c ORIGX3 record (third row of the orthogonal to submitted coordinates transformation).
                 */
                ORIGX3,
    
                /**
                 * \brief \c SCALE1 record (first row of the orthogonal to fractional coordinates transformation).
                 */
                SCALE1,
    
                /**
                 * \brief \c SCALE2 record (second row of the orthogonal to fractional coordinates transformation).
                 */
                SCALE2,
    
                /**
                 * \brief \c SCALE3 record (third row of the orthogonal to fractional coordinates transformation).
                 */
                SCALE3,
    
                /**
                 * \brief The 4 character \e PDB identifier extracted from the \c HEADER record.
                 */
                STRUCTURE_ID,
    
                /**
                 * \brief The deposition date extracted from the \c HEADER record.
                 */
                DEPOSITION_DATE,
    
                /**
                 * \brief The experimental resolution extracted from \c REMARK records.
                 */
                RESOLUTION
            };

          private:
            typedef std::map<RecordType, std::string> TypeToDataMap;

          public:
            /**
             * \brief The type of the stored record type and data pairs.
             */
            typedef typename TypeToDataMap::value_type Record;

            /**
             * \brief A constant iterator over the stored records.
             */
            typedef typename TypeToDataMap::const_iterator ConstRecordIterator;

            /**
             * \brief A mutable iterator over the stored records.
             */
            typedef typename TypeToDataMap::iterator RecordIterator;

            /**
             * \brief Constructs an empty \c %PDBData instance.
             */
            PDBData():
                data() {}

            /**
             * \brief Constructs a copy of the \c %PDBData instance \a other.
             * \param other The \c %PDBData instance to copy.
             */
            PDBData(const PDBData& other):
                data(other.data) {}

            /**
             * \brief Removes all stored records.
             */
            void clear();

            /**
             * \brief Returns the number of stored records.
             * \return The number of records.
             */
            std::size_t getNumRecords() const;

            /**
             * \brief Tells whether no records are stored.
             * \return \c true if no records are stored, and \c false otherwise.
             */
            bool isEmpty() const;

            /**
             * \brief Tells whether a record of the given type is stored.
             * \param type The queried record type.
             * \return \c true if a record of the given type has been found, and \c false otherwise.
             */
            bool containsRecord(const RecordType& type) const;

            /**
             * \brief Returns an iterator to the record of the given type.
             * \param type The record type to look up.
             * \return An iterator pointing to the matching record, or to getRecordsEnd() if no
             *         matching record exists.
             */
            RecordIterator getRecord(const RecordType& type);

            /**
             * \brief Returns a constant iterator to the record of the given type.
             * \param type The record type to look up.
             * \return A constant iterator pointing to the matching record, or to getRecordsEnd()
             *         if no matching record exists.
             */
            ConstRecordIterator getRecord(const RecordType& type) const;

            /**
             * \brief Returns the data string associated with the given record type.
             * \param type The record type whose data is requested.
             * \return A reference to the data string.
             * \throw Base::ItemNotFound if no record of the given type is stored.
             */
            std::string& getData(const RecordType& type);

            /**
             * \brief Returns the data string associated with the given record type.
             * \param type The record type whose data is requested.
             * \return A \c const reference to the data string.
             * \throw Base::ItemNotFound if no record of the given type is stored.
             */
            const std::string& getData(const RecordType& type) const;

            /**
             * \brief Removes the record referenced by the given iterator.
             * \param it Iterator pointing to the record to remove.
             */
            void removeRecord(const RecordIterator& it);

            /**
             * \brief Removes the record of the given type.
             * \param type The type of the record to remove.
             * \return \c true if the record was removed, and \c false if no matching record existed.
             */
            bool removeRecord(const RecordType& type);

            /**
             * \brief Stores the given record (any pre-existing record of the same type is replaced).
             * \param rec The record to store.
             * \return An iterator pointing to the stored record.
             */
            RecordIterator setRecord(const Record& rec);

            /**
             * \brief Stores a record built from \a type and \a data (any pre-existing record of the same type is replaced).
             * \param type The record type.
             * \param data The record data string.
             * \return An iterator pointing to the stored record.
             */
            RecordIterator setRecord(const RecordType& type, const std::string& data);

            /**
             * \brief Returns a constant iterator pointing to the first stored record.
             * \return A constant iterator pointing to the first record.
             */
            ConstRecordIterator getRecordsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the first stored record.
             * \return A mutable iterator pointing to the first record.
             */
            RecordIterator getRecordsBegin();

            /**
             * \brief Returns a constant iterator pointing one past the last stored record.
             * \return A constant iterator pointing one past the last record.
             */
            ConstRecordIterator getRecordsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing one past the last stored record.
             * \return A mutable iterator pointing one past the last record.
             */
            RecordIterator getRecordsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first stored record (range-based for support).
             * \return A constant iterator pointing to the first record.
             */
            ConstRecordIterator begin() const;

            /**
             * \brief Returns a mutable iterator pointing to the first stored record (range-based for support).
             * \return A mutable iterator pointing to the first record.
             */
            RecordIterator begin();

            /**
             * \brief Returns a constant iterator pointing one past the last stored record (range-based for support).
             * \return A constant iterator pointing one past the last record.
             */
            ConstRecordIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing one past the last stored record (range-based for support).
             * \return A mutable iterator pointing one past the last record.
             */
            RecordIterator end();

          private:
            TypeToDataMap data;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_PDBDATA_HPP
