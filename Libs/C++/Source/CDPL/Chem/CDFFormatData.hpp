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


#ifndef CDPL_CHEM_CDFFORMATDATA_HPP
#define CDPL_CHEM_CDFFORMATDATA_HPP

#include <cstddef>
#include <cstdint>

#include "CDPL/Internal/CDFFormatData.hpp"


namespace CDPL
{

    namespace Chem
    {

        namespace CDF
        {

            using namespace Internal::CDF;

            typedef std::uint32_t UIntType;
            typedef std::int32_t  LongType;
            typedef std::uint8_t  BoolType;
            typedef std::uint8_t  BondAtomIndexLengthTuple;

            constexpr std::uint8_t MOLECULE_RECORD_ID  = 1;
            constexpr std::uint8_t REACTION_RECORD_ID  = 2;
            constexpr std::uint8_t CURR_FORMAT_VERSION = 1;

            constexpr std::size_t              NUM_BOND_ATOM_INDEX_LENGTH_BITS = 4;
            constexpr BondAtomIndexLengthTuple BOND_ATOM_INDEX_LENGTH_MASK     = 0xf;

            constexpr unsigned int EXTENDED_PROP_LIST = 31;

            namespace AtomProperty
            {

                constexpr unsigned int NAME                    = 1;
                constexpr unsigned int SYMBOL                  = 2;
                constexpr unsigned int TYPE                    = 3;
                constexpr unsigned int FORMAL_CHARGE           = 4;
                constexpr unsigned int ISOTOPE                 = 5;
                constexpr unsigned int RADICAL_TYPE            = 6;
                constexpr unsigned int HYBRIDIZATION           = 7;
                constexpr unsigned int RING_FLAG               = 8;
                constexpr unsigned int AROMATICITY_FLAG        = 9;
                constexpr unsigned int UNPAIRED_ELECTRON_COUNT = 10;
                constexpr unsigned int IMPLICIT_HYDROGEN_COUNT = 11;
                constexpr unsigned int COORDINATES_2D          = 12;
                constexpr unsigned int COORDINATES_3D          = 13;
                constexpr unsigned int COORDINATES_3D_ARRAY    = 14;
                constexpr unsigned int STEREO_DESCRIPTOR       = 15;
                constexpr unsigned int CIP_CONFIGURATION       = 16;
                constexpr unsigned int REACTION_CENTER_STATUS  = 17;
                constexpr unsigned int ATOM_MAPPING_ID         = 18;
                constexpr unsigned int MATCH_CONSTRAINTS       = 19;
                constexpr unsigned int COMPONENT_GROUP_ID      = 20;
            } // namespace AtomProperty

            namespace BondProperty
            {

                constexpr unsigned int ORDER                  = 1;
                constexpr unsigned int RING_FLAG              = 2;
                constexpr unsigned int AROMATICITY_FLAG       = 3;
                constexpr unsigned int STEREO_DESCRIPTOR      = 4;
                constexpr unsigned int CIP_CONFIGURATION      = 5;
                constexpr unsigned int DIRECTION              = 6;
                constexpr unsigned int STEREO_2D_FLAG         = 7;
                constexpr unsigned int REACTION_CENTER_STATUS = 8;
                constexpr unsigned int MATCH_CONSTRAINTS      = 9;
            } // namespace BondProperty

            namespace MolecularGraphProperty
            {

                constexpr unsigned int NAME                  = 1;
                constexpr unsigned int MATCH_CONSTRAINTS     = 2;
                constexpr unsigned int STOICHIOMETRIC_NUMBER = 3;
                constexpr unsigned int CONFORMATION_INDEX    = 4;
                constexpr unsigned int STRUCTURE_DATA        = 5;
                constexpr unsigned int HASH_CODE             = 6;
                constexpr unsigned int CONFORMER_ENERGIES    = 7;
                constexpr unsigned int SSSR                  = 8;
            } // namespace MolecularGraphProperty

            namespace ReactionProperty
            {

                constexpr unsigned int NAME              = 1;
                constexpr unsigned int MATCH_CONSTRAINTS = 2;
                constexpr unsigned int REACTION_DATA     = 3;
            } // namespace ReactionProperty
        } // namespace CDF
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CDFFORMATDATA_HPP
