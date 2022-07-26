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
class HierarchyView(Boost.Python.instance):

    ##
    # \brief Initializes the \e %HierarchyView instance.
    # \param self The \e %HierarchyView instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %HierarchyView instance.
    # \param self The \e %HierarchyView instance to initialize.
    # \param molgraph 
    #
    def __init__(self: object, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %HierarchyView instance this method is called upon.
    #
    # Different Python \e %HierarchyView instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %HierarchyView instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: HierarchyView) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \param molgraph 
    #
    def build(self: HierarchyView, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \return 
    #
    def getResidues(self: HierarchyView) -> ResidueList: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \return 
    #
    def getNumModels(self: HierarchyView) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getModel(self: HierarchyView, idx: int) -> HierarchyViewModel: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \param num 
    # \return 
    #
    def hasModelWithNumber(self: HierarchyView, num: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \param num 
    # \return 
    #
    def getModelByNumber(self: HierarchyView, num: int) -> HierarchyViewModel: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \return 
    #
    def __len__(self: HierarchyView) -> int: pass

    ##
    # \brief 
    # \param self The \e %HierarchyView instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: HierarchyView, idx: int) -> HierarchyViewModel: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numModels = property(getNumModels)

    ##
    # \brief 
    #
    residues = property(getResidues)
