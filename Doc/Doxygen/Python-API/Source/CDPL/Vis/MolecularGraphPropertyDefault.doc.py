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
# \brief Provides default values for built-in Chem.MolecularGraph properties.
# 
class MolecularGraphPropertyDefault(Boost.Python.instance):

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_COLOR property.
    # 
    ATOM_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_COLOR_TABLE property.
    # 
    ATOM_COLOR_TABLE = ColorTable()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.RADICAL_ELECTRON_DOT_SIZE property.
    # 
    RADICAL_ELECTRON_DOT_SIZE = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_LABEL_FONT property.
    # 
    ATOM_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_LABEL_MARGIN property.
    # 
    ATOM_LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_LABEL_SIZE property.
    # 
    ATOM_LABEL_SIZE = SizeSpecification(value=10, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_FONT property.
    # 
    SECONDARY_ATOM_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.SECONDARY_ATOM_LABEL_SIZE property.
    # 
    SECONDARY_ATOM_LABEL_SIZE = SizeSpecification(value=6, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_SIZE property.
    # 
    # \since 1.2
    # 
    ATOM_HIGHLIGHT_AREA_SIZE = SizeSpecification(value=16, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_BRUSH property.
    # 
    # \since 1.2
    # 
    ATOM_HIGHLIGHT_AREA_BRUSH = Brush(color=Color(r=0.8, g=0.8, b=1), style=SOLID_PATTERN)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_HIGHLIGHT_AREA_OUTLINE_PEN property.
    # 
    # \since 1.2
    # 
    ATOM_HIGHLIGHT_AREA_OUTLINE_PEN = Pen(color=Color(r=0.6, g=0.6, b=0.75), width=1, line_style=SOLID_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.HIGHLIGHT_AREA_OUTLINE_WIDTH property.
    # 
    # \since 1.2
    # 
    HIGHLIGHT_AREA_OUTLINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_COLOR property.
    # 
    BOND_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_LABEL_FONT property.
    # 
    BOND_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_LABEL_MARGIN property.
    # 
    BOND_LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_LABEL_SIZE property.
    # 
    BOND_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_LINE_SPACING property.
    # 
    BOND_LINE_SPACING = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_LINE_WIDTH property.
    # 
    BOND_LINE_WIDTH = SizeSpecification(value=1.5, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_LENGTH property.
    # 
    REACTION_CENTER_LINE_LENGTH = SizeSpecification(value=0.4, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.REACTION_CENTER_LINE_SPACING property.
    # 
    REACTION_CENTER_LINE_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.STEREO_BOND_HASH_SPACING property.
    # 
    STEREO_BOND_HASH_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.STEREO_BOND_WEDGE_WIDTH property.
    # 
    STEREO_BOND_WEDGE_WIDTH = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.DOUBLE_BOND_TRIM_LENGTH property.
    # 
    DOUBLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.TRIPLE_BOND_TRIM_LENGTH property.
    # 
    TRIPLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_FONT property.
    # 
    # \since 1.1
    # 
    ATOM_CONFIGURATION_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_SIZE property.
    # 
    # \since 1.1
    # 
    ATOM_CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_CONFIGURATION_LABEL_COLOR property.
    # 
    # \since 1.2
    # 
    ATOM_CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_WIDTH property.
    # 
    # \since 1.2
    # 
    BOND_HIGHLIGHT_AREA_WIDTH = SizeSpecification(value=12, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_BRUSH property.
    # 
    # \since 1.2
    # 
    BOND_HIGHLIGHT_AREA_BRUSH = Brush(color=Color(r=0.8, g=0.8, b=1), style=SOLID_PATTERN)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_HIGHLIGHT_AREA_OUTLINE_PEN property.
    # 
    # \since 1.2
    # 
    BOND_HIGHLIGHT_AREA_OUTLINE_PEN = Pen(color=Color(r=0.6, g=0.6, b=0.75), width=1, line_style=SOLID_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_FONT property.
    # 
    # \since 1.1
    # 
    BOND_CONFIGURATION_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_SIZE property.
    # 
    # \since 1.1
    # 
    BOND_CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_CONFIGURATION_LABEL_COLOR property.
    # 
    # \since 1.2
    # 
    BOND_CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_FONT property.
    # 
    # \since 1.2
    # 
    ATOM_CUSTOM_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_SIZE property.
    # 
    # \since 1.2
    # 
    ATOM_CUSTOM_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.ATOM_CUSTOM_LABEL_COLOR property.
    # 
    # \since 1.2
    # 
    ATOM_CUSTOM_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_FONT property.
    # 
    # \since 1.2
    # 
    BOND_CUSTOM_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_SIZE property.
    # 
    # \since 1.2
    # 
    BOND_CUSTOM_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.MolecularGraphProperty.BOND_CUSTOM_LABEL_COLOR property.
    # 
    # \since 1.2
    # 
    BOND_CUSTOM_LABEL_COLOR = Color(r=0, g=0, b=0)
