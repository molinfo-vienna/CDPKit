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
# \brief Provides constants that are used to specify the role of molecules (components) in a chemical reaction.
# 
class ReactionRole(Boost.Python.instance):

    ##
    # \brief Specifies that a molecule is not a reaction component.
    # 
    NONE = 0

    ##
    # \brief Specifies reactants, agents and products of a reaction.
    # 
    ALL = 7

    ##
    # \brief Specifies the agents of a reaction (e.g. solvent or catalyst).
    # 
    AGENT = 2

    ##
    # \brief Equivalent to ReactionRole.AGENT.
    # 
    CATALYST = 2

    ##
    # \brief Specifies the products of a reaction.
    # 
    PRODUCT = 4

    ##
    # \brief Specifies the reactants of a reaction.
    # 
    REACTANT = 1
