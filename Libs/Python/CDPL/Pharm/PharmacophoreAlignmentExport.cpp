 /* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreAlignmentExport.cpp 
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

#include "CDPL/Pharm/PharmacophoreAlignment.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/CopyAssOp.hpp"
#include "Chem/SpatialEntityAlignmentExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportPharmacophoreAlignment()
{
    using namespace boost;
    using namespace CDPL;

	CDPLPythonChem::SpatialEntityAlignmentExport<Pharm::Feature>("SpatialFeatureAlignment");

    python::class_<Pharm::PharmacophoreAlignment, python::bases<Chem::SpatialEntityAlignment<Pharm::Feature> >,
				   boost::noncopyable>("PharmacophoreAlignment", python::no_init)
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode"))))
		.def(python::init<const Pharm::PharmacophoreAlignment&>((python::arg("self"), python::arg("alignment")))[python::with_custodian_and_ward<1, 2>()])
		.def("addFeatures", &Pharm::PharmacophoreAlignment::addFeatures, 
			 (python::arg("self"), python::arg("cntnr"), python::arg("first_set")), python::with_custodian_and_ward<1, 2>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::PharmacophoreAlignment::operator=), 
			 (python::arg("self"), python::arg("alignment")), python::return_self<python::with_custodian_and_ward<1, 2> >());
}

