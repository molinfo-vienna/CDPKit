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
class AtomMatchExpressionList(AtomMatchExpression):

    ##
    # \brief Initializes the \e %AtomMatchExpressionList instance.
    # \param self The \e %AtomMatchExpressionList instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %AtomMatchExpressionList instance.
    # \param self The \e %AtomMatchExpressionList instance to initialize.
    # \param expr 
    #
    def __init__(self: object, expr: AtomMatchExpressionList) -> None: pass

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
    def getObjectID(self: AtomMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getSize(self: AtomMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \return 
    #
    def isEmpty(self: AtomMatchExpressionList) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: AtomMatchExpressionList, num_elem: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: AtomMatchExpressionList, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getCapacity(self: AtomMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    #
    def clear(self: AtomMatchExpressionList) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomMatchExpressionList instance \a array.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param array The \e %AtomMatchExpressionList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AtomMatchExpressionList, array: AtomMatchExpressionList) -> AtomMatchExpressionList: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomMatchExpressionList instance \a num_elem.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param num_elem The \e %AtomMatchExpressionList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AtomMatchExpressionList, num_elem: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param value 
    #
    def addElement(self: AtomMatchExpressionList, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param values 
    #
    def addElements(self: AtomMatchExpressionList, values: AtomMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: AtomMatchExpressionList, idx: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: AtomMatchExpressionList, idx: int, num_elem: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: AtomMatchExpressionList, index: int, values: AtomMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    #
    def popLastElement(self: AtomMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: AtomMatchExpressionList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: AtomMatchExpressionList, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: AtomMatchExpressionList) -> AtomMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getLastElement(self: AtomMatchExpressionList) -> AtomMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: AtomMatchExpressionList, idx: int) -> AtomMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: AtomMatchExpressionList, idx: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: AtomMatchExpressionList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: AtomMatchExpressionList, idx: int) -> AtomMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \return 
    #
    def __len__(self: AtomMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: AtomMatchExpressionList, index: int, value: AtomMatchExpression) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == expr</tt>.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param expr The \e %AtomMatchExpressionList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: AtomMatchExpressionList, expr: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != expr</tt>.
    # \param self The \e %AtomMatchExpressionList instance this method is called upon.
    # \param expr The \e %AtomMatchExpressionList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: AtomMatchExpressionList, expr: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
