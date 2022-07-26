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
    # \param self The \e %GZipIOStream instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GZipIOStream instance.
    # \param self The \e %GZipIOStream instance to initialize.
    # \param ios 
    #
    def __init__(self: object, ios: CDPL.Base.IOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readline(self: GZipIOStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readlines(self: GZipIOStream, size: int = -1) -> list: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \return 
    #
    def xreadlines(self: GZipIOStream) -> GZipIOStream: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def read(self: GZipIOStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \return 
    #
    def tell(self: GZipIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \return 
    #
    def tellr(self: GZipIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seek(self: GZipIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekr(self: GZipIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \return 
    #
    def next(self: GZipIOStream) -> str: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    #
    def flush(self: GZipIOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param string 
    #
    def write(self: GZipIOStream, string: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param iterable 
    #
    def writelines(self: GZipIOStream, iterable: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \return 
    #
    def tellw(self: GZipIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekw(self: GZipIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    #
    def close(self: GZipIOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \param ios 
    #
    def open(self: GZipIOStream, ios: CDPL.Base.IOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %GZipIOStream instance this method is called upon.
    # \return 
    #
    def __iter__(self: GZipIOStream) -> GZipIOStream: pass

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
