/* 
 * MolecularGraphFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_VIS_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_VIS_MOLECULARGRAPHFUNCTIONS_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Vis
    {

        class Color;
        class Font;
        class Pen;
        class Brush;
        class SizeSpecification;

        CDPL_VIS_API const ColorTable::SharedPointer& getAtomColorTable(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomColorTable(Chem::MolecularGraph& molgraph, const ColorTable::SharedPointer& colors);

        CDPL_VIS_API bool hasAtomColorTable(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomColorTable(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const Color& getAtomColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomColor(Chem::MolecularGraph& molgraph, const Color& color);

        CDPL_VIS_API bool hasAtomColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomColor(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const Font& getAtomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasAtomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomLabelFont(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getAtomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomLabelSize(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const Font& getSecondaryAtomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setSecondaryAtomLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasSecondaryAtomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearSecondaryAtomLabelFont(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getSecondaryAtomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setSecondaryAtomLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasSecondaryAtomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearSecondaryAtomLabelSize(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getAtomLabelMargin(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomLabelMargin(Chem::MolecularGraph& molgraph, const SizeSpecification& margin);

        CDPL_VIS_API bool hasAtomLabelMargin(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomLabelMargin(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getRadicalElectronDotSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setRadicalElectronDotSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasRadicalElectronDotSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearRadicalElectronDotSize(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const Font& getAtomConfigurationLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomConfigurationLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasAtomConfigurationLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomConfigurationLabelFont(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getAtomConfigurationLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomConfigurationLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomConfigurationLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomConfigurationLabelSize(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getAtomConfigurationLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomConfigurationLabelColor(Chem::MolecularGraph& molgraph, const Color& color);

        CDPL_VIS_API bool hasAtomConfigurationLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomConfigurationLabelColor(Chem::MolecularGraph& molgraph);

       /*
         * \since 1.2
         */
        CDPL_VIS_API const Font& getAtomCustomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomCustomLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasAtomCustomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomCustomLabelFont(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getAtomCustomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomCustomLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomCustomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomCustomLabelSize(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getAtomCustomLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomCustomLabelColor(Chem::MolecularGraph& molgraph, const Color& color);

        CDPL_VIS_API bool hasAtomCustomLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomCustomLabelColor(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getAtomHighlightAreaSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomHighlightAreaSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasAtomHighlightAreaSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomHighlightAreaSize(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getAtomHighlightAreaBrush(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomHighlightAreaBrush(Chem::MolecularGraph& molgraph, const Brush& brush);

        CDPL_VIS_API bool hasAtomHighlightAreaBrush(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomHighlightAreaBrush(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getAtomHighlightAreaOutlinePen(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setAtomHighlightAreaOutlinePen(Chem::MolecularGraph& molgraph, const Pen& pen);

        CDPL_VIS_API bool hasAtomHighlightAreaOutlinePen(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearAtomHighlightAreaOutlinePen(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getHighlightAreaOutlineWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setHighlightAreaOutlineWidth(Chem::MolecularGraph& molgraph, const SizeSpecification& width);

        CDPL_VIS_API bool hasHighlightAreaOutlineWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearHighlightAreaOutlineWidth(Chem::MolecularGraph& molgraph);

        
        CDPL_VIS_API const Color& getBondColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondColor(Chem::MolecularGraph& molgraph, const Color& color);

        CDPL_VIS_API bool hasBondColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondColor(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getBondLineWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondLineWidth(Chem::MolecularGraph& molgraph, const SizeSpecification& width);

        CDPL_VIS_API bool hasBondLineWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondLineWidth(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getBondLineSpacing(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondLineSpacing(Chem::MolecularGraph& molgraph, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasBondLineSpacing(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondLineSpacing(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getStereoBondWedgeWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setStereoBondWedgeWidth(Chem::MolecularGraph& molgraph, const SizeSpecification& width);

        CDPL_VIS_API bool hasStereoBondWedgeWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearStereoBondWedgeWidth(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getStereoBondHashSpacing(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setStereoBondHashSpacing(Chem::MolecularGraph& molgraph, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasStereoBondHashSpacing(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearStereoBondHashSpacing(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getReactionCenterLineLength(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setReactionCenterLineLength(Chem::MolecularGraph& molgraph, const SizeSpecification& length);

        CDPL_VIS_API bool hasReactionCenterLineLength(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearReactionCenterLineLength(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getReactionCenterLineSpacing(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setReactionCenterLineSpacing(Chem::MolecularGraph& molgraph, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasReactionCenterLineSpacing(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearReactionCenterLineSpacing(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getDoubleBondTrimLength(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setDoubleBondTrimLength(Chem::MolecularGraph& molgraph, const SizeSpecification& length);

        CDPL_VIS_API bool hasDoubleBondTrimLength(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearDoubleBondTrimLength(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getTripleBondTrimLength(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setTripleBondTrimLength(Chem::MolecularGraph& molgraph, const SizeSpecification& length);

        CDPL_VIS_API bool hasTripleBondTrimLength(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearTripleBondTrimLength(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const Font& getBondLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasBondLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondLabelFont(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getBondLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasBondLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondLabelSize(Chem::MolecularGraph& molgraph);


        CDPL_VIS_API const SizeSpecification& getBondLabelMargin(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondLabelMargin(Chem::MolecularGraph& molgraph, const SizeSpecification& margin);

        CDPL_VIS_API bool hasBondLabelMargin(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondLabelMargin(Chem::MolecularGraph& molgraph);
             /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getBondHighlightAreaWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondHighlightAreaWidth(Chem::MolecularGraph& molgraph, const SizeSpecification& width);

        CDPL_VIS_API bool hasBondHighlightAreaWidth(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondHighlightAreaWidth(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getBondHighlightAreaBrush(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondHighlightAreaBrush(Chem::MolecularGraph& molgraph, const Brush& brush);

        CDPL_VIS_API bool hasBondHighlightAreaBrush(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondHighlightAreaBrush(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getBondHighlightAreaOutlinePen(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondHighlightAreaOutlinePen(Chem::MolecularGraph& molgraph, const Pen& pen);

        CDPL_VIS_API bool hasBondHighlightAreaOutlinePen(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondHighlightAreaOutlinePen(Chem::MolecularGraph& molgraph);
        
        /*
         * \since 1.1
         */
        CDPL_VIS_API const Font& getBondConfigurationLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondConfigurationLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasBondConfigurationLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondConfigurationLabelFont(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getBondConfigurationLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondConfigurationLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasBondConfigurationLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondConfigurationLabelSize(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getBondConfigurationLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondConfigurationLabelColor(Chem::MolecularGraph& molgraph, const Color& color);

        CDPL_VIS_API bool hasBondConfigurationLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondConfigurationLabelColor(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Font& getBondCustomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondCustomLabelFont(Chem::MolecularGraph& molgraph, const Font& font);

        CDPL_VIS_API bool hasBondCustomLabelFont(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondCustomLabelFont(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getBondCustomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondCustomLabelSize(Chem::MolecularGraph& molgraph, const SizeSpecification& size);

        CDPL_VIS_API bool hasBondCustomLabelSize(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondCustomLabelSize(Chem::MolecularGraph& molgraph);

        /*
         * \since 1.2
         */
        CDPL_VIS_API const Color& getBondCustomLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void setBondCustomLabelColor(Chem::MolecularGraph& molgraph, const Color& color);

        CDPL_VIS_API bool hasBondCustomLabelColor(const Chem::MolecularGraph& molgraph);

        CDPL_VIS_API void clearBondCustomLabelColor(Chem::MolecularGraph& molgraph);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_MOLECULARGRAPHFUNCTIONS_HPP
