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
# \brief Provides constants for the specification of directional bonds in <em>Daylight SMILES</em> and <em>SMARTS</em> strings.
# 
# Directional bonds in <em>Daylight SMILES</em> or <em>SMARTS</em> strings are used to specify the configuration around a double bond by indicating the relative direction of the bonds to its substituent atoms. They have only a meaning when they occur on both sides of the double bond (see [\ref SMILES, \ref SMARTS]).
# 
class BondDirection(Boost.Python.instance):

    ##
    # \brief Specifies that the bond has no associated direction.
    # 
    NONE = 0

    ##
    # \brief Specifies that the bond is directed downwards.
    # 
    # In <em>SMILES</em> and <em>SMARTS</em> strings <em>down</em> bonds are specified by a backslash '\'.
    # 
    DOWN = 2

    ##
    # \brief In a substructure search query pattern this flag indicates that the specified query bond direction is not mandatory and that target bonds with an unspecified direction shall also be considered as a match.
    # 
    # The flag only has a meaning for directional bonds in <em>SMARTS</em> patterns where
    #  - its resulting bitwise OR combination with BondDirection.UP specifies that a matching target bond is required to have an <em>upward or unspecified</em> direction
    #  - and its combination with BondDirection.DOWN specifies that a target bond must have a <em>downward or unspecified</em> direction to be considered as a match.
    # 
    UNSPECIFIED = 4

    ##
    # \brief Specifies that the bond is directed upwards.
    # 
    # In <em>SMILES</em> and <em>SMARTS</em> strings <em>up</em> bonds are specified by a slash '/'.
    # 
    UP = 1
