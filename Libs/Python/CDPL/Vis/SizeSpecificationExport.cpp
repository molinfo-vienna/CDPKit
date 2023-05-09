/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SizeSpecificationExport.cpp 
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


#include <sstream>
#include <iomanip>

#include <boost/python.hpp>

#include "CDPL/Vis/SizeSpecification.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	std::string toString(const CDPL::Vis::SizeSpecification& spec)
	{
		std::ostringstream oss;

		oss << std::boolalpha;
		oss << "CDPL.Vis.SizeSpecification(value=" << spec.getValue() << ", relative=" << spec.isRelative() << ", in_scaling=" << spec.followsInputScaling() 
			<< ", out_scaling=" << spec.followsOutputScaling() << ')';

		return oss.str();
	}
}


void CDPLPythonVis::exportSizeSpecification()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Vis::SizeSpecification>("SizeSpecification", python::no_init)
		.def(python::init<const Vis::SizeSpecification&>((python::arg("self"), python::arg("spec"))))
		.def(python::init<double, bool, bool, bool>
			 ((python::arg("self"), python::arg("value") = 0.0, python::arg("relative") = false,
			   python::arg("input_scaling") = false, python::arg("output_scaling") = false)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::SizeSpecification>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Vis::SizeSpecification::operator=), (python::arg("self"), python::arg("spec")),
			 python::return_self<>())
		.def("followsInputScaling", &Vis::SizeSpecification::followsInputScaling, python::arg("self"))
		.def("followInputScaling", &Vis::SizeSpecification::followInputScaling, 
			 (python::arg("self"), python::arg("follow")))
		.def("followsOutputScaling", &Vis::SizeSpecification::followsOutputScaling, python::arg("self"))
		.def("followOutputScaling", &Vis::SizeSpecification::followOutputScaling, 
			 (python::arg("self"), python::arg("follow")))
		.def("isRelative" , &Vis::SizeSpecification::isRelative, python::arg("self"))
		.def("setRelative", &Vis::SizeSpecification::setRelative, (python::arg("self"), python::arg("relative")))
		.def("getValue", &Vis::SizeSpecification::getValue, python::arg("self"))
		.def("setValue", &Vis::SizeSpecification::setValue, (python::arg("self"), python::arg("value")))
		.def("__eq__", &Vis::SizeSpecification::operator==, (python::arg("self"), python::arg("spec")))
		.def("__ne__", &Vis::SizeSpecification::operator!=, (python::arg("self"), python::arg("spec")))
		.def("__str__", &toString, python::arg("self"))
		.add_property("inputScaling", &Vis::SizeSpecification::followsInputScaling, 
					  &Vis::SizeSpecification::followInputScaling)
		.add_property("outputScaling", &Vis::SizeSpecification::followsOutputScaling, 
					  &Vis::SizeSpecification::followOutputScaling)
		.add_property("relative", &Vis::SizeSpecification::isRelative, &Vis::SizeSpecification::setRelative)
		.add_property("value", &Vis::SizeSpecification::getValue, &Vis::SizeSpecification::setValue);
}
