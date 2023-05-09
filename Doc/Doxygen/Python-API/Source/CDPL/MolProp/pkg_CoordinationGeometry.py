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
# \brief 
#
class CoordinationGeometry(Boost.Python.instance):

    ##
    # \brief 
    #
    UNDEF = 0

    ##
    # \brief 
    #
    NONE = 1

    ##
    # \brief 
    #
    LINEAR = 2

    ##
    # \brief 
    #
    TRIGONAL_PLANAR = 3

    ##
    # \brief 
    #
    TETRAHEDRAL = 4

    ##
    # \brief 
    #
    TRIGONAL_BIPYRAMIDAL = 5

    ##
    # \brief 
    #
    OCTAHEDRAL = 6

    ##
    # \brief 
    #
    PENTAGONAL_BIPYRAMIDAL = 7

    ##
    # \brief 
    #
    SQUARE_ANTIPRISMATIC = 8

    ##
    # \brief 
    #
    BENT = 9

    ##
    # \brief 
    #
    TRIGONAL_PYRAMIDAL = 10

    ##
    # \brief 
    #
    SQUARE_PLANAR = 11

    ##
    # \brief 
    #
    SQUARE_PYRAMIDAL = 12

    ##
    # \brief 
    #
    T_SHAPED = 13

    ##
    # \brief 
    #
    SEESAW = 14

    ##
    # \brief 
    #
    PENTAGONAL_PYRAMIDAL = 15

    ##
    # \brief 
    #
    PENTAGONAL_PLANAR = 16
