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
class ElectronSystemList(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ElectronSystemList instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ElectronSystemList instance.
    # \param list 
    #
    def __init__(list: ElectronSystemList) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ElectronSystemList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ElectronSystemList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param num_elem 
    # \param value 
    #
    def resize(num_elem: int, value: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param num_elem 
    #
    def reserve(num_elem: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCapacity() -> int: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ElectronSystemList instance \a array.
    # \param array The \e %ElectronSystemList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(array: ElectronSystemList) -> ElectronSystemList: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ElectronSystemList instance \a num_elem.
    # \param num_elem The \e %ElectronSystemList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(num_elem: int, value: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def addElement(value: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param values 
    #
    def addElements(values: ElectronSystemList) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \param value 
    #
    def insertElement(idx: int, value: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(idx: int, num_elem: int, value: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param index 
    # \param values 
    #
    def insertElements(index: int, values: ElectronSystemList) -> None: pass

    ##
    # \brief 
    #
    def popLastElement() -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeElement(idx: int) -> None: pass

    ##
    # \brief 
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFirstElement() -> ElectronSystem: pass

    ##
    # \brief 
    # \return 
    #
    def getLastElement() -> ElectronSystem: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getElement(idx: int) -> ElectronSystem: pass

    ##
    # \brief 
    # \param idx 
    # \param value 
    #
    def setElement(idx: int, value: ElectronSystem) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> ElectronSystem: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param index 
    # \param value 
    #
    def __setitem__(index: int, value: ElectronSystem) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == list</tt>.
    # \param list The \e %ElectronSystemList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(list: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != list</tt>.
    # \param list The \e %ElectronSystemList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(list: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
