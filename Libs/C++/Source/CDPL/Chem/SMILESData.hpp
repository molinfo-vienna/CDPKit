/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMILESData.hpp 
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


#ifndef CDPL_CHEM_SMILESDATA_HPP
#define CDPL_CHEM_SMILESDATA_HPP

#include <string>


namespace CDPL 
{

	namespace Chem
	{

		namespace SMILES
		{

			const char REACTION_ROLE_SEPARATOR = '>';
			const char COMPONENT_SEPARATOR     = '.';

			const char BRANCH_PREFIX           = '(';
			const char BRANCH_SUFFIX           = ')';

			const char CLOSURE_NO_PREFIX       = '%';	

			namespace AtomString
			{

				const char SPECIAL_ATOM_PREFIX    = '['; 
				const char SPECIAL_ATOM_SUFFIX    = ']'; 

				const char UNDEF_ELEMENT_SYMBOL   = '*';

				const char H_COUNT_PREFIX         = 'H';

				const char POSITIVE_CHARGE_PREFIX = '+';
				const char NEGATIVE_CHARGE_PREFIX = '-';

				const char ATOM_MAPPING_ID_PREFIX = ':';

				const char CHIRAL_CLASS_PREFIX    = '@';

				const std::string TETRAHEDRAL_CHIRALITY   = "TH";
				const std::string ALLENE_TYPE_CHIRALITY   = "AL";
				const std::string SQUARE_PLANAR_CHIRALITY = "SP";
				const std::string TRIG_BIPYR_CHIRALITY    = "TB";
				const std::string OCTAHEDRAL_CHIRALITY    = "OH";
			}

			namespace BondSymbol
			{

				const char SINGLE_BOND   = '-';
				const char DOUBLE_BOND   = '=';
				const char TRIPLE_BOND   = '#';
				const char AROMATIC_BOND = ':';

				const char UP_DIR_FLAG   = '/';
				const char DOWN_DIR_FLAG = '\\';
			}
		}
	}
}

#endif // CDPL_CHEM_SMILESDATA_HPP

 
