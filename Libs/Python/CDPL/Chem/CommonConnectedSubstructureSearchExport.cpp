/* 
 * CommonConnectedSubstructureSearchExport.cpp 
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

#include "CDPL/Chem/CommonConnectedSubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportCommonConnectedSubstructureSearch()
{
    using namespace boost;
    using namespace CDPL;

    Chem::AtomBondMapping& (Chem::CommonConnectedSubstructureSearch::*getMappingFunc)(std::size_t) = &Chem::CommonConnectedSubstructureSearch::getMapping;

    bool (Chem::CommonConnectedSubstructureSearch::*uniqueMappingsOnlyGetFunc)() const = &Chem::CommonConnectedSubstructureSearch::uniqueMappingsOnly;
    void (Chem::CommonConnectedSubstructureSearch::*uniqueMappingsOnlySetFunc)(bool) = &Chem::CommonConnectedSubstructureSearch::uniqueMappingsOnly;

    python::class_<Chem::CommonConnectedSubstructureSearch, Chem::CommonConnectedSubstructureSearch::SharedPointer,
                   boost::noncopyable>("CommonConnectedSubstructureSearch", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("query")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::CommonConnectedSubstructureSearch>())
        .def("setAtomMatchExpressionFunction", &Chem::CommonConnectedSubstructureSearch::setAtomMatchExpressionFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setBondMatchExpressionFunction", &Chem::CommonConnectedSubstructureSearch::setBondMatchExpressionFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setMolecularGraphMatchExpressionFunction", &Chem::CommonConnectedSubstructureSearch::setMolecularGraphMatchExpressionFunction, 
             (python::arg("self"), python::arg("func")))
        .def("mappingExists", &Chem::CommonConnectedSubstructureSearch::mappingExists, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("findAllMappings", &Chem::CommonConnectedSubstructureSearch::findAllMappings, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("findMaxMappings", &Chem::CommonConnectedSubstructureSearch::findMaxMappings, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("getNumMappings", &Chem::CommonConnectedSubstructureSearch::getNumMappings, python::arg("self"))
        .def("getMapping", getMappingFunc, (python::arg("self"), python::arg("idx")), 
             python::return_internal_reference<1>())
        .def("uniqueMappingsOnly", uniqueMappingsOnlySetFunc, (python::arg("self"), python::arg("unique")))
        .def("uniqueMappingsOnly", uniqueMappingsOnlyGetFunc, python::arg("self"))
        .def("getMaxNumMappings", &Chem::CommonConnectedSubstructureSearch::getMaxNumMappings, 
             python::arg("self"))
        .def("setMaxNumMappings", &Chem::CommonConnectedSubstructureSearch::setMaxNumMappings,
             (python::arg("self"), python::arg("max_num_mappings")))
        .def("getMinSubstructureSize", &Chem::CommonConnectedSubstructureSearch::getMinSubstructureSize, 
             python::arg("self"))
        .def("setMinSubstructureSize", &Chem::CommonConnectedSubstructureSearch::setMinSubstructureSize, 
             (python::arg("self"), python::arg("min_size")))
        .def("setQuery", &Chem::CommonConnectedSubstructureSearch::setQuery, 
             (python::arg("self"), python::arg("query")), python::with_custodian_and_ward<1, 2>())
        .add_property("numMappings", &Chem::CommonConnectedSubstructureSearch::getNumMappings)
        .add_property("uniqueMappings", uniqueMappingsOnlyGetFunc, uniqueMappingsOnlySetFunc)
        .add_property("maxNumMappings", &Chem::CommonConnectedSubstructureSearch::getMaxNumMappings, 
                      &Chem::CommonConnectedSubstructureSearch::setMaxNumMappings)
        .add_property("minSubstructureSize", &Chem::CommonConnectedSubstructureSearch::getMinSubstructureSize, 
                      &Chem::CommonConnectedSubstructureSearch::setMinSubstructureSize)
        .def("__getitem__", getMappingFunc, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<1>())
        .def("__len__", &Chem::CommonConnectedSubstructureSearch::getNumMappings, python::arg("self"))
        .def("__nonzero__", &Chem::CommonConnectedSubstructureSearch::mappingExists, python::arg("self"))
        .def("__bool__", &Chem::CommonConnectedSubstructureSearch::mappingExists, python::arg("self"));
}
