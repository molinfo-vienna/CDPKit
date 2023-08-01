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
# \brief Provides constants used to specify the spatial geometry of atom arrangements around a common central atom.
# 
class CoordinationGeometry(Boost.Python.instance):

    ##
    # \brief Specifies undefined or unknown geometry.
    # 
    UNDEF = 0

    ##
    # \brief Specifies that a geometry cannot be assigned due to the lack of enough (>1) defining entities.
    # 
    NONE = 1

    ##
    # \brief Specifies <em>linear</em> geometry.
    # 
    LINEAR = 2

    ##
    # \brief Specifies <em>trigonal planar</em> geometry.
    # 
    TRIGONAL_PLANAR = 3

    ##
    # \brief Specifies <em>tetrahedral</em> geometry.
    # 
    TETRAHEDRAL = 4

    ##
    # \brief Specifies <em>trigonal bipyramidal</em> geometry.
    # 
    TRIGONAL_BIPYRAMIDAL = 5

    ##
    # \brief Specifies <em>octahedral</em> geometry.
    # 
    OCTAHEDRAL = 6

    ##
    # \brief Specifies <em>pentagonal bipyramidal</em> geometry.
    # 
    PENTAGONAL_BIPYRAMIDAL = 7

    ##
    # \brief Specifies <em>square antiprismatic</em> geometry.
    # 
    SQUARE_ANTIPRISMATIC = 8

    ##
    # \brief Specifies <em>bent</em> geometry.
    # 
    BENT = 9

    ##
    # \brief Specifies <em>trigonal pyramidal</em> geometry.
    # 
    TRIGONAL_PYRAMIDAL = 10

    ##
    # \brief Specifies <em>square planar</em> geometry.
    # 
    SQUARE_PLANAR = 11

    ##
    # \brief Specifies <em>square pyramidal</em> geometry.
    # 
    SQUARE_PYRAMIDAL = 12

    ##
    # \brief Specifies <em>T-shaped</em> geometry.
    # 
    T_SHAPED = 13

    ##
    # \brief Specifies <em>seesaw</em> geometry.
    # 
    SEESAW = 14

    ##
    # \brief Specifies <em>pentagonal pyramidal</em> geometry.
    # 
    PENTAGONAL_PYRAMIDAL = 15

    ##
    # \brief Specifies <em>pentagonal planar</em> geometry.
    # 
    PENTAGONAL_PLANAR = 16
