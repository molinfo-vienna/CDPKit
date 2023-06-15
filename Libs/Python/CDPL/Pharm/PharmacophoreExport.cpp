/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreExport.cpp 
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


#include <memory>

#include <boost/python.hpp>

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "FeatureContainerVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	struct PharmacophoreWrapper : CDPL::Pharm::Pharmacophore, boost::python::wrapper<CDPL::Pharm::Pharmacophore> 
	{

		typedef std::shared_ptr<PharmacophoreWrapper> SharedPointer;

		FEATURECONTAINER_IMPL() 

		void clear() {
			this->get_override("clear")();
		}

		CDPL::Pharm::Feature& addFeature() {
			return this->get_override("addFeature")();
		}

		void removeFeature(std::size_t idx) {
			this->get_override("removeFeature")(idx);
		}

		void copy(const Pharmacophore& pharm) {
			this->get_override("copy")(boost::ref(pharm));
		}

		void copy(const FeatureContainer& cntnr) {
			this->get_override("copy")(boost::ref(cntnr));
		}
	
		void append(const Pharmacophore& pharm) {
			this->get_override("append")(boost::ref(pharm));
		}

		void append(const FeatureContainer& cntnr) {
			this->get_override("append")(boost::ref(cntnr));
		}

		void remove(const FeatureContainer& cntnr) {
			this->get_override("remove")(boost::ref(cntnr));
		}

		Pharmacophore::SharedPointer clone() const {
			return this->get_override("clone")();
		}
	};
}


void CDPLPythonPharm::exportPharmacophore()
{
	using namespace boost;
	using namespace CDPL;

	void (Pharm::Pharmacophore::*removeFeatureFunc)(std::size_t) = &Pharm::Pharmacophore::removeFeature;

	void (Pharm::Pharmacophore::*copyPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::copy;
	void (Pharm::Pharmacophore::*copyFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::copy;

	void (Pharm::Pharmacophore::*appendPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::append;
	void (Pharm::Pharmacophore::*appendFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::append;

	Pharm::Pharmacophore& (Pharm::Pharmacophore::*assignPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::operator=;
	Pharm::Pharmacophore& (Pharm::Pharmacophore::*assignFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::operator=;

	Pharm::Pharmacophore& (Pharm::Pharmacophore::*addPharmFunc)(const Pharm::Pharmacophore&) = &Pharm::Pharmacophore::operator+=;
	Pharm::Pharmacophore& (Pharm::Pharmacophore::*addFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::Pharmacophore::operator+=;

	python::scope scope = python::class_<PharmacophoreWrapper, PharmacophoreWrapper::SharedPointer, 
										 python::bases<Pharm::FeatureContainer>,
										 boost::noncopyable>("Pharmacophore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("clear",  python::pure_virtual(&Pharm::Pharmacophore::clear), python::arg("self"))
		.def("addFeature",  python::pure_virtual(&Pharm::Pharmacophore::addFeature), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("removeFeature", python::pure_virtual(removeFeatureFunc), (python::arg("self"), python::arg("idx")))
		.def("copy", python::pure_virtual(copyPharmFunc), (python::arg("self"), python::arg("pharm")))
		.def("copy", python::pure_virtual(copyFtrContainerFunc), (python::arg("self"), python::arg("cntnr")))
		.def("append", python::pure_virtual(appendPharmFunc), (python::arg("self"), python::arg("pharm")))
		.def("append", python::pure_virtual(appendFtrContainerFunc), (python::arg("self"), python::arg("cntnr")))
		.def("remove", python::pure_virtual(&Pharm::Pharmacophore::remove), (python::arg("self"), python::arg("cntnr")))
		.def("assign", assignPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
		.def("assign", assignFtrContainerFunc, (python::arg("self"), python::arg("cntnr")), python::return_self<>())
		.def("clone", python::pure_virtual(&Pharm::Pharmacophore::clone), python::arg("self"))
		.def("__iadd__", addPharmFunc, (python::arg("self"), python::arg("pharm")), python::return_self<>())
		.def("__iadd__", addFtrContainerFunc, (python::arg("self"), python::arg("cntnr")), python::return_self<>())
		.def("__isub__", &Pharm::Pharmacophore::operator-=, (python::arg("self"), python::arg("cntnr")), python::return_self<>())
		.def("__delitem__", removeFeatureFunc, (python::arg("self"), python::arg("idx")))
		.def(FeatureContainerVirtualFunctionsVisitor<PharmacophoreWrapper>())
		.def(FeatureContainerSpecialFunctionsVisitor(false))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor(true));

	python::register_ptr_to_python<Pharm::Pharmacophore::SharedPointer>();
}
