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
# \brief Data structure for the representation of individual biological macromolecule models.
# 
# \see Biomol.HierarchyView
# 
class HierarchyViewModel(HierarchyViewNode):

    ##
    # \brief Returns the number of chains in this model.
    # 
    # \return The number of chains.
    # 
    def getNumChains() -> int: pass

    ##
    # \brief Returns the chain at index <em>idx</em>.
    # 
    # \param idx The zero-based chain index.
    # 
    # \return A reference to the chain. 
    # 
    # \throw Base.IndexError if the number of chains is zero or <em>idx</em> is not in the range [0, getNumChains() - 1].
    # 
    def getChain(idx: int) -> HierarchyViewChain: pass

    ##
    # \brief Tells whether this model contains a chain with the given PDB chain ID.
    # 
    # \param id The PDB chain ID.
    # 
    # \return <tt>True</tt> if such a chain exists, and <tt>False</tt> otherwise.
    # 
    def hasChainWithID(id: str) -> bool: pass

    ##
    # \brief Returns the chain identified by the given PDB chain ID.
    # 
    # \param id The PDB chain ID.
    # 
    # \return A reference to the chain. 
    # 
    # \throw Base.ItemNotFound if no chain with the requested ID exists.
    # 
    def getChainByID(id: str) -> HierarchyViewChain: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> HierarchyViewChain: pass

    numChains = property(getNumChains)
