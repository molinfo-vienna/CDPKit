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
    }
}

#endif // CDPL_VIS_MOLECULARGRAPHFUNCTIONS_HPP
