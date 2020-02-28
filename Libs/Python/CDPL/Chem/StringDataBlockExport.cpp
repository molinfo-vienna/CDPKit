/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StringDataBlockExport.cpp 
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

#include "CDPL/Chem/StringDataBlock.hpp"

#include "Util/ArrayVisitor.hpp"
#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportStringDataBlock()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::StringDataBlockEntry>("StringDataBlockEntry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::StringDataBlockEntry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, const std::string&>((python::arg("self"), python::arg("header"),
																   python::arg("data"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::StringDataBlockEntry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::StringDataBlockEntry::operator=), (python::arg("self"), python::arg("entry")),
			 python::return_self<>())
		.def("getHeader", &Chem::StringDataBlockEntry::getHeader, python::arg("self"),  
			 python::return_value_policy<python::copy_const_reference>())
		.def("setHeader", &Chem::StringDataBlockEntry::setHeader, (python::arg("self"), python::arg("header")))
		.def("getData", &Chem::StringDataBlockEntry::getData, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setData", &Chem::StringDataBlockEntry::setData, (python::arg("self"), python::arg("data")))
		.def("__eq__", &Chem::StringDataBlockEntry::operator==, (python::arg("self"), python::arg("entry")))
		.def("__ne__", &Chem::StringDataBlockEntry::operator!=, (python::arg("self"), python::arg("entry")))
		.add_property("header", python::make_function(&Chem::StringDataBlockEntry::getHeader, 
													  python::return_value_policy<python::copy_const_reference>()),
					  &Chem::StringDataBlockEntry::setHeader)
		.add_property("data", python::make_function(&Chem::StringDataBlockEntry::getData, 
													  python::return_value_policy<python::copy_const_reference>()),
					  &Chem::StringDataBlockEntry::setData);

	python::class_<Chem::StringDataBlock, Chem::StringDataBlock::SharedPointer>("StringDataBlock", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::StringDataBlock&>((python::arg("self"), python::arg("data_block"))))
		.def(CDPLPythonUtil::ArrayVisitor<Chem::StringDataBlock, 
			 python::return_internal_reference<>, python::default_call_policies,
			 python::default_call_policies, python::default_call_policies>())
		.def("addEntry", &Chem::StringDataBlock::addEntry, 
			 (python::arg("self"), python::arg("header"), python::arg("data")))
		.def("__eq__", &Chem::StringDataBlock::operator==, (python::arg("self"), python::arg("data_block")))
		.def("__ne__", &Chem::StringDataBlock::operator!=, (python::arg("self"), python::arg("data_block")));
}
