/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyFlagExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/AtomPropertyFlag.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomPropertyFlag {};
}


void CDPLPythonChem::exportAtomPropertyFlags()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomPropertyFlag, boost::noncopyable>("AtomPropertyFlag", python::no_init)
		.def_readonly("NONE", &Chem::AtomPropertyFlag::NONE)
		.def_readonly("DEFAULT", &Chem::AtomPropertyFlag::DEFAULT)
		.def_readonly("AROMATICITY", &Chem::AtomPropertyFlag::AROMATICITY)
		.def_readonly("TYPE", &Chem::AtomPropertyFlag::TYPE)
		.def_readonly("CIP_CONFIGURATION", &Chem::AtomPropertyFlag::CIP_CONFIGURATION)
		.def_readonly("CONFIGURATION", &Chem::AtomPropertyFlag::CONFIGURATION)
		.def_readonly("FORMAL_CHARGE", &Chem::AtomPropertyFlag::FORMAL_CHARGE)
		.def_readonly("H_COUNT", &Chem::AtomPropertyFlag::H_COUNT)
		.def_readonly("ISOTOPE", &Chem::AtomPropertyFlag::ISOTOPE)
		.def_readonly("SYMBOL", &Chem::AtomPropertyFlag::SYMBOL)
		.def_readonly("TOPOLOGY", &Chem::AtomPropertyFlag::TOPOLOGY)
		.def_readonly("ATOM_MAPPING_ID", &Chem::AtomPropertyFlag::TOPOLOGY);
}
