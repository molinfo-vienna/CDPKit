/* 
 * BasicPharmacophoreExport.cpp 
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

#include "CDPL/Pharm/BasicPharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportBasicPharmacophore()
{
    using namespace boost;
    using namespace CDPL;

    void (Pharm::BasicPharmacophore::*copyBasicPharmFunc)(const Pharm::BasicPharmacophore&) = &Pharm::BasicPharmacophore::copy;
    void (Pharm::BasicPharmacophore::*copyPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::copy;
    void (Pharm::BasicPharmacophore::*copyFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::copy;

    void (Pharm::BasicPharmacophore::*appendBasicPharmFunc)(const Pharm::BasicPharmacophore&) = &Pharm::BasicPharmacophore::append;
    void (Pharm::BasicPharmacophore::*appendPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::append;
    void (Pharm::BasicPharmacophore::*appendFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::append;

    Pharm::BasicPharmacophore& (Pharm::BasicPharmacophore::*assignBasicPharmFunc)(const Pharm::BasicPharmacophore&) = &Pharm::BasicPharmacophore::operator=;
    Pharm::Pharmacophore& (Pharm::Pharmacophore::*assignPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::operator=;
    Pharm::Pharmacophore& (Pharm::Pharmacophore::*assignFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::operator=;

    Pharm::BasicPharmacophore& (Pharm::BasicPharmacophore::*addBasicPharmFunc)(const Pharm::BasicPharmacophore&) = &Pharm::BasicPharmacophore::operator+=;
    Pharm::Pharmacophore& (Pharm::Pharmacophore::*addPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::operator+=;
    Pharm::Pharmacophore& (Pharm::Pharmacophore::*addFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::operator+=;

    python::class_<Pharm::BasicPharmacophore, Pharm::BasicPharmacophore::SharedPointer, 
		   python::bases<Pharm::Pharmacophore> >("BasicPharmacophore", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Pharm::BasicPharmacophore&>((python::arg("self"), python::arg("pharm"))))
	.def(python::init<const Pharm::Pharmacophore&>((python::arg("self"), python::arg("pharm"))))
	.def(python::init<const Pharm::FeatureContainer&>((python::arg("self"), python::arg("cntnr"))))
	.def("copy", copyBasicPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("copy", copyPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("copy", copyFtrContainerFunc, (python::arg("self"), python::arg("cntnr")))
	.def("append", appendBasicPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("append", appendPharmFunc, (python::arg("self"), python::arg("pharm")))
	.def("append", appendFtrContainerFunc, (python::arg("self"), python::arg("cntnr")))
	.def("assign", assignBasicPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("assign", assignPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("assign", assignFtrContainerFunc, (python::arg("self"), python::arg("cntnr")), python::return_self<>())
	.def("__iadd__", addBasicPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("__iadd__", addPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
	.def("__iadd__", addFtrContainerFunc, (python::arg("self"), python::arg("cntnr")), python::return_self<>());
}
