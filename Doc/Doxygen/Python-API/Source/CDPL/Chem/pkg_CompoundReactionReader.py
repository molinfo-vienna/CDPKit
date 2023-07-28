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
# \brief CompoundDataReader.
# 
class CompoundReactionReader(ReactionReaderBase):

    ##
    # \brief Initializes the \e %CompoundReactionReader instance.
    # \param self The \e %CompoundReactionReader instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumReaders() -> int: pass

    ##
    # \brief 
    # \param reader 
    #
    def addReader(reader: ReactionReaderBase) -> None: pass

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
    def getReader(idx: int) -> ReactionReaderBase: pass

    numReaders = property(getNumReaders)
