/* 
 * FileScreeningHitCollectorExport.cpp 
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

#include "CDPL/Pharm/FileScreeningHitCollector.hpp"
#include "CDPL/Base/DataWriter.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportFileScreeningHitCollector()
{
    using namespace boost;
    using namespace CDPL;

    typedef void (Pharm::FileScreeningHitCollector::*SetBoolFunc)(bool);
    typedef bool (Pharm::FileScreeningHitCollector::*GetBoolFunc)() const;

    python::class_<Pharm::FileScreeningHitCollector, boost::noncopyable>("FileScreeningHitCollector", python::no_init)
        .def(python::init<const Pharm::FileScreeningHitCollector&>((python::arg("self"), python::arg("collector")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(python::init<Pharm::FileScreeningHitCollector::MolecularGraphWriter&>((python::arg("self"), python::arg("writer")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FileScreeningHitCollector>())
        .def("assign", CDPLPythonBase::copyAssOp<Pharm::FileScreeningHitCollector>(), (python::arg("self"), python::arg("collector")),
             python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("__call__", &Pharm::FileScreeningHitCollector::operator(), 
             (python::arg("self"), python::arg("hit"), python::arg("score")))
        .def("setDataWriter", &Pharm::FileScreeningHitCollector::setDataWriter, 
             (python::arg("self"), python::arg("writer")),
             python::with_custodian_and_ward<1, 2>())
        .def("getDataWriter", &Pharm::FileScreeningHitCollector::getDataWriter, python::arg("self"),
             python::return_internal_reference<>())
        .def("alignHitMolecule", SetBoolFunc(&Pharm::FileScreeningHitCollector::alignHitMolecule), 
             (python::arg("self"), python::arg("align")))
        .def("alignHitMolecule", GetBoolFunc(&Pharm::FileScreeningHitCollector::alignHitMolecule), python::arg("self"))
        .def("outputScoreProperty", SetBoolFunc(&Pharm::FileScreeningHitCollector::outputScoreProperty), 
             (python::arg("self"), python::arg("output")))
        .def("outputScoreProperty", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputScoreProperty), python::arg("self"))
        .def("outputDBNameProperty", SetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBNameProperty), 
             (python::arg("self"), python::arg("output")))
        .def("outputDBNameProperty", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBNameProperty), python::arg("self"))
        .def("outputDBMoleculeIndexProperty", SetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBMoleculeIndexProperty), 
             (python::arg("self"), python::arg("output")))
        .def("outputDBMoleculeIndexProperty", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBMoleculeIndexProperty), 
             python::arg("self"))
        .def("outputMoleculeConfIndexProperty", SetBoolFunc(&Pharm::FileScreeningHitCollector::outputMoleculeConfIndexProperty), 
             (python::arg("self"), python::arg("output")))
        .def("outputMoleculeConfIndexProperty", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputMoleculeConfIndexProperty), 
             python::arg("self"))
        .def("outputZeroBasedIndices", SetBoolFunc(&Pharm::FileScreeningHitCollector::outputZeroBasedIndices), 
             (python::arg("self"), python::arg("zero_based")))
        .def("outputZeroBasedIndices", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputZeroBasedIndices), 
             python::arg("self"))
        .add_property("dataWriter", python::make_function(&Pharm::FileScreeningHitCollector::getDataWriter,
                                                          python::return_internal_reference<>()),
                      python::make_function(&Pharm::FileScreeningHitCollector::setDataWriter, 
                                            python::with_custodian_and_ward<1, 2>()))
        .add_property("alignHitMol", GetBoolFunc(&Pharm::FileScreeningHitCollector::alignHitMolecule),
                      SetBoolFunc(&Pharm::FileScreeningHitCollector::alignHitMolecule))
        .add_property("outputScoreProp", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputScoreProperty),
                      SetBoolFunc(&Pharm::FileScreeningHitCollector::outputScoreProperty))
        .add_property("outputDBNameProp", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBNameProperty),
                      SetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBNameProperty))
        .add_property("outputDBMoleculeIndexProp", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBMoleculeIndexProperty),
                      SetBoolFunc(&Pharm::FileScreeningHitCollector::outputDBMoleculeIndexProperty))
        .add_property("outputMoleculeConfIndexProp", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputMoleculeConfIndexProperty),
                      SetBoolFunc(&Pharm::FileScreeningHitCollector::outputMoleculeConfIndexProperty))
        .add_property("outputZeroBasedInds", GetBoolFunc(&Pharm::FileScreeningHitCollector::outputZeroBasedIndices),
                      SetBoolFunc(&Pharm::FileScreeningHitCollector::outputZeroBasedIndices));
}
