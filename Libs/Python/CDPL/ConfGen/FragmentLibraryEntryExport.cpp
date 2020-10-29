/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryEntryExport.cpp 
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

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentLibraryEntry()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ConfGen::FragmentLibraryEntry, ConfGen::FragmentLibraryEntry::SharedPointer>("FragmentLibraryEntry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::FragmentLibraryEntry&>((python::arg("self"), python::arg("entry"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentLibraryEntry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentLibraryEntry::operator=),
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("setHashCode", &ConfGen::FragmentLibraryEntry::setHashCode, (python::arg("self"), python::arg("hash_code")))
		.def("getHashCode", &ConfGen::FragmentLibraryEntry::getHashCode, python::arg("self"))
		.def("setSMILES", &ConfGen::FragmentLibraryEntry::setSMILES, (python::arg("self"), python::arg("smiles")))
		.def("getSMILES", &ConfGen::FragmentLibraryEntry::getSMILES, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("getNumAtoms", &ConfGen::FragmentLibraryEntry::getNumAtoms, python::arg("self"))
		.def("getNumConformers", &ConfGen::FragmentLibraryEntry::getNumConformers, python::arg("self"))
		.def("clearConformers", &ConfGen::FragmentLibraryEntry::clearConformers, python::arg("self"))
		.def("addConformer", &ConfGen::FragmentLibraryEntry::addConformer, (python::arg("self"), python::arg("conf_data")))
		.def("getConformer", static_cast<ConfGen::ConformerData& (ConfGen::FragmentLibraryEntry::*)(std::size_t idx)>
			 (&ConfGen::FragmentLibraryEntry::getConformer),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", static_cast<ConfGen::ConformerData& (ConfGen::FragmentLibraryEntry::*)(std::size_t idx)>
			 (&ConfGen::FragmentLibraryEntry::getConformer),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.add_property("numConformers", &ConfGen::FragmentLibraryEntry::getNumConformers)
		.add_property("numAtoms", &ConfGen::FragmentLibraryEntry::getNumAtoms)
		.add_property("hashCode", &ConfGen::FragmentLibraryEntry::getHashCode, &ConfGen::FragmentLibraryEntry::setHashCode)
		.add_property("smiles", python::make_function(&ConfGen::FragmentLibraryEntry::getSMILES,
													  python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::FragmentLibraryEntry::setSMILES);
}
