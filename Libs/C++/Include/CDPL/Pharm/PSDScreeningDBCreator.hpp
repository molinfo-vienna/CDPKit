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
 * \brief Definition of the class CDPL::Pharm::PSDScreeningDBCreator.
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
         * \brief A class for the creation of optimized pharmacophore screening databases.
         */
        class CDPL_PHARM_API PSDScreeningDBCreator : public ScreeningDBCreator
        {

          public:
            typedef std::shared_ptr<PSDScreeningDBCreator> SharedPointer;

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

            /**
             * \brief Destructor.
             */
            ~PSDScreeningDBCreator();

            void open(const std::string& name, Mode mode = CREATE, bool allow_dup_entries = true);

            void close();

            Mode getMode() const;

            bool allowDuplicateEntries() const;

            bool process(const Chem::MolecularGraph& molgraph);

            bool merge(const ScreeningDBAccessor& db_acc, const ProgressCallbackFunction& func);

            const std::string& getDatabaseName() const;

            std::size_t getNumProcessed() const;

            std::size_t getNumRejected() const;

            std::size_t getNumDeleted() const;

            std::size_t getNumInserted() const;

          private:
            typedef std::auto_ptr<PSDScreeningDBCreatorImpl> ImplementationPointer;

            PSDScreeningDBCreator(const PSDScreeningDBCreator&);

            PSDScreeningDBCreator& operator=(const PSDScreeningDBCreator&);
        
            ImplementationPointer impl;
        };
    }
}

#endif // CDPL_PHARM_PSDSCREENINGDBCREATOR_HPP
