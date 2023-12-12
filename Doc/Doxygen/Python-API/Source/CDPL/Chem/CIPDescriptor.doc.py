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
# \brief Provides constants for the specification of stereogenic atom/bond configurations determined by the CIP sequence rules.
# 
class CIPDescriptor(Boost.Python.instance):

    ##
    # \brief Specifies that the configuration of the stereocenter (if any) is completely undefined.
    # 
    UNDEF = 0

    ##
    # \brief Specifies that the atom/bond is not a stereogenic center and thus cannot be assigned a configuration.
    # 
    NONE = 1

    ##
    # \brief Specifies that the atom/bond is a stereogenic center but has no specified configuration.
    # 
    NS = 2

    ##
    # \brief Specifies that the stereocenter has <em>R</em> configuration.
    # 
    R = 3

    ##
    # \brief Specifies that the stereocenter has <em>S</em> configuration.
    # 
    S = 4

    ##
    # \brief Specifies that the stereocenter has <em>r</em> configuration.
    # 
    r = 5

    ##
    # \brief Specifies that the stereocenter has <em>s</em> configuration.
    # 
    s = 6

    ##
    # \brief Specifies that the stereocenter has <em>M</em> configuration.
    # 
    M = 11

    ##
    # \brief Specifies that the stereocenter has <em>P</em> configuration.
    # 
    P = 12

    ##
    # \brief Specifies that the stereocenter has <em>m</em> configuration.
    # 
    m = 13

    ##
    # \brief Specifies that the stereocenter has <em>p</em> configuration.
    # 
    p = 14

    ##
    # \brief Specifies that the stereocenter has <em>E</em> configuration.
    # 
    E = 9

    ##
    # \brief Specifies that the stereocenter has <em>Z</em> configuration.
    # 
    Z = 10

    ##
    # \brief Specifies that the stereocenter has <em>seqCis</em> configuration.
    # 
    seqCis = 8

    ##
    # \brief Specifies that the stereocenter has <em>seqTrans</em> configuration.
    # 
    seqTrans = 7
