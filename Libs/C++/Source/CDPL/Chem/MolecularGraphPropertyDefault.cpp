/* 
 * MolecularGraphPropertyDefault.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/MolecularGraphPropertyDefault.hpp"
#include "CDPL/Chem/MDLDataFormatVersion.hpp"
#include "CDPL/Chem/MOL2MoleculeType.hpp"
#include "CDPL/Chem/MOL2ChargeType.hpp"


namespace CDPL
{

	namespace Chem
	{

		namespace MolecularGraphPropertyDefault
		{

			const std::string NAME                                     = "";
			const double STOICHIOMETRIC_NUMBER                         = 1.0;
			const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS = MatchConstraintList::SharedPointer(new MatchConstraintList());
			const unsigned int MDL_CTAB_VERSION                        = MDLDataFormatVersion::UNDEF;
			const std::string MDL_COMMENT                              = "";
			const std::string MDL_PROGRAM_NAME                         = "CDPL";
			const std::string MDL_USER_INITIALS                        = "";
			const std::size_t MDL_DIMENSIONALITY                       = 0;
			const double MDL_ENERGY                                    = 0.0 ;
			const bool MDL_CHIRAL_FLAG                                 = false;
			const long MDL_SCALING_FACTOR1                             = 1;
			const double MDL_SCALING_FACTOR2                           = 1;
			const unsigned int MOL2_MOLECULE_TYPE                      = MOL2MoleculeType::UNKNOWN;
			const unsigned int MOL2_CHARGE_TYPE                        = MOL2ChargeType::UNKNOWN;
		}

		void initMolecularGraphPropertyDefaults() {}
	}
}
