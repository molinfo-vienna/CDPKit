/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOL2FormatData.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_CHEM_MOL2FORMATDATA_HPP
#define CDPL_CHEM_MOL2FORMATDATA_HPP

#include <cstddef>
#include <string>


namespace CDPL
{

	namespace Chem
	{
		
		namespace MOL2
		{
		
			const char END_OF_LINE          = '\n';
			const char COMMENT_PREFIX       = '#';
			const char LINE_CONT_MARKER     = '\\';

			const std::string EMPTY_FIELD   = "****";

			const std::string MOLECULE_RTI  = "@<TRIPOS>MOLECULE";
			const std::string ATOM_RTI      = "@<TRIPOS>ATOM";
			const std::string BOND_RTI      = "@<TRIPOS>BOND";

			namespace MoleculeType
			{

				const std::string SMALL        = "SMALL";
				const std::string BIOPOLYMER   = "BIOPOLYMER";
				const std::string PROTEIN      = "PROTEIN";
				const std::string NUCLEIC_ACID = "NUCLEIC_ACID";
				const std::string SACCHARIDE   = "SACCHARIDE";
			}

			namespace ChargeType
			{

				const std::string NO_CHARGES   = "NO_CHARGES";
				const std::string DEL_RE       = "DEL_RE";
				const std::string GASTEIGER    = "GASTEIGER";
				const std::string GAST_HUCK    = "GAST_HUCK";
				const std::string HUCKEL       = "HUCKEL";
				const std::string PULLMAN      = "PULLMAN"; 
				const std::string GAUSS80      = "GAUSS80_CHARGES"; 
				const std::string AMPAC        = "AMPAC_CHARGES";
				const std::string MULLIKEN     = "MULLIKEN_CHARGES"; 
				const std::string DICT         = "DICT_CHARGES"; 
				const std::string MMFF94       = "MMFF94_CHARGES";
				const std::string USER         = "USER_CHARGES";
			}
		}
	}
}

#endif // CDPL_CHEM_MOL2FORMATDATA_HPP
