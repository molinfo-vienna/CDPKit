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
# \param rxn 
# \param show 
#
def setAgentAlignment(rxn: Chem.Reaction, show: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasAgentAlignment(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getAgentAlignment(rxn: Chem.Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearAgentAlignment(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param dir 
#
def setAgentLayoutDirection(rxn: Chem.Reaction, dir: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasAgentLayoutDirection(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getAgentLayoutDirection(rxn: Chem.Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearAgentLayoutDirection(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param show 
#
def setAgentLayout(rxn: Chem.Reaction, show: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasAgentLayout(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getAgentLayout(rxn: Chem.Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearAgentLayout(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param color 
#
def setArrowColor(rxn: Chem.Reaction, color: Color) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowColor(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowColor(rxn: Chem.Reaction) -> Color: pass

##
# \brief 
# \param rxn 
#
def clearArrowColor(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param length 
#
def setArrowHeadLength(rxn: Chem.Reaction, length: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowHeadLength(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowHeadLength(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearArrowHeadLength(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param width 
#
def setArrowHeadWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowHeadWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowHeadWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearArrowHeadWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param length 
#
def setArrowLength(rxn: Chem.Reaction, length: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowLength(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowLength(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearArrowLength(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param width 
#
def setArrowLineWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowLineWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowLineWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearArrowLineWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param width 
#
def setArrowShaftWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowShaftWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowShaftWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearArrowShaftWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param style 
#
def setArrowStyle(rxn: Chem.Reaction, style: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasArrowStyle(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getArrowStyle(rxn: Chem.Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearArrowStyle(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setAtomColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

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
#
def clearAtomColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param colors 
#
def setAtomColorTable(molgraph: Chem.MolecularGraph, colors: ColorTable) -> None: pass

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
#
def clearAtomColorTable(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

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
#
def clearAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setAtomCustomLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

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
#
def clearAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setAtomCustomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomCustomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param brush 
#
def setAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph, brush: Brush) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> Brush: pass

##
# \brief 
# \param molgraph 
#
def clearAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param pen 
#
def setAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph, pen: Pen) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> Pen: pass

##
# \brief 
# \param molgraph 
#
def clearAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomHighlightAreaSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAtomHighlightAreaSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAtomHighlightAreaSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
#
def clearAtomHighlightAreaSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setAtomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearAtomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param margin 
#
def setAtomLabelMargin(molgraph: Chem.MolecularGraph, margin: SizeSpecification) -> None: pass

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
#
def clearAtomLabelMargin(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setAtomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearAtomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setBondColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

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
#
def clearBondColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setBondConfigurationLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

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
#
def clearBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setBondConfigurationLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setBondConfigurationLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param color 
#
def setBondCustomLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

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
#
def clearBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setBondCustomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setBondCustomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param brush 
#
def setBondHighlightAreaBrush(molgraph: Chem.MolecularGraph, brush: Brush) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> Brush: pass

##
# \brief 
# \param molgraph 
#
def clearBondHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param pen 
#
def setBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph, pen: Pen) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> Pen: pass

##
# \brief 
# \param molgraph 
#
def clearBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param width 
#
def setBondHighlightAreaWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasBondHighlightAreaWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getBondHighlightAreaWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
#
def clearBondHighlightAreaWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setBondLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearBondLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param margin 
#
def setBondLabelMargin(molgraph: Chem.MolecularGraph, margin: SizeSpecification) -> None: pass

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
#
def clearBondLabelMargin(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setBondLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearBondLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param spacing 
#
def setBondLineSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

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
#
def clearBondLineSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param width 
#
def setBondLineWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

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
#
def clearBondLineWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param color 
#
def setColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasColor(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getColor(atom: Chem.Atom) -> Color: pass

##
# \brief 
# \param atom 
#
def clearColor(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param color 
#
def setColor(bond: Chem.Bond, color: Color) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasColor(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getColor(bond: Chem.Bond) -> Color: pass

##
# \brief 
# \param bond 
#
def clearColor(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param rxn 
# \param dir 
#
def setComponentLayoutDirection(rxn: Chem.Reaction, dir: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasComponentLayoutDirection(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getComponentLayoutDirection(rxn: Chem.Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearComponentLayoutDirection(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param layout 
#
def setComponentLayout(rxn: Chem.Reaction, layout: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasComponentLayout(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getComponentLayout(rxn: Chem.Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearComponentLayout(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param margin 
#
def setComponentMargin(rxn: Chem.Reaction, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasComponentMargin(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getComponentMargin(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearComponentMargin(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param color 
#
def setConfigurationLabelColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasConfigurationLabelColor(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getConfigurationLabelColor(atom: Chem.Atom) -> Color: pass

##
# \brief 
# \param atom 
#
def clearConfigurationLabelColor(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param color 
#
def setConfigurationLabelColor(bond: Chem.Bond, color: Color) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasConfigurationLabelColor(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getConfigurationLabelColor(bond: Chem.Bond) -> Color: pass

##
# \brief 
# \param bond 
#
def clearConfigurationLabelColor(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param font 
#
def setConfigurationLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasConfigurationLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getConfigurationLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief 
# \param atom 
#
def clearConfigurationLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param font 
#
def setConfigurationLabelFont(bond: Chem.Bond, font: Font) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasConfigurationLabelFont(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getConfigurationLabelFont(bond: Chem.Bond) -> Font: pass

##
# \brief 
# \param bond 
#
def clearConfigurationLabelFont(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param size 
#
def setConfigurationLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasConfigurationLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getConfigurationLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
#
def clearConfigurationLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param size 
#
def setConfigurationLabelSize(bond: Chem.Bond, size: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasConfigurationLabelSize(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getConfigurationLabelSize(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearConfigurationLabelSize(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param text 
#
def setCustomLabel(atom: Chem.Atom, text: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCustomLabel(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCustomLabel(atom: Chem.Atom) -> object: pass

##
# \brief 
# \param atom 
#
def clearCustomLabel(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param text 
#
def setCustomLabel(bond: Chem.Bond, text: str) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasCustomLabel(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getCustomLabel(bond: Chem.Bond) -> object: pass

##
# \brief 
# \param bond 
#
def clearCustomLabel(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param color 
#
def setCustomLabelColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCustomLabelColor(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCustomLabelColor(atom: Chem.Atom) -> Color: pass

##
# \brief 
# \param atom 
#
def clearCustomLabelColor(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param color 
#
def setCustomLabelColor(bond: Chem.Bond, color: Color) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasCustomLabelColor(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getCustomLabelColor(bond: Chem.Bond) -> Color: pass

##
# \brief 
# \param bond 
#
def clearCustomLabelColor(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param font 
#
def setCustomLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCustomLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCustomLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief 
# \param atom 
#
def clearCustomLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param font 
#
def setCustomLabelFont(bond: Chem.Bond, font: Font) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasCustomLabelFont(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getCustomLabelFont(bond: Chem.Bond) -> Font: pass

##
# \brief 
# \param bond 
#
def clearCustomLabelFont(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param size 
#
def setCustomLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCustomLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCustomLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
#
def clearCustomLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param size 
#
def setCustomLabelSize(bond: Chem.Bond, size: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasCustomLabelSize(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getCustomLabelSize(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearCustomLabelSize(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param bond 
# \param length 
#
def setDoubleBondTrimLength(bond: Chem.Bond, length: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasDoubleBondTrimLength(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getDoubleBondTrimLength(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearDoubleBondTrimLength(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param length 
#
def setDoubleBondTrimLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

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
#
def clearDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param brush 
#
def setHighlightAreaBrush(atom: Chem.Atom, brush: Brush) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHighlightAreaBrush(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHighlightAreaBrush(atom: Chem.Atom) -> Brush: pass

##
# \brief 
# \param atom 
#
def clearHighlightAreaBrush(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param brush 
#
def setHighlightAreaBrush(bond: Chem.Bond, brush: Brush) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasHighlightAreaBrush(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getHighlightAreaBrush(bond: Chem.Bond) -> Brush: pass

##
# \brief 
# \param bond 
#
def clearHighlightAreaBrush(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param pen 
#
def setHighlightAreaOutlinePen(atom: Chem.Atom, pen: Pen) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHighlightAreaOutlinePen(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHighlightAreaOutlinePen(atom: Chem.Atom) -> Pen: pass

##
# \brief 
# \param atom 
#
def clearHighlightAreaOutlinePen(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param pen 
#
def setHighlightAreaOutlinePen(bond: Chem.Bond, pen: Pen) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasHighlightAreaOutlinePen(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getHighlightAreaOutlinePen(bond: Chem.Bond) -> Pen: pass

##
# \brief 
# \param bond 
#
def clearHighlightAreaOutlinePen(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param width 
#
def setHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief 
# \param molgraph 
#
def clearHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param highlighted 
#
def setHighlightedFlag(atom: Chem.Atom, highlighted: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHighlightedFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHighlightedFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearHighlightedFlag(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param highlighted 
#
def setHighlightedFlag(bond: Chem.Bond, highlighted: bool) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasHighlightedFlag(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getHighlightedFlag(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
#
def clearHighlightedFlag(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param font 
#
def setLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief 
# \param atom 
#
def clearLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param font 
#
def setLabelFont(bond: Chem.Bond, font: Font) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasLabelFont(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getLabelFont(bond: Chem.Bond) -> Font: pass

##
# \brief 
# \param bond 
#
def clearLabelFont(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param margin 
#
def setLabelMargin(atom: Chem.Atom, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasLabelMargin(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getLabelMargin(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
#
def clearLabelMargin(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param margin 
#
def setLabelMargin(bond: Chem.Bond, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasLabelMargin(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getLabelMargin(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearLabelMargin(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param atom 
# \param size 
#
def setLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
#
def clearLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param size 
#
def setLabelSize(bond: Chem.Bond, size: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasLabelSize(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getLabelSize(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearLabelSize(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param bond 
# \param spacing 
#
def setLineSpacing(bond: Chem.Bond, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasLineSpacing(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getLineSpacing(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearLineSpacing(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param bond 
# \param width 
#
def setLineWidth(bond: Chem.Bond, width: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasLineWidth(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getLineWidth(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearLineWidth(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param obj 
# \param material 
#
def setMaterial(obj: Object3D, material: Material) -> None: pass

##
# \brief 
# \param obj 
# \return 
#
def hasMaterial(obj: Object3D) -> bool: pass

##
# \brief 
# \param obj 
# \return 
#
def getMaterial(obj: Object3D) -> Material: pass

##
# \brief 
# \param obj 
#
def clearMaterial(obj: Object3D) -> None: pass

##
# \brief 
# \param rxn 
# \param color 
#
def setPlusSignColor(rxn: Chem.Reaction, color: Color) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasPlusSignColor(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getPlusSignColor(rxn: Chem.Reaction) -> Color: pass

##
# \brief 
# \param rxn 
#
def clearPlusSignColor(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param width 
#
def setPlusSignLineWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasPlusSignLineWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getPlusSignLineWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearPlusSignLineWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param size 
#
def setPlusSignSize(rxn: Chem.Reaction, size: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasPlusSignSize(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getPlusSignSize(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief 
# \param rxn 
#
def clearPlusSignSize(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param size 
#
def setRadicalElectronDotSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasRadicalElectronDotSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getRadicalElectronDotSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
#
def clearRadicalElectronDotSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setRadicalElectronDotSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param bond 
# \param length 
#
def setReactionCenterLineLength(bond: Chem.Bond, length: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasReactionCenterLineLength(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getReactionCenterLineLength(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearReactionCenterLineLength(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param length 
#
def setReactionCenterLineLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

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
#
def clearReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param bond 
# \param spacing 
#
def setReactionCenterLineSpacing(bond: Chem.Bond, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasReactionCenterLineSpacing(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getReactionCenterLineSpacing(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearReactionCenterLineSpacing(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param spacing 
#
def setReactionCenterLineSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

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
#
def clearReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param font 
#
def setSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

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
#
def clearSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param size 
#
def setSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

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
#
def clearSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param font 
#
def setSecondaryLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSecondaryLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSecondaryLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief 
# \param atom 
#
def clearSecondaryLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param size 
#
def setSecondaryLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSecondaryLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSecondaryLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
#
def clearSecondaryLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param obj 
# \param shape 
#
def setShape(obj: Object3D, shape: Shape3D) -> None: pass

##
# \brief 
# \param obj 
# \return 
#
def hasShape(obj: Object3D) -> bool: pass

##
# \brief 
# \param obj 
# \return 
#
def getShape(obj: Object3D) -> object: pass

##
# \brief 
# \param obj 
#
def clearShape(obj: Object3D) -> None: pass

##
# \brief 
# \param rxn 
# \param show 
#
def setShowAgents(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasShowAgents(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getShowAgents(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
#
def clearShowAgents(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param show 
#
def setShowPlusSigns(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasShowPlusSigns(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getShowPlusSigns(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
#
def clearShowPlusSigns(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param show 
#
def setShowProducts(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasShowProducts(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getShowProducts(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
#
def clearShowProducts(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param show 
#
def setShowReactants(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasShowReactants(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getShowReactants(rxn: Chem.Reaction) -> bool: pass

##
# \brief 
# \param rxn 
#
def clearShowReactants(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param bond 
# \param spacing 
#
def setStereoBondHashSpacing(bond: Chem.Bond, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasStereoBondHashSpacing(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getStereoBondHashSpacing(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearStereoBondHashSpacing(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param spacing 
#
def setStereoBondHashSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

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
#
def clearStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param bond 
# \param width 
#
def setStereoBondWedgeWidth(bond: Chem.Bond, width: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasStereoBondWedgeWidth(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getStereoBondWedgeWidth(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearStereoBondWedgeWidth(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param width 
#
def setStereoBondWedgeWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

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
#
def clearStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param obj 
# \param mtx 
#
def setTransformationMatrix(obj: Object3D, mtx: Math.Matrix4D) -> None: pass

##
# \brief 
# \param obj 
# \return 
#
def hasTransformationMatrix(obj: Object3D) -> bool: pass

##
# \brief 
# \param obj 
# \return 
#
def getTransformationMatrix(obj: Object3D) -> Math.Matrix4D: pass

##
# \brief 
# \param obj 
#
def clearTransformationMatrix(obj: Object3D) -> None: pass

##
# \brief 
# \param bond 
# \param length 
#
def setTripleBondTrimLength(bond: Chem.Bond, length: SizeSpecification) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasTripleBondTrimLength(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getTripleBondTrimLength(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief 
# \param bond 
#
def clearTripleBondTrimLength(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param length 
#
def setTripleBondTrimLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

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
#
def clearTripleBondTrimLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param mesh 
# \param weight_face_size 
#
def calcVertexFromFaceNormals(mesh: TriangleMesh3D, weight_face_size: bool = False) -> None: pass

##
# \brief 
# \param mesh 
# \param normals 
# \param weight_face_size 
#
def calcVertexFromFaceNormals(mesh: TriangleMesh3D, normals: Math.Vector3DArray, weight_face_size: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
#
def prepareFor2DVisualization(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
#
def prepareFor2DVisualization(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param mesh 
# \param check_vn 
# \param tol 
# \return 
#
def removeVertexDuplicates(mesh: TriangleMesh3D, check_vn: bool = True, tol: float = 0.0) -> int: pass

##
# \brief 
# \param mesh 
# \param angle 
# \param vtx_offs 
# \param vtx_count 
#
def rotateX(mesh: TriangleMesh3D, angle: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param angle 
# \param vtx_offs 
# \param vtx_count 
#
def rotateY(mesh: TriangleMesh3D, angle: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param angle 
# \param vtx_offs 
# \param vtx_count 
#
def rotateZ(mesh: TriangleMesh3D, angle: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param scale_x 
# \param scale_y 
# \param scale_z 
# \param vtx_offs 
# \param vtx_count 
#
def scale(mesh: TriangleMesh3D, scale_x: float, scale_y: float, scale_z: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
#
def subdivideSpherical(mesh: TriangleMesh3D) -> None: pass

##
# \brief 
# \param mesh 
# \param mtx 
# \param vtx_offs 
# \param vtx_count 
#
def transform(mesh: TriangleMesh3D, mtx: Math.Matrix4D, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param trans_x 
# \param trans_y 
# \param trans_z 
# \param vtx_offs 
# \param vtx_count 
#
def translate(mesh: TriangleMesh3D, trans_x: float, trans_y: float, trans_z: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param cntnr 
# \param alignment 
#
def setAlignmentParameter(cntnr: Base.ControlParameterContainer, alignment: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAlignmentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAlignmentParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearAlignmentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setAtomColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearAtomColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param colors 
#
def setAtomColorTableParameter(cntnr: Base.ControlParameterContainer, colors: ColorTable) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomColorTableParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomColorTableParameter(cntnr: Base.ControlParameterContainer) -> ColorTable: pass

##
# \brief 
# \param cntnr 
#
def clearAtomColorTableParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param brush 
#
def setAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer, brush: Brush) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> Brush: pass

##
# \brief 
# \param cntnr 
#
def clearAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param pen 
#
def setAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief 
# \param cntnr 
#
def clearAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setAtomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param margin 
#
def setAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param brush 
#
def setBackgroundBrushParameter(cntnr: Base.ControlParameterContainer, brush: Brush) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBackgroundBrushParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBackgroundBrushParameter(cntnr: Base.ControlParameterContainer) -> Brush: pass

##
# \brief 
# \param cntnr 
#
def clearBackgroundBrushParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setBondColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearBondColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param brush 
#
def setBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer, brush: Brush) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> Brush: pass

##
# \brief 
# \param cntnr 
#
def clearBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param pen 
#
def setBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief 
# \param cntnr 
#
def clearBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setBondLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearBondLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param margin 
#
def setBondLabelMarginParameter(cntnr: Base.ControlParameterContainer, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setBondLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setBondLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param spacing 
#
def setBondLineSpacingParameter(cntnr: Base.ControlParameterContainer, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setBondLineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondLineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondLineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearBondLineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param brk 
#
def setBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer, brk: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param matrial 
#
def setDefaultMaterialParameter(cntnr: Base.ControlParameterContainer, matrial: Material) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasDefaultMaterialParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getDefaultMaterialParameter(cntnr: Base.ControlParameterContainer) -> Material: pass

##
# \brief 
# \param cntnr 
#
def clearDefaultMaterialParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param colors 
#
def setFeatureColorTableParameter(cntnr: Base.ControlParameterContainer, colors: ColorTable) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasFeatureColorTableParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getFeatureColorTableParameter(cntnr: Base.ControlParameterContainer) -> ColorTable: pass

##
# \brief 
# \param cntnr 
#
def clearFeatureColorTableParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param pen 
#
def setGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param padding 
#
def setGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer, padding: float) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param pen 
#
def setGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param margin 
#
def setGridViewMarginParameter(cntnr: Base.ControlParameterContainer, margin: float) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewMarginParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param pen 
#
def setGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setGridViewTextColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewTextColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewTextColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewTextColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setGridViewTextFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasGridViewTextFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getGridViewTextFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearGridViewTextFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param factor 
#
def setOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer, factor: float) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief 
# \param cntnr 
#
def clearOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param alignment 
#
def setReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer, alignment: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param dir 
#
def setReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer, dir: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param layout 
#
def setReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer, layout: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setReactionArrowColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param style 
#
def setReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer, style: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param spacing 
#
def setReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param dir 
#
def setReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer, dir: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param layout 
#
def setReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer, layout: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param margin 
#
def setReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param color 
#
def setReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief 
# \param cntnr 
#
def clearReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param font 
#
def setSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief 
# \param cntnr 
#
def clearSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param size 
#
def setSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowCarbonsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowCarbonsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowCarbonsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowCarbonsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowChargesParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowIsotopesParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowIsotopesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowIsotopesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowIsotopesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowReactionProductsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowReactionProductsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowReactionProductsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowReactionProductsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param show 
#
def setShowStereoBondsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasShowStereoBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getShowStereoBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearShowStereoBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param adjustment 
#
def setSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer, adjustment: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param spacing 
#
def setStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer, spacing: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param width 
#
def setStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief 
# \param cntnr 
#
def clearTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param use 
#
def setUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer, use: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param viewport 
#
def setViewportParameter(cntnr: Base.ControlParameterContainer, viewport: Rectangle2D) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasViewportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getViewportParameter(cntnr: Base.ControlParameterContainer) -> Rectangle2D: pass

##
# \brief 
# \param cntnr 
#
def clearViewportParameter(cntnr: Base.ControlParameterContainer) -> None: pass
