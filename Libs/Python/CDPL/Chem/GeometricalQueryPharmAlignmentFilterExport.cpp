/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalQueryPharmAlignmentFilterExport.cpp 
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

#include "CDPL/Chem/GeometricalQueryPharmAlignmentFilter.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportGeometricalQueryPharmAlignmentFilter()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::GeometricalQueryPharmAlignmentFilter, 
		   boost::noncopyable>("GeometricalQueryPharmAlignmentFilter", python::no_init)
	.def(python::init<const Chem::GeometricalQueryPharmAlignmentFilter&>(
		 (python::arg("self"), python::arg("filter"))))
	.def(python::init<const Chem::Pharmacophore&, std::size_t>(
		 (python::arg("self"), python::arg("query"), python::arg("max_omtd_ftrs"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::GeometricalQueryPharmAlignmentFilter>())
	.def("assign", &Chem::GeometricalQueryPharmAlignmentFilter::operator=, 
	     (python::arg("self"), python::arg("filter")), python::return_self<>())
	.def("__call__", &Chem::GeometricalQueryPharmAlignmentFilter::operator(),
	     (python::arg("self"), python::arg("mapping")));
}
