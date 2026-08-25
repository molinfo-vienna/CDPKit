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
# \brief Bidirectional stream that transparently (de)compresses bzip2 data.
# 
class BZip2IOStream(Base.IOStream):

    ##
    # \brief Initializes the \c %BZip2IOStream instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \c %BZip2IOStream instance.
    # \param ios 
    # 
    def __init__(ios: Base.IOStream) -> None: pass

    def readline(size: int = -1) -> str: pass

    def readlines(size: int = -1) -> list: pass

    def xreadlines() -> BZip2IOStream: pass

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

    def close() -> None: pass

    def open(ios: Base.IOStream) -> None: pass

    def __iter__() -> BZip2IOStream: pass

    closed = property(isClosed)

    mode = property(getOpenModeString)

    modeFlags = property(getOpenModeFlags)

    softspace = property(getSoftSpace, setSoftSpace)
