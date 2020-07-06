/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BRICSRuleIDExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/BRICSRuleID.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct BRICSRuleID {};
}


void CDPLPythonChem::exportBRICSRuleIDs()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<BRICSRuleID, boost::noncopyable>("BRICSRuleID", python::no_init)
		.def_readonly("NONE", &Chem::BRICSRuleID::NONE)
		.def_readonly("L1_L2", &Chem::BRICSRuleID::L1_L2)
		.def_readonly("L1_L3", &Chem::BRICSRuleID::L1_L3)
		.def_readonly("L1_L10", &Chem::BRICSRuleID::L1_L10)
		.def_readonly("L2_L12", &Chem::BRICSRuleID::L2_L12)
		.def_readonly("L2_L14", &Chem::BRICSRuleID::L2_L14)
		.def_readonly("L2_L16", &Chem::BRICSRuleID::L2_L16)
		.def_readonly("L3_L4", &Chem::BRICSRuleID::L3_L4)
		.def_readonly("L3_L13", &Chem::BRICSRuleID::L3_L13)
		.def_readonly("L3_L14", &Chem::BRICSRuleID::L3_L14)
		.def_readonly("L3_L15", &Chem::BRICSRuleID::L3_L15)
		.def_readonly("L3_L16", &Chem::BRICSRuleID::L3_L16)
		.def_readonly("L4_L5", &Chem::BRICSRuleID::L4_L5)
		.def_readonly("L4_L11", &Chem::BRICSRuleID::L4_L11)
		.def_readonly("L5_L13", &Chem::BRICSRuleID::L5_L13)
		.def_readonly("L5_L15", &Chem::BRICSRuleID::L5_L15)
		.def_readonly("L6_L13", &Chem::BRICSRuleID::L6_L13)
		.def_readonly("L6_L14", &Chem::BRICSRuleID::L6_L14)
		.def_readonly("L6_L15", &Chem::BRICSRuleID::L6_L15)
		.def_readonly("L6_L16", &Chem::BRICSRuleID::L6_L16)
		.def_readonly("L7_L7", &Chem::BRICSRuleID::L7_L7)
		.def_readonly("L8_L9", &Chem::BRICSRuleID::L8_L9)
		.def_readonly("L8_L10", &Chem::BRICSRuleID::L8_L10)
		.def_readonly("L8_L13", &Chem::BRICSRuleID::L8_L13)
		.def_readonly("L8_L14", &Chem::BRICSRuleID::L8_L14)
		.def_readonly("L8_L15", &Chem::BRICSRuleID::L8_L15)
		.def_readonly("L8_L16", &Chem::BRICSRuleID::L8_L16)
		.def_readonly("L9_L15", &Chem::BRICSRuleID::L9_L15)
		.def_readonly("L9_L16", &Chem::BRICSRuleID::L9_L16)
		.def_readonly("L10_L13", &Chem::BRICSRuleID::L10_L13)
		.def_readonly("L10_L14", &Chem::BRICSRuleID::L10_L14)
		.def_readonly("L10_L15", &Chem::BRICSRuleID::L10_L15)
		.def_readonly("L10_L16", &Chem::BRICSRuleID::L10_L16)
		.def_readonly("L11_L13", &Chem::BRICSRuleID::L11_L13)
		.def_readonly("L11_L14", &Chem::BRICSRuleID::L11_L14)
		.def_readonly("L11_L15", &Chem::BRICSRuleID::L11_L15)
		.def_readonly("L11_L16", &Chem::BRICSRuleID::L11_L16)
		.def_readonly("L13_L14", &Chem::BRICSRuleID::L13_L14)
		.def_readonly("L13_L15", &Chem::BRICSRuleID::L13_L15)
		.def_readonly("L13_L16", &Chem::BRICSRuleID::L13_L16)
		.def_readonly("L14_L15", &Chem::BRICSRuleID::L14_L15)
		.def_readonly("L14_L16", &Chem::BRICSRuleID::L14_L16)
		.def_readonly("L15_L16", &Chem::BRICSRuleID::L15_L16);
}
