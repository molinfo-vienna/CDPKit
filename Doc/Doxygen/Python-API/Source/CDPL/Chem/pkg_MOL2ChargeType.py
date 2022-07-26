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
class MOL2ChargeType(Boost.Python.instance):

    ##
    # \brief 
    #
    UNKNOWN = 0

    ##
    # \brief 
    #
    NO_CHARGES = 1

    ##
    # \brief 
    #
    DEL_RE = 2

    ##
    # \brief 
    #
    GASTEIGER = 3

    ##
    # \brief 
    #
    GAST_HUCK = 4

    ##
    # \brief 
    #
    HUCKEL = 5

    ##
    # \brief 
    #
    PULLMAN = 6

    ##
    # \brief 
    #
    GAUSS80 = 7

    ##
    # \brief 
    #
    AMPAC = 8

    ##
    # \brief 
    #
    MULLIKEN = 9

    ##
    # \brief 
    #
    DICT = 10

    ##
    # \brief 
    #
    MMFF94 = 11

    ##
    # \brief 
    #
    USER = 12
