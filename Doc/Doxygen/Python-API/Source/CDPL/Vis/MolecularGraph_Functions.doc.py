#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief 
# \param molgraph 
#
def clearAtomColorTable(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomColorTable(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomColorTable(molgraph: Chem.MolecularGraph) -> ColorTable: pass

##
# \brief 
# \param molgraph 
# \param colors 
#
def setAtomColorTable(molgraph: Chem.MolecularGraph, colors: ColorTable) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setBondLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setBondCustomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomCustomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setBondConfigurationLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setRadicalElectronDotSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondLineSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondLineSpacing(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondLineSpacing(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param spacing 
#
def setBondLineSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param spacing 
#
def setReactionCenterLineSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param spacing 
#
def setStereoBondHashSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param width 
#
def setStereoBondWedgeWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondLineWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondLineWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondLineWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param width 
#
def setBondLineWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param length 
#
def setReactionCenterLineLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param length 
#
def setDoubleBondTrimLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearTripleBondTrimLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasTripleBondTrimLength(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getTripleBondTrimLength(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param length 
#
def setTripleBondTrimLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondLabelMargin(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondLabelMargin(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondLabelMargin(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param margin 
#
def setBondLabelMargin(molgraph: Chem.MolecularGraph, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomLabelMargin(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomLabelMargin(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomLabelMargin(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
# \param margin 
#
def setAtomLabelMargin(molgraph: Chem.MolecularGraph, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setBondColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setBondCustomLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setAtomCustomLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setBondConfigurationLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setAtomColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setBondLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setAtomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setBondCustomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setAtomCustomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setBondConfigurationLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass
