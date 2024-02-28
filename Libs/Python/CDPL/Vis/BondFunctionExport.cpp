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
#include "CDPL/Vis/BondFunctions.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "FunctionExports.hpp"


#define MAKE_BOND_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)     \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond) \
{                                                      \
    return CDPL::Vis::get##FUNC_SUFFIX(bond);          \
}                                                      \
                                                       \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond) \
{                                                      \
    return CDPL::Vis::has##FUNC_SUFFIX(bond);          \
}

#define EXPORT_BOND_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("bond"));                             \
python::def("set"#FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 


namespace
{

    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::Color&, Color)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, LineWidth)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, LineSpacing)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, StereoBondWedgeWidth)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, StereoBondHashSpacing)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionCenterLineLength)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionCenterLineSpacing)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, DoubleBondTrimLength)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, TripleBondTrimLength)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::Font&, LabelFont)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, LabelSize)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, LabelMargin)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::Font&, ConfigurationLabelFont)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ConfigurationLabelSize)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::Color&, ConfigurationLabelColor)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::Font&, CustomLabelFont)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, CustomLabelSize)
    MAKE_BOND_FUNC_WRAPPERS(const CDPL::Vis::Color&, CustomLabelColor)
    MAKE_BOND_FUNC_WRAPPERS(const std::string&, CustomLabel)
}


void CDPLPythonVis::exportBondFunctions()
{
    using namespace boost;
    using namespace CDPL;

    EXPORT_BOND_FUNCS_INT_REF(Color, color)
    EXPORT_BOND_FUNCS_INT_REF(LineWidth, width)
    EXPORT_BOND_FUNCS_INT_REF(LineSpacing, spacing)
    EXPORT_BOND_FUNCS_INT_REF(StereoBondWedgeWidth, width)
    EXPORT_BOND_FUNCS_INT_REF(StereoBondHashSpacing, spacing)
    EXPORT_BOND_FUNCS_INT_REF(ReactionCenterLineLength, length)
    EXPORT_BOND_FUNCS_INT_REF(ReactionCenterLineSpacing, spacing)
    EXPORT_BOND_FUNCS_INT_REF(DoubleBondTrimLength, length)
    EXPORT_BOND_FUNCS_INT_REF(TripleBondTrimLength, length)
    EXPORT_BOND_FUNCS_INT_REF(LabelFont, font)
    EXPORT_BOND_FUNCS_INT_REF(LabelSize, size)
    EXPORT_BOND_FUNCS_INT_REF(LabelMargin, margin)
    EXPORT_BOND_FUNCS_INT_REF(ConfigurationLabelFont, font)
    EXPORT_BOND_FUNCS_INT_REF(ConfigurationLabelSize, size)
    EXPORT_BOND_FUNCS_INT_REF(ConfigurationLabelColor, color)
    EXPORT_BOND_FUNCS_INT_REF(CustomLabelFont, font)
    EXPORT_BOND_FUNCS_INT_REF(CustomLabelSize, size)
    EXPORT_BOND_FUNCS_INT_REF(CustomLabelColor, color)
    EXPORT_BOND_FUNCS_INT_REF(CustomLabel, text)
}
