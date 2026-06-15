/* 
 * FeatureFunctions.hpp 
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
 * \brief Declaration of functions that operate on Pharm::Feature instances.
 */

#ifndef CDPL_GRAIL_FEATUREFUNCTIONS_HPP
#define CDPL_GRAIL_FEATUREFUNCTIONS_HPP

#include "CDPL/GRAIL/APIPrefix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;
    };

    namespace GRAIL
    {

        /**
         * \brief Perceives the GRAIL extended pharmacophore feature type
         *        of the given Pharm::Feature instance.
         * \param feature The feature for which to perceive the extended type.
         * \param lig_side If \c true, the perception is performed assuming the feature is part of a
         *                 ligand; otherwise it is assumed to be part of a target structure.
         * \return The perceived extended feature type (see namespace GRAIL::FeatureType).
         */
        CDPL_GRAIL_API unsigned int perceiveExtendedType(const Pharm::Feature& feature, bool lig_side);
    }
} // namespace CDPL

#endif // CDPL_GRAIL_FEATUREFUNCTIONS_HPP
