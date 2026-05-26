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
# \brief Provides flags for the specification of a set of force field interaction types.
# 
class InteractionType(Boost.Python.instance):

    ##
    # \brief Specifies no interaction.
    # 
    NONE = 0

    ##
    # \brief Specifies a bond stretching interaction.
    # 
    BOND_STRETCHING = 1

    ##
    # \brief Specifies an angle bending interaction.
    # 
    ANGLE_BENDING = 2

    ##
    # \brief Specifies a stretch-bend coupling interaction.
    # 
    STRETCH_BEND = 4

    ##
    # \brief Specifies an out-of-plane bending interaction.
    # 
    OUT_OF_PLANE_BENDING = 8

    ##
    # \brief Specifies a torsion interaction.
    # 
    TORSION = 16

    ##
    # \brief Specifies a Van der Waals interaction.
    # 
    VAN_DER_WAALS = 32

    ##
    # \brief Specifies an electrostatic interaction.
    # 
    ELECTROSTATIC = 64

    ##
    # \brief A bitmask covering all interaction types.
    # 
    ALL = 127
