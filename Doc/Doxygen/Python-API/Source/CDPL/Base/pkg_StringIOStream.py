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
class StringIOStream(IOStream):

    ##
    # \brief Initializes the \e %StringIOStream instance.
    # \param self The \e %StringIOStream instance to initialize.
    # \param string 
    # \param mode 
    #
    def __init__(self: object, string: str = '', mode: str = 'r+') -> None: pass

    ##
    # \brief Initializes the \e %StringIOStream instance.
    # \param self The \e %StringIOStream instance to initialize.
    # \param string 
    # \param mode 
    #
    def __init__(self: object, string: str = '', mode: OpenMode = CDPL.Base.OpenMode(24)) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readline(self: StringIOStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readlines(self: StringIOStream, size: int = -1) -> list: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def xreadlines(self: StringIOStream) -> StringIOStream: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def read(self: StringIOStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def tell(self: StringIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def tellr(self: StringIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seek(self: StringIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekr(self: StringIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def next(self: StringIOStream) -> str: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    #
    def flush(self: StringIOStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param string 
    #
    def write(self: StringIOStream, string: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param iterable 
    #
    def writelines(self: StringIOStream, iterable: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def tellw(self: StringIOStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekw(self: StringIOStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def isatty(self: StringIOStream) -> bool: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param length 
    #
    def truncate(self: StringIOStream, length: int = -1) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def getvalue(self: StringIOStream) -> str: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \param value 
    #
    def setvalue(self: StringIOStream, value: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %StringIOStream instance this method is called upon.
    # \return 
    #
    def __iter__(self: StringIOStream) -> StringIOStream: pass

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
    value = property(getValue, setValue)
