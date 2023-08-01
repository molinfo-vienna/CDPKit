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
# \brief Provides numerical identifiers for built-in Chem.Bond matching constraints and flags for the specification of bond orders.
# 
class BondMatchConstraint(Boost.Python.instance):

    ##
    # \brief Specifies a constraint which requires the target bond to fulfill additional contraints specified by a Chem.MatchConstraintList object.
    # 
    CONSTRAINT_LIST = 0

    ##
    # \brief Specifies a bond of any order.
    # 
    ANY_ORDER = 15

    ##
    # \brief Specifies an aromatic bond with delocalized electrons.
    # 
    AROMATIC = 8

    ##
    # \brief Specifies a constraint on the aromaticity of the target bond.
    # 
    AROMATICITY = 2

    ##
    # \brief Specifies a constraint on the relative direction of the target bond.
    # 
    # \see Chem.BondDirection
    # 
    DIRECTION = 6

    ##
    # \brief Specifies a constraint on the steric configuration of the target bond that is defined by the relative direction of attached bonds.
    # 
    # \see Chem.BondDirection
    # 
    DIRECTION_CONFIG = 5

    ##
    # \brief Specifies a double bond.
    # 
    DOUBLE = 2

    ##
    # \brief Specifies a constraint on the steric configuration of the target bond.
    # 
    CONFIGURATION = 4

    ##
    # \brief Specifies that the target bond must have the specified order even if the bond is aromatic.
    # 
    IGNORE_AROMATICITY = 16

    ##
    # \brief Specifies a constraint on the order of the target bond.
    # 
    ORDER = 1

    ##
    # \brief Specifies a constraint on the reaction center status of the target bond.
    # 
    # \see Chem.ReactionCenterStatus
    # 
    REACTION_CENTER_STATUS = 7

    ##
    # \brief Specifies a constraint on the ring-membership of the target bond.
    # 
    RING_TOPOLOGY = 3

    ##
    # \brief Specifies a single bond.
    # 
    SINGLE = 1

    ##
    # \brief Specifies a triple bond.
    # 
    TRIPLE = 4
