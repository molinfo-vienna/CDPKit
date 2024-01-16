/* 
 * ElasticPotentialExport.cpp 
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

#include "CDPL/ForceField/ElasticPotential.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportElasticPotential()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ForceField::ElasticPotential>("ElasticPotential", python::no_init)
        .def(python::init<const ForceField::ElasticPotential&>((python::arg("self"), python::arg("pot"))))
        .def(python::init<std::size_t, std::size_t, double, double>(
            (python::arg("self"), python::arg("atom1_idx"), python::arg("atom2_idx"),
             python::arg("force_const"), python::arg("ref_length"))))
        .def("getAtom1Index", &ForceField::ElasticPotential::getAtom1Index, python::arg("self"))
        .def("getAtom2Index", &ForceField::ElasticPotential::getAtom2Index, python::arg("self"))
        .def("getForceConstant", &ForceField::ElasticPotential::getForceConstant, python::arg("self"))
        .def("getReferenceLength", &ForceField::ElasticPotential::getReferenceLength, python::arg("self"))
        .def("setReferenceLength", &ForceField::ElasticPotential::setReferenceLength,
             (python::arg("self"), python::arg("length")))
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::ElasticPotential>(),
             (python::arg("self"), python::arg("pot")), python::return_self<>())
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::ElasticPotential>())
        .add_property("atom1Index", &ForceField::ElasticPotential::getAtom1Index)
        .add_property("atom2Index", &ForceField::ElasticPotential::getAtom2Index)
        .add_property("forceConstant", &ForceField::ElasticPotential::getForceConstant)
        .add_property("referenceLength", &ForceField::ElasticPotential::getReferenceLength,
                      &ForceField::ElasticPotential::setReferenceLength);
}
