/* 
 * MolecularGraphProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::MolecularGraphProperty.
 */

#ifndef CDPL_VIS_MOLECULARGRAPHPROPERTY_HPP
#define CDPL_VIS_MOLECULARGRAPHPROPERTY_HPP

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
         * \brief Provides keys for built-in Chem::MolecularGraph properties.
         */
        namespace MolecularGraphProperty
        {

            /**
             * \brief Specifies a lookup table for the atom type dependent coloring of atom labels.
             *
             * If the color for a particular atom type is missing, the color specified by Vis::ControlParameter::ATOM_COLOR or
             * Vis::MolecularGraphProperty::ATOM_COLOR will be used instead. The specified color takes precedence over the table
             * specified by the parameter Vis::ControlParameter::ATOM_COLOR_TABLE.
             *
             * \valuetype Vis::ColorTable::SharedPointer
             * \note The color table will only be considered if the Chem::Atom property Vis::AtomProperty::COLOR has not been set.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_COLOR_TABLE;

            /**
             * \brief Specifies the color of atom labels.
             *
             * The specified color takes precedence over the color specified by the parameter Vis::ControlParameter::ATOM_COLOR. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::COLOR.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_COLOR;

            /**
             * \brief Specifies the font for atom element and query match expression labels.
             *
             * The specified font takes precedence over the font specified by the parameter Vis::ControlParameter::ATOM_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::LABEL_FONT.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_LABEL_FONT;

            /**
             * \brief Specifies the size of atom element and query match expression labels.
             *
             * The font size has to be specified as an absolute value. If input-scaling is enabled, the font size will follow the size
             * change of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will
             * grow/shrink with the size of the chemical structure during viewport size adjustment. The specified size takes precedence
             * over the size specified by the parameter Vis::ControlParameter::ATOM_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::LABEL_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_LABEL_SIZE;

            /**
             * \brief Specifies the font for text labels that show the value of various atomic properties.
             *
             * The specified font takes precedence over the
             * font specified by the parameter Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::SECONDARY_LABEL_FONT.
             */
            extern CDPL_VIS_API const Base::LookupKey SECONDARY_ATOM_LABEL_FONT;

            /**
             * \brief Specifies the size of text labels that show the value of various atomic properties.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. The specified size takes precedence over the size specified by the parameter 
             * Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::SECONDARY_LABEL_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey SECONDARY_ATOM_LABEL_SIZE;

            /**
             * \brief Specifies the margin of free space around atom labels.
             *
             * The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the label margin will follow the size change of the chemical structure during
             * viewport size adjustment. The specified margin takes precedence over the margin specified by the parameter
             * Vis::ControlParameter::ATOM_LABEL_MARGIN. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::LABEL_MARGIN.
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_LABEL_MARGIN;

            /**
             * \brief Specifies the size of radical electron dots.
             *
             * The dot size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the dot diameter will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the diameter will follow the size change of the chemical structure during
             * viewport size adjustment. The specified size takes precedence over the size specified by the parameter 
             * Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey RADICAL_ELECTRON_DOT_SIZE;

            /**
             * \brief Specifies the font used for atom configuration descriptor text labels.
             *
             * The specified font takes precedence over the
             * font specified by the parameter Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::CONFIGURATION_LABEL_FONT.
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
             * viewport size adjustment. The specified size takes precedence over the size specified by the parameter 
             * Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::CONFIGURATION_LABEL_SIZE.
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Specifies the color used for atom configuration descriptor text labels.
             *
             * The specified color takes precedence over the
             * color specified by the parameter Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::CONFIGURATION_LABEL_COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CONFIGURATION_LABEL_COLOR;

            /**
             * \brief Specifies the font used for custom text labels.
             *
             * The specified font takes precedence over the
             * font specified by the parameter Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::CUSTOM_LABEL_FONT.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CUSTOM_LABEL_FONT;
            
            /**
             * \brief Specifies the size of custom text labels.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::MolecularGraphProperty::ATOM_LABEL_SIZE or Vis::AtomProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. The specified size takes precedence over the size specified by the parameter 
             * Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::CUSTOM_LABEL_SIZE.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CUSTOM_LABEL_SIZE;

            /**
             * \brief Specifies the color used for custom text labels.
             *
             * The specified color takes precedence over the
             * color specified by the parameter Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Atom property Vis::AtomProperty::CUSTOM_LABEL_COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey ATOM_CUSTOM_LABEL_COLOR;
  
            /**
             * \brief Specifies the color of bonds.
             *
             * The specified color takes precedence over the color specified by the parameter Vis::ControlParameter::BOND_COLOR. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::COLOR.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_COLOR;

            /**
             * \brief Specifies the width of bond lines.
             *
             * The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the line width will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the line width grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * The specified line width takes precedence over the width specified by the parameter Vis::ControlParameter::BOND_LINE_WIDTH. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::LINE_WIDTH.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LINE_WIDTH;

            /**
             * \brief Specifies the distance between the lines of double and triple bonds.
             *
             * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the line distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified line
             * spacing takes precedence over the distance specified by the parameter Vis::ControlParameter::BOND_LINE_SPACING. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::LINE_SPACING.    
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LINE_SPACING;

            /**
             * \brief Specifies the width of wedge-shaped stereo bonds.
             *
             * The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the wedge width will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the wedge width grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * The specified wedge width takes precedence over the width specified by the parameter Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH.            
             */
            extern CDPL_VIS_API const Base::LookupKey STEREO_BOND_WEDGE_WIDTH;

            /**
             * \brief Specifies the distance between the hashes of down stereo bonds.
             *
             * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the hash distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the hash distance grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * The specified hash spacing takes precedence over the spacing specified by the parameter Vis::ControlParameter::STEREO_BOND_HASH_SPACING. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::STEREO_BOND_HASH_SPACING.    
             */
            extern CDPL_VIS_API const Base::LookupKey STEREO_BOND_HASH_SPACING;

            /**
             * \brief Specifies the length of the lines in reaction center marks.
             *
             * The length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the line length will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment.
             * The specified line length takes precedence over the length specified by the parameter 
             * Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::REACTION_CENTER_LINE_LENGTH.        
             * \see Vis::ControlParameter::SHOW_BOND_REACTION_INFOS
             */
            extern CDPL_VIS_API const Base::LookupKey REACTION_CENTER_LINE_LENGTH;

            /**
             * \brief Specifies the distance between the lines in reaction center marks. 
             *
             * The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the line distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified line
             * spacing takes precedence over the spacing specified by the parameter Vis::ControlParameter::REACTION_CENTER_LINE_SPACING. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::REACTION_CENTER_LINE_SPACING.    
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
             * The specified trim length takes precedence over the length specified by the parameter Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH.        
             */
            extern CDPL_VIS_API const Base::LookupKey DOUBLE_BOND_TRIM_LENGTH;

            /**
             * \brief Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end.
             *
             * The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled,
             * the trim length will follow the size change of the chemical structure during bond length normalization. If output-scaling is
             * enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified trim length
             * takes precedence over the length specified by the parameter Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH.            
             */
            extern CDPL_VIS_API const Base::LookupKey TRIPLE_BOND_TRIM_LENGTH;

            /**
             * \brief Specifies the font for bond labels.
             *
             * The specified font takes precedence over the font specified by the parameter Vis::ControlParameter::BOND_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::LABEL_FONT.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LABEL_FONT;

            /**
             * \brief Specifies the size of bond labels.
             *
             * The font size has to be specified as an absolute value. If input-scaling is enabled, the font size will follow the size change
             * of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change
             * of the chemical structure during viewport size adjustment. The specified font size takes precedence over the size specified by the
             * parameter Vis::ControlParameter::BOND_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::LABEL_SIZE.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LABEL_SIZE;

            /**
             * \brief Specifies the margin of free space around bond labels.
             *
             * The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::BOND_LABEL_SIZE, Vis::MolecularGraphProperty::BOND_LABEL_SIZE or Vis::BondProperty::LABEL_SIZE.
             * If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during
             * bond length normalization. If output-scaling is enabled, the label margin will follow the size change of the chemical
             * structure during viewport size adjustment. The specified margin takes precedence over the margin specified by the
             * parameter Vis::ControlParameter::BOND_LABEL_MARGIN. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::LABEL_MARGIN.
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_LABEL_MARGIN;

            /**
             * \brief Specifies the font used for bond configuration descriptor text labels.
             *
             * The specified font takes precedence over the
             * font specified by the parameter Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::CONFIGURATION_LABEL_FONT.
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
             * viewport size adjustment. The specified size takes precedence over the size specified by the parameter 
             * Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::CONFIGURATION_LABEL_SIZE.
             * \since 1.1
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Specifies the color used for bond configuration descriptor text labels.
             *
             * The specified color takes precedence over the
             * color specified by the parameter Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::CONFIGURATION_LABEL_COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CONFIGURATION_LABEL_COLOR;

            /**
             * \brief Specifies the font used for custom text labels.
             *
             * The specified font takes precedence over the
             * font specified by the parameter Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT. 
             *
             * \valuetype Vis::Font
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::CUSTOM_LABEL_FONT.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CUSTOM_LABEL_FONT;
            
            /**
             * \brief Specifies the size of custom text labels.
             *
             * The size can either be specified as an absolute value or as a scaling factor for the primary label size given by
             * Vis::ControlParameter::BOND_LABEL_SIZE, Vis::MolecularGraphProperty::BOND_LABEL_SIZE or Vis::BondProperty::LABEL_SIZE.
             * If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length
             * normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during 
             * viewport size adjustment. The specified size takes precedence over the size specified by the parameter 
             * Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE. 
             *
             * \valuetype Vis::SizeSpecification
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::CUSTOM_LABEL_SIZE.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CUSTOM_LABEL_SIZE;

            /**
             * \brief Specifies the color used for custom text labels.
             *
             * The specified color takes precedence over the
             * color specified by the parameter Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR. 
             *
             * \valuetype Vis::Color
             * \note The setting is overridden by the Chem::Bond property Vis::BondProperty::CUSTOM_LABEL_COLOR.
             * \since 1.2
             */
            extern CDPL_VIS_API const Base::LookupKey BOND_CUSTOM_LABEL_COLOR;

        } // namespace MolecularGraphProperty
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_MOLECULARGRAPHPROPERTY_HPP
