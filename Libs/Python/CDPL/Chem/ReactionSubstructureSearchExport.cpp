/* 
 * ReactionSubstructureSearchExport.cpp 
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

#include "CDPL/Chem/ReactionSubstructureSearch.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportReactionSubstructureSearch()
{
    using namespace boost;
    using namespace CDPL;

    Chem::AtomBondMapping& (Chem::ReactionSubstructureSearch::*getMappingFunc)(std::size_t) = &Chem::ReactionSubstructureSearch::getMapping;

    bool (Chem::ReactionSubstructureSearch::*uniqueMappingsOnlyGetFunc)() const = &Chem::ReactionSubstructureSearch::uniqueMappingsOnly;
    void (Chem::ReactionSubstructureSearch::*uniqueMappingsOnlySetFunc)(bool) = &Chem::ReactionSubstructureSearch::uniqueMappingsOnly;

    python::class_<Chem::ReactionSubstructureSearch, boost::noncopyable>("ReactionSubstructureSearch", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::Reaction&>((python::arg("self"), python::arg("query")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::ReactionSubstructureSearch>())    
        .def("mappingExists", &Chem::ReactionSubstructureSearch::mappingExists, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("findMappings", &Chem::ReactionSubstructureSearch::findMappings, 
             (python::arg("self"), python::arg("target")), python::with_custodian_and_ward<1, 2>())
        .def("getNumMappings", &Chem::ReactionSubstructureSearch::getNumMappings, python::arg("self"))
        .def("getMapping", getMappingFunc, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<1>())
        .def("uniqueMappingsOnly", uniqueMappingsOnlySetFunc, (python::arg("self"), python::arg("unique")))
        .def("uniqueMappingsOnly", uniqueMappingsOnlyGetFunc, python::arg("self"))
        .def("getMaxNumMappings", &Chem::ReactionSubstructureSearch::getMaxNumMappings, python::arg("self"))
        .def("setMaxNumMappings", &Chem::ReactionSubstructureSearch::setMaxNumMappings, 
             (python::arg("self"), python::arg("max_num_mappings")))
        .def("getEnabledReactionRoles", &Chem::ReactionSubstructureSearch::getEnabledReactionRoles, python::arg("self")) 
        .def("setEnabledReactionRoles", &Chem::ReactionSubstructureSearch::setEnabledReactionRoles, 
             (python::arg("self"), python::arg("roles")))
        .def("setQuery", &Chem::ReactionSubstructureSearch::setQuery, (python::arg("self"), python::arg("query")), 
             python::with_custodian_and_ward<1, 2>())
        .add_property("enabledReactionRoles", &Chem::ReactionSubstructureSearch::getEnabledReactionRoles, 
                      &Chem::ReactionSubstructureSearch::setEnabledReactionRoles)
        .add_property("numMappings", &Chem::ReactionSubstructureSearch::getNumMappings)
        .add_property("uniqueMappings", uniqueMappingsOnlyGetFunc, uniqueMappingsOnlySetFunc)
        .add_property("maxNumMappings", &Chem::ReactionSubstructureSearch::getMaxNumMappings, 
                      &Chem::ReactionSubstructureSearch::setMaxNumMappings)
        .def("__getitem__", getMappingFunc, (python::arg("self"), python::arg("idx")), 
             python::return_internal_reference<1>())
        .def("__len__", &Chem::ReactionSubstructureSearch::getNumMappings, python::arg("self"))
        .def("__nonzero__", &Chem::ReactionSubstructureSearch::mappingExists, python::arg("self"))
        .def("__bool__", &Chem::ReactionSubstructureSearch::mappingExists, python::arg("self"));
}
