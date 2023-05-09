/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HierarchyViewExport.cpp 
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

#include "CDPL/Biomol/HierarchyView.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonBiomol::exportHierarchyView()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Biomol::HierarchyView, Biomol::HierarchyView::SharedPointer, boost::noncopyable>("HierarchyView", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph")))
	     [python::with_custodian_and_ward<1, 2>()])
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::HierarchyView>())	
	.def("build", &Biomol::HierarchyView::build, (python::arg("self"), python::arg("molgraph")), 
	     python::with_custodian_and_ward<1, 2>())
	.def("getResidues", &Biomol::HierarchyView::getResidues, python::arg("self"),
	     python::return_internal_reference<>())
	.def("getNumModels", &Biomol::HierarchyView::getNumModels, python::arg("self"))
	.def("getModel", &Biomol::HierarchyView::getModel, (python::arg("self"), python::arg("idx")),
	     python::return_internal_reference<>())
	.def("hasModelWithNumber", &Biomol::HierarchyView::hasModelWithNumber, (python::arg("self"), python::arg("num")))
	.def("getModelByNumber", &Biomol::HierarchyView::getModelByNumber, (python::arg("self"), python::arg("num")),
	     python::return_internal_reference<>())
	.def("__len__", &Biomol::HierarchyView::getNumModels, python::arg("self"))
	.def("__getitem__", &Biomol::HierarchyView::getModel, (python::arg("self"), python::arg("idx")),
	     python::return_internal_reference<>())
	.add_property("numModels", &Biomol::HierarchyView::getNumModels)
	.add_property("residues", python::make_function(&Biomol::HierarchyView::getResidues, python::return_internal_reference<>()));
}
