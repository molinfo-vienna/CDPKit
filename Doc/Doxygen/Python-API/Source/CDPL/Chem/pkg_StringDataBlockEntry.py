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
class StringDataBlockEntry(Boost.Python.instance):

    ##
    # \brief Initializes the \e %StringDataBlockEntry instance.
    # \param self The \e %StringDataBlockEntry instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %StringDataBlockEntry instance.
    # \param self The \e %StringDataBlockEntry instance to initialize.
    # \param entry 
    #
    def __init__(self: object, entry: StringDataBlockEntry) -> None: pass

    ##
    # \brief Initializes the \e %StringDataBlockEntry instance.
    # \param self The \e %StringDataBlockEntry instance to initialize.
    # \param header 
    # \param data 
    #
    def __init__(self: object, header: str, data: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    #
    # Different Python \e %StringDataBlockEntry instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StringDataBlockEntry instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: StringDataBlockEntry) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %StringDataBlockEntry instance \a entry.
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \param entry The \e %StringDataBlockEntry instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: StringDataBlockEntry, entry: StringDataBlockEntry) -> StringDataBlockEntry: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \return 
    #
    def getHeader(self: StringDataBlockEntry) -> str: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \param header 
    #
    def setHeader(self: StringDataBlockEntry, header: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \return 
    #
    def getData(self: StringDataBlockEntry) -> str: pass

    ##
    # \brief 
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \param data 
    #
    def setData(self: StringDataBlockEntry, data: str) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == entry</tt>.
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \param entry The \e %StringDataBlockEntry instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: StringDataBlockEntry, entry: StringDataBlockEntry) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != entry</tt>.
    # \param self The \e %StringDataBlockEntry instance this method is called upon.
    # \param entry The \e %StringDataBlockEntry instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: StringDataBlockEntry, entry: StringDataBlockEntry) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    header = property(getHeader, setHeader)

    ##
    # \brief 
    #
    data = property(getData, setData)
