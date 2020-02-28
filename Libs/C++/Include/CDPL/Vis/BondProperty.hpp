/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::BondProperty.
 */

#ifndef CDPL_VIS_BONDPROPERTY_HPP
#define CDPL_VIS_BONDPROPERTY_HPP

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
		 * \addtogroup CDPL_VIS_BOND_PROPERTIES
		 * @{
		 */

		/**
		 * \brief Provides keys for built-in Chem::Bond properties.
		 */
		namespace BondProperty
		{

			/**
			 * \brief Specifies the color of the bond.
			 *
			 * The color specified by this property takes precedence over the colors
			 * specified by Vis::ControlParameter::BOND_COLOR and Vis::MolecularGraphProperty::BOND_COLOR.
			 *
			 * \valuetype Vis::Color
			 */
			extern CDPL_VIS_API const Base::LookupKey COLOR;

			/**
			 * \brief Specifies the width of bond lines.
			 *
			 * The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
			 * the line width will follow the size change of the chemical structure during bond length normalization. If output-scaling is
			 * enabled, the line width grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The line width specified by this property takes precedence over the widths specified by Vis::ControlParameter::BOND_LINE_WIDTH
			 * and Vis::MolecularGraphProperty::BOND_LINE_WIDTH.
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey LINE_WIDTH;

			/**
			 * \brief Specifies the distance between the lines of double and triple bonds.
			 *
			 * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
			 * the line distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is
			 * enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The line spacing specified by this property takes precedence over the distances specified by Vis::ControlParameter::BOND_LINE_SPACING
			 * and Vis::MolecularGraphProperty::BOND_LINE_SPACING.	
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey LINE_SPACING;

			/**
			 * \brief Specifies the width of wedge-shaped stereo bonds.
			 *
			 * The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the
			 * wedge width will follow the size change of the chemical structure during bond length normalization. If output-scaling is
			 * enabled, the wedge width grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The wedge width specified by this property takes precedence over the width specified by Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH
			 * or Vis::MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH.
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey STEREO_BOND_WEDGE_WIDTH;

			/**
			 * \brief Specifies the distance between the hashes of down stereo bonds.
			 *
			 * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
			 * the hash distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is
			 * enabled, the hash distance grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The hash spacing specified by this property takes precedence over the distances specified by
			 * Vis::ControlParameter::STEREO_BOND_HASH_SPACING and Vis::MolecularGraphProperty::STEREO_BOND_HASH_SPACING.	
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey STEREO_BOND_HASH_SPACING;

			/**
			 * \brief Specifies the length of the lines in reaction center marks. 
			 *
			 * The length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
			 * the line length will follow the size change of the chemical structure during bond length normalization. If output-scaling is
			 * enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The line length specified by this property takes precedence over the length specified by 
			 * Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH or Vis::MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH.				
			 *
			 * \valuetype Vis::SizeSpecification
			 * \see Vis::ControlParameter::SHOW_BOND_REACTION_INFOS
			 */
			extern CDPL_VIS_API const Base::LookupKey REACTION_CENTER_LINE_LENGTH;
	
			/**
			 * \brief Specifies the distance between the lines in reaction center marks. 
			 *
			 * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
			 * the line distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is
			 * enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The line spacing specified by this property takes precedence over the spacing specified by 
			 * Vis::ControlParameter::REACTION_CENTER_LINE_SPACING or Vis::MolecularGraphProperty::REACTION_CENTER_LINE_SPACING.				
			 *
			 * \valuetype Vis::SizeSpecification
			 * \see Vis::ControlParameter::SHOW_BOND_REACTION_INFOS
			 */
			extern CDPL_VIS_API const Base::LookupKey REACTION_CENTER_LINE_SPACING;
	
			/**
			 * \brief Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each
			 *        line end.
			 *
			 * The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
			 * enabled, the trim length will follow the size change of the chemical structure during bond length normalization. If
			 * output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The trim length specified by this property takes precedence over the lengths specified by 
			 * Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH and Vis::MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH.						
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey DOUBLE_BOND_TRIM_LENGTH;

			/**
			 * \brief Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end.
			 *
			 * The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is
			 * enabled, the trim length will follow the size change of the chemical structure during bond length normalization. If
			 * output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
			 * The trim length specified by this property takes precedence over the lengths specified by 
			 * Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH and Vis::MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH.		
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey TRIPLE_BOND_TRIM_LENGTH;

			/**
			 * \brief Specifies the font for bond labels.
			 *
			 * The font specified by this property takes precedence over the fonts specified by Vis::ControlParameter::BOND_LABEL_FONT and
			 * Vis::MolecularGraphProperty::BOND_LABEL_FONT.		
			 *
			 * \valuetype Vis::Font
			 */
			extern CDPL_VIS_API const Base::LookupKey LABEL_FONT;

			/**
			 * \brief Specifies the size of bond labels.
			 *
			 * The font size has to be specified as an absolute value. If input-scaling is enabled, the font size will follow the size change
			 * of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change
			 * of the chemical structure during viewport size adjustment. The font size specified by this property takes precedence over the sizes
			 * specified by Vis::ControlParameter::BOND_LABEL_SIZE and Vis::MolecularGraphProperty::BOND_LABEL_SIZE.	
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey LABEL_SIZE;
	
			/**
			 * \brief Specifies the margin of free space around bond labels.
			 *
			 * The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by
			 * Vis::ControlParameter::BOND_LABEL_SIZE, Vis::MolecularGraphProperty::BOND_LABEL_SIZE or Vis::BondProperty::LABEL_SIZE.
			 * If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during
			 * bond length normalization. If output-scaling is enabled, the margin will follow the size change of the chemical
			 * structure during viewport size adjustment. The margin specified by this property takes precedence over the margins
			 * specified by Vis::ControlParameter::BOND_LABEL_MARGIN and Vis::MolecularGraphProperty::BOND_LABEL_MARGIN.	
			 *
			 * \valuetype Vis::SizeSpecification
			 */
			extern CDPL_VIS_API const Base::LookupKey LABEL_MARGIN;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_BONDPROPERTY_HPP
