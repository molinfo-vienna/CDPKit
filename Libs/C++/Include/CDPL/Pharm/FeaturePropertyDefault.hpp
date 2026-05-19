/* 
 * FeaturePropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Pharm::FeaturePropertyDefault.
 */

#ifndef CDPL_PHARM_FEATUREPROPERTYDEFAULT_HPP
#define CDPL_PHARM_FEATUREPROPERTYDEFAULT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief Provides default values for built-in Pharm::Feature properties.
         */
        namespace FeaturePropertyDefault
        {

            /** \brief Default value of the Pharm::FeatureProperty::OPTIONAL_FLAG property. */
            extern CDPL_PHARM_API const bool         OPTIONAL_FLAG;
            /** \brief Default value of the Pharm::FeatureProperty::DISABLED_FLAG property. */
            extern CDPL_PHARM_API const bool         DISABLED_FLAG;

            /** \brief Default value of the Pharm::FeatureProperty::LENGTH property. */
            extern CDPL_PHARM_API const double       LENGTH;
            /** \brief Default value of the Pharm::FeatureProperty::TOLERANCE property. */
            extern CDPL_PHARM_API const double       TOLERANCE;
            /** \brief Default value of the Pharm::FeatureProperty::WEIGHT property. */
            extern CDPL_PHARM_API const double       WEIGHT;
            /** \brief Default value of the Pharm::FeatureProperty::HYDROPHOBICITY property. */
            extern CDPL_PHARM_API const double       HYDROPHOBICITY;

            /** \brief Default value of the Pharm::FeatureProperty::TYPE property. */
            extern CDPL_PHARM_API const unsigned int TYPE;
            /** \brief Default value of the Pharm::FeatureProperty::GEOMETRY property. */
            extern CDPL_PHARM_API const unsigned int GEOMETRY;
        } // namespace FeaturePropertyDefault
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREPROPERTYDEFAULT_HPP
