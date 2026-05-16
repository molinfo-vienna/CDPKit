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
# \brief Reader for grid data of type Grid.DRegularGrid in any supported format.
# 
class DRegularGridReader(DRegularGridReaderBase):

    ##
    # \brief Constructs a reader for the file <em>file_name</em> with format detected from its extension.
    # 
    # \param file_name The path of the input file.
    # \param mode The flags specifying the file open mode.
    # 
    # \throw Base.IOError if no input handler for the file extension is registered.
    # 
    def __init__(file_name: str, mode: OpenMode = Base.IOStream.OpenMode(12)) -> None: pass

    ##
    # \brief Constructs a reader for the file <em>file_name</em> using the format described by <em>fmt</em>.
    # 
    # \param file_name The path of the input file.
    # \param fmt The Base.DataFormat instance describing the format.
    # \param mode The flags specifying the file open mode.
    # 
    # \throw Base.IOError if no input handler for <em>fmt</em> is registered.
    # 
    def __init__(file_name: str, fmt: str, mode: OpenMode = Base.IOStream.OpenMode(12)) -> None: pass

    ##
    # \brief Constructs a reader for the file <em>file_name</em> using the format described by <em>fmt</em>.
    # 
    # \param file_name The path of the input file.
    # \param fmt The Base.DataFormat instance describing the format.
    # \param mode The flags specifying the file open mode.
    # 
    # \throw Base.IOError if no input handler for <em>fmt</em> is registered.
    # 
    def __init__(file_name: str, fmt: Base.DataFormat, mode: OpenMode = Base.IOStream.OpenMode(12)) -> None: pass

    ##
    # \brief Constructs a reader for the input stream <em>is</em> using the format described by <em>fmt</em>.
    # 
    # \param is The input stream providing the data.
    # \param fmt The Base.DataFormat instance describing the format.
    # 
    # \throw Base.IOError if no input handler for <em>fmt</em> is registered.
    # 
    def __init__(is: Base.IStream, fmt: str) -> None: pass

    ##
    # \brief Constructs a reader for the input stream <em>is</em> using the format described by <em>fmt</em>.
    # 
    # \param is The input stream providing the data.
    # \param fmt The Base.DataFormat instance describing the format.
    # 
    # \throw Base.IOError if no input handler for <em>fmt</em> is registered.
    # 
    def __init__(is: Base.IStream, fmt: Base.DataFormat) -> None: pass

    ##
    # \brief Returns the data format the wrapped reader was instantiated for.
    # 
    # \return The data format.
    # 
    def getDataFormat() -> Base.DataFormat: pass

    dataFormat = property(getDataFormat)
