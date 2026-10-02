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
# \brief Wrapper for C++ \c std::fstream exposing a Python-style file-oriented I/O interface.
# 
class FileIOStream(IOStream):

    ##
    # \brief Construct the \c FileIOStream instance and opens the specified file in the given mode.
    # \param file_name The path to the file to open.
    # \param mode A combination of file open mode flags (see IOStream.OpenMode) or a Python-style open mode string (e.g. 'r+').
    # 
    def __init__(file_name: str, mode: str = 'r') -> None: pass

    ##
    # \brief Construct the \c FileIOStream instance and opens the specified file in the given mode.
    # \param file_name The path to the file to open.
    # \param mode A combination of file open mode flags (see IOStream.OpenMode) or a Python-style open mode string (e.g. 'r+').
    # 
    def __init__(file_name: str, mode: OpenMode = IOStream.OpenMode.IN) -> None: pass

    def readline(size: int = -1) -> str: pass

    def readlines(size: int = -1) -> list: pass

    def xreadlines() -> FileIOStream: pass

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
    # \brief Closes the file.
    # 
    # A closed file cannot be read or written any more. Any operation which requires that the file be open will raise a
    # \c ValueError after the file has been closed. Calling close() more than once is allowed.
    # 
    def close() -> None: pass

    ##
    # \brief Return the file path string that got passed to the constructor.
    # \return The file path string that got passed to the constructor.
    # 
    def getFileName() -> str: pass

    def __iter__() -> FileIOStream: pass

    closed = property(isClosed)

    mode = property(getOpenModeString)

    modeFlags = property(getOpenModeFlags)

    softspace = property(getSoftSpace, setSoftSpace)

    name = property(getFileName)
