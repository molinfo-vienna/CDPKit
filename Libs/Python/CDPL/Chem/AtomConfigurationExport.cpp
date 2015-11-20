/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomConfigurationExport.cpp 
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

#include "CDPL/Chem/AtomConfiguration.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomConfiguration {};
}


void CDPLPythonChem::exportAtomConfigurations()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomConfiguration, boost::noncopyable>("AtomConfiguration", python::no_init)
		.def_readonly("UNDEF", &Chem::AtomConfiguration::UNDEF)
		.def_readonly("NONE", &Chem::AtomConfiguration::NONE)
		.def_readonly("R", &Chem::AtomConfiguration::R)
		.def_readonly("S", &Chem::AtomConfiguration::S)
		.def_readonly("EITHER", &Chem::AtomConfiguration::EITHER);
}
