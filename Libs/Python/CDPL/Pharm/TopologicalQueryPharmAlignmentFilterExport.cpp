/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TopologicalQueryPharmAlignmentFilterExport.cpp 
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

#include "CDPL/Pharm/TopologicalQueryPharmAlignmentFilter.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportTopologicalQueryPharmAlignmentFilter()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::TopologicalQueryPharmAlignmentFilter, 
		   boost::noncopyable>("TopologicalQueryPharmAlignmentFilter", python::no_init)
	.def(python::init<const Pharm::TopologicalQueryPharmAlignmentFilter&>(
		 (python::arg("self"), python::arg("filter"))))
	.def(python::init<const Pharm::Pharmacophore&, std::size_t>(
		 (python::arg("self"), python::arg("query"), python::arg("max_omtd_ftrs"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::TopologicalQueryPharmAlignmentFilter>())
	.def("assign", &Pharm::TopologicalQueryPharmAlignmentFilter::operator=, 
	     (python::arg("self"), python::arg("filter")), python::return_self<>())
	.def("__call__", &Pharm::TopologicalQueryPharmAlignmentFilter::operator(),
	     (python::arg("self"), python::arg("mapping")));
}
