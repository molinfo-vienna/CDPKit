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
# \brief Provides constants for the identification of <em>RECAP</em> fragmentation rules.
# 
# \see [\ref RECAP]
# 
class RECAPRuleID(Boost.Python.instance):

    ##
    # \brief Specifies that no rule applies.
    # 
    NONE = 0

    ##
    # \brief Specifies the rule for amide bond cleavage.
    # 
    AMIDE = 1

    ##
    # \brief Specifies the rule for ester bond cleavage.
    # 
    ESTER = 2

    ##
    # \brief Specifies the rule for amine bond cleavage.
    # 
    AMINE = 3

    ##
    # \brief Specifies the rule for urea bond cleavage.
    # 
    UREA = 4

    ##
    # \brief Specifies the rule for ether bond cleavage.
    # 
    ETHER = 5

    ##
    # \brief Specifies the rule for olefinic bond cleavage.
    # 
    OLEFIN = 6

    ##
    # \brief Specifies the rule for quaternary amine bond cleavage.
    # 
    QUATERNARY_N = 7

    ##
    # \brief Specifies the rule for aromatic nitrogen to aliphatic carbon bond cleavage.
    # 
    AROMATIC_N_ALIPHATIC_C = 8

    ##
    # \brief Specifies the rule for lactam bond cleavage.
    # 
    LACTAM_N_ALIPHATIC_C = 9

    ##
    # \brief Specifies the rule for aromatic carbon-carbon bond cleavage (biaryl).
    # 
    AROMATIC_C_AROMATIC_C = 10

    ##
    # \brief Specifies the rule for sulfonamide bond cleavage.
    # 
    SULFONAMIDE = 11
