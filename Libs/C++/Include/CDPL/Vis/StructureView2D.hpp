/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureView2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::StructureView2D.
 */

#ifndef CDPL_VIS_STRUCTUREVIEW2D_HPP
#define CDPL_VIS_STRUCTUREVIEW2D_HPP

#include <vector>
#include <memory>
#include <string>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/View2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/LinePrimitive2D.hpp"
#include "CDPL/Vis/PolylinePrimitive2D.hpp"
#include "CDPL/Vis/PolygonPrimitive2D.hpp"
#include "CDPL/Vis/LineSegmentListPrimitive2D.hpp"
#include "CDPL/Vis/PointListPrimitive2D.hpp"
#include "CDPL/Vis/TextLabelPrimitive2D.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

	namespace Base
	{

		class PropertyContainer;
	}

	namespace Chem
	{

		class MolecularGraph;
		class Fragment;
		class Atom;
		class Bond;
	}

	namespace Vis
	{

		class FontMetrics;
		class StructureView2DParameters;

		/**
		 * \addtogroup CDPL_VIS_STRUCTURE_VISUALIZATION
		 * @{
		 */

		/**
		 * \brief Implements the 2D visualization of chemical structures.
		 *
		 * \c %StructureView2D visualizes chemical structures in the form of 2D structure diagrams (also known
		 * as skeletal formulas [\ref WSKF] or structural formulas [\ref WSTF]) that allow for an easy perception
		 * of important chemical characteristics like constitution, connectivity and stereochemistry.
		 *
		 * Graphical details of the generated structure diagrams (colors, fonts, line-widths etc.) are configurable on a
		 * \c %StructureView2D instance level by control-parameters and on a visualized data object level
		 * by setting appropriate Chem::Atom, Chem::Bond or Chem::MolecularGraph properties. Properties of the
		 * visualized data objects have a higher priority than equivalent control-parameters of the \c %StructureView2D
		 * instance and properties of Chem::Atom or Chem::Bond objects override corresponding properties of the
		 * parent Chem::MolecularGraph instance.
		 *
		 * \c %StructureView2D supports the following control-parameters:
		 *
		 * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::VIEWPORT</td>
		 *   <td>Specifies a rectangular viewport area which constrains the location and size of the generated structure diagram</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::SIZE_ADJUSTMENT</td>
		 *   <td>Specifies how to adjust the size of the structure diagram relative to the available viewport area</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::ALIGNMENT</td>
		 *   <td>Specifies the alignment of the structure diagram within the viewport area</td>
		 *  </tr>
		 *  <tr>
		 *   <td>Vis::ControlParameter::BACKGROUND_COLOR</td>
		 *   <td>Specifies the backround color of the structure diagram</td>
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
		 *   <td>Specifies the distance between lines in reaction center marks</td>
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
		 * </table>
		 *
		 * Default values for most of the control-parameters are defined in namespace Vis::ControlParameterDefault.
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
		 *   <td>Specifies the margin of free space around atom labels</td>
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
		class CDPL_VIS_API StructureView2D : public View2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %StructureView2D instances.
			 */
			typedef boost::shared_ptr<StructureView2D> SharedPointer;
			
			/**
			 * \brief Constructs and initializes a \c %StructureView2D instance for the visualization of the chemical
			 *        structure specified by \a molgraph.
			 * \param molgraph A pointer to the Chem::MolecularGraph object to visualize.
			 */
			StructureView2D(const Chem::MolecularGraph* molgraph = 0);

			/**
			 * \brief Destructor.
			 */
			~StructureView2D();

			void render(Renderer2D& renderer);

			void setFontMetrics(FontMetrics* font_metrics);

			/**
			 * \brief Returns a pointer to the used font metrics object.
			 * \return A pointer to the used font metrics object, or \e null if none was specified.
			 */
			FontMetrics* getFontMetrics() const;

			/**
			 * \brief Specifies the chemical structure to visualize.
			 *
			 * If the chemical structure or a property has changed \e after this method has been called
			 * for a Chem::MolecularGraph object, the method needs to be called again for the object
			 * to make the changes visible.
			 *
			 * \param molgraph A pointer to the Chem::MolecularGraph object to visualize, or \e null.
			 */
			void setStructure(const Chem::MolecularGraph* molgraph);
			
			/**
			 * \brief Returns a pointer to the visualized chemical structure.
			 * \return A pointer to the visualized Chem::MolecularGraph object, or \e null if none was specified.
			 */
			const Chem::MolecularGraph* getStructure() const;

			/**
			 * \brief Calculates the bounds of the rendered structure in output space.
			 * \param bounds The object storing the calculated bounding box.
			 */
			void getModelBounds(Rectangle2D& bounds);

			/**
			 * \brief Add a custom graphics primitive that gets rendered along the structure diagram.
			 * \param anchor_pos The anchor position of the primitive in the atom 2D coordinates space of the structure.
			 * \param prim The graphics primitive to render.
			 * \param alignment The alignment of the primitive relative to the anchor position.
			 * \param front \c true if the primitive shall be rendered after the structure, and \false if before.
			 * \note A copy of the specified graphics primitive gets stored and thus can be reused/changed after the call.
			 */
			void addGraphicsPrimitive(const Math::Vector2D& anchor_pos, const GraphicsPrimitive2D& prim, unsigned int alignment, bool front);
	
			/**
			 * \brief Add a custom graphics primitive that gets rendered along the structure diagram.
			 * \param anchor_atom Specifies an atom of the structure that serves as the anchor position of the primitive.
			 * \param prim The graphics primitive to render.
			 * \param alignment The alignment of the primitive relative to the anchor atom position.
			 * \param front \c true if the primitive shall be rendered after the structure, and \false if before.
			 * \note A copy of the specified graphics primitive gets stored and thus can be reused/changed after the call.
			 */
			void addGraphicsPrimitive(const Chem::Atom& anchor_atom, const GraphicsPrimitive2D& prim, unsigned int alignment, bool front);
	
			/**
			 * \brief Add a custom graphics primitive that gets rendered along the structure diagram.
			 * \param anchor_atoms Specifies a group of atoms of the structure whose centroid serves as the anchor position of the primitive.
			 * \param prim The graphics primitive to render.
			 * \param alignment The alignment of the primitive relative to the centroid of the anchor atom group.
			 * \param front \c true if the primitive shall be rendered after the structure, and \false if before.
			 * \note A copy of the specified graphics primitive gets stored and thus can be reused/changed after the call.
			 */
			void addGraphicsPrimitive(const Chem::Fragment& anchor_atoms, const GraphicsPrimitive2D& prim, unsigned int alignment, bool front);

			/**
			 * \brief Removes all previously added custom graphics primitives.
			 */
			void clearGraphicsPrimitives();

		private:
			class CustomGraphicsData;
			friend class ReactionView2D;

			typedef boost::shared_ptr<CustomGraphicsData> CustomGraphicsDataPtr;
			typedef std::vector<CustomGraphicsDataPtr> CustomGraphicsDataList;

			StructureView2D(const StructureView2D&);
			StructureView2D(bool);

			StructureView2D& operator=(const StructureView2D&);

			void paintBackground(Renderer2D&) const;

			void renderGraphicsPrimitives(Renderer2D&) const;

			void init();

			void initTextLabelBounds();

			void createAtomPrimitives();
			void createAtomPrimitives(const Chem::Atom&);
			double createAtomQueryInfoLabelPrimitive(const Chem::Atom&, const std::string&, Rectangle2D&);
			void createAtomQueryInfoLabelPrimitive(const Chem::Atom&, const std::string&, double, Rectangle2D&);
			double createAtomSymbolLabelPrimitive(const Chem::Atom&, const std::string&, Rectangle2D&);
			void createRadicalElectronPrimitives(const Chem::Atom&, std::size_t, Rectangle2D&);
			void createAtomIsotopeLabelPrimitive(const Chem::Atom&, std::size_t, Rectangle2D&);
			void createAtomChargeLabelPrimitive(const Chem::Atom&, long, std::size_t, Rectangle2D&);
			void createAtomHCountLabelPrimitives(const Chem::Atom&, std::size_t, double, Rectangle2D&);
			void createAtomMappingLabelPrimitive(const Chem::Atom&, std::size_t, const Rectangle2D&);

			void createBondPrimitives();

			void createBondLabelPrimitives(const Chem::Bond&, const Line2D&, int);
			double createBondRxnInfoLabelPrimitive(const Chem::Bond&, const Line2D&, int);
			void createBondQueryInfoLabelPrimitive(const Chem::Bond&, const Line2D&, int, double);

			void createUndefOrderBondPrimitives(const Chem::Bond&, const Line2D&);
			void createSingleBondPrimitives(const Chem::Bond&, const Line2D&);
			void createUpSingleBondPrimitives(const Chem::Bond&, const Line2D&, bool);
			void extendUpBondWedgeSides(const Chem::Bond&, const Chem::Atom&, Line2D&, Line2D&, bool, bool) const;
			void extendWedgeSideToNeighborBonds(Line2D&, const Chem::Bond&, const Chem::Atom&, bool) const;
			void createDownSingleBondPrimitives(const Chem::Bond&, const Line2D&, bool);
			void createEitherSingleBondPrimitives(const Chem::Bond&, const Line2D&, bool);
			void createPlainSingleBondPrimitives(const Chem::Bond&, const Line2D&);

			void createDoubleBondPrimitives(const Chem::Bond&, const Line2D&, int);
			void createAsymDoubleBondPrimitives(const Chem::Bond&, bool, const Line2D&, int);
			void createSymDoubleBondPrimitives(const Chem::Bond&, bool, const Line2D&);

			void createTripleBondPrimitives(const Chem::Bond&, const Line2D&);

			void createBondRxnCenterPrimitives(const Chem::Bond&, const Line2D&, int);

			int getBondAsymmetryShiftDirection(const Chem::Bond&) const;

			bool trimLine(Line2D&, double, bool) const;

			bool clipLineAgainstAtomBounds(Line2D&, const Chem::Bond&) const;
			bool clipLineAgainstAtomBounds(Line2D&, std::size_t, bool) const;

			void extendBondLineToNeighborBonds(Line2D&, const Chem::Bond&, const Chem::Atom&, bool) const;
			void clipLineAgainstNeighborBonds(Line2D&, const Chem::Bond&, const Chem::Atom&, bool) const;
			void clipLineAgainstBondLabel(LinePrimitive2D*, std::size_t);

			std::size_t getHydrogenCount(const Chem::Atom&) const;

			double calcCongestionFactor(const Rectangle2D&, const Base::PropertyContainer&) const;

			double calcBondAngle(const Chem::Bond&, const Chem::Bond&) const;
			double calcInputBondLength(const Chem::Bond&) const;

			void prepareStructureData();
			void initInputAtomPosTable();

			void calcViewTransforms();

			double calcAvgInputBondLength() const;

			void calcStdBondLengthScalingFactor();
			void calcViewportAdjustmentScalingFactor();

			void calcInputStructureBounds();
			void calcOutputStructureBounds();
			void calcOutputAtomCoords();

			void initOutputBondLineTable();

			unsigned int getBondStereoFlag(const Chem::Bond&, const Chem::MolecularGraph&) const;
			std::size_t getBondOrder(const Chem::Bond& bond) const;

			void setHasAtomCoordsFlag();

			double getLineWidth(const Chem::Bond&) const;
			double getRxnCenterLineLength(const Chem::Bond&) const;
			double getRxnCenterLineSpacing(const Chem::Bond&) const;
			double getDoubleBondTrimLength(const Chem::Bond&) const;
			double getTripleBondTrimLength(const Chem::Bond&) const;
			double getLineSpacing(const Chem::Bond&) const;
			double getWedgeWidth(const Chem::Bond&) const;
			double getHashSpacing(const Chem::Bond&) const;
			double getLabelSize(const Chem::Bond&) const;

			const Color& getColor(const Chem::Bond&) const;
			const Font& getLabelFont(const Chem::Bond&) const;
			const SizeSpecification& getLabelSizeSpec(const Chem::Bond&) const;
			const SizeSpecification& getLabelMarginSpec(const Chem::Bond&) const;

			void setupLabelMargin(const Chem::Bond&);
			void setupPen(const Chem::Bond&);
			void setupLabelFont(const Chem::Bond&);

			double getLabelSize(const Chem::Atom&) const;
			double getSecondaryLabelSize(const Chem::Atom&) const;
			double getElectronDotSize(const Chem::Atom&) const;

			const Color& getColor(const Chem::Atom&) const;
			const Font& getLabelFont(const Chem::Atom&) const;
			const Font& getSecondaryLabelFont(const Chem::Atom&) const;
			const SizeSpecification& getLabelSizeSpec(const Chem::Atom&) const;
			const SizeSpecification& getSecondaryLabelSizeSpec(const Chem::Atom&) const;
			const SizeSpecification& getLabelMarginSpec(const Chem::Atom&) const;
			const SizeSpecification& getElectronDotSizeSpec(const Chem::Atom&) const;

			void setupLabelMargin(const Chem::Atom&);
			void setupPen(const Chem::Atom&);
			void setupLabelFont(const Chem::Atom&);
			void setupSecondaryLabelFont(const Chem::Atom&);
		
			double calcOutputSize(const Chem::Bond&, const SizeSpecification&) const;
			double calcOutputSize(const Chem::Atom&, const SizeSpecification&) const;

			double calcOutputSize(const SizeSpecification&) const;
			double calcOutputSize(double, const SizeSpecification&) const;

			void freeGraphicsPrimitives();

			LinePrimitive2D* allocLinePrimitive(bool = true);
			PolylinePrimitive2D* allocPolylinePrimitive();
			PolygonPrimitive2D* allocPolygonPrimitive();
			LineSegmentListPrimitive2D* allocLineSegListPrimitive();
			PointListPrimitive2D* allocPointListPrimitive();
			TextLabelPrimitive2D* allocTextLabelPrimitive();

			void addCustomGraphics(CustomGraphicsData* gfx_data, bool front);
			void renderCustomGraphics(Renderer2D& renderer, const CustomGraphicsDataList& gfx_data) const;

			class CustomGraphicsData
			{

			public:
				CustomGraphicsData(const Math::Vector2D& anchor_pos, const GraphicsPrimitive2D& prim, unsigned int alignment);

				CustomGraphicsData(const Chem::Atom& anchor_atom, const GraphicsPrimitive2D& prim, unsigned int alignment);

				CustomGraphicsData(const Chem::Fragment& anchor_atoms, const GraphicsPrimitive2D& prim, unsigned int alignment);

				const Rectangle2D& calcBounds(const Math::Vector2DArray& coords, const Chem::MolecularGraph& structure, FontMetrics* font_metrics);

				const Rectangle2D& getBounds() const;

				const Math::Vector2D& getTranslation() const;

				const GraphicsPrimitive2D& getPrimitive() const;

			private:
				typedef std::vector<const Chem::Atom*>   AtomList;

				Math::Vector2D                     anchorPos;
				AtomList                           anchorAtoms;
				GraphicsPrimitive2D::SharedPointer primitive;
				unsigned int                       alignment;
				Math::Vector2D                     translation;
				Rectangle2D                        bounds;
			};

			typedef std::vector<const GraphicsPrimitive2D*> GraphicsPrimitiveList;
			typedef std::vector<Rectangle2D> RectangleList;
			typedef std::vector<RectangleList> RectangleListTable;
			typedef std::vector<Line2D> BondLineTable;

			typedef std::vector<LinePrimitive2D::SharedPointer> AllocLinePrimitiveList;
			typedef std::vector<PolylinePrimitive2D::SharedPointer> AllocPolylinePrimitiveList;
			typedef std::vector<PolygonPrimitive2D::SharedPointer> AllocPolygonPrimitiveList;
			typedef std::vector<LineSegmentListPrimitive2D::SharedPointer> AllocLineSegListPrimitiveList;
			typedef std::vector<PointListPrimitive2D::SharedPointer> AllocPointListPrimitiveList;
			typedef std::vector<TextLabelPrimitive2D::SharedPointer> AllocTextLabelPrimitiveList;

			typedef std::auto_ptr<StructureView2DParameters> StructureView2DParametersPtr;
			typedef std::auto_ptr<Chem::Fragment> FragmentPtr;

			StructureView2DParametersPtr       parameters;
			const Chem::MolecularGraph*        structure;
			const Chem::MolecularGraph*        origStructure;
			FragmentPtr                        hDepleteStructure;
			FontMetrics*                       fontMetrics;
			Rectangle2D                        inputStructureBounds;
			Rectangle2D                        outputStructureBounds;
			Util::UIArray                      calcBondStereoFlags;
			Math::Vector2DArray                calcInputAtomCoords;
			Math::Vector2DArray                inputAtomCoords;
			Math::Vector2DArray                outputAtomCoords;
			BondLineTable                      outputBondLines;
			RectangleListTable                 atomLabelBounds;
			RectangleList                      bondLabelBounds;
			GraphicsPrimitiveList              drawList;
			double                             avgInputBondLength;
			double                             stdBondLengthScalingFactor;
			double                             viewportAdjustmentScalingFactor;
			double                             viewScalingFactor;
			Math::Vector2D                     viewTranslations[2];
			bool                               structureChanged;
			bool                               fontMetricsChanged;
			bool                               customGraphicsChanged;
			Pen                                activePen;
			Font                               activeLabelFont;
			Font                               activeSecondaryLabelFont;
			double                             activeLabelMargin;
			AllocLinePrimitiveList             allocLinePrimitives;
			AllocPolylinePrimitiveList         allocPolylinePrimitives;
			AllocPolygonPrimitiveList          allocPolygonPrimitives;
			AllocLineSegListPrimitiveList      allocLineSegListPrimitives;
			AllocPointListPrimitiveList        allocPointListPrimitives;
			AllocTextLabelPrimitiveList        allocTextLabelPrimitives;
			CustomGraphicsDataList             backCustomGraphics;
			CustomGraphicsDataList             frontCustomGraphics;
			std::size_t                        freeLinePrimitiveIdx;
			std::size_t                        freePolylinePrimitiveIdx;
			std::size_t                        freePolygonPrimitiveIdx;
			std::size_t                        freeLineSegListPrimitiveIdx;
			std::size_t                        freePointListPrimitiveIdx;
			std::size_t                        freeTextLabelPrimitiveIdx;
			bool                               reactionContext;
			bool                               hasAtomCoords;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_STRUCTUREVIEW2D_HPP
