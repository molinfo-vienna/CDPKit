/* 
 * Shape3DExport.cpp 
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


#include <memory>

#include <boost/python.hpp>

#include "CDPL/Vis/Shape3D.hpp"
#include "CDPL/Vis/Shape3DVisitor.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct Shape3DWrapper : CDPL::Vis::Shape3D, boost::python::wrapper<CDPL::Vis::Shape3D>
    {

        typedef std::shared_ptr<Shape3DWrapper> SharedPointer;
        
        CDPL::Vis::Shape3D::SharedPointer clone() const {
            return this->get_override("clone")();
        }

        void accept(CDPL::Vis::Shape3DVisitor& visitor) const {
            this->get_override("accept")(boost::ref(visitor));
        }
    };
}


void CDPLPythonVis::exportShape3D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape3DWrapper, Shape3DWrapper::SharedPointer, boost::noncopyable>("Shape3D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Shape3D>())    
        .def("clone", python::pure_virtual(&Vis::Shape3D::clone), python::arg("self"))
        .def("accept", python::pure_virtual(&Vis::Shape3D::accept), (python::arg("self"), python::arg("visitor")))
        ;

    python::register_ptr_to_python<Vis::Shape3D::SharedPointer>();
}
