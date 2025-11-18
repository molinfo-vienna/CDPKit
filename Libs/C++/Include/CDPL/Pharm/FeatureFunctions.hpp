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

#ifndef CDPL_PHARM_FEATUREFUNCTIONS_HPP
#define CDPL_PHARM_FEATUREFUNCTIONS_HPP

#include <string>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        CDPL_PHARM_API unsigned int getType(const Feature& feature);

        CDPL_PHARM_API void setType(Feature& feature, unsigned int type);

        CDPL_PHARM_API void clearType(Feature& feature);

        CDPL_PHARM_API bool hasType(const Feature& feature);


        CDPL_PHARM_API unsigned int getGeometry(const Feature& feature);

        CDPL_PHARM_API void setGeometry(Feature& feature, unsigned int geom);

        CDPL_PHARM_API void clearGeometry(Feature& feature);

        CDPL_PHARM_API bool hasGeometry(const Feature& feature);


        CDPL_PHARM_API const Math::Vector3D& getOrientation(const Feature& feature);

        CDPL_PHARM_API void setOrientation(Feature& feature, const Math::Vector3D& orient);

        CDPL_PHARM_API void clearOrientation(Feature& feature);

        CDPL_PHARM_API bool hasOrientation(const Feature& feature);


        CDPL_PHARM_API double getLength(const Feature& feature);

        CDPL_PHARM_API void setLength(Feature& feature, double length);

        CDPL_PHARM_API void clearLength(Feature& feature);

        CDPL_PHARM_API bool hasLength(const Feature& feature);


        CDPL_PHARM_API double getTolerance(const Feature& feature);

        CDPL_PHARM_API void setTolerance(Feature& feature, double tol);

        CDPL_PHARM_API void clearTolerance(Feature& feature);

        CDPL_PHARM_API bool hasTolerance(const Feature& feature);


        CDPL_PHARM_API double getWeight(const Feature& feature);

        CDPL_PHARM_API void setWeight(Feature& feature, double weight);

        CDPL_PHARM_API void clearWeight(Feature& feature);

        CDPL_PHARM_API bool hasWeight(const Feature& feature);


        CDPL_PHARM_API const Chem::Fragment::SharedPointer& getSubstructure(const Feature& feature);

        CDPL_PHARM_API void setSubstructure(Feature& feature, const Chem::Fragment::SharedPointer& substruct);

        CDPL_PHARM_API void clearSubstructure(Feature& feature);

        CDPL_PHARM_API bool hasSubstructure(const Feature& feature);

        /**
         * \since 1.3
         */
        CDPL_PHARM_API const std::string& getEnvironmentResidueInfo(const Feature& feature);

        CDPL_PHARM_API void setEnvironmentResidueInfo(Feature& feature, const std::string& res_info);

        CDPL_PHARM_API void clearEnvironmentResidueInfo(Feature& feature);

        CDPL_PHARM_API bool hasEnvironmentResidueInfo(const Feature& feature);
        

        CDPL_PHARM_API bool getDisabledFlag(const Feature& feature);

        CDPL_PHARM_API void setDisabledFlag(Feature& feature, bool flag);

        CDPL_PHARM_API void clearDisabledFlag(Feature& feature);

        CDPL_PHARM_API bool hasDisabledFlag(const Feature& feature);


        CDPL_PHARM_API bool getOptionalFlag(const Feature& feature);

        CDPL_PHARM_API void setOptionalFlag(Feature& feature, bool flag);

        CDPL_PHARM_API void clearOptionalFlag(Feature& feature);

        CDPL_PHARM_API bool hasOptionalFlag(const Feature& feature);


        CDPL_PHARM_API double getHydrophobicity(const Feature& feature);

        CDPL_PHARM_API void setHydrophobicity(Feature& feature, double hyd);

        CDPL_PHARM_API void clearHydrophobicity(Feature& feature);

        CDPL_PHARM_API bool hasHydrophobicity(const Feature& feature);
        
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREFUNCTIONS_HPP
