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
 * \brief Definition of class CDPL::Pharm::PSDScreeningDBAccessor.
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
         * \brief Pharm::ScreeningDBAccessor implementation that reads pharmacophore screening databases stored
         *        in the built-in optimized PSD format.
         */
        class CDPL_PHARM_API PSDScreeningDBAccessor : public ScreeningDBAccessor
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PSDScreeningDBAccessor instances. */
            typedef std::shared_ptr<PSDScreeningDBAccessor> SharedPointer;

            /**
             * \brief Constructs a \c %PSDScreeningDBAccessor instance without an associated database.
             */
            PSDScreeningDBAccessor();

            /**
             * \brief Constructs a \c %PSDScreeningDBAccessor instance that will read data from the
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

            /**
             * \brief Opens the database-file specified by \a name.
             * \param name The name of the database-file.
             */
            void open(const std::string& name);

            /**
             * \brief Closes the currently associated database-file (if any).
             */
            void close();

            /**
             * \brief Returns the name of the currently associated database-file.
             * \return A \c const reference to the database-file name (or an empty string if no database is open).
             */
            const std::string& getDatabaseName() const;

            /**
             * \brief Returns the total number of molecules stored in the database.
             * \return The molecule count.
             */
            std::size_t getNumMolecules() const;

            /**
             * \brief Returns the total number of pharmacophores stored in the database.
             * \return The pharmacophore count (the sum of getNumPharmacophores(mol_idx) over all molecules).
             */
            std::size_t getNumPharmacophores() const;

            /**
             * \brief Returns the number of pharmacophores (conformers) stored for the molecule at index \a mol_idx.
             * \param mol_idx The zero-based molecule index.
             * \return The per-molecule pharmacophore count.
             */
            std::size_t getNumPharmacophores(std::size_t mol_idx) const;

            /**
             * \brief Retrieves the molecule at index \a mol_idx and stores it in \a mol.
             * \param mol_idx The zero-based molecule index.
             * \param mol The output molecule.
             * \param overwrite If \c true, the output molecule is cleared before the database molecule is copied into it.
             */
            void getMolecule(std::size_t mol_idx, Chem::Molecule& mol, bool overwrite = true) const;

            /**
             * \brief Retrieves the pharmacophore at index \a pharm_idx and stores it in \a pharm.
             * \param pharm_idx The zero-based pharmacophore index.
             * \param pharm The output pharmacophore.
             * \param overwrite If \c true, the output pharmacophore is cleared before the database pharmacophore is copied into it.
             */
            void getPharmacophore(std::size_t pharm_idx, Pharmacophore& pharm, bool overwrite = true) const;

            /**
             * \brief Retrieves the pharmacophore for the given (molecule, conformer) pair and stores it in \a pharm.
             * \param mol_idx The zero-based molecule index.
             * \param mol_conf_idx The zero-based conformer index within the molecule.
             * \param pharm The output pharmacophore.
             * \param overwrite If \c true, the output pharmacophore is cleared before the database pharmacophore is copied into it.
             */
            void getPharmacophore(std::size_t mol_idx, std::size_t mol_conf_idx, Pharmacophore& pharm, bool overwrite = true) const;

            /**
             * \brief Returns the molecule index of the pharmacophore at index \a pharm_idx.
             * \param pharm_idx The zero-based pharmacophore index.
             * \return The owning molecule index.
             */
            std::size_t getMoleculeIndex(std::size_t pharm_idx) const;

            /**
             * \brief Returns the conformer index (within its owning molecule) of the pharmacophore at index \a pharm_idx.
             * \param pharm_idx The zero-based pharmacophore index.
             * \return The conformer index.
             */
            std::size_t getConformationIndex(std::size_t pharm_idx) const;

            /**
             * \brief Returns the per-feature-type counts of the pharmacophore at index \a pharm_idx.
             * \param pharm_idx The zero-based pharmacophore index.
             * \return A \c const reference to the feature-type histogram.
             */
            const FeatureTypeHistogram& getFeatureCounts(std::size_t pharm_idx) const;

            /**
             * \brief Returns the per-feature-type counts of the pharmacophore for the given (molecule, conformer) pair.
             * \param mol_idx The zero-based molecule index.
             * \param mol_conf_idx The zero-based conformer index within the molecule.
             * \return A \c const reference to the feature-type histogram.
             */
            const FeatureTypeHistogram& getFeatureCounts(std::size_t mol_idx, std::size_t mol_conf_idx) const;

          private:
            typedef std::unique_ptr<PSDScreeningDBAccessorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDSCREENINGDBACCESSOR_HPP
