/* 
 * ConformerDataExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/ConformerData.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportConformerData()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::ConformerData, ConfGen::ConformerData::SharedPointer, python::bases<Math::Vector3DArray> >("ConformerData", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::ConformerData&>((python::arg("self"), python::arg("data"))))
		.def(python::init<const Math::Vector3DArray&, double>((python::arg("self"), python::arg("coords"), python::arg("energy") = 0.0)))
		.def("swap", &ConfGen::ConformerData::swap, 
			 (python::arg("self"), python::arg("data")))
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::ConformerData::operator=), 
			 (python::arg("self"), python::arg("data")), python::return_self<>())
		.def("assign", CDPLPythonBase::copyAssOp(&Math::Vector3DArray::operator=), 
			 (python::arg("self"), python::arg("coords")), python::return_self<>())
		.def("getEnergy", &ConfGen::ConformerData::getEnergy, python::arg("self"))
		.def("setEnergy", &ConfGen::ConformerData::setEnergy, (python::arg("self"), python::arg("energy")))
		.add_property("energy", &ConfGen::ConformerData::getEnergy, &ConfGen::ConformerData::setEnergy);
}
