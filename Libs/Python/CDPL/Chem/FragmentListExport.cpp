/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentListExport.cpp 
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

#include "CDPL/Chem/FragmentList.hpp"

#include "Util/ArrayVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportFragmentList()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::FragmentList, Chem::FragmentList::SharedPointer>("FragmentList", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::FragmentList&>((python::arg("self"), python::arg("list")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonUtil::ArrayVisitor<Chem::FragmentList, 
			 python::return_value_policy<python::copy_non_const_reference, python::with_custodian_and_ward_postcall<0, 1> >, 
			 python::with_custodian_and_ward<1, 2>, python::with_custodian_and_ward<1, 3>, python::with_custodian_and_ward<1, 4> >())
		.def("__eq__", &Chem::FragmentList::operator==, (python::arg("self"), python::arg("list")))
		.def("__ne__", &Chem::FragmentList::operator!=, (python::arg("self"), python::arg("list")));
}
