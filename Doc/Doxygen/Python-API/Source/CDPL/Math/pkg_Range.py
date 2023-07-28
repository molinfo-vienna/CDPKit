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
class Range(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Range instance.
    # \param self The \e %Range instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Range instance.
    # \param self The \e %Range instance to initialize.
    # \param r 
    # 
    def __init__(r: Range) -> None: pass

    ##
    # \brief Initializes the \e %Range instance.
    # \param self The \e %Range instance to initialize.
    # \param start 
    # \param stop 
    # 
    def __init__(start: int, stop: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStart() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStop() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getIndex(i: int) -> int: pass

    ##
    # \brief 
    # \param r 
    # \return 
    #
    def assign(r: Range) -> Range: pass

    ##
    # \brief 
    # \param r 
    #
    def swap(r: Range) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param self The \e %Range instance this method is called upon.
    # \param r The \e %Range instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: Range) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param self The \e %Range instance this method is called upon.
    # \param r The \e %Range instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: Range) -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __call__(i: int) -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> int: pass

    objectID = property(getObjectID)

    start = property(getStart)

    stop = property(getStop)

    size = property(getSize)
