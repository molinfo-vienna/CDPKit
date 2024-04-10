/* 
 * ControlParameter.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::ControlParameter.
 */

#ifndef CDPL_VIS_CONTROLPARAMETER_HPP
#define CDPL_VIS_CONTROLPARAMETER_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Vis
    {

        /**
         * \brief Provides keys for built-in control-parameters.
         */
        namespace ControlParameter
        {

            /**
             * \brief Specifies a factor for the scaling of logical to drawing surface coordinates.
             *
             * A factor higher than \e 1.0 (the default) makes only sense for rendering to pixel-based surfaces (e.g. a Cairo [\ref CAIRO] image surface).
             * For example, a scaling factor of \e 4.0 causes a logical pixel (a square with side length \e 1.0) being mapped to \e 16 drawing surface pixels.
             * Thus, the higher the scaling factor the higher will be the resolution and size of pixel-based output images.
             *
             * \valuetype double
             */
            extern CDPL_VIS_API const Base::LookupKey OUTPUT_SCALING_FACTOR;
            
            /**
             * \brief Specifies a rectangular viewport area which constrains the location and size of 2D depictions.
             *
             * The way the size and location of
             * a graphical object is adjusted has to be specified separately by the control-parameters Vis::ControlParameter::SIZE_ADJUSTMENT 
             * and Vis::ControlParameter::ALIGNMENT. If \c VIEWPORT is left unspecified, the default setting
             * Vis::ControlParameterDefault::VIEWPORT will be used.
             *
             * \valuetype Vis::Rectangle2D
             */
            extern CDPL_VIS_API const Base::LookupKey VIEWPORT;

            /**
             * \brief Specifies how to adjust the size of a 2D depiction relative to the available viewport area.
             *
             * Supported adjustment policies are defined in namespace Vis::SizeAdjustment. If 
             * \c SIZE_ADJUSTMENT is left unspecified, the default size adjustment setting 
             * Vis::ControlParameterDefault::SIZE_ADJUSTMENT will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The control-parameter setting only takes effect if a valid viewport area has been specified by the parameter
             *       Vis::ControlParameter::VIEWPORT.
             */
            extern CDPL_VIS_API const Base::LookupKey SIZE_ADJUSTMENT;

            /**
             * \brief Specifies the alignment of a 2D depiction within the viewport area.
             *
             * The alignment is specified by a combination of the flags defined in namespace Vis::Alignment.
             * If \c ALIGNMENT is left unspecified, the default alignment setting 
             * Vis::ControlParameterDefault::ALIGNMENT will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The control-parameter setting only takes effect if a valid viewport area has been specified by the parameter
             *       Vis::ControlParameter::VIEWPORT.
             */
            extern CDPL_VIS_API const Base::LookupKey ALIGNMENT;

            /**
             * \brief Specifies the brush with which the drawing area gets erased before rendering any graphical primitives.
             *
             * The area which gets ereased is either the
             * viewport area specified by Vis::ControlParameter::VIEWPORT, or if Vis::ControlParameter::VIEWPORT is not defined, the
             * total bounds of the graphical objects to render. 
             *
             * \valuetype Vis::Brush
             */
            extern CDPL_VIS_API const Base::LookupKey BACKGROUND_BRUSH;

            /**
             * \brief Specifies the style of reaction arrows.
             *
             * Supported styles are defined as constants in namespace Vis::ArrowStyle. If
             * \c REACTION_ARROW_STYLE is left unspecified and the property Vis::ReactionProperty::ARROW_STYLE is not set, the default
             * arrow style Vis::ControlParameterDefault::REACTION_ARROW_STYLE will be used.
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_STYLE.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_STYLE;

            /**
             * \brief Specifies the color of reaction arrows.
             *
             * If the control-parameter is left unspecified and the
             * property Vis::ReactionProperty::ARROW_COLOR is not set, the default setting Vis::ControlParameterDefault::REACTION_ARROW_COLOR
             * will be used. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_COLOR.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_COLOR;

            /**
             * \brief Specifies the length of reaction arrows.
             *
             * Specifying the length as beeing relative has the
             * effect, that the given length is interpreted as a minimum length for an arrow which is as long as the width of the
             * overall area covered by the drawn reaction agents (if any). The output- and input-scaling settings are ignored and have no
             * effect. If the control-parameter is left unspecified and the property Vis::ReactionProperty::ARROW_LENGTH is not set, the
             * default setting Vis::ControlParameterDefault::REACTION_ARROW_LENGTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_LENGTH.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_LENGTH;

            /**
             * \brief Specifies the head length of reaction arrows.
             *
             * The specified head length can be absolute or
             * relative to the overall arrow length defined by Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH.
             * The output- and input-scaling settings are ignored and have no effect.
             * If the control-parameter is left unspecified and the property Vis::ReactionProperty::ARROW_HEAD_LENGTH is not set, the default setting
             * Vis::ControlParameterDefault::REACTION_ARROW_HEAD_LENGTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_HEAD_LENGTH.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_HEAD_LENGTH;

            /**
             * \brief Specifies the head width of reaction arrows.
             *
             * The specified width can be absolute or
             * relative to the overall arrow length defined by Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH.
             * The output- and input-scaling settings are ignored and have no effect.
             * If the control-parameter is left unspecified and the property Vis::ReactionProperty::ARROW_HEAD_WIDTH is not set, the default setting
             * Vis::ControlParameterDefault::REACTION_ARROW_HEAD_WIDTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_HEAD_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_HEAD_WIDTH;

            /**
             * \brief Specifies the shaft width of reaction arrows.
             *
             * The specified width can be absolute or
             * relative to the overall arrow length defined by Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH.
             * The output- and input-scaling settings are ignored and have no effect.
             * If the control-parameter is left unspecified and the property Vis::ReactionProperty::ARROW_SHAFT_WIDTH is not set, the default setting 
             * Vis::ControlParameterDefault::REACTION_ARROW_SHAFT_WIDTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_SHAFT_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_SHAFT_WIDTH;

            /**
             * \brief Specifies the width of reaction arrow outlines.
             *
             * The specified width can be absolute or
             * relative to the overall arrow length defined by Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH.
             * The output- and input-scaling settings are ignored and have no effect.
             * If the control-parameter is left unspecified and the property Vis::ReactionProperty::ARROW_LINE_WIDTH is not set, the default setting
             * Vis::ControlParameterDefault::REACTION_ARROW_HEAD_LENGTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::ARROW_LINE_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_ARROW_LINE_WIDTH;

            /**
             * \brief Specifies the layout style of reaction products and reactants.
             *
             * Supported layout styles are defined in namespace Vis::LayoutStyle. If
             * \c REACTION_COMPONENT_LAYOUT is left unspecified and the property Vis::ReactionProperty::COMPONENT_LAYOUT is not set, the
             * default layout setting Vis::ControlParameterDefault::REACTION_COMPONENT_LAYOUT will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::COMPONENT_LAYOUT.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_COMPONENT_LAYOUT;

            /**
             * \brief Specifies the layout direction of reaction products and reactants.
             *
             * Supported layout directions are defined in namespace Vis::LayoutDirection. If 
             * \c REACTION_COMPONENT_LAYOUT_DIRECTION is left unspecified and the property Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION
             * is not set, the default layout direction Vis::ControlParameterDefault::REACTION_COMPONENT_LAYOUT_DIRECTION will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_COMPONENT_LAYOUT_DIRECTION;

            /**
             * \brief Specifies the amount of free space that is added horizontally and vertically to the bounds of a reaction component.
             *
             * The margin width has to be specified as an absolute value. The output- and input-scaling
             * settings are ignored and have no effect. If the control-parameter is left unspecified and the property 
             * Vis::ReactionProperty::COMPONENT_MARGIN is not set, the default setting Vis::ControlParameterDefault::REACTION_COMPONENT_MARGIN
             * will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::COMPONENT_MARGIN.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_COMPONENT_MARGIN;

            /**
             * \brief Specifies whether or not to show the reactants of a reaction.
             *
             * If the control-parameter is left unspecified and the property
             * Vis::ReactionProperty::SHOW_REACTANTS is not set, the default setting Vis::ControlParameterDefault::SHOW_REACTION_REACTANTS will
             * be used.
             *
             * \valuetype \c bool
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::SHOW_REACTANTS.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_REACTION_REACTANTS;

            /**
             * \brief Specifies whether or not to show the agents of a reaction.
             *
             * If the control-parameter is left unspecified and the property
             * Vis::ReactionProperty::SHOW_AGENTS is not set, the default setting Vis::ControlParameterDefault::SHOW_REACTION_AGENTS will be
             * used.
             *
             * \valuetype \c bool
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::SHOW_AGENTS.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_REACTION_AGENTS;

            /**
             * \brief Specifies whether or not to show the products of a reaction.
             *
             * If the control-parameter is left unspecified and the property
             * Vis::ReactionProperty::SHOW_PRODUCTS is not set, the default setting Vis::ControlParameterDefault::SHOW_REACTION_PRODUCTS will
             * be used.
             *
             * \valuetype \c bool
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::SHOW_PRODUCTS.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_REACTION_PRODUCTS;

            /**
             * \brief Specifies the vertical alignment of reaction agents relative to the reaction arrow.
             *
             * Supported vertical alignment styles are defined in namespace Vis::Alignment. If
             * \c REACTION_AGENT_ALIGNMENT is left unspecified and the property Vis::ReactionProperty::AGENT_ALIGNMENT is not set, the 
             * default alignment setting Vis::ControlParameterDefault::REACTION_AGENT_ALIGNMENT will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::AGENT_ALIGNMENT.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_AGENT_ALIGNMENT;

            /**
             * \brief Specifies the reaction agent layout style.
             *
             * Supported layout styles are defined in namespace Vis::LayoutStyle. If \c REACTION_AGENT_LAYOUT
             * is left unspecified and the property Vis::ReactionProperty::AGENT_LAYOUT is not set, the default layout 
             * Vis::ControlParameterDefault::REACTION_AGENT_LAYOUT will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::AGENT_LAYOUT.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_AGENT_LAYOUT;

            /**
             * \brief Specifies the reaction agent layout direction.
             *
             * Supported layout directions are defined in namespace Vis::LayoutDirection. If 
             * \c REACTION_AGENT_LAYOUT_DIRECTION is left unspecified and the property Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION is
             * not set, the default layout direction Vis::ControlParameterDefault::REACTION_AGENT_LAYOUT_DIRECTION will be used. 
             *
             * \valuetype <tt>unsigned int</tt>
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_AGENT_LAYOUT_DIRECTION;

            /**
             * \brief Specifies the color of reaction component '+' signs.
             *
             * If the control-parameter is left unspecified and the property Vis::ReactionProperty::PLUS_SIGN_COLOR is not set,
             * the default setting Vis::ControlParameterDefault::REACTION_PLUS_SIGN_COLOR will be used. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::PLUS_SIGN_COLOR.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_PLUS_SIGN_COLOR;

            /**
             * \brief Specifies the size of reaction component '+' signs.
             *
             * The size has to be specified as an absolute value. The output- and input-scaling
             * settings are ignored and have no effect. If the control-parameter is left unspecified and the property
             * Vis::ReactionProperty::PLUS_SIGN_SIZE is not set, the default setting Vis::ControlParameterDefault::REACTION_PLUS_SIGN_SIZE
             * will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::PLUS_SIGN_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_PLUS_SIGN_SIZE;

            /**
             * \brief Specifies the line width of reaction component '+' signs.
             *
             * The size has to be specified as an absolute value. The output- and input-scaling
             * settings are ignored and have no effect. If the control-parameter is left unspecified and the property
             * Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH is not set, the default setting 
             * Vis::ControlParameterDefault::REACTION_PLUS_SIGN_LINE_WIDTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_PLUS_SIGN_LINE_WIDTH;

            /**
             * \brief Specifies whether or not to draw '+' signs between the components of a reaction.
             *
             * If the control-parameter is left unspecified and the property
             * Vis::ReactionProperty::SHOW_PLUS_SIGNS is not set, the default setting Vis::ControlParameterDefault::SHOW_REACTION_PLUS_SIGNS
             * will be used.
             *
             * \valuetype \c bool
             * \note The setting is overridden by the Chem::Reaction property Vis::ReactionProperty::SHOW_PLUS_SIGNS.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_REACTION_PLUS_SIGNS;

            /**
             * \brief Specifies the color of atom labels.
             *
             * If \c ATOM_COLOR is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_COLOR and Vis::AtomProperty::COLOR
             * are not set, the default color setting Vis::ControlParameterDefault::ATOM_COLOR will be used. If an atom color table has been
             * specified by Vis::ControlParameter::ATOM_COLOR_TABLE or Vis::MolecularGraphProperty::ATOM_COLOR_TABLE and the property
             * Vis::AtomProperty::COLOR is not set, the color provided by \c ATOM_COLOR or Vis::MolecularGraphProperty::ATOM_COLOR will be
             * used as a fallback for missing color table entries.
             *
             * \valuetype Vis::Color
             * \note The control-parameter setting is ignored if a color has been specified by Vis::MolecularGraphProperty::ATOM_COLOR or 
             *       Vis::AtomProperty::COLOR.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_COLOR;

            /**
             * \brief Specifies a lookup table for the atom type dependent coloring of atom labels.
             *
             * If the color for a particular atom type is missing, the color specified by Vis::ControlParameter::ATOM_COLOR or
             * Vis::MolecularGraphProperty::ATOM_COLOR will be used. 
             *
             * \valuetype Vis::ColorTable::SharedPointer
             * \note The color table will only be considered if the property Vis::AtomProperty::COLOR has not been set for the atom to
             *       visualize. A color table specified by Vis::MolecularGraphProperty::ATOM_COLOR_TABLE takes precedence over the table
             *       specified by \c ATOM_COLOR_TABLE.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_COLOR_TABLE;

            /**
             * \brief Specifies whether or not to use calculated atom coordinates for the visualization of chemical structures.
             *
             * If the control-parameter is set to \c false and assigned 2D atom
             * coordinates are available, then the assigned coordinates will be used. If the parameter is \c true or no assigned
             * 2D-coordinates are available, the atom coordinates will be calculated. If the control-parameter is left unspecified,
             * the default setting Vis::ControlParameterDefault::USE_CALCULATED_ATOM_COORDINATES will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey USE_CALCULATED_ATOM_COORDINATES;

            /**
             * \brief Specifies the font for atom element and query match expression labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_LABEL_FONT and
             * Vis::AtomProperty::LABEL_FONT are not set, the default font Vis::ControlParameterDefault::ATOM_LABEL_FONT will be used. 
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by Vis::MolecularGraphProperty::ATOM_LABEL_FONT
             *       or Vis::AtomProperty::LABEL_FONT.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_LABEL_FONT;

            /**
             * \brief Specifies the size of atom element and query match expression labels.
             *
             * The font size has to be specified as an absolute value. If input-scaling
             * is enabled, the font size will follow the size change of the chemical structure during bond length normalization.
             * If output-scaling is enabled, the font size will grow/shrink with the size of the chemical structure during viewport
             * size adjustment. If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_LABEL_SIZE
             * and Vis::AtomProperty::LABEL_SIZE are not set, the default setting Vis::ControlParameterDefault::ATOM_LABEL_SIZE will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by Vis::MolecularGraphProperty::ATOM_LABEL_SIZE
             *       or Vis::AtomProperty::LABEL_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_LABEL_SIZE;

            /**
             * \brief Specifies the font for text labels that show the value of various atomic properties.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT and
             * Vis::AtomProperty::SECONDARY_LABEL_FONT are not set, the default setting Vis::ControlParameterDefault::SECONDARY_ATOM_LABEL_FONT
             * will be used.
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by 
             *       Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT or Vis::AtomProperty::SECONDARY_LABEL_FONT.
             */
            extern CDPL_VIS_API const Base::LookupKey SECONDARY_ATOM_LABEL_FONT;

            /**
             * \brief Specifies the size of text labels that show the value of various atomic properties.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. If the control-parameter is left unspecified and the properties 
             * Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE and Vis::AtomProperty::SECONDARY_LABEL_SIZE are not set, the default
             * setting Vis::ControlParameterDefault::SECONDARY_ATOM_LABEL_SIZE will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by 
             *       Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE or Vis::AtomProperty::SECONDARY_LABEL_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey SECONDARY_ATOM_LABEL_SIZE;

            /**
             * \brief Specifies the font used for atom configuration descriptor text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_FONT and
             * Vis::AtomProperty::CONFIGURATION_LABEL_FONT are not set, the default setting Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_FONT
             * will be used.
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by 
             *       Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_FONT or Vis::AtomProperty::CONFIGURATION_LABEL_FONT.
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CONFIGURATION_LABEL_FONT;
            
            /**
             * \brief Specifies the size of atom configuration descriptor text labels.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. If the control-parameter is left unspecified and the properties 
             * Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_SIZE and Vis::AtomProperty::CONFIGURATION_LABEL_SIZE are not set, the default
             * setting Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_SIZE will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by 
             *       Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_SIZE or Vis::AtomProperty::ATOM_CONFIGURATION_LABEL_SIZE.
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Specifies the color of atom configuration descriptor text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_COLOR and
             * Vis::AtomProperty::CONFIGURATION_LABEL_COLOR are not set, the default setting Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_COLOR will be used. 
             *
             * \valuetype Vis::Color
             * \note The control-parameter setting is ignored if a color has been specified by Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_COLOR or 
             *       Vis::BondProperty::COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CONFIGURATION_LABEL_COLOR;
        
            /**
             * \brief Specifies the font used for atom custom text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_FONT and
             * Vis::AtomProperty::CUSTOM_LABEL_FONT are not set, the default setting Vis::ControlParameterDefault::ATOM_CUSTOM_LABEL_FONT
             * will be used.
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by 
             *       Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_FONT or Vis::AtomProperty::CUSTOM_LABEL_FONT.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CUSTOM_LABEL_FONT;

            /**
             * \brief Specifies the size of atom custom text labels.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. If the control-parameter is left unspecified and the properties 
             * Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_SIZE and Vis::AtomProperty::CUSTOM_LABEL_SIZE are not set, the default
             * setting Vis::ControlParameterDefault::ATOM_CUSTOM_LABEL_SIZE will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by 
             *       Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_SIZE or Vis::AtomProperty::ATOM_CUSTOM_LABEL_SIZE.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CUSTOM_LABEL_SIZE;

            /**
             * \brief Specifies the color of atom custom text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_COLOR and
             * Vis::AtomProperty::CUSTOM_LABEL_COLOR are not set, the default setting Vis::ControlParameterDefault::ATOM_CUSTOM_LABEL_COLOR will be used. 
             *
             * \valuetype Vis::Color
             * \note The control-parameter setting is ignored if a color has been specified by Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_COLOR or 
             *       Vis::BondProperty::COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CUSTOM_LABEL_COLOR;
            
            /**
             * \brief Specifies the margin of free space around atom labels.
             *
             * The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the label margin will follow the size change of the chemical structure during
             * viewport size adjustment. If the control-parameter is left unspecified and the properties
             * Vis::MolecularGraphProperty::ATOM_LABEL_MARGIN and Vis::AtomProperty::LABEL_MARGIN are not set, the default setting
             * Vis::ControlParameterDefault::ATOM_LABEL_MARGIN will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a margin has been specified by
             *       Vis::MolecularGraphProperty::ATOM_LABEL_MARGIN or Vis::AtomProperty::LABEL_MARGIN.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_LABEL_MARGIN;

            /**
             * \brief Specifies the size of radical electron dots.
             *
             * The dot size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the dot diameter will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the diameter will follow the size change of the chemical structure during
             * viewport size adjustment. If the control-parameter is left unspecified and the properties
             * Vis::MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE and Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE are not set, the
             * default setting Vis::ControlParameterDefault::RADICAL_ELECTRON_DOT_SIZE will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a dot size has been specified by
             *       Vis::MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE or Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey RADICAL_ELECTRON_DOT_SIZE;

            /**
             * \brief Specifies the minimum size of atom highlighting areas.
             *
             * The size has to be specified as an absolute value. 
             * If input-scaling is enabled, the size will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the size will follow the size change of the chemical structure during
             * viewport size adjustment. If the control-parameter is left unspecified and the property
             * Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_SIZE is not set, the default setting 
             * Vis::ControlParameterDefault::ATOM_HIGHLIGHT_AREA_SIZE will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_SIZE.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_HIGHLIGHT_AREA_SIZE;

            /**
             * \brief Specifies the brush to use for filling atom highlighting areas.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_BRUSH and
             * Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH are not set, the default setting Vis::ControlParameterDefault::ATOM_HIGHLIGHT_AREA_BRUSH will be used. 
             *
             * \valuetype Vis::Brush
             * \note The control-parameter setting is ignored if a brush has been specified by
             *       Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_BRUSH or Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_HIGHLIGHT_AREA_BRUSH;
   
            /**
             * \brief Specifies the pen to use for drawing atom highlighting area outlines.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN and
             * Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN are not set, the default setting Vis::ControlParameterDefault::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN
             * will be used. 
             *
             * \valuetype Vis::Pen
             * \note The control-parameter setting is ignored if a pen has been specified by
             *       Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN or Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_HIGHLIGHT_AREA_OUTLINE_PEN;
   
            /**
             * \brief Specifies whether or not the drawing of atom highlighting area outlines shall be suspended at incident highlighted bonds.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE will be used.
             *
             * \valuetype bool
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE;

            /**
             * \brief Specifies whether or not to show explicit hydrogen atoms.
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_EXPLICIT_HYDROGENS
             * will be used.
             *
             * \valuetype \c bool
             * \note This setting has only an effect for standard explicit hydrogen atoms which are bound to at least one heavy atom.
             *       Explicit hydrogens whose formal charge (Vis::ControlParameter::SHOW_CHARGES), 
             *       isotopic mass (see Vis::ControlParameter::SHOW_ISOTOPES), query expression
             *       label (see Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS), atom-atom mapping number
             *       (see Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS) or radical electron cloud 
             *       (see Vis::ControlParameter::SHOW_RADICAL_ELECTRONS) is visible, are always drawn.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_EXPLICIT_HYDROGENS;

            /**
             * \brief Specifies whether or not to show the element label of carbon atoms.
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_CARBONS will be used.
             *
             * \valuetype \c bool
             * \note The control-parameter setting has only an effect for normal carbon atoms with bonds to other visible atoms.
             *       Element labels of isolated carbons and carbons with a visible formal charge (Vis::ControlParameter::SHOW_CHARGES),
             *       isotopic mass (see Vis::ControlParameter::SHOW_ISOTOPES), query 
             *       expression label (see Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS), atom-atom
             *       mapping number (see Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS) or with visible radical
             *       electron dots (see Vis::ControlParameter::SHOW_RADICAL_ELECTRONS) are always shown.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_CARBONS;

            /**
             * \brief Specifies whether or not to show the formal charge of atoms.
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_CHARGES will be used.
             *
             * \valuetype \c bool
             * \note The control-parameter setting has only an effect for atoms with a non-zero formal charge. A formal charge of
             *       zero is never shown.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_CHARGES;

            /**
             * \brief Specifies whether or not to show the isotopic mass of atoms.
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_ISOTOPES will be used.
             *
             * \valuetype \c bool
             * \note The control-parameter setting has only an effect for atoms with a non-zero isotopic mass. An istopic mass of
             *       zero is never shown.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_ISOTOPES;

            /**
             * \brief Specifies whether or not to show the implicit hydrogen count of connected atoms.
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_HYDROGEN_COUNTS will
             * be used.
             *
             * \valuetype \c bool
             * \note The control-parameter setting has no effect for isolated atoms (i.e. that have no bonds to other visible atoms).
             *       The hydrogen count of unbound atoms is always shown.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_HYDROGEN_COUNTS;

            /**
             * \brief Specifies whether or not to show the implicit hydrogen count of connected non-carbon atoms.
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_NON_CARBON_HYDROGEN_COUNTS
             * will be used.
             *
             * \valuetype \c bool
             * \note The control-parameter setting has no effect if Vis::ControlParameter::SHOW_HYDROGEN_COUNTS is
             *       set to \c true or if an atom has no bonds to other visible atoms.
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_NON_CARBON_HYDROGEN_COUNTS;

            /**
             * \brief Specifies whether or not to show query atom match expressions.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_ATOM_QUERY_INFOS will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_ATOM_QUERY_INFOS;

            /**
             * \brief Specifies whether or not to show reaction atom-atom mapping numbers.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_ATOM_REACTION_INFOS will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_ATOM_REACTION_INFOS;

            /**
             * \brief Specifies whether or not to draw radical electron dots.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_RADICAL_ELECTRONS will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_RADICAL_ELECTRONS;
            
            /**
             * \brief Specifies whether or not to show atom configuration descriptor labels.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_ATOM_CONFIGURATION_LABELS will be used.
             *
             * \valuetype \c bool
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_ATOM_CONFIGURATION_LABELS;

            /**
             * \brief Specifies whether or not to show atom custom text labels.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_ATOM_CUSTOM_LABELS will be used.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_ATOM_CUSTOM_LABELS;

            /**
             * \brief Specifies whether or not to enable atom highlighting.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::ENABLE_ATOM_HIGHLIGHTING will be used.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ENABLE_ATOM_HIGHLIGHTING;

            /**
             * \brief Specifies the line width for drawing atom and bond highlighting area outlines.
             *
             * The width has to be specified as an absolute value. If input-scaling 
             * is enabled, the line width will follow the size change of the chemical structure during bond length normalization. 
             * If output-scaling is enabled, the width grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the property Vis::MolecularGraphProperty::HIGHLIGHT_AREA_OUTLINE_WIDTH
             * is not set, the default setting Vis::ControlParameterDefault::HIGHLIGHT_AREA_OUTLINE_WIDTH will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a line width has been specified by 
             *       Vis::MolecularGraphProperty::HIGHLIGHT_AREA_OUTLINE_WIDTH.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey HIGHLIGHT_AREA_OUTLINE_WIDTH;

            /**
             * \brief Specifies the desired average bond length for the visualization of chemical structures.
             *
             * The bond length has to be specified as an absolute value. The input- and output-scaling settings are ignored and have no
             * effect. If the specified bond length is smaller or equal zero, then the structure is not resized and the original 2D atom
             * coordinates are used. Otherwise the atom coordinates are scaled to obtain the specified average bond length. If the
             * control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::BOND_LENGTH will be used.
             *
             * \valuetype Vis::SizeSpecification
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LENGTH;

            /**
             * \brief Specifies the color of bonds.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_COLOR and
             * Vis::BondProperty::COLOR are not set, the default setting Vis::ControlParameterDefault::BOND_COLOR will be used. 
             *
             * \valuetype Vis::Color
             * \note The control-parameter setting is ignored if a color has been specified by Vis::MolecularGraphProperty::BOND_COLOR or 
             *       Vis::BondProperty::COLOR.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_COLOR;

            /**
             * \brief Specifies the width of bond lines.
             *
             * The width can either be specified as an
             * absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the line width 
             * will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the line width grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_LINE_WIDTH
             * and Vis::BondProperty::LINE_WIDTH are not set, the default setting Vis::ControlParameterDefault::BOND_LINE_WIDTH
             * will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a line width has been specified by
             *       Vis::MolecularGraphProperty::BOND_LINE_WIDTH or Vis::BondProperty::LINE_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LINE_WIDTH;

            /**
             * \brief Specifies the distance between the lines of double and triple bonds.
             *
             * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
             * enabled, the line distance will follow the size change of the chemical structure during bond length normalization. If
             * output-scaling is enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_LINE_SPACING and
             * Vis::BondProperty::LINE_SPACING are not set, the default setting Vis::ControlParameterDefault::BOND_LINE_SPACING will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a line spacing has been specified by
             *       Vis::MolecularGraphProperty::BOND_LINE_SAPCING or Vis::BondProperty::LINE_SPACING.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LINE_SPACING;

            /**
             * \brief Specifies the width of wedge-shaped stereo bonds.
             *
             * The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the wedge width will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the wedge width grows/shrinks with the size of the chemical structure during viewport size adjustment. If the
             * control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH and 
             * Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH are not set, the default setting Vis::ControlParameterDefault::STEREO_BOND_WEDGE_WIDTH
             * will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a wedge width has been specified by
             *       Vis::MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH or Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey STEREO_BOND_WEDGE_WIDTH;

            /**
             * \brief Specifies the distance between the hashes of down stereo bonds.
             *
             * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
             * enabled, the hash distance will follow the size change of the chemical structure during bond length normalization. If
             * output-scaling is enabled, the hash distance grows/shrinks with the size of the chemical structure during viewport size
             * adjustment. If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::STEREO_BOND_HASH_SPACING
             * and Vis::BondProperty::STEREO_BOND_HASH_SPACING are not set, the default setting
             * Vis::ControlParameterDefault::STEREO_BOND_HASH_DISTANCE will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a hash spacing has been specified by
             *       Vis::MolecularGraphProperty::STEREO_BOND_HASH_SPACING or Vis::BondProperty::STEREO_BOND_HASH_SPACING.
             */
            extern CDPL_VIS_API const Base::LookupKey STEREO_BOND_HASH_SPACING;

            /**
             * \brief Specifies the length of the lines in reaction center marks.
             *
             * The length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the line length will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH and 
             * Vis::BondProperty::REACTION_CENTER_LINE_LENGTH are not set, the default setting 
             * Vis::ControlParameterDefault::REACTION_CENTER_LINE_LENGTH will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a line length has been specified by
             *       Vis::MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH or Vis::BondProperty::REACTION_CENTER_LINE_LENGTH.
             * \see Vis::ControlParameter::SHOW_BOND_REACTION_INFOS
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_CENTER_LINE_LENGTH;

            /**
             * \brief Specifies the distance between the lines in reaction center marks.
             *
             * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
             * enabled, the line distance will follow the size change of the chemical structure during bond length normalization. If
             * output-scaling is enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::REACTION_CENTER_LINE_SPACING and 
             * Vis::BondProperty::REACTION_CENTER_LINE_SPACING are not set, the default setting
             * Vis::ControlParameterDefault::REACTION_CENTER_LINE_SPACING will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a line length has been specified by
             *       Vis::MolecularGraphProperty::REACTION_CENTER_LINE_SPACING or Vis::BondProperty::REACTION_CENTER_LINE_SPACING.
             * \see Vis::ControlParameter::SHOW_BOND_REACTION_INFOS
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_CENTER_LINE_SPACING;

            /**
             * \brief Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end.
             *
             * The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
             * enabled, the trim length will follow the size change of the chemical structure during bond length normalization. If
             * output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH and
             * Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH are not set, the default setting Vis::ControlParameterDefault::DOUBLE_BOND_TRIM_LENGTH
             * will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a trim length has been specified by
             *       Vis::MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH or Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH.
             * \see Vis::ControlParameter::SHOW_BOND_REACTION_INFOS
             */
            extern CDPL_VIS_API const Base::LookupKey DOUBLE_BOND_TRIM_LENGTH;

            /**
             * \brief Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end.
             *
             * The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
             * enabled, the trim length will follow the size change of the chemical structure during bond length normalization. If
             * output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH and
             * Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH are not set, the default setting Vis::ControlParameterDefault::TRIPLE_BOND_TRIM_LENGTH
             * will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a trim length has been specified by
             *       Vis::MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH or Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH.
             */
            extern CDPL_VIS_API const Base::LookupKey TRIPLE_BOND_TRIM_LENGTH;

            /**
             * \brief Specifies the font for bond labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_LABEL_FONT and
             * Vis::BondProperty::LABEL_FONT are not set, the default setting Vis::ControlParameterDefault::BOND_LABEL_FONT will be used.
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by Vis::MolecularGraphProperty::BOND_LABEL_FONT
             *       or Vis::BondProperty::LABEL_FONT.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LABEL_FONT;

            /**
             * \brief Specifies the size of bond labels.
             *
             * The font size has to be specified as an absolute value. If input-scaling is enabled, the font size will follow the size change of
             * the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change
             * of the chemical structure during viewport size adjustment. If the control-parameter is left unspecified and the properties
             * Vis::MolecularGraphProperty::BOND_LABEL_SIZE and Vis::BondProperty::LABEL_SIZE are not set, the default setting
             * Vis::ControlParameterDefault::BOND_LABEL_SIZE will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a font has been specified by Vis::MolecularGraphProperty::BOND_LABEL_SIZE or
             *       Vis::BondProperty::LABEL_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LABEL_SIZE;
      
            /**
             * \brief Specifies the font used for bond configuration descriptor text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_FONT and
             * Vis::BondProperty::CONFIGURATION_LABEL_FONT are not set, the default setting Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_FONT
             * will be used.
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by 
             *       Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_FONT or Vis::BondProperty::CONFIGURATION_LABEL_FONT.
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CONFIGURATION_LABEL_FONT;
            
            /**
             * \brief Specifies the size of bond configuration descriptor text labels.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::BOND_LABEL_SIZE, Vis::MolecularGraphProperty::BOND_LABEL_SIZE or Vis::BondProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. If the control-parameter is left unspecified and the properties 
             * Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_SIZE and Vis::BondProperty::CONFIGURATION_LABEL_SIZE are not set, the default
             * setting Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_SIZE will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by 
             *       Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_SIZE or Vis::BondProperty::CONFIGURATION_LABEL_SIZE.
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Specifies the color of bond configuration descriptor text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_COLOR and
             * Vis::BondProperty::CONFIGURATION_LABEL_COLOR are not set, the default setting Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_COLOR will be used. 
             *
             * \valuetype Vis::Color
             * \note The control-parameter setting is ignored if a color has been specified by Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_COLOR or 
             *       Vis::BondProperty::COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CONFIGURATION_LABEL_COLOR;
                
            /**
             * \brief Specifies the font used for bond custom text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_FONT and
             * Vis::BondProperty::CUSTOM_LABEL_FONT are not set, the default setting Vis::ControlParameterDefault::BOND_CUSTOM_LABEL_FONT
             * will be used.
             *
             * \valuetype Vis::Font
             * \note The control-parameter setting is ignored if a font has been specified by 
             *       Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_FONT or Vis::BondProperty::CUSTOM_LABEL_FONT.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CUSTOM_LABEL_FONT;
            
            /**
             * \brief Specifies the size of bond custom text labels.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::BOND_LABEL_SIZE, Vis::MolecularGraphProperty::BOND_LABEL_SIZE or Vis::BondProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. If the control-parameter is left unspecified and the properties 
             * Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_SIZE and Vis::BondProperty::CUSTOM_LABEL_SIZE are not set, the default
             * setting Vis::ControlParameterDefault::BOND_CUSTOM_LABEL_SIZE will be used.
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a size has been specified by 
             *       Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_SIZE or Vis::BondProperty::CUSTOM_LABEL_SIZE.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CUSTOM_LABEL_SIZE;

            /**
             * \brief Specifies the color of bond custom text labels.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_COLOR and
             * Vis::BondProperty::CUSTOM_LABEL_COLOR are not set, the default setting Vis::ControlParameterDefault::BOND_CUSTOM_LABEL_COLOR will be used. 
             *
             * \valuetype Vis::Color
             * \note The control-parameter setting is ignored if a color has been specified by Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_COLOR or 
             *       Vis::BondProperty::COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CUSTOM_LABEL_COLOR;
            
            /**
             * \brief Specifies the margin of free space around bond labels.
             *
             * The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::BOND_LABEL_SIZE, Vis::MolecularGraphProperty::BOND_LABEL_SIZE or Vis::BondProperty::LABEL_SIZE.
             * If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during
             * bond length normalization. If output-scaling is enabled, the label margin will follow the size change of the chemical
             * structure during viewport size adjustment. If the control-parameter is left unspecified and the properties
             * Vis::MolecularGraphProperty::BOND_LABEL_MARGIN and Vis::BondProperty::LABEL_MARGIN are not set, the default setting
             * Vis::ControlParameterDefault::BOND_LABEL_MARGIN will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a margin has been specified by Vis::MolecularGraphProperty::BOND_LABEL_MARGIN
             *       or Vis::BondProperty::LABEL_MARGIN.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LABEL_MARGIN;

            /**
             * \brief Specifies the width of bond highlighting areas.
             *
             * The width has to be specified as an absolute value. If input-scaling 
             * is enabled, the width will follow the size change of the chemical structure during bond length normalization. 
             * If output-scaling is enabled, the width grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * If the control-parameter is left unspecified and the property Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_WIDTH
             * is not set, the default setting Vis::ControlParameterDefault::BOND_HIGHLIGHT_AREA_WIDTH will be used. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The control-parameter setting is ignored if a width has been specified by Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_WIDTH.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_HIGHLIGHT_AREA_WIDTH;

            /**
             * \brief Specifies the brush to use for filling bond highlighting areas.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_BRUSH and
             * Vis::BondProperty::HIGHLIGHT_AREA_BRUSH are not set, the default setting Vis::ControlParameterDefault::BOND_HIGHLIGHT_AREA_BRUSH will be used. 
             *
             * \valuetype Vis::Brush
             * \note The control-parameter setting is ignored if a brush has been specified by
             *       Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_BRUSH or Vis::BondProperty::HIGHLIGHT_AREA_BRUSH.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_HIGHLIGHT_AREA_BRUSH;
   
            /**
             * \brief Specifies the pen to use for drawing bond highlighting area outlines.
             *
             * If the control-parameter is left unspecified and the properties Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_OUTLINE_PEN and
             * Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN are not set, the default setting Vis::ControlParameterDefault::BOND_HIGHLIGHT_AREA_OUTLINE_PEN will be used. 
             *
             * \valuetype Vis::Pen
             * \note The control-parameter setting is ignored if a pen has been specified by
             *       Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_OUTLINE_PEN or Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_HIGHLIGHT_AREA_OUTLINE_PEN;

            /**
             * \brief Specifies whether or not to draw reaction center marks.
             *
             * If the control-parameter value is set to \c true and a bond is part of a reaction center, the bond will be decorated with
             * reaction center marks. The look of reaction center marks is determined by the value of the Chem::Bond property
             * Chem::BondProperty::REACTION_CENTER_STATUS:
             *  - the status Chem::ReactionCenterStatus::NO_CENTER is represented by a 'X' label 
             *  - the status Chem::ReactionCenterStatus::IS_CENTER is represented by a '#' label
             *  - if the status flag Chem::ReactionCenterStatus::BOND_ORDER_CHANGE is set, the bond gets decorated with a
             *    single perpendicular line
             *  - if at least one of the status flags Chem::ReactionCenterStatus::BOND_MADE or Chem::ReactionCenterStatus::BOND_BROKEN
             *    is set, the bond gets decorated with two perpendicluar lines
             *  - if the status flag Chem::ReactionCenterStatus::BOND_ORDER_CHANGE and additionally at least one of the flags
             *    Chem::ReactionCenterStatus::BOND_MADE or Chem::ReactionCenterStatus::BOND_BROKEN is set, the bond gets
             *    decorated with three perpendicular lines
             *
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_BOND_REACTION_INFOS
             * will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_BOND_REACTION_INFOS;

            /**
             * \brief Specifies whether or not to show query bond match expressions.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_BOND_QUERY_INFOS will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_BOND_QUERY_INFOS;

            /**
             * \brief Specifies whether or not to draw stereo bonds.
             *
             * If \c SHOW_STEREO_BONDS is set to \c true, the look of single and double bonds is determined by the value of the Chem::Bond
             * property Chem::BondProperty::STEREO_FLAG. 
             *
             * Depending on the value of the stereo flag single bonds are drawn as follows:
             *  - as a filled wedge for Chem::BondStereoFlag::UP and Chem::BondStereoFlag::REVERSE_UP
             *  - as a hashed wedge for Chem::BondStereoFlag::DOWN and Chem::BondStereoFlag::REVERSE_DOWN
             *  - as a zig-zag wedge for Chem::BondStereoFlag::EITHER and Chem::BondStereoFlag::REVERSE_EITHER
             *  - and as a straight line for all other stereo flag values
             *
             * Double bonds are drawn as crossed lines if the bond is flagged with Chem::BondStereoFlag::EITHER or 
             * Chem::BondStereoFlag::REVERSE_EITHER. 
             * All other flag values have no effect.
             * 
             * If the control-parameter is left unspecified, the default setting Vis::ControlParameterDefault::SHOW_STERO_BONDS
             * will be used.
             *
             * \valuetype \c bool
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_STEREO_BONDS;

            /**
             * \brief Specifies whether or not to show bond configuration descriptor labels.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_BOND_CONFIGURATION_LABELS will be used.
             *
             * \valuetype \c bool
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_BOND_CONFIGURATION_LABELS;

            /**
             * \brief Specifies whether or not to show bond custom text labels.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::SHOW_BOND_CUSTOM_LABELS will be used.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey SHOW_BOND_CUSTOM_LABELS;

           /**
             * \brief Specifies whether or not to enable bond highlighting.
             *
             * If the control-parameter is left unspecified, the default setting 
             * Vis::ControlParameterDefault::ENABLE_BOND_HIGHLIGHTING will be used.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ENABLE_BOND_HIGHLIGHTING;

            /**
             * \valuetype Vis::Pen
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_BORDER_PEN;

            /**
             * \valuetype Vis::Pen
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_ROW_SEPARATOR_PEN;

            /**
             * \valuetype Vis::Pen
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_COLUMN_SEPARATOR_PEN;

            /**
             * \valuetype \c double
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_MARGIN;
   
            /**
             * \valuetype \c double
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_CELL_PADDING;
            
            /**
             * \valuetype Vis::Font
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_TEXT_FONT;

            /**
             * \valuetype Vis::Color
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey GRID_VIEW_TEXT_COLOR;
            
        } // namespace ControlParameter
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_CONTROLPARAMETER_HPP
