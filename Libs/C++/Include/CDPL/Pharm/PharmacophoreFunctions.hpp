/* 
 * PharmacophoreFunctions.hpp 
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
 * \brief Declaration of functions that operate on Pharm::Pharmacophore instances.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP
#define CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
    }

    namespace Pharm
    {

        class Pharmacophore;
        class FeatureMapping;
        class FeatureContainer;

        /**
         * \brief Removes positional duplicate features from \a pharm in place.
         *
         * Two features count as duplicates if they have identical Pharm::FeatureType and their position vectors either match
         * exactly (\a pos_tol &le; 0) or lie within \a pos_tol from each other. When a duplicate is detected, the feature with
         * the larger position tolerance is retained.
         *
         * \param pharm The pharmacophore to deduplicate.
         * \param pos_tol The position-equality tolerance in &Aring;ngstrom; values &le; 0 require an exact position match.
         * \return \c true if at least one feature was removed, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removePositionalDuplicates(Pharmacophore& pharm, double pos_tol = 0.0);

        /**
         * \brief Removes every feature in \a pharm whose Pharm::FeatureType matches \a type.
         * \param pharm The pharmacophore to filter.
         * \param type The Pharm::FeatureType to remove.
         * \return \c true if at least one feature was removed, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removeFeaturesWithType(Pharmacophore& pharm, unsigned int type);

        /**
         * \brief Builds an interaction pharmacophore from the supplied feature-to-feature mapping by emitting one feature
         *        per source feature, optionally enriched with orientation vectors and environment substructures derived
         *        from the mapped partner features.
         * \param pharm The output pharmacophore where to add the generated features.
         * \param iactions The feature-to-feature mapping describing the interactions.
         * \param append If \c false, \a pharm is cleared before any features are added.
         */
        CDPL_PHARM_API void generateInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions, bool append = false);

        /**
         * \brief Creates exclusion-volume features at the 3D positions of the atoms in \a cntnr and appends them to \a pharm.
         * \param pharm The pharmacophore receiving the new exclusion volumes.
         * \param cntnr The atom container providing the seed positions.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param tol The position tolerance to assign to new exclusion volumes (if &le; 0, the per-atom vdW radius is used).
         * \param min_dist Minimum distance (\a rel_dist controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
         * \param rel_dist If \c true, the per-pair tolerance sum is subtracted from the pair distance before testing against \a min_dist; otherwise the absolute distance is tested.
         * \param append If \c false, \a pharm is cleared before any exclusion volumes are added.
         */
        CDPL_PHARM_API void createExclusionVolumes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
                                                   const Chem::Atom3DCoordinatesFunction& coords_func,
                                                   double tol = 0.0, double min_dist = 0.0, bool rel_dist = true, bool append = true);

        /**
         * \brief Creates exclusion-volume features at the 3D positions of the features in \a cntnr and appends them to \a pharm.
         * \param pharm The pharmacophore receiving the new exclusion volumes.
         * \param cntnr The feature container providing the seed positions.
         * \param tol The position tolerance to assign to new exclusion volumes (if &le; 0, the per-feature tolerance is used).
         * \param min_dist Minimum distance (\a rel_dist controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
         * \param rel_dist If \c true, the per-pair tolerance sum is subtracted from the pair distance before testing against \a min_dist; otherwise the absolute distance is tested.
         * \param append If \c false, \a pharm is cleared before any exclusion volumes are added.
         */
        CDPL_PHARM_API void createExclusionVolumes(Pharmacophore& pharm, const FeatureContainer& cntnr,
                                                   double tol = 0.0, double min_dist = 0.0, bool rel_dist = true, bool append = true);

        /**
         * \brief Removes every Pharm::FeatureType::EXCLUSION_VOLUME feature of \a pharm whose tolerance sphere clashes with
         *        any atom of \a cntnr.
         * \param pharm The pharmacophore to filter.
         * \param cntnr The atom container providing the clash partners.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param vdw_scaling_fact Scaling factor applied to the per-atom van der Waals radius during the clash test.
         * \return \c true if at least one exclusion volume was removed, and \c false otherwise.
         */
        CDPL_PHARM_API bool removeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
                                                              const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact = 1.0);

        /**
         * \brief Shrinks the tolerance of every Pharm::FeatureType::EXCLUSION_VOLUME feature of \a pharm whose tolerance sphere
         *        clashes with any atom of \a cntnr; removes the exclusion volume when the resulting tolerance falls below 0.25.
         * \param pharm The pharmacophore to modify.
         * \param cntnr The atom container providing the clash partners.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param vdw_scaling_fact Scaling factor applied to the per-atom van der Waals radius during the clash test.
         * \return \c true if at least one exclusion volume was resized or removed, and \c false otherwise.
         */
        CDPL_PHARM_API bool resizeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
                                                              const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact = 1.0);

    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP
