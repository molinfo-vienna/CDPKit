#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
class AtomPropertyFlag(Boost.Python.instance):

    ##
    # \brief 
    #
    NONE = 0

    ##
    # \brief 
    #
    DEFAULT = 2147483648

    ##
    # \brief 
    #
    AROMATICITY = 128

    ##
    # \brief 
    #
    TYPE = 2

    ##
    # \brief 
    #
    CIP_CONFIGURATION = 1

    ##
    # \brief 
    #
    CONFIGURATION = 256

    ##
    # \brief 
    #
    FORMAL_CHARGE = 8

    ##
    # \brief 
    #
    H_COUNT = 16

    ##
    # \brief 
    #
    HEAVY_BOND_COUNT = 1024

    ##
    # \brief 
    #
    EXPLICIT_BOND_COUNT = 4096

    ##
    # \brief 
    #
    VALENCE = 2048

    ##
    # \brief 
    #
    ISOTOPE = 4

    ##
    # \brief 
    #
    SYMBOL = 32

    ##
    # \brief 
    #
    TOPOLOGY = 64

    ##
    # \brief 
    #
    HYBRIDIZATION_STATE = 8192

    ##
    # \brief 
    #
    ATOM_MAPPING_ID = 512
