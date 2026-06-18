/* 
 * MolecularGraphPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::MolecularGraphPropertyDefault.
 */

#ifndef CDPL_VIS_MOLECULARGRAPHPROPERTYDEFAULT_HPP
#define CDPL_VIS_MOLECULARGRAPHPROPERTYDEFAULT_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Provides default values for built-in Chem::MolecularGraph properties.
         */
        namespace MolecularGraphPropertyDefault
        {

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_COLOR_TABLE property.
             */
            extern CDPL_VIS_API const ColorTable::SharedPointer ATOM_COLOR_TABLE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_COLOR property.
             */
            extern CDPL_VIS_API const Color                     ATOM_COLOR;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_LABEL_FONT property.
             */
            extern CDPL_VIS_API const Font                      ATOM_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_LABEL_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification         ATOM_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT property.
             */
            extern CDPL_VIS_API const Font                      SECONDARY_ATOM_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification         SECONDARY_ATOM_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_LABEL_MARGIN property.
             */
            extern CDPL_VIS_API const SizeSpecification         ATOM_LABEL_MARGIN;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification         RADICAL_ELECTRON_DOT_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_FONT property.
             * \since 1.1
             */
            extern CDPL_VIS_API const Font                      ATOM_CONFIGURATION_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_SIZE property.
             * \since 1.1
             */
            extern CDPL_VIS_API const SizeSpecification         ATOM_CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_CONFIGURATION_LABEL_COLOR property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Color                     ATOM_CONFIGURATION_LABEL_COLOR;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_FONT property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Font                      ATOM_CUSTOM_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_SIZE property.
             * \since 1.2
             */
            extern CDPL_VIS_API const SizeSpecification         ATOM_CUSTOM_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_CUSTOM_LABEL_COLOR property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Color                     ATOM_CUSTOM_LABEL_COLOR;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_SIZE property.
             * \since 1.2
             */
            extern CDPL_VIS_API const SizeSpecification         ATOM_HIGHLIGHT_AREA_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_BRUSH property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Brush                     ATOM_HIGHLIGHT_AREA_BRUSH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Pen                       ATOM_HIGHLIGHT_AREA_OUTLINE_PEN;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::HIGHLIGHT_AREA_OUTLINE_WIDTH property.
             * \since 1.2
             */
            extern CDPL_VIS_API const SizeSpecification         HIGHLIGHT_AREA_OUTLINE_WIDTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_COLOR property.
             */
            extern CDPL_VIS_API const Color                     BOND_COLOR;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_LINE_WIDTH property.
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_LINE_WIDTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_LINE_SPACING property.
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_LINE_SPACING;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH property.
             */
            extern CDPL_VIS_API const SizeSpecification         STEREO_BOND_WEDGE_WIDTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::STEREO_BOND_HASH_SPACING property.
             */
            extern CDPL_VIS_API const SizeSpecification         STEREO_BOND_HASH_SPACING;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH property.
             */
            extern CDPL_VIS_API const SizeSpecification         REACTION_CENTER_LINE_LENGTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::REACTION_CENTER_LINE_SPACING property.
             */
            extern CDPL_VIS_API const SizeSpecification         REACTION_CENTER_LINE_SPACING;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH property.
             */
            extern CDPL_VIS_API const SizeSpecification         DOUBLE_BOND_TRIM_LENGTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH property.
             */
            extern CDPL_VIS_API const SizeSpecification         TRIPLE_BOND_TRIM_LENGTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_LABEL_FONT property.
             */
            extern CDPL_VIS_API const Font                      BOND_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_LABEL_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_LABEL_MARGIN property.
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_LABEL_MARGIN;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_FONT property.
             * \since 1.1
             */
            extern CDPL_VIS_API const Font                      BOND_CONFIGURATION_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_SIZE property.
             * \since 1.1
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_CONFIGURATION_LABEL_COLOR property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Color                     BOND_CONFIGURATION_LABEL_COLOR;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_FONT property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Font                      BOND_CUSTOM_LABEL_FONT;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_SIZE property.
             * \since 1.2
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_CUSTOM_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_CUSTOM_LABEL_COLOR property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Color                     BOND_CUSTOM_LABEL_COLOR;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_WIDTH property.
             * \since 1.2
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_HIGHLIGHT_AREA_WIDTH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_BRUSH property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Brush                     BOND_HIGHLIGHT_AREA_BRUSH;

            /**
             * \brief Default value of the Vis::MolecularGraphProperty::BOND_HIGHLIGHT_AREA_OUTLINE_PEN property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Pen                       BOND_HIGHLIGHT_AREA_OUTLINE_PEN;
        } // namespace MolecularGraphPropertyDefault
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_MOLECULARGRAPHPROPERTYDEFAULT_HPP
