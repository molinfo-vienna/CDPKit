/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryEntryExport.cpp 
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

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentLibraryEntry()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ConfGen::FragmentLibraryEntry, ConfGen::FragmentLibraryEntry::SharedPointer, 
		python::bases<Chem::MolecularGraph>, boost::noncopyable>("FragmentLibraryEntry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(python::init<const ConfGen::FragmentLibraryEntry&>((python::arg("self"), python::arg("entry"))))
		.def("assign", &ConfGen::FragmentLibraryEntry::operator=, (python::arg("self"), python::arg("entry")),
			 python::return_self<>())
		.def("create", &ConfGen::FragmentLibraryEntry::create, (python::arg("self"), python::arg("molgraph")))
		.def("getHashCode", &ConfGen::FragmentLibraryEntry::getHashCode, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("clear", &ConfGen::FragmentLibraryEntry::clear, python::arg("self"))
		.add_property("hashCode", python::make_function(&ConfGen::FragmentLibraryEntry::getHashCode,
														python::return_value_policy<python::copy_const_reference>()));
}
