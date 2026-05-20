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
# \brief Composite Base.DataReader that aggregates several underlying readers and presents their records as one contiguous record stream.
# 
class CompoundReactionReader(ReactionReaderBase):

    ##
    # \brief Constructs an empty <tt>CompoundDataReader</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the number of underlying readers.
    # 
    # \return The reader count.
    # 
    def getNumReaders() -> int: pass

    ##
    # \brief Appends <em>reader</em> to the list of underlying readers.
    # 
    # \param reader The reader to add.
    # 
    def addReader(reader: ReactionReaderBase) -> None: pass

    ##
    # \brief Removes the reader at index <em>idx</em> from the list of underlying readers.
    # 
    # \param idx The zero-based reader index.
    # 
    def removeReader(idx: int) -> None: pass

    ##
    # \brief Removes all underlying readers.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the underlying reader at index <em>idx</em>.
    # 
    # \param idx The zero-based reader index.
    # 
    # \return A reference to the reader shared reference.
    # 
    def getReader(idx: int) -> ReactionReaderBase: pass

    numReaders = property(getNumReaders)
