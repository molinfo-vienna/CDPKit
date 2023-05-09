/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeaturePropertyExport.cpp 
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

#include "CDPL/Pharm/FeatureProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct FeatureProperty {};
}


void CDPLPythonPharm::exportFeatureProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<FeatureProperty, boost::noncopyable>("FeatureProperty", python::no_init)
	    .def_readonly("TYPE", &Pharm::FeatureProperty::TYPE)
	    .def_readonly("GEOMETRY", &Pharm::FeatureProperty::GEOMETRY)
	    .def_readonly("LENGTH", &Pharm::FeatureProperty::LENGTH)
	    .def_readonly("ORIENTATION", &Pharm::FeatureProperty::ORIENTATION)
	    .def_readonly("TOLERANCE", &Pharm::FeatureProperty::TOLERANCE)
	    .def_readonly("WEIGHT", &Pharm::FeatureProperty::WEIGHT)
	    .def_readonly("SUBSTRUCTURE", &Pharm::FeatureProperty::SUBSTRUCTURE)
	    .def_readonly("DISABLED_FLAG", &Pharm::FeatureProperty::DISABLED_FLAG)
	    .def_readonly("OPTIONAL_FLAG", &Pharm::FeatureProperty::OPTIONAL_FLAG)
	    .def_readonly("HYDROPHOBICITY", &Pharm::FeatureProperty::HYDROPHOBICITY)
		;
}
