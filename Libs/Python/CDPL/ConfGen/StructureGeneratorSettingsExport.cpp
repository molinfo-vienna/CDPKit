/* 
 * StructureGeneratorSettingsExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportStructureGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

    typedef void (ConfGen::StructureGeneratorSettings::*SetBoolFunc)(bool);
    typedef bool (ConfGen::StructureGeneratorSettings::*GetBoolFunc)() const;

    python::class_<ConfGen::StructureGeneratorSettings>("StructureGeneratorSettings", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ConfGen::StructureGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::StructureGeneratorSettings>())
        .def("assign", CDPLPythonBase::copyAssOp(&ConfGen::StructureGeneratorSettings::operator=), 
             (python::arg("self"), python::arg("settings")), python::return_self<>())
        .def("setGenerationMode", &ConfGen::StructureGeneratorSettings::setGenerationMode, 
             (python::arg("self"), python::arg("mode")))
        .def("getGenerationMode", &ConfGen::StructureGeneratorSettings::getGenerationMode, 
             python::arg("self"))
        .def("generateCoordinatesFromScratch", SetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch), 
             (python::arg("self"), python::arg("generate")))
        .def("generateCoordinatesFromScratch", GetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch), 
             python::arg("self"))
        .def("sampleAngleToleranceRanges", SetBoolFunc(&ConfGen::StructureGeneratorSettings::sampleAngleToleranceRanges), 
             (python::arg("self"), python::arg("sample")))
        .def("sampleAngleToleranceRanges", GetBoolFunc(&ConfGen::StructureGeneratorSettings::sampleAngleToleranceRanges), 
             python::arg("self"))
        .def("setTimeout", &ConfGen::StructureGeneratorSettings::setTimeout, 
             (python::arg("self"), python::arg("mil_secs")))
        .def("getTimeout", &ConfGen::StructureGeneratorSettings::getTimeout, 
             python::arg("self"))
        .def("setFragmentModeForceFieldType", &ConfGen::StructureGeneratorSettings::setFragmentModeForceFieldType, 
             (python::arg("self"), python::arg("type")))
        .def("getFragmentModeForceFieldType", &ConfGen::StructureGeneratorSettings::getFragmentModeForceFieldType, 
             python::arg("self"))
        .def("setDGModeForceFieldType", &ConfGen::StructureGeneratorSettings::setDGModeForceFieldType, 
             (python::arg("self"), python::arg("type")))
        .def("getDGModeForceFieldType", &ConfGen::StructureGeneratorSettings::getDGModeForceFieldType, 
             python::arg("self"))
        .def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization), 
             (python::arg("self"), python::arg("strict")))
        .def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization), 
             python::arg("self"))
        .def("setDielectricConstant", &ConfGen::StructureGeneratorSettings::setDielectricConstant, 
             (python::arg("self"), python::arg("de_const")))
        .def("getDielectricConstant", &ConfGen::StructureGeneratorSettings::getDielectricConstant, 
             python::arg("self"))
        .def("setDistanceExponent", &ConfGen::StructureGeneratorSettings::setDistanceExponent, 
             (python::arg("self"), python::arg("dist_expo")))
        .def("getDistanceExponent", &ConfGen::StructureGeneratorSettings::getDistanceExponent, 
             python::arg("self"))
        .def("setMaxNumRefinementIterations", &ConfGen::StructureGeneratorSettings::setMaxNumRefinementIterations, 
             (python::arg("self"), python::arg("max_num")))
        .def("getMaxNumRefinementIterations", &ConfGen::StructureGeneratorSettings::getMaxNumRefinementIterations, 
             python::arg("self"))
        .def("setRefinementTolerance", &ConfGen::StructureGeneratorSettings::setRefinementTolerance, 
             (python::arg("self"), python::arg("tol")))
        .def("getRefinementTolerance", &ConfGen::StructureGeneratorSettings::getRefinementTolerance, 
             python::arg("self"))
        .def("setMacrocycleRotorBondCountThreshold", &ConfGen::StructureGeneratorSettings::setMacrocycleRotorBondCountThreshold, 
             (python::arg("self"), python::arg("max_size")))
        .def("getMacrocycleRotorBondCountThreshold", &ConfGen::StructureGeneratorSettings::getMacrocycleRotorBondCountThreshold, 
             python::arg("self"))
        .def("setMaxNumSampledConformers", &ConfGen::StructureGeneratorSettings::setMaxNumSampledConformers, 
             (python::arg("self"), python::arg("max_num")))
        .def("getMaxNumSampledConformers", &ConfGen::StructureGeneratorSettings::getMaxNumSampledConformers, 
             python::arg("self"))
        .def("setConvergenceCheckCycleSize", &ConfGen::StructureGeneratorSettings::setConvergenceCheckCycleSize, 
             (python::arg("self"), python::arg("size")))
        .def("getConvergenceCheckCycleSize", &ConfGen::StructureGeneratorSettings::getConvergenceCheckCycleSize, 
             python::arg("self"))
        .def("getFragmentBuildSettings", 
             static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::StructureGeneratorSettings::*)()>
             (&ConfGen::StructureGeneratorSettings::getFragmentBuildSettings),
             python::arg("self"), python::return_internal_reference<>())
        .def_readonly("DEFAULT", ConfGen::StructureGeneratorSettings::DEFAULT)
        .add_property("generationMode", &ConfGen::StructureGeneratorSettings::getGenerationMode,
                      &ConfGen::StructureGeneratorSettings::setGenerationMode)
        .add_property("genCoordsFromScratch", GetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch),
                      SetBoolFunc(&ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch))
        .add_property("sampleAngleTolRanges", GetBoolFunc(&ConfGen::StructureGeneratorSettings::sampleAngleToleranceRanges),
                      SetBoolFunc(&ConfGen::StructureGeneratorSettings::sampleAngleToleranceRanges))
        .add_property("timeout", &ConfGen::StructureGeneratorSettings::getTimeout,
                      &ConfGen::StructureGeneratorSettings::setTimeout)
        .add_property("fragModeForceFieldType", &ConfGen::StructureGeneratorSettings::getFragmentModeForceFieldType, 
                      &ConfGen::StructureGeneratorSettings::setFragmentModeForceFieldType)
        .add_property("dgModeForceFieldType", &ConfGen::StructureGeneratorSettings::getDGModeForceFieldType, 
                      &ConfGen::StructureGeneratorSettings::setDGModeForceFieldType)
        .add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization), 
                      SetBoolFunc(&ConfGen::StructureGeneratorSettings::strictForceFieldParameterization))
        .add_property("dielectricConstant", &ConfGen::StructureGeneratorSettings::getDielectricConstant, 
                      &ConfGen::StructureGeneratorSettings::setDielectricConstant)
        .add_property("distanceExponent", &ConfGen::StructureGeneratorSettings::getDistanceExponent, 
                      &ConfGen::StructureGeneratorSettings::setDistanceExponent)
        .add_property("maxNumRefinementIterations", &ConfGen::StructureGeneratorSettings::getMaxNumRefinementIterations, 
                      &ConfGen::StructureGeneratorSettings::setMaxNumRefinementIterations)
        .add_property("refinementTolerance", &ConfGen::StructureGeneratorSettings::getRefinementTolerance,
                      &ConfGen::StructureGeneratorSettings::setRefinementTolerance)
        .add_property("macrocycleRotorBondCountThresh", &ConfGen::StructureGeneratorSettings::getMacrocycleRotorBondCountThreshold, 
                      &ConfGen::StructureGeneratorSettings::setMacrocycleRotorBondCountThreshold)
        .add_property("maxNumSampledConformers", &ConfGen::StructureGeneratorSettings::getMaxNumSampledConformers, 
                      &ConfGen::StructureGeneratorSettings::setMaxNumSampledConformers)
        .add_property("convCheckCycleSize", &ConfGen::StructureGeneratorSettings::getConvergenceCheckCycleSize, 
                      &ConfGen::StructureGeneratorSettings::setConvergenceCheckCycleSize)
        .add_property("fragmentBuildSettings", 
                      python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings& (ConfGen::StructureGeneratorSettings::*)()>
                                            (&ConfGen::StructureGeneratorSettings::getFragmentBuildSettings),
                                            python::return_internal_reference<>()));
}
