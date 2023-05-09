/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SequenceFunctionExport.cpp 
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

#include "FunctionExports.hpp"


namespace
{

    void forEach(PyObject* seq, boost::python::object func)
    {
	using namespace boost;
	
	PyObject *iter = PyObject_GetIter(seq);

	if (!iter) {
	    PyErr_SetString(PyExc_TypeError, "forEach(): Iterable object expected as 1st argument");

	    python::throw_error_already_set();
	}

	python::handle<> iter_handle(iter);
	PyObject *item;

	while ((item = PyIter_Next(iter)))
	    func(python::handle<>(item));
    }

    void forEachPair(PyObject* seq1, PyObject* seq2, boost::python::object func)
    {
	using namespace boost;
	
	PyObject *iter1 = PyObject_GetIter(seq1);

	if (!iter1) {
	    PyErr_SetString(PyExc_TypeError, "forEach(): Iterable object expected as 1st argument");

	    python::throw_error_already_set();
	}

	python::handle<> iter_handle1(iter1);

	PyObject *iter2 = PyObject_GetIter(seq2);

	if (!iter2) {
	    PyErr_SetString(PyExc_TypeError, "forEach(): Iterable object expected as 2nd argument");

	    python::throw_error_already_set();
	}

	python::handle<> iter_handle2(iter2);
	PyObject *item1;
	PyObject *item2;

	while ((item1 = PyIter_Next(iter1)) && (item2 = PyIter_Next(iter2)))
	    func(python::handle<>(item1), python::handle<>(item2));
    }
}


void CDPLPythonUtil::exportSequenceFunctions()
{
    using namespace boost;

    python::def("forEach", &forEach, (python::arg("seq"), python::arg("func")));
    python::def("forEachPair", &forEachPair, (python::arg("seq1"), python::arg("seq2"), python::arg("func")));
}
