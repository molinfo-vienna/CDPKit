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
# \brief Output stream that transparently writes bzip2-compressed data.
# 
class BZip2OStream(Base.OStream):

    ##
    # \brief Initializes the \c %BZip2OStream instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \c %BZip2OStream instance.
    # \param os 
    # 
    def __init__(os: Base.OStream) -> None: pass

    def flush() -> None: pass

    def write(string: object) -> None: pass

    def writelines(iterable: object) -> None: pass

    def tellw() -> int: pass

    def seekw(offs: int, whence: int = 0) -> None: pass

    def isClosed() -> bool: pass

    def getOpenModeString() -> str: pass

    def getOpenModeFlags() -> OpenMode: pass

    def getSoftSpace() -> bool: pass

    def setSoftSpace(value: bool) -> None: pass

    def close() -> None: pass

    def open(os: Base.OStream) -> None: pass

    closed = property(isClosed)

    softspace = property(getSoftSpace, setSoftSpace)

    mode = property(getOpenModeString)

    modeFlags = property(getOpenModeFlags)
