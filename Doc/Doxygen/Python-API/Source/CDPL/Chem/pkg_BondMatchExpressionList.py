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
class BondMatchExpressionList(BondMatchExpression):

    ##
    # \brief Initializes the \e %BondMatchExpressionList instance.
    # \param self The \e %BondMatchExpressionList instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BondMatchExpressionList instance.
    # \param self The \e %BondMatchExpressionList instance to initialize.
    # \param expr 
    #
    def __init__(self: object, expr: BondMatchExpressionList) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    #
    # Different Python \e %BondMatchExpressionList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondMatchExpressionList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: BondMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getSize(self: BondMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \return 
    #
    def isEmpty(self: BondMatchExpressionList) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: BondMatchExpressionList, num_elem: int, value: BondMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: BondMatchExpressionList, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getCapacity(self: BondMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    #
    def clear(self: BondMatchExpressionList) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BondMatchExpressionList instance \a array.
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param array The \e %BondMatchExpressionList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BondMatchExpressionList, array: BondMatchExpressionList) -> BondMatchExpressionList: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BondMatchExpressionList instance \a num_elem.
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param num_elem The \e %BondMatchExpressionList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BondMatchExpressionList, num_elem: int, value: BondMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param value 
    #
    def addElement(self: BondMatchExpressionList, value: BondMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param values 
    #
    def addElements(self: BondMatchExpressionList, values: BondMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: BondMatchExpressionList, idx: int, value: BondMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: BondMatchExpressionList, idx: int, num_elem: int, value: BondMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: BondMatchExpressionList, index: int, values: BondMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    #
    def popLastElement(self: BondMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: BondMatchExpressionList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: BondMatchExpressionList, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: BondMatchExpressionList) -> BondMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getLastElement(self: BondMatchExpressionList) -> BondMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: BondMatchExpressionList, idx: int) -> BondMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: BondMatchExpressionList, idx: int, value: BondMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: BondMatchExpressionList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: BondMatchExpressionList, idx: int) -> BondMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \return 
    #
    def __len__(self: BondMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: BondMatchExpressionList, index: int, value: BondMatchExpression) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == expr</tt>.
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param expr The \e %BondMatchExpressionList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: BondMatchExpressionList, expr: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != expr</tt>.
    # \param self The \e %BondMatchExpressionList instance this method is called upon.
    # \param expr The \e %BondMatchExpressionList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: BondMatchExpressionList, expr: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
