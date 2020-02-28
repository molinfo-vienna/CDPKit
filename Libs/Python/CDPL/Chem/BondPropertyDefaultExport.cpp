/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondPropertyDefaultExport.cpp 
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

#include "CDPL/Chem/BondPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct BondPropertyDefault {};
}


void CDPLPythonChem::exportBondPropertyDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<BondPropertyDefault, boost::noncopyable>("BondPropertyDefault", python::no_init)
		.def_readonly("ORDER", &Chem::BondPropertyDefault::ORDER)
		.def_readonly("SYBYL_TYPE", &Chem::BondPropertyDefault::SYBYL_TYPE)
		.def_readonly("DIRECTION", &Chem::BondPropertyDefault::DIRECTION)
		.def_readonly("STEREO_2D_FLAG", &Chem::BondPropertyDefault::STEREO_2D_FLAG)
		.def_readonly("STEREO_DESCRIPTOR", &Chem::BondPropertyDefault::STEREO_DESCRIPTOR)
		.def_readonly("REACTION_CENTER_STATUS", &Chem::BondPropertyDefault::REACTION_CENTER_STATUS)
		.def_readonly("MATCH_CONSTRAINTS", &Chem::BondPropertyDefault::MATCH_CONSTRAINTS);
}
