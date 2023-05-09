/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOL2MoleculeInputHandlerExport.cpp 
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

#include "CDPL/Config.hpp"
#include "CDPL/Chem/MOL2MoleculeInputHandler.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Chem/MOL2GZMoleculeInputHandler.hpp"
#include "CDPL/Chem/MOL2BZ2MoleculeInputHandler.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "ClassExports.hpp"


void CDPLPythonChem::exportMOL2MoleculeInputHandler()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::MOL2MoleculeInputHandler, 
		python::bases<Base::DataInputHandler<Chem::Molecule> > >("MOL2MoleculeInputHandler", python::no_init)
		.def(python::init<>(python::arg("self")));

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	python::class_<Chem::MOL2GZMoleculeInputHandler, 
		python::bases<Base::DataInputHandler<Chem::Molecule> > >("MOL2GZMoleculeInputHandler", python::no_init)
		.def(python::init<>(python::arg("self")));

	python::class_<Chem::MOL2BZ2MoleculeInputHandler, 
		python::bases<Base::DataInputHandler<Chem::Molecule> > >("MOL2BZ2MoleculeInputHandler", python::no_init)
		.def(python::init<>(python::arg("self")));

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
}
