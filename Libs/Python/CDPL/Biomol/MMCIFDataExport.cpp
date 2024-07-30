/* 
 * MMCIFDataExport.cpp 
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

#include "CDPL/Biomol/MMCIFData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonBiomol::exportMMCIFData()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Biomol::MMCIFData, Biomol::MMCIFData::SharedPointer> cls("MMCIFData", python::no_init);
    python::scope scope = cls;

    python::class_<Biomol::MMCIFData::Category>("Category", python::no_init)
        .def(python::init<const std::string&>((python::arg("self"), python::arg("name"))))
        .def(python::init<const Biomol::MMCIFData::Category&>((python::arg("self"), python::arg("cat"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::MMCIFData::Category>())
        .def("assign", CDPLPythonBase::copyAssOp<Biomol::MMCIFData::Category>(), (python::arg("self"), python::arg("cat")), 
             python::return_self<>())
        .def("getName", python::make_function(&Biomol::MMCIFData::Category::getName,
                                              python::return_value_policy<python::copy_const_reference>()))
        .add_property("name", python::make_function(&Biomol::MMCIFData::Category::getName,
                                                    python::return_value_policy<python::copy_const_reference>()))
        ;
    
    cls
        .def(python::init<>(python::arg("self")))    
        .def(python::init<const Biomol::MMCIFData&>((python::arg("self"), python::arg("data"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::MMCIFData>())
        .def("getNumCategories", &Biomol::MMCIFData::getNumCategories, python::arg("self"))
        .def("isEmpty", &Biomol::MMCIFData::isEmpty, python::arg("self"))
        .def("clear", &Biomol::MMCIFData::clear, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<Biomol::MMCIFData>(), (python::arg("self"), python::arg("data")), 
             python::return_self<>())
        .def("swap", &Biomol::MMCIFData::swap, (python::arg("self"), python::arg("data"))) 
        .def("hasCategory", &Biomol::MMCIFData::hasCategory, (python::arg("self"), python::arg("name")))
        .def("addCategory", &Biomol::MMCIFData::addCategory, (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("getCategory", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)(const std::string&)>(&Biomol::MMCIFData::getCategory),
             (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("getCategory", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)(std::size_t)>(&Biomol::MMCIFData::getCategory),
             (python::arg("self"), python::arg("index")),
             python::return_internal_reference<>())
        .def("removeCategory", static_cast<bool (Biomol::MMCIFData::*)(const std::string&)>(&Biomol::MMCIFData::removeCategory),
             (python::arg("self"), python::arg("name")))
        .def("removeCategory", static_cast<void (Biomol::MMCIFData::*)(std::size_t)>(&Biomol::MMCIFData::removeCategory),
             (python::arg("self"), python::arg("index")))
        .def("__len__", &Biomol::MMCIFData::getNumCategories, python::arg("self"))
        .def("__getitem__", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)(const std::string&)>(&Biomol::MMCIFData::getCategory),
             (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("__getitem__", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)(std::size_t)>(&Biomol::MMCIFData::getCategory),
             (python::arg("self"), python::arg("index")),
             python::return_internal_reference<>())
        .def("__delitem__", static_cast<bool (Biomol::MMCIFData::*)(const std::string&)>(&Biomol::MMCIFData::removeCategory),
             (python::arg("self"), python::arg("name")))
        .def("__delitem__", static_cast<void (Biomol::MMCIFData::*)(std::size_t)>(&Biomol::MMCIFData::removeCategory),
             (python::arg("self"), python::arg("index")))
        .def("__contains__", &Biomol::MMCIFData::hasCategory, (python::arg("self"), python::arg("name")))
        .add_property("numCategories", &Biomol::MMCIFData::getNumCategories);
}
