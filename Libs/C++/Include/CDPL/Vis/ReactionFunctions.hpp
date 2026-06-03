/*
 * ReactionFunctions.hpp
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
 * \brief Declaration of functions that operate on Chem::Reaction instances.
 */

#ifndef CDPL_VIS_REACTIONFUNCTIONS_HPP
#define CDPL_VIS_REACTIONFUNCTIONS_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Reaction;
    }

    namespace Vis
    {

        class Color;
        class SizeSpecification;

        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_STYLE property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_STYLE property.
         */
        CDPL_VIS_API unsigned int getArrowStyle(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_STYLE property of the reaction \a rxn to \a style.
         * \param rxn The reaction for which to set the property value.
         * \param style The new arrow style (see Vis::ArrowStyle).
         */
        CDPL_VIS_API void setArrowStyle(Chem::Reaction& rxn, unsigned int style);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_STYLE property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowStyle(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_STYLE property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowStyle(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_COLOR property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_COLOR property.
         */
        CDPL_VIS_API const Color& getArrowColor(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_COLOR property of the reaction \a rxn to \a color.
         * \param rxn The reaction for which to set the property value.
         * \param color The new arrow color.
         */
        CDPL_VIS_API void setArrowColor(Chem::Reaction& rxn, const Color& color);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_COLOR property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowColor(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_COLOR property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowColor(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_LENGTH property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_LENGTH property.
         */
        CDPL_VIS_API const SizeSpecification& getArrowLength(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_LENGTH property of the reaction \a rxn to \a length.
         * \param rxn The reaction for which to set the property value.
         * \param length The new arrow length.
         */
        CDPL_VIS_API void setArrowLength(Chem::Reaction& rxn, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_LENGTH property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowLength(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_LENGTH property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowLength(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_HEAD_LENGTH property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_HEAD_LENGTH property.
         */
        CDPL_VIS_API const SizeSpecification& getArrowHeadLength(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_HEAD_LENGTH property of the reaction \a rxn to \a length.
         * \param rxn The reaction for which to set the property value.
         * \param length The new arrow head length.
         */
        CDPL_VIS_API void setArrowHeadLength(Chem::Reaction& rxn, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_HEAD_LENGTH property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowHeadLength(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_HEAD_LENGTH property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowHeadLength(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_HEAD_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_HEAD_WIDTH property.
         */
        CDPL_VIS_API const SizeSpecification& getArrowHeadWidth(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_HEAD_WIDTH property of the reaction \a rxn to \a width.
         * \param rxn The reaction for which to set the property value.
         * \param width The new arrow head width.
         */
        CDPL_VIS_API void setArrowHeadWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_HEAD_WIDTH property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowHeadWidth(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_HEAD_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowHeadWidth(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_SHAFT_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_SHAFT_WIDTH property.
         */
        CDPL_VIS_API const SizeSpecification& getArrowShaftWidth(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_SHAFT_WIDTH property of the reaction \a rxn to \a width.
         * \param rxn The reaction for which to set the property value.
         * \param width The new arrow shaft width.
         */
        CDPL_VIS_API void setArrowShaftWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_SHAFT_WIDTH property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowShaftWidth(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_SHAFT_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowShaftWidth(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::ARROW_LINE_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::ARROW_LINE_WIDTH property.
         */
        CDPL_VIS_API const SizeSpecification& getArrowLineWidth(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::ARROW_LINE_WIDTH property of the reaction \a rxn to \a width.
         * \param rxn The reaction for which to set the property value.
         * \param width The new arrow outline width.
         */
        CDPL_VIS_API void setArrowLineWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ReactionProperty::ARROW_LINE_WIDTH property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasArrowLineWidth(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::ARROW_LINE_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearArrowLineWidth(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::COMPONENT_LAYOUT property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::COMPONENT_LAYOUT property.
         */
        CDPL_VIS_API unsigned int getComponentLayout(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::COMPONENT_LAYOUT property of the reaction \a rxn to \a layout.
         * \param rxn The reaction for which to set the property value.
         * \param layout The new layout style (see Vis::LayoutStyle).
         */
        CDPL_VIS_API void setComponentLayout(Chem::Reaction& rxn, unsigned int layout);

        /**
         * \brief Tells whether the Vis::ReactionProperty::COMPONENT_LAYOUT property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasComponentLayout(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::COMPONENT_LAYOUT property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearComponentLayout(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION property.
         */
        CDPL_VIS_API unsigned int getComponentLayoutDirection(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION property of the reaction \a rxn to \a dir.
         * \param rxn The reaction for which to set the property value.
         * \param dir The new layout direction (see Vis::LayoutDirection).
         */
        CDPL_VIS_API void setComponentLayoutDirection(Chem::Reaction& rxn, unsigned int dir);

        /**
         * \brief Tells whether the Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasComponentLayoutDirection(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearComponentLayoutDirection(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::COMPONENT_MARGIN property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::COMPONENT_MARGIN property.
         */
        CDPL_VIS_API const SizeSpecification& getComponentMargin(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::COMPONENT_MARGIN property of the reaction \a rxn to \a margin.
         * \param rxn The reaction for which to set the property value.
         * \param margin The new component margin.
         */
        CDPL_VIS_API void setComponentMargin(Chem::Reaction& rxn, const SizeSpecification& margin);

        /**
         * \brief Tells whether the Vis::ReactionProperty::COMPONENT_MARGIN property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasComponentMargin(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::COMPONENT_MARGIN property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearComponentMargin(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::SHOW_REACTANTS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::SHOW_REACTANTS property.
         */
        CDPL_VIS_API bool getShowReactants(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::SHOW_REACTANTS property of the reaction \a rxn to \a show.
         * \param rxn The reaction for which to set the property value.
         * \param show \c true to show the reactants, and \c false to hide them.
         */
        CDPL_VIS_API void setShowReactants(Chem::Reaction& rxn, bool show);

        /**
         * \brief Tells whether the Vis::ReactionProperty::SHOW_REACTANTS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowReactants(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::SHOW_REACTANTS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearShowReactants(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::SHOW_AGENTS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::SHOW_AGENTS property.
         */
        CDPL_VIS_API bool getShowAgents(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::SHOW_AGENTS property of the reaction \a rxn to \a show.
         * \param rxn The reaction for which to set the property value.
         * \param show \c true to show the agents, and \c false to hide them.
         */
        CDPL_VIS_API void setShowAgents(Chem::Reaction& rxn, bool show);

        /**
         * \brief Tells whether the Vis::ReactionProperty::SHOW_AGENTS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowAgents(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::SHOW_AGENTS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearShowAgents(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::SHOW_PRODUCTS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::SHOW_PRODUCTS property.
         */
        CDPL_VIS_API bool getShowProducts(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::SHOW_PRODUCTS property of the reaction \a rxn to \a show.
         * \param rxn The reaction for which to set the property value.
         * \param show \c true to show the products, and \c false to hide them.
         */
        CDPL_VIS_API void setShowProducts(Chem::Reaction& rxn, bool show);

        /**
         * \brief Tells whether the Vis::ReactionProperty::SHOW_PRODUCTS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowProducts(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::SHOW_PRODUCTS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearShowProducts(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::AGENT_ALIGNMENT property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::AGENT_ALIGNMENT property.
         */
        CDPL_VIS_API unsigned int getAgentAlignment(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::AGENT_ALIGNMENT property of the reaction \a rxn to \a alignment.
         * \param rxn The reaction for which to set the property value.
         * \param alignment The new agent alignment (see Vis::Alignment).
         */
        CDPL_VIS_API void setAgentAlignment(Chem::Reaction& rxn, unsigned int alignment);

        /**
         * \brief Tells whether the Vis::ReactionProperty::AGENT_ALIGNMENT property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAgentAlignment(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::AGENT_ALIGNMENT property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearAgentAlignment(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::AGENT_LAYOUT property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::AGENT_LAYOUT property.
         */
        CDPL_VIS_API unsigned int getAgentLayout(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::AGENT_LAYOUT property of the reaction \a rxn to \a layout.
         * \param rxn The reaction for which to set the property value.
         * \param layout The new agent layout style (see Vis::LayoutStyle).
         */
        CDPL_VIS_API void setAgentLayout(Chem::Reaction& rxn, unsigned int layout);

        /**
         * \brief Tells whether the Vis::ReactionProperty::AGENT_LAYOUT property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAgentLayout(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::AGENT_LAYOUT property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearAgentLayout(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION property.
         */
        CDPL_VIS_API unsigned int getAgentLayoutDirection(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION property of the reaction \a rxn to \a dir.
         * \param rxn The reaction for which to set the property value.
         * \param dir The new agent layout direction (see Vis::LayoutDirection).
         */
        CDPL_VIS_API void setAgentLayoutDirection(Chem::Reaction& rxn, unsigned int dir);

        /**
         * \brief Tells whether the Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasAgentLayoutDirection(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearAgentLayoutDirection(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::PLUS_SIGN_COLOR property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::PLUS_SIGN_COLOR property.
         */
        CDPL_VIS_API const Color& getPlusSignColor(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::PLUS_SIGN_COLOR property of the reaction \a rxn to \a color.
         * \param rxn The reaction for which to set the property value.
         * \param color The new plus-sign color.
         */
        CDPL_VIS_API void setPlusSignColor(Chem::Reaction& rxn, const Color& color);

        /**
         * \brief Tells whether the Vis::ReactionProperty::PLUS_SIGN_COLOR property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasPlusSignColor(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::PLUS_SIGN_COLOR property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearPlusSignColor(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::PLUS_SIGN_SIZE property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::PLUS_SIGN_SIZE property.
         */
        CDPL_VIS_API const SizeSpecification& getPlusSignSize(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::PLUS_SIGN_SIZE property of the reaction \a rxn to \a size.
         * \param rxn The reaction for which to set the property value.
         * \param size The new plus-sign size.
         */
        CDPL_VIS_API void setPlusSignSize(Chem::Reaction& rxn, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::ReactionProperty::PLUS_SIGN_SIZE property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasPlusSignSize(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::PLUS_SIGN_SIZE property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearPlusSignSize(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH property.
         */
        CDPL_VIS_API const SizeSpecification& getPlusSignLineWidth(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH property of the reaction \a rxn to \a width.
         * \param rxn The reaction for which to set the property value.
         * \param width The new plus-sign line width.
         */
        CDPL_VIS_API void setPlusSignLineWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasPlusSignLineWidth(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearPlusSignLineWidth(Chem::Reaction& rxn);


        /**
         * \brief Returns the value of the Vis::ReactionProperty::SHOW_PLUS_SIGNS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The value of the Vis::ReactionProperty::SHOW_PLUS_SIGNS property.
         */
        CDPL_VIS_API bool getShowPlusSigns(const Chem::Reaction& rxn);

        /**
         * \brief Sets the value of the Vis::ReactionProperty::SHOW_PLUS_SIGNS property of the reaction \a rxn to \a show.
         * \param rxn The reaction for which to set the property value.
         * \param show \c true to draw the '+' signs, and \c false to hide them.
         */
        CDPL_VIS_API void setShowPlusSigns(Chem::Reaction& rxn, bool show);

        /**
         * \brief Tells whether the Vis::ReactionProperty::SHOW_PLUS_SIGNS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasShowPlusSigns(const Chem::Reaction& rxn);

        /**
         * \brief Clears the value of the Vis::ReactionProperty::SHOW_PLUS_SIGNS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_VIS_API void clearShowPlusSigns(Chem::Reaction& rxn);

        /**
         * \brief Prepares \a rxn for 2D visualization by perceiving all properties (aromaticity, hybridization, rings,
         *        stereo, etc.) that downstream 2D-rendering code expects to be set on each reaction component.
         * \param rxn The reaction to prepare (modified in place).
         * \since 1.3
         */
        CDPL_VIS_API void prepareFor2DVisualization(Chem::Reaction& rxn);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_REACTIONFUNCTIONS_HPP
