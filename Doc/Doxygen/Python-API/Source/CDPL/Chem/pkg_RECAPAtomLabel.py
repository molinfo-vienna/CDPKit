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
# \brief Provides constants for the labeling of atoms in bonds matched by a RECAP fragmentation rule.
# 
# \see [\ref RECAP]
# 
class RECAPAtomLabel(Boost.Python.instance):

    ##
    # \brief 
    #
    NONE = 0

    ##
    # \brief 
    #
    AMIDE_N = 1

    ##
    # \brief 
    #
    AMIDE_C = 2

    ##
    # \brief 
    #
    ESTER_O = 3

    ##
    # \brief 
    #
    ESTER_C = 4

    ##
    # \brief 
    #
    AMINE_N = 5

    ##
    # \brief 
    #
    AMINE_C = 6

    ##
    # \brief 
    #
    UREA_N = 7

    ##
    # \brief 
    #
    UREA_C = 8

    ##
    # \brief 
    #
    ETHER_O = 9

    ##
    # \brief 
    #
    ETHER_C = 10

    ##
    # \brief 
    #
    OLEFIN_C = 11

    ##
    # \brief 
    #
    QUARTERNARY_N_N = 12

    ##
    # \brief 
    #
    QUARTERNARY_N_C = 13

    ##
    # \brief 
    #
    AROMATIC_N_ALIPHATIC_C_N = 14

    ##
    # \brief 
    #
    AROMATIC_N_ALIPHATIC_C_C = 15

    ##
    # \brief 
    #
    LACTAM_N_ALIPHATIC_C_N = 16

    ##
    # \brief 
    #
    LACTAM_N_ALIPHATIC_C_C = 17

    ##
    # \brief 
    #
    AROMATIC_C_AROMATIC_C_C = 18

    ##
    # \brief 
    #
    SULFONAMIDE_N = 19

    ##
    # \brief 
    #
    SULFONAMIDE_S = 20
