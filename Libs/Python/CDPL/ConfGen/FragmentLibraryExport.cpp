/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryExport.cpp 
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

#include "CDPL/ConfGen/FragmentLibrary.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::list getEntries(const CDPL::ConfGen::FragmentLibrary& map)
    {
	using namespace CDPL;
	using namespace ConfGen;

	boost::python::list entries;

	for (FragmentLibrary::ConstEntryIterator it = map.getEntriesBegin(), end = map.getEntriesEnd(); it != end; ++it)
	    entries.append(boost::ref(*it));

	return entries;
    }
}


void CDPLPythonConfGen::exportFragmentLibrary()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ConfGen::FragmentLibrary, 
					 ConfGen::FragmentLibrary::SharedPointer>("FragmentLibrary", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const ConfGen::FragmentLibrary&>((python::arg("self"), python::arg("lib"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentLibrary>())	
	.def("addEntry", &ConfGen::FragmentLibrary::addEntry, 
	     (python::arg("self"), python::arg("frag_hash"), python::arg("frag"))) 
	.def("removeEntry", static_cast<bool (ConfGen::FragmentLibrary::*)(Base::uint64)>(
		 &ConfGen::FragmentLibrary::removeEntry), (python::arg("self"), python::arg("frag_hash"))) 
	.def("getEntry", &ConfGen::FragmentLibrary::getEntry, 
	     (python::arg("self"), python::arg("frag_hash")), python::return_value_policy<python::copy_const_reference>()) 
	.def("clear", &ConfGen::FragmentLibrary::clear, python::arg("self")) 
	.def("getNumEntries", &ConfGen::FragmentLibrary::getNumEntries, python::arg("self")) 
	.def("getEntries", &getEntries, python::arg("self")) 
	.def("load", &ConfGen::FragmentLibrary::load, (python::arg("self"), python::arg("is"))) 
	.def("loadDefaults", &ConfGen::FragmentLibrary::loadDefaults, python::arg("self")) 
	.def("save", &ConfGen::FragmentLibrary::save, (python::arg("self"), python::arg("os"))) 
	.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentLibrary::operator=), 
	     (python::arg("self"), python::arg("lib")), python::return_self<>())
	.add_property("numEntries", &ConfGen::FragmentLibrary::getNumEntries)
	.add_property("entries", python::make_function(&getEntries))
	.def("set", &ConfGen::FragmentLibrary::set, python::arg("map"))
	.staticmethod("set")
	.def("get", &ConfGen::FragmentLibrary::get, python::return_value_policy<python::copy_const_reference>())
	.staticmethod("get");

    python::class_<ConfGen::FragmentLibrary::Entry>("Entry", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const ConfGen::FragmentLibrary::Entry&>((python::arg("self"), python::arg("entry"))))
	.def(python::init<Base::uint64, Chem::MolecularGraph::SharedPointer>(
		 (python::arg("self"), python::arg("frag_hash"), python::arg("frag"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentLibrary::Entry>())	
	.def_readonly("hashCode", &ConfGen::FragmentLibrary::Entry::first)
	.def_readonly("fragment", &ConfGen::FragmentLibrary::Entry::second);
}
