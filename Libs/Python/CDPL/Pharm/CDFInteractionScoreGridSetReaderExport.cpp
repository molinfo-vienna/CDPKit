/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFInteractionScoreGridSetReaderExport.cpp 
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
#include "CDPL/Pharm/CDFInteractionScoreGridSetReader.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Pharm/CDFGZInteractionScoreGridSetReader.hpp"
#include "CDPL/Pharm/CDFBZ2InteractionScoreGridSetReader.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Util/FileDataReader.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportCDFInteractionScoreGridSetReader()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Pharm::CDFInteractionScoreGridSetReader, python::bases<Base::DataReader<Pharm::InteractionScoreGridSet> >, 
		boost::noncopyable>("CDFInteractionScoreGridSetReader", python::no_init)
		.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataReader<Pharm::CDFInteractionScoreGridSetReader>, python::bases<Base::DataReader<Pharm::InteractionScoreGridSet> >, 
		boost::noncopyable>("FileCDFInteractionScoreGridSetReader", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary)));

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	python::class_<Pharm::CDFGZInteractionScoreGridSetReader, python::bases<Base::DataReader<Pharm::InteractionScoreGridSet> >, 
		boost::noncopyable>("CDFGZInteractionScoreGridSetReader", python::no_init)
		.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataReader<Pharm::CDFGZInteractionScoreGridSetReader>, python::bases<Base::DataReader<Pharm::InteractionScoreGridSet> >, 
		boost::noncopyable>("FileCDFGZInteractionScoreGridSetReader", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary)));

	python::class_<Pharm::CDFBZ2InteractionScoreGridSetReader, python::bases<Base::DataReader<Pharm::InteractionScoreGridSet> >, 
		boost::noncopyable>("CDFBZ2InteractionScoreGridSetReader", python::no_init)
		.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
			 [python::with_custodian_and_ward<1, 2>()]);

	python::class_<Util::FileDataReader<Pharm::CDFBZ2InteractionScoreGridSetReader>, python::bases<Base::DataReader<Pharm::InteractionScoreGridSet> >, 
		boost::noncopyable>("FileCDFBZ2InteractionScoreGridSetReader", python::no_init)
		.def(python::init<const std::string&, std::ios_base::openmode>(
				 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary)));

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
}
