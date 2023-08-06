/* 
 * FragmentConformerGeneratorSettingsExport.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportFragmentConformerGeneratorSettings()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ConfGen::FragmentConformerGeneratorSettings> cl("FragmentConformerGeneratorSettings", python::no_init);
    python::scope scope = cl;

    python::class_<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings>("FragmentSettings")
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ConfGen::FragmentConformerGeneratorSettings::FragmentSettings&>((python::arg("self"), python::arg("settings"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings>())
        .def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::operator=), 
             (python::arg("self"), python::arg("settings")), python::return_self<>())
        .def("setMaxNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMaxNumSampledConformers, 
             (python::arg("self"), python::arg("max_num")))
        .def("getMaxNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMaxNumSampledConformers, 
             python::arg("self"))
        .def("setMinNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMinNumSampledConformers, 
             (python::arg("self"), python::arg("min_num")))
        .def("getMinNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMinNumSampledConformers, 
             python::arg("self"))
        .def("setTimeout", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setTimeout, 
             (python::arg("self"), python::arg("mil_secs")))
        .def("getTimeout", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getTimeout, 
             python::arg("self"))
        .def("setEnergyWindow", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setEnergyWindow, 
             (python::arg("self"), python::arg("win_size")))
        .def("getEnergyWindow", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getEnergyWindow, 
             python::arg("self"))
        .def("setMaxNumOutputConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMaxNumOutputConformers, 
             (python::arg("self"), python::arg("max_num")))
        .def("getMaxNumOutputConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMaxNumOutputConformers, 
             python::arg("self"))
        .def("setMinRMSD", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMinRMSD, 
             (python::arg("self"), python::arg("min_rmsd")))
        .def("getMinRMSD", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMinRMSD, 
             python::arg("self"))
        .add_property("maxNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMaxNumSampledConformers, 
                      &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMaxNumSampledConformers)
        .add_property("minNumSampledConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMinNumSampledConformers, 
                      &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMinNumSampledConformers)
        .add_property("timeout", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getTimeout,
                      &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setTimeout)
        .add_property("energyWindow", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getEnergyWindow,
                      &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setEnergyWindow)
        .add_property("maxNumOutputConformers", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMaxNumOutputConformers, 
                      &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMaxNumOutputConformers)
        .add_property("minRMSD", &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMinRMSD, 
                      &ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMinRMSD);

    typedef void (ConfGen::FragmentConformerGeneratorSettings::*SetBoolFunc)(bool);
    typedef bool (ConfGen::FragmentConformerGeneratorSettings::*GetBoolFunc)() const;

    cl
        .def(python::init<>(python::arg("self")))
        .def(python::init<const ConfGen::FragmentConformerGeneratorSettings&>((python::arg("self"), python::arg("settings"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::FragmentConformerGeneratorSettings>())
        .def("assign", CDPLPythonBase::copyAssOp(&ConfGen::FragmentConformerGeneratorSettings::operator=), 
             (python::arg("self"), python::arg("settings")), python::return_self<>())
        .def("preserveInputBondingGeometries", SetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::preserveInputBondingGeometries), 
             (python::arg("self"), python::arg("preserve")))
        .def("preserveInputBondingGeometries", GetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::preserveInputBondingGeometries), 
             python::arg("self"))
        .def("setForceFieldType", &ConfGen::FragmentConformerGeneratorSettings::setForceFieldType, 
             (python::arg("self"), python::arg("type")))
        .def("getForceFieldType", &ConfGen::FragmentConformerGeneratorSettings::getForceFieldType, 
             python::arg("self"))
        .def("strictForceFieldParameterization", SetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization), 
             (python::arg("self"), python::arg("strict")))
        .def("strictForceFieldParameterization", GetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization), 
             python::arg("self"))
        .def("setDielectricConstant", &ConfGen::FragmentConformerGeneratorSettings::setDielectricConstant, 
             (python::arg("self"), python::arg("de_const")))
        .def("getDielectricConstant", &ConfGen::FragmentConformerGeneratorSettings::getDielectricConstant, 
             python::arg("self"))
        .def("setDistanceExponent", &ConfGen::FragmentConformerGeneratorSettings::setDistanceExponent, 
             (python::arg("self"), python::arg("dist_expo")))
        .def("getDistanceExponent", &ConfGen::FragmentConformerGeneratorSettings::getDistanceExponent, 
             python::arg("self"))
        .def("setMaxNumRefinementIterations", &ConfGen::FragmentConformerGeneratorSettings::setMaxNumRefinementIterations, 
             (python::arg("self"), python::arg("max_num")))
        .def("getMaxNumRefinementIterations", &ConfGen::FragmentConformerGeneratorSettings::getMaxNumRefinementIterations, 
             python::arg("self"))
        .def("setRefinementStopGradient", &ConfGen::FragmentConformerGeneratorSettings::setRefinementStopGradient, 
             (python::arg("self"), python::arg("grad_norm")))
        .def("getRefinementStopGradient", &ConfGen::FragmentConformerGeneratorSettings::getRefinementStopGradient, 
             python::arg("self"))
        .def("setMacrocycleRotorBondCountThreshold", &ConfGen::FragmentConformerGeneratorSettings::setMacrocycleRotorBondCountThreshold, 
             (python::arg("self"), python::arg("max_size")))
        .def("getMacrocycleRotorBondCountThreshold", &ConfGen::FragmentConformerGeneratorSettings::getMacrocycleRotorBondCountThreshold, 
             python::arg("self"))
        .def("getChainSettings", 
             static_cast<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
             (&ConfGen::FragmentConformerGeneratorSettings::getChainSettings),
             python::arg("self"), python::return_internal_reference<>())
        .def("getMacrocycleSettings", 
             static_cast<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
             (&ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings),
             python::arg("self"), python::return_internal_reference<>())
        .def("getSmallRingSystemSettings", 
             static_cast<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
             (&ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings),
             python::arg("self"), python::return_internal_reference<>())
        .def("setSmallRingSystemSamplingFactor", &ConfGen::FragmentConformerGeneratorSettings::setSmallRingSystemSamplingFactor, 
             (python::arg("self"), python::arg("min_rmsd")))
        .def("getSmallRingSystemSamplingFactor", &ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSamplingFactor, 
             python::arg("self"))
        .def_readonly("DEFAULT", ConfGen::FragmentConformerGeneratorSettings::DEFAULT)
        .def_readonly("FAST", ConfGen::FragmentConformerGeneratorSettings::FAST)
        .def_readonly("THOROUGH", ConfGen::FragmentConformerGeneratorSettings::THOROUGH)
        .add_property("preserveInputBondingGeom", GetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::preserveInputBondingGeometries), 
                      SetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::preserveInputBondingGeometries))
        .add_property("forceFieldType", &ConfGen::FragmentConformerGeneratorSettings::getForceFieldType, 
                      &ConfGen::FragmentConformerGeneratorSettings::setForceFieldType)
        .add_property("strictForceFieldParam", GetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization), 
                      SetBoolFunc(&ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization))
        .add_property("dielectricConstant", &ConfGen::FragmentConformerGeneratorSettings::getDielectricConstant, 
                      &ConfGen::FragmentConformerGeneratorSettings::setDielectricConstant)
        .add_property("distanceExponent", &ConfGen::FragmentConformerGeneratorSettings::getDistanceExponent, 
                      &ConfGen::FragmentConformerGeneratorSettings::setDistanceExponent)
        .add_property("maxNumRefinementIterations", &ConfGen::FragmentConformerGeneratorSettings::getMaxNumRefinementIterations, 
                      &ConfGen::FragmentConformerGeneratorSettings::setMaxNumRefinementIterations)
        .add_property("refinementStopGradient", &ConfGen::FragmentConformerGeneratorSettings::getRefinementStopGradient,
                      &ConfGen::FragmentConformerGeneratorSettings::setRefinementStopGradient)
        .add_property("macrocycleRotorBondCountThresh", &ConfGen::FragmentConformerGeneratorSettings::getMacrocycleRotorBondCountThreshold, 
                      &ConfGen::FragmentConformerGeneratorSettings::setMacrocycleRotorBondCountThreshold)
        .add_property("chainSettings", 
                      python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
                                            (&ConfGen::FragmentConformerGeneratorSettings::getChainSettings),
                                            python::return_internal_reference<>()))
        .add_property("macrocycleSettings", 
                      python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
                                            (&ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings),
                                            python::return_internal_reference<>()))
        .add_property("smallRingSysSettings", 
                      python::make_function(static_cast<ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& (ConfGen::FragmentConformerGeneratorSettings::*)()>
                                            (&ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings),
                                            python::return_internal_reference<>()))
        .add_property("smallRingSysSamplingFactor", &ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSamplingFactor, 
                      &ConfGen::FragmentConformerGeneratorSettings::setSmallRingSystemSamplingFactor);
}
