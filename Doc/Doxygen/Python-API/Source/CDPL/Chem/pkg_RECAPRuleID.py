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
# \brief Provides constants for the identification of RECAP fragmentation rules.
# 
# \see [\ref RECAP]
# 
class RECAPRuleID(Boost.Python.instance):

    ##
    # \brief 
    #
    NONE = 0

    ##
    # \brief 
    #
    AMIDE = 1

    ##
    # \brief 
    #
    ESTER = 2

    ##
    # \brief 
    #
    AMINE = 3

    ##
    # \brief 
    #
    UREA = 4

    ##
    # \brief 
    #
    ETHER = 5

    ##
    # \brief 
    #
    OLEFIN = 6

    ##
    # \brief 
    #
    QUARTERNARY_N = 7

    ##
    # \brief 
    #
    AROMATIC_N_ALIPHATIC_C = 8

    ##
    # \brief 
    #
    LACTAM_N_ALIPHATIC_C = 9

    ##
    # \brief 
    #
    AROMATIC_C_AROMATIC_C = 10

    ##
    # \brief 
    #
    SULFONAMIDE = 11
