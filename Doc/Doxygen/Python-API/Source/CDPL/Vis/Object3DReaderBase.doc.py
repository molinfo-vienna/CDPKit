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
# \brief 
#
class Object3DReaderBase(Base.DataIOBase):

    ##
    # \brief Initializes the \e %Object3DReaderBase instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief 
    # \param obj 
    # \param overwrite 
    # \return 
    #
    def read(obj: Object3D, overwrite: bool = True) -> Object3DReaderBase: pass

    ##
    # \brief 
    # \param idx 
    # \param obj 
    # \param overwrite 
    # \return 
    #
    def read(idx: int, obj: Object3D, overwrite: bool = True) -> Object3DReaderBase: pass

    ##
    # \brief 
    # \return 
    #
    def skip() -> Object3DReaderBase: pass

    ##
    # \brief 
    # \return 
    #
    def hasMoreData() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getRecordIndex() -> int: pass

    ##
    # \brief 
    # \param idx 
    #
    def setRecordIndex(idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumRecords() -> int: pass

    ##
    # \brief 
    #
    def close() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __nonzero__() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    numRecords = property(getNumRecords)
