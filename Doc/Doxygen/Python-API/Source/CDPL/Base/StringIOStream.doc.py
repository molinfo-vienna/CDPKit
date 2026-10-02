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
# \brief Wrapper for C++ \c std::stringstream exposing a Python-style file-oriented I/O interface.
# 
class StringIOStream(IOStream):

    ##
    # \brief Construct the \c StringIOStream instance for the given string.
    # \param string The string to use as initial content of the string stream.
    # \param mode A combination of open mode flags (see IOStream.OpenMode) or a Python-style open mode string (e.g. 'r+').
    # 
    def __init__(string: str = '', mode: str = 'r+') -> None: pass

    ##
    # \brief Construct the \c StringIOStream instance for the given string.
    # \param string The string to use as initial content of the string stream.
    # \param mode A combination of open mode flags (see IOStream.OpenMode) or a Python-style open mode string (e.g. 'r+').
    # 
    def __init__(string: str = '', mode: OpenMode = IOStream.OpenMode(24)) -> None: pass

    def readline(size: int = -1) -> str: pass

    def readlines(size: int = -1) -> list: pass

    def xreadlines() -> StringIOStream: pass

    def read(size: int = -1) -> str: pass

    def tell() -> int: pass

    def tellr() -> int: pass

    def seek(offs: int, whence: int = 0) -> None: pass

    def seekr(offs: int, whence: int = 0) -> None: pass

    def next() -> str: pass

    def isClosed() -> bool: pass

    def getOpenModeString() -> str: pass

    def getOpenModeFlags() -> OpenMode: pass

    def flush() -> None: pass

    def write(string: object) -> None: pass

    def writelines(iterable: object) -> None: pass

    def tellw() -> int: pass

    def seekw(offs: int, whence: int = 0) -> None: pass

    def getSoftSpace() -> bool: pass

    def setSoftSpace(value: bool) -> None: pass

    ##
    # \brief Returns always \c False.
    # \return \c False.
    # 
    def isatty() -> bool: pass

    ##
    # \brief Truncates the contained string to the specified length.
    # 
    # If the optional \a length argument is present, the string is truncated to (at most) that size.
    # The size defaults to the current I/O position.
    # Note that if a specified length exceeds the strings' current size, the string is extended to the specified size with zeros.
    # 
    # \param length The new size of the string or, by default, the current I/O position.
    # \note The current I/O position will be reset to zero.
    # 
    def truncate(length: int = -1) -> None: pass

    ##
    # \brief Returns the current string stream content.
    # \return The current string stream content.
    # 
    def getvalue() -> str: pass

    ##
    # \brief Returns the current string stream content as \c bytes object.
    # \return The current string stream content as \c bytes object.
    # 
    def getbytes() -> object: pass

    ##
    # \brief Replace the current string stream content by \a value.
    # \param value The new content of the string stream.
    # \note The current I/O position will be reset to zero.
    # 
    def setvalue(value: str) -> None: pass

    def __iter__() -> StringIOStream: pass

    closed = property(isClosed)

    mode = property(getOpenModeString)

    modeFlags = property(getOpenModeFlags)

    softspace = property(getSoftSpace, setSoftSpace)

    value = property(getvalue, setvalue)
