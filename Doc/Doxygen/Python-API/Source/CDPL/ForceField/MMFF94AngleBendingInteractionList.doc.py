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
# \brief Data structure for the storage of MMFF94 angle-bending interaction parameter records.
# 
# \see [\ref MMFF94]
# 
class MMFF94AngleBendingInteractionList(Boost.Python.instance):

    ##
    # \brief Initializes the \c %MMFF94AngleBendingInteractionList instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94AngleBendingInteractionList instance \a ia_list.
    # \param ia_list The \c %MMFF94AngleBendingInteractionList instance to copy.
    # 
    def __init__(ia_list: MMFF94AngleBendingInteractionList) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94AngleBendingInteractionList instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94AngleBendingInteractionList instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getSize() -> int: pass

    def isEmpty() -> bool: pass

    def resize(num_elem: int, value: MMFF94AngleBendingInteraction) -> None: pass

    def reserve(num_elem: int) -> None: pass

    def getCapacity() -> int: pass

    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94AngleBendingInteractionList instance \a array.
    # \param array The \c %MMFF94AngleBendingInteractionList instance to copy.
    # \return \a self
    # 
    def assign(array: MMFF94AngleBendingInteractionList) -> MMFF94AngleBendingInteractionList: pass

    def assign(num_elem: int, value: MMFF94AngleBendingInteraction) -> None: pass

    def addElement(value: MMFF94AngleBendingInteraction) -> None: pass

    def addElements(values: MMFF94AngleBendingInteractionList) -> None: pass

    def insertElement(idx: int, value: MMFF94AngleBendingInteraction) -> None: pass

    def insertElements(idx: int, num_elem: int, value: MMFF94AngleBendingInteraction) -> None: pass

    def insertElements(index: int, values: MMFF94AngleBendingInteractionList) -> None: pass

    def popLastElement() -> None: pass

    def removeElement(idx: int) -> None: pass

    def removeElements(begin_idx: int, end_idx: int) -> None: pass

    def getFirstElement() -> MMFF94AngleBendingInteraction: pass

    def getLastElement() -> MMFF94AngleBendingInteraction: pass

    def getElement(idx: int) -> MMFF94AngleBendingInteraction: pass

    def setElement(idx: int, value: MMFF94AngleBendingInteraction) -> None: pass

    def __delitem__(idx: int) -> None: pass

    def __getitem__(idx: int) -> MMFF94AngleBendingInteraction: pass

    def __len__() -> int: pass

    def __setitem__(index: int, value: MMFF94AngleBendingInteraction) -> None: pass

    objectID = property(getObjectID)

    size = property(getSize)
