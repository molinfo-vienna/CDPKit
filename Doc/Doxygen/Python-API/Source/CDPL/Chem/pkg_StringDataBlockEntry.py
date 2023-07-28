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
# \brief Represents a data item in the structure or reaction data block of a <em>MDL SD-</em> or <em>RD-File</em> data record (see [\ref CTFILE]).
# 
class StringDataBlockEntry(Boost.Python.instance):

    ##
    # \brief Constructs a <tt>StringDataBlockEntry</tt> object with an empty data header and content.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %StringDataBlockEntry instance.
    # \param self The \e %StringDataBlockEntry instance to initialize.
    # \param entry 
    # 
    def __init__(entry: StringDataBlockEntry) -> None: pass

    ##
    # \brief Constructs a <tt>StringDataBlockEntry</tt> object with the specified data header and content.
    # 
    # \param header The data header.
    # \param data The data content.
    # 
    def __init__(header: str, data: str) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param entry 
    # \return 
    #
    def assign(entry: StringDataBlockEntry) -> StringDataBlockEntry: pass

    ##
    # \brief Returns the data header.
    # 
    # \return The data header.
    # 
    def getHeader() -> str: pass

    ##
    # \brief Sets the data header.
    # 
    # \param header The new data header.
    # 
    def setHeader(header: str) -> None: pass

    ##
    # \brief Returns the stored data content.
    # 
    # \return The stored data content.
    # 
    def getData() -> str: pass

    ##
    # \brief Sets the data content.
    # 
    # \param data The new data content.
    # 
    def setData(data: str) -> None: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param entry The other <tt>StringDataBlockEntry</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the data entry headers and values compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(entry: StringDataBlockEntry) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == entry)</tt>.
    # 
    # \param entry The other <tt>StringDataBlockEntry</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the data headers and/or values compare non-equal, and <tt>False</tt> otherwise. 
    # 
    # \see __eq__()
    # 
    def __ne__(entry: StringDataBlockEntry) -> bool: pass

    objectID = property(getObjectID)

    header = property(getHeader, setHeader)

    data = property(getData, setData)
