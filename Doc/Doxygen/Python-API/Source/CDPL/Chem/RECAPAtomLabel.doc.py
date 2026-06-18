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
# \brief Provides constants for the labeling of atoms of bonds matched by a RECAP fragmentation rule.
# 
# \see [\ref RECAP]
# 
class RECAPAtomLabel(Boost.Python.instance):

    ##
    # \brief Specifies that the atom carries no RECAP label.
    # 
    NONE = 0

    ##
    # \brief Specifies the nitrogen side of an amide bond cleaved by the RECAP <tt>AMIDE</tt> rule.
    # 
    AMIDE_N = 1

    ##
    # \brief Specifies the carbon side of an amide bond cleaved by the RECAP <tt>AMIDE</tt> rule.
    # 
    AMIDE_C = 2

    ##
    # \brief Specifies the oxygen side of an ester bond cleaved by the RECAP <tt>ESTER</tt> rule.
    # 
    ESTER_O = 3

    ##
    # \brief Specifies the carbon side of an ester bond cleaved by the RECAP <tt>ESTER</tt> rule.
    # 
    ESTER_C = 4

    ##
    # \brief Specifies the nitrogen side of an amine bond cleaved by the RECAP <tt>AMINE</tt> rule.
    # 
    AMINE_N = 5

    ##
    # \brief Specifies the carbon side of an amine bond cleaved by the RECAP <tt>AMINE</tt> rule.
    # 
    AMINE_C = 6

    ##
    # \brief Specifies the nitrogen side of a urea bond cleaved by the RECAP <tt>UREA</tt> rule.
    # 
    UREA_N = 7

    ##
    # \brief Specifies the carbon side of a urea bond cleaved by the RECAP <tt>UREA</tt> rule.
    # 
    UREA_C = 8

    ##
    # \brief Specifies the oxygen side of an ether bond cleaved by the RECAP <tt>ETHER</tt> rule.
    # 
    ETHER_O = 9

    ##
    # \brief Specifies the carbon side of an ether bond cleaved by the RECAP <tt>ETHER</tt> rule.
    # 
    ETHER_C = 10

    ##
    # \brief Specifies a carbon side of an olefinic bond cleaved by the RECAP <tt>OLEFIN</tt> rule.
    # 
    OLEFIN_C = 11

    ##
    # \brief Specifies the quaternary-nitrogen side of a bond cleaved by the RECAP <tt>QUARTERNARY_N</tt> rule.
    # 
    QUARTERNARY_N_N = 12

    ##
    # \brief Specifies the carbon side of a bond cleaved by the RECAP <tt>QUARTERNARY_N</tt> rule.
    # 
    QUARTERNARY_N_C = 13

    ##
    # \brief Specifies the aromatic-N side of a bond cleaved by the RECAP <tt>AROMATIC_N_ALIPHATIC_C</tt> rule.
    # 
    AROMATIC_N_ALIPHATIC_C_N = 14

    ##
    # \brief Specifies the aliphatic-C side of a bond cleaved by the RECAP <tt>AROMATIC_N_ALIPHATIC_C</tt> rule.
    # 
    AROMATIC_N_ALIPHATIC_C_C = 15

    ##
    # \brief Specifies the lactam-N side of a bond cleaved by the RECAP <tt>LACTAM_N_ALIPHATIC_C</tt> rule.
    # 
    LACTAM_N_ALIPHATIC_C_N = 16

    ##
    # \brief Specifies the aliphatic-C side of a bond cleaved by the RECAP <tt>LACTAM_N_ALIPHATIC_C</tt> rule.
    # 
    LACTAM_N_ALIPHATIC_C_C = 17

    ##
    # \brief Specifies an aromatic-C side of a biaryl bond cleaved by the RECAP <tt>AROMATIC_C_AROMATIC_C</tt> rule.
    # 
    AROMATIC_C_AROMATIC_C_C = 18

    ##
    # \brief Specifies the nitrogen side of a sulfonamide bond cleaved by the RECAP <tt>SULFONAMIDE</tt> rule.
    # 
    SULFONAMIDE_N = 19

    ##
    # \brief Specifies the sulfur side of a sulfonamide bond cleaved by the RECAP <tt>SULFONAMIDE</tt> rule.
    # 
    SULFONAMIDE_S = 20
