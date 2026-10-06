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
# \brief Wrapper for C++ \c std::iostream instances.
# 
class IOStream(IStream, OStream):

    ##
    # \brief Provides as set of stream open mode flags that mirror those defined in C++ class \c std::ios_base.
    # 
    class OpenMode(Boost.Python.enum):

        ##
        # \brief Specifies to open the stream for reading.
        # 
        IN = 8

        ##
        # \brief Specifies to open the stream for writing.
        # 
        OUT = 16

        ##
        # \brief Specifies to discard the contents of the stream when opening.
        # 
        TRUNC = 32

        ##
        # \brief Specifies to seek to the end of stream before each write.
        # 
        APP = 1

        ##
        # \brief Specifies to seek to the end of stream immediately after opening.
        # 
        ATE = 2

        ##
        # \brief Specifies to open the stream for binary data I/O.
        # 
        BIN = 4
