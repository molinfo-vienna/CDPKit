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
class MatchConstraintList(Boost.Python.instance):

    ##
    # \brief 
    #
    class Type(Boost.Python.enum):

        ##
        # \brief AND_LIST.
        #
        AND_LIST = 0

        ##
        # \brief OR_LIST.
        #
        OR_LIST = 2

        ##
        # \brief NOT_AND_LIST.
        #
        NOT_AND_LIST = 1

        ##
        # \brief NOT_OR_LIST.
        #
        NOT_OR_LIST = 3

    ##
    # \brief Initializes the \e %MatchConstraintList instance.
    # \param self The \e %MatchConstraintList instance to initialize.
    # \param list 
    #
    def __init__(self: object, list: MatchConstraintList) -> None: pass

    ##
    # \brief Initializes the \e %MatchConstraintList instance.
    # \param self The \e %MatchConstraintList instance to initialize.
    # \param type 
    #
    def __init__(self: object, type: Type = CDPL.Chem.Type.AND_LIST) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MatchConstraintList instance this method is called upon.
    #
    # Different Python \e %MatchConstraintList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MatchConstraintList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MatchConstraintList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def getSize(self: MatchConstraintList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def isEmpty(self: MatchConstraintList) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: MatchConstraintList, num_elem: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: MatchConstraintList, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def getCapacity(self: MatchConstraintList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    #
    def clear(self: MatchConstraintList) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MatchConstraintList instance \a array.
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param array The \e %MatchConstraintList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MatchConstraintList, array: MatchConstraintList) -> MatchConstraintList: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MatchConstraintList instance \a num_elem.
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param num_elem The \e %MatchConstraintList instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MatchConstraintList, num_elem: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param value 
    #
    def addElement(self: MatchConstraintList, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param id 
    # \param relation 
    #
    def addElement(self: MatchConstraintList, id: int, relation: Relation) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param id 
    # \param relation 
    # \param value 
    #
    def addElement(self: MatchConstraintList, id: int, relation: Relation, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param values 
    #
    def addElements(self: MatchConstraintList, values: MatchConstraintList) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: MatchConstraintList, idx: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: MatchConstraintList, idx: int, num_elem: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: MatchConstraintList, index: int, values: MatchConstraintList) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    #
    def popLastElement(self: MatchConstraintList) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: MatchConstraintList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: MatchConstraintList, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: MatchConstraintList) -> MatchConstraint: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def getLastElement(self: MatchConstraintList) -> MatchConstraint: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: MatchConstraintList, idx: int) -> MatchConstraint: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: MatchConstraintList, idx: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def getType(self: MatchConstraintList) -> Type: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param type 
    #
    def setType(self: MatchConstraintList, type: Type) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: MatchConstraintList, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: MatchConstraintList, idx: int) -> MatchConstraint: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return 
    #
    def __len__(self: MatchConstraintList) -> int: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: MatchConstraintList, index: int, value: MatchConstraint) -> None: pass

    ##
    # \brief Returns a string representation of the \e %MatchConstraintList instance.
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: MatchConstraintList) -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)

    ##
    # \brief 
    #
    type = property(getType, setType)
