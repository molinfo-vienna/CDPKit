/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyDefaultExport.cpp 
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

#include "CDPL/Vis/AtomPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomPropertyDefault {};
}


void CDPLPythonVis::exportAtomPropertyDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomPropertyDefault, boost::noncopyable>("AtomPropertyDefault", python::no_init)
		.def_readonly("COLOR", &Vis::AtomPropertyDefault::COLOR)
		.def_readonly("LABEL_FONT", &Vis::AtomPropertyDefault::LABEL_FONT)
		.def_readonly("LABEL_SIZE", &Vis::AtomPropertyDefault::LABEL_SIZE)
		.def_readonly("SECONDARY_LABEL_FONT", &Vis::AtomPropertyDefault::SECONDARY_LABEL_FONT)
		.def_readonly("SECONDARY_LABEL_SIZE", &Vis::AtomPropertyDefault::SECONDARY_LABEL_SIZE)
		.def_readonly("LABEL_MARGIN", &Vis::AtomPropertyDefault::LABEL_MARGIN)
		.def_readonly("RADICAL_ELECTRON_DOT_SIZE", &Vis::AtomPropertyDefault::RADICAL_ELECTRON_DOT_SIZE);
}
