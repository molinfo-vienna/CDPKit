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
class FRegularGridSet(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FRegularGridSet instance.
    # \param self The \e %FRegularGridSet instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGridSet instance.
    # \param self The \e %FRegularGridSet instance to initialize.
    # \param set 
    #
    def __init__(self: object, set: FRegularGridSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FRegularGridSet instance this method is called upon.
    #
    # Different Python \e %FRegularGridSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FRegularGridSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FRegularGridSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \return 
    #
    def getSize(self: FRegularGridSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FRegularGridSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: FRegularGridSet, num_elem: int, value: FRegularGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: FRegularGridSet, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \return 
    #
    def getCapacity(self: FRegularGridSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    #
    def clear(self: FRegularGridSet) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularGridSet instance \a array.
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param array The \e %FRegularGridSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FRegularGridSet, array: FRegularGridSet) -> FRegularGridSet: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularGridSet instance \a num_elem.
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param num_elem The \e %FRegularGridSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FRegularGridSet, num_elem: int, value: FRegularGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param value 
    #
    def addElement(self: FRegularGridSet, value: FRegularGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param values 
    #
    def addElements(self: FRegularGridSet, values: FRegularGridSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: FRegularGridSet, idx: int, value: FRegularGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: FRegularGridSet, idx: int, num_elem: int, value: FRegularGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: FRegularGridSet, index: int, values: FRegularGridSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    #
    def popLastElement(self: FRegularGridSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: FRegularGridSet, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: FRegularGridSet, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: FRegularGridSet) -> FRegularGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \return 
    #
    def getLastElement(self: FRegularGridSet) -> FRegularGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: FRegularGridSet, idx: int) -> FRegularGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: FRegularGridSet, idx: int, value: FRegularGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: FRegularGridSet, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: FRegularGridSet, idx: int) -> FRegularGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \return 
    #
    def __len__(self: FRegularGridSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: FRegularGridSet, index: int, value: FRegularGrid) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == set</tt>.
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param set The \e %FRegularGridSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FRegularGridSet, set: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != set</tt>.
    # \param self The \e %FRegularGridSet instance this method is called upon.
    # \param set The \e %FRegularGridSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FRegularGridSet, set: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
