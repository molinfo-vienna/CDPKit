/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBMolecularGraphWriterExport.cpp 
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
#include "CDPL/Biomol/PDBMolecularGraphWriter.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Biomol/PDBGZMolecularGraphWriter.hpp"
#include "CDPL/Biomol/PDBBZ2MolecularGraphWriter.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Util/FileDataWriter.hpp"

#include "ClassExports.hpp"


void CDPLPythonBiomol::exportPDBMolecularGraphWriter()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Biomol::PDBMolecularGraphWriter, python::bases<Base::DataWriter<Chem::MolecularGraph> >,
		boost::noncopyable>("PDBMolecularGraphWriter", python::no_init)
		.def(python::init<std::ostream&>((python::arg("self"), python::arg("os")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataWriter<Biomol::PDBMolecularGraphWriter>, python::bases<Base::DataWriter<Chem::MolecularGraph> >, 
		boost::noncopyable>("FilePDBMolecularGraphWriter", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
				  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	python::class_<Biomol::PDBGZMolecularGraphWriter, python::bases<Base::DataWriter<Chem::MolecularGraph> >, 
		boost::noncopyable>("PDBGZMolecularGraphWriter", python::no_init)
		.def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataWriter<Biomol::PDBGZMolecularGraphWriter>, python::bases<Base::DataWriter<Chem::MolecularGraph> >, 
		boost::noncopyable>("FilePDBGZMolecularGraphWriter", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
				  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

	python::class_<Biomol::PDBBZ2MolecularGraphWriter, python::bases<Base::DataWriter<Chem::MolecularGraph> >, 
		boost::noncopyable>("PDBBZ2MolecularGraphWriter", python::no_init)
		.def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataWriter<Biomol::PDBBZ2MolecularGraphWriter>, python::bases<Base::DataWriter<Chem::MolecularGraph> >, 
		boost::noncopyable>("FilePDBBZ2MolecularGraphWriter", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
				  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
}
