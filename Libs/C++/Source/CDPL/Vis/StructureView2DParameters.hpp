/* 
 * StructureView2DParameters.hpp 
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


#ifndef CDPL_VIS_STRUCTUREVIEW2DPARAMETERS_HPP
#define CDPL_VIS_STRUCTUREVIEW2DPARAMETERS_HPP

#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/ColorTable.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
        class Any;
    } // namespace Base

    namespace Vis
    {

        class View2D;

        class StructureView2DParameters
        {

          public:
            StructureView2DParameters(View2D&);

            ~StructureView2DParameters();

            const Rectangle2D& getViewport() const;
            unsigned int       getAlignment() const;
            double             getStdBondLength() const;
            unsigned int       getSizeAdjustment() const;

            bool         eraseBackground() const;
            const Color& getBackgroundColor() const;

            const ColorTable::SharedPointer& getAtomColorTable() const;

            bool useCalculatedAtomCoords() const;

            const Color&             getAtomColor() const;
            const Color&             getAtomConfigLabelColor() const;
            const Color&             getAtomCustomLabelColor() const;
            const Font&              getAtomLabelFont() const;
            const Font&              getSecondaryAtomLabelFont() const;
            const Font&              getAtomConfigLabelFont() const;
            const Font&              getAtomCustomLabelFont() const;
            const SizeSpecification& getAtomLabelSize() const;
            const SizeSpecification& getSecondaryAtomLabelSize() const;
            const SizeSpecification& getAtomConfigLabelSize() const;
            const SizeSpecification& getAtomCustomLabelSize() const;
            const SizeSpecification& getAtomLabelMargin() const;
            const SizeSpecification& getRadicalElectronDotSize() const;
            const SizeSpecification& getAtomHighlightAreaSize() const;
            const Brush&             getAtomHighlightAreaBrush() const;
            const Pen&               getAtomHighlightAreaPen() const;
            bool                     breakAtomHighlightAreaOutline() const;

            bool showCarbons() const;
            bool showIsotopes() const;
            bool showCharges() const;
            bool showExplicitHydrogens() const;
            bool showHydrogenCounts() const;
            bool showNonCarbonHydrogenCounts() const;
            bool showAtomReactionInfos() const;
            bool showAtomQueryInfos() const;
            bool showRadicalElectrons() const;
            bool showAtomConfigLabels() const;
            bool showAtomCustomLabels() const;
            bool enableAtomHighlighting() const;

            const SizeSpecification& getHighlightAreaOutlineWidth() const;
            
            const Color&             getBondColor() const;
            const Color&             getBondConfigLabelColor() const;
            const Color&             getBondCustomLabelColor() const;
            const Font&              getBondLabelFont() const;
            const Font&              getBondConfigLabelFont() const;
            const Font&              getBondCustomLabelFont() const;
            const SizeSpecification& getBondLabelSize() const;
            const SizeSpecification& getBondConfigLabelSize() const;
            const SizeSpecification& getBondCustomLabelSize() const;
            const SizeSpecification& getBondLabelMargin() const;
            const SizeSpecification& getBondLineWidth() const;
            const SizeSpecification& getBondLineSpacing() const;
            const SizeSpecification& getStereoBondWedgeWidth() const;
            const SizeSpecification& getStereoBondHashSpacing() const;
            const SizeSpecification& getReactionCenterLineLength() const;
            const SizeSpecification& getReactionCenterLineSpacing() const;
            const SizeSpecification& getDoubleBondTrimLength() const;
            const SizeSpecification& getTripleBondTrimLength() const;
            const SizeSpecification& getBondHighlightAreaWidth() const;
            const Brush&             getBondHighlightAreaBrush() const;
            const Pen&               getBondHighlightAreaPen() const;
     
            bool showBondReactionInfos() const;
            bool showBondQueryInfos() const;
            bool showStereoBonds() const;
            bool showBondConfigLabels() const;
            bool showBondCustomLabels() const;
            bool enableBondHighlighting() const;
            
            bool coordinatesChanged() const;
            bool explicitHVisibilityChanged() const;
            bool propertyVisibilityChanged() const;
            bool graphicsAttributeChanged() const;
            bool stdBondLengthChanged() const;
            bool viewportChanged() const;
            bool alignmentChanged() const;
            bool sizeAdjustmentChanged() const;

            void clearChangeFlags();

          private:
            void parentChanged();
            void parameterChanged(const Base::LookupKey&, Base::Any);
            void parameterRemoved(const Base::LookupKey&);

            void setViewport(const Rectangle2D&);
            void setAlignment(unsigned int);
            void setStdBondLength(double);
            void setSizeAdjustment(unsigned int);

            void eraseBackground(bool);
            void setBackgroundColor(const Color&);

            void setAtomColorTable(const ColorTable::SharedPointer&);

            void useCalculatedAtomCoords(bool);

            void setAtomColor(const Color&);
            void setAtomLabelFont(const Font&);
            void setAtomLabelSize(const SizeSpecification&);
            void setSecondaryAtomLabelFont(const Font&);
            void setSecondaryAtomLabelSize(const SizeSpecification&);
            void setAtomConfigLabelFont(const Font&);
            void setAtomConfigLabelSize(const SizeSpecification&);
            void setAtomConfigLabelColor(const Color&);
            void setAtomCustomLabelFont(const Font&);
            void setAtomCustomLabelSize(const SizeSpecification&);
            void setAtomCustomLabelColor(const Color&);
            void setAtomLabelMargin(const SizeSpecification&);
            void setRadicalElectronDotSize(const SizeSpecification&);
            void setAtomHighlightAreaSize(const SizeSpecification&);
            void setAtomHighlightAreaBrush(const Brush&);
            void setAtomHighlightAreaPen(const Pen&);
            void breakAtomHighlightAreaOutline(bool);
            
            void showCarbons(bool);
            void showIsotopes(bool);
            void showCharges(bool);
            void showExplicitHydrogens(bool);
            void showHydrogenCounts(bool);
            void showNonCarbonHydrogenCounts(bool);
            void showAtomReactionInfos(bool);
            void showAtomQueryInfos(bool);
            void showRadicalElectrons(bool);
            void showAtomConfigLabels(bool);
            void showAtomCustomLabels(bool);
            void enableAtomHighlighting(bool);
            
            void setHighlightAreaOutlineWidth(const SizeSpecification&);
            
            void setBondColor(const Color&);
            void setBondLabelFont(const Font&);
            void setBondLabelSize(const SizeSpecification&);
            void setBondConfigLabelFont(const Font&);
            void setBondConfigLabelSize(const SizeSpecification&);
            void setBondConfigLabelColor(const Color&);
            void setBondCustomLabelFont(const Font&);
            void setBondCustomLabelSize(const SizeSpecification&);
            void setBondCustomLabelColor(const Color&);
            void setBondLabelMargin(const SizeSpecification&);
            void setBondLineWidth(const SizeSpecification&);
            void setBondLineSpacing(const SizeSpecification&);
            void setStereoBondWedgeWidth(const SizeSpecification&);
            void setStereoBondHashSpacing(const SizeSpecification&);
            void setReactionCenterLineLength(const SizeSpecification&);
            void setReactionCenterLineSpacing(const SizeSpecification&);
            void setDoubleBondTrimLength(const SizeSpecification&);
            void setTripleBondTrimLength(const SizeSpecification&);
            void setBondHighlightAreaWidth(const SizeSpecification&);
            void setBondHighlightAreaBrush(const Brush&);
            void setBondHighlightAreaPen(const Pen&);
        
            void showBondReactionInfos(bool);
            void showBondQueryInfos(bool);
            void showStereoBonds(bool);
            void showBondConfigLabels(bool);
            void showBondCustomLabels(bool);
            void enableBondHighlighting(bool);

            const View2D&             view;
            Rectangle2D               viewport;
            double                    stdBondLength;
            unsigned int              sizeAdjustment;
            unsigned int              alignment;
            bool                      eraseBackgroundFlag;
            Color                     backgroundColor;
            bool                      useCalcAtomCoordsFlag;
            ColorTable::SharedPointer atomColorTable;
            Color                     atomColor;
            Font                      atomLabelFont;
            Font                      secondaryAtomLabelFont;
            Font                      atomConfigLabelFont;
            Font                      atomCustomLabelFont;
            Color                     atomConfigLabelColor;
            Color                     atomCustomLabelColor;
            SizeSpecification         atomLabelSize;
            SizeSpecification         secondaryAtomLabelSize;
            SizeSpecification         atomConfigLabelSize;
            SizeSpecification         atomCustomLabelSize;
            SizeSpecification         atomLabelMargin;
            SizeSpecification         radicalElectronDotSize;
            SizeSpecification         atomHighlightAreaSize;
            Brush                     atomHighlightAreaBrush;
            Pen                       atomHighlightAreaPen;
            bool                      breakAtomHighltAreaOutline;
            bool                      showCarbonsFlag;
            bool                      showChargesFlag;
            bool                      showIsotopesFlag;
            bool                      showExplicitHsFlag;
            bool                      showHydrogenCountsFlag;
            bool                      showNonCarbonHydrogenCountsFlag;
            bool                      showAtomReactionInfosFlag;
            bool                      showAtomQueryInfosFlag;
            bool                      showRadicalElectronsFlag;
            bool                      showAtomConfigLabelsFlag;
            bool                      showAtomCustomLabelsFlag;
            bool                      enableAtomHighlightingFlag;
            SizeSpecification         highlightAreaOutlineWidth;
            Color                     bondColor;
            Font                      bondLabelFont;
            Font                      bondConfigLabelFont;
            Font                      bondCustomLabelFont;
            Color                     bondConfigLabelColor;
            Color                     bondCustomLabelColor;
            SizeSpecification         bondLabelSize;
            SizeSpecification         bondConfigLabelSize;
            SizeSpecification         bondCustomLabelSize;
            SizeSpecification         bondLabelMargin;
            SizeSpecification         bondLineWidth;
            SizeSpecification         bondLineSpacing;
            SizeSpecification         stereoBondWedgeWidth;
            SizeSpecification         stereoBondHashSpacing;
            SizeSpecification         reactionCenterLineLength;
            SizeSpecification         reactionCenterLineSpacing;
            SizeSpecification         doubleBondTrimLength;
            SizeSpecification         tripleBondTrimLength;
            SizeSpecification         bondHighlightAreaWidth;
            Brush                     bondHighlightAreaBrush;
            Pen                       bondHighlightAreaPen;
            bool                      showBondReactionInfosFlag;
            bool                      showBondQueryInfosFlag;
            bool                      showStereoBondsFlag;
            bool                      showBondConfigLabelsFlag;
            bool                      showBondCustomLabelsFlag;
            bool                      enableBondHighlightingFlag;
            bool                      coordinatesChangedFlag;
            bool                      explicitHVisibilityChangedFlag;
            bool                      propertyVisibilityChangedFlag;
            bool                      graphicsAttributeChangedFlag;
            bool                      stdBondLengthChangedFlag;
            bool                      viewportChangedFlag;
            bool                      alignmentChangedFlag;
            bool                      sizeAdjustmentChangedFlag;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_STRUCTUREVIEW2DPARAMETERS_HPP
