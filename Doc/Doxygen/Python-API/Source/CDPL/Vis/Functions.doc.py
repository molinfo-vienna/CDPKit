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
# \brief Tells whether the Vis.ReactionProperty.AGENT_ALIGNMENT property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAgentAlignment(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.AGENT_ALIGNMENT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.AGENT_ALIGNMENT property.
# 
def getAgentAlignment(rxn: Chem.Reaction) -> int: pass

##
# \brief Clears the value of the Vis.ReactionProperty.AGENT_ALIGNMENT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearAgentAlignment(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.AGENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em> to <em>dir</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param dir The new agent layout direction (see Vis.LayoutDirection).
# 
def setAgentLayoutDirection(rxn: Chem.Reaction, dir: int) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.AGENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAgentLayoutDirection(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.AGENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.AGENT_LAYOUT_DIRECTION property.
# 
def getAgentLayoutDirection(rxn: Chem.Reaction) -> int: pass

##
# \brief Clears the value of the Vis.ReactionProperty.AGENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearAgentLayoutDirection(rxn: Chem.Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param show 
#
def setAgentLayout(rxn: Chem.Reaction, show: int) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.AGENT_LAYOUT property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAgentLayout(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.AGENT_LAYOUT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.AGENT_LAYOUT property.
# 
def getAgentLayout(rxn: Chem.Reaction) -> int: pass

##
# \brief Clears the value of the Vis.ReactionProperty.AGENT_LAYOUT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearAgentLayout(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_COLOR property of the reaction <em>rxn</em> to <em>color</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param color The new arrow color.
# 
def setArrowColor(rxn: Chem.Reaction, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_COLOR property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowColor(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_COLOR property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_COLOR property.
# 
def getArrowColor(rxn: Chem.Reaction) -> Color: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_COLOR property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowColor(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_HEAD_LENGTH property of the reaction <em>rxn</em> to <em>length</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param length The new arrow head length.
# 
def setArrowHeadLength(rxn: Chem.Reaction, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_HEAD_LENGTH property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowHeadLength(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_HEAD_LENGTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_HEAD_LENGTH property.
# 
def getArrowHeadLength(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_HEAD_LENGTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowHeadLength(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_HEAD_WIDTH property of the reaction <em>rxn</em> to <em>width</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param width The new arrow head width.
# 
def setArrowHeadWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_HEAD_WIDTH property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowHeadWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_HEAD_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_HEAD_WIDTH property.
# 
def getArrowHeadWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_HEAD_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowHeadWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_LENGTH property of the reaction <em>rxn</em> to <em>length</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param length The new arrow length.
# 
def setArrowLength(rxn: Chem.Reaction, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_LENGTH property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowLength(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_LENGTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_LENGTH property.
# 
def getArrowLength(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_LENGTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowLength(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_LINE_WIDTH property of the reaction <em>rxn</em> to <em>width</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param width The new arrow outline width.
# 
def setArrowLineWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_LINE_WIDTH property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowLineWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_LINE_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_LINE_WIDTH property.
# 
def getArrowLineWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_LINE_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowLineWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_SHAFT_WIDTH property of the reaction <em>rxn</em> to <em>width</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param width The new arrow shaft width.
# 
def setArrowShaftWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_SHAFT_WIDTH property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowShaftWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_SHAFT_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_SHAFT_WIDTH property.
# 
def getArrowShaftWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_SHAFT_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowShaftWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.ARROW_STYLE property of the reaction <em>rxn</em> to <em>style</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param style The new arrow style (see Vis.ArrowStyle).
# 
def setArrowStyle(rxn: Chem.Reaction, style: int) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.ARROW_STYLE property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasArrowStyle(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.ARROW_STYLE property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.ARROW_STYLE property.
# 
def getArrowStyle(rxn: Chem.Reaction) -> int: pass

##
# \brief Clears the value of the Vis.ReactionProperty.ARROW_STYLE property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearArrowStyle(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_COLOR property of the molecular graph <em>molgraph</em> to <em>color</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param color The new value of the Vis.MolecularGraphProperty.ATOM_COLOR property.
# 
def setAtomColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_COLOR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_COLOR property.
# 
def getAtomColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearAtomColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property of the molecular graph <em>molgraph</em> to <em>colors</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param colors The new value of the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property.
# 
def setAtomColorTable(molgraph: Chem.MolecularGraph, colors: ColorTable) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomColorTable(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property.
# 
def getAtomColorTable(molgraph: Chem.MolecularGraph) -> ColorTable: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearAtomColorTable(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em> to <em>color</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param color The new value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property.
# 
# \since 1.2
# 
def setAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property.
# 
# \since 1.1
# 
def setAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property. 
# 
# \since 1.1
# 
def getAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.1
# 
def clearAtomConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property.
# 
# \since 1.1
# 
def setAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property. 
# 
# \since 1.1
# 
def getAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.1
# 
def clearAtomConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em> to <em>color</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param color The new value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property.
# 
# \since 1.2
# 
def setAtomCustomLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomCustomLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property.
# 
# \since 1.2
# 
def setAtomCustomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property. 
# 
# \since 1.2
# 
def getAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomCustomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property.
# 
# \since 1.2
# 
def setAtomCustomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property. 
# 
# \since 1.2
# 
def getAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomCustomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em> to <em>brush</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param brush The new value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property.
# 
# \since 1.2
# 
def setAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property. 
# 
# \since 1.2
# 
def getAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> Brush: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em> to <em>pen</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param pen The new value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property.
# 
# \since 1.2
# 
def setAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property. 
# 
# \since 1.2
# 
def getAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> Pen: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property.
# 
# \since 1.2
# 
def setAtomHighlightAreaSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomHighlightAreaSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property. 
# 
# \since 1.2
# 
def getAtomHighlightAreaSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearAtomHighlightAreaSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property.
# 
def setAtomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property.
# 
def getAtomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearAtomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property of the molecular graph <em>molgraph</em> to <em>margin</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param margin The new value of the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property.
# 
def setAtomLabelMargin(molgraph: Chem.MolecularGraph, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomLabelMargin(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property.
# 
def getAtomLabelMargin(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearAtomLabelMargin(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property.
# 
def setAtomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property.
# 
def getAtomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearAtomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_COLOR property of the molecular graph <em>molgraph</em> to <em>color</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param color The new value of the Vis.MolecularGraphProperty.BOND_COLOR property.
# 
def setBondColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_COLOR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasBondColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_COLOR property.
# 
def getBondColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearBondColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em> to <em>color</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param color The new value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property.
# 
# \since 1.2
# 
def setBondConfigurationLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondConfigurationLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property.
# 
# \since 1.1
# 
def setBondConfigurationLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property. 
# 
# \since 1.1
# 
def getBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.1
# 
def clearBondConfigurationLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property.
# 
# \since 1.1
# 
def setBondConfigurationLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property. 
# 
# \since 1.1
# 
def getBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.1
# 
def clearBondConfigurationLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em> to <em>color</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param color The new value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property.
# 
# \since 1.2
# 
def setBondCustomLabelColor(molgraph: Chem.MolecularGraph, color: Color) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> Color: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondCustomLabelColor(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property.
# 
# \since 1.2
# 
def setBondCustomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property. 
# 
# \since 1.2
# 
def getBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondCustomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property.
# 
# \since 1.2
# 
def setBondCustomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property. 
# 
# \since 1.2
# 
def getBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondCustomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em> to <em>brush</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param brush The new value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property.
# 
# \since 1.2
# 
def setBondHighlightAreaBrush(molgraph: Chem.MolecularGraph, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property. 
# 
# \since 1.2
# 
def getBondHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> Brush: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondHighlightAreaBrush(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em> to <em>pen</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param pen The new value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property.
# 
# \since 1.2
# 
def setBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property. 
# 
# \since 1.2
# 
def getBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> Pen: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondHighlightAreaOutlinePen(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property of the molecular graph <em>molgraph</em> to <em>width</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param width The new value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property.
# 
# \since 1.2
# 
def setBondHighlightAreaWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondHighlightAreaWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property. 
# 
# \since 1.2
# 
def getBondHighlightAreaWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearBondHighlightAreaWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.BOND_LABEL_FONT property.
# 
def setBondLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasBondLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_LABEL_FONT property.
# 
def getBondLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearBondLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property of the molecular graph <em>molgraph</em> to <em>margin</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param margin The new value of the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property.
# 
def setBondLabelMargin(molgraph: Chem.MolecularGraph, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasBondLabelMargin(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property.
# 
def getBondLabelMargin(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearBondLabelMargin(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property.
# 
def setBondLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasBondLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property.
# 
def getBondLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearBondLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_LINE_SPACING property of the molecular graph <em>molgraph</em> to <em>spacing</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param spacing The new value of the Vis.MolecularGraphProperty.BOND_LINE_SPACING property.
# 
def setBondLineSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_LINE_SPACING property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasBondLineSpacing(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_LINE_SPACING property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_LINE_SPACING property.
# 
def getBondLineSpacing(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_LINE_SPACING property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearBondLineSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property of the molecular graph <em>molgraph</em> to <em>width</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param width The new value of the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property.
# 
def setBondLineWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasBondLineWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property.
# 
def getBondLineWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearBondLineWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.COLOR property of the atom <em>atom</em> to <em>color</em>.
# 
# \param atom The atom for which to set the property value.
# \param color The new value of the Vis.AtomProperty.COLOR property.
# 
def setColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.COLOR property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasColor(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.COLOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.COLOR property.
# 
def getColor(atom: Chem.Atom) -> Color: pass

##
# \brief Clears the value of the Vis.AtomProperty.COLOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearColor(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.COLOR property of the bond <em>bond</em> to <em>color</em>.
# 
# \param bond The bond for which to set the property value.
# \param color The new value of the Vis.BondProperty.COLOR property.
# 
def setColor(bond: Chem.Bond, color: Color) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.COLOR property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasColor(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.COLOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.COLOR property.
# 
def getColor(bond: Chem.Bond) -> Color: pass

##
# \brief Clears the value of the Vis.BondProperty.COLOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearColor(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.COMPONENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em> to <em>dir</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param dir The new layout direction (see Vis.LayoutDirection).
# 
def setComponentLayoutDirection(rxn: Chem.Reaction, dir: int) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.COMPONENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponentLayoutDirection(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.COMPONENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.COMPONENT_LAYOUT_DIRECTION property.
# 
def getComponentLayoutDirection(rxn: Chem.Reaction) -> int: pass

##
# \brief Clears the value of the Vis.ReactionProperty.COMPONENT_LAYOUT_DIRECTION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearComponentLayoutDirection(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.COMPONENT_LAYOUT property of the reaction <em>rxn</em> to <em>layout</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param layout The new layout style (see Vis.LayoutStyle).
# 
def setComponentLayout(rxn: Chem.Reaction, layout: int) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.COMPONENT_LAYOUT property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponentLayout(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.COMPONENT_LAYOUT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.COMPONENT_LAYOUT property.
# 
def getComponentLayout(rxn: Chem.Reaction) -> int: pass

##
# \brief Clears the value of the Vis.ReactionProperty.COMPONENT_LAYOUT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearComponentLayout(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.COMPONENT_MARGIN property of the reaction <em>rxn</em> to <em>margin</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param margin The new component margin.
# 
def setComponentMargin(rxn: Chem.Reaction, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.COMPONENT_MARGIN property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponentMargin(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.COMPONENT_MARGIN property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.COMPONENT_MARGIN property.
# 
def getComponentMargin(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.COMPONENT_MARGIN property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearComponentMargin(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CONFIGURATION_LABEL_COLOR property of the atom <em>atom</em> to <em>color</em>.
# 
# \param atom The atom for which to set the property value.
# \param color The new value of the Vis.AtomProperty.CONFIGURATION_LABEL_COLOR property.
# 
# \since 1.2
# 
def setConfigurationLabelColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CONFIGURATION_LABEL_COLOR property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasConfigurationLabelColor(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CONFIGURATION_LABEL_COLOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CONFIGURATION_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getConfigurationLabelColor(atom: Chem.Atom) -> Color: pass

##
# \brief Clears the value of the Vis.AtomProperty.CONFIGURATION_LABEL_COLOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearConfigurationLabelColor(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property of the bond <em>bond</em> to <em>color</em>.
# 
# \param bond The bond for which to set the property value.
# \param color The new value of the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property.
# 
# \since 1.2
# 
def setConfigurationLabelColor(bond: Chem.Bond, color: Color) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasConfigurationLabelColor(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getConfigurationLabelColor(bond: Chem.Bond) -> Color: pass

##
# \brief Clears the value of the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearConfigurationLabelColor(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CONFIGURATION_LABEL_FONT property of the atom <em>atom</em> to <em>font</em>.
# 
# \param atom The atom for which to set the property value.
# \param font The new value of the Vis.AtomProperty.CONFIGURATION_LABEL_FONT property.
# 
# \since 1.1
# 
def setConfigurationLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CONFIGURATION_LABEL_FONT property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasConfigurationLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CONFIGURATION_LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CONFIGURATION_LABEL_FONT property. 
# 
# \since 1.1
# 
def getConfigurationLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief Clears the value of the Vis.AtomProperty.CONFIGURATION_LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.1
# 
def clearConfigurationLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CONFIGURATION_LABEL_FONT property of the bond <em>bond</em> to <em>font</em>.
# 
# \param bond The bond for which to set the property value.
# \param font The new value of the Vis.BondProperty.CONFIGURATION_LABEL_FONT property.
# 
# \since 1.1
# 
def setConfigurationLabelFont(bond: Chem.Bond, font: Font) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CONFIGURATION_LABEL_FONT property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasConfigurationLabelFont(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CONFIGURATION_LABEL_FONT property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CONFIGURATION_LABEL_FONT property. 
# 
# \since 1.1
# 
def getConfigurationLabelFont(bond: Chem.Bond) -> Font: pass

##
# \brief Clears the value of the Vis.BondProperty.CONFIGURATION_LABEL_FONT property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.1
# 
def clearConfigurationLabelFont(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CONFIGURATION_LABEL_SIZE property of the atom <em>atom</em> to <em>size</em>.
# 
# \param atom The atom for which to set the property value.
# \param size The new value of the Vis.AtomProperty.CONFIGURATION_LABEL_SIZE property.
# 
# \since 1.1
# 
def setConfigurationLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CONFIGURATION_LABEL_SIZE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasConfigurationLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CONFIGURATION_LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CONFIGURATION_LABEL_SIZE property. 
# 
# \since 1.1
# 
def getConfigurationLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.AtomProperty.CONFIGURATION_LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.1
# 
def clearConfigurationLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property of the bond <em>bond</em> to <em>size</em>.
# 
# \param bond The bond for which to set the property value.
# \param size The new value of the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property.
# 
# \since 1.1
# 
def setConfigurationLabelSize(bond: Chem.Bond, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasConfigurationLabelSize(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property. 
# 
# \since 1.1
# 
def getConfigurationLabelSize(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.1
# 
def clearConfigurationLabelSize(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CUSTOM_LABEL property of the atom <em>atom</em> to <em>text</em>.
# 
# \param atom The atom for which to set the property value.
# \param text The new value of the Vis.AtomProperty.CUSTOM_LABEL property.
# 
# \since 1.2
# 
def setCustomLabel(atom: Chem.Atom, text: str) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CUSTOM_LABEL property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabel(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CUSTOM_LABEL property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CUSTOM_LABEL property. 
# 
# \since 1.2
# 
def getCustomLabel(atom: Chem.Atom) -> object: pass

##
# \brief Clears the value of the Vis.AtomProperty.CUSTOM_LABEL property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabel(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CUSTOM_LABEL property of the bond <em>bond</em> to <em>text</em>.
# 
# \param bond The bond for which to set the property value.
# \param text The new value of the Vis.BondProperty.CUSTOM_LABEL property.
# 
# \since 1.2
# 
def setCustomLabel(bond: Chem.Bond, text: str) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CUSTOM_LABEL property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabel(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CUSTOM_LABEL property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CUSTOM_LABEL property. 
# 
# \since 1.2
# 
def getCustomLabel(bond: Chem.Bond) -> object: pass

##
# \brief Clears the value of the Vis.BondProperty.CUSTOM_LABEL property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabel(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CUSTOM_LABEL_COLOR property of the atom <em>atom</em> to <em>color</em>.
# 
# \param atom The atom for which to set the property value.
# \param color The new value of the Vis.AtomProperty.CUSTOM_LABEL_COLOR property.
# 
# \since 1.2
# 
def setCustomLabelColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CUSTOM_LABEL_COLOR property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabelColor(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CUSTOM_LABEL_COLOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CUSTOM_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getCustomLabelColor(atom: Chem.Atom) -> Color: pass

##
# \brief Clears the value of the Vis.AtomProperty.CUSTOM_LABEL_COLOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabelColor(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CUSTOM_LABEL_COLOR property of the bond <em>bond</em> to <em>color</em>.
# 
# \param bond The bond for which to set the property value.
# \param color The new value of the Vis.BondProperty.CUSTOM_LABEL_COLOR property.
# 
# \since 1.2
# 
def setCustomLabelColor(bond: Chem.Bond, color: Color) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CUSTOM_LABEL_COLOR property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabelColor(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CUSTOM_LABEL_COLOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CUSTOM_LABEL_COLOR property. 
# 
# \since 1.2
# 
def getCustomLabelColor(bond: Chem.Bond) -> Color: pass

##
# \brief Clears the value of the Vis.BondProperty.CUSTOM_LABEL_COLOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabelColor(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CUSTOM_LABEL_FONT property of the atom <em>atom</em> to <em>font</em>.
# 
# \param atom The atom for which to set the property value.
# \param font The new value of the Vis.AtomProperty.CUSTOM_LABEL_FONT property.
# 
# \since 1.2
# 
def setCustomLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CUSTOM_LABEL_FONT property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CUSTOM_LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CUSTOM_LABEL_FONT property. 
# 
# \since 1.2
# 
def getCustomLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief Clears the value of the Vis.AtomProperty.CUSTOM_LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CUSTOM_LABEL_FONT property of the bond <em>bond</em> to <em>font</em>.
# 
# \param bond The bond for which to set the property value.
# \param font The new value of the Vis.BondProperty.CUSTOM_LABEL_FONT property.
# 
# \since 1.2
# 
def setCustomLabelFont(bond: Chem.Bond, font: Font) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CUSTOM_LABEL_FONT property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabelFont(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CUSTOM_LABEL_FONT property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CUSTOM_LABEL_FONT property. 
# 
# \since 1.2
# 
def getCustomLabelFont(bond: Chem.Bond) -> Font: pass

##
# \brief Clears the value of the Vis.BondProperty.CUSTOM_LABEL_FONT property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabelFont(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.CUSTOM_LABEL_SIZE property of the atom <em>atom</em> to <em>size</em>.
# 
# \param atom The atom for which to set the property value.
# \param size The new value of the Vis.AtomProperty.CUSTOM_LABEL_SIZE property.
# 
# \since 1.2
# 
def setCustomLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.CUSTOM_LABEL_SIZE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.CUSTOM_LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.CUSTOM_LABEL_SIZE property. 
# 
# \since 1.2
# 
def getCustomLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.AtomProperty.CUSTOM_LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.CUSTOM_LABEL_SIZE property of the bond <em>bond</em> to <em>size</em>.
# 
# \param bond The bond for which to set the property value.
# \param size The new value of the Vis.BondProperty.CUSTOM_LABEL_SIZE property.
# 
# \since 1.2
# 
def setCustomLabelSize(bond: Chem.Bond, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.CUSTOM_LABEL_SIZE property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCustomLabelSize(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.CUSTOM_LABEL_SIZE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.CUSTOM_LABEL_SIZE property. 
# 
# \since 1.2
# 
def getCustomLabelSize(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.CUSTOM_LABEL_SIZE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearCustomLabelSize(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property of the bond <em>bond</em> to <em>length</em>.
# 
# \param bond The bond for which to set the property value.
# \param length The new value of the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property.
# 
def setDoubleBondTrimLength(bond: Chem.Bond, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasDoubleBondTrimLength(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property.
# 
def getDoubleBondTrimLength(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearDoubleBondTrimLength(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em> to <em>length</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param length The new value of the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property.
# 
def setDoubleBondTrimLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property.
# 
def getDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearDoubleBondTrimLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.HIGHLIGHT_AREA_BRUSH property of the atom <em>atom</em> to <em>brush</em>.
# 
# \param atom The atom for which to set the property value.
# \param brush The new value of the Vis.AtomProperty.HIGHLIGHT_AREA_BRUSH property.
# 
# \since 1.2
# 
def setHighlightAreaBrush(atom: Chem.Atom, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.HIGHLIGHT_AREA_BRUSH property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightAreaBrush(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.HIGHLIGHT_AREA_BRUSH property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.HIGHLIGHT_AREA_BRUSH property. 
# 
# \since 1.2
# 
def getHighlightAreaBrush(atom: Chem.Atom) -> Brush: pass

##
# \brief Clears the value of the Vis.AtomProperty.HIGHLIGHT_AREA_BRUSH property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightAreaBrush(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property of the bond <em>bond</em> to <em>brush</em>.
# 
# \param bond The bond for which to set the property value.
# \param brush The new value of the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property.
# 
# \since 1.2
# 
def setHighlightAreaBrush(bond: Chem.Bond, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightAreaBrush(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property. 
# 
# \since 1.2
# 
def getHighlightAreaBrush(bond: Chem.Bond) -> Brush: pass

##
# \brief Clears the value of the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightAreaBrush(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the atom <em>atom</em> to <em>pen</em>.
# 
# \param atom The atom for which to set the property value.
# \param pen The new value of the Vis.AtomProperty.HIGHLIGHT_AREA_OUTLINE_PEN property.
# 
# \since 1.2
# 
def setHighlightAreaOutlinePen(atom: Chem.Atom, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightAreaOutlinePen(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.HIGHLIGHT_AREA_OUTLINE_PEN property. 
# 
# \since 1.2
# 
def getHighlightAreaOutlinePen(atom: Chem.Atom) -> Pen: pass

##
# \brief Clears the value of the Vis.AtomProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightAreaOutlinePen(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the bond <em>bond</em> to <em>pen</em>.
# 
# \param bond The bond for which to set the property value.
# \param pen The new value of the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property.
# 
# \since 1.2
# 
def setHighlightAreaOutlinePen(bond: Chem.Bond, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightAreaOutlinePen(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property. 
# 
# \since 1.2
# 
def getHighlightAreaOutlinePen(bond: Chem.Bond) -> Pen: pass

##
# \brief Clears the value of the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightAreaOutlinePen(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property of the molecular graph <em>molgraph</em> to <em>width</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param width The new value of the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property.
# 
# \since 1.2
# 
def setHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property. 
# 
# \since 1.2
# 
def getHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightAreaOutlineWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.HIGHLIGHTED_FLAG property of the atom <em>atom</em> to <em>highlighted</em>.
# 
# \param atom The atom for which to set the property value.
# \param highlighted The new value of the Vis.AtomProperty.HIGHLIGHTED_FLAG property.
# 
# \since 1.2
# 
def setHighlightedFlag(atom: Chem.Atom, highlighted: bool) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.HIGHLIGHTED_FLAG property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightedFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.HIGHLIGHTED_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.HIGHLIGHTED_FLAG property. 
# 
# \since 1.2
# 
def getHighlightedFlag(atom: Chem.Atom) -> bool: pass

##
# \brief Clears the value of the Vis.AtomProperty.HIGHLIGHTED_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightedFlag(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.HIGHLIGHTED_FLAG property of the bond <em>bond</em> to <em>highlighted</em>.
# 
# \param bond The bond for which to set the property value.
# \param highlighted The new value of the Vis.BondProperty.HIGHLIGHTED_FLAG property.
# 
# \since 1.2
# 
def setHighlightedFlag(bond: Chem.Bond, highlighted: bool) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.HIGHLIGHTED_FLAG property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightedFlag(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.HIGHLIGHTED_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.HIGHLIGHTED_FLAG property. 
# 
# \since 1.2
# 
def getHighlightedFlag(bond: Chem.Bond) -> bool: pass

##
# \brief Clears the value of the Vis.BondProperty.HIGHLIGHTED_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
# \since 1.2
# 
def clearHighlightedFlag(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.LABEL_FONT property of the atom <em>atom</em> to <em>font</em>.
# 
# \param atom The atom for which to set the property value.
# \param font The new value of the Vis.AtomProperty.LABEL_FONT property.
# 
def setLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.LABEL_FONT property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.LABEL_FONT property.
# 
def getLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief Clears the value of the Vis.AtomProperty.LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.LABEL_FONT property of the bond <em>bond</em> to <em>font</em>.
# 
# \param bond The bond for which to set the property value.
# \param font The new value of the Vis.BondProperty.LABEL_FONT property.
# 
def setLabelFont(bond: Chem.Bond, font: Font) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.LABEL_FONT property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLabelFont(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.LABEL_FONT property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.LABEL_FONT property.
# 
def getLabelFont(bond: Chem.Bond) -> Font: pass

##
# \brief Clears the value of the Vis.BondProperty.LABEL_FONT property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearLabelFont(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.LABEL_MARGIN property of the atom <em>atom</em> to <em>margin</em>.
# 
# \param atom The atom for which to set the property value.
# \param margin The new value of the Vis.AtomProperty.LABEL_MARGIN property.
# 
def setLabelMargin(atom: Chem.Atom, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.LABEL_MARGIN property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLabelMargin(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.LABEL_MARGIN property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.LABEL_MARGIN property.
# 
def getLabelMargin(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.AtomProperty.LABEL_MARGIN property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearLabelMargin(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.LABEL_MARGIN property of the bond <em>bond</em> to <em>margin</em>.
# 
# \param bond The bond for which to set the property value.
# \param margin The new value of the Vis.BondProperty.LABEL_MARGIN property.
# 
def setLabelMargin(bond: Chem.Bond, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.LABEL_MARGIN property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLabelMargin(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.LABEL_MARGIN property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.LABEL_MARGIN property.
# 
def getLabelMargin(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.LABEL_MARGIN property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearLabelMargin(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.LABEL_SIZE property of the atom <em>atom</em> to <em>size</em>.
# 
# \param atom The atom for which to set the property value.
# \param size The new value of the Vis.AtomProperty.LABEL_SIZE property.
# 
def setLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.LABEL_SIZE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.LABEL_SIZE property.
# 
def getLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.AtomProperty.LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.LABEL_SIZE property of the bond <em>bond</em> to <em>size</em>.
# 
# \param bond The bond for which to set the property value.
# \param size The new value of the Vis.BondProperty.LABEL_SIZE property.
# 
def setLabelSize(bond: Chem.Bond, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.LABEL_SIZE property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLabelSize(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.LABEL_SIZE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.LABEL_SIZE property.
# 
def getLabelSize(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.LABEL_SIZE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearLabelSize(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.LINE_SPACING property of the bond <em>bond</em> to <em>spacing</em>.
# 
# \param bond The bond for which to set the property value.
# \param spacing The new value of the Vis.BondProperty.LINE_SPACING property.
# 
def setLineSpacing(bond: Chem.Bond, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.LINE_SPACING property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLineSpacing(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.LINE_SPACING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.LINE_SPACING property.
# 
def getLineSpacing(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.LINE_SPACING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearLineSpacing(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.LINE_WIDTH property of the bond <em>bond</em> to <em>width</em>.
# 
# \param bond The bond for which to set the property value.
# \param width The new value of the Vis.BondProperty.LINE_WIDTH property.
# 
def setLineWidth(bond: Chem.Bond, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.LINE_WIDTH property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasLineWidth(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.LINE_WIDTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.LINE_WIDTH property.
# 
def getLineWidth(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.LINE_WIDTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearLineWidth(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param obj 
# \param material 
#
def setMaterial(obj: Object3D, material: Material) -> None: pass

##
# \brief Tells whether the Vis.Object3DProperty.MATERIAL property of the 3D object <em>obj</em> is set.
# 
# \param obj The 3D object for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasMaterial(obj: Object3D) -> bool: pass

##
# \brief Returns the value of the Vis.Object3DProperty.MATERIAL property of the 3D object <em>obj</em>.
# 
# \param obj The 3D object for which to return the property value.
# 
# \return The value of the Vis.Object3DProperty.MATERIAL property. 
# 
# \since 1.3
# 
def getMaterial(obj: Object3D) -> Material: pass

##
# \brief Clears the value of the Vis.Object3DProperty.MATERIAL property of the 3D object <em>obj</em>.
# 
# \param obj The 3D object for which to clear the property value.
# 
# \since 1.3
# 
def clearMaterial(obj: Object3D) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.PLUS_SIGN_COLOR property of the reaction <em>rxn</em> to <em>color</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param color The new plus-sign color.
# 
def setPlusSignColor(rxn: Chem.Reaction, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.PLUS_SIGN_COLOR property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasPlusSignColor(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.PLUS_SIGN_COLOR property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.PLUS_SIGN_COLOR property.
# 
def getPlusSignColor(rxn: Chem.Reaction) -> Color: pass

##
# \brief Clears the value of the Vis.ReactionProperty.PLUS_SIGN_COLOR property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearPlusSignColor(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.PLUS_SIGN_LINE_WIDTH property of the reaction <em>rxn</em> to <em>width</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param width The new plus-sign line width.
# 
def setPlusSignLineWidth(rxn: Chem.Reaction, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.PLUS_SIGN_LINE_WIDTH property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasPlusSignLineWidth(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.PLUS_SIGN_LINE_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.PLUS_SIGN_LINE_WIDTH property.
# 
def getPlusSignLineWidth(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.PLUS_SIGN_LINE_WIDTH property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearPlusSignLineWidth(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.PLUS_SIGN_SIZE property of the reaction <em>rxn</em> to <em>size</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param size The new plus-sign size.
# 
def setPlusSignSize(rxn: Chem.Reaction, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.PLUS_SIGN_SIZE property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasPlusSignSize(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.PLUS_SIGN_SIZE property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.PLUS_SIGN_SIZE property.
# 
def getPlusSignSize(rxn: Chem.Reaction) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.ReactionProperty.PLUS_SIGN_SIZE property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearPlusSignSize(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE property of the atom <em>atom</em> to <em>size</em>.
# 
# \param atom The atom for which to set the property value.
# \param size The new value of the Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE property.
# 
def setRadicalElectronDotSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasRadicalElectronDotSize(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE property.
# 
def getRadicalElectronDotSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearRadicalElectronDotSize(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property.
# 
def setRadicalElectronDotSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property.
# 
def getRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearRadicalElectronDotSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property of the bond <em>bond</em> to <em>length</em>.
# 
# \param bond The bond for which to set the property value.
# \param length The new value of the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property.
# 
def setReactionCenterLineLength(bond: Chem.Bond, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterLineLength(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property.
# 
def getReactionCenterLineLength(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearReactionCenterLineLength(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property of the molecular graph <em>molgraph</em> to <em>length</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param length The new value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property.
# 
def setReactionCenterLineLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property.
# 
def getReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearReactionCenterLineLength(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property of the bond <em>bond</em> to <em>spacing</em>.
# 
# \param bond The bond for which to set the property value.
# \param spacing The new value of the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property.
# 
def setReactionCenterLineSpacing(bond: Chem.Bond, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterLineSpacing(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property.
# 
def getReactionCenterLineSpacing(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearReactionCenterLineSpacing(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property of the molecular graph <em>molgraph</em> to <em>spacing</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param spacing The new value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property.
# 
def setReactionCenterLineSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property.
# 
def getReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearReactionCenterLineSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em> to <em>font</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param font The new value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property.
# 
def setSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph, font: Font) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property.
# 
def getSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> Font: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearSecondaryAtomLabelFont(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> to <em>size</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param size The new value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property.
# 
def setSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property.
# 
def getSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearSecondaryAtomLabelSize(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.SECONDARY_LABEL_FONT property of the atom <em>atom</em> to <em>font</em>.
# 
# \param atom The atom for which to set the property value.
# \param font The new value of the Vis.AtomProperty.SECONDARY_LABEL_FONT property.
# 
def setSecondaryLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.SECONDARY_LABEL_FONT property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSecondaryLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.SECONDARY_LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.SECONDARY_LABEL_FONT property.
# 
def getSecondaryLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief Clears the value of the Vis.AtomProperty.SECONDARY_LABEL_FONT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearSecondaryLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.AtomProperty.SECONDARY_LABEL_SIZE property of the atom <em>atom</em> to <em>size</em>.
# 
# \param atom The atom for which to set the property value.
# \param size The new value of the Vis.AtomProperty.SECONDARY_LABEL_SIZE property.
# 
def setSecondaryLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.AtomProperty.SECONDARY_LABEL_SIZE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSecondaryLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the Vis.AtomProperty.SECONDARY_LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The value of the Vis.AtomProperty.SECONDARY_LABEL_SIZE property.
# 
def getSecondaryLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.AtomProperty.SECONDARY_LABEL_SIZE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearSecondaryLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the Vis.Object3DProperty.SHAPE property of the 3D object <em>obj</em> to <em>shape</em>.
# 
# \param obj The 3D object for which to set the property value.
# \param shape The new value of the Vis.Object3DProperty.SHAPE property.
# 
# \since 1.3
# 
def setShape(obj: Object3D, shape: Shape3D) -> None: pass

##
# \brief Tells whether the Vis.Object3DProperty.SHAPE property of the 3D object <em>obj</em> is set.
# 
# \param obj The 3D object for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasShape(obj: Object3D) -> bool: pass

##
# \brief Returns the value of the Vis.Object3DProperty.SHAPE property of the 3D object <em>obj</em>.
# 
# \param obj The 3D object for which to return the property value.
# 
# \return The value of the Vis.Object3DProperty.SHAPE property. 
# 
# \since 1.3
# 
def getShape(obj: Object3D) -> object: pass

##
# \brief Clears the value of the Vis.Object3DProperty.SHAPE property of the 3D object <em>obj</em>.
# 
# \param obj The 3D object for which to clear the property value.
# 
# \since 1.3
# 
def clearShape(obj: Object3D) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.SHOW_AGENTS property of the reaction <em>rxn</em> to <em>show</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param show <tt>True</tt> to show the agents, and <tt>False</tt> to hide them.
# 
def setShowAgents(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.SHOW_AGENTS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasShowAgents(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.SHOW_AGENTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.SHOW_AGENTS property.
# 
def getShowAgents(rxn: Chem.Reaction) -> bool: pass

##
# \brief Clears the value of the Vis.ReactionProperty.SHOW_AGENTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearShowAgents(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.SHOW_PLUS_SIGNS property of the reaction <em>rxn</em> to <em>show</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param show <tt>True</tt> to draw the '+' signs, and <tt>False</tt> to hide them.
# 
def setShowPlusSigns(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.SHOW_PLUS_SIGNS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasShowPlusSigns(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.SHOW_PLUS_SIGNS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.SHOW_PLUS_SIGNS property.
# 
def getShowPlusSigns(rxn: Chem.Reaction) -> bool: pass

##
# \brief Clears the value of the Vis.ReactionProperty.SHOW_PLUS_SIGNS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearShowPlusSigns(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.SHOW_PRODUCTS property of the reaction <em>rxn</em> to <em>show</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param show <tt>True</tt> to show the products, and <tt>False</tt> to hide them.
# 
def setShowProducts(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.SHOW_PRODUCTS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasShowProducts(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.SHOW_PRODUCTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.SHOW_PRODUCTS property.
# 
def getShowProducts(rxn: Chem.Reaction) -> bool: pass

##
# \brief Clears the value of the Vis.ReactionProperty.SHOW_PRODUCTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearShowProducts(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.ReactionProperty.SHOW_REACTANTS property of the reaction <em>rxn</em> to <em>show</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param show <tt>True</tt> to show the reactants, and <tt>False</tt> to hide them.
# 
def setShowReactants(rxn: Chem.Reaction, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ReactionProperty.SHOW_REACTANTS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasShowReactants(rxn: Chem.Reaction) -> bool: pass

##
# \brief Returns the value of the Vis.ReactionProperty.SHOW_REACTANTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The value of the Vis.ReactionProperty.SHOW_REACTANTS property.
# 
def getShowReactants(rxn: Chem.Reaction) -> bool: pass

##
# \brief Clears the value of the Vis.ReactionProperty.SHOW_REACTANTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearShowReactants(rxn: Chem.Reaction) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.STEREO_BOND_HASH_SPACING property of the bond <em>bond</em> to <em>spacing</em>.
# 
# \param bond The bond for which to set the property value.
# \param spacing The new value of the Vis.BondProperty.STEREO_BOND_HASH_SPACING property.
# 
def setStereoBondHashSpacing(bond: Chem.Bond, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.STEREO_BOND_HASH_SPACING property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoBondHashSpacing(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.STEREO_BOND_HASH_SPACING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.STEREO_BOND_HASH_SPACING property.
# 
def getStereoBondHashSpacing(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.STEREO_BOND_HASH_SPACING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearStereoBondHashSpacing(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property of the molecular graph <em>molgraph</em> to <em>spacing</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param spacing The new value of the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property.
# 
def setStereoBondHashSpacing(molgraph: Chem.MolecularGraph, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property.
# 
def getStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearStereoBondHashSpacing(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property of the bond <em>bond</em> to <em>width</em>.
# 
# \param bond The bond for which to set the property value.
# \param width The new value of the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property.
# 
def setStereoBondWedgeWidth(bond: Chem.Bond, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoBondWedgeWidth(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property.
# 
def getStereoBondWedgeWidth(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearStereoBondWedgeWidth(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property of the molecular graph <em>molgraph</em> to <em>width</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param width The new value of the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property.
# 
def setStereoBondWedgeWidth(molgraph: Chem.MolecularGraph, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property.
# 
def getStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearStereoBondWedgeWidth(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Sets the value of the Vis.Object3DProperty.TRANSFORMATION_MATRIX property of the 3D object <em>obj</em> to <em>mtx</em>.
# 
# \param obj The 3D object for which to set the property value.
# \param mtx The new value of the Vis.Object3DProperty.TRANSFORMATION_MATRIX property.
# 
# \since 1.3
# 
def setTransformationMatrix(obj: Object3D, mtx: Math.Matrix4D) -> None: pass

##
# \brief Tells whether the Vis.Object3DProperty.TRANSFORMATION_MATRIX property of the 3D object <em>obj</em> is set.
# 
# \param obj The 3D object for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasTransformationMatrix(obj: Object3D) -> bool: pass

##
# \brief Returns the value of the Vis.Object3DProperty.TRANSFORMATION_MATRIX property of the 3D object <em>obj</em>.
# 
# \param obj The 3D object for which to return the property value.
# 
# \return The value of the Vis.Object3DProperty.TRANSFORMATION_MATRIX property. 
# 
# \since 1.3
# 
def getTransformationMatrix(obj: Object3D) -> Math.Matrix4D: pass

##
# \brief Clears the value of the Vis.Object3DProperty.TRANSFORMATION_MATRIX property of the 3D object <em>obj</em>.
# 
# \param obj The 3D object for which to clear the property value.
# 
# \since 1.3
# 
def clearTransformationMatrix(obj: Object3D) -> None: pass

##
# \brief Sets the value of the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property of the bond <em>bond</em> to <em>length</em>.
# 
# \param bond The bond for which to set the property value.
# \param length The new value of the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property.
# 
def setTripleBondTrimLength(bond: Chem.Bond, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasTripleBondTrimLength(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The value of the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property.
# 
def getTripleBondTrimLength(bond: Chem.Bond) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearTripleBondTrimLength(bond: Chem.Bond) -> None: pass

##
# \brief Sets the value of the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em> to <em>length</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param length The new value of the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property.
# 
def setTripleBondTrimLength(molgraph: Chem.MolecularGraph, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasTripleBondTrimLength(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The value of the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property.
# 
def getTripleBondTrimLength(molgraph: Chem.MolecularGraph) -> SizeSpecification: pass

##
# \brief Clears the value of the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
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
# \brief Prepares <em>molgraph</em> for 2D visualization by perceiving all properties (aromaticity, hybridization, rings, stereo, etc.) that downstream 2D-rendering code expects to be set.
# 
# \param molgraph The molecular graph to prepare (modified in place).
# 
# \since 1.3
# 
def prepareFor2DVisualization(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Prepares <em>rxn</em> for 2D visualization by perceiving all properties (aromaticity, hybridization, rings, stereo, etc.) that downstream 2D-rendering code expects to be set on each reaction component.
# 
# \param rxn The reaction to prepare (modified in place).
# 
# \since 1.3
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
# \brief Sets the value of the Vis.ControlParameter.ALIGNMENT parameter of <em>cntnr</em> to <em>alignment</em>.
# 
# \param cntnr The control-parameter container to update.
# \param alignment The new alignment flag combination (see Vis.Alignment).
# 
def setAlignmentParameter(cntnr: Base.ControlParameterContainer, alignment: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ALIGNMENT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasAlignmentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ALIGNMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ALIGNMENT parameter.
# 
def getAlignmentParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.ALIGNMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearAlignmentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new atom color.
# 
def setAtomColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasAtomColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_COLOR parameter.
# 
def getAtomColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearAtomColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_COLOR_TABLE parameter of <em>cntnr</em> to <em>colors</em>.
# 
# \param cntnr The control-parameter container to update.
# \param colors The new atom color table.
# 
def setAtomColorTableParameter(cntnr: Base.ControlParameterContainer, colors: ColorTable) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_COLOR_TABLE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasAtomColorTableParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_COLOR_TABLE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_COLOR_TABLE parameter.
# 
def getAtomColorTableParameter(cntnr: Base.ControlParameterContainer) -> ColorTable: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_COLOR_TABLE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearAtomColorTableParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new atom configuration label color.
# 
# \since 1.2
# 
def setAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR parameter. 
# 
# \since 1.2
# 
def getAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new atom configuration label font.
# 
# \since 1.1
# 
def setAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT parameter. 
# 
# \since 1.1
# 
def getAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearAtomConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new atom configuration label size.
# 
# \since 1.1
# 
def setAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE parameter. 
# 
# \since 1.1
# 
def getAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearAtomConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new atom custom label color.
# 
# \since 1.2
# 
def setAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR parameter. 
# 
# \since 1.2
# 
def getAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new atom custom label font.
# 
# \since 1.2
# 
def setAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT parameter. 
# 
# \since 1.2
# 
def getAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new atom custom label size.
# 
# \since 1.2
# 
def setAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE parameter. 
# 
# \since 1.2
# 
def getAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_BRUSH parameter of <em>cntnr</em> to <em>brush</em>.
# 
# \param cntnr The control-parameter container to update.
# \param brush The new atom highlight area brush.
# 
# \since 1.2
# 
def setAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_BRUSH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_BRUSH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_BRUSH parameter. 
# 
# \since 1.2
# 
def getAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> Brush: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_BRUSH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter of <em>cntnr</em> to <em>pen</em>.
# 
# \param cntnr The control-parameter container to update.
# \param pen The new atom highlight area outline pen.
# 
# \since 1.2
# 
def setAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter. 
# 
# \since 1.2
# 
def getAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new atom highlight area size.
# 
# \since 1.2
# 
def setAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_SIZE parameter. 
# 
# \since 1.2
# 
def getAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_HIGHLIGHT_AREA_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearAtomHighlightAreaSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new atom label font.
# 
def setAtomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_LABEL_FONT parameter.
# 
def getAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_LABEL_MARGIN parameter of <em>cntnr</em> to <em>margin</em>.
# 
# \param cntnr The control-parameter container to update.
# \param margin The new atom label margin.
# 
def setAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_LABEL_MARGIN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_LABEL_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_LABEL_MARGIN parameter.
# 
def getAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_LABEL_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearAtomLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ATOM_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new atom label size.
# 
def setAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ATOM_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ATOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ATOM_LABEL_SIZE parameter.
# 
def getAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.ATOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BACKGROUND_BRUSH parameter of <em>cntnr</em> to <em>brush</em>.
# 
# \param cntnr The control-parameter container to update.
# \param brush The new background brush.
# 
# \since 1.2
# 
def setBackgroundBrushParameter(cntnr: Base.ControlParameterContainer, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BACKGROUND_BRUSH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBackgroundBrushParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BACKGROUND_BRUSH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BACKGROUND_BRUSH parameter. 
# 
# \since 1.2
# 
def getBackgroundBrushParameter(cntnr: Base.ControlParameterContainer) -> Brush: pass

##
# \brief Removes the Vis.ControlParameter.BACKGROUND_BRUSH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBackgroundBrushParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new bond color.
# 
def setBondColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_COLOR parameter.
# 
def getBondColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.BOND_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new bond configuration label color.
# 
# \since 1.2
# 
def setBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR parameter. 
# 
# \since 1.2
# 
def getBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondConfigurationLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new bond configuration label font.
# 
# \since 1.1
# 
def setBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT parameter. 
# 
# \since 1.1
# 
def getBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearBondConfigurationLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new bond configuration label size.
# 
# \since 1.1
# 
def setBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE parameter. 
# 
# \since 1.1
# 
def getBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearBondConfigurationLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new bond custom label color.
# 
# \since 1.2
# 
def setBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR parameter. 
# 
# \since 1.2
# 
def getBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondCustomLabelColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new bond custom label font.
# 
# \since 1.2
# 
def setBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT parameter. 
# 
# \since 1.2
# 
def getBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondCustomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new bond custom label size.
# 
# \since 1.2
# 
def setBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE parameter. 
# 
# \since 1.2
# 
def getBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondCustomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_BRUSH parameter of <em>cntnr</em> to <em>brush</em>.
# 
# \param cntnr The control-parameter container to update.
# \param brush The new bond highlight area brush.
# 
# \since 1.2
# 
def setBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer, brush: Brush) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_BRUSH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_BRUSH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_BRUSH parameter. 
# 
# \since 1.2
# 
def getBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> Brush: pass

##
# \brief Removes the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_BRUSH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondHighlightAreaBrushParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter of <em>cntnr</em> to <em>pen</em>.
# 
# \param cntnr The control-parameter container to update.
# \param pen The new bond highlight area outline pen.
# 
# \since 1.2
# 
def setBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter. 
# 
# \since 1.2
# 
def getBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief Removes the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_OUTLINE_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondHighlightAreaOutlinePenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new bond highlight area width.
# 
# \since 1.2
# 
def setBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_WIDTH parameter. 
# 
# \since 1.2
# 
def getBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_HIGHLIGHT_AREA_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBondHighlightAreaWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new bond label font.
# 
def setBondLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_LABEL_FONT parameter.
# 
def getBondLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.BOND_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_LABEL_MARGIN parameter of <em>cntnr</em> to <em>margin</em>.
# 
# \param cntnr The control-parameter container to update.
# \param margin The new bond label margin.
# 
def setBondLabelMarginParameter(cntnr: Base.ControlParameterContainer, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_LABEL_MARGIN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_LABEL_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_LABEL_MARGIN parameter.
# 
def getBondLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_LABEL_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondLabelMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new bond label size.
# 
def setBondLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_LABEL_SIZE parameter.
# 
def getBondLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_LENGTH parameter of <em>cntnr</em> to <em>length</em>.
# 
# \param cntnr The control-parameter container to update.
# \param length The new average bond length.
# 
def setBondLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_LENGTH parameter.
# 
def getBondLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_LINE_SPACING parameter of <em>cntnr</em> to <em>spacing</em>.
# 
# \param cntnr The control-parameter container to update.
# \param spacing The new bond line spacing.
# 
def setBondLineSpacingParameter(cntnr: Base.ControlParameterContainer, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_LINE_SPACING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_LINE_SPACING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_LINE_SPACING parameter.
# 
def getBondLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_LINE_SPACING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BOND_LINE_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new bond line width.
# 
def setBondLineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BOND_LINE_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondLineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BOND_LINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BOND_LINE_WIDTH parameter.
# 
def getBondLineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.BOND_LINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondLineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter of <em>cntnr</em> to <em>brk</em>.
# 
# \param cntnr The control-parameter container to update.
# \param brk <tt>True</tt> to break the outline at incident highlighted bonds, and <tt>False</tt> otherwise.
# 
# \since 1.2
# 
def setBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer, brk: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter. 
# 
# \since 1.2
# 
def getBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearBreakAtomHighlightAreaOutlineParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param matrial 
#
def setDefaultMaterialParameter(cntnr: Base.ControlParameterContainer, matrial: Material) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.DEFAULT_MATERIAL parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasDefaultMaterialParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.DEFAULT_MATERIAL parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.DEFAULT_MATERIAL parameter. 
# 
# \since 1.3
# 
def getDefaultMaterialParameter(cntnr: Base.ControlParameterContainer) -> Material: pass

##
# \brief Removes the Vis.ControlParameter.DEFAULT_MATERIAL parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.3
# 
def clearDefaultMaterialParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH parameter of <em>cntnr</em> to <em>length</em>.
# 
# \param cntnr The control-parameter container to update.
# \param length The new double bond trim length.
# 
def setDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH parameter.
# 
def getDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearDoubleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ENABLE_ATOM_HIGHLIGHTING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ENABLE_ATOM_HIGHLIGHTING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ENABLE_ATOM_HIGHLIGHTING parameter. 
# 
# \since 1.2
# 
def getEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.ENABLE_ATOM_HIGHLIGHTING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearEnableAtomHighlightingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.ENABLE_BOND_HIGHLIGHTING parameter of <em>cntnr</em> to <em>enable</em>.
# 
# \param cntnr The control-parameter container to update.
# \param enable <tt>True</tt> to enable bond highlighting, and <tt>False</tt> to disable it.
# 
# \since 1.2
# 
def setEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.ENABLE_BOND_HIGHLIGHTING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.ENABLE_BOND_HIGHLIGHTING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.ENABLE_BOND_HIGHLIGHTING parameter. 
# 
# \since 1.2
# 
def getEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.ENABLE_BOND_HIGHLIGHTING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearEnableBondHighlightingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.FEATURE_COLOR_TABLE parameter of <em>cntnr</em> to <em>colors</em>.
# 
# \param cntnr The control-parameter container to update.
# \param colors The new pharmacophoric-feature color table.
# 
# \since 1.3
# 
def setFeatureColorTableParameter(cntnr: Base.ControlParameterContainer, colors: ColorTable) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.FEATURE_COLOR_TABLE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasFeatureColorTableParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.FEATURE_COLOR_TABLE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.FEATURE_COLOR_TABLE parameter. 
# 
# \since 1.3
# 
def getFeatureColorTableParameter(cntnr: Base.ControlParameterContainer) -> ColorTable: pass

##
# \brief Removes the Vis.ControlParameter.FEATURE_COLOR_TABLE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.3
# 
def clearFeatureColorTableParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_BORDER_PEN parameter of <em>cntnr</em> to <em>pen</em>.
# 
# \param cntnr The control-parameter container to update.
# \param pen The new grid view border pen.
# 
# \since 1.2
# 
def setGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_BORDER_PEN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_BORDER_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_BORDER_PEN parameter. 
# 
# \since 1.2
# 
def getGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_BORDER_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewBorderPenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_CELL_PADDING parameter of <em>cntnr</em> to <em>padding</em>.
# 
# \param cntnr The control-parameter container to update.
# \param padding The new grid view cell padding.
# 
# \since 1.2
# 
def setGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer, padding: float) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_CELL_PADDING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_CELL_PADDING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_CELL_PADDING parameter. 
# 
# \since 1.2
# 
def getGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_CELL_PADDING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewCellPaddingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN parameter of <em>cntnr</em> to <em>pen</em>.
# 
# \param cntnr The control-parameter container to update.
# \param pen The new grid view column separator pen.
# 
# \since 1.2
# 
def setGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN parameter. 
# 
# \since 1.2
# 
def getGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewColumnSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_MARGIN parameter of <em>cntnr</em> to <em>margin</em>.
# 
# \param cntnr The control-parameter container to update.
# \param margin The new grid view outer margin.
# 
# \since 1.2
# 
def setGridViewMarginParameter(cntnr: Base.ControlParameterContainer, margin: float) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_MARGIN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_MARGIN parameter. 
# 
# \since 1.2
# 
def getGridViewMarginParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN parameter of <em>cntnr</em> to <em>pen</em>.
# 
# \param cntnr The control-parameter container to update.
# \param pen The new grid view row separator pen.
# 
# \since 1.2
# 
def setGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer, pen: Pen) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN parameter. 
# 
# \since 1.2
# 
def getGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> Pen: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewRowSeparatorPenParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_TEXT_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new grid view text color.
# 
# \since 1.2
# 
def setGridViewTextColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_TEXT_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewTextColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_TEXT_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_TEXT_COLOR parameter. 
# 
# \since 1.2
# 
def getGridViewTextColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_TEXT_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewTextColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.GRID_VIEW_TEXT_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new grid view text font.
# 
# \since 1.2
# 
def setGridViewTextFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.GRID_VIEW_TEXT_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasGridViewTextFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.GRID_VIEW_TEXT_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.GRID_VIEW_TEXT_FONT parameter. 
# 
# \since 1.2
# 
def getGridViewTextFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.GRID_VIEW_TEXT_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearGridViewTextFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.HIGHLIGHT_AREA_OUTLINE_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new highlight area outline width.
# 
# \since 1.2
# 
def setHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.HIGHLIGHT_AREA_OUTLINE_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.HIGHLIGHT_AREA_OUTLINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.HIGHLIGHT_AREA_OUTLINE_WIDTH parameter. 
# 
# \since 1.2
# 
def getHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.HIGHLIGHT_AREA_OUTLINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearHighlightAreaOutlineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.OUTPUT_SCALING_FACTOR parameter of <em>cntnr</em> to <em>factor</em>.
# 
# \param cntnr The control-parameter container to update.
# \param factor The new parameter value.
# 
# \since 1.2
# 
def setOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer, factor: float) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.OUTPUT_SCALING_FACTOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.OUTPUT_SCALING_FACTOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.OUTPUT_SCALING_FACTOR parameter. 
# 
# \since 1.2
# 
def getOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief Removes the Vis.ControlParameter.OUTPUT_SCALING_FACTOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearOutputScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new radical electron dot size.
# 
def setRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE parameter.
# 
def getRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearRadicalElectronDotSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_AGENT_ALIGNMENT parameter of <em>cntnr</em> to <em>alignment</em>.
# 
# \param cntnr The control-parameter container to update.
# \param alignment The new agent alignment (see Vis.Alignment).
# 
def setReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer, alignment: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_AGENT_ALIGNMENT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_AGENT_ALIGNMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_AGENT_ALIGNMENT parameter.
# 
def getReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_AGENT_ALIGNMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionAgentAlignmentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION parameter of <em>cntnr</em> to <em>dir</em>.
# 
# \param cntnr The control-parameter container to update.
# \param dir The new agent layout direction (see Vis.LayoutDirection).
# 
def setReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer, dir: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION parameter.
# 
def getReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_AGENT_LAYOUT_DIRECTION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionAgentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_AGENT_LAYOUT parameter of <em>cntnr</em> to <em>layout</em>.
# 
# \param cntnr The control-parameter container to update.
# \param layout The new agent layout style (see Vis.LayoutStyle).
# 
def setReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer, layout: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_AGENT_LAYOUT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_AGENT_LAYOUT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_AGENT_LAYOUT parameter.
# 
def getReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_AGENT_LAYOUT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionAgentLayoutParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_ARROW_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new arrow color.
# 
def setReactionArrowColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_COLOR parameter.
# 
def getReactionArrowColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH parameter of <em>cntnr</em> to <em>length</em>.
# 
# \param cntnr The control-parameter container to update.
# \param length The new arrow head length.
# 
def setReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH parameter.
# 
def getReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_HEAD_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowHeadLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new arrow head width.
# 
def setReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH parameter.
# 
def getReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_HEAD_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowHeadWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param length 
#
def setReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_LENGTH parameter.
# 
def getReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new arrow outline width.
# 
def setReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH parameter.
# 
def getReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_LINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowLineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new arrow shaft width.
# 
def setReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH parameter.
# 
def getReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_SHAFT_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowShaftWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_ARROW_STYLE parameter of <em>cntnr</em> to <em>style</em>.
# 
# \param cntnr The control-parameter container to update.
# \param style The new arrow style (see Vis.ArrowStyle).
# 
def setReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer, style: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_ARROW_STYLE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_ARROW_STYLE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_ARROW_STYLE parameter.
# 
def getReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_ARROW_STYLE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionArrowStyleParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH parameter of <em>cntnr</em> to <em>length</em>.
# 
# \param cntnr The control-parameter container to update.
# \param length The new reaction center line length.
# 
def setReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH parameter.
# 
def getReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionCenterLineLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_CENTER_LINE_SPACING parameter of <em>cntnr</em> to <em>spacing</em>.
# 
# \param cntnr The control-parameter container to update.
# \param spacing The new reaction center line spacing.
# 
def setReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_CENTER_LINE_SPACING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_CENTER_LINE_SPACING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_CENTER_LINE_SPACING parameter.
# 
def getReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_CENTER_LINE_SPACING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionCenterLineSpacingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION parameter of <em>cntnr</em> to <em>dir</em>.
# 
# \param cntnr The control-parameter container to update.
# \param dir The new layout direction (see Vis.LayoutDirection).
# 
def setReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer, dir: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION parameter.
# 
def getReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT_DIRECTION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionComponentLayoutDirectionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT parameter of <em>cntnr</em> to <em>layout</em>.
# 
# \param cntnr The control-parameter container to update.
# \param layout The new layout style (see Vis.LayoutStyle).
# 
def setReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer, layout: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT parameter.
# 
def getReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_COMPONENT_LAYOUT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionComponentLayoutParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_COMPONENT_MARGIN parameter of <em>cntnr</em> to <em>margin</em>.
# 
# \param cntnr The control-parameter container to update.
# \param margin The new component margin.
# 
def setReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer, margin: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_COMPONENT_MARGIN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_COMPONENT_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_COMPONENT_MARGIN parameter.
# 
def getReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_COMPONENT_MARGIN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionComponentMarginParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR parameter of <em>cntnr</em> to <em>color</em>.
# 
# \param cntnr The control-parameter container to update.
# \param color The new plus-sign color.
# 
def setReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer, color: Color) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR parameter.
# 
def getReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer) -> Color: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_PLUS_SIGN_COLOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionPlusSignColorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new plus-sign line width.
# 
def setReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH parameter.
# 
def getReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_PLUS_SIGN_LINE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionPlusSignLineWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new plus-sign size.
# 
def setReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE parameter.
# 
def getReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.REACTION_PLUS_SIGN_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearReactionPlusSignSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT parameter of <em>cntnr</em> to <em>font</em>.
# 
# \param cntnr The control-parameter container to update.
# \param font The new secondary atom label font.
# 
def setSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer, font: Font) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT parameter.
# 
def getSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> Font: pass

##
# \brief Removes the Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearSecondaryAtomLabelFontParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE parameter of <em>cntnr</em> to <em>size</em>.
# 
# \param cntnr The control-parameter container to update.
# \param size The new secondary atom label size.
# 
def setSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer, size: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE parameter.
# 
def getSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearSecondaryAtomLabelSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show atom configuration descriptor labels, and <tt>False</tt> to hide them.
# 
# \since 1.1
# 
def setShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS parameter. 
# 
# \since 1.1
# 
def getShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearShowAtomConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show atom custom text labels, and <tt>False</tt> to hide them.
# 
# \since 1.2
# 
def setShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS parameter. 
# 
# \since 1.2
# 
def getShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearShowAtomCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show query atom match expressions, and <tt>False</tt> to hide them.
# 
def setShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS parameter.
# 
def getShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowAtomQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show reaction atom-atom mapping numbers, and <tt>False</tt> to hide them.
# 
def setShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS parameter.
# 
def getShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowAtomReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show bond configuration descriptor labels, and <tt>False</tt> to hide them.
# 
# \since 1.1
# 
def setShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS parameter. 
# 
# \since 1.1
# 
def getShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearShowBondConfigurationLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show bond custom text labels, and <tt>False</tt> to hide them.
# 
# \since 1.2
# 
def setShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS parameter. 
# 
# \since 1.2
# 
def getShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearShowBondCustomLabelsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_BOND_QUERY_INFOS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show query bond match expressions, and <tt>False</tt> to hide them.
# 
def setShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_BOND_QUERY_INFOS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_BOND_QUERY_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_BOND_QUERY_INFOS parameter.
# 
def getShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_BOND_QUERY_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowBondQueryInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_BOND_REACTION_INFOS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to draw reaction center marks, and <tt>False</tt> to hide them.
# 
def setShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_BOND_REACTION_INFOS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_BOND_REACTION_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_BOND_REACTION_INFOS parameter.
# 
def getShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_BOND_REACTION_INFOS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowBondReactionInfosParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_CARBONS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show carbon element labels, and <tt>False</tt> to hide them.
# 
def setShowCarbonsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_CARBONS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowCarbonsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_CARBONS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_CARBONS parameter.
# 
def getShowCarbonsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_CARBONS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowCarbonsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_CHARGES parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show formal charges, and <tt>False</tt> to hide them.
# 
def setShowChargesParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_CHARGES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_CHARGES parameter.
# 
def getShowChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show explicit hydrogens, and <tt>False</tt> to hide them.
# 
def setShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS parameter.
# 
def getShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowExplicitHydrogensParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_FEATURE_CENTERS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show feature center spheres, and <tt>False</tt> to hide them.
# 
# \since 1.3
# 
def setShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_FEATURE_CENTERS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_FEATURE_CENTERS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_FEATURE_CENTERS parameter. 
# 
# \since 1.3
# 
def getShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_FEATURE_CENTERS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.3
# 
def clearShowFeatureCentersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_HYDROGEN_COUNTS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show implicit hydrogen counts, and <tt>False</tt> to hide them.
# 
def setShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_HYDROGEN_COUNTS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_HYDROGEN_COUNTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_HYDROGEN_COUNTS parameter.
# 
def getShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_HYDROGEN_COUNTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_ISOTOPES parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show isotopic mass values, and <tt>False</tt> to hide them.
# 
def setShowIsotopesParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_ISOTOPES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowIsotopesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_ISOTOPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_ISOTOPES parameter.
# 
def getShowIsotopesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_ISOTOPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowIsotopesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show non-carbon implicit hydrogen counts, and <tt>False</tt> to hide them.
# 
def setShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS parameter.
# 
def getShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowNonCarbonHydrogenCountsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_RADICAL_ELECTRONS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show radical electron dots, and <tt>False</tt> to hide them.
# 
def setShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_RADICAL_ELECTRONS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_RADICAL_ELECTRONS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_RADICAL_ELECTRONS parameter.
# 
def getShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_RADICAL_ELECTRONS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowRadicalElectronsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_REACTION_AGENTS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show the reaction agents, and <tt>False</tt> to hide them.
# 
def setShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_REACTION_AGENTS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_REACTION_AGENTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_REACTION_AGENTS parameter.
# 
def getShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_REACTION_AGENTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowReactionAgentsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to draw the '+' signs, and <tt>False</tt> to hide them.
# 
def setShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS parameter.
# 
def getShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_REACTION_PLUS_SIGNS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowReactionPlusSignsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_REACTION_PRODUCTS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show the reaction products, and <tt>False</tt> to hide them.
# 
def setShowReactionProductsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_REACTION_PRODUCTS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowReactionProductsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_REACTION_PRODUCTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_REACTION_PRODUCTS parameter.
# 
def getShowReactionProductsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_REACTION_PRODUCTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowReactionProductsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_REACTION_REACTANTS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to show the reaction reactants, and <tt>False</tt> to hide them.
# 
def setShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_REACTION_REACTANTS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_REACTION_REACTANTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_REACTION_REACTANTS parameter.
# 
def getShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_REACTION_REACTANTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowReactionReactantsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SHOW_STEREO_BONDS parameter of <em>cntnr</em> to <em>show</em>.
# 
# \param cntnr The control-parameter container to update.
# \param show <tt>True</tt> to draw stereo bonds, and <tt>False</tt> to disable stereo bond rendering.
# 
def setShowStereoBondsParameter(cntnr: Base.ControlParameterContainer, show: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SHOW_STEREO_BONDS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasShowStereoBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SHOW_STEREO_BONDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SHOW_STEREO_BONDS parameter.
# 
def getShowStereoBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.SHOW_STEREO_BONDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearShowStereoBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.SIZE_ADJUSTMENT parameter of <em>cntnr</em> to <em>adjustment</em>.
# 
# \param cntnr The control-parameter container to update.
# \param adjustment The new size-adjustment policy (see Vis.SizeAdjustment).
# 
def setSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer, adjustment: int) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.SIZE_ADJUSTMENT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.SIZE_ADJUSTMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.SIZE_ADJUSTMENT parameter.
# 
def getSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Vis.ControlParameter.SIZE_ADJUSTMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearSizeAdjustmentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.STEREO_BOND_HASH_SPACING parameter of <em>cntnr</em> to <em>spacing</em>.
# 
# \param cntnr The control-parameter container to update.
# \param spacing The new stereo bond hash spacing.
# 
def setStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer, spacing: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.STEREO_BOND_HASH_SPACING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.STEREO_BOND_HASH_SPACING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.STEREO_BOND_HASH_SPACING parameter.
# 
def getStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.STEREO_BOND_HASH_SPACING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearStereoBondHashSpacingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH parameter of <em>cntnr</em> to <em>width</em>.
# 
# \param cntnr The control-parameter container to update.
# \param width The new stereo bond wedge width.
# 
def setStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer, width: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH parameter.
# 
def getStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearStereoBondWedgeWidthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH parameter of <em>cntnr</em> to <em>length</em>.
# 
# \param cntnr The control-parameter container to update.
# \param length The new triple bond trim length.
# 
def setTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer, length: SizeSpecification) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH parameter.
# 
def getTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> SizeSpecification: pass

##
# \brief Removes the Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearTripleBondTrimLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES parameter of <em>cntnr</em> to <em>use</em>.
# 
# \param cntnr The control-parameter container to update.
# \param use <tt>True</tt> to use calculated atom coordinates, and <tt>False</tt> to use stored ones when available.
# 
def setUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer, use: bool) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES parameter.
# 
def getUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearUseCalculatedAtomCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Vis.ControlParameter.VIEWPORT parameter of <em>cntnr</em> to <em>viewport</em>.
# 
# \param cntnr The control-parameter container to update.
# \param viewport The new viewport rectangle.
# 
def setViewportParameter(cntnr: Base.ControlParameterContainer, viewport: Rectangle2D) -> None: pass

##
# \brief Tells whether the Vis.ControlParameter.VIEWPORT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container to query.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasViewportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Vis.ControlParameter.VIEWPORT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container to query.
# 
# \return The value of the Vis.ControlParameter.VIEWPORT parameter.
# 
def getViewportParameter(cntnr: Base.ControlParameterContainer) -> Rectangle2D: pass

##
# \brief Removes the Vis.ControlParameter.VIEWPORT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearViewportParameter(cntnr: Base.ControlParameterContainer) -> None: pass
