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
class CompoundPharmacophoreReader(PharmacophoreReader):

    ##
    # \brief Initializes the \e %CompoundPharmacophoreReader instance.
    # \param self The \e %CompoundPharmacophoreReader instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %CompoundPharmacophoreReader instance.
    # \param self The \e %CompoundPharmacophoreReader instance to initialize.
    # \param reader 
    #
    def __init__(self: object, reader: CompoundPharmacophoreReader) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CompoundPharmacophoreReader instance \a reader.
    # \param self The \e %CompoundPharmacophoreReader instance this method is called upon.
    # \param reader The \e %CompoundPharmacophoreReader instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: CompoundPharmacophoreReader, reader: CompoundPharmacophoreReader) -> CompoundPharmacophoreReader: pass

    ##
    # \brief 
    # \param self The \e %CompoundPharmacophoreReader instance this method is called upon.
    # \return 
    #
    def getNumReaders(self: CompoundPharmacophoreReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %CompoundPharmacophoreReader instance this method is called upon.
    # \param reader 
    #
    def addReader(self: CompoundPharmacophoreReader, reader: PharmacophoreReader) -> None: pass

    ##
    # \brief 
    # \param self The \e %CompoundPharmacophoreReader instance this method is called upon.
    # \param idx 
    #
    def removeReader(self: CompoundPharmacophoreReader, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CompoundPharmacophoreReader instance this method is called upon.
    #
    def clear(self: CompoundPharmacophoreReader) -> None: pass

    ##
    # \brief 
    # \param self The \e %CompoundPharmacophoreReader instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getReader(self: CompoundPharmacophoreReader, idx: int) -> PharmacophoreReader: pass

    ##
    # \brief 
    #
    numReaders = property(getNumReaders)
