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
# \brief A container for the storage and evaluation of logical match expression lists.
# 
# <tt>AtomMatchExpressionList</tt> allows for a concatenation of multiple Chem.AtomMatchExpression instances that get evaluated in turn according to some logic. The actual logic of expression list evaluation has to be implemented by subclasses by overriding the virtual function call operator methods of the Chem.AtomMatchExpression interface.
# 
class AtomMatchExpressionList(AtomMatchExpression):

    ##
    # \brief Creates an empty list.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AtomMatchExpressionList instance.
    # \param self The \e %AtomMatchExpressionList instance to initialize.
    # \param expr 
    # 
    def __init__(expr: AtomMatchExpressionList) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # 
    # Different Python \e %AtomMatchExpressionList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomMatchExpressionList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the number of elements stored in the list.
    # 
    # \return The size of the list.
    # 
    def getSize() -> int: pass

    ##
    # \brief Tells whether the list is empty (getSize() == 0).
    # 
    # \return <tt>True</tt> if the list is empty, <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Inserts or erases elements at the end so that the size becomes <em>num_elem</em>.
    # 
    # \param num_elem The new size.
    # \param value The value for newly inserted elements.
    # 
    def resize(num_elem: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief Preallocates memory for (at least) <em>num_elem</em> elements.
    # 
    # If <em>num_elem</em> is less than or equal to the current capacity, this call has no effect. Otherwise, it is a request for allocation of additional memory. If the request is successful, then the capacity is greater than or equal to <em>num_elem</em>. Otherwise, the capacity is unchanged. In either case, the number of elements will not change.
    # 
    # \param num_elem The number of elements to reserve memory for.
    # 
    # \see getCapacity()
    # 
    def reserve(num_elem: int) -> None: pass

    ##
    # \brief Returns the number of elements for which memory has been allocated.
    # 
    # The capacity is always greater than or equal to the number of currently stored elements.
    # 
    # \return The current capacity.
    # 
    def getCapacity() -> int: pass

    ##
    # \brief Erases all elements.
    # 
    def clear() -> None: pass

    ##
    # \brief 
    # \param array 
    # \return 
    #
    def assign(array: AtomMatchExpressionList) -> AtomMatchExpressionList: pass

    ##
    # \brief This function fills the list with <em>num_elem</em> copies of the given <em>value</em>.
    # 
    # Note that the assignment completely changes the list and the new size is the same as the number of elements assigned. Old data will be lost.
    # 
    # \param num_elem The number of elements to be assigned.
    # \param value The value to be assigned.
    # 
    def assign(num_elem: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief Inserts a new element at the end of the list.
    # 
    # \param value The value of the new element.
    # 
    def addElement(value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param values 
    #
    def addElements(values: AtomMatchExpressionList) -> None: pass

    ##
    # \brief Inserts a new element before the location specified by the index <em>idx</em>.
    # 
    # \param idx The location where to insert the new element.
    # \param value The value of the element to insert.
    # 
    # \throw Base.IndexError if the list is empty or <em>idx</em> is not in the range [0, getSize()].
    # 
    def insertElement(idx: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief Inserts <em>num_elem</em> copies of <em>value</em> before the location specified by the index <em>idx</em>.
    # 
    # \param idx The location where to insert the new elements.
    # \param num_elem The number of elements to insert.
    # \param value The value of the elements to insert.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getSize()].
    # 
    def insertElements(idx: int, num_elem: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param index 
    # \param values 
    #
    def insertElements(index: int, values: AtomMatchExpressionList) -> None: pass

    ##
    # \brief Removes the last element of the list.
    # 
    # \throw Base.OperationFailed if the list is empty.
    # 
    def popLastElement() -> None: pass

    ##
    # \brief Removes the element at the position specified by the index <em>idx</em>.
    # 
    # \param idx The zero-based index of the element to remove.
    # 
    # \throw Base.IndexError if the list is empty or <em>idx</em> is not in the range [0, getSize() - 1].
    # 
    def removeElement(idx: int) -> None: pass

    ##
    # \brief 
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief Returns a reference to the first element of the list.
    # 
    # \return A reference to the first element. 
    # 
    # \throw Base.OperationFailed if the list is empty.
    # 
    def getFirstElement() -> AtomMatchExpression: pass

    ##
    # \brief Returns a reference to the last element of the list.
    # 
    # \return A reference to the last element. 
    # 
    # \throw Base.OperationFailed if the list is empty.
    # 
    def getLastElement() -> AtomMatchExpression: pass

    ##
    # \brief Returns a reference to the element at index <em>idx</em>.
    # 
    # The method is equivalent to operator[](std::size_t).
    # 
    # \param idx The zero-based index of the element.
    # 
    # \return A reference to the element. 
    # 
    # \throw Base.IndexError if the list is empty or <em>idx</em> is not in the range [0, getSize() - 1].
    # 
    def getElement(idx: int) -> AtomMatchExpression: pass

    ##
    # \brief Assigns a new value to the element specified by the index <em>idx</em>.
    # 
    # \param idx The zero-based index of the element for which to assign a new value.
    # \param value The new value of the element after assignment.
    # 
    # \throw Base.IndexError if the list is empty or <em>idx</em> is not in the range [0, getSize() - 1].
    # 
    def setElement(idx: int, value: AtomMatchExpression) -> None: pass

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
    def __getitem__(idx: int) -> AtomMatchExpression: pass

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
    def __setitem__(index: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == expr</tt>.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param expr The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(expr: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != expr</tt>.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param expr The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(expr: object) -> bool: pass

    objectID = property(getObjectID)

    size = property(getSize)
