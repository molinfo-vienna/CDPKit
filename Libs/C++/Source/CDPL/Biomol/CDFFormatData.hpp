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


#ifndef CDPL_BIOMOL_CDFFORMATDATA_HPP
#define CDPL_BIOMOL_CDFFORMATDATA_HPP

#include <cstdint>

#include "CDPL/Chem/CDFFormatData.hpp"


namespace CDPL
{

    namespace Biomol
    {

        namespace CDF
        {

            using namespace Chem::CDF;

            typedef std::int8_t CharType;

            namespace AtomProperty
            {

                constexpr unsigned int PROPERTY_HANDLER_ID = 1;

                constexpr unsigned int RESIDUE_ATOM_NAME         = 1;
                constexpr unsigned int RESIDUE_ALT_ATOM_NAME     = 2;
                constexpr unsigned int RESIDUE_LEAVING_ATOM_FLAG = 3;
                constexpr unsigned int RESIDUE_LINKING_ATOM_FLAG = 4;
                constexpr unsigned int RESIDUE_CODE              = 5;
                constexpr unsigned int RESIDUE_SEQUENCE_NUMBER   = 6;
                constexpr unsigned int RESIDUE_INSERTION_CODE    = 7;
                constexpr unsigned int HETERO_ATOM_FLAG          = 8;
                constexpr unsigned int CHAIN_ID                  = 9;
                constexpr unsigned int MODEL_NUMBER              = 10;
                constexpr unsigned int SERIAL_NUMBER             = 11;
            } // namespace AtomProperty

            namespace MolecularGraphProperty
            {

                constexpr unsigned int PROPERTY_HANDLER_ID = 1;

                constexpr unsigned int RESIDUE_CODE            = 1;
                constexpr unsigned int RESIDUE_SEQUENCE_NUMBER = 2;
                constexpr unsigned int RESIDUE_INSERTION_CODE  = 3;
                constexpr unsigned int CHAIN_ID                = 4;
                constexpr unsigned int MODEL_NUMBER            = 5;
            } // namespace MolecularGraphProperty
        } // namespace CDF
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_CDFFORMATDATA_HPP
