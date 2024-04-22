/* 
 * FeaturePropertyDefault.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Pharm/FeaturePropertyDefault.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"


namespace CDPL
{

    namespace Pharm
    {

        namespace FeaturePropertyDefault
        {

            constexpr bool OPTIONAL_FLAG             = false;
            constexpr bool DISABLED_FLAG             = false;

            constexpr double LENGTH                  = 1.0;
            constexpr double TOLERANCE               = 1.0;
            constexpr double WEIGHT                  = 1.0;
            constexpr double HYDROPHOBICITY          = 0.0;

            constexpr unsigned int TYPE              = FeatureType::UNKNOWN;
            constexpr unsigned int GEOMETRY          = FeatureGeometry::UNDEF;
        }

        void initFeaturePropertyDefaults() {}
    }
}
