/* 
 * NPoint3DPharmacophoreFingerprintGeneratorExport.cpp 
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

#include "CDPL/Descr/NPoint3DPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "ClassExports.hpp"


void CDPLPythonDescr::exportNPoint3DPharmacophoreFingerprintGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::NPoint3DPharmacophoreFingerprintGenerator, Descr::NPoint3DPharmacophoreFingerprintGenerator::SharedPointer,
                   python::bases<Descr::NPointPharmacophoreFingerprintGenerator> >("NPoint3DPharmacophoreFingerprintGenerator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&, Util::BitSet&>(
                 (python::arg("self"), python::arg("molgraph"), python::arg("fp"))))
        .def(python::init<const Pharm::Pharmacophore&, Util::BitSet&>(
                 (python::arg("self"), python::arg("cntnr"), python::arg("fp"))))
        .def(python::init<const Descr::NPoint3DPharmacophoreFingerprintGenerator&>((python::arg("self"), python::arg("gen"))))
        .def("assign", &Descr::NPoint3DPharmacophoreFingerprintGenerator::operator=, 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("generate", static_cast<void (Descr::NPoint3DPharmacophoreFingerprintGenerator::*)(const Chem::MolecularGraph&, Util::BitSet&)>
             (&Descr::NPoint3DPharmacophoreFingerprintGenerator::generate),
             (python::arg("self"), python::arg("molgraph"), python::arg("fp")))
        .def("generate", static_cast<void (Descr::NPoint3DPharmacophoreFingerprintGenerator::*)(const Pharm::FeatureContainer&, Util::BitSet&)>
             (&Descr::NPoint3DPharmacophoreFingerprintGenerator::generate),
             (python::arg("self"), python::arg("cntnr"), python::arg("fp")));
}
