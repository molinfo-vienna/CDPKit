/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureExport.cpp 
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

#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct FeatureWrapper : CDPL::Chem::Feature, boost::python::wrapper<CDPL::Chem::Feature> 
    {

		PROPERTYCONTAINER_IMPL(FeatureWrapper) 

		const CDPL::Chem::Pharmacophore& getPharmacophore() const {
			return this->get_override("getPharmacophore")();
		}

		CDPL::Chem::Pharmacophore& getPharmacophore() {
			return this->get_override("getPharmacophore")();
		}

		std::size_t getIndex() const {
			return this->get_override("getIndex")();
		}

		static CDPL::Chem::Feature& assign(CDPL::Chem::Feature& self, CDPL::Chem::Feature& feature) {
			return (self = feature);
		}
    };
}


void CDPLPythonChem::exportFeature()
{
    using namespace boost;
    using namespace CDPL;

    Chem::Pharmacophore& (Chem::Feature::*getPharmacophoreFunc)() = &Chem::Feature::getPharmacophore;

    python::class_<FeatureWrapper, python::bases<Chem::Entity3D>,
				   boost::noncopyable>("Feature", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("getPharmacophore", python::pure_virtual(getPharmacophoreFunc), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("getIndex", python::pure_virtual(&Chem::Feature::getIndex), python::arg("self"))
		.def("assign", &FeatureWrapper::assign, (python::arg("self"), python::arg("feature")), 
			 python::return_self<>())
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<FeatureWrapper>())
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("pharmacophore", python::make_function(getPharmacophoreFunc, 
															 python::return_internal_reference<1>()))
		.add_property("index", &Chem::Feature::getIndex);
}
