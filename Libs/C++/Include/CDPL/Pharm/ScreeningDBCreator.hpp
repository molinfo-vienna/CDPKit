/* 
 * ScreeningDBCreator.hpp 
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
 * \brief Definition of class CDPL::Pharm::ScreeningDBCreator.
 */

#ifndef CDPL_PHARM_SCREENINGDBCREATOR_HPP
#define CDPL_PHARM_SCREENINGDBCREATOR_HPP

#include <string>
#include <cstddef>
#include <memory>
#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Pharm
    {

        class ScreeningDBAccessor;

        /**
         * \brief Abstract base class for creators that build optimized pharmacophore screening databases.
         */
        class CDPL_PHARM_API ScreeningDBCreator
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ScreeningDBCreator instances. */
            typedef std::shared_ptr<ScreeningDBCreator> SharedPointer;

            /** \brief Type of the progress-reporting callback (argument: fraction in [0, 1], return: \c true to continue, \c false to abort). */
            typedef std::function<bool(double)> ProgressCallbackFunction;

            /**
             * \brief Specifies how an existing database file is treated by open().
             */
            enum Mode
            {

                /** \brief Create a new database (replacing any existing file). */
                CREATE,
                /** \brief Update an existing database in place. */
                UPDATE,
                /** \brief Append to an existing database. */
                APPEND
            };

            /**
             * \brief Virtual destructor.
             */
            virtual ~ScreeningDBCreator() {}

            /**
             * \brief Opens the database identified by \a name in the specified \a mode.
             * \param name The database name (path, URI, etc., interpreted by the concrete subclass).
             * \param mode The open mode (see Mode).
             * \param allow_dup_entries If \c true, duplicate molecule entries are allowed; if \c false, duplicates are rejected.
             */
            virtual void open(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true) = 0;

            /**
             * \brief Closes the currently open database.
             */
            virtual void close() = 0;

            /**
             * \brief Returns the mode in which the currently open database was opened.
             * \return The open mode.
             */
            virtual Mode getMode() const = 0;

            /**
             * \brief Tells whether duplicate molecule entries are allowed.
             * \return \c true if duplicates are allowed, and \c false otherwise.
             */
            virtual bool allowDuplicateEntries() const = 0;

            /**
             * \brief Processes \a molgraph and adds it (or its derived pharmacophores) to the database.
             * \param molgraph The molecular graph to process.
             * \return \c true if at least one entry was inserted, and \c false otherwise (e.g. when duplicates are rejected).
             */
            virtual bool process(const Chem::MolecularGraph& molgraph) = 0;

            /**
             * \brief Merges the contents of \a db_acc into the currently open database.
             * \param db_acc The source database accessor.
             * \param func An optional progress-reporting callback (called repeatedly with a fraction in [0, 1]).
             * \return \c true if the merge completed successfully, and \c false if it was aborted by the callback.
             */
            virtual bool merge(const ScreeningDBAccessor& db_acc, const ProgressCallbackFunction& func) = 0;

            /**
             * \brief Returns the name of the currently open database.
             * \return A \c const reference to the database name.
             */
            virtual const std::string& getDatabaseName() const = 0;

            /**
             * \brief Returns the number of molecules processed since the database was opened.
             * \return The processed-molecule count.
             */
            virtual std::size_t getNumProcessed() const = 0;

            /**
             * \brief Returns the number of molecules that were rejected (e.g. as duplicates) since the database was opened.
             * \return The rejected-molecule count.
             */
            virtual std::size_t getNumRejected() const = 0;

            /**
             * \brief Returns the number of entries that were deleted since the database was opened.
             * \return The deleted-entry count.
             */
            virtual std::size_t getNumDeleted() const = 0;

            /**
             * \brief Returns the number of entries that were inserted since the database was opened.
             * \return The inserted-entry count.
             */
            virtual std::size_t getNumInserted() const = 0;

          protected:
            ScreeningDBCreator& operator=(const ScreeningDBCreator&)
            {
                return *this;
            }
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_SCREENINGDBCREATOR_HPP
