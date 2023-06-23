/* 
 * RECAPRuleIDExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/RECAPRuleID.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct RECAPRuleID {};
}


void CDPLPythonChem::exportRECAPRuleIDs()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<RECAPRuleID, boost::noncopyable>("RECAPRuleID", python::no_init)
		.def_readonly("NONE", &Chem::RECAPRuleID::NONE)
		.def_readonly("AMIDE", &Chem::RECAPRuleID::AMIDE)
		.def_readonly("ESTER", &Chem::RECAPRuleID::ESTER)
		.def_readonly("AMINE", &Chem::RECAPRuleID::AMINE)
		.def_readonly("UREA", &Chem::RECAPRuleID::UREA)
		.def_readonly("ETHER", &Chem::RECAPRuleID::ETHER)
		.def_readonly("OLEFIN", &Chem::RECAPRuleID::OLEFIN)
		.def_readonly("QUARTERNARY_N", &Chem::RECAPRuleID::QUARTERNARY_N)
		.def_readonly("AROMATIC_N_ALIPHATIC_C", &Chem::RECAPRuleID::AROMATIC_N_ALIPHATIC_C)
		.def_readonly("LACTAM_N_ALIPHATIC_C", &Chem::RECAPRuleID::LACTAM_N_ALIPHATIC_C)
		.def_readonly("AROMATIC_C_AROMATIC_C", &Chem::RECAPRuleID::AROMATIC_C_AROMATIC_C)
		.def_readonly("SULFONAMIDE", &Chem::RECAPRuleID::SULFONAMIDE);
}
