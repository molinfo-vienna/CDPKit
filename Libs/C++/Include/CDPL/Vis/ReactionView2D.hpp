/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionView2D.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Vis::ReactionView2D.
 */

#ifndef CDPL_VIS_REACTIONVIEW2D_HPP
#define CDPL_VIS_REACTIONVIEW2D_HPP

#include <vector>
#include <map>
#include <memory>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/View2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/PolygonPrimitive2D.hpp"
#include "CDPL/Vis/LineSegmentListPrimitive2D.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Reaction;
		class Molecule;
	}

	namespace Vis
	{

		class ReactionView2DParameters;
		class FontMetrics;
	
		/**
		 * \addtogroup CDPL_VIS_REACTION_VISUALIZATION
		 * @{
		 */

		/**
		 * \brief Implements the 2D visualization of chemical reactions.
		 *
		 * \c %ReactionView2D visualizes chemical reactions in the form of schematic reaction equations in which
		 * the reaction components are depicted as 2D structure diagrams (also known as skeletal formulas [\ref WSKF]
		 * or structural formulas [\ref WSTF]).
		 *
		 * Graphical details of a reaction depiction are customizable on a \c %ReactionView2D instance level
		 * by control-parameters and on a visualized data object level by setting appropriate Chem::Reaction,
		 * Chem::MolecularGraph, Chem::Atom or Chem::Bond properties. Properties of the visualized data objects
		 * have a higher priority than control-parameters of the \c %ReactionView2D instance and properties
		 * of Chem::Atom or Chem::Bond objects override corresponding properties of the parent
		 * Chem::MolecularGraph instance.
		 *
		 * \c %ReactionView2D supports the following control-parameters:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::VIEWPORT</td>
		 *   <td>Specifies a rectangular viewport area which constrains the location and size of the generated reaction diagram</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SIZE_ADJUSTMENT</td>
		 *   <td>Specifies how to adjust the size of the reaction diagram relative to the available viewport area</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ALIGNMENT</td>
		 *   <td>Specifies the alignment of the reaction diagram within the viewport area</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BACKGROUND_COLOR</td>
		 *   <td>Specifies the backround color of the reaction diagram</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ATOM_COLOR</td>
		 *   <td>Specifies the color of atom labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ATOM_COLOR_TABLE</td>
		 *   <td>Specifies a lookup table for the atom type dependent coloring of atom labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES</td>
		 *   <td>Specifies whether or not to use calculated atom coordinates</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ATOM_LABEL_FONT</td>
		 *   <td>Specifies the font for atom element and query match expression labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ATOM_LABEL_SIZE</td>
		 *   <td>Specifies the size of atom element and query match expression labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT</td>
		 *   <td>Specifies the font for text labels that show the value of various atomic properties</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE</td>
		 *   <td>Specifies the size of text labels that show the value of various atomic properties</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ATOM_LABEL_MARGIN</td>
		 *   <td>Specifies the margin of free space around atom labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE</td>
		 *   <td>Specifies the size of radical electron dots</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS</td>
		 *   <td>Specifies whether or not to show explicit hydrogen atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_CARBONS</td>
		 *   <td>Specifies whether or not to show the element label of carbon atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_CHARGES</td>
		 *   <td>Specifies whether or not to show the formal charge of atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_ISOTOPES</td>
		 *   <td>Specifies whether or not to show the isotopic mass of atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_HYDROGEN_COUNTS</td>
		 *   <td>Specifies whether or not to show the implicit hydrogen count of connected atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS</td>
		 *   <td>Specifies whether or not to show the implicit hydrogen count of connected non-carbon atoms</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS</td>
		 *   <td>Specifies whether or not to show query atom match expressions</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS</td>
		 *   <td>Specifies whether or not to show reaction atom-atom mapping numbers</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_RADICAL_ELECTRONS</td>
		 *   <td>Specifies whether or not to draw radical electron dots</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_LENGTH</td>
		 *   <td>Specifies the desired average bond length</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_COLOR</td>
		 *   <td>Specifies the color of bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_LINE_WIDTH</td>
		 *   <td>Specifies the width of bond lines</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_LINE_SPACING</td>
		 *   <td>Specifies the distance between the lines of double and triple bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH</td>
		 *   <td>Specifies the width of wedge-shaped stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::STEREO_BOND_HASH_SPACING</td>
		 *   <td>Specifies the distance between the hashes of down stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH</td>
		 *   <td>Specifies the length of the lines in reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_CENTER_LINE_SPACING</td>
		 *   <td>Specifies the distance between the lines in reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH</td>
		 *   <td>Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH</td>
		 *   <td>Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_LABEL_FONT</td>
		 *   <td>Specifies the font for bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_LABEL_SIZE</td>
		 *   <td>Specifies the size of bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BOND_LABEL_MARGIN</td>
		 *   <td>Specifies the margin of free space around bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_BOND_REACTION_INFOS</td>
		 *   <td>Specifies whether or not to draw reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_BOND_QUERY_INFOS</td>
		 *   <td>Specifies whether or not to show query bond match expressions</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_STEREO_BONDS</td>
		 *   <td>Specifies whether or not to draw stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_STYLE</td>
		 *   <td>Specifies the style of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_COLOR</td>
		 *   <td>Specifies the color of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_LENGTH</td>
		 *   <td>Specifies the length of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH</td>
		 *   <td>Specifies the head length of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH</td>
		 *   <td>Specifies the head width of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH</td>
		 *   <td>Specifies the shaft width of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH</td>
		 *   <td>Specifies the line width of the reaction arrow outline</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_COMPONENT_LAYOUT</td>
		 *   <td>Specifies the style of the reaction product and reactant layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION</td>
		 *   <td>Specifies the main direction of the reaction product and reactant layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_COMPONENT_MARGIN</td>
		 *   <td>Specifies the amount of free space that is added horizontally and vertically to the bounds of a reaction component</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_REACTION_REACTANTS</td>
		 *   <td>Specifies whether or not to show the reactants of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_REACTION_AGENTS</td>
		 *   <td>Specifies whether or not to show the agents of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_REACTION_PRODUCTS</td>
		 *   <td>Specifies whether or not to show the products of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_AGENT_ALIGNMENT</td>
		 *   <td>Specifies the vertical alignment of the reaction agents relative to the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_AGENT_LAYOUT</td>
		 *   <td>Specifies the style of the reaction agent layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION</td>
		 *   <td>Specifies the main direction of the reaction agent layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR</td>
		 *   <td>Specifies the color of the '+' signs between the components of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE</td>
		 *   <td>Specifies the size of the '+' signs between the components of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH</td>
		 *   <td>Specifies the line width of the '+' signs between the components of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS</td>
		 *   <td>Specifies whether or not to draw '+' signs between the components of the reaction</td>
		 *  </tr>
		 * </table>
		 *
		 * Default values for most of the control-parameters are defined in namespace Vis::ControlParameterDefault.
		 *
		 * Supported Chem::Reaction properties:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Reaction Property</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_STYLE</td>
		 *   <td>Specifies the style of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_COLOR</td>
		 *   <td>Specifies the color of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_LENGTH</td>
		 *   <td>Specifies the length of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_HEAD_LENGTH</td>
		 *   <td>Specifies the head length of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_HEAD_WIDTH</td>
		 *   <td>Specifies the head width of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_SHAFT_WIDTH</td>
		 *   <td>Specifies the shaft width of the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::ARROW_LINE_WIDTH</td>
		 *   <td>Specifies the line width of the reaction arrow outline</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::COMPONENT_LAYOUT</td>
		 *   <td>Specifies the style of the reaction product and reactant layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION</td>
		 *   <td>Specifies the main direction of the reaction product and reactant layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::COMPONENT_MARGIN</td>
		 *   <td>Specifies the amount of free space that is added horizontally and vertically to the bounds of a reaction component</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::SHOW_REACTANTS</td>
		 *   <td>Specifies whether or not to show reactants of the reactions</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::SHOW_AGENTS</td>
		 *   <td>Specifies whether or not to show the agents of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::SHOW_PRODUCTS</td>
		 *   <td>Specifies whether or not to show the products of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::AGENT_ALIGNMENT</td>
		 *   <td>Specifies the vertical alignment of the reaction agents relative to the reaction arrow</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::AGENT_LAYOUT</td>
		 *   <td>Specifies the style of the reaction agent layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION</td>
		 *   <td>Specifies the main direction of the reaction agent layout</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::PLUS_SIGN_COLOR</td>
		 *   <td>Specifies the color of the '+' signs between the components of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::PLUS_SIGN_SIZE</td>
		 *   <td>Specifies the size of the '+' signs between the components of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH</td>
		 *   <td>Specifies the line width of the '+' signs between the components of the reaction</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ReactionProperty::SHOW_PLUS_SIGNS</td>
		 *   <td>Specifies whether or not to draw '+' signs between the components of the reaction</td>
		 *  </tr>
		 * </table>
		 *
		 * Supported Chem::MolecularGraph properties:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::MolecularGraph Property</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::ATOM_COLOR_TABLE</td>
		 *   <td>Specifies a lookup table for the atom type dependent coloring of atom labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::ATOM_COLOR</td>
		 *   <td>Specifies the color of atom labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::ATOM_LABEL_FONT</td>
		 *   <td>Specifies the font for atom element and query match expression labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::ATOM_LABEL_SIZE</td>
		 *   <td>Specifies the size of atom element and query match expression labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT</td>
		 *   <td>Specifies the font for text labels that show the value of various atomic properties</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE</td>
		 *   <td>Specifies the size of text labels that show the value of various atomic properties</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::ATOM_LABEL_MARGIN</td>
		 *   <td>Specifies the margin of free space around atom labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE</td>
		 *   <td>Specifies the size of radical electron dots</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::BOND_COLOR</td>
		 *   <td>Specifies the color of bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::BOND_LINE_WIDTH</td>
		 *   <td>Specifies the width of bond lines</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::BOND_LINE_SPACING</td>
		 *   <td>Specifies the distance between the lines of double and triple bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH</td>
		 *   <td>Specifies the width of wedge-shaped stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::STEREO_BOND_HASH_SPACING</td>
		 *   <td>Specifies the distance between the hashes of down stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH</td>
		 *   <td>Specifies the length of the lines in reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::REACTION_CENTER_LINE_SPACING</td>
		 *   <td>Specifies the distance between the lines in reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH</td>
		 *   <td>Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH</td>
		 *   <td>Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::BOND_LABEL_FONT</td>
		 *   <td>Specifies the font for bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::BOND_LABEL_SIZE</td>
		 *   <td>Specifies the size of bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::MolecularGraphProperty::BOND_LABEL_MARGIN</td>
		 *   <td>Specifies the margin of free space around bond labels</td>
		 *  </tr>
		 * </table>
		 *
		 * Supported Chem::Atom properties:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Atom Property</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::COLOR</td>
		 *   <td>Specifies the color of text labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::LABEL_FONT</td>
		 *   <td>Specifies the font for atom element and query match expression labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::LABEL_SIZE</td>
		 *   <td>Specifies the size of atom element and query match expression labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::SECONDARY_LABEL_FONT</td>
		 *   <td>Specifies the font for text labels that show the value of various atomic properties</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::SECONDARY_LABEL_SIZE</td>
		 *   <td>Specifies the size of text labels that show the value of various atomic properties</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::LABEL_MARGIN</td>
		 *   <td>Specifies the margin of free space around text labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE</td>
		 *   <td>Specifies the size of radical electron dots</td>
		 *  </tr>
		 * </table>
		 *
		 * Supported Chem::Bond properties:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Chem::Bond Property</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::COLOR</td>
		 *   <td>Specifies the color of the bond</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::LINE_WIDTH</td>
		 *   <td>Specifies the width of bond lines</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::LINE_SPACING</td>
		 *   <td>Specifies the distance between the lines of double and triple bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH</td>
		 *   <td>Specifies the width of wedge-shaped stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::STEREO_BOND_HASH_SPACING</td>
		 *   <td>Specifies the distance between the hashes of down stereo bonds</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::REACTION_CENTER_LINE_LENGTH</td>
		 *   <td>Specifies the length of the lines in reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::REACTION_CENTER_LINE_SPACING</td>
		 *   <td>Specifies the distance between the lines in reaction center marks</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH</td>
		 *   <td>Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH</td>
		 *   <td>Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::LABEL_FONT</td>
		 *   <td>Specifies the font for bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::LABEL_SIZE</td>
		 *   <td>Specifies the size of bond labels</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::BondProperty::LABEL_MARGIN</td>
		 *   <td>Specifies the margin of free space around bond labels</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_VIS_API ReactionView2D : public View2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %ReactionView2D instances.
			 */
			typedef boost::shared_ptr<ReactionView2D> SharedPointer;

			/**
			 * \brief Constructs and initializes a \c %ReactionView2D instance for the visualization of the chemical
			 *        reaction specified by \a rxn.
			 * \param rxn A pointer to the Chem::Reaction object to visualize.
			 */
			ReactionView2D(const Chem::Reaction* rxn = 0);

			/**
			 * \brief Destructor.
			 */
			~ReactionView2D();

			void render(Renderer2D& renderer);

			void setFontMetrics(FontMetrics* font_metrics);

			/**
			 * \brief Returns a pointer to the used font metrics object.
			 * \return A pointer to the used font metrics object, or \e null if none was specified.
			 */
			FontMetrics* getFontMetrics() const;
		
			/**
			 * \brief Specifies the chemical reaction to visualize.
			 *
			 * If the components of a chemical reaction or any properties have changed \e after this method has been called
			 * for a Chem::Reaction object, the method needs to be called again for the object to make the changes visible.
			 *
			 * \param rxn A pointer to the Chem::Reaction object to visualize, or \e null.
			 */
			void setReaction(const Chem::Reaction* rxn);

			/**
			 * \brief Returns a pointer to the visualized chemical reaction.
			 * \return A pointer to the visualized Chem::Reaction object, or \e null if none was specified.
			 */
			const Chem::Reaction* getReaction() const;

			void getModelBounds(Rectangle2D& bounds);

		private:
			ReactionView2D(const ReactionView2D&);

			ReactionView2D& operator=(const ReactionView2D&);

			void paintBackground(Renderer2D&) const;

			void renderComponents(Renderer2D&) const;
			void renderGraphicsPrimitives(Renderer2D&) const;

			void init();

			void initComponentViews();
			void initComponentBoundsTable();
			void layoutReaction();
			void calcOutputTransforms();
			void initComponentViewViewports();
			void createPlusSignPrimitives();
			void createArrowPrimitives();

			void createStdReactionArrow(bool);

			void layoutComponents(unsigned int, std::size_t, std::size_t);
			void createPackedComponentLayout(unsigned int, std::size_t, std::size_t);
			void createLinearComponentLayout(unsigned int, std::size_t, std::size_t);
			void createHLinearComponentLayout(unsigned int, std::size_t, std::size_t);
			void createVLinearComponentLayout(unsigned int, std::size_t, std::size_t);

			unsigned int getComponentLayout(unsigned int) const;
			unsigned int getComponentLayoutDirection(unsigned int) const;

			void shiftComponentPositions(std::size_t, std::size_t, const Math::Vector2D&);
			void shiftPlusSignPositions(std::size_t, std::size_t, const Math::Vector2D&);

			void calcArrowDimensions();
			void calcPlusSignDimensions();

			void freeComponentViews();
			void freeGraphicsPrimitives();

			void initArrowStyle();
			void initArrowLength();

			const Color& getArrowColor() const;
			const SizeSpecification& getArrowHeadLength() const;
			const SizeSpecification& getArrowHeadWidth() const;
			const SizeSpecification& getArrowShaftWidth() const;
			const SizeSpecification& getArrowLineWidth() const;

			void initComponentLayout();
			void initComponentLayoutDirection();
			void initComponentMargin();
			void initComponentVisibility();
			void initAgentAlignment();
			void initAgentLayout();
			void initAgentLayoutDirection();

			const Color& getPlusSignColor() const;
			const SizeSpecification& getPlusSignSize() const;
			const SizeSpecification& getPlusSignLineWidth() const;

			void initPlusSignVisibility();

			StructureView2D* allocComponentView(const Chem::Molecule&);
			PolygonPrimitive2D* allocPolygonPrimitive();
			LineSegmentListPrimitive2D* allocLineSegListPrimitive();

			typedef std::vector<StructureView2D*> ComponentViewList;
			typedef std::vector<const GraphicsPrimitive2D*> GraphicsPrimitiveList;
			typedef std::map<const Chem::MolecularGraph*, Rectangle2D> ComponentBoundsMap;
			typedef std::vector<Math::Vector2D> Vector2DArray;
			typedef Util::ObjectStack<StructureView2D> ComponentViewCache;
			typedef Util::ObjectStack<PolygonPrimitive2D> PolygonPrimitiveCache;
			typedef Util::ObjectStack<LineSegmentListPrimitive2D> LineSegListPrimitiveCache;
			typedef std::auto_ptr<ReactionView2DParameters> ReactionView2DParametersPtr;

			const Chem::Reaction*          reaction;
			ReactionView2DParametersPtr    parameters;
			FontMetrics*                   fontMetrics;
			ComponentViewList              componentViews;
			GraphicsPrimitiveList          drawList;
			Rectangle2D                    totalComponentBounds;
			Rectangle2D                    totalReactionBounds;
			ComponentBoundsMap             componentBounds;
			Vector2DArray                  componentPositions;
			Vector2DArray                  plusSignPositions;
			Math::Vector2D                 arrowPosition;
			double                         unscaledArrowLength;
			double                         unscaledArrowHeadLength;
			double                         unscaledArrowHeadWidth;
			double                         unscaledArrowShaftWidth;
			double                         unscaledArrowLineWidth;
			double                         maxUnscaledArrowWidth;
			double                         unscaledPlusSignSize;
			double                         unscaledPlusSignLineWidth;
			double                         outputScalingFactor;
			Math::Vector2D                 outputTranslation;
			unsigned int                   arrowStyle;
			SizeSpecification              arrowLength;
			unsigned int                   componentLayout;
			unsigned int                   componentLayoutDirection;
			SizeSpecification              componentMargin;
			unsigned int                   agentAlignment;		
			unsigned int                   agentLayout;
			unsigned int                   agentLayoutDirection;
			bool                           showReactants;
			bool                           showAgents;
			bool                           showProducts;
			bool                           plusSignsVisible;
			bool                           reactionChanged;
			bool                           fontMetricsChanged;
			ComponentViewCache             compViewCache;
			PolygonPrimitiveCache          polygonCache;
			LineSegListPrimitiveCache      lineSegListCache;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_REACTIONVIEW2D_HPP
