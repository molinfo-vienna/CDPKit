/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DFunctionExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/Entity3D.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_ENTITY_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                    \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Entity3D& entity)            \
{                                                                       \
	return get##FUNC_SUFFIX(entity);                                    \
}                                                                       \
                                                                        \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Entity3D& entity)            \
{                                                                       \
	return has##FUNC_SUFFIX(entity);                                    \
}

#define EXPORT_ENTITY_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                          \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("entity"));                          \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("entity"));                          \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("entity"));                         \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("entity"), python::arg(#ARG_NAME))); 

#define EXPORT_ENTITY_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                   \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("entity"),                            \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("entity"));                           \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("entity"));                          \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("entity"), python::arg(#ARG_NAME))); 


namespace
{

    MAKE_ENTITY_FUNC_WRAPPERS(const CDPL::Math::Vector3D&, 3DCoordinates)
}


void CDPLPythonChem::exportEntity3DFunctions()
{
    using namespace boost;
    using namespace CDPL;
    
	EXPORT_ENTITY_FUNCS_INT_REF(3DCoordinates, coords)
}
