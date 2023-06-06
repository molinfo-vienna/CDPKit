/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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


#ifndef CDPL_INTERNAL_CDFFORMATDATA_HPP
#define CDPL_INTERNAL_CDFFORMATDATA_HPP

#include <cstddef>
#include <cstdint>


namespace CDPL
{

    namespace Internal
    {

		namespace CDF
		{
			
			typedef std::uint32_t SizeType;
			typedef std::uint8_t  PropertySpec;

			struct Header
			{

				std::uint32_t formatID;
				std::uint8_t  recordTypeID;
				std::uint8_t  recordFormatVersion;
				std::uint64_t recordDataLength;
			};

			const std::size_t   HEADER_SIZE                = 14;
			const std::uint32_t FORMAT_ID                  = 0x4c504443;

			const std::size_t  NUM_PROP_VALUE_LENGTH_BITS = 3; 
			const PropertySpec PROP_VALUE_LENGTH_MASK     = 0x7; 

			const unsigned int PROP_LIST_END              = 0;
		}
    }
}

#endif // CDPL_INTERNAL_CDFFORMATDATA_HPP
