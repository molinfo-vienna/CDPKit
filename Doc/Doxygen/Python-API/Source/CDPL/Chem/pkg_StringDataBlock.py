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
class StringDataBlock(Boost.Python.instance):

    ##
    # \brief Initializes the \e %StringDataBlock instance.
    # \param self The \e %StringDataBlock instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %StringDataBlock instance.
    # \param self The \e %StringDataBlock instance to initialize.
    # \param data_block 
    #
    def __init__(self: object, data_block: StringDataBlock) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %StringDataBlock instance this method is called upon.
    #
    # Different Python \e %StringDataBlock instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StringDataBlock instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: StringDataBlock) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \return 
    #
    def getSize(self: StringDataBlock) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \return 
    #
    def isEmpty(self: StringDataBlock) -> bool: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: StringDataBlock, num_elem: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: StringDataBlock, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \return 
    #
    def getCapacity(self: StringDataBlock) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    #
    def clear(self: StringDataBlock) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %StringDataBlock instance \a array.
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param array The \e %StringDataBlock instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: StringDataBlock, array: StringDataBlock) -> StringDataBlock: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %StringDataBlock instance \a num_elem.
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param num_elem The \e %StringDataBlock instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: StringDataBlock, num_elem: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param value 
    #
    def addElement(self: StringDataBlock, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param values 
    #
    def addElements(self: StringDataBlock, values: StringDataBlock) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: StringDataBlock, idx: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: StringDataBlock, idx: int, num_elem: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: StringDataBlock, index: int, values: StringDataBlock) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    #
    def popLastElement(self: StringDataBlock) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: StringDataBlock, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: StringDataBlock, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: StringDataBlock) -> StringDataBlockEntry: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \return 
    #
    def getLastElement(self: StringDataBlock) -> StringDataBlockEntry: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: StringDataBlock, idx: int) -> StringDataBlockEntry: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: StringDataBlock, idx: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param header 
    # \param data 
    #
    def addEntry(self: StringDataBlock, header: str, data: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: StringDataBlock, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: StringDataBlock, idx: int) -> StringDataBlockEntry: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \return 
    #
    def __len__(self: StringDataBlock) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: StringDataBlock, index: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == data_block</tt>.
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param data_block The \e %StringDataBlock instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: StringDataBlock, data_block: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != data_block</tt>.
    # \param self The \e %StringDataBlock instance this method is called upon.
    # \param data_block The \e %StringDataBlock instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: StringDataBlock, data_block: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
