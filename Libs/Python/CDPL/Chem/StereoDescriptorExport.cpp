/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StereoDescriptorExport.cpp 
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

#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct ReferenceAtomArray
	{

		ReferenceAtomArray(const CDPL::Chem::StereoDescriptor& descr): descriptor(descr) {}

		std::size_t getNumReferenceAtoms() const {
			return descriptor.getNumReferenceAtoms();
		}

		const CDPL::Chem::Atom& getReferenceAtom(std::size_t idx) const {
			if (idx >= descriptor.getNumReferenceAtoms())
				throw CDPL::Base::IndexError("StereoDescriptor: reference atom index out of bounds");

			return *descriptor.getReferenceAtoms()[idx];
		}

		bool containsReferenceAtom(CDPL::Chem::Atom& atom) const {
			for (std::size_t i = 0; i < descriptor.getNumReferenceAtoms(); i++)
				if (descriptor.getReferenceAtoms()[i] == &atom)
					return true;

			return false;
		}

		const CDPL::Chem::StereoDescriptor& descriptor;
	};

	ReferenceAtomArray createReferenceAtomArray(CDPL::Chem::StereoDescriptor& descr)
	{
		return ReferenceAtomArray(descr);
	}

	unsigned int getPermutationParity3(CDPL::Chem::StereoDescriptor& descr, CDPL::Chem::Atom& a1, 
									   CDPL::Chem::Atom& a2, CDPL::Chem::Atom& a3)
	{
		return descr.getPermutationParity(a1, a2, a3);
	}

	unsigned int getPermutationParity4(CDPL::Chem::StereoDescriptor& descr, CDPL::Chem::Atom& a1, 
									   CDPL::Chem::Atom& a2, CDPL::Chem::Atom& a3, CDPL::Chem::Atom& a4)
	{
		return descr.getPermutationParity(a1, a2, a3, a4);
	}

	bool isValidForAtom(CDPL::Chem::StereoDescriptor& descr, CDPL::Chem::Atom& atom)
	{
		return descr.isValid(atom);
	}

	bool isValidForBond(CDPL::Chem::StereoDescriptor& descr, CDPL::Chem::Atom& bond)
	{
		return descr.isValid(bond);
	}
}

void CDPLPythonChem::exportStereoDescriptor()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<Chem::StereoDescriptor>("StereoDescriptor", python::no_init)
		.def(python::init<unsigned int>((python::arg("self"), python::arg("config"))))
		.def(python::init<const Chem::StereoDescriptor&>((python::arg("self"), python::arg("descr")))
			 [python::with_custodian_and_ward<1, 2>()])

		.def(python::init<unsigned int, Chem::Atom&, Chem::Atom&, Chem::Atom&>((python::arg("self"), python::arg("config"), 
																				python::arg("atom1"), python::arg("atom2"), 
																				python::arg("atom3")))
			 [python::with_custodian_and_ward<1, 3, python::with_custodian_and_ward<1, 4, python::with_custodian_and_ward<1, 5> > >()])
		.def(python::init<unsigned int, Chem::Atom&, Chem::Atom&, Chem::Atom&, Chem::Atom&>((python::arg("self"), python::arg("config"), 
																							 python::arg("atom1"), python::arg("atom2"), 
																							 python::arg("atom3"), python::arg("atom4")))
			 [python::with_custodian_and_ward<1, 3, python::with_custodian_and_ward<1, 4, python::with_custodian_and_ward<1, 5, 
			  python::with_custodian_and_ward<1, 6> > > >()])
		.def("getConfiguration", &Chem::StereoDescriptor::getConfiguration, python::arg("self"))
		.def("setConfiguration", &Chem::StereoDescriptor::setConfiguration, 
			 (python::arg("self"), python::arg("config")))
		.def("getNumReferenceAtoms", &Chem::StereoDescriptor::getNumReferenceAtoms, 
			 python::arg("self"))
		.def("getReferenceAtoms", &createReferenceAtomArray, python::arg("self"), 
			 python::with_custodian_and_ward_postcall<0, 1>())
		.def("assign", &Chem::StereoDescriptor::operator=, 
			 (python::arg("self"), python::arg("descr")), python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("getPermutationParity", &getPermutationParity4, 
			 (python::arg("self"), python::arg("atom1"), python::arg("atom2"), 
			  python::arg("atom3"), python::arg("atom4")))
		.def("getPermutationParity", &getPermutationParity3, 
			 (python::arg("self"), python::arg("atom1"), python::arg("atom2"), 
			  python::arg("atom3")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::StereoDescriptor>())
		.def("isValid", &isValidForAtom, (python::arg("self"), python::arg("atom")))
		.def("isValid", &isValidForBond, (python::arg("self"), python::arg("bond")))
		.add_property("configuration", &Chem::StereoDescriptor::getConfiguration, 
					  &Chem::StereoDescriptor::setConfiguration)  
		.add_property("numReferenceAtoms", &Chem::StereoDescriptor::getNumReferenceAtoms)  
		.add_property("referenceAtoms", python::make_function(&createReferenceAtomArray, 
															  python::with_custodian_and_ward_postcall<0, 1>()));

	python::class_<ReferenceAtomArray>("ReferenceAtomArray", python::no_init)
		.def("__len__", &ReferenceAtomArray::getNumReferenceAtoms, python::arg("self"))
		.def("__contains__", &ReferenceAtomArray::containsReferenceAtom, (python::arg("self"), python::arg("atom")))
		.def("__getitem__", &ReferenceAtomArray::getReferenceAtom, 
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>());
}
