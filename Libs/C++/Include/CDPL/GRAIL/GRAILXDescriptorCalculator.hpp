/* 
 * GRAILXDescriptorCalculator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::GRAILXDescriptorCalculator.
 */

#ifndef CDPL_GRAIL_GRAILXDESCRIPTORCALCULATOR_HPP
#define CDPL_GRAIL_GRAILXDESCRIPTORCALCULATOR_HPP

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
         * \brief Calculation of the extended GRAIL-X descriptor for protein-ligand complexes.
         *
         * \c %GRAILXDescriptorCalculator is the SYBYL-atom-type-aware variant of
         * GRAIL::GRAILDescriptorCalculator. The resulting 177-element descriptor refines the
         * generic hydrogen-bond donor/acceptor terms by also resolving the chemical environment
         * (N3, N2, Nar, Nam, Npl3, N4, O3, O2, Oco2, S3, S2) of the participating heavy atom.
         * The full element layout is given by ElementIndex.
         *
         * \see [\ref GRADE]
         */
        class CDPL_GRAIL_API GRAILXDescriptorCalculator
        {

          public:
            /**
             * \brief Total number of elements in the calculated descriptor vector.
             */
            static constexpr std::size_t TOTAL_DESCRIPTOR_SIZE  = 177;

            /**
             * \brief Number of ligand-only descriptor elements (the first \c LIGAND_DESCRIPTOR_SIZE entries of the vector).
             */
            static constexpr std::size_t LIGAND_DESCRIPTOR_SIZE = 31;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GRAILXDescriptorCalculator instances.
             */
            typedef std::shared_ptr<GRAILXDescriptorCalculator> SharedPointer;

            /**
             * \brief Indices of the individual elements of the extended GRAIL-X descriptor vector.
             *
             * The layout consists of six sections (in this order):
             *   1. Feature/atom/bond counts of the ligand (positions [0, 8) and [26, 31)).
             *   2. HBD / HBA counts of the ligand resolved by heavy atom SYBYL type (positions [8, 26)).
             *   3. Target-environment H-bond occupancy SUM/MAX values resolved by ligand-feature heavy atom element ([31, 43)).
             *   4. Generic interaction scores SUM/MAX (PI-AR, AR-PI, H-H, AR-AR) ([43, 51)).
             *   5. Hydrogen-bond interaction SUM/MAX scores between ligand HBD/HBA subtype and target HBA/HBD by heavy atom element ([51, 171)).
             *   6. Halogen-bond and energy terms ([171, 177)).
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
                /** \brief Ligand HBD feature count with N3 heavy atom. */
                HBD_N3_COUNT,
                /** \brief Ligand HBD feature count with N2 heavy atom. */
                HBD_N2_COUNT,
                /** \brief Ligand HBD feature count with Nar heavy atom. */
                HBD_Nar_COUNT,
                /** \brief Ligand HBD feature count with Nam heavy atom. */
                HBD_Nam_COUNT,
                /** \brief Ligand HBD feature count with Npl3 heavy atom. */
                HBD_Npl3_COUNT,
                /** \brief Ligand HBD feature count with N4 heavy atom. */
                HBD_N4_COUNT,
                /** \brief Ligand HBD feature count with O3 heavy atom. */
                HBD_O3_COUNT,
                /** \brief Ligand HBD feature count with S3 heavy atom. */
                HBD_S3_COUNT,
                /** \brief Ligand HBA feature count with N3 heavy atom. */
                HBA_N3_COUNT,
                /** \brief Ligand HBA feature count with N2 heavy atom. */
                HBA_N2_COUNT,
                /** \brief Ligand HBA feature count with N1 heavy atom. */
                HBA_N1_COUNT,
                /** \brief Ligand HBA feature count with Nar heavy atom. */
                HBA_Nar_COUNT,
                /** \brief Ligand HBA feature count with Npl3 heavy atom. */
                HBA_Npl3_COUNT,
                /** \brief Ligand HBA feature count with O3 heavy atom. */
                HBA_O3_COUNT,
                /** \brief Ligand HBA feature count with O2 heavy atom. */
                HBA_O2_COUNT,
                /** \brief Ligand HBA feature count with Oco2 heavy atom. */
                HBA_Oco2_COUNT,
                /** \brief Ligand HBA feature count with S3 heavy atom. */
                HBA_S3_COUNT,
                /** \brief Ligand HBA feature count with S2 heavy atom. */
                HBA_S2_COUNT,
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
                /** \brief Sum of environment HBA occupancy scores against ligand HBD-N atoms. */
                ENV_HBA_N_OCC_SUM,
                /** \brief Maximum environment HBA occupancy score against ligand HBD-N atoms. */
                ENV_HBA_N_OCC_MAX,
                /** \brief Sum of environment HBA occupancy scores against ligand HBD-O atoms. */
                ENV_HBA_O_OCC_SUM,
                /** \brief Maximum environment HBA occupancy score against ligand HBD-O atoms. */
                ENV_HBA_O_OCC_MAX,
                /** \brief Sum of environment HBA occupancy scores against ligand HBD-S atoms. */
                ENV_HBA_S_OCC_SUM,
                /** \brief Maximum environment HBA occupancy score against ligand HBD-S atoms. */
                ENV_HBA_S_OCC_MAX,
                /** \brief Sum of environment HBD occupancy scores against ligand HBA-N atoms. */
                ENV_HBD_N_OCC_SUM,
                /** \brief Maximum environment HBD occupancy score against ligand HBA-N atoms. */
                ENV_HBD_N_OCC_MAX,
                /** \brief Sum of environment HBD occupancy scores against ligand HBA-O atoms. */
                ENV_HBD_O_OCC_SUM,
                /** \brief Maximum environment HBD occupancy score against ligand HBA-O atoms. */
                ENV_HBD_O_OCC_MAX,
                /** \brief Sum of environment HBD occupancy scores against ligand HBA-S atoms. */
                ENV_HBD_S_OCC_SUM,
                /** \brief Maximum environment HBD occupancy score against ligand HBA-S atoms. */
                ENV_HBD_S_OCC_MAX,
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
                /** \brief Sum of (any ligand HBD &rarr; target HBA-N) interaction scores. */
                HBD_HBA_N_SCORE_SUM,
                /** \brief Maximum (any ligand HBD &rarr; target HBA-N) interaction score. */
                HBD_HBA_N_SCORE_MAX,
                /** \brief Sum of (any ligand HBD &rarr; target HBA-O) interaction scores. */
                HBD_HBA_O_SCORE_SUM,
                /** \brief Maximum (any ligand HBD &rarr; target HBA-O) interaction score. */
                HBD_HBA_O_SCORE_MAX,
                /** \brief Sum of (any ligand HBD &rarr; target HBA-S) interaction scores. */
                HBD_HBA_S_SCORE_SUM,
                /** \brief Maximum (any ligand HBD &rarr; target HBA-S) interaction score. */
                HBD_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N3 &rarr; target HBA-N) interaction scores. */
                HBD_N3_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N3 &rarr; target HBA-N) interaction score. */
                HBD_N3_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N3 &rarr; target HBA-O) interaction scores. */
                HBD_N3_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N3 &rarr; target HBA-O) interaction score. */
                HBD_N3_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N3 &rarr; target HBA-S) interaction scores. */
                HBD_N3_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N3 &rarr; target HBA-S) interaction score. */
                HBD_N3_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N2 &rarr; target HBA-N) interaction scores. */
                HBD_N2_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N2 &rarr; target HBA-N) interaction score. */
                HBD_N2_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N2 &rarr; target HBA-O) interaction scores. */
                HBD_N2_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N2 &rarr; target HBA-O) interaction score. */
                HBD_N2_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N2 &rarr; target HBA-S) interaction scores. */
                HBD_N2_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N2 &rarr; target HBA-S) interaction score. */
                HBD_N2_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Nar &rarr; target HBA-N) interaction scores. */
                HBD_Nar_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Nar &rarr; target HBA-N) interaction score. */
                HBD_Nar_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Nar &rarr; target HBA-O) interaction scores. */
                HBD_Nar_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Nar &rarr; target HBA-O) interaction score. */
                HBD_Nar_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Nar &rarr; target HBA-S) interaction scores. */
                HBD_Nar_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Nar &rarr; target HBA-S) interaction score. */
                HBD_Nar_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Nam &rarr; target HBA-N) interaction scores. */
                HBD_Nam_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Nam &rarr; target HBA-N) interaction score. */
                HBD_Nam_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Nam &rarr; target HBA-O) interaction scores. */
                HBD_Nam_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Nam &rarr; target HBA-O) interaction score. */
                HBD_Nam_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Nam &rarr; target HBA-S) interaction scores. */
                HBD_Nam_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Nam &rarr; target HBA-S) interaction score. */
                HBD_Nam_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Npl3 &rarr; target HBA-N) interaction scores. */
                HBD_Npl3_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Npl3 &rarr; target HBA-N) interaction score. */
                HBD_Npl3_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Npl3 &rarr; target HBA-O) interaction scores. */
                HBD_Npl3_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Npl3 &rarr; target HBA-O) interaction score. */
                HBD_Npl3_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-Npl3 &rarr; target HBA-S) interaction scores. */
                HBD_Npl3_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-Npl3 &rarr; target HBA-S) interaction score. */
                HBD_Npl3_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N4 &rarr; target HBA-N) interaction scores. */
                HBD_N4_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N4 &rarr; target HBA-N) interaction score. */
                HBD_N4_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N4 &rarr; target HBA-O) interaction scores. */
                HBD_N4_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N4 &rarr; target HBA-O) interaction score. */
                HBD_N4_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-N4 &rarr; target HBA-S) interaction scores. */
                HBD_N4_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-N4 &rarr; target HBA-S) interaction score. */
                HBD_N4_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-O3 &rarr; target HBA-N) interaction scores. */
                HBD_O3_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-O3 &rarr; target HBA-N) interaction score. */
                HBD_O3_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-O3 &rarr; target HBA-O) interaction scores. */
                HBD_O3_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-O3 &rarr; target HBA-O) interaction score. */
                HBD_O3_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-O3 &rarr; target HBA-S) interaction scores. */
                HBD_O3_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-O3 &rarr; target HBA-S) interaction score. */
                HBD_O3_HBA_S_SCORE_MAX,
                /** \brief Sum of (ligand HBD-S3 &rarr; target HBA-N) interaction scores. */
                HBD_S3_HBA_N_SCORE_SUM,
                /** \brief Maximum (ligand HBD-S3 &rarr; target HBA-N) interaction score. */
                HBD_S3_HBA_N_SCORE_MAX,
                /** \brief Sum of (ligand HBD-S3 &rarr; target HBA-O) interaction scores. */
                HBD_S3_HBA_O_SCORE_SUM,
                /** \brief Maximum (ligand HBD-S3 &rarr; target HBA-O) interaction score. */
                HBD_S3_HBA_O_SCORE_MAX,
                /** \brief Sum of (ligand HBD-S3 &rarr; target HBA-S) interaction scores. */
                HBD_S3_HBA_S_SCORE_SUM,
                /** \brief Maximum (ligand HBD-S3 &rarr; target HBA-S) interaction score. */
                HBD_S3_HBA_S_SCORE_MAX,
                /** \brief Sum of (any ligand HBA &rarr; target HBD-N) interaction scores. */
                HBA_HBD_N_SCORE_SUM,
                /** \brief Maximum (any ligand HBA &rarr; target HBD-N) interaction score. */
                HBA_HBD_N_SCORE_MAX,
                /** \brief Sum of (any ligand HBA &rarr; target HBD-O) interaction scores. */
                HBA_HBD_O_SCORE_SUM,
                /** \brief Maximum (any ligand HBA &rarr; target HBD-O) interaction score. */
                HBA_HBD_O_SCORE_MAX,
                /** \brief Sum of (any ligand HBA &rarr; target HBD-S) interaction scores. */
                HBA_HBD_S_SCORE_SUM,
                /** \brief Maximum (any ligand HBA &rarr; target HBD-S) interaction score. */
                HBA_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N3 &rarr; target HBD-N) interaction scores. */
                HBA_N3_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N3 &rarr; target HBD-N) interaction score. */
                HBA_N3_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N3 &rarr; target HBD-O) interaction scores. */
                HBA_N3_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N3 &rarr; target HBD-O) interaction score. */
                HBA_N3_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N3 &rarr; target HBD-S) interaction scores. */
                HBA_N3_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N3 &rarr; target HBD-S) interaction score. */
                HBA_N3_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N2 &rarr; target HBD-N) interaction scores. */
                HBA_N2_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N2 &rarr; target HBD-N) interaction score. */
                HBA_N2_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N2 &rarr; target HBD-O) interaction scores. */
                HBA_N2_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N2 &rarr; target HBD-O) interaction score. */
                HBA_N2_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N2 &rarr; target HBD-S) interaction scores. */
                HBA_N2_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N2 &rarr; target HBD-S) interaction score. */
                HBA_N2_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N1 &rarr; target HBD-N) interaction scores. */
                HBA_N1_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N1 &rarr; target HBD-N) interaction score. */
                HBA_N1_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N1 &rarr; target HBD-O) interaction scores. */
                HBA_N1_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N1 &rarr; target HBD-O) interaction score. */
                HBA_N1_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-N1 &rarr; target HBD-S) interaction scores. */
                HBA_N1_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-N1 &rarr; target HBD-S) interaction score. */
                HBA_N1_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Nar &rarr; target HBD-N) interaction scores. */
                HBA_Nar_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Nar &rarr; target HBD-N) interaction score. */
                HBA_Nar_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Nar &rarr; target HBD-O) interaction scores. */
                HBA_Nar_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Nar &rarr; target HBD-O) interaction score. */
                HBA_Nar_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Nar &rarr; target HBD-S) interaction scores. */
                HBA_Nar_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Nar &rarr; target HBD-S) interaction score. */
                HBA_Nar_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Npl3 &rarr; target HBD-N) interaction scores. */
                HBA_Npl3_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Npl3 &rarr; target HBD-N) interaction score. */
                HBA_Npl3_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Npl3 &rarr; target HBD-O) interaction scores. */
                HBA_Npl3_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Npl3 &rarr; target HBD-O) interaction score. */
                HBA_Npl3_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Npl3 &rarr; target HBD-S) interaction scores. */
                HBA_Npl3_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Npl3 &rarr; target HBD-S) interaction score. */
                HBA_Npl3_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-O3 &rarr; target HBD-N) interaction scores. */
                HBA_O3_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-O3 &rarr; target HBD-N) interaction score. */
                HBA_O3_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-O3 &rarr; target HBD-O) interaction scores. */
                HBA_O3_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-O3 &rarr; target HBD-O) interaction score. */
                HBA_O3_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-O3 &rarr; target HBD-S) interaction scores. */
                HBA_O3_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-O3 &rarr; target HBD-S) interaction score. */
                HBA_O3_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-O2 &rarr; target HBD-N) interaction scores. */
                HBA_O2_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-O2 &rarr; target HBD-N) interaction score. */
                HBA_O2_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-O2 &rarr; target HBD-O) interaction scores. */
                HBA_O2_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-O2 &rarr; target HBD-O) interaction score. */
                HBA_O2_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-O2 &rarr; target HBD-S) interaction scores. */
                HBA_O2_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-O2 &rarr; target HBD-S) interaction score. */
                HBA_O2_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Oco2 &rarr; target HBD-N) interaction scores. */
                HBA_Oco2_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Oco2 &rarr; target HBD-N) interaction score. */
                HBA_Oco2_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Oco2 &rarr; target HBD-O) interaction scores. */
                HBA_Oco2_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Oco2 &rarr; target HBD-O) interaction score. */
                HBA_Oco2_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-Oco2 &rarr; target HBD-S) interaction scores. */
                HBA_Oco2_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-Oco2 &rarr; target HBD-S) interaction score. */
                HBA_Oco2_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-S3 &rarr; target HBD-N) interaction scores. */
                HBA_S3_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-S3 &rarr; target HBD-N) interaction score. */
                HBA_S3_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-S3 &rarr; target HBD-O) interaction scores. */
                HBA_S3_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-S3 &rarr; target HBD-O) interaction score. */
                HBA_S3_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-S3 &rarr; target HBD-S) interaction scores. */
                HBA_S3_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-S3 &rarr; target HBD-S) interaction score. */
                HBA_S3_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand HBA-S2 &rarr; target HBD-N) interaction scores. */
                HBA_S2_HBD_N_SCORE_SUM,
                /** \brief Maximum (ligand HBA-S2 &rarr; target HBD-N) interaction score. */
                HBA_S2_HBD_N_SCORE_MAX,
                /** \brief Sum of (ligand HBA-S2 &rarr; target HBD-O) interaction scores. */
                HBA_S2_HBD_O_SCORE_SUM,
                /** \brief Maximum (ligand HBA-S2 &rarr; target HBD-O) interaction score. */
                HBA_S2_HBD_O_SCORE_MAX,
                /** \brief Sum of (ligand HBA-S2 &rarr; target HBD-S) interaction scores. */
                HBA_S2_HBD_S_SCORE_SUM,
                /** \brief Maximum (ligand HBA-S2 &rarr; target HBD-S) interaction score. */
                HBA_S2_HBD_S_SCORE_MAX,
                /** \brief Sum of (ligand XBD &rarr; target XBA) interaction scores. */
                XBD_XBA_SCORE_SUM,
                /** \brief Maximum (ligand XBD &rarr; target XBA) interaction score. */
                XBD_XBA_SCORE_MAX,
                /** \brief Electrostatic interaction energy. */
                ES_ENERGY,
                /** \brief Electrostatic interaction energy with squared atom-pair distance dependency. */
                ES_ENERGY_SQRD_DIST,
                /** \brief Attractive part of the Van der Waals interaction energy. */
                VDW_ENERGY_ATT,
                /** \brief Repulsive part of the Van der Waals interaction energy. */
                VDW_ENERGY_REP
            };

            /**
             * \brief Constructs the \c %GRAILXDescriptorCalculator instance.
             */
            GRAILXDescriptorCalculator();

            /**
             * \brief Constructs a copy of the \c %GRAILXDescriptorCalculator instance \a calc.
             * \param calc The \c %GRAILXDescriptorCalculator to copy.
             */
            GRAILXDescriptorCalculator(const GRAILXDescriptorCalculator& calc);

            /**
             * \brief Destructor.
             */
            ~GRAILXDescriptorCalculator();

            /**
             * \brief Copy assignment operator.
             * \param calc The other \c %GRAILXDescriptorCalculator instance.
             * \return A reference to itself.
             */
            GRAILXDescriptorCalculator& operator=(const GRAILXDescriptorCalculator& calc);

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
             * \brief Calculates the extended GRAIL-X descriptor for the current ligand pose.
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

#endif // CDPL_GRAIL_GRAILXDESCRIPTORCALCULATOR_HPP
