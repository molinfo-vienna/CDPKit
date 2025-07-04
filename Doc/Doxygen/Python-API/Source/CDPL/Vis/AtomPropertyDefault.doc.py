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
# \brief Provides default values for built-in Chem.Atom properties.
# 
class AtomPropertyDefault(Boost.Python.instance):

    ##
    # \brief 
    #
    COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    LABEL_FONT = Font()

    ##
    # \brief 
    #
    LABEL_SIZE = SizeSpecification(value=10, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    SECONDARY_LABEL_FONT = Font()

    ##
    # \brief 
    #
    SECONDARY_LABEL_SIZE = SizeSpecification(value=6, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    RADICAL_ELECTRON_DOT_SIZE = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    CONFIGURATION_LABEL_FONT = Font()

    ##
    # \brief 
    #
    CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    CUSTOM_LABEL_FONT = Font()

    ##
    # \brief 
    #
    CUSTOM_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    CUSTOM_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    CUSTOM_LABEL = ''

    ##
    # \brief 
    #
    HIGHLIGHTED_FLAG = False

    ##
    # \brief 
    #
    HIGHLIGHT_AREA_BRUSH = Brush(color=Color(r=0.8, g=0.8, b=1), style=SOLID_PATTERN)

    ##
    # \brief 
    #
    HIGHLIGHT_AREA_OUTLINE_PEN = Pen(color=Color(r=0.6, g=0.6, b=0.75), width=1, line_style=SOLID_LINE, cap_style=ROUND_CAP, join_style=ROUND_JOIN)
