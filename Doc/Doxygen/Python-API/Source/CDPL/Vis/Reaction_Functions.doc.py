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
#
def clearArrowStyle(rxn: Chem.Reaction) -> None: pass

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
# \param style 
#
def setArrowStyle(rxn: Chem.Reaction, style: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearPlusSignSize(rxn: Chem.Reaction) -> None: pass

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
# \param size 
#
def setPlusSignSize(rxn: Chem.Reaction, size: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearArrowHeadWidth(rxn: Chem.Reaction) -> None: pass

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
# \param width 
#
def setArrowHeadWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearPlusSignLineWidth(rxn: Chem.Reaction) -> None: pass

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
# \param width 
#
def setPlusSignLineWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearArrowLineWidth(rxn: Chem.Reaction) -> None: pass

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
# \param width 
#
def setArrowLineWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearArrowShaftWidth(rxn: Chem.Reaction) -> None: pass

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
# \param width 
#
def setArrowShaftWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearArrowHeadLength(rxn: Chem.Reaction) -> None: pass

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
# \param length 
#
def setArrowHeadLength(rxn: Chem.Reaction, length: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearArrowLength(rxn: Chem.Reaction) -> None: pass

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
# \param length 
#
def setArrowLength(rxn: Chem.Reaction, length: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def clearComponentMargin(rxn: Chem.Reaction) -> None: pass

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
# \param margin 
#
def setComponentMargin(rxn: Chem.Reaction, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param rxn 
#
def prepareFor2DVisualization(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
#
def clearAgentLayoutDirection(rxn: Chem.Reaction) -> None: pass

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
# \param dir 
#
def setAgentLayoutDirection(rxn: Chem.Reaction, dir: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearComponentLayoutDirection(rxn: Chem.Reaction) -> None: pass

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
# \param dir 
#
def setComponentLayoutDirection(rxn: Chem.Reaction, dir: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearPlusSignColor(rxn: Chem.Reaction) -> None: pass

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
# \param color 
#
def setPlusSignColor(rxn: Chem.Reaction, color: Color) -> None: pass

##
# \brief 
# \param rxn 
#
def clearArrowColor(rxn: Chem.Reaction) -> None: pass

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
# \param color 
#
def setArrowColor(rxn: Chem.Reaction, color: Color) -> None: pass

##
# \brief 
# \param rxn 
#
def clearShowPlusSigns(rxn: Chem.Reaction) -> None: pass

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
# \param show 
#
def setShowPlusSigns(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearShowProducts(rxn: Chem.Reaction) -> None: pass

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
# \param show 
#
def setShowProducts(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearShowReactants(rxn: Chem.Reaction) -> None: pass

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
# \param show 
#
def setShowReactants(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearShowAgents(rxn: Chem.Reaction) -> None: pass

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
# \param show 
#
def setShowAgents(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearAgentAlignment(rxn: Chem.Reaction) -> None: pass

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
# \param show 
#
def setAgentAlignment(rxn: Chem.Reaction, show: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearAgentLayout(rxn: Chem.Reaction) -> None: pass

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
# \param show 
#
def setAgentLayout(rxn: Chem.Reaction, show: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearComponentLayout(rxn: Chem.Reaction) -> None: pass

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
# \param layout 
#
def setComponentLayout(rxn: Chem.Reaction, layout: int) -> None: pass
