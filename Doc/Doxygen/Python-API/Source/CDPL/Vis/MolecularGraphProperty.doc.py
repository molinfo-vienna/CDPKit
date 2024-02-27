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
# \brief Provides keys for built-in Chem.MolecularGraph properties.
# 
class MolecularGraphProperty(Boost.Python.instance):

    ##
    # \brief Specifies the color of atom labels.
    # 
    # The specified color takes precedence over the color specified by the parameter Vis.ControlParameter.ATOM_COLOR.
    # 
    # <b>Value Type:</b> Vis.Color \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.COLOR.
    # 
    ATOM_COLOR = CDPL.Base.LookupKey('ATOM_COLOR')

    ##
    # \brief Specifies a lookup table for the atom type dependent coloring of atom labels.
    # 
    # If the color for a particular atom type is missing, the color specified by Vis.ControlParameter.ATOM_COLOR or Vis.MolecularGraphProperty.ATOM_COLOR will be used instead. The specified color takes precedence over the table specified by the parameter Vis.ControlParameter.ATOM_COLOR_TABLE.
    # 
    # <b>Value Type:</b> Vis.ColorTable.SharedPointer \note The color table will only be considered if the Chem.Atom property Vis.AtomProperty.COLOR has not been set.
    # 
    ATOM_COLOR_TABLE = CDPL.Base.LookupKey('ATOM_COLOR_TABLE')

    ##
    # \brief Specifies the size of radical electron dots.
    # 
    # The dot size can either be specified as an absolute value or as a scaling factor for the primary label size given by Vis.ControlParameter.ATOM_LABEL_SIZE, Vis.MolecularGraphProperty.ATOM_LABEL_SIZE or Vis.AtomProperty.LABEL_SIZE. If input-scaling is enabled, the dot diameter will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the diameter will follow the size change of the chemical structure during viewport size adjustment. The specified size takes precedence over the size specified by the parameter Vis.ControlParameter.RADICAL_ELECTRON_DOT_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.RADICAL_ELECTRON_DOT_SIZE.
    # 
    RADICAL_ELECTRON_DOT_SIZE = CDPL.Base.LookupKey('RADICAL_ELECTRON_DOT_SIZE')

    ##
    # \brief Specifies the font for atom element and query match expression labels.
    # 
    # The specified font takes precedence over the font specified by the parameter Vis.ControlParameter.ATOM_LABEL_FONT.
    # 
    # <b>Value Type:</b> Vis.Font \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.LABEL_FONT.
    # 
    ATOM_LABEL_FONT = CDPL.Base.LookupKey('ATOM_LABEL_FONT')

    ##
    # \brief Specifies the margin of free space around atom labels.
    # 
    # The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by Vis.ControlParameter.ATOM_LABEL_SIZE, Vis.MolecularGraphProperty.ATOM_LABEL_SIZE or Vis.AtomProperty.LABEL_SIZE. If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the label margin will follow the size change of the chemical structure during viewport size adjustment. The specified margin takes precedence over the margin specified by the parameter Vis.ControlParameter.ATOM_LABEL_MARGIN.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.LABEL_MARGIN.
    # 
    ATOM_LABEL_MARGIN = CDPL.Base.LookupKey('ATOM_LABEL_MARGIN')

    ##
    # \brief Specifies the size of atom element and query match expression labels.
    # 
    # The font size has to be specified as an absolute value. If input-scaling is enabled, the font size will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will grow/shrink with the size of the chemical structure during viewport size adjustment. The specified size takes precedence over the size specified by the parameter Vis.ControlParameter.ATOM_LABEL_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.LABEL_SIZE.
    # 
    ATOM_LABEL_SIZE = CDPL.Base.LookupKey('ATOM_LABEL_SIZE')

    ##
    # \brief Specifies the font for text labels that show the value of various atomic properties.
    # 
    # The specified font takes precedence over the font specified by the parameter Vis.ControlParameter.SECONDARY_ATOM_LABEL_FONT.
    # 
    # <b>Value Type:</b> Vis.Font \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.SECONDARY_LABEL_FONT.
    # 
    SECONDARY_ATOM_LABEL_FONT = CDPL.Base.LookupKey('SECONDARY_ATOM_LABEL_FONT')

    ##
    # \brief Specifies the size of text labels that show the value of various atomic properties.
    # 
    # The size can either be specified as an absolute value or as a scaling factor for the primary label size given by Vis.ControlParameter.ATOM_LABEL_SIZE, Vis.MolecularGraphProperty.ATOM_LABEL_SIZE or Vis.AtomProperty.LABEL_SIZE. If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during viewport size adjustment. The specified size takes precedence over the size specified by the parameter Vis.ControlParameter.SECONDARY_ATOM_LABEL_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.SECONDARY_LABEL_SIZE.
    # 
    SECONDARY_ATOM_LABEL_SIZE = CDPL.Base.LookupKey('SECONDARY_ATOM_LABEL_SIZE')

    ##
    # \brief Specifies the color of bonds.
    # 
    # The specified color takes precedence over the color specified by the parameter Vis.ControlParameter.BOND_COLOR.
    # 
    # <b>Value Type:</b> Vis.Color \note The setting is overridden by the Chem.Bond property Vis.BondProperty.COLOR.
    # 
    BOND_COLOR = CDPL.Base.LookupKey('BOND_COLOR')

    ##
    # \brief Specifies the font for bond labels.
    # 
    # The specified font takes precedence over the font specified by the parameter Vis.ControlParameter.BOND_LABEL_FONT.
    # 
    # <b>Value Type:</b> Vis.Font \note The setting is overridden by the Chem.Bond property Vis.BondProperty.LABEL_FONT.
    # 
    BOND_LABEL_FONT = CDPL.Base.LookupKey('BOND_LABEL_FONT')

    ##
    # \brief Specifies the margin of free space around bond labels.
    # 
    # The margin can either be specified as an absolute value or as a scaling factor for the primary label size given by Vis.ControlParameter.BOND_LABEL_SIZE, Vis.MolecularGraphProperty.BOND_LABEL_SIZE or Vis.BondProperty.LABEL_SIZE. If input-scaling is enabled, the width of the margin will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the label margin will follow the size change of the chemical structure during viewport size adjustment. The specified margin takes precedence over the margin specified by the parameter Vis.ControlParameter.BOND_LABEL_MARGIN.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.LABEL_MARGIN.
    # 
    BOND_LABEL_MARGIN = CDPL.Base.LookupKey('BOND_LABEL_MARGIN')

    ##
    # \brief Specifies the size of bond labels.
    # 
    # The font size has to be specified as an absolute value. If input-scaling is enabled, the font size will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during viewport size adjustment. The specified font size takes precedence over the size specified by the parameter Vis.ControlParameter.BOND_LABEL_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.LABEL_SIZE.
    # 
    BOND_LABEL_SIZE = CDPL.Base.LookupKey('BOND_LABEL_SIZE')

    ##
    # \brief Specifies the distance between the lines of double and triple bonds.
    # 
    # The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the line distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified line spacing takes precedence over the distance specified by the parameter Vis.ControlParameter.BOND_LINE_SPACING.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.LINE_SPACING. <br>
    # 
    BOND_LINE_SPACING = CDPL.Base.LookupKey('BOND_LINE_SPACING')

    ##
    # \brief Specifies the width of bond lines.
    # 
    # The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the line width will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the line width grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified line width takes precedence over the width specified by the parameter Vis.ControlParameter.BOND_LINE_WIDTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.LINE_WIDTH.
    # 
    BOND_LINE_WIDTH = CDPL.Base.LookupKey('BOND_LINE_WIDTH')

    ##
    # \brief Specifies the length of the lines in reaction center marks.
    # 
    # The length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the line length will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified line length takes precedence over the length specified by the parameter Vis.ControlParameter.REACTION_CENTER_LINE_LENGTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.REACTION_CENTER_LINE_LENGTH. <br>
    #  
    # 
    # \see Vis.ControlParameter.SHOW_BOND_REACTION_INFOS
    # 
    REACTION_CENTER_LINE_LENGTH = CDPL.Base.LookupKey('REACTION_CENTER_LINE_LENGTH')

    ##
    # \brief Specifies the distance between the lines in reaction center marks.
    # 
    # The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the line distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the distance grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified line spacing takes precedence over the spacing specified by the parameter Vis.ControlParameter.REACTION_CENTER_LINE_SPACING.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.REACTION_CENTER_LINE_SPACING. <br>
    #  
    # 
    # \see Vis.ControlParameter.SHOW_BOND_REACTION_INFOS
    # 
    REACTION_CENTER_LINE_SPACING = CDPL.Base.LookupKey('REACTION_CENTER_LINE_SPACING')

    ##
    # \brief Specifies the distance between the hashes of down stereo bonds.
    # 
    # The distance can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the hash distance will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the hash distance grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified hash spacing takes precedence over the spacing specified by the parameter Vis.ControlParameter.STEREO_BOND_HASH_SPACING.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.STEREO_BOND_HASH_SPACING. <br>
    # 
    STEREO_BOND_HASH_SPACING = CDPL.Base.LookupKey('STEREO_BOND_HASH_SPACING')

    ##
    # \brief Specifies the width of wedge-shaped stereo bonds.
    # 
    # The width can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the wedge width will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the wedge width grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified wedge width takes precedence over the width specified by the parameter Vis.ControlParameter.STEREO_BOND_WEDGE_WIDTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH. <br>
    # 
    STEREO_BOND_WEDGE_WIDTH = CDPL.Base.LookupKey('STEREO_BOND_WEDGE_WIDTH')

    ##
    # \brief Specifies the amount by which the non-central lines of asymmetric double bonds have to be trimmed at each line end.
    # 
    # The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the trim length will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified trim length takes precedence over the length specified by the parameter Vis.ControlParameter.DOUBLE_BOND_TRIM_LENGTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH. <br>
    # 
    DOUBLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey('DOUBLE_BOND_TRIM_LENGTH')

    ##
    # \brief Specifies the amount by which the non-central lines of triple bonds have to be trimmed at each line end.
    # 
    # The trim length can either be specified as an absolute value or as a scaling factor for the bond length. If input-scaling is enabled, the trim length will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the length grows/shrinks with the size of the chemical structure during viewport size adjustment. The specified trim length takes precedence over the length specified by the parameter Vis.ControlParameter.TRIPLE_BOND_TRIM_LENGTH.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH. <br>
    # 
    TRIPLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey('TRIPLE_BOND_TRIM_LENGTH')

    ##
    # \brief Specifies the font used for atom configuration descriptor text labels.
    # 
    # The specified font takes precedence over the font specified by the parameter Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_FONT.
    # 
    # <b>Value Type:</b> Vis.Font \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.CONFIGURATION_LABEL_FONT. 
    # 
    # \since 1.1
    # 
    ATOM_CONFIGURATION_LABEL_FONT = CDPL.Base.LookupKey('ATOM_CONFIGURATION_LABEL_FONT')

    ##
    # \brief Specifies the size of atom configuration descriptor text labels.
    # 
    # The size can either be specified as an absolute value or as a scaling factor for the primary label size given by Vis.ControlParameter.ATOM_LABEL_SIZE, Vis.MolecularGraphProperty.ATOM_LABEL_SIZE or Vis.AtomProperty.LABEL_SIZE. If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during viewport size adjustment. The specified size takes precedence over the size specified by the parameter Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.CONFIGURATION_LABEL_SIZE. 
    # 
    # \since 1.1
    # 
    ATOM_CONFIGURATION_LABEL_SIZE = CDPL.Base.LookupKey('ATOM_CONFIGURATION_LABEL_SIZE')

    ##
    # \brief Specifies the color used for atom configuration descriptor text labels.
    # 
    # The specified color takes precedence over the color specified by the parameter Vis.ControlParameter.ATOM_CONFIGURATION_LABEL_COLOR.
    # 
    # <b>Value Type:</b> Vis.Color \note The setting is overridden by the Chem.Atom property Vis.AtomProperty.CONFIGURATION_LABEL_COLOR. 
    # 
    # \since 1.2
    # 
    ATOM_CONFIGURATION_LABEL_COLOR = CDPL.Base.LookupKey('ATOM_CONFIGURATION_LABEL_COLOR')

    ##
    # \brief Specifies the font used for bond configuration descriptor text labels.
    # 
    # The specified font takes precedence over the font specified by the parameter Vis.ControlParameter.BOND_CONFIGURATION_LABEL_FONT.
    # 
    # <b>Value Type:</b> Vis.Font \note The setting is overridden by the Chem.Bond property Vis.BondProperty.CONFIGURATION_LABEL_FONT. 
    # 
    # \since 1.1
    # 
    BOND_CONFIGURATION_LABEL_FONT = CDPL.Base.LookupKey('BOND_CONFIGURATION_LABEL_FONT')

    ##
    # \brief Specifies the size of bond configuration descriptor text labels.
    # 
    # The size can either be specified as an absolute value or as a scaling factor for the primary label size given by Vis.ControlParameter.BOND_LABEL_SIZE, Vis.MolecularGraphProperty.BOND_LABEL_SIZE or Vis.BondProperty.LABEL_SIZE. If input-scaling is enabled, the size of the font will follow the size change of the chemical structure during bond length normalization. If output-scaling is enabled, the font size will follow the size change of the chemical structure during viewport size adjustment. The specified size takes precedence over the size specified by the parameter Vis.ControlParameter.BOND_CONFIGURATION_LABEL_SIZE.
    # 
    # <b>Value Type:</b> Vis.SizeSpecification \note The setting is overridden by the Chem.Bond property Vis.BondProperty.CONFIGURATION_LABEL_SIZE. 
    # 
    # \since 1.1
    # 
    BOND_CONFIGURATION_LABEL_SIZE = CDPL.Base.LookupKey('BOND_CONFIGURATION_LABEL_SIZE')

    ##
    # \brief Specifies the color used for bond configuration descriptor text labels.
    # 
    # The specified color takes precedence over the color specified by the parameter Vis.ControlParameter.BOND_CONFIGURATION_LABEL_COLOR.
    # 
    # <b>Value Type:</b> Vis.Color \note The setting is overridden by the Chem.Bond property Vis.BondProperty.CONFIGURATION_LABEL_COLOR. 
    # 
    # \since 1.2
    # 
    BOND_CONFIGURATION_LABEL_COLOR = CDPL.Base.LookupKey('BOND_CONFIGURATION_LABEL_COLOR')
