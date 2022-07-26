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
class PharmacophoreReader(CDPL.Base.DataIOBase):

    ##
    # \brief Initializes the \e %PharmacophoreReader instance.
    # \param self The \e %PharmacophoreReader instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \param pharm 
    # \param overwrite 
    # \return 
    #
    def read(self: PharmacophoreReader, pharm: Pharmacophore, overwrite: bool = True) -> PharmacophoreReader: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \param idx 
    # \param pharm 
    # \param overwrite 
    # \return 
    #
    def read(self: PharmacophoreReader, idx: int, pharm: Pharmacophore, overwrite: bool = True) -> PharmacophoreReader: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \return 
    #
    def skip(self: PharmacophoreReader) -> PharmacophoreReader: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \return 
    #
    def hasMoreData(self: PharmacophoreReader) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \return 
    #
    def getRecordIndex(self: PharmacophoreReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \param idx 
    #
    def setRecordIndex(self: PharmacophoreReader, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \return 
    #
    def getNumRecords(self: PharmacophoreReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    #
    def close(self: PharmacophoreReader) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \return 
    #
    def __nonzero__(self: PharmacophoreReader) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreReader instance this method is called upon.
    # \return 
    #
    def __bool__(self: PharmacophoreReader) -> bool: pass

    ##
    # \brief 
    #
    numRecords = property(getNumRecords)
