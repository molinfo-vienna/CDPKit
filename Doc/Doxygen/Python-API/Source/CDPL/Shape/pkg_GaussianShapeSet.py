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
class GaussianShapeSet(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GaussianShapeSet instance.
    # \param self The \e %GaussianShapeSet instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeSet instance.
    # \param self The \e %GaussianShapeSet instance to initialize.
    # \param list 
    #
    def __init__(self: object, list: GaussianShapeSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    #
    # Different Python \e %GaussianShapeSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \return 
    #
    def getSize(self: GaussianShapeSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \return 
    #
    def isEmpty(self: GaussianShapeSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param num_elem 
    # \param value 
    #
    def resize(self: GaussianShapeSet, num_elem: int, value: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param num_elem 
    #
    def reserve(self: GaussianShapeSet, num_elem: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \return 
    #
    def getCapacity(self: GaussianShapeSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    #
    def clear(self: GaussianShapeSet) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShapeSet instance \a array.
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param array The \e %GaussianShapeSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: GaussianShapeSet, array: GaussianShapeSet) -> GaussianShapeSet: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShapeSet instance \a num_elem.
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param num_elem The \e %GaussianShapeSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: GaussianShapeSet, num_elem: int, value: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param value 
    #
    def addElement(self: GaussianShapeSet, value: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param values 
    #
    def addElements(self: GaussianShapeSet, values: GaussianShapeSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def insertElement(self: GaussianShapeSet, idx: int, value: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    # \param num_elem 
    # \param value 
    #
    def insertElements(self: GaussianShapeSet, idx: int, num_elem: int, value: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param index 
    # \param values 
    #
    def insertElements(self: GaussianShapeSet, index: int, values: GaussianShapeSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    #
    def popLastElement(self: GaussianShapeSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: GaussianShapeSet, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param begin_idx 
    # \param end_idx 
    #
    def removeElements(self: GaussianShapeSet, begin_idx: int, end_idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \return 
    #
    def getFirstElement(self: GaussianShapeSet) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \return 
    #
    def getLastElement(self: GaussianShapeSet) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: GaussianShapeSet, idx: int) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def setElement(self: GaussianShapeSet, idx: int, value: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: GaussianShapeSet, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: GaussianShapeSet, idx: int) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \return 
    #
    def __len__(self: GaussianShapeSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param index 
    # \param value 
    #
    def __setitem__(self: GaussianShapeSet, index: int, value: GaussianShape) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == list</tt>.
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param list The \e %GaussianShapeSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: GaussianShapeSet, list: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != list</tt>.
    # \param self The \e %GaussianShapeSet instance this method is called upon.
    # \param list The \e %GaussianShapeSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: GaussianShapeSet, list: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
