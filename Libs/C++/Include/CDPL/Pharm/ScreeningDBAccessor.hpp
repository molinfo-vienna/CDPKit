/* 
 * ScreeningDBAccessor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::ScreeningDBAccessor.
 */

#ifndef CDPL_PHARM_SCREENINGDBACCESSOR_HPP
#define CDPL_PHARM_SCREENINGDBACCESSOR_HPP

#include <string>
#include <cstddef>
#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }

    namespace Pharm
    {

        class Pharmacophore;
        class FeatureTypeHistogram;

        /**
         * \brief A class for accessing the data stored in pharmacophore screening databases.
         */
        class CDPL_PHARM_API ScreeningDBAccessor
        {

          public:
            typedef std::shared_ptr<ScreeningDBAccessor> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~ScreeningDBAccessor() {}

            virtual void open(const std::string& name) = 0;

            virtual void close() = 0;

            virtual const std::string& getDatabaseName() const = 0;

            virtual std::size_t getNumMolecules() const = 0;

            virtual std::size_t getNumPharmacophores() const = 0;

            virtual std::size_t getNumPharmacophores(std::size_t mol_idx) const = 0;

            virtual void getMolecule(std::size_t mol_idx, Chem::Molecule& mol, bool overwrite = true) const = 0;

            virtual void getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm, bool overwrite = true) const = 0;

            virtual void getPharmacophore(std::size_t mol_idx, std::size_t mol_conf_idx, Pharmacophore& pharm, bool overwrite = true) const = 0;

            virtual std::size_t getMoleculeIndex(std::size_t pharm_idx) const = 0;

            virtual std::size_t getConformationIndex(std::size_t pharm_idx) const = 0;

            virtual const FeatureTypeHistogram& getFeatureCounts(std::size_t pharm_idx) const = 0;

            virtual const FeatureTypeHistogram& getFeatureCounts(std::size_t mol_idx, std::size_t mol_conf_idx) const = 0;

          protected:
            ScreeningDBAccessor& operator=(const ScreeningDBAccessor&)
            {
                return *this;
            }
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_SCREENINGDBACCESSOR_HPP
