/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningDBAccessorExport.cpp 
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

#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct ScreeningDBAccessorWrapper : CDPL::Pharm::ScreeningDBAccessor, boost::python::wrapper<CDPL::Pharm::ScreeningDBAccessor> 
	{

		typedef boost::shared_ptr<ScreeningDBAccessorWrapper> SharedPointer;

		void open(const std::string& name) {
			this->get_override("open")(name);
		}

		void close() {
			this->get_override("close")();
		}

		const std::string& getDatabaseName() const {
			return this->get_override("getDatabaseName")();
		}

		std::size_t getNumMolecules() const {
			return this->get_override("getNumMolecules")();
		}

		std::size_t getNumPharmacophores() const {
			return this->get_override("getNumPharmacophores")();
		}

		void getMolecule(std::size_t idx, CDPL::Chem::Molecule& mol) const {
			this->get_override("getMolecule")(idx, boost::ref(mol));
		} 

		void getPharmacophore(std::size_t idx, CDPL::Pharm::Pharmacophore& pharm) const {
			this->get_override("getPharmacophore")(idx, boost::ref(pharm));
		} 

		void getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, CDPL::Pharm::Pharmacophore& pharm) const {
			this->get_override("getPharmacophore")(mol_idx, conf_idx, boost::ref(pharm));
		} 

		std::size_t findMatchingEntries(const CDPL::Pharm::Pharmacophore& pharm) {
			return this->get_override("findMatchingEntries")(boost::ref(pharm));
		}

		std::size_t getNumMatchingEntries() {
			return this->get_override("getNumMatchingEntries")();
		}

		std::size_t getMatchingEntryMolIndex(std::size_t idx) const {
			return this->get_override("getMatchingEntryMolIndex")(idx);
		}

		std::size_t getMatchingEntryConfIndex(std::size_t idx) const {
			return this->get_override("getMatchingEntryConfIndex")(idx);
		}
	};
}


void CDPLPythonPharm::exportScreeningDBAccessor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ScreeningDBAccessorWrapper, ScreeningDBAccessorWrapper::SharedPointer, 
				   boost::noncopyable>("ScreeningDBAccessor", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ScreeningDBAccessor>())	
		.def("open", python::pure_virtual(&Pharm::ScreeningDBAccessor::open),
			 (python::arg("self"), python::arg("name")))
		.def("close", python::pure_virtual(&Pharm::ScreeningDBAccessor::close),
			 python::arg("self"))
		.def("getDatabaseName", python::pure_virtual(&Pharm::ScreeningDBAccessor::getDatabaseName),
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("getNumMolecules", python::pure_virtual(&Pharm::ScreeningDBAccessor::getNumMolecules),
			 python::arg("self"))
		.def("getNumPharmacophores", python::pure_virtual(&Pharm::ScreeningDBAccessor::getNumPharmacophores),
			 python::arg("self"))
		.def("getMolecule", python::pure_virtual(&Pharm::ScreeningDBAccessor::getMolecule),
			 (python::arg("self"), python::arg("idx"), python::arg("mol")))
		.def("getPharmacophore", 
			 python::pure_virtual(
				 static_cast<void (Pharm::ScreeningDBAccessor::*)(std::size_t, Pharm::Pharmacophore&) const>(
					 &Pharm::ScreeningDBAccessor::getPharmacophore)),
			 (python::arg("self"), python::arg("idx"), python::arg("pharm")))
		.def("getPharmacophore", 
			 python::pure_virtual(
				 static_cast<void (Pharm::ScreeningDBAccessor::*)(std::size_t, std::size_t, Pharm::Pharmacophore&) const>(
					 &Pharm::ScreeningDBAccessor::getPharmacophore)),
			 (python::arg("self"), python::arg("mol_idx"), python::arg("conf_idx"), python::arg("pharm")))
		.def("findMatchingEntries", python::pure_virtual(&Pharm::ScreeningDBAccessor::findMatchingEntries),
			 (python::arg("self"), python::arg("pharm")))
		.def("getNumMatchingEntries", python::pure_virtual(&Pharm::ScreeningDBAccessor::getNumMatchingEntries),
			 python::arg("self"))
		.def("getMatchingEntryMolIndex", python::pure_virtual(&Pharm::ScreeningDBAccessor::getMatchingEntryMolIndex),
			 (python::arg("self"), python::arg("idx")))
		.def("getMatchingEntryConfIndex", python::pure_virtual(&Pharm::ScreeningDBAccessor::getMatchingEntryConfIndex),
			 (python::arg("self"), python::arg("idx")))
		.add_property("databaseName", python::make_function(&Pharm::ScreeningDBAccessor::getDatabaseName,											
															python::return_value_policy<python::copy_const_reference>()))
		.add_property("numMolecules", &Pharm::ScreeningDBAccessor::getNumMolecules)
		.add_property("numPharmacophores", &Pharm::ScreeningDBAccessor::getNumPharmacophores);

	python::register_ptr_to_python<Pharm::ScreeningDBAccessor::SharedPointer>();
}
