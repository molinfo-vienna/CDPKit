/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFMoleculeReaderExport.cpp 
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
#include "CDPL/Chem/CDFMoleculeReader.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Chem/CDFGZMoleculeReader.hpp"
#include "CDPL/Chem/CDFBZ2MoleculeReader.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Util/FileDataReader.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportCDFMoleculeReader()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::CDFMoleculeReader, python::bases<Base::DataReader<Chem::Molecule> >, 
		boost::noncopyable>("CDFMoleculeReader", python::no_init)
		.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataReader<Chem::CDFMoleculeReader>, python::bases<Base::DataReader<Chem::Molecule> >, 
		boost::noncopyable>("FileCDFMoleculeReader", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary)));

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	python::class_<Chem::CDFGZMoleculeReader, python::bases<Base::DataReader<Chem::Molecule> >, 
		boost::noncopyable>("CDFGZMoleculeReader", python::no_init)
		.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataReader<Chem::CDFGZMoleculeReader>, python::bases<Base::DataReader<Chem::Molecule> >, 
		boost::noncopyable>("FileCDFGZMoleculeReader", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary)));

	python::class_<Chem::CDFBZ2MoleculeReader, python::bases<Base::DataReader<Chem::Molecule> >, 
		boost::noncopyable>("CDFBZ2MoleculeReader", python::no_init)
		.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataReader<Chem::CDFBZ2MoleculeReader>, python::bases<Base::DataReader<Chem::Molecule> >, 
		boost::noncopyable>("FileCDFBZ2MoleculeReader", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary)));

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
}
