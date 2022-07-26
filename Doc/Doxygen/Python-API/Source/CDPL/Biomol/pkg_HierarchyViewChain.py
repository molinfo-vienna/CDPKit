#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class HierarchyViewChain(HierarchyViewNode):

    ##
    # \brief 
    # \param self The \e %HierarchyViewChain instance this method is called upon.
    # \return 
    #
    def getNumFragments(self: HierarchyViewChain) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewChain instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFragment(self: HierarchyViewChain, idx: int) -> HierarchyViewFragment: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewChain instance this method is called upon.
    # \return 
    #
    def __len__(self: HierarchyViewChain) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewChain instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: HierarchyViewChain, idx: int) -> HierarchyViewFragment: pass

    ##
    # \brief 
    #
    numFragments = property(getNumFragments)
