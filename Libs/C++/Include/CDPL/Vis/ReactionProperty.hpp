/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionProperty.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of constants in namespace CDPL::Vis::ReactionProperty.
 */

#ifndef CDPL_VIS_REACTIONPROPERTY_HPP
#define CDPL_VIS_REACTIONPROPERTY_HPP

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
		 * \brief Provides keys for built-in Chem::Reaction properties.
		 */
		namespace ReactionProperty
		{
	
			/**
			 * \brief Specifies the style of the reaction arrow.
			 *
			 * Supported styles are defined as constants in namespace Vis::ArrowStyle. The arrow style specified by this property takes
			 * precedence over the style specified by the parameter Vis::ControlParameter::REACTION_ARROW_STYLE. 
			 *
			 * \valuetype <tt>unsigned int</tt>
			 */
			extern CDPL_VIS_API const Base::LookupKey ARROW_STYLE;

			/**
			 * \brief Specifies the color of the reaction arrow.
			 *
			 * The specified color takes precedence over the color specified by the parameter Vis::ControlParameter::REACTION_ARROW_COLOR. 
			 *
			 * \valuetype Vis::Color
			 */
			extern CDPL_VIS_API const Base::LookupKey ARROW_COLOR;

			/**
			 * \brief Specifies the length of the reaction arrow.
			 *
			 * Specifying the length as beeing relative has the effect, that the given length is interpreted as a minimum length for an arrow
			 * which is as long as the width of the overall area covered by the drawn reaction agents (if any). The output- and input-scaling
			 * settings are ignored and have no effect. The specified length takes precedence over the length specified by the parameter
			 * Vis::ControlParameter::REACTION_ARROW_LENGTH. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey ARROW_LENGTH;

			/**
			 * \brief Specifies the head length of the reaction arrow.
			 *
			 * The value of the specified length can be absolute or relative to the overall arrow length defined by
			 * Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH. The output- and input-scaling settings
			 * are ignored and have no effect. The specified length takes precedence over the length specified by the parameter
			 * Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey ARROW_HEAD_LENGTH;

			/**
			 * \brief Specifies the head width of the reaction arrow.
			 *
			 * The value of the specified width can be absolute or relative to the overall arrow length defined by
			 * Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH. The output- and input-scaling settings are
			 * ignored and have no effect. The specified width takes precedence over the width specified by the parameter
			 * Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */		
			extern CDPL_VIS_API const Base::LookupKey ARROW_HEAD_WIDTH;

			/**
			 * \brief Specifies the shaft width of the reaction arrow.
			 *
			 * The value of the specified width can be absolute or relative to the overall arrow length defined by
			 * Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH. The output- and input-scaling settings are
			 * ignored and have no effect. The specified width takes precedence over the width specified by the parameter
			 * Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */		
			extern CDPL_VIS_API const Base::LookupKey ARROW_SHAFT_WIDTH;

			/**
			 * \brief Specifies the line width of the reaction arrow outline.
			 *
			 * The value of the specified width can be absolute or relative to the overall arrow length defined by
			 * Vis::ControlParameter::REACTION_ARROW_LENGTH or Vis::ReactionProperty::ARROW_LENGTH. The output- and input-scaling settings are
			 * ignored and have no effect. The specified width takes precedence over the width specified by the parameter
			 * Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */		
			extern CDPL_VIS_API const Base::LookupKey ARROW_LINE_WIDTH;

			/**
			 * \brief Specifies the style of the reaction product and reactant layout.
			 *
			 * Supported layout styles are defined in namespace Vis::LayoutStyle. The specified layout style takes precedence over the layout
			 * specified by the parameter Vis::ControlParameter::REACTION_COMPONENT_LAYOUT. 
			 *
			 * \valuetype <tt>unsigned int</tt>
			 */
			extern CDPL_VIS_API const Base::LookupKey COMPONENT_LAYOUT;

			/**
			 * \brief Specifies the direction of the reaction product and reactant layout.
			 *
			 * Supported layout directions are defined in namespace Vis::LayoutDirection. The specified layout direction takes precedence over
			 * the direction specified by the parameter Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION. 
			 *
			 * \valuetype <tt>unsigned int</tt>
			 */
			extern CDPL_VIS_API const Base::LookupKey COMPONENT_LAYOUT_DIRECTION;

			/**
			 * \brief Specifies the amount of free space that is added horizontally and vertically to the bounds of a reaction component.
			 *
			 * The margin width has to be specified as an absolute value. The output- and input-scaling settings are ignored and have no effect.
			 * The specified margin takes precedence over the margin specified by the parameter Vis::ControlParameter::REACTION_COMPONENT_MARGIN. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey COMPONENT_MARGIN;

			/**
			 * \brief Specifies whether or not to show the reactants of the reaction.
			 *
			 * The reactant visibility specified by this property overrides the setting of the control-parameter
			 * Vis::ControlParameter::SHOW_REACTION_REACTANTS.
			 *
			 * \valuetype \c bool
			 */
			extern CDPL_VIS_API const Base::LookupKey SHOW_REACTANTS;
	
			/**
			 * \brief Specifies whether or not to show the agents of the reaction.
			 *
			 * The agent visibility specified by this property overrides the setting of the control-parameter
			 * Vis::ControlParameter::SHOW_REACTION_AGENTS.
			 *
			 * \valuetype \c bool
			 */
			extern CDPL_VIS_API const Base::LookupKey SHOW_AGENTS;
	
			/**
			 * \brief Specifies whether or not to show the products of the reaction.
			 *
			 * The product visibility specified by this property overrides the setting of the control-parameter
			 * Vis::ControlParameter::SHOW_REACTION_PRODUCTS.
			 *
			 * \valuetype \c bool
			 */
			extern CDPL_VIS_API const Base::LookupKey SHOW_PRODUCTS;
	
			/**
			 * \brief Specifies the vertical alignment of the reaction agents relative to the reaction arrow.
			 *
			 * Supported vertical alignment styles are defined in namespace Vis::Alignment. The specified alignment takes precedence over
			 * the alignment specified by the parameter Vis::ControlParameter::REACTION_AGENT_ALIGNMENT. 
			 *
			 * \valuetype <tt>unsigned int</tt>
			 */
			extern CDPL_VIS_API const Base::LookupKey AGENT_ALIGNMENT;

			/**
			 * \brief Specifies the style of the reaction agent layout.
			 *
			 * Supported layout styles are defined in namespace Vis::LayoutStyle. The specified layout style takes precedence over the
			 * layout specified by the parameter Vis::ControlParameter::REACTION_AGENT_LAYOUT. 
			 *
			 * \valuetype <tt>unsigned int</tt>
			 */
			extern CDPL_VIS_API const Base::LookupKey AGENT_LAYOUT;

			/**
			 * \brief Specifies the direction of the reaction agent layout.
			 *
			 * Supported layout directions are defined in namespace Vis::LayoutDirection. The specified layout direction takes precedence 
			 * over the direction specified by the parameter Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION. 
			 *
			 * \valuetype <tt>unsigned int</tt>
			 */
			extern CDPL_VIS_API const Base::LookupKey AGENT_LAYOUT_DIRECTION;

			/**
			 * \brief Specifies the color of the '+' signs between the components of the reaction.
			 *
			 * The specified color takes precedence over the color specified by the parameter Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR. 
			 *
			 * \valuetype Vis::Color
			 */
			extern CDPL_VIS_API const Base::LookupKey PLUS_SIGN_COLOR;

			/**
			 * \brief Specifies the size of the '+' signs between the components of the reaction.
			 *
			 * The size has to be specified as an absolute value. The output- and input-scaling settings are ignored and have no effect. The
			 * specified size takes precedence over the size specified by the parameter Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey PLUS_SIGN_SIZE;

			/**
			 * \brief Specifies the line width of the '+' signs between the components of the reaction.
			 *
			 * The size has to be specified as an absolute value. The output- and input-scaling settings are ignored and have no effect. The
			 * specified line width takes precedence over the width specified by the parameter Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH. 
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey PLUS_SIGN_LINE_WIDTH;
	
			/**
			 * \brief Specifies whether or not to draw '+' signs between the components of the reaction.
			 *
			 * The visibility specified by this property overrides the setting of the control-parameter
			 * Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS.
			 *
			 * \valuetype \c bool
			 */
			extern CDPL_VIS_API const Base::LookupKey SHOW_PLUS_SIGNS;
		}
	}
}

#endif // CDPL_VIS_REACTIONPROPERTY_HPP
