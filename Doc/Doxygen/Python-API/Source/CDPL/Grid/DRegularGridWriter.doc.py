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
# \brief Writer for grid data of type Grid.DRegularGrid in any supported format.
# 
class DRegularGridWriter(DRegularGridWriterBase):

    ##
    # \brief Constructs a <tt>MultiFormatDataWriter</tt> that opens <em>file_name</em> and deduces the output format from its name.
    # 
    # \param file_name The output-file name.
    # \param mode The open mode of the underlying file stream.
    # 
    # \throw Base.IOError if no matching output handler was found.
    # 
    def __init__(file_name: str, mode: OpenMode = Base.IOStream.OpenMode(60)) -> None: pass

    ##
    # \brief Constructs a <tt>MultiFormatDataWriter</tt> that opens <em>file_name</em> and uses the output handler matching the Base.DataFormat <em>fmt</em>.
    # 
    # \param file_name The output-file name.
    # \param fmt The output format identifier.
    # \param mode The open mode of the underlying file stream.
    # 
    # \throw Base.IOError if no matching output handler was found.
    # 
    def __init__(file_name: str, fmt: str, mode: OpenMode = Base.IOStream.OpenMode(60)) -> None: pass

    ##
    # \brief Constructs a <tt>MultiFormatDataWriter</tt> that opens <em>file_name</em> and uses the output handler matching the Base.DataFormat <em>fmt</em>.
    # 
    # \param file_name The output-file name.
    # \param fmt The output format identifier.
    # \param mode The open mode of the underlying file stream.
    # 
    # \throw Base.IOError if no matching output handler was found.
    # 
    def __init__(file_name: str, fmt: Base.DataFormat, mode: OpenMode = Base.IOStream.OpenMode(12)) -> None: pass

    ##
    # \brief Constructs a <tt>MultiFormatDataWriter</tt> that wraps <em>ios</em> and uses the output handler matching the Base.DataFormat <em>fmt</em>.
    # 
    # \param ios The output stream to wrap.
    # \param fmt The output format identifier.
    # 
    # \throw Base.IOError if no matching output handler was found.
    # 
    def __init__(ios: Base.IOStream, fmt: str) -> None: pass

    ##
    # \brief Constructs a <tt>MultiFormatDataWriter</tt> that wraps <em>ios</em> and uses the output handler matching the Base.DataFormat <em>fmt</em>.
    # 
    # \param ios The output stream to wrap.
    # \param fmt The output format identifier.
    # 
    # \throw Base.IOError if no matching output handler was found.
    # 
    def __init__(ios: Base.IOStream, fmt: Base.DataFormat) -> None: pass

    ##
    # \brief Returns the data format actually used by the wrapped output handler.
    # 
    # \return A reference to the resolved Base.DataFormat.
    # 
    def getDataFormat() -> Base.DataFormat: pass

    dataFormat = property(getDataFormat)
