/* 
 * GRAILDescriptorCalculator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::GRAILDescriptorCalculator.
 */

#ifndef CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
#define CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP

#include <cstddef>
#include <memory>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }
    
    namespace GRAIL
    {

        class GRAILDescriptorCalculatorImpl;
        
        /**
         * \brief Calculation of GRAIL descriptors for protein-ligand complexes.
         *
         * The descriptor is a vector of 35 elements that captures ligand-only properties
         * (counts of pharmacophore features, heavy atoms, rotatable bonds, \f$ \log P \f$,
         * \f$ TPSA \f$, etc.) and target-environment-specific scores (HBA/HBD occupancy sums and
         * maxima, pi/aromatic/hydrophobic/halogen-bonding interaction scores, and electrostatic
         * + van der Waals energy contributions). See ElementIndex for the layout.
         *
         * \see [\ref GRAIL]
         */
        class CDPL_GRAIL_API GRAILDescriptorCalculator
        {

          public:
            /**
             * \brief Total number of elements in the calculated descriptor vector.
             */
            static constexpr std::size_t TOTAL_DESCRIPTOR_SIZE  = 35;

            /**
             * \brief Number of ligand-only descriptor elements (the first \c LIGAND_DESCRIPTOR_SIZE entries of the vector).
             */
            static constexpr std::size_t LIGAND_DESCRIPTOR_SIZE = 13;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GRAILDescriptorCalculator instances.
             */
            typedef std::shared_ptr<GRAILDescriptorCalculator> SharedPointer;

            /**
             * \brief Indices of the individual elements of the GRAIL descriptor vector.
             */
            enum ElementIndex
            {

                /** \brief Positive-ionizable feature count (ligand). */
                PI_COUNT,
                /** \brief Negative-ionizable feature count (ligand). */
                NI_COUNT,
                /** \brief Aromatic feature count (ligand). */
                AR_COUNT,
                /** \brief Hydrophobic feature count (ligand). */
                H_COUNT,
                /** \brief Hydrogen-bond donor feature count (ligand). */
                HBD_COUNT,
                /** \brief Hydrogen-bond acceptor feature count (ligand). */
                HBA_COUNT,
                /** \brief Halogen-bond donor feature count (ligand). */
                XBD_COUNT,
                /** \brief Halogen-bond acceptor feature count (ligand). */
                XBA_COUNT,
                /** \brief Heavy atom count (ligand). */
                HVY_ATOM_COUNT,
                /** \brief Rotatable bond count (ligand). */
                ROT_BOND_COUNT,
                /** \brief Total computed hydrophobicity (ligand). */
                TOTAL_HYD,
                /** \brief Computed \f$ \log P \f$ (ligand). */
                LOGP,
                /** \brief Computed topological polar surface area (ligand). */
                TPSA,
                /** \brief Sum of HBA occupancy scores against the target environment. */
                ENV_HBA_OCC_SUM,
                /** \brief Maximum HBA occupancy score against the target environment. */
                ENV_HBA_OCC_MAX,
                /** \brief Sum of HBD occupancy scores against the target environment. */
                ENV_HBD_OCC_SUM,
                /** \brief Maximum HBD occupancy score against the target environment. */
                ENV_HBD_OCC_MAX,
                /** \brief Sum of (ligand positive-ionizable &rarr; target aromatic) interaction scores. */
                PI_AR_SCORE_SUM,
                /** \brief Maximum (ligand positive-ionizable &rarr; target aromatic) interaction score. */
                PI_AR_SCORE_MAX,
                /** \brief Sum of (ligand aromatic &rarr; target positive-ionizable) interaction scores. */
                AR_PI_SCORE_SUM,
                /** \brief Maximum (ligand aromatic &rarr; target positive-ionizable) interaction score. */
                AR_PI_SCORE_MAX,
                /** \brief Sum of hydrophobic-hydrophobic interaction scores. */
                H_H_SCORE_SUM,
                /** \brief Maximum hydrophobic-hydrophobic interaction score. */
                H_H_SCORE_MAX,
                /** \brief Sum of aromatic-aromatic interaction scores. */
                AR_AR_SCORE_SUM,
                /** \brief Maximum aromatic-aromatic interaction score. */
                AR_AR_SCORE_MAX,
                /** \brief Sum of (ligand HBD &rarr; target HBA) interaction scores. */
                HBD_HBA_SCORE_SUM,
                /** \brief Maximum (ligand HBD &rarr; target HBA) interaction score. */
                HBD_HBA_SCORE_MAX,
                /** \brief Sum of (ligand HBA &rarr; target HBD) interaction scores. */
                HBA_HBD_SCORE_SUM,
                /** \brief Maximum (ligand HBA &rarr; target HBD) interaction score. */
                HBA_HBD_SCORE_MAX,
                /** \brief Sum of (ligand XBD &rarr; target XBA) interaction scores. */
                XBD_XBA_SCORE_SUM,
                /** \brief Maximum (ligand XBD &rarr; target XBA) interaction score. */
                XBD_XBA_SCORE_MAX,
                /** \brief Electrostatic interaction energy. */
                ES_ENERGY,
                /** \brief Electrostatic interaction energy weighted by squared atom-pair distance. */
                ES_ENERGY_SQRD_DIST,
                /** \brief Attractive part of the van der Waals interaction energy. */
                VDW_ENERGY_ATT,
                /** \brief Repulsive part of the van der Waals interaction energy. */
                VDW_ENERGY_REP
            };

            /**
             * \brief Constructs the \c %GRAILDescriptorCalculator instance.
             */
            GRAILDescriptorCalculator();

            /**
             * \brief Constructs a copy of the \c %GRAILDescriptorCalculator instance \a calc.
             * \param calc The \c %GRAILDescriptorCalculator to copy.
             */
            GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc);

            /**
             * \brief Destructor.
             */
            ~GRAILDescriptorCalculator();

            /**
             * \brief Copy assignment operator.
             * \param calc The other \c %GRAILDescriptorCalculator instance.
             * \return A reference to itself.
             */
            GRAILDescriptorCalculator& operator=(const GRAILDescriptorCalculator& calc);

            /**
             * \brief Initializes the calculator with target-environment data for subsequent descriptor calculations.
             * \param tgt_env The target environment (e.g. binding-site residues).
             * \param coords_func The function used to retrieve atom 3D-coordinates from \a tgt_env.
             * \param tgt_env_changed If \c true, the target environment is reinitialized even if the same target was supplied previously.
             */
            void initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
                                bool tgt_env_changed = true);

            /**
             * \brief Initializes the calculator with the molecular graph of the ligand.
             * \param ligand The ligand molecular graph.
             */
            void initLigandData(const Chem::MolecularGraph& ligand);

            /**
             * \brief Calculates the GRAIL descriptor for the current ligand pose.
             *
             * The pose is supplied via per-atom 3D coordinates in \a atom_coords (same order as the atoms
             * of the molecular graph passed to initLigandData()). The result is written to \a descr.
             *
             * \param atom_coords The 3D coordinates of the ligand atoms.
             * \param descr The output descriptor vector (resized to TOTAL_DESCRIPTOR_SIZE).
             * \param update_lig_part If \c true, the ligand-only part of the descriptor is recomputed.
             */
            void calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part = true);

          private:
            void initCalculatorImpl();

            typedef std::unique_ptr<GRAILDescriptorCalculatorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
