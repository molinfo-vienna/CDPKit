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
# \brief Provides constants for the rotational symmetry class of a Gaussian shape.
# 
class SymmetryClass(Boost.Python.instance):

    ##
    # \brief Specifies an undefined symmetry class.
    # 
    UNDEF = 0

    ##
    # \brief Specifies an asymmetric shape (all three principal moments of inertia distinct).
    # 
    ASYMMETRIC = 1

    ##
    # \brief Specifies an oblate (disc-shaped) symmetric top.
    # 
    OBLATE = 2

    ##
    # \brief Specifies a prolate (cigar-shaped) symmetric top.
    # 
    PROLATE = 3

    ##
    # \brief Specifies a spherical top (all three principal moments of inertia equal).
    # 
    SPHERICAL = 4
