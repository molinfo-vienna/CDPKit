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
class ColorTable(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ColorTable instance.
    # \param self The \e %ColorTable instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ColorTable instance.
    # \param self The \e %ColorTable instance to initialize.
    # \param table 
    #
    def __init__(self: object, table: ColorTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ColorTable instance this method is called upon.
    #
    # Different Python \e %ColorTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ColorTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ColorTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \return 
    #
    def getSize(self: ColorTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \return 
    #
    def isEmpty(self: ColorTable) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    #
    def clear(self: ColorTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ColorTable instance \a map.
    # \param self The \e %ColorTable instance this method is called upon.
    # \param map The \e %ColorTable instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ColorTable, map: ColorTable) -> ColorTable: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \return 
    #
    def getValue(self: ColorTable, key: int) -> Color: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \param def_value 
    # \return 
    #
    def getValue(self: ColorTable, key: int, def_value: Color) -> Color: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeEntry(self: ColorTable, key: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setEntry(self: ColorTable, key: int, value: Color) -> None: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \return 
    #
    def getKeys(self: ColorTable) -> object: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \return 
    #
    def getValues(self: ColorTable) -> object: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \return 
    #
    def getEntries(self: ColorTable) -> object: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \return 
    #
    def containsEntry(self: ColorTable, key: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \param value 
    # \return 
    #
    def insertEntry(self: ColorTable, key: int, value: Color) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \return 
    #
    def __len__(self: ColorTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: ColorTable, key: int) -> Color: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: ColorTable, key: int, value: Color) -> None: pass

    ##
    # \brief 
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: ColorTable, key: int) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %ColorTable instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: ColorTable, key: int) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ColorTable instance.
    # \param self The \e %ColorTable instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ColorTable) -> str: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == table</tt>.
    # \param self The \e %ColorTable instance this method is called upon.
    # \param table The \e %ColorTable instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ColorTable, table: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != table</tt>.
    # \param self The \e %ColorTable instance this method is called upon.
    # \param table The \e %ColorTable instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ColorTable, table: object) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    keys = property(getKeys)

    ##
    # \brief 
    #
    values = property(getValues)

    ##
    # \brief 
    #
    entries = property(getEntries)

    ##
    # \brief 
    #
    size = property(getSize)
