/* 
 * DGStructureGenerator.hpp 
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
 * \brief Definition of class CDPL::ConfGen::DGStructureGenerator.
 */

#ifndef CDPL_CONFGEN_DGSTRUCTUREGENERATOR_HPP
#define CDPL_CONFGEN_DGSTRUCTUREGENERATOR_HPP

#include <cstddef>

#include <boost/random/mersenne_twister.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/DGConstraintGenerator.hpp"
#include "CDPL/ConfGen/DGStructureGeneratorSettings.hpp"
#include "CDPL/Util/DGCoordinatesGenerator.hpp"


namespace CDPL
{

    namespace Chem
    {

        class FragmentList;
    }
    
    namespace ConfGen
    {

        /**
         * \brief Distance-geometry-based generation of raw 3D structures for molecular graphs.
         *
         * Constraints are produced by an embedded ConfGen::DGConstraintGenerator and used to embed the coordinates
         * via a two-phase Util::DG3DCoordinatesGenerator pipeline. After generation, atom and bond stereo
         * configurations can be validated against the perceived stereo descriptors.
         */
        class CDPL_CONFGEN_API DGStructureGenerator
        {

          public:
            /**
             * \brief Constructs the \c %DGStructureGenerator instance.
             */
            DGStructureGenerator();

            /**
             * \brief Returns the current generator settings (mutable).
             * \return A reference to the settings.
             */
            DGStructureGeneratorSettings& getSettings();

            /**
             * \brief Returns the current generator settings.
             * \return A \c const reference to the settings.
             */
            const DGStructureGeneratorSettings& getSettings() const;

            /**
             * \brief Returns the bit mask of hydrogens excluded from the coordinate-generation step.
             * \return A \c const reference to the bit mask.
             */
            const Util::BitSet& getExcludedHydrogenMask() const;

            /**
             * \brief Sets up the generator for \a molgraph using geometry defaults derived from each atom's
             *        element number and hybridization state.
             *
             * No MMFF94 parameterization is carried out; reference bond lengths and angles are taken from
             * element-/hybridization-based lookup tables.
             *
             * \param molgraph The input molecular graph.
             */
            void setup(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Sets up the generator for \a molgraph using the supplied MMFF94 interaction data.
             * \param molgraph The input molecular graph.
             * \param ia_data The pre-computed MMFF94 interaction data.
             */
            void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

            /**
             * \brief Sets up the generator for \a molgraph while keeping the substructure fragments in \a fixed_substr_frags at the supplied 3D coordinates.
             * \param molgraph The input molecular graph.
             * \param fixed_substr_frags The substructure fragments that must retain their 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to the fixed substructures.
             * \since 1.1
             */
            void setup(const Chem::MolecularGraph& molgraph, const Chem::FragmentList& fixed_substr_frags,
                       const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Sets up the generator for \a molgraph using the supplied MMFF94 interaction data and fixed-substructure data.
             * \param molgraph The input molecular graph.
             * \param ia_data The pre-computed MMFF94 interaction data.
             * \param fixed_substr_frags The substructure fragments that must retain their 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to the fixed substructures.
             * \since 1.1
             */
            void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data,
                       const Chem::FragmentList& fixed_substr_frags, const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Generates a 3D coordinate set that respects the configured distance constraints.
             * \param coords The output 3D coordinate array.
             * \return \c true if the embedding succeeded, and \c false otherwise.
             */
            bool generate(Math::Vector3DArray& coords);

            /**
             * \brief Validates the per-atom stereo-configurations of \a coords against the perceived stereo descriptors.
             * \param coords The 3D coordinates to test.
             * \return \c true if all per-atom stereo-configurations are valid, and \c false otherwise.
             */
            bool checkAtomConfigurations(Math::Vector3DArray& coords) const;

            /**
             * \brief Validates the per-bond stereo-configurations of \a coords against the perceived stereo descriptors.
             * \param coords The 3D coordinates to test.
             * \return \c true if all per-bond stereo-configurations are valid, and \c false otherwise.
             */
            bool checkBondConfigurations(Math::Vector3DArray& coords) const;

            /**
             * \brief Returns the number of atom stereo centers in the set-up molecular graph.
             * \return The atom stereo-center count.
             */
            std::size_t getNumAtomStereoCenters() const;

            /**
             * \brief Returns the number of bond stereo centers in the set-up molecular graph.
             * \return The bond stereo-center count.
             */
            std::size_t getNumBondStereoCenters() const;

            /**
             * \brief Returns the embedded constraint generator used to produce the distance/volume constraints.
             * \return A \c const reference to the constraint generator.
             */
            const DGConstraintGenerator& getConstraintGenerator() const;

          private:
            void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData* ia_data,
                       const Chem::FragmentList* fixed_substr_frags, const Math::Vector3DArray* fixed_substr_coords);

            typedef boost::random::mt11213b RandNumEngine;

            const Chem::MolecularGraph*    molGraph;
            const Chem::FragmentList*      fixedSubstructFrags;
            const Math::Vector3DArray*     fixedSubstructCoords;
            Math::Vector3DArray            fixedSubstructFragCtrs;
            DGConstraintGenerator          dgConstraintsGen;
            Util::DG3DCoordinatesGenerator phase1CoordsGen;
            Util::DG3DCoordinatesGenerator phase2CoordsGen;
            RandNumEngine                  randomEngine;
            DGStructureGeneratorSettings   settings;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_DGSTRUCTUREGENERATOR_HPP
