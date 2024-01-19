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
# \brief Provides constants that are used to describe the result of operations related to conformer generation.
# 
class ReturnCode(Boost.Python.instance):

    ##
    # \brief 
    #
    SUCCESS = 0

    ##
    # \brief 
    #
    UNINITIALIZED = 1

    ##
    # \brief 
    #
    TIMEOUT = 2

    ##
    # \brief 
    #
    ABORTED = 3

    ##
    # \brief 
    #
    FORCEFIELD_SETUP_FAILED = 4

    ##
    # \brief 
    #
    FORCEFIELD_MINIMIZATION_FAILED = 5

    ##
    # \brief 
    #
    FRAGMENT_LIBRARY_NOT_SET = 6

    ##
    # \brief 
    #
    FRAGMENT_CONF_GEN_FAILED = 7

    ##
    # \brief 
    #
    FRAGMENT_CONF_GEN_TIMEOUT = 8

    ##
    # \brief 
    #
    FRAGMENT_ALREADY_PROCESSED = 9

    ##
    # \brief 
    #
    TORSION_DRIVING_FAILED = 10

    ##
    # \brief 
    #
    CONF_GEN_FAILED = 11

    ##
    # \brief 
    #
    TOO_MUCH_SYMMETRY = 12

    ##
    # \brief 
    #
    MAX_ROT_BOND_COUNT_EXCEEDED = 13

    ##
    # \brief 
    #
    NO_FIXED_SUBSTRUCT_COORDS = 14
