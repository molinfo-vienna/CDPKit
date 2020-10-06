/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFFormatData.hpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Internal/CDFFormatData.hpp"


namespace CDPL
{

    namespace Chem
    {

		namespace CDF
		{
			
			using namespace Internal::CDF;

			typedef Base::uint32 UIntType;
			typedef Base::int32  LongType;
			typedef Base::uint8  BoolType;
			typedef Base::uint8  BondAtomIndexLengthTuple;

			const Base::uint8 MOLECULE_RECORD_ID  = 1;
			const Base::uint8 REACTION_RECORD_ID  = 2;
			const Base::uint8 CURR_FORMAT_VERSION = 1;

			const std::size_t              NUM_BOND_ATOM_INDEX_LENGTH_BITS = 4; 
			const BondAtomIndexLengthTuple BOND_ATOM_INDEX_LENGTH_MASK     = 0xf; 

			const unsigned int  EXTENDED_PROP_LIST = 31;

			namespace AtomProperty
			{

				const unsigned int NAME                     = 1;
				const unsigned int SYMBOL                   = 2;
				const unsigned int TYPE                     = 3;
				const unsigned int FORMAL_CHARGE            = 4;
				const unsigned int ISOTOPE                  = 5;
				const unsigned int RADICAL_TYPE             = 6;
				const unsigned int HYBRIDIZATION            = 7; 
				const unsigned int RING_FLAG                = 8;
				const unsigned int AROMATICITY_FLAG         = 9;
				const unsigned int UNPAIRED_ELECTRON_COUNT  = 10;
				const unsigned int IMPLICIT_HYDROGEN_COUNT  = 11;
				const unsigned int COORDINATES_2D           = 12;
				const unsigned int COORDINATES_3D           = 13;
				const unsigned int COORDINATES_3D_ARRAY     = 14;
				const unsigned int STEREO_DESCRIPTOR        = 15;
				const unsigned int CIP_CONFIGURATION        = 16;
				const unsigned int REACTION_CENTER_STATUS   = 17;
				const unsigned int ATOM_MAPPING_ID          = 18;
				const unsigned int MATCH_CONSTRAINTS        = 19;
				const unsigned int COMPONENT_GROUP_ID       = 20;
			}

			namespace BondProperty
			{
				
				const unsigned int ORDER                    = 1;
				const unsigned int RING_FLAG                = 2;
				const unsigned int AROMATICITY_FLAG         = 3;
				const unsigned int STEREO_DESCRIPTOR        = 4;
				const unsigned int CIP_CONFIGURATION        = 5;
				const unsigned int DIRECTION                = 6;
				const unsigned int STEREO_2D_FLAG           = 7;
				const unsigned int REACTION_CENTER_STATUS   = 8;
				const unsigned int MATCH_CONSTRAINTS        = 9;
			}

			namespace MolecularGraphProperty
			{
				
				const unsigned int NAME                     = 1; 
				const unsigned int MATCH_CONSTRAINTS        = 2;
				const unsigned int STOICHIOMETRIC_NUMBER    = 3;
				const unsigned int CONFORMATION_INDEX       = 4;
				const unsigned int STRUCTURE_DATA           = 5;
				const unsigned int HASH_CODE                = 6;
				const unsigned int CONFORMER_ENERGIES       = 7;
				const unsigned int SSSR                     = 8;
			}

			namespace ReactionProperty
			{
				
				const unsigned int NAME                     = 1; 
				const unsigned int MATCH_CONSTRAINTS        = 2;
				const unsigned int REACTION_DATA            = 3;
			}
		}
    }
}

#endif // CDPL_CHEM_CDFFORMATDATA_HPP
