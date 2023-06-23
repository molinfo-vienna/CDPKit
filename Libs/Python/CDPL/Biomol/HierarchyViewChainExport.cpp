/* 
 * HierarchyViewChainExport.cpp 
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

#include "CDPL/Biomol/HierarchyViewChain.hpp"

#include "ClassExports.hpp"


void CDPLPythonBiomol::exportHierarchyViewChain()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Biomol::HierarchyViewChain, python::bases<Biomol::HierarchyViewNode>, boost::noncopyable>("HierarchyViewChain", python::no_init)
        .def("getNumFragments", &Biomol::HierarchyViewChain::getNumFragments, python::arg("self"))
        .def("getFragment", &Biomol::HierarchyViewChain::getFragment, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<>())
        .def("__len__", &Biomol::HierarchyViewChain::getNumFragments, python::arg("self"))
        .def("__getitem__", &Biomol::HierarchyViewChain::getFragment, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<>())
        .add_property("numFragments", &Biomol::HierarchyViewChain::getNumFragments);
}
