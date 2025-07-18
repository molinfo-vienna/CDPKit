/* 
 * BuiltinTriangleMeshesExport.cpp 
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

#include "CDPL/Vis/IcosahedronMesh3D.hpp"
#include "CDPL/Vis/RightFrustumMesh3D.hpp"
#include "CDPL/Vis/TorusMesh3D.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportBuiltinTriangleMeshes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::IcosahedronMesh3D, Vis::IcosahedronMesh3D::SharedPointer,
                   python::bases<Vis::TriangleMesh3D> >("IcosahedronMesh3D", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("radius") = 1.0)))
        .def(python::init<const Vis::IcosahedronMesh3D&>((python::arg("self"), python::arg("mesh"))));

    python::class_<Vis::RightFrustumMesh3D, Vis::RightFrustumMesh3D::SharedPointer,
                   python::bases<Vis::TriangleMesh3D> >("RightFrustumMesh3D", python::no_init)
        .def(python::init<double, double, double, std::size_t, bool, bool>(
            (python::arg("self"), python::arg("radius1"), python::arg("radius2"), python::arg("height"),
             python::arg("num_sides"), python::arg("close_btm") = true, python::arg("close_top") = true)))
        .def(python::init<const Vis::RightFrustumMesh3D&>((python::arg("self"), python::arg("mesh"))));

    python::class_<Vis::TorusMesh3D, Vis::TorusMesh3D::SharedPointer,
                   python::bases<Vis::TriangleMesh3D> >("TorusMesh3D", python::no_init)
        .def(python::init<double, double, std::size_t, std::size_t>(
            (python::arg("self"), python::arg("radius1"), python::arg("radius2"), python::arg("num_sect1"),
             python::arg("num_sect2"))))
        .def(python::init<const Vis::TorusMesh3D&>((python::arg("self"), python::arg("mesh"))));
}
