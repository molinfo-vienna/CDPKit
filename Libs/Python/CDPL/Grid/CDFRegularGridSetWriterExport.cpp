/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFRegularGridSetWriterExport.cpp 
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
#include "CDPL/Grid/CDFDRegularGridSetWriter.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Grid/CDFGZDRegularGridSetWriter.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetWriter.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Util/FileDataWriter.hpp"

#include "ClassExports.hpp"


void CDPLPythonGrid::exportCDFRegularGridSetWriter()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Grid::CDFDRegularGridSetWriter, python::bases<Base::DataWriter<Grid::DRegularGridSet> >,
		boost::noncopyable>("CDFDRegularGridSetWriter", python::no_init)
		.def(python::init<std::ostream&>((python::arg("self"), python::arg("os")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataWriter<Grid::CDFDRegularGridSetWriter>, python::bases<Base::DataWriter<Grid::DRegularGridSet> >, 
		boost::noncopyable>("FileCDFDRegularGridSetWriter", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
				  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	python::class_<Grid::CDFGZDRegularGridSetWriter, python::bases<Base::DataWriter<Grid::DRegularGridSet> >, 
		boost::noncopyable>("CDFGZDRegularGridSetWriter", python::no_init)
		.def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataWriter<Grid::CDFGZDRegularGridSetWriter>, python::bases<Base::DataWriter<Grid::DRegularGridSet> >, 
		boost::noncopyable>("FileCDFGZDRegularGridSetWriter", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
				  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

	python::class_<Grid::CDFBZ2DRegularGridSetWriter, python::bases<Base::DataWriter<Grid::DRegularGridSet> >, 
		boost::noncopyable>("CDFBZ2DRegularGridSetWriter", python::no_init)
		.def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataWriter<Grid::CDFBZ2DRegularGridSetWriter>, python::bases<Base::DataWriter<Grid::DRegularGridSet> >, 
		boost::noncopyable>("FileCDFBZ2DRegularGridSetWriter", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
				  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
}
