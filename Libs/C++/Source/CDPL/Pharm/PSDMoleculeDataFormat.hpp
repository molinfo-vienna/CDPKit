/* 
 * PSDMoleculeDataFormat.hpp
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


#ifndef CDPL_PHARM_PSDMOLECULEDATAFORMAT_HPP
#define CDPL_PHARM_PSDMOLECULEDATAFORMAT_HPP

#include <cstdint>


namespace CDPL
{

    namespace Pharm
    {

        namespace PSDMoleculeDataFormat
        {

            constexpr std::uint8_t FORMAT_ID = 'M';

            constexpr std::uint8_t CURR_VERSION = 0;
            constexpr std::uint8_t VERSION_MASK = 0x0f;

            constexpr std::uint8_t NAME_LENGTH_BYTE_COUNT_MASK  = 0xf0;
            constexpr unsigned int NAME_LENGTH_BYTE_COUNT_SHIFT = 4;

            constexpr unsigned int SD_HEADER_LENGTH_BYTE_COUNT_MASK = 0x0f;
            constexpr unsigned int SD_DATA_LENGTH_BYTE_COUNT_MASK   = 0xf0;
            constexpr unsigned int SD_DATA_LENGTH_BYTE_COUNT_SHIFT  = 4;

            constexpr std::uint8_t ATOM_3D_COORDS_MARKER = 0xff;

            constexpr unsigned int COORDS_PRECISION = 10;

            constexpr std::uint8_t X_COORD_TRANSLATION_FLAG   = 0x10;
            constexpr std::uint8_t Y_COORD_TRANSLATION_FLAG   = 0x20;
            constexpr std::uint8_t Z_COORD_TRANSLATION_FLAG   = 0x40;
            constexpr std::uint8_t COORDS_SCALING_FACTOR_FLAG = 0x80;

            namespace Atom
            {

                constexpr std::uint8_t TYPE_FLAG                = 0x01;
                constexpr std::uint8_t SYMBOL_FLAG              = 0x02;
                constexpr std::uint8_t FORMAL_CHARGE_FLAG       = 0x04;
                constexpr std::uint8_t UNPAIRED_ELEC_COUNT_FLAG = 0x08;
                constexpr std::uint8_t STEREO_DESCRIPTOR_FLAG   = 0x10;
            }

            namespace Bond
            {

                constexpr std::uint8_t ORDER_FLAG             = 0x01;
                constexpr std::uint8_t STEREO_DESCRIPTOR_FLAG = 0x02;

                constexpr unsigned int ATOM1_INDEX_BYTE_COUNT_MASK  = 0x0f;
                constexpr unsigned int ATOM2_INDEX_BYTE_COUNT_MASK  = 0xf0;
                constexpr unsigned int ATOM2_INDEX_BYTE_COUNT_SHIFT = 4;
            }
        } // namespace PSDMoleculeDataFormat
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDMOLECULEDATAFORMAT_HPP
