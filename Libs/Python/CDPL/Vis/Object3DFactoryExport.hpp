/* 
 * Object3DFactoryExport.hpp 
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


#ifndef CDPL_PYTHON_VIS_OBJECT3DFACTORYEXPORT_HPP
#define CDPL_PYTHON_VIS_OBJECT3DFACTORYEXPORT_HPP

#include <memory>

#include <boost/python.hpp>

#include "CDPL/Vis/Object3DFactory.hpp"


namespace CDPLPythonVis
{

    template <typename T>
    struct Object3DFactoryWrapper : CDPL::Vis::Object3DFactory<T>,
                                    boost::python::wrapper<CDPL::Vis::Object3DFactory<T> >
    {

        typedef std::shared_ptr<Object3DFactoryWrapper<T> > SharedPointer;

        CDPL::Vis::Object3D::SharedPointer create(const T& data)
        {
            return this->get_override("create")(boost::ref(data));
        }
    };

    template <typename T>
    struct Object3DFactoryExport
    {

        Object3DFactoryExport(const char* name)
        {
            using namespace boost;
            using namespace CDPL;

            typedef Vis::Object3DFactory<T> FactoryType;

            python::class_<Object3DFactoryWrapper<T>, typename Object3DFactoryWrapper<T>::SharedPointer,
                           python::bases<Base::ControlParameterContainer>, boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def("create", python::pure_virtual(&FactoryType::create),
                     (python::arg("self"), python::arg("data")));

            python::register_ptr_to_python<typename Vis::Object3DFactory<T>::SharedPointer>();
        }
    };
} // namespace CDPLPythonVis

#endif // CDPL_PYTHON_VIS_OBJECT3DFACTORYEXPORT_HPP
