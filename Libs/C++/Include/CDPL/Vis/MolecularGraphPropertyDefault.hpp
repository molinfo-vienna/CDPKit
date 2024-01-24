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

            extern CDPL_VIS_API const ColorTable::SharedPointer ATOM_COLOR_TABLE;
            extern CDPL_VIS_API const Color                     ATOM_COLOR;
            extern CDPL_VIS_API const Font                      ATOM_LABEL_FONT;
            extern CDPL_VIS_API const SizeSpecification         ATOM_LABEL_SIZE;
            extern CDPL_VIS_API const Font                      SECONDARY_ATOM_LABEL_FONT;
            extern CDPL_VIS_API const SizeSpecification         SECONDARY_ATOM_LABEL_SIZE;
            extern CDPL_VIS_API const SizeSpecification         ATOM_LABEL_MARGIN;
            extern CDPL_VIS_API const SizeSpecification         RADICAL_ELECTRON_DOT_SIZE;

            /*
             * \since 1.1
             */
            extern CDPL_VIS_API const Font                      ATOM_CONFIGURATION_LABEL_FONT;

            /*
             * \since 1.1
             */
            extern CDPL_VIS_API const SizeSpecification         ATOM_CONFIGURATION_LABEL_SIZE;
            extern CDPL_VIS_API const Color                     BOND_COLOR;
            extern CDPL_VIS_API const SizeSpecification         BOND_LINE_WIDTH;
            extern CDPL_VIS_API const SizeSpecification         BOND_LINE_SPACING;
            extern CDPL_VIS_API const SizeSpecification         STEREO_BOND_WEDGE_WIDTH;
            extern CDPL_VIS_API const SizeSpecification         STEREO_BOND_HASH_SPACING;
            extern CDPL_VIS_API const SizeSpecification         REACTION_CENTER_LINE_LENGTH;
            extern CDPL_VIS_API const SizeSpecification         REACTION_CENTER_LINE_SPACING;
            extern CDPL_VIS_API const SizeSpecification         DOUBLE_BOND_TRIM_LENGTH;
            extern CDPL_VIS_API const SizeSpecification         TRIPLE_BOND_TRIM_LENGTH;
            extern CDPL_VIS_API const Font                      BOND_LABEL_FONT;
            extern CDPL_VIS_API const SizeSpecification         BOND_LABEL_SIZE;
            extern CDPL_VIS_API const SizeSpecification         BOND_LABEL_MARGIN;

            /*
             * \since 1.1
             */
            extern CDPL_VIS_API const Font                      BOND_CONFIGURATION_LABEL_FONT;

            /*
             * \since 1.1
             */
            extern CDPL_VIS_API const SizeSpecification         BOND_CONFIGURATION_LABEL_SIZE;
        } // namespace MolecularGraphPropertyDefault
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_MOLECULARGRAPHPROPERTYDEFAULT_HPP
