/* 
 * BuriednessScoreExport.cpp 
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

#include "CDPL/GRAIL/BuriednessScore.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    double callOperator(CDPL::GRAIL::BuriednessScore& func, const CDPL::Math::Vector3D& pos, 
                        CDPL::Chem::AtomContainer& atoms)
    {
        return func(pos, atoms);
    }
}


void CDPLPythonGRAIL::exportBuriednessScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GRAIL::BuriednessScore, boost::noncopyable>("BuriednessScore", python::no_init)
        .def(python::init<const GRAIL::BuriednessScore&>((python::arg("self"), python::arg("score"))))
        .def(python::init<double, double, double>((python::arg("self"), python::arg("probe_radius") = GRAIL::BuriednessScore::DEF_PROBE_RADIUS,
                                                   python::arg("min_vdw_surf_dist") = GRAIL::BuriednessScore::DEF_MIN_VDW_SURFACE_DISTANCE,
                                                   python::arg("num_test_rays") = GRAIL::BuriednessScore::DEF_NUM_TEST_RAYS)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::BuriednessScore>())
        .def("setMinVdWSurfaceDistance", &GRAIL::BuriednessScore::setMinVdWSurfaceDistance, (python::arg("self"), python::arg("dist")))
        .def("getMinVdWSurfaceDistance", &GRAIL::BuriednessScore::getMinVdWSurfaceDistance, python::arg("self"))
        .def("setProbeRadius", &GRAIL::BuriednessScore::setProbeRadius, (python::arg("self"), python::arg("radius")))
        .def("getProbeRadius", &GRAIL::BuriednessScore::getProbeRadius, python::arg("self"))
        .def("setNumTestRays", &GRAIL::BuriednessScore::setNumTestRays, (python::arg("self"), python::arg("num_rays")))
        .def("getNumTestRays", &GRAIL::BuriednessScore::getNumTestRays, python::arg("self"))
        .def("setAtom3DCoordinatesFunction", &GRAIL::BuriednessScore::setAtom3DCoordinatesFunction,
             (python::arg("self"), python::arg("func")))
        .def("getAtom3DCoordinatesFunction", &GRAIL::BuriednessScore::getAtom3DCoordinatesFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("assign", CDPLPythonBase::copyAssOp<GRAIL::BuriednessScore>(), 
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &callOperator, (python::arg("self"), python::arg("pos"), python::arg("atoms")))
        .add_property("probeRadius", &GRAIL::BuriednessScore::getProbeRadius, &GRAIL::BuriednessScore::setProbeRadius)
        .add_property("minVdWSurfaceDistance", &GRAIL::BuriednessScore::getMinVdWSurfaceDistance, 
                      &GRAIL::BuriednessScore::setMinVdWSurfaceDistance)
        .add_property("numTestRays", &GRAIL::BuriednessScore::getNumTestRays, &GRAIL::BuriednessScore::setNumTestRays)
        .add_property("atomCoordsFunction", 
                      python::make_function(&GRAIL::BuriednessScore::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
                      &GRAIL::BuriednessScore::setAtom3DCoordinatesFunction)
        .def_readonly("DEF_NUM_TEST_RAYS", GRAIL::BuriednessScore::DEF_NUM_TEST_RAYS)
        .def_readonly("DEF_PROBE_RADIUS", GRAIL::BuriednessScore::DEF_PROBE_RADIUS);
}
