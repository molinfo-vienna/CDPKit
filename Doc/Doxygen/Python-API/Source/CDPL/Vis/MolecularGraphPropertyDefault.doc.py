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
    # \brief 
    #
    ATOM_COLOR_TABLE = ColorTable()

    ##
    # \brief 
    #
    ATOM_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    ATOM_LABEL_FONT = Font()

    ##
    # \brief 
    #
    ATOM_LABEL_SIZE = SizeSpecification(value=10, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    SECONDARY_ATOM_LABEL_FONT = Font()

    ##
    # \brief 
    #
    SECONDARY_ATOM_LABEL_SIZE = SizeSpecification(value=6, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    ATOM_LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    RADICAL_ELECTRON_DOT_SIZE = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    BOND_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    BOND_LINE_WIDTH = SizeSpecification(value=1, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    BOND_LINE_SPACING = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    STEREO_BOND_WEDGE_WIDTH = SizeSpecification(value=0.15, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    STEREO_BOND_HASH_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_LENGTH = SizeSpecification(value=0.4, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_SPACING = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    DOUBLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    TRIPLE_BOND_TRIM_LENGTH = SizeSpecification(value=0.1, relative=True, in_scaling=True, out_scaling=True)

    ##
    # \brief 
    #
    BOND_LABEL_FONT = Font()

    ##
    # \brief 
    #
    BOND_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    BOND_LABEL_MARGIN = SizeSpecification(value=2, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    ATOM_CONFIGURATION_LABEL_FONT = Font()

    ##
    # \brief 
    #
    ATOM_CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    ATOM_CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    BOND_CONFIGURATION_LABEL_FONT = Font()

    ##
    # \brief 
    #
    BOND_CONFIGURATION_LABEL_SIZE = SizeSpecification(value=8, relative=False, in_scaling=False, out_scaling=True)

    ##
    # \brief 
    #
    BOND_CONFIGURATION_LABEL_COLOR = Color(r=0, g=0, b=0)
