/* 
 * MaxCommonBondSubstructureSearchExport.cpp 
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

#include "CDPL/Chem/MaxCommonBondSubstructureSearch.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportMaxCommonBondSubstructureSearch()
{
    using namespace boost;
    using namespace CDPL;

    Chem::AtomBondMapping& (Chem::MaxCommonBondSubstructureSearch::*getMappingFunc)(std::size_t) = &Chem::MaxCommonBondSubstructureSearch::getMapping;

    bool (Chem::MaxCommonBondSubstructureSearch::*uniqueMappingsOnlyGetFunc)() const = &Chem::MaxCommonBondSubstructureSearch::uniqueMappingsOnly;
    void (Chem::MaxCommonBondSubstructureSearch::*uniqueMappingsOnlySetFunc)(bool) = &Chem::MaxCommonBondSubstructureSearch::uniqueMappingsOnly;

    python::class_<Chem::MaxCommonBondSubstructureSearch, 
        boost::noncopyable>("MaxCommonBondSubstructureSearch", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("query")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MaxCommonBondSubstructureSearch>())    
        .def("mappingExists", &Chem::MaxCommonBondSubstructureSearch::mappingExists, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("findMappings", &Chem::MaxCommonBondSubstructureSearch::findMappings, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("getNumMappings", &Chem::MaxCommonBondSubstructureSearch::getNumMappings, python::arg("self"))
        .def("getMapping", getMappingFunc, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<1>())
        .def("uniqueMappingsOnly", uniqueMappingsOnlySetFunc, (python::arg("self"), python::arg("unique")))
        .def("uniqueMappingsOnly", uniqueMappingsOnlyGetFunc, python::arg("self"))
        .def("getMaxNumMappings", &Chem::MaxCommonBondSubstructureSearch::getMaxNumMappings, python::arg("self"))
        .def("setMaxNumMappings", &Chem::MaxCommonBondSubstructureSearch::setMaxNumMappings, 
             (python::arg("self"), python::arg("max_num_mappings")))
        .def("getMinSubstructureSize", &Chem::MaxCommonBondSubstructureSearch::getMinSubstructureSize, 
             python::arg("self"))
        .def("setMinSubstructureSize", &Chem::MaxCommonBondSubstructureSearch::setMinSubstructureSize, 
             (python::arg("self"), python::arg("min_size")))
        .def("setQuery", &Chem::MaxCommonBondSubstructureSearch::setQuery, 
             (python::arg("self"), python::arg("query")), python::with_custodian_and_ward<1, 2>())
        .add_property("numMappings", &Chem::MaxCommonBondSubstructureSearch::getNumMappings)
        .add_property("uniqueMappings", uniqueMappingsOnlyGetFunc, uniqueMappingsOnlySetFunc)
        .add_property("maxNumMappings", &Chem::MaxCommonBondSubstructureSearch::getMaxNumMappings, 
                      &Chem::MaxCommonBondSubstructureSearch::setMaxNumMappings)
        .add_property("minSubstructureSize", &Chem::MaxCommonBondSubstructureSearch::getMinSubstructureSize, 
                      &Chem::MaxCommonBondSubstructureSearch::setMinSubstructureSize)
        .def("__getitem__", getMappingFunc, (python::arg("self"), python::arg("idx")), 
             python::return_internal_reference<1>())
        .def("__len__", &Chem::MaxCommonBondSubstructureSearch::getNumMappings, python::arg("self"))
        .def("__nonzero__", &Chem::MaxCommonBondSubstructureSearch::mappingExists, python::arg("self"))
        .def("__bool__", &Chem::MaxCommonBondSubstructureSearch::mappingExists, python::arg("self"));
}
