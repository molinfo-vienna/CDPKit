/* 
 * ReactionPropertyExport.cpp 
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

#include "CDPL/Chem/ReactionProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ReactionProperty {};
}


void CDPLPythonChem::exportReactionProperties()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ReactionProperty, boost::noncopyable>("ReactionProperty", python::no_init)
        .def_readonly("NAME", &Chem::ReactionProperty::NAME)
        .def_readonly("COMMENT", &Chem::ReactionProperty::COMMENT)
        .def_readonly("TIMESTAMP", &Chem::ReactionProperty::TIMESTAMP)
        .def_readonly("MATCH_EXPRESSION", &Chem::ReactionProperty::MATCH_EXPRESSION)
        .def_readonly("MATCH_CONSTRAINTS", &Chem::ReactionProperty::MATCH_CONSTRAINTS)
        .def_readonly("COMPONENT_GROUPS", &Chem::ReactionProperty::COMPONENT_GROUPS)
        .def_readonly("ATOM_MAPPING", &Chem::ReactionProperty::ATOM_MAPPING)
        .def_readonly("REACTION_DATA", &Chem::ReactionProperty::REACTION_DATA)
        .def_readonly("MDL_USER_INITIALS", &Chem::ReactionProperty::MDL_USER_INITIALS)
        .def_readonly("MDL_PROGRAM_NAME", &Chem::ReactionProperty::MDL_PROGRAM_NAME)
        .def_readonly("MDL_REGISTRY_NUMBER", &Chem::ReactionProperty::MDL_REGISTRY_NUMBER)
        .def_readonly("MDL_MOLECULE_RECORD", &Chem::ReactionProperty::MDL_MOLECULE_RECORD)
        .def_readonly("MDL_INTERNAL_REGISTRY_NUMBER", &Chem::ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER)
        .def_readonly("MDL_EXTERNAL_REGISTRY_NUMBER", &Chem::ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER)
        .def_readonly("MDL_RXN_FILE_VERSION", &Chem::ReactionProperty::MDL_RXN_FILE_VERSION);
}
