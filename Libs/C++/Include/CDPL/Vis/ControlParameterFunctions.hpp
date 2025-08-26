/* 
 * ControlParameterFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of convenience functions for control-parameter handling.
 */

#ifndef CDPL_VIS_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_VIS_CONTROLPARAMETERFUNCTIONS_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL
{

    namespace Base
    {

        class ControlParameterContainer;
    }

    namespace Vis
    {

        class Rectangle2D;
        class SizeSpecification;
        class Font;
        class Color;
        class Pen;
        class Brush;

        /*
         * \since 1.2
         */
        CDPL_VIS_API double getOutputScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setOutputScalingFactorParameter(Base::ControlParameterContainer& cntnr, double factor);

        CDPL_VIS_API bool hasOutputScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearOutputScalingFactorParameter(Base::ControlParameterContainer& cntnr);

        
        CDPL_VIS_API const Rectangle2D& getViewportParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setViewportParameter(Base::ControlParameterContainer& cntnr, const Rectangle2D& viewport);

        CDPL_VIS_API bool hasViewportParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearViewportParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getSizeAdjustmentParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setSizeAdjustmentParameter(Base::ControlParameterContainer& cntnr, unsigned int adjustment);

        CDPL_VIS_API bool hasSizeAdjustmentParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearSizeAdjustmentParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAlignmentParameter(Base::ControlParameterContainer& cntnr, unsigned int alignment);

        CDPL_VIS_API bool hasAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAlignmentParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getBackgroundBrushParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBackgroundBrushParameter(Base::ControlParameterContainer& cntnr, const Brush& brush);

        CDPL_VIS_API bool hasBackgroundBrushParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBackgroundBrushParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getReactionArrowStyleParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowStyleParameter(Base::ControlParameterContainer& cntnr, unsigned int style);

        CDPL_VIS_API bool hasReactionArrowStyleParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowStyleParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Color& getReactionArrowColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasReactionArrowColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowColorParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionArrowLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasReactionArrowLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowLengthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionArrowHeadLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowHeadLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        CDPL_VIS_API bool hasReactionArrowHeadLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowHeadLengthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionArrowHeadWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowHeadWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasReactionArrowHeadWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowHeadWidthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionArrowShaftWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowShaftWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasReactionArrowShaftWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowShaftWidthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionArrowLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionArrowLineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasReactionArrowLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionArrowLineWidthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getReactionComponentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionComponentLayoutParameter(Base::ControlParameterContainer& cntnr, unsigned int layout);

        CDPL_VIS_API bool hasReactionComponentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionComponentLayoutParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getReactionComponentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionComponentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr, unsigned int dir);

        CDPL_VIS_API bool hasReactionComponentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionComponentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionComponentMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionComponentMarginParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& margin);

        CDPL_VIS_API bool hasReactionComponentMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionComponentMarginParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowReactionReactantsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowReactionReactantsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowReactionReactantsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowReactionReactantsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowReactionAgentsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowReactionAgentsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowReactionAgentsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowReactionAgentsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowReactionProductsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowReactionProductsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowReactionProductsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowReactionProductsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getReactionAgentAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionAgentAlignmentParameter(Base::ControlParameterContainer& cntnr, unsigned int alignment);

        CDPL_VIS_API bool hasReactionAgentAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionAgentAlignmentParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getReactionAgentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionAgentLayoutParameter(Base::ControlParameterContainer& cntnr, unsigned int layout);

        CDPL_VIS_API bool hasReactionAgentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionAgentLayoutParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API unsigned int getReactionAgentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionAgentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr, unsigned int dir);

        CDPL_VIS_API bool hasReactionAgentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionAgentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Color& getReactionPlusSignColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionPlusSignColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasReactionPlusSignColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionPlusSignColorParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionPlusSignSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionPlusSignSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasReactionPlusSignSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionPlusSignSizeParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionPlusSignLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionPlusSignLineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasReactionPlusSignLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionPlusSignLineWidthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowReactionPlusSignsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowReactionPlusSignsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowReactionPlusSignsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowReactionPlusSignsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Color& getAtomColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasAtomColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomColorParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const ColorTable::SharedPointer& getAtomColorTableParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomColorTableParameter(Base::ControlParameterContainer& cntnr, const ColorTable::SharedPointer& colors);

        CDPL_VIS_API bool hasAtomColorTableParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomColorTableParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getUseCalculatedAtomCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setUseCalculatedAtomCoordinatesParameter(Base::ControlParameterContainer& cntnr, bool use);

        CDPL_VIS_API bool hasUseCalculatedAtomCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearUseCalculatedAtomCoordinatesParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Font& getAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomLabelFontParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Font& getSecondaryAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setSecondaryAtomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasSecondaryAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearSecondaryAtomLabelFontParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getSecondaryAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setSecondaryAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasSecondaryAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearSecondaryAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getAtomLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomLabelMarginParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& margin);

        CDPL_VIS_API bool hasAtomLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomLabelMarginParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getRadicalElectronDotSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setRadicalElectronDotSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasRadicalElectronDotSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearRadicalElectronDotSizeParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getAtomHighlightAreaSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomHighlightAreaSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomHighlightAreaSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomHighlightAreaSizeParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getAtomHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr, const Brush& brush);

        CDPL_VIS_API bool hasAtomHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getAtomHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        CDPL_VIS_API bool hasAtomHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr);
    
        /*
         * \since 1.2
         */
        CDPL_VIS_API bool getBreakAtomHighlightAreaOutlineParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBreakAtomHighlightAreaOutlineParameter(Base::ControlParameterContainer& cntnr, bool brk);

        CDPL_VIS_API bool hasBreakAtomHighlightAreaOutlineParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBreakAtomHighlightAreaOutlineParameter(Base::ControlParameterContainer& cntnr);

        
        CDPL_VIS_API bool getShowExplicitHydrogensParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowExplicitHydrogensParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowExplicitHydrogensParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowExplicitHydrogensParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowCarbonsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowCarbonsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowCarbonsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowCarbonsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowChargesParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowChargesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowChargesParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowIsotopesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowIsotopesParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowIsotopesParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowIsotopesParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowHydrogenCountsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowHydrogenCountsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowNonCarbonHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowNonCarbonHydrogenCountsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowNonCarbonHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowNonCarbonHydrogenCountsParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowAtomQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowAtomQueryInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowAtomQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowAtomQueryInfosParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowAtomReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowAtomReactionInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowAtomReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowAtomReactionInfosParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowRadicalElectronsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowRadicalElectronsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowRadicalElectronsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowRadicalElectronsParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.1
         */
        CDPL_VIS_API bool getShowAtomConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowAtomConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowAtomConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowAtomConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API bool getShowAtomCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowAtomCustomLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowAtomCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowAtomCustomLabelsParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API bool getEnableAtomHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setEnableAtomHighlightingParameter(Base::ControlParameterContainer& cntnr, bool enale);

        CDPL_VIS_API bool hasEnableAtomHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearEnableAtomHighlightingParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getAtomConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const Font& getAtomConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasAtomConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getAtomConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasAtomConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getAtomCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Font& getAtomCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomCustomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasAtomCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomCustomLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getAtomCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setAtomCustomLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasAtomCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearAtomCustomLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getHighlightAreaOutlineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setHighlightAreaOutlineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasHighlightAreaOutlineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearHighlightAreaOutlineWidthParameter(Base::ControlParameterContainer& cntnr);

        
        CDPL_VIS_API const SizeSpecification& getBondLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        CDPL_VIS_API bool hasBondLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondLengthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Color& getBondColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasBondColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondColorParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getBondLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondLineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasBondLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondLineWidthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getBondLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondLineSpacingParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasBondLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondLineSpacingParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getStereoBondWedgeWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setStereoBondWedgeWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasStereoBondWedgeWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearStereoBondWedgeWidthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getStereoBondHashSpacingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setStereoBondHashSpacingParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasStereoBondHashSpacingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearStereoBondHashSpacingParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionCenterLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionCenterLineLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        CDPL_VIS_API bool hasReactionCenterLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionCenterLineLengthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getReactionCenterLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setReactionCenterLineSpacingParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasReactionCenterLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearReactionCenterLineSpacingParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getDoubleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setDoubleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        CDPL_VIS_API bool hasDoubleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearDoubleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getTripleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setTripleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        CDPL_VIS_API bool hasTripleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearTripleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const Font& getBondLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasBondLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondLabelFontParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getBondLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasBondLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondLabelSizeParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API const SizeSpecification& getBondLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondLabelMarginParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& margin);

        CDPL_VIS_API bool hasBondLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondLabelMarginParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getBondHighlightAreaWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondHighlightAreaWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        CDPL_VIS_API bool hasBondHighlightAreaWidthParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondHighlightAreaWidthParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getBondHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr, const Brush& brush);

        CDPL_VIS_API bool hasBondHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getBondHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        CDPL_VIS_API bool hasBondHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr);

        
        CDPL_VIS_API bool getShowBondReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowBondReactionInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowBondReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowBondReactionInfosParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowBondQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowBondQueryInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowBondQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowBondQueryInfosParameter(Base::ControlParameterContainer& cntnr);


        CDPL_VIS_API bool getShowStereoBondsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowStereoBondsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowStereoBondsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowStereoBondsParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.1
         */
        CDPL_VIS_API bool getShowBondConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowBondConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowBondConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowBondConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API bool getShowBondCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setShowBondCustomLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        CDPL_VIS_API bool hasShowBondCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearShowBondCustomLabelsParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API bool getEnableBondHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setEnableBondHighlightingParameter(Base::ControlParameterContainer& cntnr, bool enable);

        CDPL_VIS_API bool hasEnableBondHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearEnableBondHighlightingParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getBondConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasBondConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const Font& getBondConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasBondConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getBondConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasBondConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr);
    
        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getBondCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        CDPL_VIS_API bool hasBondCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Font& getBondCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondCustomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasBondCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondCustomLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getBondCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setBondCustomLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasBondCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearBondCustomLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getGridViewBorderPenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewBorderPenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        CDPL_VIS_API bool hasGridViewBorderPenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewBorderPenParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getGridViewRowSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewRowSeparatorPenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        CDPL_VIS_API bool hasGridViewRowSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewRowSeparatorPenParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getGridViewColumnSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewColumnSeparatorPenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        CDPL_VIS_API bool hasGridViewColumnSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewColumnSeparatorPenParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API double getGridViewMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewMarginParameter(Base::ControlParameterContainer& cntnr, double margin);

        CDPL_VIS_API bool hasGridViewMarginParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewMarginParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API double getGridViewCellPaddingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewCellPaddingParameter(Base::ControlParameterContainer& cntnr, double padding);

        CDPL_VIS_API bool hasGridViewCellPaddingParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewCellPaddingParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Font& getGridViewTextFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewTextFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        CDPL_VIS_API bool hasGridViewTextFontParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewTextFontParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getGridViewTextColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setGridViewTextColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        CDPL_VIS_API bool hasGridViewTextColorParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearGridViewTextColorParameter(Base::ControlParameterContainer& cntnr);

        /*
         * \since 1.3
         */
        CDPL_VIS_API const ColorTable::SharedPointer& getFeatureColorTableParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void setFeatureColorTableParameter(Base::ControlParameterContainer& cntnr, const ColorTable::SharedPointer& colors);

        CDPL_VIS_API bool hasFeatureColorTableParameter(const Base::ControlParameterContainer& cntnr);

        CDPL_VIS_API void clearFeatureColorTableParameter(Base::ControlParameterContainer& cntnr);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_CONTROLPARAMETERFUNCTIONS_HPP
