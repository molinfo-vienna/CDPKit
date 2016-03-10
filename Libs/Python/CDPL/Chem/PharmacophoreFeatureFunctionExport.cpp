/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreFeatureFunctionExport.cpp 
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

#include "CDPL/Chem/PharmacophoreFeature.hpp"
#include "CDPL/Chem/PharmacophoreFeatureFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_FEATURE_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                       \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::PharmacophoreFeature& feature)   \
{                                                                           \
	return get##FUNC_SUFFIX(feature);                                   \
}                                                                           \
                                                                            \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::PharmacophoreFeature& feature)   \
{                                                                           \
	return has##FUNC_SUFFIX(feature);                                   \
}

#define EXPORT_FEATURE_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("feature"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("feature"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("feature"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("feature"), python::arg(#ARG_NAME))); 


namespace
{

    MAKE_FEATURE_FUNC_WRAPPERS(unsigned int, Type)
    MAKE_FEATURE_FUNC_WRAPPERS(unsigned int, Geometry)
}


void CDPLPythonChem::exportPharmacophoreFeatureFunctions()
{
    using namespace boost;
    using namespace CDPL;
    
    EXPORT_FEATURE_FUNCS(Type, type)
    EXPORT_FEATURE_FUNCS(Geometry, geom)
}
