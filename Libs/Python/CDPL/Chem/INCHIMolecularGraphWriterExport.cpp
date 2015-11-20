/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * INCHIMolecularGraphWriterExport.cpp 
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

#include "CDPL/Chem/INCHIMolecularGraphWriter.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportINCHIMolecularGraphWriter()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::INCHIMolecularGraphWriter, python::bases<Base::DataWriter<Chem::MolecularGraph> >, 
		boost::noncopyable>("INCHIMolecularGraphWriter", python::no_init)
		.def(python::init<std::ostream&>((python::arg("self"), python::arg("os")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def("getReturnCode", &Chem::INCHIMolecularGraphWriter::getReturnCode, python::arg("self"))
		.def("getMessage", &Chem::INCHIMolecularGraphWriter::getMessage, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("getLogOutput", &Chem::INCHIMolecularGraphWriter::getLogOutput, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.add_property("returnCode", &Chem::INCHIMolecularGraphWriter::getReturnCode)
		.add_property("message", 
					  python::make_function(&Chem::INCHIMolecularGraphWriter::getMessage, 
											python::return_value_policy<python::copy_const_reference>()))
		.add_property("logOutput", 
					  python::make_function(&Chem::INCHIMolecularGraphWriter::getLogOutput, 
											python::return_value_policy<python::copy_const_reference>()));
}
