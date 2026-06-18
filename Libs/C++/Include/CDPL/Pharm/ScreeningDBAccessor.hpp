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
 * \brief Definition of class CDPL::Pharm::ScreeningDBAccessor.
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
         * \brief Abstract base class for accessors that read the data stored in pharmacophore screening databases.
         */
        class CDPL_PHARM_API ScreeningDBAccessor
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ScreeningDBAccessor instances.
             */
            typedef std::shared_ptr<ScreeningDBAccessor> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~ScreeningDBAccessor() {}

            /**
             * \brief Opens the screening database identified by \a name.
             * \param name The database name (path, URI, etc., interpreted by the concrete subclass).
             */
            virtual void open(const std::string& name) = 0;

            /**
             * \brief Closes the currently open database.
             */
            virtual void close() = 0;

            /**
             * \brief Returns the name of the currently open database.
             * \return A \c const reference to the database name.
             */
            virtual const std::string& getDatabaseName() const = 0;

            /**
             * \brief Returns the total number of molecules stored in the database.
             * \return The molecule count.
             */
            virtual std::size_t getNumMolecules() const = 0;

            /**
             * \brief Returns the total number of pharmacophores stored in the database (one per molecule conformer).
             * \return The pharmacophore count.
             */
            virtual std::size_t getNumPharmacophores() const = 0;

            /**
             * \brief Returns the number of pharmacophores stored for the molecule at index \a mol_idx.
             * \param mol_idx The zero-based molecule index.
             * \return The pharmacophore count for the molecule.
             */
            virtual std::size_t getNumPharmacophores(std::size_t mol_idx) const = 0;

            /**
             * \brief Reads the molecule at index \a mol_idx into \a mol.
             * \param mol_idx The zero-based molecule index.
             * \param mol The output molecule.
             * \param overwrite If \c true, \a mol is cleared before reading. If \c false, the atoms/bonds are appended.
             */
            virtual void getMolecule(std::size_t mol_idx, Chem::Molecule& mol, bool overwrite = true) const = 0;

            /**
             * \brief Reads the pharmacophore at index \a pharm_idx into \a pharm.
             * \param pharm_idx The zero-based pharmacophore index (across all molecules).
             * \param pharm The output pharmacophore.
             * \param overwrite If \c true, \a pharm is cleared before reading. If \c false, the features are appended.
             */
            virtual void getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm, bool overwrite = true) const = 0;

            /**
             * \brief Reads the pharmacophore corresponding to conformer \a mol_conf_idx of molecule \a mol_idx into \a pharm.
             * \param mol_idx The zero-based molecule index.
             * \param mol_conf_idx The zero-based conformer index within the molecule.
             * \param pharm The output pharmacophore.
             * \param overwrite If \c true, \a pharm is cleared before reading. If \c false, the features are appended.
             */
            virtual void getPharmacophore(std::size_t mol_idx, std::size_t mol_conf_idx, Pharmacophore& pharm, bool overwrite = true) const = 0;

            /**
             * \brief Returns the molecule index of the pharmacophore at index \a pharm_idx.
             * \param pharm_idx The zero-based pharmacophore index.
             * \return The zero-based molecule index.
             */
            virtual std::size_t getMoleculeIndex(std::size_t pharm_idx) const = 0;

            /**
             * \brief Returns the conformer index within the parent molecule of the pharmacophore at index \a pharm_idx.
             * \param pharm_idx The zero-based pharmacophore index.
             * \return The zero-based conformer index.
             */
            virtual std::size_t getConformationIndex(std::size_t pharm_idx) const = 0;

            /**
             * \brief Returns the cached per Pharm::FeatureType frequency histogram of the pharmacophore at index \a pharm_idx.
             * \param pharm_idx The zero-based pharmacophore index.
             * \return A \c const reference to the feature-type histogram.
             */
            virtual const FeatureTypeHistogram& getFeatureCounts(std::size_t pharm_idx) const = 0;

            /**
             * \brief Returns the cached per Pharm::FeatureType frequency histogram of conformer \a mol_conf_idx of molecule \a mol_idx.
             * \param mol_idx The zero-based molecule index.
             * \param mol_conf_idx The zero-based conformer index within the molecule.
             * \return A \c const reference to the feature-type histogram.
             */
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
