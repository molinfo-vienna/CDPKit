/* 
 * MMFF94ElectrostaticInteractionParameterizerExport.cpp 
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

#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94ElectrostaticInteractionParameterizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94ElectrostaticInteractionParameterizer, 
                   ForceField::MMFF94ElectrostaticInteractionParameterizer::SharedPointer>("MMFF94ElectrostaticInteractionParameterizer", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ForceField::MMFF94ElectrostaticInteractionParameterizer&>((python::arg("self"), python::arg("parameterizer"))))
        .def(python::init<const Chem::MolecularGraph&, ForceField::MMFF94ElectrostaticInteractionList&, bool>(
                 (python::arg("self"), python::arg("molgraph"), python::arg("ia_list"), python::arg("strict"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94ElectrostaticInteractionParameterizer>())    
        .def("setFilterFunction", &ForceField::MMFF94ElectrostaticInteractionParameterizer::setFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setAtomChargeFunction", &ForceField::MMFF94ElectrostaticInteractionParameterizer::setAtomChargeFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setTopologicalDistanceFunction", &ForceField::MMFF94ElectrostaticInteractionParameterizer::setTopologicalDistanceFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setDielectricConstant", &ForceField::MMFF94ElectrostaticInteractionParameterizer::setDielectricConstant, 
             (python::arg("self"), python::arg("de_const")))
        .def("setDistanceExponent", &ForceField::MMFF94ElectrostaticInteractionParameterizer::setDistanceExponent, 
             (python::arg("self"), python::arg("dist_expo")))
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94ElectrostaticInteractionParameterizer>(),
             (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
        .def("parameterize", &ForceField::MMFF94ElectrostaticInteractionParameterizer::parameterize, 
             (python::arg("self"), python::arg("molgraph"), python::arg("ia_list"), python::arg("strict")))
        .def_readonly("DEF_DISTANCE_EXPONENT", ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DISTANCE_EXPONENT)
        .def_readonly("DEF_DIELECTRIC_CONSTANT", ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DIELECTRIC_CONSTANT)
        .def_readonly("DIELECTRIC_CONSTANT_WATER", ForceField::MMFF94ElectrostaticInteractionParameterizer::DIELECTRIC_CONSTANT_WATER);
}
