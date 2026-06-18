/* 
 * PSDScreeningDBCreator.hpp 
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
 * \brief Definition of class CDPL::Pharm::PSDScreeningDBCreator.
 */

#ifndef CDPL_PHARM_PSDSCREENINGDBCREATOR_HPP
#define CDPL_PHARM_PSDSCREENINGDBCREATOR_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/ScreeningDBCreator.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class PSDScreeningDBCreatorImpl;

        /**
         * \brief Pharm::ScreeningDBCreator implementation that builds optimized pharmacophore screening databases
         *        in the built-in PSD format.
         */
        class CDPL_PHARM_API PSDScreeningDBCreator : public ScreeningDBCreator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PSDScreeningDBCreator instances.
             */
            typedef std::shared_ptr<PSDScreeningDBCreator> SharedPointer;

            /**
             * \brief Constructs a \c %PSDScreeningDBCreator instance without an associated database.
             */
            PSDScreeningDBCreator();

            /**
             * \brief Constructs a \c %PSDScreeningDBCreator instance that will write data to the
             *        database-file specified by \a name in the given insert mode.
             * \param name The name of the database-file.
             * \param mode Specifies whether to (re)create the database or to update/append to existing records.
             * \param allow_dup_entries Specifies whether input molecules that are duplicates of already
             *                          stored molecules should be discarded.
             */
            PSDScreeningDBCreator(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true);

            PSDScreeningDBCreator(const PSDScreeningDBCreator&) = delete;

            /**
             * \brief Destructor.
             */
            ~PSDScreeningDBCreator();

            PSDScreeningDBCreator& operator=(const PSDScreeningDBCreator&) = delete;

            /**
             * \brief Opens the database-file specified by \a name in the given insert mode.
             * \param name The name of the database-file.
             * \param mode Specifies whether to (re)create the database or to update/append to existing records.
             * \param allow_dup_entries Specifies whether input molecules that are duplicates of already
             *                          stored molecules should be discarded.
             */
            void open(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true);

            /**
             * \brief Closes the currently associated database-file (if any).
             */
            void close();

            /**
             * \brief Returns the currently configured insert mode.
             * \return The Pharm::ScreeningDBCreator::Mode value.
             */
            Mode getMode() const;

            /**
             * \brief Tells whether duplicate database entries are currently allowed.
             * \return \c true if duplicates are allowed, and \c false otherwise.
             */
            bool allowDuplicateEntries() const;

            /**
             * \brief Processes \a molgraph and inserts the resulting molecule (with derived conformer pharmacophores) into the database.
             * \param molgraph The molecular graph to process.
             * \return \c true if the molecule was inserted, and \c false if it was rejected (e.g. as a duplicate).
             */
            bool process(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Merges all molecule/pharmacophore records of \a db_acc into the currently open database.
             * \param db_acc The source database accessor.
             * \param func A progress-reporting callback invoked during the merge.
             * \return \c true if the merge completed successfully, and \c false if it was aborted (e.g. by the callback).
             */
            bool merge(const ScreeningDBAccessor& db_acc, const ProgressCallbackFunction& func);

            /**
             * \brief Returns the name of the currently associated database-file.
             * \return A \c const reference to the database-file name (or an empty string if no database is open).
             */
            const std::string& getDatabaseName() const;

            /**
             * \brief Returns the total number of input molecules processed since the database was opened.
             * \return The processed-molecule count.
             */
            std::size_t getNumProcessed() const;

            /**
             * \brief Returns the number of processed molecules that were rejected (e.g. as duplicates).
             * \return The rejected-molecule count.
             */
            std::size_t getNumRejected() const;

            /**
             * \brief Returns the number of pre-existing database entries that were deleted (under Mode::UPDATE/CREATE).
             * \return The deleted-entry count.
             */
            std::size_t getNumDeleted() const;

            /**
             * \brief Returns the number of new database entries that were inserted.
             * \return The inserted-entry count.
             */
            std::size_t getNumInserted() const;

          private:
            typedef std::unique_ptr<PSDScreeningDBCreatorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDSCREENINGDBCREATOR_HPP
