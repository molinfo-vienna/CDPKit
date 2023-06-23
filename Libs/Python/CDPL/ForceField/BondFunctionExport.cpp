/* 
 * BondFunctionExport.cpp 
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

#include "CDPL/Chem/Bond.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"

#include "FunctionExports.hpp"


#define MAKE_BOND_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond)             \
{                                                                  \
    return CDPL::ForceField::get##FUNC_SUFFIX(bond);               \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond)             \
{                                                                  \
    return CDPL::ForceField::has##FUNC_SUFFIX(bond);               \
}

#define EXPORT_BOND_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("bond"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 

#define EXPORT_BOND_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("bond"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 

#define EXPORT_BOND_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
            python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("bond"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME)), \
            python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_BOND_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("bond"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME)), \
            python::with_custodian_and_ward<1, 2>());  


namespace
{

    MAKE_BOND_FUNC_WRAPPERS(unsigned int, MMFF94TypeIndex)
}


void CDPLPythonForceField::exportBondFunctions()
{
    using namespace boost;
    using namespace CDPL;

    EXPORT_BOND_FUNCS(MMFF94TypeIndex, type_idx)
}
