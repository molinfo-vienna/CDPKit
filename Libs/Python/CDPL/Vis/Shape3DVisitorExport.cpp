/* 
 * Shape3DVisitorExport.cpp 
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

#include "CDPL/Vis/Shape3DVisitor.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct Shape3DVisitorWrapper : CDPL::Vis::Shape3DVisitor, boost::python::wrapper<CDPL::Vis::Shape3DVisitor>
    {

        void visitTriangleMesh(const CDPL::Vis::TriangleMesh3D& mesh) {
            if (boost::python::override f = this->get_override("visitTriangleMesh"))
                f(boost::ref(mesh));    
            else
                Shape3DVisitor::visitTriangleMesh(mesh);
        }

        void visitTriangleMeshDef(const CDPL::Vis::TriangleMesh3D& mesh) {
            Shape3DVisitor::visitTriangleMesh(mesh);
        }
    };
}


void CDPLPythonVis::exportShape3DVisitor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape3DVisitorWrapper, boost::noncopyable>("Shape3DVisitor", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Shape3DVisitor>())    
        .def("visitTriangleMesh",
             static_cast<void (Vis::Shape3DVisitor::*)(const Vis::TriangleMesh3D&)>(&Vis::Shape3DVisitor::visitTriangleMesh),
             static_cast<void (Shape3DVisitorWrapper::*)(const Vis::TriangleMesh3D&)>(&Shape3DVisitorWrapper::visitTriangleMeshDef),
             (python::arg("self"), python::arg("mesh")))
        ;
}
