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
#include "CDPL/Base/Exceptions.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct AtomMapping
	{

		AtomMapping(const CDPL::ConfGen::FragmentLibraryEntry& entry): entry(entry) {}

		std::size_t getNumAtoms() const {
			return entry.getAtomMapping().size();
		}

		const CDPL::Chem::Atom& getAtom(std::size_t idx) const {
			if (idx >= entry.getAtomMapping().size())
				throw CDPL::Base::IndexError("FragmentLibraryEntry.AtomMapping: index out of bounds");

			return *entry.getAtomMapping()[idx];
		}

		const CDPL::ConfGen::FragmentLibraryEntry& entry;
	};

	AtomMapping getAtomMapping(CDPL::ConfGen::FragmentLibraryEntry& entry)
	{
		return AtomMapping(entry);
	}

	struct AtomMappingExport
	{

		AtomMappingExport(const char* name) {
			using namespace boost;

			python::class_<AtomMapping>(name, python::no_init)
				.def("__len__", &AtomMapping::getNumAtoms, python::arg("self"))
				.def("__getitem__", &AtomMapping::getAtom, (python::arg("self"), python::arg("idx")), 
					 python::return_internal_reference<1>());
		}
	};
}


void CDPLPythonConfGen::exportFragmentLibraryEntry()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ConfGen::FragmentLibraryEntry, ConfGen::FragmentLibraryEntry::SharedPointer, 
				   python::bases<Chem::MolecularGraph>, boost::noncopyable> cl("FragmentLibraryEntry", python::no_init);

	python::scope scope = cl;
  
	python::class_<AtomMapping>("AtomMapping", python::no_init)
		.def("__len__", &AtomMapping::getNumAtoms, python::arg("self"))
		.def("__getitem__", &AtomMapping::getAtom, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>());

	cl
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&, const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"), python::arg("parent"))))
		.def(python::init<const ConfGen::FragmentLibraryEntry&>((python::arg("self"), python::arg("entry"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentLibraryEntry>())	
		.def("assign", &ConfGen::FragmentLibraryEntry::operator=, (python::arg("self"), python::arg("entry")),
			 python::return_self<>())
		.def("create", &ConfGen::FragmentLibraryEntry::create, (python::arg("self"), python::arg("molgraph"), python::arg("parent")))
		.def("getHashCode", &ConfGen::FragmentLibraryEntry::getHashCode, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("clear", &ConfGen::FragmentLibraryEntry::clear, python::arg("self"))
		.def("getAtomMapping", &getAtomMapping, python::arg("self"), python::with_custodian_and_ward_postcall<0, 1>())
		.add_property("hashCode", python::make_function(&ConfGen::FragmentLibraryEntry::getHashCode,
														python::return_value_policy<python::copy_const_reference>()))
		.add_property("atomMapping", python::make_function(&getAtomMapping,
														   python::with_custodian_and_ward_postcall<0, 1>()));
}
