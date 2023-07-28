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
# \brief MatchConstraintList.
# 
class MatchConstraintList(Boost.Python.instance):

    ##
    # \brief Defines constants that describe the logical type of the match constraint list.
    # 
    class Type(Boost.Python.enum):

        ##
        # \brief Specifies that all of the match constraints must be fulfilled.
        # 
        AND_LIST = 0

        ##
        # \brief Specifies that at least one of the match constraints must be fulfilled.
        # 
        OR_LIST = 2

        ##
        # \brief Specifies that at least one of the match constraints must not be fulfilled.
        # 
        NOT_AND_LIST = 1

        ##
        # \brief Specifies that all of the match constraints must not be fulfilled.
        # 
        NOT_OR_LIST = 3

    ##
    # \brief Initializes the \e %MatchConstraintList instance.
    # \param self The \e %MatchConstraintList instance to initialize.
    # \param list 
    # 
    def __init__(list: MatchConstraintList) -> None: pass

    ##
    # \brief Constructs a <tt>MatchConstraintList</tt> object with the specified logical type.
    # 
    # \param type The logical type of the match constraint list.
    # 
    def __init__(type: Type = CDPL.Chem.Type.AND_LIST) -> None: pass

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
    def resize(num_elem: int, value: MatchConstraint) -> None: pass

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
    # \brief 
    # \param array 
    # \return 
    #
    def assign(array: MatchConstraintList) -> MatchConstraintList: pass

    ##
    # \brief 
    # \param num_elem 
    # \param value 
    #
    def assign(num_elem: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def addElement(value: MatchConstraint) -> None: pass

    ##
    # \brief Appends a new Chem.MatchConstraint element with the given identifier and relational constraint on the values of matching query/target attribute pairs.
    # 
    # \param id The identifier of the match constraint.
    # \param rel The relational constraint on the values of matching query/target attribute pairs.
    # 
    def addElement(id: int, rel: Relation) -> None: pass

    ##
    # \brief Appends a new Chem.MatchConstraint element with the given identifier, relational constraint on the values of matching query/target attribute pairs and value of the query attribute.
    # 
    # \param id The identifier of the match constraint.
    # \param rel The relational constraint on the values of matching query/target attribute pairs.
    # \param val The value of the query attribute.
    # 
    def addElement(id: int, rel: Relation, val: CDPL.Base.Any) -> None: pass

    ##
    # \brief 
    # \param values 
    #
    def addElements(values: MatchConstraintList) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \param value 
    #
    def insertElement(idx: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(idx: int, num_elem: int, value: MatchConstraint) -> None: pass

    ##
    # \brief 
    # \param index 
    # \param values 
    #
    def insertElements(index: int, values: MatchConstraintList) -> None: pass

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
    def getFirstElement() -> MatchConstraint: pass

    ##
    # \brief 
    # \return 
    #
    def getLastElement() -> MatchConstraint: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getElement(idx: int) -> MatchConstraint: pass

    ##
    # \brief 
    # \param idx 
    # \param value 
    #
    def setElement(idx: int, value: MatchConstraint) -> None: pass

    ##
    # \brief Returns the logical type of the match constraint list.
    # 
    # \return The logical type of the match constraint list.
    # 
    def getType() -> Type: pass

    ##
    # \brief Sets the logical type of the match constraint list.
    # 
    # \param type The logical type of the match constraint list.
    # 
    def setType(type: Type) -> None: pass

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
    def __getitem__(idx: int) -> MatchConstraint: pass

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
    def __setitem__(index: int, value: MatchConstraint) -> None: pass

    ##
    # \brief Returns a string representation of the \e %MatchConstraintList instance.
    # \param self The \e %MatchConstraintList instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    size = property(getSize)

    type = property(getType, setType)
