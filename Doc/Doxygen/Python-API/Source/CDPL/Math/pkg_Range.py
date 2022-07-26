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
class Range(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Range instance.
    # \param self The \e %Range instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Range instance.
    # \param self The \e %Range instance to initialize.
    # \param r 
    #
    def __init__(self: object, r: Range) -> None: pass

    ##
    # \brief Initializes the \e %Range instance.
    # \param self The \e %Range instance to initialize.
    # \param start 
    # \param stop 
    #
    def __init__(self: object, start: int, stop: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \return 
    #
    def getStart(self: Range) -> int: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \return 
    #
    def getStop(self: Range) -> int: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \return 
    #
    def getSize(self: Range) -> int: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \return 
    #
    def isEmpty(self: Range) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \param i 
    # \return 
    #
    def getIndex(self: Range, i: int) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Range instance \a r.
    # \param self The \e %Range instance this method is called upon.
    # \param r The \e %Range instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Range, r: Range) -> Range: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \param r 
    #
    def swap(self: Range, r: Range) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Range instance this method is called upon.
    #
    # Different Python \e %Range instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Range instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Range) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param self The \e %Range instance this method is called upon.
    # \param r The \e %Range instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Range, r: Range) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param self The \e %Range instance this method is called upon.
    # \param r The \e %Range instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Range, r: Range) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: Range, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %Range instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: Range, i: int) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    start = property(getStart)

    ##
    # \brief 
    #
    stop = property(getStop)

    ##
    # \brief 
    #
    size = property(getSize)
