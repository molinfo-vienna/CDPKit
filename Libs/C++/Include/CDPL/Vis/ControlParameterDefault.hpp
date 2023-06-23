/* 
 * ControlParameterDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::ControlParameterDefault.
 */

#ifndef CDPL_VIS_CONTROLPARAMETERDEFAULT_HPP
#define CDPL_VIS_CONTROLPARAMETERDEFAULT_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL 
{

	namespace Vis
	{

		class Color;
		class Font;
		class SizeSpecification;
		class Rectangle2D;

		/**
		 * \brief Provides default values for built-in control-parameters.
		 */
		namespace ControlParameterDefault
		{

			/**
			 * \brief Default setting (= \c %Rectangle2D()) for the control-parameter Vis::ControlParameter::VIEWPORT.
			 */
			extern CDPL_VIS_API const Rectangle2D               VIEWPORT;
		
			/**
			 * \brief Default setting (= \c %SizeAdjustment::IF_REQUIRED) for the control-parameter Vis::ControlParameter::SIZE_ADJUSTMENT.
			 */
			extern CDPL_VIS_API const unsigned int              SIZE_ADJUSTMENT;
		
			/**
			 * \brief Default setting (= \c %Alignment::CENTER) for the control-parameter Vis::ControlParameter::ALIGNMENT.
			 */
			extern CDPL_VIS_API const unsigned int              ALIGNMENT; 

			/**
			 * \brief Default setting (= \c %Color::TRANSPARENT) for the control-parameter Vis::ControlParameter::BACKGROUND_COLOR.
			 */
			extern CDPL_VIS_API const Color                     BACKGROUND_COLOR;

			/**
			 * \brief Default setting (= \c %ArrowStyle::REACTION_SOLID) for the control-parameter Vis::ControlParameter::REACTION_ARROW_STYLE.
			 */
			extern CDPL_VIS_API const unsigned int              REACTION_ARROW_STYLE;
			
			/**
			 * \brief Default setting (= \c %Color::BLACK) for the control-parameter Vis::ControlParameter::REACTION_ARROW_COLOR.
			 */
			extern CDPL_VIS_API const Color                     REACTION_ARROW_COLOR;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(35.0, true, true, true)) for the control-parameter Vis::ControlParameter::REACTION_ARROW_LENGTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_ARROW_LENGTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(8.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_ARROW_HEAD_LENGTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(5.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_ARROW_HEAD_WIDTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_ARROW_SHAFT_WIDTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(1.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_ARROW_LINE_WIDTH;
			
			/**
			 * \brief Default setting (= \c %LayoutStyle::PACKED) for the control-parameter Vis::ControlParameter::REACTION_COMPONENT_LAYOUT.
			 */
			extern CDPL_VIS_API const unsigned int              REACTION_COMPONENT_LAYOUT;
			
			/**
			 * \brief Default setting (= \c %LayoutDirection::HORIZONTAL) for the control-parameter Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION.
			 */
			extern CDPL_VIS_API const unsigned int              REACTION_COMPONENT_LAYOUT_DIRECTION;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(5.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_COMPONENT_MARGIN.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_COMPONENT_MARGIN;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_REACTION_REACTANTS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_REACTION_REACTANTS;

			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_REACTION_AGENTS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_REACTION_AGENTS;

			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_REACTION_PRODUCTS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_REACTION_PRODUCTS;

			/**
			 * \brief Default setting (= \c %Alignment::V_CENTER) for the control-parameter Vis::ControlParameter::REACTION_AGENT_ALIGNMENT.
			 */
			extern CDPL_VIS_API const unsigned int              REACTION_AGENT_ALIGNMENT;
			
			/**
			 * \brief Default setting (= \c %LayoutStyle::LINEAR) for the control-parameter Vis::ControlParameter::REACTION_AGENT_LAYOUT.
			 */
			extern CDPL_VIS_API const unsigned int              REACTION_AGENT_LAYOUT;
			
			/**
			 * \brief Default setting (= \c %LayoutDirection::HORIZONTAL) for the control-parameter Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION.
			 */
			extern CDPL_VIS_API const unsigned int              REACTION_AGENT_LAYOUT_DIRECTION;
			
			/**
			 * \brief Default setting (= \c %Color::BLACK) for the control-parameter Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR.
			 */
			extern CDPL_VIS_API const Color                     REACTION_PLUS_SIGN_COLOR;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(10.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_PLUS_SIGN_SIZE;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(3.0, false, true, true)) for the control-parameter Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_PLUS_SIGN_LINE_WIDTH;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_REACTION_PLUS_SIGNS;
			
			/**
			 * \brief Default setting (= \c %Color::BLACK) for the control-parameter Vis::ControlParameter::ATOM_COLOR.
			 */
			extern CDPL_VIS_API const Color                     ATOM_COLOR;
	
			/**
			 * \brief Default setting (= \c %ColorTable()) for the control-parameter Vis::ControlParameter::ATOM_COLOR_TABLE.
			 */
			extern CDPL_VIS_API const ColorTable::SharedPointer ATOM_COLOR_TABLE;

			/**
			 * \brief Default setting (= \c false) for the control-parameter Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES.
			 */
			extern CDPL_VIS_API const bool                      USE_CALCULATED_ATOM_COORDINATES;
			
			/**
			 * \brief Default setting (= \c %Font()) for the control-parameter Vis::ControlParameter::ATOM_LABEL_FONT.
			 */
			extern CDPL_VIS_API const Font                      ATOM_LABEL_FONT;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(10.0, false, false, true)) for the control-parameter Vis::ControlParameter::ATOM_LABEL_SIZE.
			 */
			extern CDPL_VIS_API const SizeSpecification         ATOM_LABEL_SIZE;
			
			/**
			 * \brief Default setting (= \c %Font()) for the control-parameter Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT.
			 */
			extern CDPL_VIS_API const Font                      SECONDARY_ATOM_LABEL_FONT;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(6.0, false, false, true)) for the control-parameter Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE.
			 */
			extern CDPL_VIS_API const SizeSpecification         SECONDARY_ATOM_LABEL_SIZE;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(2.0, false, false, true)) for the control-parameter Vis::ControlParameter::ATOM_LABEL_MARGIN.
			 */
			extern CDPL_VIS_API const SizeSpecification         ATOM_LABEL_MARGIN;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(1.0, false, false, true)) for the control-parameter Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE.
			 */
			extern CDPL_VIS_API const SizeSpecification         RADICAL_ELECTRON_DOT_SIZE;
			
			/**
			 * \brief Default setting (= \c false) for the control-parameter Vis::ControlParameter::SHOW_CARBONS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_CARBONS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_EXPLICIT_HYDROGENS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_CHARGES.
			 */
			extern CDPL_VIS_API const bool                      SHOW_CHARGES;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_ISOTOPES.
			 */
			extern CDPL_VIS_API const bool                      SHOW_ISOTOPES;
			
			/**
			 * \brief Default setting (= \c false) for the control-parameter Vis::ControlParameter::SHOW_HYDROGEN_COUNTS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_HYDROGEN_COUNTS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_NON_CARBON_HYDROGEN_COUNTS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_ATOM_QUERY_INFOS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_ATOM_REACTION_INFOS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_RADICAL_ELECTRONS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_RADICAL_ELECTRONS;
			
			/**
			 * \brief Default setting (= \c %Color::BLACK) for the control-parameter Vis::ControlParameter::BOND_COLOR.
			 */
			extern CDPL_VIS_API const Color                     BOND_COLOR;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(30.0)) for the control-parameter Vis::ControlParameter::BOND_LENGTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         BOND_LENGTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(1.0, false, false, true)) for the control-parameter Vis::ControlParameter::BOND_LINE_WIDTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         BOND_LINE_WIDTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.15, true, true, true)) for the control-parameter Vis::ControlParameter::BOND_LINE_SPACING.
			 */
			extern CDPL_VIS_API const SizeSpecification         BOND_LINE_SPACING;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.15, true, true, true)) for the control-parameter Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         STEREO_BOND_WEDGE_WIDTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.1, true, true, true)) for the control-parameter Vis::ControlParameter::STEREO_BOND_HASH_SPACING.
			 */
			extern CDPL_VIS_API const SizeSpecification         STEREO_BOND_HASH_SPACING;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.4, true, true, true)) for the control-parameter Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_CENTER_LINE_LENGTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.1, true, true, true)) for the control-parameter Vis::ControlParameter::REACTION_CENTER_LINE_SPACING.
			 */
			extern CDPL_VIS_API const SizeSpecification         REACTION_CENTER_LINE_SPACING;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.1, true, true, true)) for the control-parameter Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         DOUBLE_BOND_TRIM_LENGTH;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(0.1, true, true, true)) for the control-parameter Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH.
			 */
			extern CDPL_VIS_API const SizeSpecification         TRIPLE_BOND_TRIM_LENGTH;
			
			/**
			 * \brief Default setting (= \c %Font()) for the control-parameter Vis::ControlParameter::BOND_LABEL_FONT.
			 */
			extern CDPL_VIS_API const Font                      BOND_LABEL_FONT;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(8.0, false, false, true)) for the control-parameter Vis::ControlParameter::BOND_LABEL_SIZE.
			 */
			extern CDPL_VIS_API const SizeSpecification         BOND_LABEL_SIZE;
			
			/**
			 * \brief Default setting (= \c %SizeSpecification(2.0, false, false, true)) for the control-parameter Vis::ControlParameter::BOND_LABEL_MARGIN.
			 */
			extern CDPL_VIS_API const SizeSpecification         BOND_LABEL_MARGIN;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_BOND_REACTION_INFOS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_BOND_REACTION_INFOS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_BOND_QUERY_INFOS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_BOND_QUERY_INFOS;
			
			/**
			 * \brief Default setting (= \c true) for the control-parameter Vis::ControlParameter::SHOW_STEREO_BONDS.
			 */
			extern CDPL_VIS_API const bool                      SHOW_STEREO_BONDS;
		}
	}
}

#endif // CDPL_VIS_CONTROLPARAMETERDEFAULT_HPP
