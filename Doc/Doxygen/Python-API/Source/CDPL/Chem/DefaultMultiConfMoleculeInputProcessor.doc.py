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
# \brief MultiConfMoleculeInputProcessor.
# 
class DefaultMultiConfMoleculeInputProcessor(MultiConfMoleculeInputProcessor):

    ##
    # \brief 
    #
    DEF_ATOM_PROPERTY_FLAGS = 14

    ##
    # \brief 
    #
    DEF_BOND_PROPERTY_FLAGS = 2

    ##
    # \brief Initializes the \e %DefaultMultiConfMoleculeInputProcessor instance.
    # \param comp_names 
    # \param atom_flags 
    # \param bond_flags 
    # 
    def __init__(comp_names: bool = False, atom_flags: int = 14, bond_flags: int = 2) -> None: pass
