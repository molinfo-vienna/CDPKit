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
class MMFF94BondStretchingInteractionData(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94BondStretchingInteractionData instance.
    # \param self The \e %MMFF94BondStretchingInteractionData instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94BondStretchingInteractionData instance.
    # \param self The \e %MMFF94BondStretchingInteractionData instance to initialize.
    # \param ia_data 
    #
    def __init__(self: object, ia_data: MMFF94BondStretchingInteractionData) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    #
    # Different Python \e %MMFF94BondStretchingInteractionData instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94BondStretchingInteractionData instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94BondStretchingInteractionData) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \return 
    #
    def getSize(self: MMFF94BondStretchingInteractionData) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \return 
    #
    def isEmpty(self: MMFF94BondStretchingInteractionData) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: MMFF94BondStretchingInteractionData, num_elem: int, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: MMFF94BondStretchingInteractionData, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \return 
    #
    def getCapacity(self: MMFF94BondStretchingInteractionData) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    #
    def clear(self: MMFF94BondStretchingInteractionData) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94BondStretchingInteractionData instance \a array.
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param array The \e %MMFF94BondStretchingInteractionData instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94BondStretchingInteractionData, array: MMFF94BondStretchingInteractionData) -> MMFF94BondStretchingInteractionData: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94BondStretchingInteractionData instance \a num_elem.
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param num_elem The \e %MMFF94BondStretchingInteractionData instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94BondStretchingInteractionData, num_elem: int, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param value 
    #
    def addElement(self: MMFF94BondStretchingInteractionData, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param values 
    #
    def addElements(self: MMFF94BondStretchingInteractionData, values: MMFF94BondStretchingInteractionData) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: MMFF94BondStretchingInteractionData, idx: int, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: MMFF94BondStretchingInteractionData, idx: int, num_elem: int, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: MMFF94BondStretchingInteractionData, index: int, values: MMFF94BondStretchingInteractionData) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    #
    def popLastElement(self: MMFF94BondStretchingInteractionData) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: MMFF94BondStretchingInteractionData, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: MMFF94BondStretchingInteractionData, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: MMFF94BondStretchingInteractionData) -> MMFF94BondStretchingInteraction: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \return 
    #
    def getLastElement(self: MMFF94BondStretchingInteractionData) -> MMFF94BondStretchingInteraction: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: MMFF94BondStretchingInteractionData, idx: int) -> MMFF94BondStretchingInteraction: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: MMFF94BondStretchingInteractionData, idx: int, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: MMFF94BondStretchingInteractionData, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: MMFF94BondStretchingInteractionData, idx: int) -> MMFF94BondStretchingInteraction: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \return 
    #
    def __len__(self: MMFF94BondStretchingInteractionData) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteractionData instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: MMFF94BondStretchingInteractionData, index: int, value: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
