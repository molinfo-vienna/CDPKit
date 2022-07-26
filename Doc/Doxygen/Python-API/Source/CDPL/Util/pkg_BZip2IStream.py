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
class BZip2IStream(CDPL.Base.IStream):

    ##
    # \brief Initializes the \e %BZip2IStream instance.
    # \param self The \e %BZip2IStream instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BZip2IStream instance.
    # \param self The \e %BZip2IStream instance to initialize.
    # \param is 
    #
    def __init__(self: object, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readline(self: BZip2IStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def readlines(self: BZip2IStream, size: int = -1) -> list: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \return 
    #
    def xreadlines(self: BZip2IStream) -> BZip2IStream: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \param size 
    # \return 
    #
    def read(self: BZip2IStream, size: int = -1) -> str: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \return 
    #
    def tell(self: BZip2IStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \return 
    #
    def tellr(self: BZip2IStream) -> int: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seek(self: BZip2IStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \param offs 
    # \param whence 
    #
    def seekr(self: BZip2IStream, offs: int, whence: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \return 
    #
    def next(self: BZip2IStream) -> str: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    #
    def close(self: BZip2IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \param is 
    #
    def open(self: BZip2IStream, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %BZip2IStream instance this method is called upon.
    # \return 
    #
    def __iter__(self: BZip2IStream) -> BZip2IStream: pass

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
