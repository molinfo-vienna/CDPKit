/* 
 * PSDPharmacophoreReader.hpp 
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
 * \brief Definition of class CDPL::Pharm::PSDPharmacophoreReader.
 */

#ifndef CDPL_PHARM_PSDPHARMACOPHOREREADER_HPP
#define CDPL_PHARM_PSDPHARMACOPHOREREADER_HPP

#include <string>
#include <iosfwd>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"
#include "CDPL/Base/DataReader.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Pharmacophore;

        /**
         * \brief A reader for pharmacophore data in the PSD-format of the <em>CDPL</em>.
         */
        class CDPL_PHARM_API PSDPharmacophoreReader : public Base::DataReader<Pharmacophore>
        {

          public:
            /**
             * \brief Constructs a \c %PSDPharmacophoreReader instance that will read the pharmacophore data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            PSDPharmacophoreReader(std::istream& is);

            /**
             * \brief Constructs a \c %PSDPharmacophoreReader instance that will read the pharmacophore data from the input
             *        file \a file_name.
             * \param file_name The input file to read from.
             */
            PSDPharmacophoreReader(const std::string& file_name);

            /**
             * \brief Destructor.
             */
            ~PSDPharmacophoreReader();

            /**
             * \brief Reads the next pharmacophore into \a pharm.
             * \param pharm The output pharmacophore.
             * \param overwrite If \c true, the output pharmacophore is cleared before the database pharmacophore is copied into it.
             * \return A reference to itself.
             */
            PSDPharmacophoreReader& read(Pharmacophore& pharm, bool overwrite = true);

            /**
             * \brief Reads the pharmacophore at record index \a idx into \a pharm.
             * \param idx The zero-based record index.
             * \param pharm The output pharmacophore.
             * \param overwrite If \c true, the output pharmacophore is cleared before the database pharmacophore is copied into it.
             * \return A reference to itself.
             */
            PSDPharmacophoreReader& read(std::size_t idx, Pharmacophore& pharm, bool overwrite = true);

            /**
             * \brief Skips the next pharmacophore record (advances the current record index).
             * \return A reference to itself.
             */
            PSDPharmacophoreReader& skip();

            /**
             * \brief Tells whether the reader has more records to read.
             * \return \c true if at least one more record is available, and \c false otherwise.
             */
            bool hasMoreData();

            /**
             * \brief Returns the current record index.
             * \return The zero-based record index of the next record to read.
             */
            std::size_t getRecordIndex() const;

            /**
             * \brief Sets the current record index.
             * \param idx The new zero-based record index.
             */
            void        setRecordIndex(std::size_t idx);

            /**
             * \brief Returns the total number of records.
             * \return The record count.
             */
            std::size_t getNumRecords();

            /**
             * \brief Tells whether the reader is in a good (readable) state.
             * \return A non-\c nullptr pointer if the reader is in a good state, and \c nullptr otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether the reader is in a bad (non-readable) state.
             * \return \c true if the reader is in a bad state, and \c false otherwise.
             */
            bool operator!() const;

          private:
            PSDScreeningDBAccessor accessor;
            std::size_t            recordIndex;
            std::size_t            numRecords;
            bool                   state;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDPHARMACOPHOREREADER_HPP
