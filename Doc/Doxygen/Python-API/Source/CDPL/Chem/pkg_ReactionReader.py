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
class ReactionReader(CDPL.Base.DataIOBase):

    ##
    # \brief Initializes the \e %ReactionReader instance.
    # \param self The \e %ReactionReader instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \param rxn 
    # \param overwrite 
    # \return 
    #
    def read(self: ReactionReader, rxn: Reaction, overwrite: bool = True) -> ReactionReader: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \param idx 
    # \param rxn 
    # \param overwrite 
    # \return 
    #
    def read(self: ReactionReader, idx: int, rxn: Reaction, overwrite: bool = True) -> ReactionReader: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \return 
    #
    def skip(self: ReactionReader) -> ReactionReader: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \return 
    #
    def hasMoreData(self: ReactionReader) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \return 
    #
    def getRecordIndex(self: ReactionReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \param idx 
    #
    def setRecordIndex(self: ReactionReader, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \return 
    #
    def getNumRecords(self: ReactionReader) -> int: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    #
    def close(self: ReactionReader) -> None: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \return 
    #
    def __nonzero__(self: ReactionReader) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ReactionReader instance this method is called upon.
    # \return 
    #
    def __bool__(self: ReactionReader) -> bool: pass

    ##
    # \brief 
    #
    numRecords = property(getNumRecords)
