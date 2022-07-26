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
class DRegularGridSetReader(CDPL.Base.DataIOBase):

    ##
    # \brief Initializes the \e %DRegularGridSetReader instance.
    # \param self The \e %DRegularGridSetReader instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \param grid_set 
    # \param overwrite 
    # \return 
    #
    def read(self: DRegularGridSetReader, grid_set: DRegularGridSet, overwrite: bool = True) -> DRegularGridSetReader: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \param idx 
    # \param grid_set 
    # \param overwrite 
    # \return 
    #
    def read(self: DRegularGridSetReader, idx: int, grid_set: DRegularGridSet, overwrite: bool = True) -> DRegularGridSetReader: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \return 
    #
    def skip(self: DRegularGridSetReader) -> DRegularGridSetReader: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \return 
    #
    def hasMoreData(self: DRegularGridSetReader) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \return 
    #
    def getRecordIndex(self: DRegularGridSetReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \param idx 
    #
    def setRecordIndex(self: DRegularGridSetReader, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \return 
    #
    def getNumRecords(self: DRegularGridSetReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    #
    def close(self: DRegularGridSetReader) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \return 
    #
    def __nonzero__(self: DRegularGridSetReader) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularGridSetReader instance this method is called upon.
    # \return 
    #
    def __bool__(self: DRegularGridSetReader) -> bool: pass

    ##
    # \brief 
    #
    numRecords = property(getNumRecords)
