/* 
 * FeatureContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Pharm::FeatureContainer instances.
 */

#ifndef CDPL_PHARM_FEATURECONTAINERFUNCTIONS_HPP
#define CDPL_PHARM_FEATURECONTAINERFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
        class Fragment;
    } // namespace Chem

    namespace Pharm
    {

        class FeatureContainer;
        class FeatureTypeHistogram;
        class FeatureSet;

        /**
         * \brief Returns the value of the Pharm::FeatureContainerProperty::NAME property of the feature container \a cntnr.
         * \param cntnr The feature container for which to return the property value.
         * \return The name (or an empty string if the property is not set).
         */
        CDPL_PHARM_API const std::string& getName(const FeatureContainer& cntnr);

        /**
         * \brief Sets the value of the Pharm::FeatureContainerProperty::NAME property of the feature container \a cntnr to \a name.
         * \param cntnr The feature container for which to set the property value.
         * \param name The new name.
         */
        CDPL_PHARM_API void setName(FeatureContainer& cntnr, const std::string& name);

        /**
         * \brief Clears the value of the Pharm::FeatureContainerProperty::NAME property of the feature container \a cntnr.
         * \param cntnr The feature container for which to clear the property value.
         */
        CDPL_PHARM_API void clearName(FeatureContainer& cntnr);

        /**
         * \brief Tells whether the Pharm::FeatureContainerProperty::NAME property of the feature container \a cntnr is set.
         * \param cntnr The feature container for which to query the property value.
         * \return \c true if the name property is set, and \c false otherwise.
         */
        CDPL_PHARM_API bool hasName(const FeatureContainer& cntnr);


        /**
         * \brief Returns the total number of features stored in the feature container \a cntnr.
         * \param cntnr The feature container.
         * \return The number of stored features.
         */
        CDPL_PHARM_API std::size_t getFeatureCount(const FeatureContainer& cntnr);

        /**
         * \brief Returns the number of features in the feature container \a cntr whose type matches \a type.
         * \param cntnr The feature container.
         * \param type The feature type to count.
         * \return The number of features of the specified type.
         */
        CDPL_PHARM_API std::size_t getFeatureCount(const FeatureContainer& cntnr, unsigned int type);

        /**
         * \brief Computes a per-feature type frequency histogram of the features in the feature container \a cntr.
         * \param cntnr The feature container.
         * \param hist The output histogram (feature type to count).
         * \param append If \c false, \a hist is cleared before the counts are accumulated.
         */
        CDPL_PHARM_API void generateFeatureTypeHistogram(const FeatureContainer& cntnr, FeatureTypeHistogram& hist, bool append = false);

        /**
         * \brief Generates a string representation of the feature type histogram of the feature container \a cntr.
         *
         * The generated string is a human readable comma separated list of entries of the form <em>Name(count)</em>.
         *
         * \param cntnr The feature container.
         * \param histo_str The output string.
         */
        CDPL_PHARM_API void generateFeatureTypeHistogramString(const FeatureContainer& cntnr, std::string& histo_str);

        /**
         * \brief Clears the orientation property of every feature in the feature container \a cntr and
         *        (optionally) resets each feature's geometry property.
         * \param cntnr The feature container.
         * \param fix_geom If \c true, the geometry property of each feature is set to Pharm::FeatureGeometry::SPHERE after clearing the orientation.
         * \since 1.2
         */
        CDPL_PHARM_API void clearOrientations(FeatureContainer& cntnr, bool fix_geom = true);

        /**
         * \brief Copies the features in the feature container \a cntr into \a tgt_set, suppressing features that share both type and 3D position
         *        with an already collected feature.
         *
         * Two features count as duplicates if they have identical type and their position vectors either match
         * exactly (\a pos_tol &le; 0) or lie within \a pos_tol from each other. When a duplicate is detected, the feature with
         * the larger position tolerance is retained.
         *
         * \param cntnr The feature container providing the input features.
         * \param tgt_set The feature set receiving the deduplicated features.
         * \param pos_tol The position-equality tolerance in &Aring;ngstrom. Values &le; \e 0 require an exact position match.
         * \param append If \c false, \a tgt_set is cleared before adding any features.
         * \return \c true if at least one duplicate was detected, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removePositionalDuplicates(const FeatureContainer& cntnr, FeatureSet& tgt_set, double pos_tol = 0.0, bool append = false);

        /**
         * \brief Copies the features in the feature container \a cntr into \a tgt_set, skipping every feature whose type matches \a type.
         * \param cntnr The feature container providing the input features.
         * \param tgt_set The feature set receiving the filtered features.
         * \param type The feature type to exclude (see namespace Pharm::FeatureType).
         * \param append If \c false, \a tgt_set is cleared before adding any features.
         * \return \c true if at least one feature was excluded, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removeFeaturesWithType(const FeatureContainer& cntnr, FeatureSet& tgt_set, unsigned int type, bool append = false);

        /**
         * \brief Applies the affine transformation \a mtx to the 3D position property and, if set, the orientation property of every
         *        feature in the feature container \a cntr.
         * \param cntnr The feature container to transform.
         * \param mtx The 4x4 transformation matrix.
         */
        CDPL_PHARM_API void transform3DCoordinates(FeatureContainer& cntnr, const Math::Matrix4D& mtx);

        /**
         * \brief Tests whether the exclusion volume features in \a ftr_cntnr remain clash-free with respect to the transformed
         *        atom positions of \a atom_cntnr.
         *
         * Each enabled feature of type Pharm::FeatureType::EXCLUSION_VOLUME is checked against every atom of \a atom_cntnr:
         * a clash is reported as soon as the distance between feature and atom is smaller than the sum of the feature's position
         * tolerance and \a vdw_factor times the atom's Van der Waals radius.
         *
         * \param ftr_cntnr The feature container providing the exclusion volume features.
         * \param atom_cntnr The atom container providing the test atoms.
         * \param coords_func The function returning the 3D coordinates of an atom.
         * \param xform The 4x4 transformation applied to the atom coordinates before the clash test.
         * \param vdw_factor Scaling factor for the per-atom Van der Waals radii. If &le; \e 0 the atoms are treated as point particles.
         * \return \c true if no clash is detected, and \c false otherwise.
         */
        CDPL_PHARM_API bool checkForExclusionVolumeClashes(const FeatureContainer& ftr_cntnr, const Chem::AtomContainer& atom_cntnr,
                                                           const Chem::Atom3DCoordinatesFunction& coords_func,
                                                           const Math::Matrix4D& xform, double vdw_factor = 1.0);

        /**
         * \brief Collects the atoms of the molecular substructures underlying the features of the feature container \a cntr into \a atoms.
         *
         * Features without an associated substructure (see Pharm::hasSubstructure()) are silently skipped.
         *
         * \param cntnr The feature container providing the features.
         * \param atoms The output fragment receiving the contributing atoms.
         * \param append If \c false, \a atoms is cleared before any atoms are added.
         */
        CDPL_PHARM_API void getFeatureAtoms(const FeatureContainer& cntnr, Chem::Fragment& atoms, bool append = false);
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATURECONTAINERFUNCTIONS_HPP
