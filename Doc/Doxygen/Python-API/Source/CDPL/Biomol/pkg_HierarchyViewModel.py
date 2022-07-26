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
class HierarchyViewModel(HierarchyViewNode):

    ##
    # \brief 
    # \param self The \e %HierarchyViewModel instance this method is called upon.
    # \return 
    #
    def getNumChains(self: HierarchyViewModel) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewModel instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getChain(self: HierarchyViewModel, idx: int) -> HierarchyViewChain: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewModel instance this method is called upon.
    # \param id 
    # \return 
    #
    def hasChainWithID(self: HierarchyViewModel, id: str) -> bool: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewModel instance this method is called upon.
    # \param id 
    # \return 
    #
    def getChainByID(self: HierarchyViewModel, id: str) -> HierarchyViewChain: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewModel instance this method is called upon.
    # \return 
    #
    def __len__(self: HierarchyViewModel) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyViewModel instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: HierarchyViewModel, idx: int) -> HierarchyViewChain: pass

    ##
    # \brief 
    #
    numChains = property(getNumChains)
