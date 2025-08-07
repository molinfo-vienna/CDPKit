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
# \brief Writer for Vis.Object3D data in any supported format.
# 
# \since 1.3
# 
class Object3DWriter(Object3DWriterBase):

    ##
    # \brief Initializes the \e %Object3DWriter instance.
    # \param file_name 
    # \param mode 
    # 
    def __init__(file_name: str, mode: OpenMode = Base.IOStream.OpenMode(60)) -> None: pass

    ##
    # \brief Initializes the \e %Object3DWriter instance.
    # \param file_name 
    # \param fmt 
    # \param mode 
    # 
    def __init__(file_name: str, fmt: str, mode: OpenMode = Base.IOStream.OpenMode(60)) -> None: pass

    ##
    # \brief Initializes the \e %Object3DWriter instance.
    # \param file_name 
    # \param fmt 
    # \param mode 
    # 
    def __init__(file_name: str, fmt: Base.DataFormat, mode: OpenMode = Base.IOStream.OpenMode(12)) -> None: pass

    ##
    # \brief Initializes the \e %Object3DWriter instance.
    # \param ios 
    # \param fmt 
    # 
    def __init__(ios: Base.IOStream, fmt: str) -> None: pass

    ##
    # \brief Initializes the \e %Object3DWriter instance.
    # \param ios 
    # \param fmt 
    # 
    def __init__(ios: Base.IOStream, fmt: Base.DataFormat) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDataFormat() -> Base.DataFormat: pass

    dataFormat = property(getDataFormat)
