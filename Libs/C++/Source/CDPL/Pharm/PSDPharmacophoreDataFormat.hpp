/* 
 * PSDPharmacophoreDataFormat.hpp
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


#ifndef CDPL_PHARM_PSDPHARMACOPHOREDATAFORMAT_HPP
#define CDPL_PHARM_PSDPHARMACOPHOREDATAFORMAT_HPP

#include <cstdint>


namespace CDPL
{

    namespace Pharm
    {

        namespace PSDPharmacophoreDataFormat
        {

            constexpr std::uint8_t FORMAT_ID = 'P';

            constexpr std::uint8_t CURR_VERSION = 0;
            constexpr std::uint8_t VERSION_MASK = 0x0f;

            constexpr std::uint8_t NAME_LENGTH_BYTE_COUNT_MASK  = 0xf0;
            constexpr unsigned int NAME_LENGTH_BYTE_COUNT_SHIFT = 4;

            constexpr std::uint8_t FEATURE_COUNT_BYTE_COUNT_MASK  = 0x0f;
            
            constexpr std::uint8_t FEATURE_X_POS_TRANSLATION_FLAG  = 0x10;
            constexpr std::uint8_t FEATURE_Y_POS_TRANSLATION_FLAG  = 0x20;
            constexpr std::uint8_t FEATURE_Z_POS_TRANSLATION_FLAG  = 0x40;
            constexpr std::uint8_t FEATURE_POS_SCALING_FACTOR_FLAG = 0x80;

            namespace Feature
            {

                constexpr std::uint8_t TYPE_FLAG           = 0x01;
                constexpr std::uint8_t GEOMETRY_FLAG       = 0x02;
                constexpr std::uint8_t POSITION_FLAG       = 0x04;
                constexpr std::uint8_t ORIENTATION_FLAG    = 0x08;
                constexpr std::uint8_t TOLERANCE_FLAG      = 0x10;
                constexpr std::uint8_t LENGTH_FLAG         = 0x20;
                constexpr std::uint8_t WEIGHT_FLAG         = 0x40;
                constexpr std::uint8_t HYDROPHOBICITY_FLAG = 0x80;

                constexpr std::uint8_t TYPE_MASK = 0x0f;

                constexpr std::uint8_t GEOMETRY_MASK  = 0xf0;
                constexpr unsigned int GEOMETRY_SHIFT = 4;

                constexpr unsigned int POSITION_PRECISION       = 10;
                constexpr unsigned int ORIENTATION_PRECISION    = 14;
                constexpr unsigned int TOLERANCE_PRECISION      = 11;
                constexpr unsigned int LENGTH_PRECISION         = 11;
                constexpr unsigned int WEIGHT_PRECISION         = 11;
                constexpr unsigned int HYDROPHOBICITY_PRECISION = 11;
            } // namespace Feature
        } // namespace PSDPharmacophoreDataFormat
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDPHARMACOPHOREDATAFORMAT_HPP
