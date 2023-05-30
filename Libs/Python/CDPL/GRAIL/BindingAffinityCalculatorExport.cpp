/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BindingAffinityCalculatorExport.cpp 
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

#include "CDPL/GRAIL/BindingAffinityCalculator.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAIL::exportBindingAffinityCalculator()
{
    using namespace boost;
    using namespace CDPL;
  
    python::class_<GRAIL::BindingAffinityCalculator, GRAIL::BindingAffinityCalculator::SharedPointer,
			   boost::noncopyable> cls("BindingAffinityCalculator", python::no_init);

	python::scope scope = cls;

	python::enum_<GRAIL::BindingAffinityCalculator::AffinityMeasure>("AffinityMeasure")
		.value("PKD", GRAIL::BindingAffinityCalculator::PKD)
		.value("PKI", GRAIL::BindingAffinityCalculator::PKI)
		.value("DG", GRAIL::BindingAffinityCalculator::DG)
		.value("PKD_PKI", GRAIL::BindingAffinityCalculator::PKD_PKI)
		.export_values();

	cls
		.def(python::init<>(python::arg("self")))
		.def(python::init<GRAIL::BindingAffinityCalculator::AffinityMeasure>((python::arg("self"), python::arg("measure"))))
		.def(python::init<const GRAIL::BindingAffinityCalculator&>((python::arg("self"), python::arg("calc"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::BindingAffinityCalculator>())
		.def("assign", CDPLPythonBase::copyAssOp(&GRAIL::BindingAffinityCalculator::operator=), 
			 (python::arg("self"), python::arg("calc")), python::return_self<>())
		.def("setAffinityMeasure", &GRAIL::BindingAffinityCalculator::setAffinityMeasure,
			 (python::arg("self"), python::arg("measure")))
		.def("getAffinityMeasure", &GRAIL::BindingAffinityCalculator::getAffinityMeasure,
			 python::arg("self"))
		.def("__call__", &GRAIL::BindingAffinityCalculator::operator(),
			 (python::arg("self"), python::arg("descr")))
		.add_property("affinityMeasure", &GRAIL::BindingAffinityCalculator::getAffinityMeasure,
					  &GRAIL::BindingAffinityCalculator::setAffinityMeasure);
}
