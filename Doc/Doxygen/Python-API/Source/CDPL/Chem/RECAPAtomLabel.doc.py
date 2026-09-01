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
# \brief Provides constants for labeling the endpoints of bonds matched by <em>RECAP</em> fragmentation rules.
# 
# \see [\ref RECAP]
# 
class RECAPAtomLabel(Boost.Python.instance):

    ##
    # \brief Specifies that the atom carries no label.
    # 
    NONE = 0

    ##
    # \brief Specifies the nitrogen side of an amide bond.
    # 
    AMIDE_N = 1

    ##
    # \brief Specifies the carbon side of an amide bond.
    # 
    AMIDE_C = 2

    ##
    # \brief Specifies the oxygen side of an ester bond.
    # 
    ESTER_O = 3

    ##
    # \brief Specifies the carbon side of an ester bond.
    # 
    ESTER_C = 4

    ##
    # \brief Specifies the nitrogen side of an amine bond.
    # 
    AMINE_N = 5

    ##
    # \brief Specifies the carbon side of an amine bond.
    # 
    AMINE_C = 6

    ##
    # \brief Specifies the nitrogen side of a urea bond.
    # 
    UREA_N = 7

    ##
    # \brief Specifies the carbon side of a urea bond.
    # 
    UREA_C = 8

    ##
    # \brief Specifies the oxygen side of an ether bond.
    # 
    ETHER_O = 9

    ##
    # \brief Specifies the carbon side of an ether bond.
    # 
    ETHER_C = 10

    ##
    # \brief Specifies a carbon side of an olefinic bond.
    # 
    OLEFIN_C = 11

    ##
    # \brief Specifies the nitrogen side of a quaternary amine bond.
    # 
    QUATERNARY_N_N = 12

    ##
    # \brief Specifies the carbon side of a quaternary amine bond.
    # 
    QUATERNARY_N_C = 13

    ##
    # \brief Specifies the nitrogen side of an aromatic nitrogen to aliphatic carbon bond.
    # 
    AROMATIC_N_ALIPHATIC_C_N = 14

    ##
    # \brief Specifies the carbon side of an aromatic nitrogen to aliphatic carbon bond.
    # 
    AROMATIC_N_ALIPHATIC_C_C = 15

    ##
    # \brief Specifies the nitrogen side of a lactam bond.
    # 
    LACTAM_N_ALIPHATIC_C_N = 16

    ##
    # \brief Specifies the carbon side of a lactam bond.
    # 
    LACTAM_N_ALIPHATIC_C_C = 17

    ##
    # \brief Specifies an atom of an aromatic carbon-carbon bond.
    # 
    AROMATIC_C_AROMATIC_C_C = 18

    ##
    # \brief Specifies the nitrogen side of a sulfonamide bond.
    # 
    SULFONAMIDE_N = 19

    ##
    # \brief Specifies the sulfur side of a sulfonamide bond.
    # 
    SULFONAMIDE_S = 20
