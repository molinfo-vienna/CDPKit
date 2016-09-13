/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLiteScreeningDBCreatorExport.cpp 
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

#include "CDPL/Pharm/SQLiteScreeningDBCreator.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportSQLiteScreeningDBCreator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::SQLiteScreeningDBCreator, boost::noncopyable> creator_class("SQLiteScreeningDBCreator", python::no_init);
	python::scope scope = creator_class;

	python::enum_<Pharm::SQLiteScreeningDBCreator::Mode>("Mode")
		.value("CREATE", Pharm::SQLiteScreeningDBCreator::CREATE)
		.value("UPDATE", Pharm::SQLiteScreeningDBCreator::UPDATE)
		.value("APPEND", Pharm::SQLiteScreeningDBCreator::APPEND)
		.export_values();

	creator_class
		.def(python::init<>(python::arg("self")))
		.def(python::init<const std::string&, Pharm::SQLiteScreeningDBCreator::Mode, bool>
			 ((python::arg("self"), python::arg("name"), python::arg("mode") = Pharm::SQLiteScreeningDBCreator::CREATE, 
			   python::arg("allow_duplicates") = true)))
		.def("open", &Pharm::SQLiteScreeningDBCreator::open, 
			 (python::arg("self"), python::arg("name"), python::arg("mode") = Pharm::SQLiteScreeningDBCreator::CREATE, 
			  python::arg("allow_duplicates") = true))
		.def("close", &Pharm::SQLiteScreeningDBCreator::close, python::arg("self"))
		.def("getMode", &Pharm::SQLiteScreeningDBCreator::getMode, python::arg("self"))
		.def("allowDuplicates", &Pharm::SQLiteScreeningDBCreator::allowDuplicates, python::arg("self"))
		.add_property("mode", &Pharm::SQLiteScreeningDBCreator::getMode)
		.add_property("duplicates", &Pharm::SQLiteScreeningDBCreator::allowDuplicates);
}