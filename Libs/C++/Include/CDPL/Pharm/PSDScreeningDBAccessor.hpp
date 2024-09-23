/* 
 * PSDScreeningDBAccessor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PSDScreeningDBAccessor.
 */

#ifndef CDPL_PHARM_PSDSCREENINGDBACCESSOR_HPP
#define CDPL_PHARM_PSDSCREENINGDBACCESSOR_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class PSDScreeningDBAccessorImpl;

        /**
         * \brief A class for accessing pharmacophore screening databases in the built-in optimized format.
         */
        class CDPL_PHARM_API PSDScreeningDBAccessor : public ScreeningDBAccessor
        {

          public:
            typedef std::shared_ptr<PSDScreeningDBAccessor> SharedPointer;

            PSDScreeningDBAccessor();

            /**
             * \brief Constructs a \c %ScreeningDBAccessor instance that will read data from the 
             *        database-file specified by \a name.
             * \param name The name of the database-file.
             */
            PSDScreeningDBAccessor(const std::string& name);

            PSDScreeningDBAccessor(const PSDScreeningDBAccessor&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~PSDScreeningDBAccessor();

            PSDScreeningDBAccessor& operator=(const PSDScreeningDBAccessor&) = delete;

            void open(const std::string& name);

            void close();

            const std::string& getDatabaseName() const;

            std::size_t getNumMolecules() const;

            std::size_t getNumPharmacophores() const;

            std::size_t getNumPharmacophores(std::size_t mol_idx) const;

            void getMolecule(std::size_t mol_idx, Chem::Molecule& mol, bool overwrite = true) const;

            void getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm, bool overwrite = true) const;

            void getPharmacophore(std::size_t mol_idx, std::size_t mol_conf_idx, Pharmacophore& pharm, bool overwrite = true) const;

            std::size_t getMoleculeIndex(std::size_t pharm_idx) const;

            std::size_t getConformationIndex(std::size_t pharm_idx) const;

            const FeatureTypeHistogram& getFeatureCounts(std::size_t pharm_idx) const;

            const FeatureTypeHistogram& getFeatureCounts(std::size_t mol_idx, std::size_t mol_conf_idx) const;

          private:
            typedef std::unique_ptr<PSDScreeningDBAccessorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDSCREENINGDBACCESSOR_HPP
