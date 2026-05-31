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
# \brief Default Chem.MultiConfMoleculeInputProcessor implementation that detects multi-conformer input by comparing atom and bond properties (and optionally molecule names) between successive input molecules.
# 
class DefaultMultiConfMoleculeInputProcessor(MultiConfMoleculeInputProcessor):

    ##
    # \brief Specifies the default set of atom properties considered when checking conformer compatibility.
    # 
    DEF_ATOM_PROPERTY_FLAGS = 14

    ##
    # \brief Specifies the default set of bond properties considered when checking conformer compatibility.
    # 
    DEF_BOND_PROPERTY_FLAGS = 2

    ##
    # \brief Constructs the processor with the given property-comparison configuration.
    # 
    # \param comp_names If <tt>True</tt>, the molecule name property must agree between successive conformers.
    # \param atom_flags The bitwise-OR combination of Chem.AtomPropertyFlag values that must agree atom-wise.
    # \param bond_flags The bitwise-OR combination of Chem.BondPropertyFlag values that must agree bond-wise.
    # 
    def __init__(comp_names: bool = False, atom_flags: int = 14, bond_flags: int = 2) -> None: pass
