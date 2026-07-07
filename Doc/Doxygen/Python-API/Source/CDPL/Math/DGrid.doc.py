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
# \brief Unbounded dense grid storing floating-point values of type <tt>double</tt>.
# 
class DGrid(Boost.Python.instance):

    ##
    # \brief Constructs an empty grid (zero size on every axis).
    # 
    def __init__() -> None: pass

    ##
    # \brief Move-constructs a grid from <em>g</em> (<em>g</em> is left in a valid empty state).
    # 
    # \param g The grid to move from.
    # 
    def __init__(g: DGrid) -> None: pass

    ##
    # \brief Constructs an <em>m&times;n&times;o</em> grid with default-initialized elements.
    # 
    # \param m The size along the first axis.
    # \param n The size along the second axis.
    # \param o The size along the third axis.
    # 
    def __init__(m: int, n: int, o: int) -> None: pass

    ##
    # \brief Constructs an <em>m&times;n&times;o</em> grid with every element initialized to <em>v</em>.
    # 
    # \param m The size along the first axis.
    # \param n The size along the second axis.
    # \param o The size along the third axis.
    # \param v The value used for element initialization.
    # 
    def __init__(m: int, n: int, o: int, v: float) -> None: pass

    ##
    # \brief Initializes the \c %DGrid instance.
    # \param e 
    # 
    def __init__(e: ConstFGridExpression) -> None: pass

    ##
    # \brief Initializes the \c %DGrid instance.
    # \param e 
    # 
    def __init__(e: ConstDGridExpression) -> None: pass

    ##
    # \brief Initializes the \c %DGrid instance.
    # \param e 
    # 
    def __init__(e: object) -> None: pass

    ##
    # \brief Resizes the grid to <em>m&times;n&times;o</em> elements.
    # 
    # \param m The new first-axis size.
    # \param n The new second-axis size.
    # \param o The new third-axis size.
    # \param preserve If <tt>True</tt>, existing element values at indices that remain valid are kept. If <tt>False</tt>, all elements are set to <em>v</em>.
    # \param v The fill value for newly added elements (or for all elements when <em>preserve</em> is <tt>False</tt>).
    # 
    def resize(m: int, n: int, o: int, preserve: bool = True, v: float = 0.0) -> None: pass

    ##
    # \brief Sets every element of the grid to the value <em>v</em>.
    # 
    # \param v The fill value.
    # 
    def clear(v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Resizes this grid to match <em>e</em> and assigns its elements without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFGridExpression) -> DGrid: pass

    ##
    # \brief Resizes this grid to match <em>e</em> and assigns its elements without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDGridExpression) -> DGrid: pass

    ##
    # \brief Resizes this grid to match <em>e</em> and assigns its elements without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: object) -> DGrid: pass

    ##
    # \brief Move-assigns the contents of <em>g</em> to this grid.
    # 
    # \param g The source grid (left in a valid but unspecified state).
    # 
    # \return \a self
    # 
    def assign(g: DGrid) -> DGrid: pass

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
    # \brief Tells whether the grid is empty.
    # 
    # \return <tt>True</tt> if the underlying storage holds no elements, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getElement(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief Returns the total element count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
    # 
    # \return The total number of elements.
    # 
    def getSize() -> int: pass

    ##
    # \brief Swaps the contents of this grid with those of <em>g</em>.
    # 
    # \param g The grid to swap with.
    # 
    def swap(g: DGrid) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns a reference to the element at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return A reference to the element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __call__(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Returns a reference to the element at linear index <em>i</em>.
    # 
    # \param i The zero-based linear index.
    # 
    # \return A reference to the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief 
    # \param ijk 
    # \return 
    #
    def __getitem__(ijk: tuple) -> float: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param g The \c %DGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: DGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \c %DGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: DGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %DGrid instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstDGridExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %DGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDGridExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param ijk 
    # \param v 
    #
    def __setitem__(ijk: tuple, v: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param g Specifies the second addend.
    # \return The updated \c %DGrid instance \a self.
    # 
    def __iadd__(g: DGrid) -> DGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %DGrid instance \a self.
    # 
    def __iadd__(e: ConstDGridExpression) -> DGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param g Specifies the subtrahend.
    # \return The updated \c %DGrid instance \a self.
    # 
    def __isub__(g: DGrid) -> DGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %DGrid instance \a self.
    # 
    def __isub__(e: ConstDGridExpression) -> DGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %DGrid instance \a self.
    # 
    def __imul__(t: float) -> DGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %DGrid instance \a self.
    # 
    def __idiv__(t: float) -> DGrid: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> DGrid: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
