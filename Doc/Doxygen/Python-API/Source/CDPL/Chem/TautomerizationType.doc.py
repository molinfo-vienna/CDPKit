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
# \brief Provides constants serving as identifiers for built-in Chem.TautomerizationRule implementations.
# 
class TautomerizationType(Boost.Python.instance):

    ##
    # \brief Identifier for the keto-enol tautomerization rule.
    # 
    KETO_ENOL = 0

    ##
    # \brief Identifier for the imine-enamine tautomerization rule.
    # 
    IMINE_ENAMINE = 1

    ##
    # \brief Identifier for the nitroso-oxime tautomerization rule.
    # 
    NITROSO_OXIME = 2

    ##
    # \brief Identifier for the amide-imidic-acid tautomerization rule.
    # 
    AMIDE_IMIDIC_ACID = 3

    ##
    # \brief Identifier for the lactam-lactim tautomerization rule.
    # 
    LACTAM_LACTIM = 4

    ##
    # \brief Identifier for the ketene-ynol tautomerization rule.
    # 
    KETENE_YNOL = 5

    ##
    # \brief Identifier for the nitro-aci tautomerization rule.
    # 
    NITRO_ACI = 6

    ##
    # \brief Identifier for the phosphinic-acid tautomerization rule.
    # 
    PHOSPHINIC_ACID = 7

    ##
    # \brief Identifier for the sulfenic-acid tautomerization rule.
    # 
    SULFENIC_ACID = 8

    ##
    # \brief Identifier for the generic 1,3-hydrogen-shift tautomerization rule.
    # 
    GENERIC_H_13_SHIFT = 9

    ##
    # \brief Identifier for the generic 1,5-hydrogen-shift tautomerization rule.
    # 
    GENERIC_H_15_SHIFT = 10

    ##
    # \brief Identifier for the conjugated-ring-bond-pattern switching tautomerization rule.
    # 
    # \since 1.3
    # 
    CONJ_RING_BOND_SWITCH = 11
