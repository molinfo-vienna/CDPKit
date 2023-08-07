/* 
 * ArrayExport.cpp 
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

#include "CDPL/Util/Array.hpp"

#include "ArrayVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    CDPL::Util::STPair& assignSTPair(CDPL::Util::STPair& lhs, const CDPL::Util::STPair& rhs)
    {
        return lhs.operator=(rhs);
    }

    std::size_t getFirst(const CDPL::Util::STPair& pair)
    {
        return pair.first;
    }

    void setFirst(CDPL::Util::STPair& pair, std::size_t value)
    {
        pair.first = value;
    }

    std::size_t getSecond(const CDPL::Util::STPair& pair)
    {
        return pair.second;
    }

    void setSecond(CDPL::Util::STPair& pair, std::size_t value)
    {
        pair.second = value;
    }
}


void CDPLPythonUtil::exportArrays()
{
    using namespace boost;
    using namespace CDPL;
    
    python::class_<Util::UIArray, Util::UIArray::SharedPointer>("UIArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::UIArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::UIArray, 
             python::return_value_policy<python::return_by_value>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::UIArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::UIArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::UIArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::UIArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::UIArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::UIArray::operator>, (python::arg("self"), python::arg("array")));

    python::class_<Util::LArray, Util::LArray::SharedPointer>("LArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::LArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::LArray, 
             python::return_value_policy<python::return_by_value>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::LArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::LArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::LArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::LArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::LArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::LArray::operator>, (python::arg("self"), python::arg("array")));

    python::class_<Util::STArray, Util::STArray::SharedPointer>("STArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::STArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::STArray, 
             python::return_value_policy<python::return_by_value>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::STArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::STArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::STArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::STArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::STArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::STArray::operator>, (python::arg("self"), python::arg("array")));

    python::class_<Util::STPair>("STPair", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::STPair&>((python::arg("self"), python::arg("pair"))))
        .def(python::init<std::size_t, std::size_t>((python::arg("self"), python::arg("first"), python::arg("second"))))
        .def("getFirst", &getFirst, python::arg("self"))
        .def("setFirst", &setFirst, (python::arg("self"), python::arg("value")))
        .def("getSecond", &getSecond, python::arg("self"))
        .def("setSecond", &setSecond, (python::arg("self"), python::arg("value")))
        .def_readwrite("first", &Util::STPair::first)
        .def_readwrite("second", &Util::STPair::second)
        .def("assign", &assignSTPair,
             (python::arg("self"), python::arg("array")), python::return_self<>())
        .def("__eq__", static_cast<bool (*)(const Util::STPair&, const Util::STPair&)>(&std::operator==),
             (python::arg("self"), python::arg("pair")))
        .def("__ne__", static_cast<bool (*)(const Util::STPair&, const Util::STPair&)>(&std::operator!=),
             (python::arg("self"), python::arg("pair")))
        .def("__le__", static_cast<bool (*)(const Util::STPair&, const Util::STPair&)>(&std::operator<=),
             (python::arg("self"), python::arg("pair")))
        .def("__ge__", static_cast<bool (*)(const Util::STPair&, const Util::STPair&)>(&std::operator>=),
             (python::arg("self"), python::arg("pair")))
        .def("__lt__", static_cast<bool (*)(const Util::STPair&, const Util::STPair&)>(&std::operator<),
             (python::arg("self"), python::arg("pair")))
        .def("__gt__", static_cast<bool (*)(const Util::STPair&, const Util::STPair&)>(&std::operator>),
             (python::arg("self"), python::arg("pair")));
    
    python::class_<Util::STPairArray, Util::STPairArray::SharedPointer>("STPairArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::STPairArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::STPairArray, 
             python::return_internal_reference<>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::STPairArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::STPairArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::STPairArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::STPairArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::STPairArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::STPairArray::operator>, (python::arg("self"), python::arg("array")));
    
    python::class_<Util::DArray, Util::DArray::SharedPointer>("DArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::DArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::DArray, 
             python::return_value_policy<python::return_by_value>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::DArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::DArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::DArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::DArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::DArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::DArray::operator>, (python::arg("self"), python::arg("array")));

    python::class_<Util::SArray, Util::SArray::SharedPointer>("SArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::SArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::SArray, 
             python::return_value_policy<python::return_by_value>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::SArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::SArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::SArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::SArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::SArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::SArray::operator>, (python::arg("self"), python::arg("array")));

    python::class_<Util::BitSetArray, Util::BitSetArray::SharedPointer>("BitSetArray", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::BitSetArray&>((python::arg("self"), python::arg("array"))))
        .def(ArrayVisitor<Util::BitSetArray, 
             python::return_internal_reference<>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("__eq__", &Util::BitSetArray::operator==, (python::arg("self"), python::arg("array")))
        .def("__ne__", &Util::BitSetArray::operator!=, (python::arg("self"), python::arg("array")))
        .def("__le__", &Util::BitSetArray::operator<=, (python::arg("self"), python::arg("array")))
        .def("__ge__", &Util::BitSetArray::operator>=, (python::arg("self"), python::arg("array")))
        .def("__lt__", &Util::BitSetArray::operator<, (python::arg("self"), python::arg("array")))
        .def("__gt__", &Util::BitSetArray::operator>, (python::arg("self"), python::arg("array")));
}
