/* 
 * ControlParameterFunctionExport.cpp 
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

#include "CDPL/Base/ControlParameterContainer.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/Material.hpp"

#include "FunctionExports.hpp"


#define MAKE_CONTROL_PARAM_FUNC_WRAPPERS(TYPE, FUNC_INFIX)                           \
TYPE get##FUNC_INFIX##ParameterWrapper(CDPL::Base::ControlParameterContainer& cntnr) \
{                                                                                    \
    return CDPL::Vis::get##FUNC_INFIX##Parameter(cntnr);                             \
}                                                                                    \
                                                                                     \
bool has##FUNC_INFIX##ParameterWrapper(CDPL::Base::ControlParameterContainer& cntnr) \
{                                                                                    \
    return CDPL::Vis::has##FUNC_INFIX##Parameter(cntnr);                             \
}

#define EXPORT_CONTROL_PARAM_FUNCS_INT_REF(FUNC_INFIX, ARG_NAME)                                                                  \
python::def("get"#FUNC_INFIX"Parameter", &get##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"),                                \
            python::return_internal_reference<1>());                                                                              \
python::def("has"#FUNC_INFIX"Parameter", &has##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("clear"#FUNC_INFIX"Parameter", &Vis::clear##FUNC_INFIX##Parameter, python::arg("cntnr"));                             \
python::def("set"#FUNC_INFIX"Parameter", &Vis::set##FUNC_INFIX##Parameter, (python::arg("cntnr"), python::arg(#ARG_NAME))); 

#define EXPORT_CONTROL_PARAM_FUNCS(FUNC_INFIX, ARG_NAME)                                                                          \
python::def("get"#FUNC_INFIX"Parameter", &get##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("has"#FUNC_INFIX"Parameter", &has##FUNC_INFIX##ParameterWrapper, python::arg("cntnr"));                               \
python::def("clear"#FUNC_INFIX"Parameter", &Vis::clear##FUNC_INFIX##Parameter, python::arg("cntnr"));                             \
python::def("set"#FUNC_INFIX"Parameter", &Vis::set##FUNC_INFIX##Parameter, (python::arg("cntnr"), python::arg(#ARG_NAME))); 


namespace
{

    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(double, OutputScalingFactor)
    
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Rectangle2D&, Viewport)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, SizeAdjustment)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, Alignment)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Brush&, BackgroundBrush)

    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, ReactionArrowStyle)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, ReactionArrowColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionArrowLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionArrowHeadLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionArrowHeadWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionArrowShaftWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionArrowLineWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, ReactionComponentLayout)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, ReactionComponentLayoutDirection)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionComponentMargin)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowReactionReactants)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowReactionAgents)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowReactionProducts)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, ReactionAgentAlignment)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, ReactionAgentLayout)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(unsigned int, ReactionAgentLayoutDirection)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, ReactionPlusSignColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionPlusSignSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionPlusSignLineWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowReactionPlusSigns)

    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::ColorTable::SharedPointer&, AtomColorTable)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, AtomColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, UseCalculatedAtomCoordinates)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, AtomLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, AtomLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, SecondaryAtomLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, SecondaryAtomLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, AtomLabelMargin)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, RadicalElectronDotSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowExplicitHydrogens)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowCarbons)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowCharges)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowIsotopes)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowHydrogenCounts)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowNonCarbonHydrogenCounts)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowAtomQueryInfos)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowAtomReactionInfos)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowRadicalElectrons)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowAtomConfigurationLabels)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowAtomCustomLabels)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, EnableAtomHighlighting)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, AtomConfigurationLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, AtomConfigurationLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, AtomConfigurationLabelColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, AtomCustomLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, AtomCustomLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, AtomCustomLabelColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, AtomHighlightAreaSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Brush&, AtomHighlightAreaBrush)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Pen&, AtomHighlightAreaOutlinePen)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, BreakAtomHighlightAreaOutline)
    
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, HighlightAreaOutlineWidth)
    
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, BondColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondLineWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondLineSpacing)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, StereoBondWedgeWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, StereoBondHashSpacing)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionCenterLineLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ReactionCenterLineSpacing)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, DoubleBondTrimLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, TripleBondTrimLength)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, BondLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondLabelMargin)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowBondReactionInfos)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowBondQueryInfos)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowStereoBonds)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowBondConfigurationLabels)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, ShowBondCustomLabels)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(bool, EnableBondHighlighting)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, BondConfigurationLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondConfigurationLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, BondConfigurationLabelColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, BondCustomLabelFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondCustomLabelSize)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, BondCustomLabelColor)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, BondHighlightAreaWidth)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Brush&, BondHighlightAreaBrush)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Pen&, BondHighlightAreaOutlinePen)

    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Pen&, GridViewBorderPen)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Pen&, GridViewRowSeparatorPen)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Pen&, GridViewColumnSeparatorPen)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(double, GridViewMargin)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(double, GridViewCellPadding)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Font&, GridViewTextFont)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Color&, GridViewTextColor)

    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::ColorTable::SharedPointer&, FeatureColorTable)
    MAKE_CONTROL_PARAM_FUNC_WRAPPERS(const CDPL::Vis::Material&, DefaultMaterial)
}


void CDPLPythonVis::exportControlParameterFunctions()
{
    using namespace boost;
    using namespace CDPL;

    EXPORT_CONTROL_PARAM_FUNCS(OutputScalingFactor, factor)
        
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(Viewport, viewport)
    EXPORT_CONTROL_PARAM_FUNCS(SizeAdjustment, adjustment)
    EXPORT_CONTROL_PARAM_FUNCS(Alignment, alignment)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BackgroundBrush, brush)

    EXPORT_CONTROL_PARAM_FUNCS(ReactionArrowStyle, style)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionArrowColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionArrowLength, length)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionArrowHeadLength, length)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionArrowHeadWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionArrowShaftWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionArrowLineWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS(ReactionComponentLayout, layout)
    EXPORT_CONTROL_PARAM_FUNCS(ReactionComponentLayoutDirection, dir)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionComponentMargin, margin)
    EXPORT_CONTROL_PARAM_FUNCS(ShowReactionReactants, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowReactionAgents, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowReactionProducts, show)
    EXPORT_CONTROL_PARAM_FUNCS(ReactionAgentAlignment, alignment)
    EXPORT_CONTROL_PARAM_FUNCS(ReactionAgentLayout, layout)
    EXPORT_CONTROL_PARAM_FUNCS(ReactionAgentLayoutDirection, dir)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionPlusSignColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionPlusSignSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionPlusSignLineWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS(ShowReactionPlusSigns, show)

    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomColorTable, colors)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomColor, color)
    EXPORT_CONTROL_PARAM_FUNCS(UseCalculatedAtomCoordinates, use)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(SecondaryAtomLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(SecondaryAtomLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomLabelMargin, margin)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(RadicalElectronDotSize, size)
    EXPORT_CONTROL_PARAM_FUNCS(ShowExplicitHydrogens, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowCarbons, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowCharges, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowIsotopes, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowHydrogenCounts, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowNonCarbonHydrogenCounts, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowAtomQueryInfos, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowAtomReactionInfos, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowRadicalElectrons, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowAtomConfigurationLabels, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowAtomCustomLabels, show)
    EXPORT_CONTROL_PARAM_FUNCS(EnableAtomHighlighting, enable)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomConfigurationLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomConfigurationLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomConfigurationLabelColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomCustomLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomCustomLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomCustomLabelColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomHighlightAreaSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomHighlightAreaBrush, brush)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(AtomHighlightAreaOutlinePen, pen)
    EXPORT_CONTROL_PARAM_FUNCS(BreakAtomHighlightAreaOutline, brk)

    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(HighlightAreaOutlineWidth, width)
        
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondLength, length)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondLineWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondLineSpacing, spacing)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(StereoBondWedgeWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(StereoBondHashSpacing, spacing)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionCenterLineLength, length)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(ReactionCenterLineSpacing, spacing)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(DoubleBondTrimLength, length)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(TripleBondTrimLength, length)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondLabelMargin, margin)
    EXPORT_CONTROL_PARAM_FUNCS(ShowBondReactionInfos, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowBondQueryInfos, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowStereoBonds, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowBondConfigurationLabels, show)
    EXPORT_CONTROL_PARAM_FUNCS(ShowBondCustomLabels, show)
    EXPORT_CONTROL_PARAM_FUNCS(EnableBondHighlighting, enable)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondConfigurationLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondConfigurationLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondConfigurationLabelColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondCustomLabelFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondCustomLabelSize, size)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondCustomLabelColor, color)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondHighlightAreaWidth, width)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondHighlightAreaBrush, brush)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(BondHighlightAreaOutlinePen, pen)

    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(GridViewBorderPen, pen)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(GridViewRowSeparatorPen, pen)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(GridViewColumnSeparatorPen, pen)
    EXPORT_CONTROL_PARAM_FUNCS(GridViewMargin, margin)
    EXPORT_CONTROL_PARAM_FUNCS(GridViewCellPadding, padding)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(GridViewTextFont, font)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(GridViewTextColor, color)

    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(FeatureColorTable, colors)
    EXPORT_CONTROL_PARAM_FUNCS_INT_REF(DefaultMaterial, matrial)
}
