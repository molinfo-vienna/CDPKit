/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReturnCodeExport.cpp 
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
		.def_readonly("FORCEFIELD_SETUP_FAILED", &ConfGen::ReturnCode::FORCEFIELD_SETUP_FAILED)
		.def_readonly("FORCEFIELD_MINIMIZATION_FAILED", &ConfGen::ReturnCode::FORCEFIELD_MINIMIZATION_FAILED)
		.def_readonly("MAX_NUM_TRIALS_EXCEEDED", &ConfGen::ReturnCode::MAX_NUM_TRIALS_EXCEEDED)
		.def_readonly("TIMEOUT_EXCEEDED", &ConfGen::ReturnCode::TIMEOUT_EXCEEDED)
		.def_readonly("ERROR", &ConfGen::ReturnCode::ERROR);
}
