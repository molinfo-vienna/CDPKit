/* 
 * TorsionDriverExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/TorsionDriver.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportTorsionDriver()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ConfGen::TorsionDriver, boost::noncopyable>("TorsionDriver", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionDriver>())
        .def("getSettings", 
             static_cast<ConfGen::TorsionDriverSettings& (ConfGen::TorsionDriver::*)()>
             (&ConfGen::TorsionDriver::getSettings), 
             python::arg("self"), python::return_internal_reference<>())
        .def("clearTorsionLibraries", &ConfGen::TorsionDriver::clearTorsionLibraries, 
             python::arg("self"))
        .def("addTorsionLibrary", &ConfGen::TorsionDriver::addTorsionLibrary, 
             (python::arg("self"), python::arg("lib")))
        .def("setup", static_cast<unsigned int (ConfGen::TorsionDriver::*)(const Chem::MolecularGraph&)>(
                 &ConfGen::TorsionDriver::setup), 
             (python::arg("self"), python::arg("molgraph")))
        .def("setup", static_cast<unsigned int (ConfGen::TorsionDriver::*)(const Chem::MolecularGraph&, const Util::BitSet&)>(
                 &ConfGen::TorsionDriver::setup), 
             (python::arg("self"), python::arg("molgraph"), python::arg("bond_mask")), 
             python::arg("molgraph"), python::with_custodian_and_ward<1, 2>())
        .def("setup", static_cast<unsigned int (ConfGen::TorsionDriver::*)(const Chem::MolecularGraph&)>(
                 &ConfGen::TorsionDriver::setup), 
             (python::arg("self"), python::arg("molgraph")), python::with_custodian_and_ward<1, 2>())
        .def ("clearInputCoordinates", static_cast<void (ConfGen::TorsionDriver::*)()>(
                  &ConfGen::TorsionDriver::clearInputCoordinates), 
              python::arg("self"))
        .def ("clearInputCoordinates", static_cast<void (ConfGen::TorsionDriver::*)(std::size_t)>(
                  &ConfGen::TorsionDriver::clearInputCoordinates), 
              (python::arg("self"), python::arg("frag_idx")))
        .def ("addInputCoordinates", static_cast<void (ConfGen::TorsionDriver::*)(const Math::Vector3DArray&)>(
                  &ConfGen::TorsionDriver::addInputCoordinates), 
              (python::arg("self"), python::arg("coords")))
        .def ("addInputCoordinates", static_cast<void (ConfGen::TorsionDriver::*)(const Math::Vector3DArray&, std::size_t)>(
                  &ConfGen::TorsionDriver::addInputCoordinates), 
              (python::arg("self"), python::arg("coords"), python::arg("frag_idx")))
        .def ("addInputCoordinates", static_cast<void (ConfGen::TorsionDriver::*)(const ConfGen::ConformerData&, std::size_t)>(
                  &ConfGen::TorsionDriver::addInputCoordinates), 
              (python::arg("self"), python::arg("conf_data"), python::arg("frag_idx")))
        .def ("addInputCoordinates", static_cast<void (ConfGen::TorsionDriver::*)(const ConfGen::ConformerData::SharedPointer&, std::size_t)>(
                  &ConfGen::TorsionDriver::addInputCoordinates), 
              (python::arg("self"), python::arg("conf_data"), python::arg("frag_idx")))
        .def("setAbortCallback", &ConfGen::TorsionDriver::setAbortCallback, 
             (python::arg("self"), python::arg("func")))
        .def("getAbortCallback", &ConfGen::TorsionDriver::getAbortCallback, 
             python::arg("self"), python::return_internal_reference<>())
        .def("setTimeoutCallback", &ConfGen::TorsionDriver::setTimeoutCallback, 
             (python::arg("self"), python::arg("func")))
        .def("getTimeoutCallback", &ConfGen::TorsionDriver::getTimeoutCallback, 
             python::arg("self"), python::return_internal_reference<>())
        .def("setLogMessageCallback", &ConfGen::TorsionDriver::setLogMessageCallback, 
             (python::arg("self"), python::arg("func")))
        .def("getLogMessageCallback", &ConfGen::TorsionDriver::getLogMessageCallback, 
             python::arg("self"), python::return_internal_reference<>())
        .def("generateConformers", &ConfGen::TorsionDriver::generateConformers, python::arg("self"))
        .def("getNumConformers", &ConfGen::TorsionDriver::getNumConformers, python::arg("self"))
        .def("getConformer", 
             static_cast<ConfGen::ConformerData& (ConfGen::TorsionDriver::*)(std::size_t)>(&ConfGen::TorsionDriver::getConformer),
             (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
        .def("__getitem__", 
             static_cast<ConfGen::ConformerData& (ConfGen::TorsionDriver::*)(std::size_t)>(&ConfGen::TorsionDriver::getConformer),
             (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
        .add_property("numConformers", &ConfGen::TorsionDriver::getNumConformers)
        .add_property("settings", 
                      python::make_function(static_cast<ConfGen::TorsionDriverSettings& (ConfGen::TorsionDriver::*)()>
                                            (&ConfGen::TorsionDriver::getSettings),
                                            python::return_internal_reference<>()))    
        .add_property("abortCallback", 
                      python::make_function(&ConfGen::TorsionDriver::getAbortCallback,
                                            python::return_internal_reference<>()),
                      &ConfGen::TorsionDriver::setAbortCallback)
    
        .add_property("timeoutCallback", 
                      python::make_function(&ConfGen::TorsionDriver::getTimeoutCallback,
                                            python::return_internal_reference<>()),
                      &ConfGen::TorsionDriver::setTimeoutCallback)
        .add_property("logMessageCallback", 
                      python::make_function(&ConfGen::TorsionDriver::getLogMessageCallback,
                                            python::return_internal_reference<>()),
                      &ConfGen::TorsionDriver::setLogMessageCallback);
}
