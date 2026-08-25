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
# \brief Data structure storing a set of (shared) Gaussian shapes.
# 
# <tt>GaussianShapeSet</tt> is an indirect array of Shape.GaussianShape smart references, typically used as input to alignment / overlap routines that operate on multiple shapes at once.
# 
class GaussianShapeSet(Boost.Python.instance):

    ##
    # \brief Initializes the \c %GaussianShapeSet instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %GaussianShapeSet instance \a list.
    # \param list The \c %GaussianShapeSet instance to copy.
    # 
    def __init__(list: GaussianShapeSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getSize() -> int: pass

    def isEmpty() -> bool: pass

    def resize(num_elem: int, value: GaussianShape) -> None: pass

    def reserve(num_elem: int) -> None: pass

    def getCapacity() -> int: pass

    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %GaussianShapeSet instance \a array.
    # \param array The \c %GaussianShapeSet instance to copy.
    # \return \a self
    # 
    def assign(array: GaussianShapeSet) -> GaussianShapeSet: pass

    def assign(num_elem: int, value: GaussianShape) -> None: pass

    def addElement(value: GaussianShape) -> None: pass

    def addElements(values: GaussianShapeSet) -> None: pass

    def insertElement(idx: int, value: GaussianShape) -> None: pass

    def insertElements(idx: int, num_elem: int, value: GaussianShape) -> None: pass

    def insertElements(index: int, values: GaussianShapeSet) -> None: pass

    def popLastElement() -> None: pass

    def removeElement(idx: int) -> None: pass

    def removeElements(begin_idx: int, end_idx: int) -> None: pass

    def getFirstElement() -> GaussianShape: pass

    def getLastElement() -> GaussianShape: pass

    def getElement(idx: int) -> GaussianShape: pass

    def setElement(idx: int, value: GaussianShape) -> None: pass

    def __delitem__(idx: int) -> None: pass

    def __getitem__(idx: int) -> GaussianShape: pass

    def __len__() -> int: pass

    def __setitem__(index: int, value: GaussianShape) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == list</tt>.
    # \param list The \c %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(list: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != list</tt>.
    # \param list The \c %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(list: object) -> bool: pass

    objectID = property(getObjectID)

    size = property(getSize)
