/* 
 * FeatureProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Pharm::FeatureProperty.
 */

#ifndef CDPL_PHARM_FEATUREPROPERTY_HPP
#define CDPL_PHARM_FEATUREPROPERTY_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Pharm
    {

        /**
         * \brief Provides keys for built-in Pharm::Feature properties.
         */
        namespace FeatureProperty
        {

            /**
             * \brief Specifies the type of the pharmacophore feature (see namespace Pharm::FeatureType).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_PHARM_API const Base::LookupKey TYPE;

            /**
             * \brief Specifies the geometric shape of the feature (see namespace Pharm::FeatureGeometry).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_PHARM_API const Base::LookupKey GEOMETRY;

            /**
             * \brief Specifies the length of the feature (for directional features).
             *
             * \valuetype \c double
             */
            extern CDPL_PHARM_API const Base::LookupKey LENGTH;

            /**
             * \brief Specifies the orientation of the feature in 3D space.
             *
             * \valuetype Math::Vector3D
             */
            extern CDPL_PHARM_API const Base::LookupKey ORIENTATION;

            /**
             * \brief Specifies the positional tolerance of the feature.
             *
             * \valuetype \c double
             */
            extern CDPL_PHARM_API const Base::LookupKey TOLERANCE;

            /**
             * \brief Specifies the weight (relative importance) of the feature.
             *
             * \valuetype \c double
             */
            extern CDPL_PHARM_API const Base::LookupKey WEIGHT;

            /**
             * \brief Specifies the atoms and bonds associated with the feature.
             *
             * \valuetype Chem::Fragment::SharedPointer
             */
            extern CDPL_PHARM_API const Base::LookupKey SUBSTRUCTURE;

            /**
             * \brief Specifies whether the feature is currently disabled (not considered in pharmacophore matching).
             *
             * \valuetype \c bool
             */
            extern CDPL_PHARM_API const Base::LookupKey DISABLED_FLAG;

            /**
             * \brief Specifies whether the feature is optional in pharmacophore matching.
             *
             * \valuetype \c bool
             */
            extern CDPL_PHARM_API const Base::LookupKey OPTIONAL_FLAG;

            /**
             * \brief Specifies the summed hydrophobicities of the atoms that are covered by the feature.
             *
             * \valuetype \c double
             */
            extern CDPL_PHARM_API const Base::LookupKey HYDROPHOBICITY;

            /**
             * \brief Specifies the environment atoms and bonds (e.g. of interacting pocket residues) associated with the feature.
             *
             * \valuetype Chem::Fragment::SharedPointer
             * \since 1.4
             */
            extern CDPL_PHARM_API const Base::LookupKey ENVIRONMENT_SUBSTRUCTURE;
            
        } // namespace FeatureProperty
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREPROPERTY_HPP
