/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * JMEFormatData.hpp 
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


#ifndef CDPL_CHEM_JMEFORMATDATA_HPP
#define CDPL_CHEM_JMEFORMATDATA_HPP

#include <string>
#include <cstddef>


namespace CDPL 
{

	namespace Chem
	{

		namespace JME
		{

			const char REACTION_ROLE_SEPARATOR = '>';
			const char COMPONENT_SEPARATOR     = '|';

			namespace AtomString
			{

				const char ATOM_LIST_SEPARATOR             = ',';
				const char QUERY_FLAGS_SEPARATOR           = ';';
				const char RXN_ATOM_ID_SEPARATOR           = ':';

				const char ATOMIC_NUMBER_PREFIX            = '#';
				const char H_COUNT_PREFIX                  = 'H';
				const char HEAVY_BOND_COUNT_PREFIX         = 'D';

				const char POSITIVE_CHARGE_PREFIX          = '+';
				const char NEGATIVE_CHARGE_PREFIX          = '-';

				const std::size_t MAX_H_COUNT              = 3;
				const std::size_t MAX_HEAVY_BOND_COUNT     = 6;

				const std::string ANY_ATOM_SYMBOL          = "*";
				const std::string ANY_AROM_ATOM_SYMBOL     = "a";
				const std::string ANY_NON_AROM_ATOM_SYMBOL = "A";
				const std::string ANY_NON_C_ATOM_SYMBOL    = "!#6";

				const std::string CHAIN_ATOM_FLAG          = "!R";
				const std::string RING_ATOM_FLAG           = "R";
			}

			namespace BondType
			{

				const int DOWN    = -2;
				const int UP      = -1;
				const int SINGLE  =  1;
				const int DOUBLE  =  2;
				const int TRIPLE  =  3;
			}
		}
	}
}

#endif // CDPL_CHEM_JMEFORMATDATA_HPP

