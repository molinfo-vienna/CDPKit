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


#include <sstream>

#include <boost/python.hpp>

#include "CDPL/Biomol/MMCIFData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    bool hasItem(const CDPL::Biomol::MMCIFData::Category& cif_cat, const std::string& name)
    {
        return cif_cat.findItem(name);
    }
    
    bool hasCategory(const CDPL::Biomol::MMCIFData& cif_data, const std::string& name)
    {
        return cif_data.findCategory(name);
    }

    template <typename T>
    boost::python::object toString(const T& data)
    {
        std::ostringstream oss;

        oss << data;

        return boost::python::str(oss.str());
    }
}


void CDPLPythonBiomol::exportMMCIFData()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Biomol::MMCIFData, Biomol::MMCIFData::SharedPointer> cls("MMCIFData", python::no_init);
    python::scope scope = cls;

    python::class_<Biomol::MMCIFData::Item>("Item", python::no_init)
        .def(python::init<const std::string&>((python::arg("self"), python::arg("name"))))
        .def(python::init<const Biomol::MMCIFData::Item&>((python::arg("self"), python::arg("item"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::MMCIFData::Item>())
        .def("assign", CDPLPythonBase::copyAssOp<Biomol::MMCIFData::Item>(), (python::arg("self"), python::arg("item")),
             python::return_self<>())
        .def("swap", &Biomol::MMCIFData::Item::swap, (python::arg("self"), python::arg("cat")))
        .def("clear", &Biomol::MMCIFData::Item::clear, python::arg("self"))
        .def("getName", python::make_function(&Biomol::MMCIFData::Item::getName,
                                              python::return_value_policy<python::copy_const_reference>()))
        .def("getNumValues", &Biomol::MMCIFData::Item::getNumValues, python::arg("self"))
        .def("getValue", &Biomol::MMCIFData::Item::getValue,
             (python::arg("self"), python::arg("index")),
             python::return_value_policy<python::copy_const_reference>())
        .def("setValue", &Biomol::MMCIFData::Item::setValue,
             (python::arg("self"), python::arg("index"), python::arg("value")))
        .def("addValue", &Biomol::MMCIFData::Item::addValue, (python::arg("self"), python::arg("value")))
        .def("removeValue", static_cast<void (Biomol::MMCIFData::Item::*)(std::size_t)>(&Biomol::MMCIFData::Item::removeValue),
             (python::arg("self"), python::arg("index")))
        .def("__len__", &Biomol::MMCIFData::Item::getNumValues, python::arg("self"))
        .def("__getitem__", &Biomol::MMCIFData::Item::getValue,
             (python::arg("self"), python::arg("index")),
             python::return_value_policy<python::copy_const_reference>())
        .def("__delitem__", static_cast<void (Biomol::MMCIFData::Item::*)(std::size_t)>(&Biomol::MMCIFData::Item::removeValue),
             (python::arg("self"), python::arg("index")))
        .def("__setitem__", &Biomol::MMCIFData::Item::setValue,
             (python::arg("self"), python::arg("index"), python::arg("value")))
        .add_property("numValues", &Biomol::MMCIFData::Item::getNumValues)
        .add_property("name", python::make_function(&Biomol::MMCIFData::Item::getName,
                                                    python::return_value_policy<python::copy_const_reference>()));

    python::class_<Biomol::MMCIFData::Category>("Category", python::no_init)
        .def(python::init<const std::string&>((python::arg("self"), python::arg("name"))))
        .def(python::init<const Biomol::MMCIFData::Category&>((python::arg("self"), python::arg("cat"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::MMCIFData::Category>())
        .def("assign", CDPLPythonBase::copyAssOp<Biomol::MMCIFData::Category>(), (python::arg("self"), python::arg("cat")), 
             python::return_self<>())
        .def("getName", python::make_function(&Biomol::MMCIFData::Category::getName,
                                              python::return_value_policy<python::copy_const_reference>()))
        .def("getNumItems", &Biomol::MMCIFData::Category::getNumItems, python::arg("self"))
        .def("getNumValueRows", &Biomol::MMCIFData::Category::getNumValueRows, python::arg("self"))
        .def("clear", &Biomol::MMCIFData::Category::clear, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<Biomol::MMCIFData>(), (python::arg("self"), python::arg("cat")), 
             python::return_self<>())
        .def("swap", &Biomol::MMCIFData::Category::swap, (python::arg("self"), python::arg("cat"))) 
        .def("clear", &Biomol::MMCIFData::Category::clear, python::arg("self"))
        .def("findItem", static_cast<Biomol::MMCIFData::Item* (Biomol::MMCIFData::Category::*)(const std::string&)>(&Biomol::MMCIFData::Category::findItem),
             (python::arg("self"), python::arg("name")), python::return_internal_reference<>())
        .def("addItem", &Biomol::MMCIFData::Category::addItem, (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("getItem", static_cast<Biomol::MMCIFData::Item& (Biomol::MMCIFData::Category::*)(const std::string&)>(&Biomol::MMCIFData::Category::getItem),
             (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("getItem", static_cast<Biomol::MMCIFData::Item& (Biomol::MMCIFData::Category::*)(std::size_t)>(&Biomol::MMCIFData::Category::getItem),
             (python::arg("self"), python::arg("index")),
             python::return_internal_reference<>())
        .def("removeItem", static_cast<bool (Biomol::MMCIFData::Category::*)(const std::string&)>(&Biomol::MMCIFData::Category::removeItem),
             (python::arg("self"), python::arg("name")))
        .def("removeItem", static_cast<void (Biomol::MMCIFData::Category::*)(std::size_t)>(&Biomol::MMCIFData::Category::removeItem),
             (python::arg("self"), python::arg("index")))
        .def("__len__", &Biomol::MMCIFData::Category::getNumItems, python::arg("self"))
        .def("__getitem__", static_cast<Biomol::MMCIFData::Item& (Biomol::MMCIFData::Category::*)(const std::string&)>(&Biomol::MMCIFData::Category::getItem),
             (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("__getitem__", static_cast<Biomol::MMCIFData::Item& (Biomol::MMCIFData::Category::*)(std::size_t)>(&Biomol::MMCIFData::Category::getItem),
             (python::arg("self"), python::arg("index")),
             python::return_internal_reference<>())
        .def("__delitem__", static_cast<bool (Biomol::MMCIFData::Category::*)(const std::string&)>(&Biomol::MMCIFData::Category::removeItem),
             (python::arg("self"), python::arg("name")))
        .def("__delitem__", static_cast<void (Biomol::MMCIFData::Category::*)(std::size_t)>(&Biomol::MMCIFData::Category::removeItem),
             (python::arg("self"), python::arg("index")))
        .def("__contains__", &hasItem, (python::arg("self"), python::arg("name")))
        .def("__str__", &toString<Biomol::MMCIFData::Category>, python::arg("self"))
        .add_property("numValueRows", &Biomol::MMCIFData::Category::getNumValueRows)
        .add_property("numItems", &Biomol::MMCIFData::Category::getNumItems)
        .add_property("name", python::make_function(&Biomol::MMCIFData::Category::getName,
                                                    python::return_value_policy<python::copy_const_reference>()));
    
    cls
        .def(python::init<>(python::arg("self")))    
        .def(python::init<const Biomol::MMCIFData&>((python::arg("self"), python::arg("data"))))
        .def(python::init<const std::string&>((python::arg("self"), python::arg("id"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::MMCIFData>())
        .def("getID", &Biomol::MMCIFData::getID, python::arg("self"),
             python::return_value_policy<python::copy_const_reference>())
        .def("setID", &Biomol::MMCIFData::setID, (python::arg("self"), python::arg("id")))
        .def("getNumCategories", &Biomol::MMCIFData::getNumCategories, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<Biomol::MMCIFData>(), (python::arg("self"), python::arg("data")), 
             python::return_self<>())
        .def("swap", &Biomol::MMCIFData::swap, (python::arg("self"), python::arg("data"))) 
        .def("clear", &Biomol::MMCIFData::clear, python::arg("self"))
        .def("findCategory", static_cast<Biomol::MMCIFData::Category* (Biomol::MMCIFData::*)(const std::string&)>(&Biomol::MMCIFData::findCategory),
             (python::arg("self"), python::arg("name")), python::return_internal_reference<>())
        .def("addCategory", &Biomol::MMCIFData::addCategory, (python::arg("self"), python::arg("name"), python::arg("front") = false),
             python::return_internal_reference<>())
        .def("getCategory", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)(const std::string&)>(&Biomol::MMCIFData::getCategory),
             (python::arg("self"), python::arg("name")),
             python::return_internal_reference<>())
        .def("getCategory", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)(std::size_t)>(&Biomol::MMCIFData::getCategory),
             (python::arg("self"), python::arg("index")),
             python::return_internal_reference<>())
        .def("lastCategory", static_cast<Biomol::MMCIFData::Category& (Biomol::MMCIFData::*)()>(&Biomol::MMCIFData::lastCategory),
             python::arg("self"), python::return_internal_reference<>())
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
        .def("__contains__", &hasCategory, (python::arg("self"), python::arg("name")))
        .def("__str__", &toString<Biomol::MMCIFData>, python::arg("self"))
        .add_property("numCategories", &Biomol::MMCIFData::getNumCategories)
        .add_property("id", python::make_function(&Biomol::MMCIFData::getID, python::return_value_policy<python::copy_const_reference>()),
                      &Biomol::MMCIFData::setID);
}
