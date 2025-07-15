/* 
 * TriangleMesh3DExport.cpp 
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

#include "CDPL/Vis/TriangleMesh3D.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportTriangleMesh3D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::TriangleMesh3D, Vis::TriangleMesh3D::SharedPointer,
                   python::bases<Vis::Shape3D> >("TriangleMesh3D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Vis::TriangleMesh3D&>((python::arg("self"), python::arg("mesh"))))
        .def("assign", CDPLPythonBase::copyAssOp<Vis::TriangleMesh3D>(),
             (python::arg("self"), python::arg("mesh")), python::return_self<>())
        .def("getVertices", static_cast<Math::Vector3DArray& (Vis::TriangleMesh3D::*)()>(&Vis::TriangleMesh3D::getVertices),
             python::arg("self"), python::return_internal_reference<>())
        .def("addVertex", &Vis::TriangleMesh3D::addVertex, (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("z")))
        .def("getNumVertices", &Vis::TriangleMesh3D::getNumVertices, python::arg("self"))
        .def("getVertexNormals", static_cast<Math::Vector3DArray& (Vis::TriangleMesh3D::*)()>(&Vis::TriangleMesh3D::getVertexNormals),
             python::arg("self"), python::return_internal_reference<>())
        .def("addVertexNormal", &Vis::TriangleMesh3D::addVertex, (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("z")))
        .def("getNumVertexNormals", &Vis::TriangleMesh3D::getNumVertexNormals, python::arg("self"))
        .def("getFaces", static_cast<Math::Vector3ULArray& (Vis::TriangleMesh3D::*)()>(&Vis::TriangleMesh3D::getFaces),
             python::arg("self"), python::return_internal_reference<>())
        .def("addFace", &Vis::TriangleMesh3D::addFace, (python::arg("self"), python::arg("v1_idx"), python::arg("v2_idx"), python::arg("v3_idx")))
        .def("getNumFaces", &Vis::TriangleMesh3D::getNumFaces, python::arg("self"))
        .def("clear", &Vis::TriangleMesh3D::clear, python::arg("self"))
        .def("swap", &Vis::TriangleMesh3D::swap, (python::arg("self"), python::arg("mesh")),
             python::return_self<>())
        .def("__iadd__", &Vis::TriangleMesh3D::operator+=, (python::arg("self"), python::arg("mesh")),
             python::return_self<>())
        .add_property("vertices",
                      python::make_function(static_cast<Math::Vector3DArray& (Vis::TriangleMesh3D::*)()>(&Vis::TriangleMesh3D::getVertices),
                                            python::return_internal_reference<>()))
        .add_property("numVertices", &Vis::TriangleMesh3D::getNumVertices)
        .add_property("vertexNormals",
                      python::make_function(static_cast<Math::Vector3DArray& (Vis::TriangleMesh3D::*)()>(&Vis::TriangleMesh3D::getVertexNormals),
                                            python::return_internal_reference<>()))
        .add_property("numVertexNormals", &Vis::TriangleMesh3D::getNumVertexNormals)
        .add_property("faces",
                      python::make_function(static_cast<Math::Vector3ULArray& (Vis::TriangleMesh3D::*)()>(&Vis::TriangleMesh3D::getFaces),
                                            python::return_internal_reference<>()))
        .add_property("numFaces", &Vis::TriangleMesh3D::getNumFaces);
}
