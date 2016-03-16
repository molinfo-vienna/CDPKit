/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmFeaturePropertyExport.cpp 
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

#include "CDPL/Chem/PharmFeatureProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct PharmFeatureProperty {};
}


void CDPLPythonChem::exportPharmFeatureProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<PharmFeatureProperty, boost::noncopyable>("PharmFeatureProperty", python::no_init)
	    .def_readonly("TYPE", &Chem::PharmFeatureProperty::TYPE)
	    .def_readonly("GEOMETRY", &Chem::PharmFeatureProperty::GEOMETRY)
	    .def_readonly("LENGTH", &Chem::PharmFeatureProperty::LENGTH)
	    .def_readonly("ORIENTATION", &Chem::PharmFeatureProperty::ORIENTATION)
	    .def_readonly("TOLERANCE", &Chem::PharmFeatureProperty::TOLERANCE)
	    .def_readonly("SUBSTRUCTURE", &Chem::PharmFeatureProperty::SUBSTRUCTURE)
	    .def_readonly("DISABLED_FLAG", &Chem::PharmFeatureProperty::DISABLED_FLAG)
	    .def_readonly("OPTIONAL_FLAG", &Chem::PharmFeatureProperty::OPTIONAL_FLAG)
		;
}
