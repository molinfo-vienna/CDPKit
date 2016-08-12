/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MDLDataBlockExport.cpp 
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

#include "CDPL/Chem/MDLDataBlock.hpp"

#include "Util/ArrayVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportMDLDataBlock()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::MDLDataBlockEntry>("MDLDataBlockEntry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MDLDataBlockEntry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, const std::string&>((python::arg("self"), python::arg("header"),
																   python::arg("data"))))
		.def("assign", &Chem::MDLDataBlockEntry::operator=, (python::arg("self"), python::arg("entry")),
			 python::return_self<>())
		.def("getHeader", &Chem::MDLDataBlockEntry::getHeader, python::arg("self"),  
			 python::return_value_policy<python::copy_const_reference>())
		.def("setHeader", &Chem::MDLDataBlockEntry::setHeader, (python::arg("self"), python::arg("header")))
		.def("getData", &Chem::MDLDataBlockEntry::getData, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setData", &Chem::MDLDataBlockEntry::setData, (python::arg("self"), python::arg("data")))
		.def("__eq__", &Chem::MDLDataBlockEntry::operator==, (python::arg("self"), python::arg("entry")))
		.def("__ne__", &Chem::MDLDataBlockEntry::operator!=, (python::arg("self"), python::arg("entry")))
		.add_property("header", python::make_function(&Chem::MDLDataBlockEntry::getHeader, 
													  python::return_value_policy<python::copy_const_reference>()),
					  &Chem::MDLDataBlockEntry::setHeader)
		.add_property("data", python::make_function(&Chem::MDLDataBlockEntry::getData, 
													  python::return_value_policy<python::copy_const_reference>()),
					  &Chem::MDLDataBlockEntry::setData);

	python::class_<Chem::MDLDataBlock, Chem::MDLDataBlock::SharedPointer>("MDLDataBlock", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MDLDataBlock&>((python::arg("self"), python::arg("data_block"))))
		.def(CDPLPythonUtil::ArrayVisitor<Chem::MDLDataBlock, 
			 python::return_internal_reference<>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("__eq__", &Chem::MDLDataBlock::operator==, (python::arg("self"), python::arg("data_block")))
		.def("__ne__", &Chem::MDLDataBlock::operator!=, (python::arg("self"), python::arg("data_block")));
}
