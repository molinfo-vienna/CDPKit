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
# \brief Implements the 2D visualization of chemical structures.
# 
# <tt>StructureView2D</tt> visualizes chemical structures in the form of 2D structure diagrams (also known as skeletal formulas [\ref WSKF] or structural formulas [\ref WSTF]) that allow for an easy perception of important chemical characteristics like constitution, connectivity and stereochemistry.
# 
# Graphical details of the generated structure diagrams (colors, fonts, line-widths etc.) are configurable on a <tt>StructureView2D</tt> instance level by control-parameters and on a visualized data object level by setting appropriate Chem.Atom, Chem.Bond or Chem.MolecularGraph properties. Properties of the visualized data objects have a higher priority than equivalent control-parameters of the <tt>StructureView2D</tt> instance and properties of Chem.Atom or Chem.Bond objects override corresponding properties of the parent Chem.MolecularGraph instance.
# 
# <tt>StructureView2D</tt> supports the following control-parameters:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Description</th></tr>
#  <tr><td>Vis.ControlParameter.VIEWPORT</td><td>Specifies a rectangular viewport area which constrains the location and size of the generated structure diagram</td></tr>
#  <tr><td>Vis.ControlParameter.SIZE_ADJUSTMENT</td><td>Specifies how to adjust the size of the structure diagram relative to the available viewport area</td></tr>
#  <tr><td>Vis.ControlParameter.ALIGNMENT</td><td>Specifies the alignment of the structure diagram within the viewport area</td></tr>
#  <tr><td>Vis.ControlParameter.BACKGROUND_COLOR</td><td>Specifies the backround color of the structure diagram</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_COLOR</td><td>Specifies the color of atom labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_COLOR_TABLE</td><td>Specifies a lookup table for the atom type dependent coloring of atom labels</td></tr>
#  <tr><td>Vis.ControlParameter.USE_CALCULATED_ATOM_COORDINATES</td><td>Specifies whether or not to use calculated atom coordinates</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_LABEL_FONT</td><td>Specifies the font for atom element and query match expression labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_LABEL_SIZE</td><td>Specifies the size of atom element and query match expression labels</td></tr>
#  <tr><td>Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT</td><td>Specifies the font for text labels that show the value of various atomic properties</td></tr>
#  <tr><td>Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE</td><td>Specifies the size of text labels that show the value of various atomic properties</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT</td><td>Specifies the font for atom configuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE</td><td>Specifies the size of atom configuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR</td><td>Specifies the color of atom configuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_CUSTOM_LABEL_FONT</td><td>Specifies the font for atom custom labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_CUSTOM_LABEL_SIZE</td><td>Specifies the size of atom custom labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_CUSTOM_LABEL_COLOR</td><td>Specifies the color of atom custom labels</td></tr>
#  <tr><td>Vis.ControlParameter.ATOM_LABEL_MARGIN</td><td>Specifies the margin of free space around atom labels</td></tr>
#  <tr><td>Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE</td><td>Specifies the size of radical electron dots</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_EXPLICIT_HYDROGENS</td><td>Specifies whether or not to show explicit hydrogen atoms</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_CARBONS</td><td>Specifies whether or not to show the element label of carbon atoms</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_CHARGES</td><td>Specifies whether or not to show the formal charge of atoms</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_ISOTOPES</td><td>Specifies whether or not to show the isotopic mass of atoms</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_HYDROGEN_COUNTS</td><td>Specifies whether or not to show the implicit hydrogen count of connected atoms</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_NON_CARBON_HYDROGEN_COUNTS</td><td>Specifies whether or not to show the implicit hydrogen count of connected non-carbon atoms</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_ATOM_QUERY_INFOS</td><td>Specifies whether or not to show query atom match expressions</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_ATOM_REACTION_INFOS</td><td>Specifies whether or not to show reaction atom-atom mapping numbers</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_RADICAL_ELECTRONS</td><td>Specifies whether or not to draw radical electron dots</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_ATOM_CONFIGURATION_LABELS</td><td>Specifies whether or not to show atom confiuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_ATOM_CUSTOM_LABELS</td><td>Specifies whether or not to show atom confiuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_LENGTH</td><td>Specifies the desired average bond length</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_COLOR</td><td>Specifies the color of bonds</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_LINE_WIDTH</td><td>Specifies the width of bond lines</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_LINE_SPACING</td><td>Specifies the distance between the lines of double and triple bonds</td></tr>
#  <tr><td>Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH</td><td>Specifies the width of wedge-shaped stereo bonds</td></tr>
#  <tr><td>Vis.ControlParameter.STEREO_BOND_HASH_SPACING</td><td>Specifies the distance between the hashes of down stereo bonds</td></tr>
#  <tr><td>Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH</td><td>Specifies the length of the lines in reaction center marks</td></tr>
#  <tr><td>Vis.ControlParameter.REACTION_CENTER_LINE_SPACING</td><td>Specifies the distance between lines in reaction center marks</td></tr>
#  <tr><td>Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH</td><td>Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end</td></tr>
#  <tr><td>Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH</td><td>Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_LABEL_FONT</td><td>Specifies the font for bond labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_LABEL_SIZE</td><td>Specifies the size of bond labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT</td><td>Specifies the font for bond configuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE</td><td>Specifies the size of bond configuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR</td><td>Specifies the color of bond configuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_CUSTOM_LABEL_FONT</td><td>Specifies the font for bond custom labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_CUSTOM_LABEL_SIZE</td><td>Specifies the size of bond custom labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_CUSTOM_LABEL_COLOR</td><td>Specifies the color of bond custom labels</td></tr>
#  <tr><td>Vis.ControlParameter.BOND_LABEL_MARGIN</td><td>Specifies the margin of free space around bond labels</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_BOND_REACTION_INFOS</td><td>Specifies whether or not to draw reaction center marks</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_BOND_QUERY_INFOS</td><td>Specifies whether or not to show query bond match expressions</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_STEREO_BONDS</td><td>Specifies whether or not to draw stereo bonds</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_BOND_CONFIGURATION_LABELS</td><td>Specifies whether or not to show bond confiuration labels</td></tr>
#  <tr><td>Vis.ControlParameter.SHOW_BOND_CUSTOM_LABELS</td><td>Specifies whether or not to show bond confiuration labels</td></tr>
# </table>
# 
# Default values for most of the control-parameters are defined in namespace Vis.ControlParameterDefault.
# 
# Supported Chem.MolecularGraph properties:
# 
# <table>
#  <tr><th>Chem.MolecularGraph Property</th><th>Description</th></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_COLOR_TABLE</td><td>Specifies a lookup table for the atom type dependent coloring of atom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_COLOR</td><td>Specifies the color of atom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_LABEL_FONT</td><td>Specifies the font for atom element and query match expression labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_LABEL_SIZE</td><td>Specifies the size of atom element and query match expression labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT</td><td>Specifies the font for text labels that show the value of various atomic properties</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE</td><td>Specifies the size of text labels that show the value of various atomic properties</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT</td><td>Specifies the font for atom configuration labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE</td><td>Specifies the size of atom configuration labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR</td><td>Specifies the color of atom configuration labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT</td><td>Specifies the font for atom custom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE</td><td>Specifies the size of atom custom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR</td><td>Specifies the color of atom custom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN</td><td>Specifies the margin of free space around atom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE</td><td>Specifies the size of radical electron dots</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_COLOR</td><td>Specifies the color of bonds</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_LINE_WIDTH</td><td>Specifies the width of bond lines</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_LINE_SPACING</td><td>Specifies the distance between the lines of double and triple bonds</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH</td><td>Specifies the width of wedge-shaped stereo bonds</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING</td><td>Specifies the distance between the hashes of down stereo bonds</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH</td><td>Specifies the length of the lines in reaction center marks</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING</td><td>Specifies the distance between the lines in reaction center marks</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH</td><td>Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH</td><td>Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_LABEL_FONT</td><td>Specifies the font for bond labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_LABEL_SIZE</td><td>Specifies the size of bond labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT</td><td>Specifies the font for bond configuration labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE</td><td>Specifies the size of bond configuration labels</td><td>Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR</td><td>Specifies the color of bond configuration labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT</td><td>Specifies the font for bond custom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE</td><td>Specifies the size of bond custom labels</td><td>Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR</td><td>Specifies the color of bond custom labels</td></tr>
#  <tr><td>Vis.MolecularGraphProperty.BOND_LABEL_MARGIN</td><td>Specifies the margin of free space around bond labels</td></tr>
# </table>
# 
# Supported Chem.Atom properties:
# 
# <table>
#  <tr><th>Chem.Atom Property</th><th>Description</th></tr>
#  <tr><td>Vis.AtomProperty.COLOR</td><td>Specifies the color of text labels</td></tr>
#  <tr><td>Vis.AtomProperty.LABEL_FONT</td><td>Specifies the font for atom element and query match expression labels</td></tr>
#  <tr><td>Vis.AtomProperty.LABEL_SIZE</td><td>Specifies the size of atom element and query match expression labels</td></tr>
#  <tr><td>Vis.AtomProperty.SECONDARY_LABEL_FONT</td><td>Specifies the font for text labels that show the value of various atomic properties</td></tr>
#  <tr><td>Vis.AtomProperty.SECONDARY_LABEL_SIZE</td><td>Specifies the size of text labels that show the value of various atomic properties</td></tr>
#  <tr><td>Vis.AtomProperty.LABEL_MARGIN</td><td>Specifies the margin of free space around atom labels</td></tr>
#  <tr><td>Vis.AtomProperty.CONFIGURATION_LABEL_FONT</td><td>Specifies the font for atom configuration labels</td></tr>
#  <tr><td>Vis.AtomProperty.CONFIGURATION_LABEL_SIZE</td><td>Specifies the size of atom configuration labels</td></tr>
#  <tr><td>Vis.AtomProperty.CONFIGURATION_LABEL_COLOR</td><td>Specifies the color of atom configuration labels</td></tr>
#  <tr><td>Vis.AtomProperty.CUSTOM_LABEL_FONT</td><td>Specifies the font for atom custom labels</td></tr>
#  <tr><td>Vis.AtomProperty.CUSTOM_LABEL_SIZE</td><td>Specifies the size of atom custom labels</td></tr>
#  <tr><td>Vis.AtomProperty.CUSTOM_LABEL_COLOR</td><td>Specifies the color of atom custom labels</td></tr>
#  <tr><td>Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE</td><td>Specifies the size of radical electron dots</td></tr>
# </table>
# 
# Supported Chem.Bond properties:
# 
# <table>
#  <tr><th>Chem.Bond Property</th><th>Description</th></tr>
#  <tr><td>Vis.BondProperty.COLOR</td><td>Specifies the color of the bond</td></tr>
#  <tr><td>Vis.BondProperty.LINE_WIDTH</td><td>Specifies the width of bond lines</td></tr>
#  <tr><td>Vis.BondProperty.LINE_SPACING</td><td>Specifies the distance between the lines of double and triple bonds</td></tr>
#  <tr><td>Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH</td><td>Specifies the width of wedge-shaped stereo bonds</td></tr>
#  <tr><td>Vis.BondProperty.STEREO_BOND_HASH_SPACING</td><td>Specifies the distance between the hashes of down stereo bonds</td></tr>
#  <tr><td>Vis.BondProperty.REACTION_CENTER_LINE_LENGTH</td><td>Specifies the length of the lines in reaction center marks</td></tr>
#  <tr><td>Vis.BondProperty.REACTION_CENTER_LINE_SPACING</td><td>Specifies the distance between the lines in reaction center marks</td></tr>
#  <tr><td>Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH</td><td>Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end</td></tr>
#  <tr><td>Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH</td><td>Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end</td></tr>
#  <tr><td>Vis.BondProperty.LABEL_FONT</td><td>Specifies the font for bond labels</td></tr>
#  <tr><td>Vis.BondProperty.LABEL_SIZE</td><td>Specifies the size of bond labels</td></tr>
#  <tr><td>Vis.BondProperty.LABEL_MARGIN</td><td>Specifies the margin of free space around bond labels</td></tr>
#  <tr><td>Vis.BondProperty.CONFIGURATION_LABEL_FONT</td><td>Specifies the font for bond configuration labels</td></tr>
#  <tr><td>Vis.BondProperty.CONFIGURATION_LABEL_SIZE</td><td>Specifies the size of bond configuration labels</td></tr>
#  <tr><td>Vis.BondProperty.CONFIGURATION_LABEL_COLOR</td><td>Specifies the color of bond configuration labels</td></tr>
#  <tr><td>Vis.BondProperty.CUSTOM_LABEL_FONT</td><td>Specifies the font for bond custom labels</td></tr>
#  <tr><td>Vis.BondProperty.CUSTOM_LABEL_SIZE</td><td>Specifies the size of bond custom labels</td></tr>
#  <tr><td>Vis.BondProperty.CUSTOM_LABEL_COLOR</td><td>Specifies the color of bond custom labels</td></tr>
# </table>
# 
class StructureView2D(View2D):

    ##
    # \brief Initializes the \e %StructureView2D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs and initializes a <tt>StructureView2D</tt> instance for the visualization of the chemical structure specified by <em>molgraph</em>.
    # 
    # \param molgraph A reference to the Chem.MolecularGraph object to visualize.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Specifies the chemical structure to visualize.
    # 
    # If the chemical structure or a property has changed <em>after</em> this method has been called for a Chem.MolecularGraph object, the method needs to be called again for the object to make the changes visible.
    # 
    # \param molgraph A reference to the Chem.MolecularGraph object to visualize, or <em>None</em>.
    # 
    def setStructure(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns a reference to the visualized chemical structure.
    # 
    # \return A reference to the visualized Chem.MolecularGraph object, or <em>None</em> if none was specified.
    # 
    def getStructure() -> Chem.MolecularGraph: pass

    ##
    # \brief Returns a reference to the used font metrics object.
    # 
    # \return A reference to the used font metrics object, or <em>None</em> if none was specified.
    # 
    def getFontMetrics() -> FontMetrics: pass

    structure = property(getStructure, setStructure)

    fontMetrics = property(getFontMetrics, setFontMetrics)
