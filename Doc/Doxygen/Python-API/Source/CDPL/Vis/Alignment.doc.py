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
# \brief Provides flags that are used to specify the 2D alignment of graphical objects within a bounded rectangular area.
# 
# The flags may be combined by a bitwise OR operation to specify a composite alignment for both directions. For example: <tt>(Alignment.RIGHT | Alignment.BOTTOM)</tt> specifies an alignment to the bottom-right corner.
# 
class Alignment(Boost.Python.instance):

    ##
    # \brief Specifies an alignment to the bottom.
    # 
    BOTTOM = 8

    ##
    # \brief Specifies that an object has to be centered horizontally and vertically.
    # 
    CENTER = 15

    ##
    # \brief A bitmask for all horizontal alignment flags.
    # 
    H_ALIGNMENT_MASK = 3

    ##
    # \brief Specifies that an object has to be centered horizontally.
    # 
    H_CENTER = 3

    ##
    # \brief Specifies an alignment to the left.
    # 
    LEFT = 1

    ##
    # \brief Specifies that an object has no special alignment.
    # 
    NONE = 0

    ##
    # \brief Specifies an alignment to the right.
    # 
    RIGHT = 2

    ##
    # \brief Specifies an alignment to the top.
    # 
    TOP = 4

    ##
    # \brief A bitmask for all vertical alignment flags.
    # 
    V_ALIGNMENT_MASK = 12

    ##
    # \brief Specifies that an object has to be centered vertically.
    # 
    V_CENTER = 12
