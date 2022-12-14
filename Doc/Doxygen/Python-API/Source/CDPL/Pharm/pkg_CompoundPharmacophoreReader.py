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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %CompoundPharmacophoreReader instance.
    # \param reader 
    #
    def __init__(reader: CompoundPharmacophoreReader) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CompoundPharmacophoreReader instance \a reader.
    # \param reader The \e %CompoundPharmacophoreReader instance to copy.
    # \return \a self
    #
    def assign(reader: CompoundPharmacophoreReader) -> CompoundPharmacophoreReader: pass

    ##
    # \brief 
    # \return 
    #
    def getNumReaders() -> int: pass

    ##
    # \brief 
    # \param reader 
    #
    def addReader(reader: PharmacophoreReader) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeReader(idx: int) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getReader(idx: int) -> PharmacophoreReader: pass

    ##
    # \brief 
    #
    numReaders = property(getNumReaders)
