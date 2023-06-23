/* 
 * ReturnCodeExport.cpp 
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

#include "CDPL/ConfGen/ReturnCode.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct ReturnCode {};
}


void CDPLPythonConfGen::exportReturnCodes()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ReturnCode, boost::noncopyable>("ReturnCode", python::no_init)
		.def_readonly("SUCCESS", &ConfGen::ReturnCode::SUCCESS)
		.def_readonly("UNINITIALIZED", &ConfGen::ReturnCode::UNINITIALIZED)
		.def_readonly("TIMEOUT", &ConfGen::ReturnCode::TIMEOUT)
		.def_readonly("ABORTED", &ConfGen::ReturnCode::ABORTED)
		.def_readonly("FORCEFIELD_SETUP_FAILED", &ConfGen::ReturnCode::FORCEFIELD_SETUP_FAILED)
		.def_readonly("FORCEFIELD_MINIMIZATION_FAILED", &ConfGen::ReturnCode::FORCEFIELD_MINIMIZATION_FAILED)
		.def_readonly("FRAGMENT_LIBRARY_NOT_SET", &ConfGen::ReturnCode::FRAGMENT_LIBRARY_NOT_SET)
		.def_readonly("FRAGMENT_CONF_GEN_FAILED", &ConfGen::ReturnCode::FRAGMENT_CONF_GEN_FAILED)
		.def_readonly("FRAGMENT_CONF_GEN_TIMEOUT", &ConfGen::ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT)
		.def_readonly("FRAGMENT_ALREADY_PROCESSED", &ConfGen::ReturnCode::FRAGMENT_ALREADY_PROCESSED)
		.def_readonly("TORSION_DRIVING_FAILED", &ConfGen::ReturnCode::TORSION_DRIVING_FAILED)
		.def_readonly("CONF_GEN_FAILED", &ConfGen::ReturnCode::CONF_GEN_FAILED)
		.def_readonly("TOO_MUCH_SYMMETRY", &ConfGen::ReturnCode::TOO_MUCH_SYMMETRY)
		;
}
