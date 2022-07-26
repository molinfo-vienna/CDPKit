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
class SArray(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SArray instance.
    # \param self The \e %SArray instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SArray instance.
    # \param self The \e %SArray instance to initialize.
    # \param array 
    #
    def __init__(self: object, array: SArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SArray instance this method is called upon.
    #
    # Different Python \e %SArray instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SArray instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SArray) -> int: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \return 
    #
    def getSize(self: SArray) -> int: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \return 
    #
    def isEmpty(self: SArray) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: SArray, num_elem: int, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: SArray, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \return 
    #
    def getCapacity(self: SArray) -> int: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    #
    def clear(self: SArray) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SArray instance \a array.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SArray, array: SArray) -> SArray: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SArray instance \a num_elem.
    # \param self The \e %SArray instance this method is called upon.
    # \param num_elem The \e %SArray instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SArray, num_elem: int, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param value 
    #
    def addElement(self: SArray, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param values 
    #
    def addElements(self: SArray, values: SArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: SArray, idx: int, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: SArray, idx: int, num_elem: int, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: SArray, index: int, values: SArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    #
    def popLastElement(self: SArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: SArray, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: SArray, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: SArray) -> str: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \return 
    #
    def getLastElement(self: SArray) -> str: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: SArray, idx: int) -> str: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: SArray, idx: int, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: SArray, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: SArray, idx: int) -> str: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \return 
    #
    def __len__(self: SArray) -> int: pass

    ##
    # \brief 
    # \param self The \e %SArray instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: SArray, index: int, value: str) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == array</tt>.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: SArray, array: SArray) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != array</tt>.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: SArray, array: SArray) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= array</tt>.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __le__(self: SArray, array: SArray) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= array</tt>.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ge__(self: SArray, array: SArray) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < array</tt>.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(self: SArray, array: SArray) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > array</tt>.
    # \param self The \e %SArray instance this method is called upon.
    # \param array The \e %SArray instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __gt__(self: SArray, array: SArray) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
