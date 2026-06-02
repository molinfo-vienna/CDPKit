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
# \brief Provides default values for built-in Chem.Bond properties.
# 
class BondPropertyDefault(Boost.Python.instance):

    ##
    # \brief Default value of the Vis.BondProperty.COLOR property.
    # 
    COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.BondProperty.LINE_WIDTH property.
    # 
    LINE_WIDTH = SizeSpecification(value=1.5, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.LINE_SPACING property.
    # 
    LINE_SPACING = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.STEREO_BOND_WEDGE_WIDTH property.
    # 
    STEREO_BOND_WEDGE_WIDTH = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.STEREO_BOND_HASH_SPACING property.
    # 
    STEREO_BOND_HASH_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.REACTION_CENTER_LINE_LENGTH property.
    # 
    REACTION_CENTER_LINE_LENGTH = SizeSpecification(value=0.4, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.REACTION_CENTER_LINE_SPACING property.
    # 
    REACTION_CENTER_LINE_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.DOUBLE_BOND_TRIM_LENGTH property.
    # 
    DOUBLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.TRIPLE_BOND_TRIM_LENGTH property.
    # 
    TRIPLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.LABEL_FONT property.
    # 
    LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.BondProperty.LABEL_SIZE property.
    # 
    LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.LABEL_MARGIN property.
    # 
    LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.CONFIGURATION_LABEL_FONT property.
    # 
    # \since 1.1
    # 
    CONFIGURATION_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.BondProperty.CONFIGURATION_LABEL_SIZE property.
    # 
    # \since 1.1
    # 
    CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.CONFIGURATION_LABEL_COLOR property.
    # 
    # \since 1.2
    # 
    CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.BondProperty.CUSTOM_LABEL_FONT property.
    # 
    # \since 1.2
    # 
    CUSTOM_LABEL_FONT = Font()

    ##
    # \brief Default value of the Vis.BondProperty.CUSTOM_LABEL_SIZE property.
    # 
    # \since 1.2
    # 
    CUSTOM_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief Default value of the Vis.BondProperty.CUSTOM_LABEL_COLOR property.
    # 
    # \since 1.2
    # 
    CUSTOM_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief Default value of the Vis.BondProperty.CUSTOM_LABEL property.
    # 
    # \since 1.2
    # 
    CUSTOM_LABEL = ''

    ##
    # \brief Default value of the Vis.BondProperty.HIGHLIGHTED_FLAG property.
    # 
    # \since 1.2
    # 
    HIGHLIGHTED_FLAG = False

    ##
    # \brief Default value of the Vis.BondProperty.HIGHLIGHT_AREA_BRUSH property.
    # 
    # \since 1.2
    # 
    HIGHLIGHT_AREA_BRUSH = Brush(color=Color(r=0.8, g=0.8, b=1), style=SOLID_PATTERN)

    ##
    # \brief Default value of the Vis.BondProperty.HIGHLIGHT_AREA_OUTLINE_PEN property.
    # 
    # \since 1.2
    # 
    HIGHLIGHT_AREA_OUTLINE_PEN = Pen(color=Color(r=0.6, g=0.6, b=0.75), width=1, line_style=SOLID_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)
