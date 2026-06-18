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
# \brief Provides constants for the specification of a MMFF94 parameter set variant.
# 
# \see [\ref MMFF94, \ref MMFF94s, \ref RTOR]
# 
class MMFF94ParameterSet(Boost.Python.instance):

    ##
    # \brief Original dynamic MMFF94 parameter set.
    # 
    DYNAMIC = 0

    ##
    # \brief Original static MMFF94 parameter set.
    # 
    STATIC = 1

    ##
    # \brief Static MMFF94 parameter set with extended out-of-plane bending parameters.
    # 
    STATIC_XOOP = 2

    ##
    # \brief Static MMFF94 parameter set with refined torsion parameters.
    # 
    STATIC_RTOR = 3

    ##
    # \brief Static MMFF94 parameter set with both extended out-of-plane bending and refined torsion parameters.
    # 
    STATIC_RTOR_XOOP = 4
