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
# \brief Data structure for the representation of biological macromolecule chains.
# 
# \see Biomol.HierarchyView
# 
class HierarchyViewChain(HierarchyViewNode):

    ##
    # \brief Returns the number of fragments this chain consists of.
    # 
    # \return The number of chain fragments.
    # 
    def getNumFragments() -> int: pass

    ##
    # \brief Returns the chain fragment at index <em>idx</em>.
    # 
    # \param idx The zero-based fragment index.
    # 
    # \return A reference to the chain fragment. 
    # 
    # \throw Base.IndexError if the number of chain fragments is zero or <em>idx</em> is not in the range [0, getNumFragments() - 1].
    # 
    def getFragment(idx: int) -> HierarchyViewFragment: pass

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
    def __getitem__(idx: int) -> HierarchyViewFragment: pass

    numFragments = property(getNumFragments)
