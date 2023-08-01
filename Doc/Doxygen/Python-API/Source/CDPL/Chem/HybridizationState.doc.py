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
# \brief Provides constants for the specification of atom hybridization states.
# 
class HybridizationState(Boost.Python.instance):

    ##
    # \brief Specifies an unknown hybridization state.
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies the hybridization <em>dp</em>.
    # 
    DP = 4

    ##
    # \brief Specifies the hybridization state <em>sd<sup>3</sup></em>.
    # 
    SD3 = 5

    ##
    # \brief Specifies the hybridization state <em>sp</em>.
    # 
    SP = 1

    ##
    # \brief Specifies the hybridization state <em>sp<sup>1</sup></em>.
    # 
    SP1 = 1

    ##
    # \brief Specifies the hybridization state <em>sp<sup>2</sup></em>.
    # 
    SP2 = 2

    ##
    # \brief Specifies the hybridization state <em>sp<sup>2</sup>d</em>.
    # 
    SP2D = 6

    ##
    # \brief Specifies the hybridization state <em>sp<sup>3</sup></em>.
    # 
    SP3 = 3

    ##
    # \brief Specifies the hybridization state <em>sp<sup>3</sup>d</em>.
    # 
    SP3D = 7

    ##
    # \brief Specifies the hybridization state <em>sp<sup>3</sup>d<sup>2</sup></em>.
    # 
    SP3D2 = 8

    ##
    # \brief Specifies the hybridization state <em>sp<sup>3</sup>d<sup>3</sup></em>.
    # 
    SP3D3 = 9
