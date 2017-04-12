/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueDictionaryExport.cpp 
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

#include "CDPL/Biomol/ResidueDictionary.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	boost::python::list getEntries(const CDPL::Biomol::ResidueDictionary& dict)
	{
		using namespace CDPL;
		using namespace Biomol;

		boost::python::list entries;

		for (ResidueDictionary::ConstEntryIterator it = dict.getEntriesBegin(), end = dict.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
	}

	void setDictionary(boost::python::object dict_obj)
	{	
		using namespace boost;
		using namespace CDPL;

		static python::handle<> dict_handle;

		if (dict_obj.ptr() == Py_None) {
			Biomol::ResidueDictionary::set(0);
			dict_handle = python::handle<>();
			return;
		}

		Biomol::ResidueDictionary::set(python::extract<const CDPL::Biomol::ResidueDictionary*>(dict_obj));
		dict_handle = python::handle<>(python::borrowed(dict_obj.ptr()));
	}
}


void CDPLPythonBiomol::exportResidueDictionary()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<Biomol::ResidueDictionary, Biomol::ResidueDictionary::SharedPointer>("ResidueDictionary", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Biomol::ResidueDictionary&>((python::arg("self"), python::arg("dict"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::ResidueDictionary>())	
		.def("addEntry", &Biomol::ResidueDictionary::addEntry, (python::arg("self"), python::arg("entry"))) 
		.def("containsEntry", &Biomol::ResidueDictionary::containsEntry, (python::arg("self"), python::arg("code"))) 
		.def("removeEntry", &Biomol::ResidueDictionary::removeEntry, (python::arg("self"), python::arg("code"))) 
		.def("getEntry", &Biomol::ResidueDictionary::getEntry, (python::arg("self"), python::arg("code")),
			 python::return_internal_reference<>()) 
		.def("clear", &Biomol::ResidueDictionary::clear, python::arg("self")) 
		.def("getNumEntries", &Biomol::ResidueDictionary::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("loadDefaultEntries", &Biomol::ResidueDictionary::loadDefaultEntries, python::arg("self")) 
		.def("assign", CDPLPythonBase::copyAssOp(&Biomol::ResidueDictionary::operator=), (python::arg("self"), python::arg("dict")), python::return_self<>())
		.add_property("numEntries", &Biomol::ResidueDictionary::getNumEntries)
		.add_property("entries", &getEntries)
		.def("set", &setDictionary, python::arg("dict"))
		.staticmethod("set")
		.def("get", &Biomol::ResidueDictionary::get, python::return_value_policy<python::reference_existing_object>())
		.staticmethod("get")
		.def("getReplacedCode", &Biomol::ResidueDictionary::getReplacedCode, python::arg("code"),
			 python::return_value_policy<python::copy_const_reference>())
		.staticmethod("getReplacedCode")
		.def("getReplacedByCode", &Biomol::ResidueDictionary::getReplacedByCode, python::arg("code"),
			 python::return_value_policy<python::copy_const_reference>())
		.staticmethod("getReplacedByCode")
		.def("isObsolete", &Biomol::ResidueDictionary::isObsolete, python::arg("code"))
		.staticmethod("isObsolete")
		.def("getName", &Biomol::ResidueDictionary::getName, python::arg("code"),
			 python::return_value_policy<python::copy_const_reference>())
		.staticmethod("getName")
		.def("isStdResidue", &Biomol::ResidueDictionary::isStdResidue, python::arg("code"))
		.staticmethod("isStdResidue")
		.def("getType", &Biomol::ResidueDictionary::getType, python::arg("code"))
		.staticmethod("getType")
		.def("getStructure", &Biomol::ResidueDictionary::getStructure, python::arg("code"))
		.staticmethod("getStructure");

	python::class_<Biomol::ResidueDictionary::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Biomol::ResidueDictionary::Entry&>((python::arg("self"), python::arg("entry"))))
		.def(python::init<const std::string&, const std::string&, const std::string&, bool,
			 const std::string&, unsigned int, const Biomol::ResidueDictionary::Entry::StructureRetrievalFunction&>(
				 (python::arg("self"), python::arg("code"), python::arg("rep_code"), python::arg("rep_by_code"),
				  python::arg("obsolete"), python::arg("name"), python::arg("type"),
				  python::arg("struc_ret_func"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::ResidueDictionary::Entry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Biomol::ResidueDictionary::Entry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getCode", &Biomol::ResidueDictionary::Entry::getCode, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getReplacedCode", &Biomol::ResidueDictionary::Entry::getReplacedCode, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getReplacedByCode", &Biomol::ResidueDictionary::Entry::getReplacedByCode, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getType", &Biomol::ResidueDictionary::Entry::getType, python::arg("self"))
		.def("getName", &Biomol::ResidueDictionary::Entry::getName, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("isObsolete", &Biomol::ResidueDictionary::Entry::isObsolete, python::arg("self"))
		.def("getStructure", &Biomol::ResidueDictionary::Entry::getStructure, python::arg("self"))
		.add_property("code", python::make_function(&Biomol::ResidueDictionary::Entry::getCode,
													python::return_value_policy<python::copy_const_reference>()))
		.add_property("replacedCode", python::make_function(&Biomol::ResidueDictionary::Entry::getReplacedCode,
															python::return_value_policy<python::copy_const_reference>()))
		.add_property("replacedByCode", python::make_function(&Biomol::ResidueDictionary::Entry::getReplacedByCode,
															  python::return_value_policy<python::copy_const_reference>()))
		.add_property("obsolete", &Biomol::ResidueDictionary::Entry::isObsolete)
		.add_property("name", python::make_function(&Biomol::ResidueDictionary::Entry::getName,
													python::return_value_policy<python::copy_const_reference>()))
		.add_property("type", &Biomol::ResidueDictionary::Entry::getType)
		.add_property("structure", &Biomol::ResidueDictionary::Entry::getStructure);
}
