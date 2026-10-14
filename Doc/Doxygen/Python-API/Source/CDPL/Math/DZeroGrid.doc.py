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
# \brief Immutable grid where all elements have the value zero of type <tt>double</tt>.
# 
class DZeroGrid(Boost.Python.instance):

    ##
    # \brief Constructs an empty zero grid (zero size on every axis).
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c DZeroGrid instance \a g.
    # \param g The \c DZeroGrid instance to copy.
    # 
    def __init__(g: DZeroGrid) -> None: pass

    ##
    # \brief Constructs a zero grid of size <em>m&times;n&times;o</em>.
    # 
    # \param m The first-axis size.
    # \param n The second-axis size.
    # \param o The third-axis size.
    # 
    def __init__(m: int, n: int, o: int) -> None: pass

    ##
    # \brief Resizes the grid axes to (<em>m</em>, <em>n</em>, <em>o</em>).
    # 
    # \param m The new first-axis size.
    # \param n The new second-axis size.
    # \param o The new third-axis size.
    # 
    def resize(m: int, n: int, o: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DZeroGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DZeroGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the first-axis size.
    # 
    # \return The size along the first axis.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the second-axis size.
    # 
    # \return The size along the second axis.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Returns the third-axis size.
    # 
    # \return The size along the third axis.
    # 
    def getSize3() -> int: pass

    ##
    # \brief Tells whether the grid is empty (any axis has zero size).
    # 
    # \return <tt>True</tt> if any axis is zero, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def getElement(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Returns the element at linear index <em>i</em>.
    # 
    # \param i The zero-based linear index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def getElement(i: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Returns the total element count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
    # 
    # \return The total number of elements.
    # 
    def getSize() -> int: pass

    ##
    # \brief Copy-assigns the axis sizes from <em>g</em>.
    # 
    # \param g The source zero grid.
    # 
    # \return \a self.
    # 
    def assign(g: DZeroGrid) -> DZeroGrid: pass

    ##
    # \brief Swaps the axis sizes with <em>g</em>.
    # 
    # \param g The zero grid to swap with.
    # 
    def swap(g: DZeroGrid) -> None: pass

    ##
    # \brief Returns the zero element.
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return A reference to the zero element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __call__(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Returns the zero element.
    # 
    # \param i The zero-based linear index.
    # 
    # \return A reference to the zero element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __getitem__(ijk: tuple) -> float: pass

    ##
    # \brief Returns the element at linear index <em>i</em>.
    # 
    # \param i The zero-based linear index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the total element count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
    # 
    # \return The total number of elements.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param g The \c DZeroGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: DZeroGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \c DZeroGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: DZeroGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c DZeroGrid instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DZeroGrid: pass

    ##
    # \brief Negates each element and returns the result.
    # \return A \c ConstDGridExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstDGridExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c DZeroGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDGridExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDGridExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
