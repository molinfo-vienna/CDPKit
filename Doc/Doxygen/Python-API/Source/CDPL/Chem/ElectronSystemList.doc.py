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
# \brief Data structure for the storage of Chem.ElectronSystem instances.
# 
class ElectronSystemList(Boost.Python.instance):

    ##
    # \brief Contructs the \c ElectronSystemList instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c ElectronSystemList instance \a list.
    # \param list The \c ElectronSystemList instance to copy.
    # 
    def __init__(list: ElectronSystemList) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ElectronSystemList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ElectronSystemList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getSize() -> int: pass

    def isEmpty() -> bool: pass

    def resize(num_elem: int, value: ElectronSystem) -> None: pass

    def reserve(num_elem: int) -> None: pass

    def getCapacity() -> int: pass

    def clear() -> None: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c ElectronSystemList instance \a array.
    # \param array The \c ElectronSystemList instance to copy.
    # \return \a self
    # 
    def assign(array: ElectronSystemList) -> ElectronSystemList: pass

    ##
    # \brief This function fills the array with <em>num_elem</em> copies of the given <em>value</em>.
    # 
    # Note that the assignment completely changes the array and the new size is the same as the number of elements assigned. Old data will be lost.
    # 
    # \param num_elem The number of elements to be assigned.
    # \param value The value to be assigned.
    # 
    def assign(num_elem: int, value: ElectronSystem) -> None: pass

    def addElement(value: ElectronSystem) -> None: pass

    ##
    # \brief Adds the elements of \a values to the end of the list.
    # \param values The \c ElectronSystemList instance providing the elements to add.
    # 
    def addElements(values: ElectronSystemList) -> None: pass

    def insertElement(idx: int, value: ElectronSystem) -> None: pass

    def insertElements(idx: int, num_elem: int, value: ElectronSystem) -> None: pass

    ##
    # \brief Insert the elements of \a values before the location specified by the index \a idx.
    # \param idx The zero-based insertion index.
    # \param values The \c ElectronSystemList instance providing the elements to insert.
    # \throw Base.IndexError if \a idx is not in the range [0, getSize()].
    # 
    def insertElements(idx: int, values: ElectronSystemList) -> None: pass

    def popLastElement() -> None: pass

    def removeElement(idx: int) -> None: pass

    ##
    # \brief Removes the elements at indices in the range <em>[begin_idx, end_idx)</em>.
    # \param begin_idx The zero-based index range start.
    # \param end_idx The zero-based index range end.
    # \throw Base.IndexError if \a begin_idx or \a end_idx is not in the range
    #        [0, getSize()] or \a end_idx < \a begin_idx.
    # 
    def removeElements(begin_idx: int, end_idx: int) -> None: pass

    def getFirstElement() -> ElectronSystem: pass

    def getLastElement() -> ElectronSystem: pass

    def getElement(idx: int) -> ElectronSystem: pass

    def setElement(idx: int, value: ElectronSystem) -> None: pass

    ##
    # \brief Removes the element at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the element to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getSize()).
    # 
    def __delitem__(idx: int) -> None: pass

    def __getitem__(idx: int) -> ElectronSystem: pass

    def __len__() -> int: pass

    ##
    # \brief Assigns a new value to the element at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the element.
    # \param value The new value of the element after assignment.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getSize()).
    # 
    def __setitem__(idx: int, value: ElectronSystem) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == list</tt>.
    # \param list The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(list: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != list</tt>.
    # \param list The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(list: object) -> bool: pass

    objectID = property(getObjectID)

    size = property(getSize)
