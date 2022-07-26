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
class MolecularGraphMatchExpressionList(MolecularGraphMatchExpression):

    ##
    # \brief Initializes the \e %MolecularGraphMatchExpressionList instance.
    # \param self The \e %MolecularGraphMatchExpressionList instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MolecularGraphMatchExpressionList instance.
    # \param self The \e %MolecularGraphMatchExpressionList instance to initialize.
    # \param expr 
    #
    def __init__(self: object, expr: MolecularGraphMatchExpressionList) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    #
    # Different Python \e %MolecularGraphMatchExpressionList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MolecularGraphMatchExpressionList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MolecularGraphMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getSize(self: MolecularGraphMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \return 
    #
    def isEmpty(self: MolecularGraphMatchExpressionList) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: MolecularGraphMatchExpressionList, num_elem: int, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: MolecularGraphMatchExpressionList, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getCapacity(self: MolecularGraphMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    #
    def clear(self: MolecularGraphMatchExpressionList) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MolecularGraphMatchExpressionList instance \a array.
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param array The \e %MolecularGraphMatchExpressionList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MolecularGraphMatchExpressionList, array: MolecularGraphMatchExpressionList) -> MolecularGraphMatchExpressionList: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MolecularGraphMatchExpressionList instance \a num_elem.
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param num_elem The \e %MolecularGraphMatchExpressionList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MolecularGraphMatchExpressionList, num_elem: int, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param value 
    #
    def addElement(self: MolecularGraphMatchExpressionList, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param values 
    #
    def addElements(self: MolecularGraphMatchExpressionList, values: MolecularGraphMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: MolecularGraphMatchExpressionList, idx: int, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: MolecularGraphMatchExpressionList, idx: int, num_elem: int, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: MolecularGraphMatchExpressionList, index: int, values: MolecularGraphMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    #
    def popLastElement(self: MolecularGraphMatchExpressionList) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: MolecularGraphMatchExpressionList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: MolecularGraphMatchExpressionList, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: MolecularGraphMatchExpressionList) -> MolecularGraphMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \return 
    #
    def getLastElement(self: MolecularGraphMatchExpressionList) -> MolecularGraphMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: MolecularGraphMatchExpressionList, idx: int) -> MolecularGraphMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: MolecularGraphMatchExpressionList, idx: int, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: MolecularGraphMatchExpressionList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: MolecularGraphMatchExpressionList, idx: int) -> MolecularGraphMatchExpression: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \return 
    #
    def __len__(self: MolecularGraphMatchExpressionList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: MolecularGraphMatchExpressionList, index: int, value: MolecularGraphMatchExpression) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == expr</tt>.
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param expr The \e %MolecularGraphMatchExpressionList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: MolecularGraphMatchExpressionList, expr: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != expr</tt>.
    # \param self The \e %MolecularGraphMatchExpressionList instance this method is called upon.
    # \param expr The \e %MolecularGraphMatchExpressionList instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: MolecularGraphMatchExpressionList, expr: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
