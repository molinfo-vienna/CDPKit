/* 
 * CDFFormatData.hpp
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


#ifndef CDPL_PHARM_CDFFORMATDATA_HPP
#define CDPL_PHARM_CDFFORMATDATA_HPP

#include <cstdint>

#include "CDPL/Internal/CDFFormatData.hpp"


namespace CDPL
{

    namespace Pharm
    {

        namespace CDF
        {

            using namespace Internal::CDF;

            typedef std::uint32_t UIntType;
            typedef std::uint8_t  BoolType;

            constexpr std::uint8_t PHARMACOPHORE_RECORD_ID = 3;

            constexpr std::uint8_t CURR_FORMAT_VERSION = 1;

            namespace FeatureProperty
            {

                constexpr unsigned int TYPE           = 1;
                constexpr unsigned int COORDINATES_3D = 2;
                constexpr unsigned int GEOMETRY       = 3;
                constexpr unsigned int LENGTH         = 4;
                constexpr unsigned int ORIENTATION    = 5;
                constexpr unsigned int TOLERANCE      = 6;
                constexpr unsigned int DISABLED_FLAG  = 7;
                constexpr unsigned int OPTIONAL_FLAG  = 8;
                constexpr unsigned int HYDROPHOBICITY = 9;
                constexpr unsigned int WEIGHT         = 10;
            } // namespace FeatureProperty

            namespace PharmacophoreProperty
            {

                constexpr unsigned int NAME = 1;
            }
        } // namespace CDF
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_CDFFORMATDATA_HPP
