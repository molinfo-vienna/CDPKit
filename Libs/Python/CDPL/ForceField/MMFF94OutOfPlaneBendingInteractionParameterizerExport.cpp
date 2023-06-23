/* 
 * MMFF94OutOfPlaneBendingInteractionParameterizerExport.cpp 
 *
 * This file is part of the Chemical Parameterizer Processing Toolkit
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

#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionParameterizer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94OutOfPlaneBendingInteractionParameterizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer, 
                   ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::SharedPointer>("MMFF94OutOfPlaneBendingInteractionParameterizer", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer&>((python::arg("self"), python::arg("parameterizer"))))
        .def(python::init<const Chem::MolecularGraph&, ForceField::MMFF94OutOfPlaneBendingInteractionData&, bool>(
                 (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("strict"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer>())    
        .def("setFilterFunction", &ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setAtomTypeFunction", &ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setAtomTypeFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setOutOfPlaneBendingParameterTable", &ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setOutOfPlaneBendingParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setAtomTypePropertyTable", &ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setAtomTypePropertyTable, 
             (python::arg("self"), python::arg("table")))
        .def("setParameterAtomTypeMap", &ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::setParameterAtomTypeMap, 
             (python::arg("self"), python::arg("map")))
        .def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::operator=),
             (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
        .def("parameterize", &ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer::parameterize, 
             (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), python::arg("strict")));
}
