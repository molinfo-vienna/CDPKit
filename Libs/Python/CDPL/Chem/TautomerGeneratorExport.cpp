/* 
 * TautomerGeneratorExport.cpp 
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

#include "CDPL/Chem/TautomerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportTautomerGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::TautomerGenerator, Chem::TautomerGenerator::SharedPointer,
                   boost::noncopyable> cl("TautomerGenerator", python::no_init);

    python::scope scope = cl;
  
    python::enum_<Chem::TautomerGenerator::Mode>("Mode")
        .value("TOPOLOGICALLY_UNIQUE", Chem::TautomerGenerator::TOPOLOGICALLY_UNIQUE)
        .value("GEOMETRICALLY_UNIQUE", Chem::TautomerGenerator::GEOMETRICALLY_UNIQUE)
        .value("EXHAUSTIVE", Chem::TautomerGenerator::EXHAUSTIVE)
        .export_values();

    cl
        .def(python::init<>(python::arg("self")))
        .def(python::init<Chem::TautomerGenerator>((python::arg("self"), python::arg("gen"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::TautomerGenerator>())    
        .def("addTautomerizationRule", &Chem::TautomerGenerator::addTautomerizationRule, 
             (python::arg("self"), python::arg("rule")))
        .def("removeTautomerizationRule", &Chem::TautomerGenerator::removeTautomerizationRule, 
             (python::arg("self"), python::arg("idx")))
        .def("getTautomerizationRule", &Chem::TautomerGenerator::getTautomerizationRule, 
             (python::arg("self"), python::arg("idx")), python::return_value_policy<python::copy_const_reference>())
        .def("getNumTautomerizationRules", &Chem::TautomerGenerator::getNumTautomerizationRules, 
             python::arg("self"))
        .def("setCallbackFunction", &Chem::TautomerGenerator::setCallbackFunction, 
             (python::arg("self"), python::arg("func")))
        .def("getCallbackFunction", &Chem::TautomerGenerator::getCallbackFunction, 
             python::arg("self"), python::return_internal_reference<>())
        .def("setMode", &Chem::TautomerGenerator::setMode, (python::arg("self"), python::arg("mode")))
        .def("getMode", &Chem::TautomerGenerator::getMode, python::arg("self"))
        .def("regardStereochemistry", &Chem::TautomerGenerator::regardStereochemistry, (python::arg("self"), python::arg("regard")))
        .def("stereochemistryRegarded", &Chem::TautomerGenerator::stereochemistryRegarded, python::arg("self"))
        .def("regardIsotopes", &Chem::TautomerGenerator::regardIsotopes, (python::arg("self"), python::arg("regard")))
        .def("isotopesRegarded", &Chem::TautomerGenerator::isotopesRegarded, python::arg("self"))
        .def("clearCoordinates2D", &Chem::TautomerGenerator::clearCoordinates2D, (python::arg("self"), python::arg("clear")))
        .def("coordinates2DCleared", &Chem::TautomerGenerator::coordinates2DCleared, python::arg("self"))
        .def("clearCoordinates3D", &Chem::TautomerGenerator::clearCoordinates3D, (python::arg("self"), python::arg("clear")))
        .def("coordinates3DCleared", &Chem::TautomerGenerator::coordinates3DCleared, python::arg("self"))
        .def("removeResonanceDuplicates", &Chem::TautomerGenerator::removeResonanceDuplicates, (python::arg("self"), python::arg("remove")))
        .def("resonanceDuplicatesRemoved", &Chem::TautomerGenerator::resonanceDuplicatesRemoved, python::arg("self"))
        .def("setCustomSetupFunction", &Chem::TautomerGenerator::setCustomSetupFunction, (python::arg("self"), python::arg("func")))
        .def("generate", &Chem::TautomerGenerator::generate, 
             (python::arg("self"), python::arg("molgraph")))
        .def("assign", &Chem::TautomerGenerator::operator=, 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .add_property("callbackFunction", python::make_function(&Chem::TautomerGenerator::getCallbackFunction,
                                                                python::return_internal_reference<>()),
                      &Chem::TautomerGenerator::setCallbackFunction)
        .add_property("mode", &Chem::TautomerGenerator::getMode, &Chem::TautomerGenerator::setMode)
        .add_property("regStereo", &Chem::TautomerGenerator::stereochemistryRegarded, &Chem::TautomerGenerator::regardStereochemistry)
        .add_property("regIsotopes", &Chem::TautomerGenerator::isotopesRegarded, &Chem::TautomerGenerator::regardIsotopes)
        .add_property("clearCoordinates2D", &Chem::TautomerGenerator::coordinates2DCleared, &Chem::TautomerGenerator::clearCoordinates2D)
        .add_property("clearCoordinates3D", &Chem::TautomerGenerator::coordinates3DCleared, &Chem::TautomerGenerator::clearCoordinates3D)
        .add_property("remResonanceDuplicates", &Chem::TautomerGenerator::resonanceDuplicatesRemoved,
                      &Chem::TautomerGenerator::removeResonanceDuplicates)
        .add_property("numTautomerizationRules", &Chem::TautomerGenerator::getNumTautomerizationRules);
}
