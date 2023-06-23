/* 
 * AtomFunctionExport.cpp 
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

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_ATOM_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
    return CDPL::ForceField::get##FUNC_SUFFIX(atom);               \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
    return CDPL::ForceField::has##FUNC_SUFFIX(atom);               \
}

#define EXPORT_ATOM_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("atom"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("atom"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
            python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("atom"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)), \
            python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_ATOM_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("atom"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &ForceField::clear##FUNC_SUFFIX, python::arg("atom"));                      \
python::def("set"#FUNC_SUFFIX, &ForceField::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)), \
            python::with_custodian_and_ward<1, 2>());  


namespace
{

    MAKE_ATOM_FUNC_WRAPPERS(const std::string&, MMFF94SymbolicType)
    MAKE_ATOM_FUNC_WRAPPERS(unsigned int, MMFF94NumericType)
    MAKE_ATOM_FUNC_WRAPPERS(double, MMFF94Charge)
    MAKE_ATOM_FUNC_WRAPPERS(unsigned int, UFFType)

    MAKE_FUNCTION_WRAPPER2(unsigned int, perceiveUFFType, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
}


void CDPLPythonForceField::exportAtomFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("perceiveUFFType", &perceiveUFFTypeWrapper2, (python::arg("atom"), python::arg("molgraph")));
    
    EXPORT_ATOM_FUNCS_COPY_REF(MMFF94SymbolicType, type)
    EXPORT_ATOM_FUNCS(MMFF94NumericType, type)
    EXPORT_ATOM_FUNCS(MMFF94Charge, charge)
    EXPORT_ATOM_FUNCS(UFFType, type)
}
