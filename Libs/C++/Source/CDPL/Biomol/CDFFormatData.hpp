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


#ifndef CDPL_BIOMOL_CDFFORMATDATA_HPP
#define CDPL_BIOMOL_CDFFORMATDATA_HPP

#include "CDPL/Chem/CDFFormatData.hpp"


namespace CDPL
{

    namespace Biomol
    {

		namespace CDF
		{
			
			using namespace Chem::CDF;

			typedef Base::int8 CharType;

			namespace AtomProperty
			{

				const unsigned int PROPERTY_HANDLER_ID       = 1;

				const unsigned int RESIDUE_ATOM_NAME         = 1;
				const unsigned int RESIDUE_ALT_ATOM_NAME     = 2;
				const unsigned int RESIDUE_LEAVING_ATOM_FLAG = 3;
				const unsigned int RESIDUE_LINKING_ATOM_FLAG = 4;
				const unsigned int RESIDUE_CODE              = 5;
				const unsigned int RESIDUE_SEQUENCE_NUMBER   = 6;
				const unsigned int RESIDUE_INSERTION_CODE    = 7;
				const unsigned int HETERO_ATOM_FLAG          = 8;
				const unsigned int CHAIN_ID                  = 9;
				const unsigned int MODEL_NUMBER              = 10;
				const unsigned int SERIAL_NUMBER             = 11;
			}

			namespace MolecularGraphProperty
			{
				
				const unsigned int PROPERTY_HANDLER_ID       = 1;

				const unsigned int RESIDUE_CODE              = 1;
				const unsigned int RESIDUE_SEQUENCE_NUMBER   = 2;
				const unsigned int RESIDUE_INSERTION_CODE    = 3;
				const unsigned int CHAIN_ID                  = 4;
				const unsigned int MODEL_NUMBER              = 5;
			}
		}
    }
}

#endif // CDPL_BIOMOL_CDFFORMATDATA_HPP
