/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningDBCreatorExport.cpp 
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

#include "CDPL/Pharm/ScreeningDBCreator.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct ScreeningDBCreatorWrapper : CDPL::Pharm::ScreeningDBCreator, boost::python::wrapper<CDPL::Pharm::ScreeningDBCreator> 
    {

		typedef boost::shared_ptr<ScreeningDBCreatorWrapper> SharedPointer;

		void open(const std::string& name, Mode mode, bool allow_dup_entries) {
			this->get_override("open")(name, mode, allow_dup_entries);
		}

		void close() {
			this->get_override("close")();
		}

		Mode getMode() const {
			return this->get_override("getMode")();
		}

		bool allowDuplicateEntries() const {
			return this->get_override("allowDuplicateEntries")();
		}

		bool process(const CDPL::Chem::MolecularGraph& molgraph) {
			return this->get_override("process")(boost::ref(molgraph));
		}

		bool merge(const CDPL::Pharm::ScreeningDBAccessor& db_acc, const ProgressCallbackFunction& func) {
			return this->get_override("merge")(boost::ref(db_acc), boost::ref(func));
		}

		const std::string& getDatabaseName() const {
			return this->get_override("getDatabaseName")();
		}

		std::size_t getNumProcessed() const {
			return this->get_override("getNumProcessed")();
		}

		std::size_t getNumRejected() const {
			return this->get_override("getNumRejected")();
		}

		std::size_t getNumDeleted() const {
			return this->get_override("getNumDeleted")();
		}

		std::size_t getNumInserted() const {
			return this->get_override("getNumInserted")();
		}
    };
}


void CDPLPythonPharm::exportScreeningDBCreator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ScreeningDBCreatorWrapper, ScreeningDBCreatorWrapper::SharedPointer, 
				   boost::noncopyable> cl("ScreeningDBCreator", python::no_init);
    python::scope scope = cl;
    
    python::enum_<Pharm::ScreeningDBCreator::Mode>("Mode")
		.value("CREATE", Pharm::ScreeningDBCreator::CREATE)
		.value("UPDATE", Pharm::ScreeningDBCreator::UPDATE)
		.value("APPEND", Pharm::ScreeningDBCreator::APPEND)
		.export_values();

    cl
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ScreeningDBCreator>())	
		.def("open", python::pure_virtual(&Pharm::ScreeningDBCreator::open), 
			 (python::arg("self"), python::arg("name"), python::arg("mode") = Pharm::ScreeningDBCreator::CREATE, 
			  python::arg("allow_dup_entries") = true))
		.def("close", python::pure_virtual(&Pharm::ScreeningDBCreator::close), python::arg("self"))
		.def("getMode", python::pure_virtual(&Pharm::ScreeningDBCreator::getMode), python::arg("self"))
		.def("allowDuplicateEntries", python::pure_virtual(&Pharm::ScreeningDBCreator::allowDuplicateEntries), python::arg("self"))
		.def("process", python::pure_virtual(&Pharm::ScreeningDBCreator::process), (python::arg("self"), python::arg("molgraph")))
		.def("merge", python::pure_virtual(&Pharm::ScreeningDBCreator::merge), (python::arg("self"), python::arg("db_acc"), python::arg("func")))
		.def("getNumProcessed", python::pure_virtual(&Pharm::ScreeningDBCreator::getNumProcessed), python::arg("self"))
		.def("getNumRejected", python::pure_virtual(&Pharm::ScreeningDBCreator::getNumRejected), python::arg("self"))
		.def("getNumDeleted", python::pure_virtual(&Pharm::ScreeningDBCreator::getNumDeleted), python::arg("self"))
		.def("getNumInserted", python::pure_virtual(&Pharm::ScreeningDBCreator::getNumInserted), python::arg("self"))
		.def("getDatabaseName", python::pure_virtual(&Pharm::ScreeningDBCreator::getDatabaseName), python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.add_property("mode", &Pharm::ScreeningDBCreator::getMode)
		.add_property("allowDuplicates", &Pharm::ScreeningDBCreator::allowDuplicateEntries)
		.add_property("numProcessed", &Pharm::ScreeningDBCreator::getNumProcessed)
		.add_property("numRejected", &Pharm::ScreeningDBCreator::getNumRejected)
		.add_property("numDeleted", &Pharm::ScreeningDBCreator::getNumDeleted)
		.add_property("numInserted", &Pharm::ScreeningDBCreator::getNumInserted)
		.add_property("databaseName", python::make_function(&Pharm::ScreeningDBCreator::getDatabaseName,
															python::return_value_policy<python::copy_const_reference>()));

    python::register_ptr_to_python<Pharm::ScreeningDBCreator::SharedPointer>();
}
