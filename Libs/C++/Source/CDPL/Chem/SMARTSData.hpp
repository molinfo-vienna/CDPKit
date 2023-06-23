/* 
 * SMARTSData.hpp 
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


#ifndef CDPL_CHEM_SMARTSDATA_HPP
#define CDPL_CHEM_SMARTSDATA_HPP

#include <string>


namespace CDPL 
{

	namespace Chem
	{

		namespace SMARTS
		{

			const char REACTION_ROLE_SEPARATOR = '>';
			const char COMPONENT_SEPARATOR     = '.';

			const char GROUPING_PREFIX         = '(';
			const char GROUPING_SUFFIX         = ')';

			const char CLOSURE_NO_PREFIX       = '%';	

			const char NOT_OPERATOR            = '!';
			const char OR_OPERATOR             = ',';
			const char HI_PRECED_AND_OPERATOR  = '&';
			const char LOW_PRECED_AND_OPERATOR = ';';

			const char UNSPEC_STEREO_SUFFIX    = '?';

			namespace AtomExpression
			{

				const char COMPLEX_EXPR_PREFIX      = '['; 
				const char COMPLEX_EXPR_SUFFIX      = ']'; 

				const char RECURSIVE_SMARTS_PREFIX  = '$'; 
				const char RECURSIVE_SMARTS_BEGIN   = '('; 
				const char RECURSIVE_SMARTS_END     = ')'; 

				const char ATOMIC_NUMBER_PREFIX     = '#'; 

				const char ANY_ATOM                 = '*';
				const char ANY_AROMATIC_ATOM        = 'a';
				const char ANY_NON_AROMATIC_ATOM    = 'A';

				const char EXPLICIT_DEGREE_PREFIX   = 'D';

				const char TOTAL_H_COUNT_PREFIX     = 'H';
				const char IMPLICIT_H_COUNT_PREFIX  = 'h';

				const char RING_MEMBERSHIP_PREFIX   = 'R';
				const char RING_SIZE_PREFIX         = 'r';

				const char VALENCE_PREFIX           = 'v';

				const char UNSATURATED_FLAG         = 'u';

				const char CONNECTIVITY_PREFIX      = 'X';
				const char RING_CONNECTIVITY_PREFIX = 'x';

				const char POSITIVE_CHARGE_PREFIX   = '+';
				const char NEGATIVE_CHARGE_PREFIX   = '-';

				const char ATOM_MAPPING_ID_PREFIX   = ':';

				const char CHIRAL_CLASS_PREFIX      = '@';

				const char HYBRIDIZATION_PREFIX     = '^';

				const std::string TETRAHEDRAL_CHIRALITY   = "TH";
				const std::string ALLENE_TYPE_CHIRALITY   = "AL";
				const std::string SQUARE_PLANAR_CHIRALITY = "SP";
				const std::string TRIG_BIPYR_CHIRALITY    = "TB";
				const std::string OCTAHEDRAL_CHIRALITY    = "OH";
			}

			namespace BondExpression
			{

				const char SINGLE_BOND     = '-';
				const char DOUBLE_BOND     = '=';
				const char TRIPLE_BOND     = '#';
				const char AROMATIC_BOND   = ':';
				const char RING_BOND       = '@';
				const char ANY_BOND        = '~';

				const char UP_DIR_FLAG     = '/';
				const char DOWN_DIR_FLAG   = '\\';
			}
		}
	}
}

#endif // CDPL_CHEM_SMARTSDATA_HPP

 
