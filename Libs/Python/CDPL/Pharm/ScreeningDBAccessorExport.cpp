/* 
 * ScreeningDBAccessorExport.cpp 
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

#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct ScreeningDBAccessorWrapper : CDPL::Pharm::ScreeningDBAccessor, boost::python::wrapper<CDPL::Pharm::ScreeningDBAccessor> 
    {

        typedef std::shared_ptr<ScreeningDBAccessorWrapper> SharedPointer;

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

        std::size_t getNumPharmacophores(std::size_t mol_idx) const {
            return this->get_override("getNumPharmacophores")(mol_idx);
        }

        void getMolecule(std::size_t mol_idx, CDPL::Chem::Molecule& mol, bool overwrite) const {
            this->get_override("getMolecule")(mol_idx, boost::ref(mol), overwrite);
        } 

        void getPharmacophore(std::size_t pharm_idx, CDPL::Pharm::Pharmacophore& pharm, bool overwrite) const {
            this->get_override("getPharmacophore")(pharm_idx, boost::ref(pharm), overwrite);
        } 

        void getPharmacophore(std::size_t mol_idx, std::size_t mol_conf_idx, CDPL::Pharm::Pharmacophore& pharm, bool overwrite) const {
            this->get_override("getPharmacophore")(mol_idx, mol_conf_idx, boost::ref(pharm), overwrite);
        } 

        std::size_t getMoleculeIndex(std::size_t pharm_idx) const {
            return this->get_override("getMoleculeIndex")(pharm_idx);
        }

        std::size_t getConformationIndex(std::size_t pharm_idx) const {
            return this->get_override("getConformationIndex")(pharm_idx);
        }

        const CDPL::Pharm::FeatureTypeHistogram& getFeatureCounts(std::size_t pharm_idx) const {
            return this->get_override("getFeatureCounts")(pharm_idx);
        }

        const CDPL::Pharm::FeatureTypeHistogram& getFeatureCounts(std::size_t mol_idx, std::size_t mol_conf_idx) const {
            return this->get_override("getFeatureCounts")(mol_idx, mol_conf_idx);
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
        .def("getNumPharmacophores", python::pure_virtual(
                 static_cast<std::size_t (Pharm::ScreeningDBAccessor::*)() const>(&Pharm::ScreeningDBAccessor::getNumPharmacophores)),
             python::arg("self"))
        .def("getNumPharmacophores", python::pure_virtual(
                 static_cast<std::size_t (Pharm::ScreeningDBAccessor::*)(std::size_t) const>(&Pharm::ScreeningDBAccessor::getNumPharmacophores)),
             (python::arg("self"), python::arg("mol_idx")))
        .def("getMolecule", python::pure_virtual(&Pharm::ScreeningDBAccessor::getMolecule),
             (python::arg("self"), python::arg("mol_idx"), python::arg("mol"), python::arg("overwrite") = true))
        .def("getPharmacophore", 
             python::pure_virtual(
                 static_cast<void (Pharm::ScreeningDBAccessor::*)(std::size_t, Pharm::Pharmacophore&, bool) const>(
                     &Pharm::ScreeningDBAccessor::getPharmacophore)),
             (python::arg("self"), python::arg("pharm_idx"), python::arg("pharm"), python::arg("overwrite") = true))
        .def("getPharmacophore", 
             python::pure_virtual(
                 static_cast<void (Pharm::ScreeningDBAccessor::*)(std::size_t, std::size_t, Pharm::Pharmacophore&, bool) const>(
                     &Pharm::ScreeningDBAccessor::getPharmacophore)),
             (python::arg("self"), python::arg("mol_idx"), python::arg("mol_conf_idx"), python::arg("pharm"), python::arg("overwrite") = true))
        .def("getMoleculeIndex", python::pure_virtual(&Pharm::ScreeningDBAccessor::getMoleculeIndex),
             (python::arg("self"), python::arg("pharm_idx")))
        .def("getConformationIndex", python::pure_virtual(&Pharm::ScreeningDBAccessor::getConformationIndex),
             (python::arg("self"), python::arg("pharm_idx")))
        .def("getFeatureCounts", python::pure_virtual(
                 static_cast<const Pharm::FeatureTypeHistogram& (Pharm::ScreeningDBAccessor::*)(std::size_t) const>(&Pharm::ScreeningDBAccessor::getFeatureCounts)),
             (python::arg("self"), python::arg("pharm_idx")), python::return_internal_reference<>())
        .def("getFeatureCounts", python::pure_virtual(
                 static_cast<const Pharm::FeatureTypeHistogram& (Pharm::ScreeningDBAccessor::*)(std::size_t, std::size_t) const>(&Pharm::ScreeningDBAccessor::getFeatureCounts)),
             (python::arg("self"), python::arg("mol_idx"), python::arg("mol_conf_idx")), python::return_internal_reference<>())
        .add_property("databaseName", python::make_function(&Pharm::ScreeningDBAccessor::getDatabaseName,                                            
                                                            python::return_value_policy<python::copy_const_reference>()))
        .add_property("numMolecules", &Pharm::ScreeningDBAccessor::getNumMolecules)
        .add_property("numPharmacophores", 
                      static_cast<std::size_t (Pharm::ScreeningDBAccessor::*)() const>(&Pharm::ScreeningDBAccessor::getNumPharmacophores));

    python::register_ptr_to_python<Pharm::ScreeningDBAccessor::SharedPointer>();
}
