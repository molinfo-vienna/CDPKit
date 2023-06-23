/* 
 * MMFF94InteractionParameterizerExport.cpp 
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

#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportMMFF94InteractionParameterizer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::MMFF94InteractionParameterizer, ForceField::MMFF94InteractionParameterizer::SharedPointer>("MMFF94InteractionParameterizer", python::no_init)
        .def(python::init<unsigned int>((python::arg("self"), python::arg("param_set") = ForceField::MMFF94ParameterSet::STATIC)))
        .def(python::init<const ForceField::MMFF94InteractionParameterizer&>((python::arg("self"), python::arg("parameterizer"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94InteractionParameterizer>())    
        .def("setBondStretchingFilterFunction", &ForceField::MMFF94InteractionParameterizer::setBondStretchingFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setAngleBendingFilterFunction", &ForceField::MMFF94InteractionParameterizer::setAngleBendingFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setStretchBendFilterFunction", &ForceField::MMFF94InteractionParameterizer::setStretchBendFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setOutOfPlaneBendingFilterFunction", &ForceField::MMFF94InteractionParameterizer::setOutOfPlaneBendingFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setTorsionFilterFunction", &ForceField::MMFF94InteractionParameterizer::setTorsionFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("setElectrostaticFilterFunction", &ForceField::MMFF94InteractionParameterizer::setElectrostaticFilterFunction,
             (python::arg("self"), python::arg("func"))) 
        .def("setVanDerWaalsFilterFunction", &ForceField::MMFF94InteractionParameterizer::setVanDerWaalsFilterFunction, 
             (python::arg("self"), python::arg("func"))) 
        .def("clearFilterFunctions", &ForceField::MMFF94InteractionParameterizer::clearFilterFunctions, 
             python::arg("self"))
        .def("setSymbolicAtomTypePatternTable", &ForceField::MMFF94InteractionParameterizer::setSymbolicAtomTypePatternTable, 
             (python::arg("self"), python::arg("table")))
        .def("setHeavyToHydrogenAtomTypeMap", &ForceField::MMFF94InteractionParameterizer::setHeavyToHydrogenAtomTypeMap, 
             (python::arg("self"), python::arg("map")))
        .def("setSymbolicToNumericAtomTypeMap", &ForceField::MMFF94InteractionParameterizer::setSymbolicToNumericAtomTypeMap, 
             (python::arg("self"), python::arg("map")))
        .def("setAromaticAtomTypeDefinitionTable", &ForceField::MMFF94InteractionParameterizer::setAromaticAtomTypeDefinitionTable,
             (python::arg("self"), python::arg("table")))
        .def("setAtomTypePropertyTable", &ForceField::MMFF94InteractionParameterizer::setAtomTypePropertyTable, 
             (python::arg("self"), python::arg("table")))
        .def("setFormalAtomChargeDefinitionTable", &ForceField::MMFF94InteractionParameterizer::setFormalAtomChargeDefinitionTable, 
             (python::arg("self"), python::arg("table")))
        .def("setBondChargeIncrementTable", &ForceField::MMFF94InteractionParameterizer::setBondChargeIncrementTable,
             (python::arg("self"), python::arg("table")))
        .def("setPartialBondChargeIncrementTable", &ForceField::MMFF94InteractionParameterizer::setPartialBondChargeIncrementTable, 
             (python::arg("self"), python::arg("table")))
        .def("setPrimaryToParameterAtomTypeMap", &ForceField::MMFF94InteractionParameterizer::setPrimaryToParameterAtomTypeMap, 
             (python::arg("self"), python::arg("map")))
        .def("setAngleBendingParameterTable", &ForceField::MMFF94InteractionParameterizer::setAngleBendingParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setBondStretchingParameterTable", &ForceField::MMFF94InteractionParameterizer::setBondStretchingParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setBondStretchingRuleParameterTable", &ForceField::MMFF94InteractionParameterizer::setBondStretchingRuleParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setStretchBendParameterTable", &ForceField::MMFF94InteractionParameterizer::setStretchBendParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setDefaultStretchBendParameterTable", &ForceField::MMFF94InteractionParameterizer::setDefaultStretchBendParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setOutOfPlaneBendingParameterTable", &ForceField::MMFF94InteractionParameterizer::setOutOfPlaneBendingParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setTorsionParameterTable", &ForceField::MMFF94InteractionParameterizer::setTorsionParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setVanDerWaalsParameterTable", &ForceField::MMFF94InteractionParameterizer::setVanDerWaalsParameterTable, 
             (python::arg("self"), python::arg("table")))
        .def("setDielectricConstant", &ForceField::MMFF94InteractionParameterizer::setDielectricConstant, 
             (python::arg("self"), python::arg("de_const")))
        .def("setDistanceExponent", &ForceField::MMFF94InteractionParameterizer::setDistanceExponent, 
             (python::arg("self"), python::arg("dist_expo")))
        .def("setParameterSet", &ForceField::MMFF94InteractionParameterizer::setParameterSet, 
             (python::arg("self"), python::arg("param_set")))
        .def("assign", CDPLPythonBase::copyAssOp(&ForceField::MMFF94InteractionParameterizer::operator=),
             (python::arg("self"), python::arg("parameterizer")), python::return_self<>())
        .def("parameterize", &ForceField::MMFF94InteractionParameterizer::parameterize, 
             (python::arg("self"), python::arg("molgraph"), python::arg("ia_data"), 
              python::arg("ia_types") = ForceField::InteractionType::ALL, python::arg("strict") = true));
}
