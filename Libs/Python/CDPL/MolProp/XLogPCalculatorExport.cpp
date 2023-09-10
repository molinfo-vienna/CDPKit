/* 
 * XLogPCalculatorExport.cpp 
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

#include "CDPL/MolProp/XLogPCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportXLogPCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<MolProp::XLogPCalculator, boost::noncopyable>("XLogPCalculator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const MolProp::XLogPCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<MolProp::XLogPCalculator>())    
        .def("assign", CDPLPythonBase::copyAssOp<MolProp::XLogPCalculator>(), 
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("calculate", &MolProp::XLogPCalculator::calculate, (python::arg("self"), python::arg("molgraph")))
        .def("getResult", &MolProp::XLogPCalculator::getResult, python::arg("self"))
        .def("getFeatureVector", &MolProp::XLogPCalculator::getFeatureVector, python::arg("self"),
             python::return_internal_reference<>())
        .def("getAtomContributions", &MolProp::XLogPCalculator::getAtomContributions, python::arg("self"),
             python::return_internal_reference<>())
        .add_property("result", &MolProp::XLogPCalculator::getResult)
        .def_readonly("FEATURE_VECTOR_SIZE", &MolProp::XLogPCalculator::FEATURE_VECTOR_SIZE);
}
