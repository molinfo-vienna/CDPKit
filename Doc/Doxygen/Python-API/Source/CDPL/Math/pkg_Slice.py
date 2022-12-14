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
class Slice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Slice instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Slice instance.
    # \param s 
    #
    def __init__(s: _ast.Slice) -> None: pass

    ##
    # \brief Initializes the \e %Slice instance.
    # \param start 
    # \param stride 
    # \param size 
    #
    def __init__(start: int, stride: int, size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStart() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStride() -> int: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Slice instance \a s.
    # \param s The \e %Slice instance to copy.
    # \return \a self
    #
    def assign(s: _ast.Slice) -> _ast.Slice: pass

    ##
    # \brief 
    # \param s 
    #
    def swap(s: _ast.Slice) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %Slice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Slice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param s The \e %Slice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(s: _ast.Slice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param s The \e %Slice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(s: _ast.Slice) -> bool: pass

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
    stride = property(getStride)

    ##
    # \brief 
    #
    size = property(getSize)
