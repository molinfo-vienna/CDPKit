/* 
 * GeneralizedBellAtomDensityExport.cpp 
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

#include "CDPL/GRAIL/GeneralizedBellAtomDensity.hpp"
#include "CDPL/Chem/Atom.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    double callOperator(CDPL::GRAIL::GeneralizedBellAtomDensity& func, const CDPL::Math::Vector3D& pos, const CDPL::Math::Vector3D& atom_pos,
                        CDPL::Chem::Atom& atom)
    {
        return func(pos, atom_pos, atom);
    }
}


void CDPLPythonGRAIL::exportGeneralizedBellAtomDensity()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GRAIL::GeneralizedBellAtomDensity, boost::noncopyable>("GeneralizedBellAtomDensity", python::no_init)
        .def(python::init<const GRAIL::GeneralizedBellAtomDensity&>((python::arg("self"), python::arg("func"))))
        .def(python::init<double, double>((python::arg("self"), python::arg("probe_radius") = GRAIL::GeneralizedBellAtomDensity::DEF_PROBE_RADIUS,
                                   python::arg("rad_scaling_factor") = GRAIL::GeneralizedBellAtomDensity::DEF_RADIUS_SCALING_FACTOR)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::GeneralizedBellAtomDensity>())
        .def("getProbeRadius", &GRAIL::GeneralizedBellAtomDensity::getProbeRadius, python::arg("self"))
        .def("getRadiusScalingFactor", &GRAIL::GeneralizedBellAtomDensity::getRadiusScalingFactor, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp(&GRAIL::GeneralizedBellAtomDensity::operator=), 
             (python::arg("self"), python::arg("func")), python::return_self<>())
        .def("__call__", &callOperator, (python::arg("self"), python::arg("pos"), python::arg("atom_pos"), python::arg("atom")))
        .add_property("probeRadius", &GRAIL::GeneralizedBellAtomDensity::getProbeRadius)
        .add_property("radiusScalingFactor", &GRAIL::GeneralizedBellAtomDensity::getRadiusScalingFactor)
        .def_readonly("DEF_RADIUS_SCALING_FACTOR", GRAIL::GeneralizedBellAtomDensity::DEF_RADIUS_SCALING_FACTOR)
        .def_readonly("DEF_PROBE_RADIUS", GRAIL::GeneralizedBellAtomDensity::DEF_PROBE_RADIUS);
}
