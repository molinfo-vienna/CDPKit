/* 
 * MassCompositionExport.cpp 
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

#include "CDPL/MolProp/MassComposition.hpp"

#include "Util/MapVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportMassComposition()
{
    using namespace boost;
    using namespace CDPL;

    typedef Util::Map<unsigned int, double, true> MapType;
    typedef bool (*CompFuncType)(const MapType&, const MapType&);
 
    python::class_<MolProp::MassComposition, MolProp::MassComposition::SharedPointer>("MassComposition", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const MolProp::MassComposition&>((python::arg("self"), python::arg("mass_comp"))))
        .def(CDPLPythonUtil::MapVisitor<MolProp::MassComposition, 
             python::return_value_policy<python::copy_non_const_reference>, 
             python::default_call_policies, python::default_call_policies, python::default_call_policies, false>())
        .def("__eq__", CompFuncType(&Util::operator==), (python::arg("self"), python::arg("mass_comp")))
        .def("__ne__", CompFuncType(&Util::operator!=), (python::arg("self"), python::arg("mass_comp")))
        .def("__le__", CompFuncType(&Util::operator<=), (python::arg("self"), python::arg("mass_comp")))
        .def("__ge__", CompFuncType(&Util::operator>=), (python::arg("self"), python::arg("mass_comp")))
        .def("__lt__", CompFuncType(&Util::operator<), (python::arg("self"), python::arg("mass_comp")))
        .def("__gt__", CompFuncType(&Util::operator>), (python::arg("self"), python::arg("mass_comp")));
}
