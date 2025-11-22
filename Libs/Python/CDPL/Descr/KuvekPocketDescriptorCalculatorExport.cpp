/* 
 * KuvekPocketDescriptorCalculatorExport.cpp 
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

#include "CDPL/Descr/KuvekPocketDescriptorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    void calculate(CDPL::Descr::KuvekPocketDescriptorCalculator& calculator, const CDPL::Math::Vector3D& sphere_ctr,
                   CDPL::Chem::AtomContainer& atoms, CDPL::Math::DVector& descr)
    {
        calculator.calculate(sphere_ctr, atoms, descr);
    }
}


void CDPLPythonDescr::exportKuvekPocketDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::KuvekPocketDescriptorCalculator, boost::noncopyable>("KuvekPocketDescriptorCalculator", python::no_init)
        .def(python::init<double, std::size_t, double>((python::arg("self"), python::arg("sphere_radius") = Descr::KuvekPocketDescriptorCalculator::DEF_PROBE_RADIUS,
                                                        python::arg("num_test_vecs") = Descr::KuvekPocketDescriptorCalculator::DEF_NUM_TEST_VECTORS,
                                                        python::arg("max_atom_to_sphr_surf_dist") = Descr::KuvekPocketDescriptorCalculator::DEF_MAX_ATOM_TO_SPHERE_SURF_DIST)))
        .def(python::init<const Descr::KuvekPocketDescriptorCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::KuvekPocketDescriptorCalculator>())    
        .def("assign", CDPLPythonBase::copyAssOp<Descr::KuvekPocketDescriptorCalculator>(), 
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("setAtom3DCoordinatesFunction", &Descr::KuvekPocketDescriptorCalculator::setAtom3DCoordinatesFunction,
             (python::arg("self"), python::arg("func")))
        .def("getAtom3DCoordinatesFunction", &Descr::KuvekPocketDescriptorCalculator::getAtom3DCoordinatesFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("setAtomChargeFunction", &Descr::KuvekPocketDescriptorCalculator::setAtomChargeFunction,
             (python::arg("self"), python::arg("func")))
        .def("getAtomChargeFunction", &Descr::KuvekPocketDescriptorCalculator::getAtomChargeFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("setSphereRadius", &Descr::KuvekPocketDescriptorCalculator::setSphereRadius, 
             (python::arg("self"), python::arg("radius")))
        .def("getSphereRadius", &Descr::KuvekPocketDescriptorCalculator::getSphereRadius,
             python::arg("self"))
        .def("setMaxAtomToSphereSurfaceDistance", &Descr::KuvekPocketDescriptorCalculator::setMaxAtomToSphereSurfaceDistance,
             (python::arg("self"), python::arg("radius")))
        .def("getMaxAtomToSphereSurfaceDistance", &Descr::KuvekPocketDescriptorCalculator::getMaxAtomToSphereSurfaceDistance,
             python::arg("self"))
        .def("setNumTestVectors", &Descr::KuvekPocketDescriptorCalculator::setNumTestVectors, 
             (python::arg("self"), python::arg("num_vectors")))
        .def("getNumTestVectors", &Descr::KuvekPocketDescriptorCalculator::getNumTestVectors,
             python::arg("self"))
        .def("getTestVector", &Descr::KuvekPocketDescriptorCalculator::getTestVector,
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def("calculate", &calculate,
             (python::arg("self"), python::arg("sphere_ctr"), python::arg("atoms"), python::arg("descr")))
        .def_readonly("DEF_PROBE_RADIUS", Descr::KuvekPocketDescriptorCalculator::DEF_PROBE_RADIUS)
        .def_readonly("DEF_MAX_ATOM_TO_SPHERE_SURF_DIST", Descr::KuvekPocketDescriptorCalculator::DEF_MAX_ATOM_TO_SPHERE_SURF_DIST)
        .def_readonly("DEF_NUM_TEST_VECTORS", Descr::KuvekPocketDescriptorCalculator::DEF_NUM_TEST_VECTORS)
        .add_property("sphereRadius", &Descr::KuvekPocketDescriptorCalculator::getSphereRadius,
                      &Descr::KuvekPocketDescriptorCalculator::setSphereRadius)
        .add_property("maxAtomToSphereSurfaceDistance", &Descr::KuvekPocketDescriptorCalculator::getMaxAtomToSphereSurfaceDistance,
                      &Descr::KuvekPocketDescriptorCalculator::setMaxAtomToSphereSurfaceDistance)
        .add_property("numTestVectors", &Descr::KuvekPocketDescriptorCalculator::getNumTestVectors,
                      &Descr::KuvekPocketDescriptorCalculator::setNumTestVectors)
        .add_property("atomCoordsFunction", 
                      python::make_function(&Descr::KuvekPocketDescriptorCalculator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
                      &Descr::KuvekPocketDescriptorCalculator::setAtom3DCoordinatesFunction)
        .add_property("atomChargeFunction", 
                      python::make_function(&Descr::KuvekPocketDescriptorCalculator::getAtomChargeFunction, python::return_internal_reference<>()),
                      &Descr::KuvekPocketDescriptorCalculator::setAtomChargeFunction);
}
