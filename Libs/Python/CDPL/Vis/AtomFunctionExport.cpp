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
#include "CDPL/Vis/AtomFunctions.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "FunctionExports.hpp"


#define MAKE_ATOM_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)     \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom) \
{                                                      \
	return CDPL::Vis::get##FUNC_SUFFIX(atom);          \
}                                                      \
                                                       \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom) \
{                                                      \
	return CDPL::Vis::has##FUNC_SUFFIX(atom);          \
}

#define EXPORT_ATOM_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("atom"));                             \
python::def("set"#FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 


namespace
{

	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::Color&, Color)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::Font&, LabelFont)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, LabelSize)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::Font&, SecondaryLabelFont)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, SecondaryLabelSize)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, LabelMargin)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, RadicalElectronDotSize)
}


void CDPLPythonVis::exportAtomFunctions()
{
	using namespace boost;
	using namespace CDPL;

	EXPORT_ATOM_FUNCS_INT_REF(Color, color)
	EXPORT_ATOM_FUNCS_INT_REF(LabelFont, font)
	EXPORT_ATOM_FUNCS_INT_REF(LabelSize, size)
	EXPORT_ATOM_FUNCS_INT_REF(SecondaryLabelFont, font)
	EXPORT_ATOM_FUNCS_INT_REF(SecondaryLabelSize, size)
	EXPORT_ATOM_FUNCS_INT_REF(LabelMargin, margin)
	EXPORT_ATOM_FUNCS_INT_REF(RadicalElectronDotSize, size)
}
