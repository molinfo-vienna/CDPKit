/* 
 * SubstructureEditorExport.cpp 
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

#include "CDPL/Chem/SubstructureEditor.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportSubstructureEditor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::SubstructureEditor, Chem::SubstructureEditor::SharedPointer,
                   boost::noncopyable>("SubstructureEditor", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::SubstructureEditor&>((python::arg("self"), python::arg("editor"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SubstructureEditor>())
        .def("assign", &Chem::SubstructureEditor::operator=, (python::arg("self"), python::arg("editor")),
             python::return_self<>())
        .def("addSearchPattern", &Chem::SubstructureEditor::addSearchPattern,
             (python::arg("self"), python::arg("molgraph")))
        .def("getNumSearchPatterns", &Chem::SubstructureEditor::getNumSearchPatterns, python::arg("self"))
        .def("getSearchPattern", &Chem::SubstructureEditor::getSearchPattern,
             (python::arg("self"), python::arg("idx")),
             python::return_value_policy<python::copy_const_reference>())
        .def("removeSearchPattern", static_cast<void (Chem::SubstructureEditor::*)(std::size_t)>
             (&Chem::SubstructureEditor::removeSearchPattern),
             (python::arg("self"), python::arg("idx")))
        .def("clearSearchPatterns", &Chem::SubstructureEditor::clearSearchPatterns, python::arg("self"))
        .def("addExcludePattern", &Chem::SubstructureEditor::addExcludePattern,
             (python::arg("self"), python::arg("molgraph")))
        .def("getNumExcludePatterns", &Chem::SubstructureEditor::getNumExcludePatterns, python::arg("self"))
        .def("getExcludePattern", &Chem::SubstructureEditor::getExcludePattern,
             (python::arg("self"), python::arg("idx")),
             python::return_value_policy<python::copy_const_reference>())
        .def("removeExcludePattern", static_cast<void (Chem::SubstructureEditor::*)(std::size_t)>
             (&Chem::SubstructureEditor::removeExcludePattern),
             (python::arg("self"), python::arg("idx")))
        .def("clearExcludePatterns", &Chem::SubstructureEditor::clearExcludePatterns, python::arg("self"))
        .def("setResultPattern", &Chem::SubstructureEditor::setResultPattern,
             (python::arg("self"), python::arg("molgraph")))
        .def("getResultPattern", &Chem::SubstructureEditor::getResultPattern,
             python::arg("self"), python::return_value_policy<python::copy_const_reference>())
        .def("edit", static_cast<std::size_t (Chem::SubstructureEditor::*)(Chem::Molecule&)>(&Chem::SubstructureEditor::edit),
             (python::arg("self"), python::arg("mol")))
        .def("edit", static_cast<std::size_t (Chem::SubstructureEditor::*)(const Chem::MolecularGraph&, Chem::Molecule&)>
             (&Chem::SubstructureEditor::edit),
             (python::arg("self"), python::arg("molgraph"), python::arg("res_mol")))
        .add_property("numSearchPatterns", &Chem::SubstructureEditor::getNumSearchPatterns)
        .add_property("numExcludePatterns", &Chem::SubstructureEditor::getNumExcludePatterns)
        .add_property("resultPattern",
                      python::make_function(&Chem::SubstructureEditor::getResultPattern,
                                            python::return_value_policy<python::copy_const_reference>()),
                      &Chem::SubstructureEditor::setResultPattern);
}
