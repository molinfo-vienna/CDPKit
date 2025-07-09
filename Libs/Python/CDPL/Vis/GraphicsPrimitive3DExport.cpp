/* 
 * GraphicsPrimitive3DExport.cpp 
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

#include "CDPL/Vis/GraphicsPrimitive3D.hpp"
#include "CDPL/Vis/GraphicsPrimitive3DVisitor.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct GraphicsPrimitive3DWrapper : CDPL::Vis::GraphicsPrimitive3D, boost::python::wrapper<CDPL::Vis::GraphicsPrimitive3D>
    {

        CDPL::Vis::GraphicsPrimitive3D::SharedPointer clone() const {
            return this->get_override("clone")();
        }

        void accept(CDPL::Vis::GraphicsPrimitive3DVisitor& visitor) const {
            this->get_override("accept")(boost::ref(visitor));
        }
    };
}


void CDPLPythonVis::exportGraphicsPrimitive3D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GraphicsPrimitive3DWrapper, boost::noncopyable>("GraphicsPrimitive3D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::GraphicsPrimitive3D>())    
        .def("clone", python::pure_virtual(&Vis::GraphicsPrimitive3D::clone), python::arg("self"))
        .def("accept", python::pure_virtual(&Vis::GraphicsPrimitive3D::accept), (python::arg("self"), python::arg("visitor")))
        ;
}
