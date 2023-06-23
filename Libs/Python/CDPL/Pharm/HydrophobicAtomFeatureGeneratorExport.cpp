/* 
 * HydrophobicAtomFeatureGeneratorExport.cpp 
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

#include "CDPL/Pharm/HydrophobicAtomFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportHydrophobicAtomFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::HydrophobicAtomFeatureGenerator, Pharm::HydrophobicAtomFeatureGenerator::SharedPointer,
                   python::bases<Pharm::PatternBasedFeatureGenerator>, 
                   boost::noncopyable>("HydrophobicAtomFeatureGenerator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&, Pharm::Pharmacophore&>(
                 (python::arg("self"), python::arg("molgraph"), python::arg("pharm"))))
        .def(python::init<const Pharm::HydrophobicAtomFeatureGenerator&>(
                 (python::arg("self"), python::arg("gen"))))
        .def("assign", &Pharm::HydrophobicAtomFeatureGenerator::operator=, 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setFeatureType", &Pharm::HydrophobicAtomFeatureGenerator::setFeatureType, 
             (python::arg("self"), python::arg("type")))
        .def("setFeatureGeometry", &Pharm::HydrophobicAtomFeatureGenerator::setFeatureGeometry, 
             (python::arg("self"), python::arg("geom")))
        .def("setFeatureTolerance", &Pharm::HydrophobicAtomFeatureGenerator::setFeatureTolerance, 
             (python::arg("self"), python::arg("tol")))
        .def("setHydrophobicityThreshold", &Pharm::HydrophobicAtomFeatureGenerator::setHydrophobicityThreshold, 
             (python::arg("self"), python::arg("thresh")))
        .def("getFeatureType", &Pharm::HydrophobicAtomFeatureGenerator::getFeatureType, python::arg("self"))
        .def("getFeatureGeometry", &Pharm::HydrophobicAtomFeatureGenerator::getFeatureGeometry, python::arg("self"))
        .def("getFeatureTolerance", &Pharm::HydrophobicAtomFeatureGenerator::getFeatureTolerance, python::arg("self"))
        .def("getHydrophobicityThreshold", &Pharm::HydrophobicAtomFeatureGenerator::getHydrophobicityThreshold, python::arg("self"))
        .def("assign", &Pharm::HydrophobicAtomFeatureGenerator::operator=, 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def_readonly("DEF_FEATURE_TOL", Pharm::HydrophobicAtomFeatureGenerator::DEF_FEATURE_TOL)
        .def_readonly("DEF_FEATURE_TYPE", Pharm::HydrophobicAtomFeatureGenerator::DEF_FEATURE_TYPE)
        .def_readonly("DEF_FEATURE_GEOM", Pharm::HydrophobicAtomFeatureGenerator::DEF_FEATURE_GEOM)
        .def_readonly("DEF_HYD_THRESHOLD", Pharm::HydrophobicAtomFeatureGenerator::DEF_HYD_THRESHOLD)
        .add_property("featureType", &Pharm::HydrophobicAtomFeatureGenerator::getFeatureType,
                      &Pharm::HydrophobicAtomFeatureGenerator::setFeatureType)
        .add_property("featureGeometry", &Pharm::HydrophobicAtomFeatureGenerator::getFeatureGeometry,
                      &Pharm::HydrophobicAtomFeatureGenerator::setFeatureGeometry)
        .add_property("featureTolerance", &Pharm::HydrophobicAtomFeatureGenerator::getFeatureTolerance,
                      &Pharm::HydrophobicAtomFeatureGenerator::setFeatureTolerance)
        .add_property("hydThreshold", &Pharm::HydrophobicAtomFeatureGenerator::getHydrophobicityThreshold,
                      &Pharm::HydrophobicAtomFeatureGenerator::setHydrophobicityThreshold);
}
