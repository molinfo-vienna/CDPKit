/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOL2ChargeTypeExport.cpp 
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

#include "CDPL/Chem/MOL2ChargeType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct MOL2ChargeType {};
}


void CDPLPythonChem::exportMOL2ChargeTypes()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MOL2ChargeType, boost::noncopyable>("MOL2ChargeType", python::no_init)
		.def_readonly("UNKNOWN", &Chem::MOL2ChargeType::UNKNOWN)
	    .def_readonly("NO_CHARGES", &Chem::MOL2ChargeType::NO_CHARGES)
	    .def_readonly("DEL_RE", &Chem::MOL2ChargeType::DEL_RE)
	    .def_readonly("GASTEIGER", &Chem::MOL2ChargeType::GASTEIGER)
	    .def_readonly("GAST_HUCK", &Chem::MOL2ChargeType::GAST_HUCK)
	    .def_readonly("HUCKEL", &Chem::MOL2ChargeType::HUCKEL)
	    .def_readonly("PULLMAN", &Chem::MOL2ChargeType::PULLMAN)
	    .def_readonly("GAUSS80", &Chem::MOL2ChargeType::GAUSS80)
	    .def_readonly("AMPAC", &Chem::MOL2ChargeType::AMPAC)
	    .def_readonly("MULLIKEN", &Chem::MOL2ChargeType::MULLIKEN)
	    .def_readonly("DICT", &Chem::MOL2ChargeType::DICT)
	    .def_readonly("MMFF94", &Chem::MOL2ChargeType::MMFF94)
	    .def_readonly("USER", &Chem::MOL2ChargeType::USER);
}
