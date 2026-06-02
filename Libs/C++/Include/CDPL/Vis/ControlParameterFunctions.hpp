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
        class Material;

        /**
         * \brief Returns the value of the Vis::ControlParameter::OUTPUT_SCALING_FACTOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::OUTPUT_SCALING_FACTOR parameter.
         * \since 1.2
         */
        CDPL_VIS_API double getOutputScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::OUTPUT_SCALING_FACTOR parameter of \a cntnr to \a factor.
         * \param cntnr The control-parameter container to update.
         * \param factor The new parameter value.
         * \since 1.2
         */
        CDPL_VIS_API void setOutputScalingFactorParameter(Base::ControlParameterContainer& cntnr, double factor);

        /**
         * \brief Tells whether the Vis::ControlParameter::OUTPUT_SCALING_FACTOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasOutputScalingFactorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::OUTPUT_SCALING_FACTOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearOutputScalingFactorParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::VIEWPORT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::VIEWPORT parameter.
         */
        CDPL_VIS_API const Rectangle2D& getViewportParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::VIEWPORT parameter of \a cntnr to \a viewport.
         * \param cntnr The control-parameter container to update.
         * \param viewport The new viewport rectangle.
         */
        CDPL_VIS_API void setViewportParameter(Base::ControlParameterContainer& cntnr, const Rectangle2D& viewport);

        /**
         * \brief Tells whether the Vis::ControlParameter::VIEWPORT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasViewportParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::VIEWPORT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearViewportParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SIZE_ADJUSTMENT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SIZE_ADJUSTMENT parameter.
         */
        CDPL_VIS_API unsigned int getSizeAdjustmentParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SIZE_ADJUSTMENT parameter of \a cntnr to \a adjustment.
         * \param cntnr The control-parameter container to update.
         * \param adjustment The new size-adjustment policy (see Vis::SizeAdjustment).
         */
        CDPL_VIS_API void setSizeAdjustmentParameter(Base::ControlParameterContainer& cntnr, unsigned int adjustment);

        /**
         * \brief Tells whether the Vis::ControlParameter::SIZE_ADJUSTMENT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasSizeAdjustmentParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SIZE_ADJUSTMENT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearSizeAdjustmentParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::ALIGNMENT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ALIGNMENT parameter.
         */
        CDPL_VIS_API unsigned int getAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ALIGNMENT parameter of \a cntnr to \a alignment.
         * \param cntnr The control-parameter container to update.
         * \param alignment The new alignment flag combination (see Vis::Alignment).
         */
        CDPL_VIS_API void setAlignmentParameter(Base::ControlParameterContainer& cntnr, unsigned int alignment);

        /**
         * \brief Tells whether the Vis::ControlParameter::ALIGNMENT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ALIGNMENT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearAlignmentParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BACKGROUND_BRUSH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BACKGROUND_BRUSH parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getBackgroundBrushParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BACKGROUND_BRUSH parameter of \a cntnr to \a brush.
         * \param cntnr The control-parameter container to update.
         * \param brush The new background brush.
         * \since 1.2
         */
        CDPL_VIS_API void setBackgroundBrushParameter(Base::ControlParameterContainer& cntnr, const Brush& brush);

        /**
         * \brief Tells whether the Vis::ControlParameter::BACKGROUND_BRUSH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBackgroundBrushParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BACKGROUND_BRUSH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBackgroundBrushParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_STYLE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_STYLE parameter.
         */
        CDPL_VIS_API unsigned int getReactionArrowStyleParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_STYLE parameter of \a cntnr to \a style.
         * \param cntnr The control-parameter container to update.
         * \param style The new arrow style (see Vis::ArrowStyle).
         */
        CDPL_VIS_API void setReactionArrowStyleParameter(Base::ControlParameterContainer& cntnr, unsigned int style);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_STYLE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowStyleParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_STYLE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowStyleParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_COLOR parameter.
         */
        CDPL_VIS_API const Color& getReactionArrowColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new arrow color.
         */
        CDPL_VIS_API void setReactionArrowColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowColorParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_LENGTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionArrowLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_LENGTH parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new arrow length.
         */
        CDPL_VIS_API void setReactionArrowLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowLengthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionArrowHeadLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH parameter of \a cntnr to \a length.
         * \param cntnr The control-parameter container to update.
         * \param length The new arrow head length.
         */
        CDPL_VIS_API void setReactionArrowHeadLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowHeadLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowHeadLengthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionArrowHeadWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new arrow head width.
         */
        CDPL_VIS_API void setReactionArrowHeadWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowHeadWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowHeadWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionArrowShaftWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new arrow shaft width.
         */
        CDPL_VIS_API void setReactionArrowShaftWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowShaftWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowShaftWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionArrowLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new arrow outline width.
         */
        CDPL_VIS_API void setReactionArrowLineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionArrowLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionArrowLineWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT parameter.
         */
        CDPL_VIS_API unsigned int getReactionComponentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT parameter of \a cntnr to \a layout.
         * \param cntnr The control-parameter container to update.
         * \param layout The new layout style (see Vis::LayoutStyle).
         */
        CDPL_VIS_API void setReactionComponentLayoutParameter(Base::ControlParameterContainer& cntnr, unsigned int layout);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionComponentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionComponentLayoutParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION parameter.
         */
        CDPL_VIS_API unsigned int getReactionComponentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION parameter of \a cntnr to \a dir.
         * \param cntnr The control-parameter container to update.
         * \param dir The new layout direction (see Vis::LayoutDirection).
         */
        CDPL_VIS_API void setReactionComponentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr, unsigned int dir);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionComponentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionComponentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_COMPONENT_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_COMPONENT_MARGIN parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionComponentMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_COMPONENT_MARGIN parameter of \a cntnr to \a margin.
         * \param cntnr The control-parameter container to update.
         * \param margin The new component margin.
         */
        CDPL_VIS_API void setReactionComponentMarginParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& margin);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_COMPONENT_MARGIN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionComponentMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_COMPONENT_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionComponentMarginParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_REACTION_REACTANTS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_REACTION_REACTANTS parameter.
         */
        CDPL_VIS_API bool getShowReactionReactantsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_REACTION_REACTANTS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show the reaction reactants, and \c false to hide them.
         */
        CDPL_VIS_API void setShowReactionReactantsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_REACTION_REACTANTS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowReactionReactantsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_REACTION_REACTANTS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowReactionReactantsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_REACTION_AGENTS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_REACTION_AGENTS parameter.
         */
        CDPL_VIS_API bool getShowReactionAgentsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_REACTION_AGENTS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show the reaction agents, and \c false to hide them.
         */
        CDPL_VIS_API void setShowReactionAgentsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_REACTION_AGENTS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowReactionAgentsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_REACTION_AGENTS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowReactionAgentsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_REACTION_PRODUCTS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_REACTION_PRODUCTS parameter.
         */
        CDPL_VIS_API bool getShowReactionProductsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_REACTION_PRODUCTS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show the reaction products, and \c false to hide them.
         */
        CDPL_VIS_API void setShowReactionProductsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_REACTION_PRODUCTS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowReactionProductsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_REACTION_PRODUCTS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowReactionProductsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_AGENT_ALIGNMENT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_AGENT_ALIGNMENT parameter.
         */
        CDPL_VIS_API unsigned int getReactionAgentAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_AGENT_ALIGNMENT parameter of \a cntnr to \a alignment.
         * \param cntnr The control-parameter container to update.
         * \param alignment The new agent alignment (see Vis::Alignment).
         */
        CDPL_VIS_API void setReactionAgentAlignmentParameter(Base::ControlParameterContainer& cntnr, unsigned int alignment);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_AGENT_ALIGNMENT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionAgentAlignmentParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_AGENT_ALIGNMENT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionAgentAlignmentParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_AGENT_LAYOUT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_AGENT_LAYOUT parameter.
         */
        CDPL_VIS_API unsigned int getReactionAgentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_AGENT_LAYOUT parameter of \a cntnr to \a layout.
         * \param cntnr The control-parameter container to update.
         * \param layout The new agent layout style (see Vis::LayoutStyle).
         */
        CDPL_VIS_API void setReactionAgentLayoutParameter(Base::ControlParameterContainer& cntnr, unsigned int layout);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_AGENT_LAYOUT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionAgentLayoutParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_AGENT_LAYOUT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionAgentLayoutParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION parameter.
         */
        CDPL_VIS_API unsigned int getReactionAgentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION parameter of \a cntnr to \a dir.
         * \param cntnr The control-parameter container to update.
         * \param dir The new agent layout direction (see Vis::LayoutDirection).
         */
        CDPL_VIS_API void setReactionAgentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr, unsigned int dir);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionAgentLayoutDirectionParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionAgentLayoutDirectionParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR parameter.
         */
        CDPL_VIS_API const Color& getReactionPlusSignColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new plus-sign color.
         */
        CDPL_VIS_API void setReactionPlusSignColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionPlusSignColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionPlusSignColorParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionPlusSignSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new plus-sign size.
         */
        CDPL_VIS_API void setReactionPlusSignSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionPlusSignSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionPlusSignSizeParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionPlusSignLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new plus-sign line width.
         */
        CDPL_VIS_API void setReactionPlusSignLineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionPlusSignLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionPlusSignLineWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS parameter.
         */
        CDPL_VIS_API bool getShowReactionPlusSignsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to draw the '+' signs, and \c false to hide them.
         */
        CDPL_VIS_API void setShowReactionPlusSignsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowReactionPlusSignsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowReactionPlusSignsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_COLOR parameter.
         */
        CDPL_VIS_API const Color& getAtomColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new atom color.
         */
        CDPL_VIS_API void setAtomColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAtomColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearAtomColorParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_COLOR_TABLE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_COLOR_TABLE parameter.
         */
        CDPL_VIS_API const ColorTable::SharedPointer& getAtomColorTableParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_COLOR_TABLE parameter of \a cntnr to \a colors.
         * \param cntnr The control-parameter container to update.
         * \param colors The new atom color table.
         */
        CDPL_VIS_API void setAtomColorTableParameter(Base::ControlParameterContainer& cntnr, const ColorTable::SharedPointer& colors);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_COLOR_TABLE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAtomColorTableParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_COLOR_TABLE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearAtomColorTableParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES parameter.
         */
        CDPL_VIS_API bool getUseCalculatedAtomCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES parameter of \a cntnr to \a use.
         * \param cntnr The control-parameter container to update.
         * \param use \c true to use calculated atom coordinates, and \c false to use stored ones when available.
         */
        CDPL_VIS_API void setUseCalculatedAtomCoordinatesParameter(Base::ControlParameterContainer& cntnr, bool use);

        /**
         * \brief Tells whether the Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasUseCalculatedAtomCoordinatesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearUseCalculatedAtomCoordinatesParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_LABEL_FONT parameter.
         */
        CDPL_VIS_API const Font& getAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new atom label font.
         */
        CDPL_VIS_API void setAtomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearAtomLabelFontParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_LABEL_SIZE parameter.
         */
        CDPL_VIS_API const SizeSpecification& getAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new atom label size.
         */
        CDPL_VIS_API void setAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT parameter.
         */
        CDPL_VIS_API const Font& getSecondaryAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new secondary atom label font.
         */
        CDPL_VIS_API void setSecondaryAtomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasSecondaryAtomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearSecondaryAtomLabelFontParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE parameter.
         */
        CDPL_VIS_API const SizeSpecification& getSecondaryAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new secondary atom label size.
         */
        CDPL_VIS_API void setSecondaryAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasSecondaryAtomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearSecondaryAtomLabelSizeParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_LABEL_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_LABEL_MARGIN parameter.
         */
        CDPL_VIS_API const SizeSpecification& getAtomLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_LABEL_MARGIN parameter of \a cntnr to \a margin.
         * \param cntnr The control-parameter container to update.
         * \param margin The new atom label margin.
         */
        CDPL_VIS_API void setAtomLabelMarginParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& margin);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_LABEL_MARGIN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAtomLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_LABEL_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearAtomLabelMarginParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE parameter.
         */
        CDPL_VIS_API const SizeSpecification& getRadicalElectronDotSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new radical electron dot size.
         */
        CDPL_VIS_API void setRadicalElectronDotSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasRadicalElectronDotSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearRadicalElectronDotSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_SIZE parameter.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getAtomHighlightAreaSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new atom highlight area size.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomHighlightAreaSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomHighlightAreaSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomHighlightAreaSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_BRUSH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_BRUSH parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getAtomHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_BRUSH parameter of \a cntnr to \a brush.
         * \param cntnr The control-parameter container to update.
         * \param brush The new atom highlight area brush.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr, const Brush& brush);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_BRUSH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_BRUSH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getAtomHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter of \a cntnr to \a pen.
         * \param cntnr The control-parameter container to update.
         * \param pen The new atom highlight area outline pen.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter.
         * \since 1.2
         */
        CDPL_VIS_API bool getBreakAtomHighlightAreaOutlineParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter of \a cntnr to \a brk.
         * \param cntnr The control-parameter container to update.
         * \param brk \c true to break the outline at incident highlighted bonds, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API void setBreakAtomHighlightAreaOutlineParameter(Base::ControlParameterContainer& cntnr, bool brk);

        /**
         * \brief Tells whether the Vis::ControlParameter::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBreakAtomHighlightAreaOutlineParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBreakAtomHighlightAreaOutlineParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS parameter.
         */
        CDPL_VIS_API bool getShowExplicitHydrogensParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show explicit hydrogens, and \c false to hide them.
         */
        CDPL_VIS_API void setShowExplicitHydrogensParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowExplicitHydrogensParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowExplicitHydrogensParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_CARBONS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_CARBONS parameter.
         */
        CDPL_VIS_API bool getShowCarbonsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_CARBONS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show carbon element labels, and \c false to hide them.
         */
        CDPL_VIS_API void setShowCarbonsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_CARBONS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowCarbonsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_CARBONS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowCarbonsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_CHARGES parameter.
         */
        CDPL_VIS_API bool getShowChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_CHARGES parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show formal charges, and \c false to hide them.
         */
        CDPL_VIS_API void setShowChargesParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_CHARGES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowChargesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_CHARGES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowChargesParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_ISOTOPES parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_ISOTOPES parameter.
         */
        CDPL_VIS_API bool getShowIsotopesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_ISOTOPES parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show isotopic mass values, and \c false to hide them.
         */
        CDPL_VIS_API void setShowIsotopesParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_ISOTOPES parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowIsotopesParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_ISOTOPES parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowIsotopesParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_HYDROGEN_COUNTS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_HYDROGEN_COUNTS parameter.
         */
        CDPL_VIS_API bool getShowHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_HYDROGEN_COUNTS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show implicit hydrogen counts, and \c false to hide them.
         */
        CDPL_VIS_API void setShowHydrogenCountsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_HYDROGEN_COUNTS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_HYDROGEN_COUNTS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowHydrogenCountsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS parameter.
         */
        CDPL_VIS_API bool getShowNonCarbonHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show non-carbon implicit hydrogen counts, and \c false to hide them.
         */
        CDPL_VIS_API void setShowNonCarbonHydrogenCountsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowNonCarbonHydrogenCountsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowNonCarbonHydrogenCountsParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS parameter.
         */
        CDPL_VIS_API bool getShowAtomQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show query atom match expressions, and \c false to hide them.
         */
        CDPL_VIS_API void setShowAtomQueryInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowAtomQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowAtomQueryInfosParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS parameter.
         */
        CDPL_VIS_API bool getShowAtomReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show reaction atom-atom mapping numbers, and \c false to hide them.
         */
        CDPL_VIS_API void setShowAtomReactionInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowAtomReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowAtomReactionInfosParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_RADICAL_ELECTRONS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_RADICAL_ELECTRONS parameter.
         */
        CDPL_VIS_API bool getShowRadicalElectronsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_RADICAL_ELECTRONS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show radical electron dots, and \c false to hide them.
         */
        CDPL_VIS_API void setShowRadicalElectronsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_RADICAL_ELECTRONS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowRadicalElectronsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_RADICAL_ELECTRONS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowRadicalElectronsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS parameter.
         * \since 1.1
         */
        CDPL_VIS_API bool getShowAtomConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show atom configuration descriptor labels, and \c false to hide them.
         * \since 1.1
         */
        CDPL_VIS_API void setShowAtomConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasShowAtomConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.1
         */
        CDPL_VIS_API void clearShowAtomConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_ATOM_CUSTOM_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_ATOM_CUSTOM_LABELS parameter.
         * \since 1.2
         */
        CDPL_VIS_API bool getShowAtomCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_ATOM_CUSTOM_LABELS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show atom custom text labels, and \c false to hide them.
         * \since 1.2
         */
        CDPL_VIS_API void setShowAtomCustomLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_ATOM_CUSTOM_LABELS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasShowAtomCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_ATOM_CUSTOM_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearShowAtomCustomLabelsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ENABLE_ATOM_HIGHLIGHTING parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ENABLE_ATOM_HIGHLIGHTING parameter.
         * \since 1.2
         */
        CDPL_VIS_API bool getEnableAtomHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ENABLE_ATOM_HIGHLIGHTING parameter of \a cntnr to \a enale.
         * \param cntnr The control-parameter container to update.
         * \param enale \c true to enable atom highlighting, and \c false to disable it.
         * \since 1.2
         */
        CDPL_VIS_API void setEnableAtomHighlightingParameter(Base::ControlParameterContainer& cntnr, bool enale);

        /**
         * \brief Tells whether the Vis::ControlParameter::ENABLE_ATOM_HIGHLIGHTING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasEnableAtomHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ENABLE_ATOM_HIGHLIGHTING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearEnableAtomHighlightingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE parameter.
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getAtomConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new atom configuration label size.
         * \since 1.1
         */
        CDPL_VIS_API void setAtomConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasAtomConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.1
         */
        CDPL_VIS_API void clearAtomConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT parameter.
         * \since 1.1
         */
        CDPL_VIS_API const Font& getAtomConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new atom configuration label font.
         * \since 1.1
         */
        CDPL_VIS_API void setAtomConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasAtomConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.1
         */
        CDPL_VIS_API void clearAtomConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getAtomConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new atom configuration label color.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE parameter.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getAtomCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new atom custom label size.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Font& getAtomCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new atom custom label font.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomCustomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomCustomLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getAtomCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new atom custom label color.
         * \since 1.2
         */
        CDPL_VIS_API void setAtomCustomLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasAtomCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearAtomCustomLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::HIGHLIGHT_AREA_OUTLINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::HIGHLIGHT_AREA_OUTLINE_WIDTH parameter.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getHighlightAreaOutlineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::HIGHLIGHT_AREA_OUTLINE_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new highlight area outline width.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightAreaOutlineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::HIGHLIGHT_AREA_OUTLINE_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightAreaOutlineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::HIGHLIGHT_AREA_OUTLINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightAreaOutlineWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_LENGTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getBondLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_LENGTH parameter of \a cntnr to \a length.
         * \param cntnr The control-parameter container to update.
         * \param length The new average bond length.
         */
        CDPL_VIS_API void setBondLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondLengthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_COLOR parameter.
         */
        CDPL_VIS_API const Color& getBondColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new bond color.
         */
        CDPL_VIS_API void setBondColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondColorParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_LINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_LINE_WIDTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getBondLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_LINE_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new bond line width.
         */
        CDPL_VIS_API void setBondLineWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_LINE_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondLineWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_LINE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondLineWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_LINE_SPACING parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_LINE_SPACING parameter.
         */
        CDPL_VIS_API const SizeSpecification& getBondLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_LINE_SPACING parameter of \a cntnr to \a spacing.
         * \param cntnr The control-parameter container to update.
         * \param spacing The new bond line spacing.
         */
        CDPL_VIS_API void setBondLineSpacingParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& spacing);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_LINE_SPACING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_LINE_SPACING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondLineSpacingParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getStereoBondWedgeWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new stereo bond wedge width.
         */
        CDPL_VIS_API void setStereoBondWedgeWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasStereoBondWedgeWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearStereoBondWedgeWidthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::STEREO_BOND_HASH_SPACING parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::STEREO_BOND_HASH_SPACING parameter.
         */
        CDPL_VIS_API const SizeSpecification& getStereoBondHashSpacingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::STEREO_BOND_HASH_SPACING parameter of \a cntnr to \a spacing.
         * \param cntnr The control-parameter container to update.
         * \param spacing The new stereo bond hash spacing.
         */
        CDPL_VIS_API void setStereoBondHashSpacingParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& spacing);

        /**
         * \brief Tells whether the Vis::ControlParameter::STEREO_BOND_HASH_SPACING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasStereoBondHashSpacingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::STEREO_BOND_HASH_SPACING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearStereoBondHashSpacingParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionCenterLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH parameter of \a cntnr to \a length.
         * \param cntnr The control-parameter container to update.
         * \param length The new reaction center line length.
         */
        CDPL_VIS_API void setReactionCenterLineLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionCenterLineLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionCenterLineLengthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::REACTION_CENTER_LINE_SPACING parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::REACTION_CENTER_LINE_SPACING parameter.
         */
        CDPL_VIS_API const SizeSpecification& getReactionCenterLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::REACTION_CENTER_LINE_SPACING parameter of \a cntnr to \a spacing.
         * \param cntnr The control-parameter container to update.
         * \param spacing The new reaction center line spacing.
         */
        CDPL_VIS_API void setReactionCenterLineSpacingParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& spacing);

        /**
         * \brief Tells whether the Vis::ControlParameter::REACTION_CENTER_LINE_SPACING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionCenterLineSpacingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::REACTION_CENTER_LINE_SPACING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearReactionCenterLineSpacingParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getDoubleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH parameter of \a cntnr to \a length.
         * \param cntnr The control-parameter container to update.
         * \param length The new double bond trim length.
         */
        CDPL_VIS_API void setDoubleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasDoubleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearDoubleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH parameter.
         */
        CDPL_VIS_API const SizeSpecification& getTripleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH parameter of \a cntnr to \a length.
         * \param cntnr The control-parameter container to update.
         * \param length The new triple bond trim length.
         */
        CDPL_VIS_API void setTripleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasTripleBondTrimLengthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearTripleBondTrimLengthParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_LABEL_FONT parameter.
         */
        CDPL_VIS_API const Font& getBondLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new bond label font.
         */
        CDPL_VIS_API void setBondLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondLabelFontParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_LABEL_SIZE parameter.
         */
        CDPL_VIS_API const SizeSpecification& getBondLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new bond label size.
         */
        CDPL_VIS_API void setBondLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondLabelSizeParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_LABEL_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_LABEL_MARGIN parameter.
         */
        CDPL_VIS_API const SizeSpecification& getBondLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_LABEL_MARGIN parameter of \a cntnr to \a margin.
         * \param cntnr The control-parameter container to update.
         * \param margin The new bond label margin.
         */
        CDPL_VIS_API void setBondLabelMarginParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& margin);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_LABEL_MARGIN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasBondLabelMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_LABEL_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearBondLabelMarginParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_WIDTH parameter.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getBondHighlightAreaWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_WIDTH parameter of \a cntnr to \a width.
         * \param cntnr The control-parameter container to update.
         * \param width The new bond highlight area width.
         * \since 1.2
         */
        CDPL_VIS_API void setBondHighlightAreaWidthParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_WIDTH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondHighlightAreaWidthParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_WIDTH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondHighlightAreaWidthParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_BRUSH parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_BRUSH parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getBondHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_BRUSH parameter of \a cntnr to \a brush.
         * \param cntnr The control-parameter container to update.
         * \param brush The new bond highlight area brush.
         * \since 1.2
         */
        CDPL_VIS_API void setBondHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr, const Brush& brush);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_BRUSH parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondHighlightAreaBrushParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_BRUSH parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondHighlightAreaBrushParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getBondHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter of \a cntnr to \a pen.
         * \param cntnr The control-parameter container to update.
         * \param pen The new bond highlight area outline pen.
         * \since 1.2
         */
        CDPL_VIS_API void setBondHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondHighlightAreaOutlinePenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondHighlightAreaOutlinePenParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_BOND_REACTION_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_BOND_REACTION_INFOS parameter.
         */
        CDPL_VIS_API bool getShowBondReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_BOND_REACTION_INFOS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to draw reaction center marks, and \c false to hide them.
         */
        CDPL_VIS_API void setShowBondReactionInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_BOND_REACTION_INFOS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowBondReactionInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_BOND_REACTION_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowBondReactionInfosParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_BOND_QUERY_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_BOND_QUERY_INFOS parameter.
         */
        CDPL_VIS_API bool getShowBondQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_BOND_QUERY_INFOS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show query bond match expressions, and \c false to hide them.
         */
        CDPL_VIS_API void setShowBondQueryInfosParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_BOND_QUERY_INFOS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowBondQueryInfosParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_BOND_QUERY_INFOS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowBondQueryInfosParameter(Base::ControlParameterContainer& cntnr);


        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_STEREO_BONDS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_STEREO_BONDS parameter.
         */
        CDPL_VIS_API bool getShowStereoBondsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_STEREO_BONDS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to draw stereo bonds, and \c false to disable stereo bond rendering.
         */
        CDPL_VIS_API void setShowStereoBondsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_STEREO_BONDS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowStereoBondsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_STEREO_BONDS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         */
        CDPL_VIS_API void clearShowStereoBondsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS parameter.
         * \since 1.1
         */
        CDPL_VIS_API bool getShowBondConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show bond configuration descriptor labels, and \c false to hide them.
         * \since 1.1
         */
        CDPL_VIS_API void setShowBondConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasShowBondConfigurationLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.1
         */
        CDPL_VIS_API void clearShowBondConfigurationLabelsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_BOND_CUSTOM_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_BOND_CUSTOM_LABELS parameter.
         * \since 1.2
         */
        CDPL_VIS_API bool getShowBondCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_BOND_CUSTOM_LABELS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show bond custom text labels, and \c false to hide them.
         * \since 1.2
         */
        CDPL_VIS_API void setShowBondCustomLabelsParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_BOND_CUSTOM_LABELS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasShowBondCustomLabelsParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_BOND_CUSTOM_LABELS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearShowBondCustomLabelsParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::ENABLE_BOND_HIGHLIGHTING parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::ENABLE_BOND_HIGHLIGHTING parameter.
         * \since 1.2
         */
        CDPL_VIS_API bool getEnableBondHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::ENABLE_BOND_HIGHLIGHTING parameter of \a cntnr to \a enable.
         * \param cntnr The control-parameter container to update.
         * \param enable \c true to enable bond highlighting, and \c false to disable it.
         * \since 1.2
         */
        CDPL_VIS_API void setEnableBondHighlightingParameter(Base::ControlParameterContainer& cntnr, bool enable);

        /**
         * \brief Tells whether the Vis::ControlParameter::ENABLE_BOND_HIGHLIGHTING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasEnableBondHighlightingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::ENABLE_BOND_HIGHLIGHTING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearEnableBondHighlightingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE parameter.
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getBondConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new bond configuration label size.
         * \since 1.1
         */
        CDPL_VIS_API void setBondConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasBondConfigurationLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.1
         */
        CDPL_VIS_API void clearBondConfigurationLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT parameter.
         * \since 1.1
         */
        CDPL_VIS_API const Font& getBondConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new bond configuration label font.
         * \since 1.1
         */
        CDPL_VIS_API void setBondConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasBondConfigurationLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.1
         */
        CDPL_VIS_API void clearBondConfigurationLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getBondConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new bond configuration label color.
         * \since 1.2
         */
        CDPL_VIS_API void setBondConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondConfigurationLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondConfigurationLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE parameter.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getBondCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE parameter of \a cntnr to \a size.
         * \param cntnr The control-parameter container to update.
         * \param size The new bond custom label size.
         * \since 1.2
         */
        CDPL_VIS_API void setBondCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondCustomLabelSizeParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondCustomLabelSizeParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Font& getBondCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new bond custom label font.
         * \since 1.2
         */
        CDPL_VIS_API void setBondCustomLabelFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondCustomLabelFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondCustomLabelFontParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getBondCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new bond custom label color.
         * \since 1.2
         */
        CDPL_VIS_API void setBondCustomLabelColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasBondCustomLabelColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearBondCustomLabelColorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_BORDER_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_BORDER_PEN parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getGridViewBorderPenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_BORDER_PEN parameter of \a cntnr to \a pen.
         * \param cntnr The control-parameter container to update.
         * \param pen The new grid view border pen.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewBorderPenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_BORDER_PEN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewBorderPenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_BORDER_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewBorderPenParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_ROW_SEPARATOR_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_ROW_SEPARATOR_PEN parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getGridViewRowSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_ROW_SEPARATOR_PEN parameter of \a cntnr to \a pen.
         * \param cntnr The control-parameter container to update.
         * \param pen The new grid view row separator pen.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewRowSeparatorPenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_ROW_SEPARATOR_PEN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewRowSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_ROW_SEPARATOR_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewRowSeparatorPenParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_COLUMN_SEPARATOR_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_COLUMN_SEPARATOR_PEN parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getGridViewColumnSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_COLUMN_SEPARATOR_PEN parameter of \a cntnr to \a pen.
         * \param cntnr The control-parameter container to update.
         * \param pen The new grid view column separator pen.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewColumnSeparatorPenParameter(Base::ControlParameterContainer& cntnr, const Pen& pen);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_COLUMN_SEPARATOR_PEN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewColumnSeparatorPenParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_COLUMN_SEPARATOR_PEN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewColumnSeparatorPenParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_MARGIN parameter.
         * \since 1.2
         */
        CDPL_VIS_API double getGridViewMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_MARGIN parameter of \a cntnr to \a margin.
         * \param cntnr The control-parameter container to update.
         * \param margin The new grid view outer margin.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewMarginParameter(Base::ControlParameterContainer& cntnr, double margin);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_MARGIN parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewMarginParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_MARGIN parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewMarginParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_CELL_PADDING parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_CELL_PADDING parameter.
         * \since 1.2
         */
        CDPL_VIS_API double getGridViewCellPaddingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_CELL_PADDING parameter of \a cntnr to \a padding.
         * \param cntnr The control-parameter container to update.
         * \param padding The new grid view cell padding.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewCellPaddingParameter(Base::ControlParameterContainer& cntnr, double padding);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_CELL_PADDING parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewCellPaddingParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_CELL_PADDING parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewCellPaddingParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_TEXT_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_TEXT_FONT parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Font& getGridViewTextFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_TEXT_FONT parameter of \a cntnr to \a font.
         * \param cntnr The control-parameter container to update.
         * \param font The new grid view text font.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewTextFontParameter(Base::ControlParameterContainer& cntnr, const Font& font);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_TEXT_FONT parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewTextFontParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_TEXT_FONT parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewTextFontParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::GRID_VIEW_TEXT_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::GRID_VIEW_TEXT_COLOR parameter.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getGridViewTextColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::GRID_VIEW_TEXT_COLOR parameter of \a cntnr to \a color.
         * \param cntnr The control-parameter container to update.
         * \param color The new grid view text color.
         * \since 1.2
         */
        CDPL_VIS_API void setGridViewTextColorParameter(Base::ControlParameterContainer& cntnr, const Color& color);

        /**
         * \brief Tells whether the Vis::ControlParameter::GRID_VIEW_TEXT_COLOR parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasGridViewTextColorParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::GRID_VIEW_TEXT_COLOR parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.2
         */
        CDPL_VIS_API void clearGridViewTextColorParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::FEATURE_COLOR_TABLE parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::FEATURE_COLOR_TABLE parameter.
         * \since 1.3
         */
        CDPL_VIS_API const ColorTable::SharedPointer& getFeatureColorTableParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::FEATURE_COLOR_TABLE parameter of \a cntnr to \a colors.
         * \param cntnr The control-parameter container to update.
         * \param colors The new pharmacophoric-feature color table.
         * \since 1.3
         */
        CDPL_VIS_API void setFeatureColorTableParameter(Base::ControlParameterContainer& cntnr, const ColorTable::SharedPointer& colors);

        /**
         * \brief Tells whether the Vis::ControlParameter::FEATURE_COLOR_TABLE parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_VIS_API bool hasFeatureColorTableParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::FEATURE_COLOR_TABLE parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.3
         */
        CDPL_VIS_API void clearFeatureColorTableParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::DEFAULT_MATERIAL parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::DEFAULT_MATERIAL parameter.
         * \since 1.3
         */
        CDPL_VIS_API const Material& getDefaultMaterialParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::DEFAULT_MATERIAL parameter of \a cntnr to \a material.
         * \param cntnr The control-parameter container to update.
         * \param material The new default material.
         * \since 1.3
         */
        CDPL_VIS_API void setDefaultMaterialParameter(Base::ControlParameterContainer& cntnr, const Material& material);

        /**
         * \brief Tells whether the Vis::ControlParameter::DEFAULT_MATERIAL parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_VIS_API bool hasDefaultMaterialParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::DEFAULT_MATERIAL parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.3
         */
        CDPL_VIS_API void clearDefaultMaterialParameter(Base::ControlParameterContainer& cntnr);

        /**
         * \brief Returns the value of the Vis::ControlParameter::SHOW_FEATURE_CENTERS parameter from \a cntnr.
         * \param cntnr The control-parameter container to query.
         * \return The value of the Vis::ControlParameter::SHOW_FEATURE_CENTERS parameter.
         * \since 1.3
         */
        CDPL_VIS_API bool getShowFeatureCentersParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Sets the value of the Vis::ControlParameter::SHOW_FEATURE_CENTERS parameter of \a cntnr to \a show.
         * \param cntnr The control-parameter container to update.
         * \param show \c true to show feature center spheres, and \c false to hide them.
         * \since 1.3
         */
        CDPL_VIS_API void setShowFeatureCentersParameter(Base::ControlParameterContainer& cntnr, bool show);

        /**
         * \brief Tells whether the Vis::ControlParameter::SHOW_FEATURE_CENTERS parameter of \a cntnr is set.
         * \param cntnr The control-parameter container to query.
         * \return \c true if the parameter is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_VIS_API bool hasShowFeatureCentersParameter(const Base::ControlParameterContainer& cntnr);

        /**
         * \brief Removes the Vis::ControlParameter::SHOW_FEATURE_CENTERS parameter from \a cntnr.
         * \param cntnr The control-parameter container.
         * \since 1.3
         */
        CDPL_VIS_API void clearShowFeatureCentersParameter(Base::ControlParameterContainer& cntnr);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_CONTROLPARAMETERFUNCTIONS_HPP
