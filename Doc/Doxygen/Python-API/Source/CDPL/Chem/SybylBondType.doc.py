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
# \brief Provides constants for the specification of the <em>Tripos Sybyl</em> bond type.
# 
class SybylBondType(Boost.Python.instance):

    ##
    # \brief Specifies an unknown bond (cannot be determined from the parameter tables).
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies a single bond.
    # 
    SINGLE = 1

    ##
    # \brief Specifies a double bond.
    # 
    DOUBLE = 2

    ##
    # \brief Specifies a triple bond.
    # 
    TRIPLE = 3

    ##
    # \brief Specifies an aromatic bond.
    # 
    AROMATIC = 4

    ##
    # \brief Specifies an amide bond.
    # 
    AMIDE = 5

    ##
    # \brief Specifies a dummy bond.
    # 
    DUMMY = 6

    ##
    # \brief Specifies a pseudo bond.
    # 
    NOT_CONNECTED = 7
