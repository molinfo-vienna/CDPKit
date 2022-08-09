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
class GZipIOStream(CDPL.Base.IOStream):

    ##
    # \brief Initializes the \e %GZipIOStream instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GZipIOStream instance.
    # \param ios 
    #
    def __init__(ios: CDPL.Base.IOStream) -> None: pass

    ##
    # \brief 
    # \param size 
    # \return 
    #
    def readline(size: int = -1) -> str: pass

    ##
    # \brief 
    # \param size 
    # \return 
    #
    def readlines(size: int = -1) -> list: pass

    ##
    # \brief 
    # \return 
    #
    def xreadlines() -> GZipIOStream: pass

    ##
    # \brief 
    # \param size 
    # \return 
    #
    def read(size: int = -1) -> str: pass

    ##
    # \brief 
    # \return 
    #
    def tell() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def tellr() -> int: pass

    ##
    # \brief 
    # \param offs 
    # \param whence 
    #
    def seek(offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param offs 
    # \param whence 
    #
    def seekr(offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def next() -> str: pass

    ##
    # \brief 
    #
    def flush() -> None: pass

    ##
    # \brief 
    # \param string 
    #
    def write(string: object) -> None: pass

    ##
    # \brief 
    # \param iterable 
    #
    def writelines(iterable: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def tellw() -> int: pass

    ##
    # \brief 
    # \param offs 
    # \param whence 
    #
    def seekw(offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    #
    def close() -> None: pass

    ##
    # \brief 
    # \param ios 
    #
    def open(ios: CDPL.Base.IOStream) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __iter__() -> GZipIOStream: pass

    ##
    # \brief FIXME!
    #
    closed = property(getClosed)

    ##
    # \brief FIXME!
    #
    mode = property(getMode)

    ##
    # \brief FIXME!
    #
    modeFlags = property(getModeFlags)

    ##
    # \brief FIXME!
    #
    softspace = property(getSoftspace, setSoftspace)