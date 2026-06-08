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
# \brief Provides constants for the specification of the atom charge type in <em>Sybyl MOL2</em> files.
# 
class MOL2ChargeType(Boost.Python.instance):

    ##
    # \brief Specifies that the charge type is unknown.
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies that the file contains no charge information.
    # 
    NO_CHARGES = 1

    ##
    # \brief Specifies Del Re partial atomic charges.
    # 
    DEL_RE = 2

    ##
    # \brief Specifies Gasteiger partial atomic charges.
    # 
    GASTEIGER = 3

    ##
    # \brief Specifies Gasteiger-Hückel partial atomic charges.
    # 
    GAST_HUCK = 4

    ##
    # \brief Specifies Hückel partial atomic charges.
    # 
    HUCKEL = 5

    ##
    # \brief Specifies Pullman partial atomic charges.
    # 
    PULLMAN = 6

    ##
    # \brief Specifies <em>Gaussian 80</em> derived partial atomic charges.
    # 
    GAUSS80 = 7

    ##
    # \brief Specifies <em>AMPAC</em> derived partial atomic charges.
    # 
    AMPAC = 8

    ##
    # \brief Specifies Mulliken partial atomic charges.
    # 
    MULLIKEN = 9

    ##
    # \brief Specifies dictionary-derived charges.
    # 
    DICT = 10

    ##
    # \brief Specifies MMFF94 partial atomic charges.
    # 
    MMFF94 = 11

    ##
    # \brief Specifies user-supplied charges.
    # 
    USER = 12
