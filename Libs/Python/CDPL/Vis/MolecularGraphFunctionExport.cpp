/* 
 * MolecularGraphFunctionExport.cpp 
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

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Vis/MolecularGraphFunctions.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "FunctionExports.hpp"


#define EXPORT_MOLGRAPH_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &Vis::get##FUNC_SUFFIX, python::arg("molgraph"),                                  \
            python::return_internal_reference<1>());                                                             \
python::def("has"#FUNC_SUFFIX, &Vis::has##FUNC_SUFFIX, python::arg("molgraph"));                                 \
python::def("clear"#FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("molgraph"));                             \
python::def("set"#FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &Vis::get##FUNC_SUFFIX, python::arg("molgraph"),                                  \
            python::return_value_policy<python::copy_const_reference>());                                        \
python::def("has"#FUNC_SUFFIX, &Vis::has##FUNC_SUFFIX, python::arg("molgraph"));                                 \
python::def("clear"#FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("molgraph"));                             \
python::def("set"#FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 


void CDPLPythonVis::exportMolecularGraphFunctions()
{
    using namespace boost;
    using namespace CDPL;

    EXPORT_MOLGRAPH_FUNCS_COPY_REF(AtomColorTable, colors)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(AtomColor, color)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(AtomLabelFont, font)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(AtomLabelSize, size)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(AtomConfigurationLabelFont, font)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(AtomConfigurationLabelSize, size)   
    EXPORT_MOLGRAPH_FUNCS_INT_REF(SecondaryAtomLabelFont, font)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(SecondaryAtomLabelSize, size)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(AtomLabelMargin, margin)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(RadicalElectronDotSize, size)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondColor, color)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondLineWidth, width)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondLineSpacing, spacing)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(StereoBondWedgeWidth, width)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(StereoBondHashSpacing, spacing)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(ReactionCenterLineLength, length)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(ReactionCenterLineSpacing, spacing)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(DoubleBondTrimLength, length)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(TripleBondTrimLength, length)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondLabelFont, font)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondLabelSize, size)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondLabelMargin, margin)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondConfigurationLabelFont, font)
    EXPORT_MOLGRAPH_FUNCS_INT_REF(BondConfigurationLabelSize, size)
}
