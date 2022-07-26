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
class ResidueType(Boost.Python.instance):

    ##
    # \brief 
    #
    UNKNOWN = 0

    ##
    # \brief 
    #
    OTHER = 1

    ##
    # \brief 
    #
    NON_POLYMER = 2

    ##
    # \brief 
    #
    PEPTIDE_CARBOXY_TERMINUS = 3

    ##
    # \brief 
    #
    PEPTIDE_AMINO_TERMINUS = 4

    ##
    # \brief 
    #
    PEPTIDE_LINKING = 5

    ##
    # \brief 
    #
    BETA_PEPTIDE_LINKING = 6

    ##
    # \brief 
    #
    GAMMA_PEPTIDE_LINKING = 7

    ##
    # \brief 
    #
    PEPTIDE_LIKE = 8

    ##
    # \brief 
    #
    RNA_HYDROXY_TERMINUS = 9

    ##
    # \brief 
    #
    DNA_HYDROXY_TERMINUS = 10

    ##
    # \brief 
    #
    RNA_LINKING = 11

    ##
    # \brief 
    #
    DNA_LINKING = 12

    ##
    # \brief 
    #
    SACCHARIDE_LINKING = 13

    ##
    # \brief 
    #
    SACCHARIDE = 14
