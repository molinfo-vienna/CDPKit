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
class FileIOStream(IOStream):

    ##
    # \brief Initializes the \e %FileIOStream instance.
    # \param self The \e %FileIOStream instance to initialize.
    # \param file_name 
    # \param mode 
    #
    def __init__(self: object, file_name: str, mode: str = 'r') -> None: pass

    ##
    # \brief Initializes the \e %FileIOStream instance.
    # \param self The \e %FileIOStream instance to initialize.
    # \param file_name 
    # \param mode 
    #
    def __init__(self: object, file_name: str, mode: OpenMode = CDPL.Base.OpenMode.IN) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readline(self: FileIOStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readlines(self: FileIOStream, size: int = -1) -> list: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \return 
    #
    def xreadlines(self: FileIOStream) -> FileIOStream: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def read(self: FileIOStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \return 
    #
    def tell(self: FileIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \return 
    #
    def tellr(self: FileIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seek(self: FileIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekr(self: FileIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \return 
    #
    def next(self: FileIOStream) -> str: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    #
    def flush(self: FileIOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param string 
    #
    def write(self: FileIOStream, string: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param iterable 
    #
    def writelines(self: FileIOStream, iterable: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \return 
    #
    def tellw(self: FileIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekw(self: FileIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    #
    def close(self: FileIOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %FileIOStream instance this method is called upon.
    # \return 
    #
    def __iter__(self: FileIOStream) -> FileIOStream: pass

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

    ##
    # \brief FIXME!
    #
    name = property(getName)
