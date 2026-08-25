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
# \brief Array of Chem.StringDataBlockEntry objects.
# 
# Used to store the structure or reaction data block of an <em>MDL SD-</em> or <em>RD-File</em> record (see [\ref CTFILE]).
# 
class StringDataBlock(Boost.Python.instance):

    ##
    # \brief Initializes the \c %StringDataBlock instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %StringDataBlock instance \a data_block.
    # \param data_block The \c %StringDataBlock instance to copy.
    # 
    def __init__(data_block: StringDataBlock) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %StringDataBlock instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StringDataBlock instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getSize() -> int: pass

    def isEmpty() -> bool: pass

    def resize(num_elem: int, value: StringDataBlockEntry) -> None: pass

    def reserve(num_elem: int) -> None: pass

    def getCapacity() -> int: pass

    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %StringDataBlock instance \a array.
    # \param array The \c %StringDataBlock instance to copy.
    # \return \a self
    # 
    def assign(array: StringDataBlock) -> StringDataBlock: pass

    def assign(num_elem: int, value: StringDataBlockEntry) -> None: pass

    def addElement(value: StringDataBlockEntry) -> None: pass

    def addElements(values: StringDataBlock) -> None: pass

    def insertElement(idx: int, value: StringDataBlockEntry) -> None: pass

    def insertElements(idx: int, num_elem: int, value: StringDataBlockEntry) -> None: pass

    def insertElements(index: int, values: StringDataBlock) -> None: pass

    def popLastElement() -> None: pass

    def removeElement(idx: int) -> None: pass

    def removeElements(begin_idx: int, end_idx: int) -> None: pass

    def getFirstElement() -> StringDataBlockEntry: pass

    def getLastElement() -> StringDataBlockEntry: pass

    def getElement(idx: int) -> StringDataBlockEntry: pass

    def setElement(idx: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief Appends a new entry with the supplied data header and content to the block.
    # 
    # \param header The data header of the new entry.
    # \param data The data content of the new entry.
    # 
    def addEntry(header: str, data: str) -> None: pass

    def __delitem__(idx: int) -> None: pass

    def __getitem__(idx: int) -> StringDataBlockEntry: pass

    def __len__() -> int: pass

    def __setitem__(index: int, value: StringDataBlockEntry) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == data_block</tt>.
    # \param data_block The \c %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(data_block: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != data_block</tt>.
    # \param data_block The \c %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(data_block: object) -> bool: pass

    objectID = property(getObjectID)

    size = property(getSize)
