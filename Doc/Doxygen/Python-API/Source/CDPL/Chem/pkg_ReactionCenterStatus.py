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
# \brief Provides flags that are used to describe state changes of atoms and bonds in a reaction center.
# 
# \note The flags ReactionCenterStatus.IS_CENTER, ReactionCenterStatus.BOND_MADE, ReactionCenterStatus.BOND_BROKEN, and ReactionCenterStatus.BOND_ORDER_CHANGE may be combined by bitwise OR operations to obtain a composite reaction center state.
# 
class ReactionCenterStatus(Boost.Python.instance):

    ##
    # \brief Specifies that the atom or bond is not part of the reaction center.
    # 
    NONE = 0

    ##
    # \brief Specifies that the bond is broken by the reaction.
    # 
    BOND_BROKEN = 8

    ##
    # \brief Specifies that the bond is made by the reaction.
    # 
    BOND_MADE = 4

    ##
    # \brief Specifies that the bond order is changed by the reaction.
    # 
    BOND_ORDER_CHANGE = 16

    ##
    # \brief Specifies that the change of the atom is exactly as specified.
    # 
    EXACT_CHANGE = 128

    ##
    # \brief Specifies that the bond is part of the reaction center.
    # 
    IS_CENTER = 2

    ##
    # \brief Specifies for bonds in a reaction substructure search query that matching target bonds must not be part of a reaction center.
    # 
    NO_CENTER = 1

    ##
    # \brief Specifies that the bond is left unaltered by the reaction.
    # 
    NO_CHANGE = 32

    ##
    # \brief Specifies that the configuration of the atom is inverted by the reaction.
    # 
    STEREO_INVERSION = 64

    ##
    # \brief Specifies that the configuration of the atom is retained in the reaction.
    # 
    STEREO_RETENTION = 128
