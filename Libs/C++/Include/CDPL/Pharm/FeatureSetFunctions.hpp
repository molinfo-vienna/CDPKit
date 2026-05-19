/* 
 * FeatureSetFunctions.hpp 
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
 * \brief Declaration of functions that operate on Pharm::FeatureSet instances.
 */

#ifndef CDPL_PHARM_FEATURESETFUNCTIONS_HPP
#define CDPL_PHARM_FEATURESETFUNCTIONS_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class FeatureSet;
        class FeatureMapping;

        /**
         * \brief Extracts features from \a mapping into \a ftr_set.
         * \param ftr_set The output feature set.
         * \param mapping The feature mapping.
         * \param first If \c true, the first feature of each mapping pair is added; otherwise the second feature.
         */
        CDPL_PHARM_API void getFeatures(FeatureSet& ftr_set, const FeatureMapping& mapping, bool first);

        /**
         * \brief Removes features from \a ftr_set whose 3D position duplicates that of another feature of the same type.
         * \param ftr_set The feature set to clean (modified in place).
         * \param pos_tol The positional tolerance below which two features are considered duplicates.
         * \return \c true if at least one feature was removed, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removePositionalDuplicates(FeatureSet& ftr_set, double pos_tol = 0.0);

        /**
         * \brief Removes features of the given type from \a ftr_set.
         * \param ftr_set The feature set to clean (modified in place).
         * \param type The feature type to remove (see namespace Pharm::FeatureType).
         * \return \c true if at least one feature was removed, and \c false otherwise.
         * \since 1.2
         */
        CDPL_PHARM_API bool removeFeaturesWithType(FeatureSet& ftr_set, unsigned int type);
        
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATURESETFUNCTIONS_HPP
