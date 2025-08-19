/* 
 * Object3DFunctionExport.cpp 
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

#include "CDPL/Vis/Object3D.hpp"
#include "CDPL/Vis/Object3DFunctions.hpp"

#include "FunctionExports.hpp"


#define EXPORT_OBJECT3D_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                         \
    python::def("get" #FUNC_SUFFIX, &Vis::get##FUNC_SUFFIX, python::arg("obj"),      \
                python::return_internal_reference<1>());                             \
    python::def("has" #FUNC_SUFFIX, &Vis::has##FUNC_SUFFIX, python::arg("obj"));     \
    python::def("clear" #FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("obj")); \
    python::def("set" #FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("obj"), python::arg(#ARG_NAME)));

#define EXPORT_OBJECT3D_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                        \
    python::def("get" #FUNC_SUFFIX, &Vis::get##FUNC_SUFFIX, python::arg("obj"),      \
                python::return_value_policy<python::copy_const_reference>());        \
    python::def("has" #FUNC_SUFFIX, &Vis::has##FUNC_SUFFIX, python::arg("obj"));     \
    python::def("clear" #FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("obj")); \
    python::def("set" #FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("obj"), python::arg(#ARG_NAME)));

#define EXPORT_OBJECT3D_FUNCS(FUNC_SUFFIX, ARG_NAME)                                 \
    python::def("get" #FUNC_SUFFIX, &Vis::get##FUNC_SUFFIX, python::arg("obj"));     \
    python::def("has" #FUNC_SUFFIX, &Vis::has##FUNC_SUFFIX, python::arg("obj"));     \
    python::def("clear" #FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("obj")); \
    python::def("set" #FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("obj"), python::arg(#ARG_NAME)));


void CDPLPythonVis::exportObject3DFunctions()
{
    using namespace boost;
    using namespace CDPL;

    EXPORT_OBJECT3D_FUNCS_INT_REF(Shape, shape)
    EXPORT_OBJECT3D_FUNCS_INT_REF(TransformationMatrix, mtx)
}
