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
# \brief A half-open index range \f$ [start, stop) \f$ used for slicing vector and matrix expressions.
# 
class Range(Boost.Python.instance):

    ##
    # \brief Constructs an empty range \f$ [0, 0) \f$.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %Range instance \a r.
    # \param r The \c %Range instance to copy.
    # 
    def __init__(r: Range) -> None: pass

    ##
    # \brief Constructs the range \f$ [start, stop) \f$.
    # 
    # \param start The lower (inclusive) bound.
    # \param stop The upper (exclusive) bound.
    # 
    # \throw Base.RangeError if <em>start</em> > <em>stop</em>.
    # 
    def __init__(start: int, stop: int) -> None: pass

    ##
    # \brief Returns the lower (inclusive) bound.
    # 
    # \return The lower bound.
    # 
    def getStart() -> int: pass

    ##
    # \brief Returns the upper (exclusive) bound.
    # 
    # \return The upper bound.
    # 
    def getStop() -> int: pass

    ##
    # \brief Returns the size of the range, \f$ stop - start \f$.
    # 
    # \return The range size.
    # 
    def getSize() -> int: pass

    ##
    # \brief Tells whether the range is empty.
    # 
    # \return <tt>True</tt> if the range is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getIndex(i: int) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %Range instance \a r.
    # \param r The \c %Range instance to copy.
    # \return \a self
    # 
    def assign(r: Range) -> Range: pass

    ##
    # \brief Swaps the contents of <tt>self</tt> and <em>r</em>.
    # 
    # \param r The other range.
    # 
    def swap(r: Range) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %Range instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Range instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Equality comparison.
    # 
    # \param r The other range.
    # 
    # \return <tt>True</tt> if both ranges have the same start and stop, and <tt>False</tt> otherwise.
    # 
    def __eq__(r: Range) -> bool: pass

    ##
    # \brief Inequality comparison.
    # 
    # \param r The other range.
    # 
    # \return <tt>True</tt> if the ranges differ in start or stop, and <tt>False</tt> otherwise.
    # 
    def __ne__(r: Range) -> bool: pass

    ##
    # \brief Maps the local position <em>i</em> to the global index <em>start</em> + <em>i</em>.
    # 
    # \param i The zero-based local position.
    # 
    # \return The global index. 
    # 
    # \throw Base.IndexError if <em>i</em> is not in the range \f$ [0, size) \f$.
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
