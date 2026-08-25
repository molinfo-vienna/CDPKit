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
# \brief Container for the storage and lookup of Vis.Color objects that are associated with a numeric identifier.
# 
class ColorTable(Boost.Python.instance):

    ##
    # \brief Constructs an empty color table.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %ColorTable instance \a table.
    # \param table The \c %ColorTable instance to copy.
    # 
    def __init__(table: ColorTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ColorTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ColorTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getSize() -> int: pass

    def isEmpty() -> bool: pass

    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ColorTable instance \a map.
    # \param map The \c %ColorTable instance to copy.
    # \return \a self
    # 
    def assign(map: ColorTable) -> ColorTable: pass

    def getValue(key: int) -> Color: pass

    def getValue(key: int, def_value: Color) -> Color: pass

    def removeEntry(key: int) -> bool: pass

    def setEntry(key: int, value: Color) -> None: pass

    def getKeys() -> object: pass

    def keys() -> object: pass

    def getValues() -> object: pass

    def values() -> object: pass

    def getEntries() -> object: pass

    def items() -> object: pass

    def containsEntry(key: int) -> bool: pass

    def insertEntry(key: int, value: Color) -> bool: pass

    def __len__() -> int: pass

    def __getitem__(key: int) -> Color: pass

    def __setitem__(key: int, value: Color) -> None: pass

    def __delitem__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: int) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %ColorTable instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == table</tt>.
    # \param table The \c %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(table: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != table</tt>.
    # \param table The \c %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(table: object) -> bool: pass

    objectID = property(getObjectID)

    size = property(getSize)
