/* 
 * NPoint2DPharmacophoreFingerprintGeneratorExport.cpp 
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

#include "CDPL/Descr/NPoint2DPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "ClassExports.hpp"


void CDPLPythonDescr::exportNPoint2DPharmacophoreFingerprintGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::NPoint2DPharmacophoreFingerprintGenerator, Descr::NPoint2DPharmacophoreFingerprintGenerator::SharedPointer,
                   python::bases<Descr::NPointPharmacophoreFingerprintGenerator> > cls("NPoint2DPharmacophoreFingerprintGenerator", python::no_init);
    python::scope scope = cls;

    python::enum_<Descr::NPoint2DPharmacophoreFingerprintGenerator::FeatureDistanceType>("FeatureDistanceType")
        .value("", Descr::NPoint2DPharmacophoreFingerprintGenerator::MIN_PATH_LENGTH)
        .value("", Descr::NPoint2DPharmacophoreFingerprintGenerator::MAX_PATH_LENGTH)
        .value("", Descr::NPoint2DPharmacophoreFingerprintGenerator::AVG_PATH_LENGTH)
        .export_values();
    
    cls
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&, Util::BitSet&>(
                 (python::arg("self"), python::arg("molgraph"), python::arg("fp"))))
        .def(python::init<const Descr::NPoint2DPharmacophoreFingerprintGenerator&>((python::arg("self"), python::arg("gen"))))
        .def("assign", &Descr::NPoint2DPharmacophoreFingerprintGenerator::operator=, 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setFeatureDistanceType",  &Descr::NPoint2DPharmacophoreFingerprintGenerator::setFeatureDistanceType,
             (python::arg("self"), python::arg("dist_type")))
        .def("getFeatureDistanceType", &Descr::NPoint2DPharmacophoreFingerprintGenerator::getFeatureDistanceType,
             python::arg("self"))
        .def("generate", &Descr::NPoint2DPharmacophoreFingerprintGenerator::generate,
             (python::arg("self"), python::arg("molgraph"), python::arg("fp")))
        .add_property("featureDistanceType", &Descr::NPoint2DPharmacophoreFingerprintGenerator::getFeatureDistanceType,
                      &Descr::NPoint2DPharmacophoreFingerprintGenerator::setFeatureDistanceType)
        .def_readonly("DEF_FEATURE_DISTANCE_TYPE", Descr::NPoint2DPharmacophoreFingerprintGenerator::DEF_FEATURE_DISTANCE_TYPE);
}
