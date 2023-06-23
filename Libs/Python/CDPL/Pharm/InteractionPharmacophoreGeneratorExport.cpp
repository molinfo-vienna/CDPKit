/* 
 * InteractionPharmacophoreGeneratorExport.cpp 
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

#include "CDPL/Pharm/InteractionPharmacophoreGenerator.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportInteractionPharmacophoreGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::InteractionPharmacophoreGenerator, boost::noncopyable>("InteractionPharmacophoreGenerator", python::no_init)
        .def(python::init<Pharm::DefaultPharmacophoreGenerator::Configuration, Pharm::DefaultPharmacophoreGenerator::Configuration>
             ((python::arg("self"), python::arg("core_ph4_gen_cfg") = Pharm::DefaultPharmacophoreGenerator::DEFAULT_CONFIG, 
               python::arg("env_ph4_gen_cfg") = Pharm::DefaultPharmacophoreGenerator::DEFAULT_CONFIG)))
        .def(python::init<const Pharm::InteractionPharmacophoreGenerator&>((python::arg("self"), python::arg("gen"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::InteractionPharmacophoreGenerator>())    
        .def("assign", CDPLPythonBase::copyAssOp(&Pharm::InteractionPharmacophoreGenerator::operator=), 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setCoreEnvironmentRadius", &Pharm::InteractionPharmacophoreGenerator::setCoreEnvironmentRadius, 
             (python::arg("self"), python::arg("radius")))
        .def("getCoreEnvironmentRadius", &Pharm::InteractionPharmacophoreGenerator::getCoreEnvironmentRadius,
             python::arg("self"))
        .def("addExclusionVolumes", &Pharm::InteractionPharmacophoreGenerator::addExclusionVolumes, 
             (python::arg("self"), python::arg("add")))
        .def("exclusionVolumesAdded", &Pharm::InteractionPharmacophoreGenerator::exclusionVolumesAdded,
             python::arg("self"))
        .def("getCorePharmacophoreGenerator", static_cast<Pharm::PharmacophoreGenerator& (Pharm::InteractionPharmacophoreGenerator::*)()>(
                 &Pharm::InteractionPharmacophoreGenerator::getCorePharmacophoreGenerator),
             python::arg("self"), python::return_internal_reference<>())
        .def("getEnvironmentPharmacophoreGenerator", static_cast<Pharm::PharmacophoreGenerator& (Pharm::InteractionPharmacophoreGenerator::*)()>(
                 &Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophoreGenerator),
             python::arg("self"), python::return_internal_reference<>())
        .def("getInteractionAnalyzer", static_cast<Pharm::InteractionAnalyzer& (Pharm::InteractionPharmacophoreGenerator::*)()>(
                 &Pharm::InteractionPharmacophoreGenerator::getInteractionAnalyzer),
             python::arg("self"), python::return_internal_reference<>())
        .def("getCorePharmacophore", &Pharm::InteractionPharmacophoreGenerator::getCorePharmacophore,
             python::arg("self"), python::return_internal_reference<>())
        .def("getEnvironmentPharmacophore", &Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophore,
             python::arg("self"), python::return_internal_reference<>())
        .def("getInteractionMapping", &Pharm::InteractionPharmacophoreGenerator::getInteractionMapping,
             python::arg("self"), python::return_internal_reference<>())
        .def("getCoreEnvironment", &Pharm::InteractionPharmacophoreGenerator::getCoreEnvironment,
             python::arg("self"), python::return_internal_reference<>())
        .def("generate", &Pharm::InteractionPharmacophoreGenerator::generate,
             (python::arg("self"), python::arg("core"), python::arg("tgt"), python::arg("ia_pharm"), 
              python::arg("extract_core_env"), python::arg("append") = false))
        .add_property("coreEnvironmentRadius", &Pharm::InteractionPharmacophoreGenerator::getCoreEnvironmentRadius,
                      &Pharm::InteractionPharmacophoreGenerator::setCoreEnvironmentRadius)
        .add_property("addXVolumes", &Pharm::InteractionPharmacophoreGenerator::exclusionVolumesAdded,
                      &Pharm::InteractionPharmacophoreGenerator::addExclusionVolumes)
        .add_property("corePharmacophoreGenerator", 
                      python::make_function(static_cast<Pharm::PharmacophoreGenerator& (Pharm::InteractionPharmacophoreGenerator::*)()>(
                                                &Pharm::InteractionPharmacophoreGenerator::getCorePharmacophoreGenerator), 
                                            python::return_internal_reference<>()))
        .add_property("envPharmacophoreGenerator", 
                      python::make_function(static_cast<Pharm::PharmacophoreGenerator& (Pharm::InteractionPharmacophoreGenerator::*)()>(
                                                &Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophoreGenerator), 
                                            python::return_internal_reference<>()))
        .add_property("interactionAnalyzer", 
                      python::make_function(static_cast<Pharm::InteractionAnalyzer& (Pharm::InteractionPharmacophoreGenerator::*)()>(
                                                &Pharm::InteractionPharmacophoreGenerator::getInteractionAnalyzer), 
                                            python::return_internal_reference<>()))
        .add_property("corePharmacophore", python::make_function(&Pharm::InteractionPharmacophoreGenerator::getCorePharmacophore, 
                                                                 python::return_internal_reference<>()))
        .add_property("envPharmacophore", python::make_function(&Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophore, 
                                                                python::return_internal_reference<>()))
        .add_property("interactionMapping", python::make_function(&Pharm::InteractionPharmacophoreGenerator::getInteractionMapping, 
                                                                  python::return_internal_reference<>()))
        .add_property("coreEnvironment", python::make_function(&Pharm::InteractionPharmacophoreGenerator::getCoreEnvironment, 
                                                               python::return_internal_reference<>()));
}
