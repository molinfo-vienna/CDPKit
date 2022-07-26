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
class FeatureType(Boost.Python.instance):

    ##
    # \brief 
    #
    UNKNOWN = 0

    ##
    # \brief 
    #
    HYDROPHOBIC = 1

    ##
    # \brief 
    #
    AROMATIC = 2

    ##
    # \brief 
    #
    NEGATIVE_IONIZABLE = 3

    ##
    # \brief 
    #
    POSITIVE_IONIZABLE = 4

    ##
    # \brief 
    #
    H_BOND_DONOR = 5

    ##
    # \brief 
    #
    H_BOND_ACCEPTOR = 6

    ##
    # \brief 
    #
    HALOGEN_BOND_DONOR = 7

    ##
    # \brief 
    #
    HALOGEN_BOND_ACCEPTOR = 8

    ##
    # \brief 
    #
    EXCLUSION_VOLUME = 9

    ##
    # \brief 
    #
    MAX_TYPE = 9
