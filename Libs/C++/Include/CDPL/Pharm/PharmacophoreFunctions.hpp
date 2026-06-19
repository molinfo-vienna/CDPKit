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
         * \brief Removes positional duplicate features from the pharmacophore \a pharm in place.
         *
         * Two features count as duplicates if they have identical type and their position vectors either match
         * exactly (\a pos_tol &le; 0) or lie within \a pos_tol from each other. When a duplicate is detected, the feature with
         * the larger position tolerance is retained.
         *
         * \param pharm The pharmacophore to deduplicate.
         * \param pos_tol The position-equality tolerance in &Aring;ngstrom. Values &le; 0 require an exact position match.
         * \return \c true if at least one feature was removed, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removePositionalDuplicates(Pharmacophore& pharm, double pos_tol = 0.0);

        /**
         * \brief Removes every feature in the pharmacophore \a pharm whose type matches \a type.
         * \param pharm The pharmacophore to filter.
         * \param type The feature type to remove (see namespace Pharm::FeatureType).
         * \return \c true if at least one feature was removed, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removeFeaturesWithType(Pharmacophore& pharm, unsigned int type);

        /**
         * \brief Builds an interaction pharmacophore from the supplied feature mapping.
         *
         * At least one output feature per interacting ligand feature is emitted. For H-bond donor/acceptor and X-bonding interactions
         * separate vector features are output. The environment substructure properties of the output features are
         * set to the (combined) substructures covered by the interacting target features.
         *
         * \param pharm The output pharmacophore where to add the generated features.
         * \param iactions The feature mapping describing the interactions.
         * \param append If \c false, the pharmacophore \a pharm is cleared before any features are added.
         */
        CDPL_PHARM_API void generateInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions, bool append = false);

        /**
         * \brief Creates exclusion volume features at the 3D positions of the atoms in \a cntnr and appends them to the pharmacophore \a pharm.
         * \param pharm The pharmacophore receiving the new exclusion volumes.
         * \param cntnr The atom container providing the seed positions.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param tol The position tolerance to assign to new exclusion volumes (if &le; 0 the per-atom VdW radius is used).
         * \param min_dist Minimum distance (\a rel_dist controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
         * \param rel_dist If \c true, the per-pair tolerance sum is subtracted from the pair distance before testing against \a min_dist. Otherwise, the absolute distance is tested.
         * \param append If \c false, the pharmacophore \a pharm is cleared before any exclusion volumes are added.
         */
        CDPL_PHARM_API void createExclusionVolumes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
                                                   const Chem::Atom3DCoordinatesFunction& coords_func,
                                                   double tol = 0.0, double min_dist = 0.0, bool rel_dist = true, bool append = true);

        /**
         * \brief Creates exclusion volume features at the 3D positions of the features in \a cntnr and appends them to the pharmacophore \a pharm.
         * \param pharm The pharmacophore receiving the new exclusion volumes.
         * \param cntnr The feature container providing the seed positions.
         * \param tol The position tolerance to assign to new exclusion volumes (if &le; 0 the per-feature tolerance is used).
         * \param min_dist Minimum distance (\a rel_dist controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
         * \param rel_dist If \c true, the per-pair tolerance sum is subtracted from the pair distance before testing against \a min_dist. Otherwise, the absolute distance is tested.
         * \param append If \c false, the pharmacophore \a pharm is cleared before any exclusion volumes are added.
         */
        CDPL_PHARM_API void createExclusionVolumes(Pharmacophore& pharm, const FeatureContainer& cntnr,
                                                   double tol = 0.0, double min_dist = 0.0, bool rel_dist = true, bool append = true);

        /**
         * \brief Removes every exclusion volume feature from the pharmacophore \a pharm whose tolerance sphere clashes with
         *        any atom of \a cntnr.
         * \param pharm The pharmacophore to filter.
         * \param cntnr The atom container providing the clash partners.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param vdw_scaling_fact Scaling factor applied to the per-atom Van der Waals radius during the clash test.
         * \return \c true if at least one exclusion volume was removed, and \c false otherwise.
         */
        CDPL_PHARM_API bool removeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
                                                              const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact = 1.0);

        /**
         * \brief Shrinks the tolerance of every exclusion volume feature in the pharmacophore \a pharm whose tolerance sphere
         *        clashes with any atom of \a cntnr.
         *
         * If the resulting tolerance falls below 0.25 then the exclusion volume feature is removed.
         *
         * \param pharm The pharmacophore to modify.
         * \param cntnr The atom container providing the clash partners.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param vdw_scaling_fact Scaling factor applied to the per-atom Van der Waals radius during the clash test.
         * \return \c true if at least one exclusion volume was resized or removed, and \c false otherwise.
         */
        CDPL_PHARM_API bool resizeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
                                                              const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact = 1.0);

    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP
