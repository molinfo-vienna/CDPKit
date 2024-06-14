/* 
 * NPointPharmacophoreFingerprintGeneratorExport.cpp 
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

#include "CDPL/Descr/NPointPharmacophoreFingerprintGenerator.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonDescr::exportNPointPharmacophoreFingerprintGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::NPointPharmacophoreFingerprintGenerator, boost::noncopyable>("NPointPharmacophoreFingerprintGenerator", python::no_init)
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::NPointPharmacophoreFingerprintGenerator>())
        .def("assign", &Descr::NPointPharmacophoreFingerprintGenerator::operator=,
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setMinFeatureTupleSize", &Descr::NPointPharmacophoreFingerprintGenerator::setMinFeatureTupleSize,
             (python::arg("self"), python::arg("min_size")))
        .def("getMinFeatureTupleSize", &Descr::NPointPharmacophoreFingerprintGenerator::getMinFeatureTupleSize,
             python::arg("self"))
        .def("setMaxFeatureTupleSize",  &Descr::NPointPharmacophoreFingerprintGenerator::setMaxFeatureTupleSize,
             (python::arg("self"), python::arg("max_size")))
        .def("getMaxFeatureTupleSize", &Descr::NPointPharmacophoreFingerprintGenerator::getMaxFeatureTupleSize,
             python::arg("self"))
        .def("setBinSize",  &Descr::NPointPharmacophoreFingerprintGenerator::setBinSize,
             (python::arg("self"), python::arg("bin_size")))
        .def("getBinSize", &Descr::NPointPharmacophoreFingerprintGenerator::getBinSize,
             python::arg("self"))
        .def("getPharmacophoreGenerator", static_cast<Pharm::PharmacophoreGenerator& (Descr::NPointPharmacophoreFingerprintGenerator::*)()>
             (&Descr::NPointPharmacophoreFingerprintGenerator::getPharmacophoreGenerator), python::arg("self"),
             python::return_internal_reference<>())
        .add_property("minFeatureTupleSize", &Descr::NPointPharmacophoreFingerprintGenerator::getMinFeatureTupleSize,
                      &Descr::NPointPharmacophoreFingerprintGenerator::setMinFeatureTupleSize)
        .add_property("maxFeatureTupleSize", &Descr::NPointPharmacophoreFingerprintGenerator::getMaxFeatureTupleSize,
                      &Descr::NPointPharmacophoreFingerprintGenerator::setMaxFeatureTupleSize)
        .add_property("binSize", &Descr::NPointPharmacophoreFingerprintGenerator::getBinSize,
                      &Descr::NPointPharmacophoreFingerprintGenerator::setBinSize)
        .add_property("pharmGenerator",
                      python::make_function(static_cast<Pharm::PharmacophoreGenerator& (Descr::NPointPharmacophoreFingerprintGenerator::*)()>
                                            (&Descr::NPointPharmacophoreFingerprintGenerator::getPharmacophoreGenerator),
                                            python::return_internal_reference<>()))
        .def_readonly("DEF_MIN_FEATURE_TUPLE_SIZE", Descr::NPointPharmacophoreFingerprintGenerator::DEF_MIN_FEATURE_TUPLE_SIZE)
        .def_readonly("DEF_MAX_FEATURE_TUPLE_SIZE", Descr::NPointPharmacophoreFingerprintGenerator::DEF_MAX_FEATURE_TUPLE_SIZE)
        .def_readonly("DEF_BIN_SIZE", Descr::NPointPharmacophoreFingerprintGenerator::DEF_BIN_SIZE);
}
