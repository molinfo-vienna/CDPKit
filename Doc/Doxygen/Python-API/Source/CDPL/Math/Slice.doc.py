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
# \brief Index slice ( \f$ start, stride, size \f$) used for strided slicing of vector and matrix expressions.
# 
# Local position <em>i</em> is mapped to the global index \f$ start + i \cdot stride \f$. Negative strides (reverse iteration) are supported as long as the resulting indices stay non-negative.
# 
class Slice(Boost.Python.instance):

    ##
    # \brief Constructs an empty slice.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %Slice instance \a s.
    # \param s The \c %Slice instance to copy.
    # 
    def __init__(s: Slice) -> None: pass

    ##
    # \brief Constructs the slice (<em>start</em>, <em>stride</em>, <em>size</em>).
    # 
    # \param start The starting global index.
    # \param stride The signed step size between consecutive entries.
    # \param size The number of entries.
    # 
    # \throw Base.RangeError if the slice would produce a negative global index.
    # 
    def __init__(start: int, stride: int, size: int) -> None: pass

    ##
    # \brief Returns the starting global index.
    # 
    # \return The starting index.
    # 
    def getStart() -> int: pass

    ##
    # \brief Returns the signed step size between consecutive entries.
    # 
    # \return The stride.
    # 
    def getStride() -> int: pass

    ##
    # \brief Returns the number of entries in the slice.
    # 
    # \return The slice size.
    # 
    def getSize() -> int: pass

    ##
    # \brief Tells whether the slice is empty.
    # 
    # \return <tt>True</tt> if the slice contains no entries, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getIndex(i: int) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %Slice instance \a s.
    # \param s The \c %Slice instance to copy.
    # \return \a self
    # 
    def assign(s: Slice) -> Slice: pass

    ##
    # \brief Swaps the contents of <tt>self</tt> and <em>s</em>.
    # 
    # \param s The other slice.
    # 
    def swap(s: Slice) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %Slice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Slice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Equality comparison.
    # 
    # \param s The other slice.
    # 
    # \return <tt>True</tt> if both slices have the same start, stride and size, and <tt>False</tt> otherwise.
    # 
    def __eq__(s: Slice) -> bool: pass

    ##
    # \brief Inequality comparison.
    # 
    # \param s The other slice.
    # 
    # \return <tt>True</tt> if the slices differ in start, stride or size, and <tt>False</tt> otherwise.
    # 
    def __ne__(s: Slice) -> bool: pass

    ##
    # \brief Maps the local position <em>i</em> to the global index \f$ start + i \cdot stride \f$.
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

    stride = property(getStride)

    size = property(getSize)
