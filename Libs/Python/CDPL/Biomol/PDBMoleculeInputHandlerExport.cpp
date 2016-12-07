/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBMoleculeInputHandlerExport.cpp 
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

#include "CDPL/Config.hpp"
#include "CDPL/Biomol/PDBMoleculeInputHandler.hpp"

#if defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Biomol/PDBGZMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBBZ2MoleculeInputHandler.hpp"

#endif // defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "ClassExports.hpp"


void CDPLPythonBiomol::exportPDBMoleculeInputHandler()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Biomol::PDBMoleculeInputHandler, 
		python::bases<Base::DataInputHandler<Chem::Molecule> > >("PDBMoleculeInputHandler", python::no_init)
		.def(python::init<>(python::arg("self")));

#if defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	python::class_<Biomol::PDBGZMoleculeInputHandler, 
		python::bases<Base::DataInputHandler<Chem::Molecule> > >("PDBGZMoleculeInputHandler", python::no_init)
		.def(python::init<>(python::arg("self")));

	python::class_<Biomol::PDBBZ2MoleculeInputHandler, 
		python::bases<Base::DataInputHandler<Chem::Molecule> > >("PDBBZ2MoleculeInputHandler", python::no_init)
		.def(python::init<>(python::arg("self")));

#endif // defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
}
