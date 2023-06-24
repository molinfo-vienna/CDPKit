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
 * \brief Definition of the class CDPL::Pharm::ScreeningDBCreator.
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
         * \brief A class for the creation of optimized pharmacophore screening databases.
         */
        class CDPL_PHARM_API ScreeningDBCreator
        {

          public:
            typedef std::shared_ptr<ScreeningDBCreator> SharedPointer;

            typedef std::function<bool(double)> ProgressCallbackFunction;

            enum Mode
            {

                CREATE,
                UPDATE,
                APPEND
            };

            /**
             * \brief Virtual destructor.
             */
            virtual ~ScreeningDBCreator() {}

            virtual void open(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true) = 0;

            virtual void close() = 0;

            virtual Mode getMode() const = 0;

            virtual bool allowDuplicateEntries() const = 0;

            virtual bool process(const Chem::MolecularGraph& molgraph) = 0;

            virtual bool merge(const ScreeningDBAccessor& db_acc, const ProgressCallbackFunction& func) = 0;

            virtual const std::string& getDatabaseName() const = 0;

            virtual std::size_t getNumProcessed() const = 0;

            virtual std::size_t getNumRejected() const = 0;

            virtual std::size_t getNumDeleted() const = 0;

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
