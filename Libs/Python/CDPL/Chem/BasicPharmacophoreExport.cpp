/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicPharmacophoreExport.cpp 
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

#include "CDPL/Chem/BasicPharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportBasicPharmacophore()
{
    using namespace boost;
    using namespace CDPL;

    void (Chem::BasicPharmacophore::*copyBasicPharmFunc)(const Chem::BasicPharmacophore&) = &Chem::BasicPharmacophore::copy;
    void (Chem::BasicPharmacophore::*copyPharmFunc)(const Chem::Pharmacophore&) = &Chem::BasicPharmacophore::copy;

    void (Chem::BasicPharmacophore::*appendBasicPharmFunc)(const Chem::BasicPharmacophore&) = &Chem::BasicPharmacophore::append;
    void (Chem::BasicPharmacophore::*appendPharmFunc)(const Chem::Pharmacophore&) = &Chem::BasicPharmacophore::append;

    Chem::BasicPharmacophore& (Chem::BasicPharmacophore::*assignBasicPharmFunc)(const Chem::BasicPharmacophore&) = &Chem::BasicPharmacophore::operator=;
    Chem::Pharmacophore& (Chem::Pharmacophore::*assignPharmFunc)(const Chem::Pharmacophore&) = &Chem::Pharmacophore::operator=;

    Chem::BasicPharmacophore& (Chem::BasicPharmacophore::*addBasicPharmFunc)(const Chem::BasicPharmacophore&) = &Chem::BasicPharmacophore::operator+=;
    Chem::Pharmacophore& (Chem::Pharmacophore::*addPharmFunc)(const Chem::Pharmacophore&) = &Chem::Pharmacophore::operator+=;

    python::class_<Chem::BasicPharmacophore, Chem::BasicPharmacophore::SharedPointer, 
		   python::bases<Chem::Pharmacophore> >("BasicPharmacophore", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Chem::BasicPharmacophore&>((python::arg("self"), python::arg("pharm"))))
	.def(python::init<const Chem::Pharmacophore&>((python::arg("self"), python::arg("pharm"))))
	.def("copy", copyBasicPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("copy", copyPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("append", appendBasicPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("append", appendPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("assign", assignBasicPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("assign", assignPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("__iadd__", addBasicPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("__iadd__", addPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>());
}
