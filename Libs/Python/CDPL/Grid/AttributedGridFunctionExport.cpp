/* 
 * AttributedGridFunctionExport.cpp 
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

#include "CDPL/Grid/AttributedGridFunctions.hpp"
#include "CDPL/Grid/AttributedGrid.hpp"

#include "FunctionExports.hpp"


#define EXPORT_ATTRGRID_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                            \
python::def("get"#FUNC_SUFFIX, &Grid::get##FUNC_SUFFIX, python::arg("grid"),                             \
            python::return_value_policy<python::copy_const_reference>());                                \
python::def("has"#FUNC_SUFFIX, &Grid::has##FUNC_SUFFIX, python::arg("grid"));                            \
python::def("clear"#FUNC_SUFFIX, &Grid::clear##FUNC_SUFFIX, python::arg("grid"));                        \
python::def("set"#FUNC_SUFFIX, &Grid::set##FUNC_SUFFIX, (python::arg("grid"), python::arg(#ARG_NAME))); 


void CDPLPythonGrid::exportAttributedGridFunctions()
{
    using namespace boost;
    using namespace CDPL;

	EXPORT_ATTRGRID_FUNCS_COPY_REF(Name, name)
}
