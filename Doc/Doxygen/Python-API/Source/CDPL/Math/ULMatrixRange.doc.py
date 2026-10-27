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
# \brief Matrix expression proxy that views a contiguous rectangular subrange of an underlying matrix.
# 
class ULMatrixRange(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ULMatrixRange instance \a r.
    # \param r The \c ULMatrixRange instance to copy.
    # 
    def __init__(r: ULMatrixRange) -> None: pass

    ##
    # \brief Constructs the matrix range proxy viewing rows in <em>r1</em> and columns in <em>r2</em> of <em>m</em>.
    # 
    # \param m The wrapped matrix.
    # \param r1 The row index range.
    # \param r2 The column index range.
    # 
    def __init__(m: ULMatrixExpression, r1: Range, r2: Range) -> None: pass

    ##
    # \brief Returns the row index range's start index in the wrapped matrix.
    # 
    # \return The start row index.
    # 
    def getStart1() -> int: pass

    ##
    # \brief Returns the column index range's start index in the wrapped matrix.
    # 
    # \return The start column index.
    # 
    def getStart2() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ULMatrixRange instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ULMatrixRange instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix range (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFMatrixExpression) -> ULMatrixRange: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix range (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDMatrixExpression) -> ULMatrixRange: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix range (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLMatrixExpression) -> ULMatrixRange: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix range (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULMatrixExpression) -> ULMatrixRange: pass

    ##
    # \brief Copy-assigns the contents of <em>r</em> to this matrix range (via a temporary to handle aliasing).
    # 
    # \param r The source matrix range.
    # 
    # \return \a self.
    # 
    def assign(r: ULMatrixRange) -> ULMatrixRange: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this matrix range.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Returns the number of rows in the proxy (size of the row range).
    # 
    # \return The number of rows.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the number of columns in the proxy (size of the column range).
    # 
    # \return The number of columns.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Tells whether the proxy is empty (either range has size zero).
    # 
    # \return <tt>True</tt> if either range has zero size, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the element at proxy index (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # 
    # \return The value of the element <tt>m(r1(i), r2(j))</tt>.
    # 
    def getElement(i: int, j: int) -> int: pass

    ##
    # \brief Converts the \c ULMatrixRange instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this matrix range with those of <em>r</em> (via element-wise swap of the underlying matrix elements).
    # 
    # \param r The matrix range to swap with.
    # 
    def swap(r: ULMatrixRange) -> None: pass

    ##
    # \brief Sets the value of the element at proxy index (\a i, \a j) to \a v.
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def setElement(i: int, j: int, v: int) -> None: pass

    ##
    # \brief Returns the wrapped matrix.
    # 
    # \return The wrapped matrix.
    # 
    def getData() -> ULMatrixExpression: pass

    ##
    # \brief Returns the element at proxy index (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # 
    # \return The value of the element <tt>m(r1(i), r2(j))</tt>.
    # 
    def __call__(i: int, j: int) -> int: pass

    ##
    # \brief Returns the element at proxy index (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # 
    # \return The value of the element <tt>m(r1(i), r2(j))</tt>.
    # 
    def __getitem__(ij: tuple) -> int: pass

    ##
    # \brief Returns the number of rows in the proxy (size of the row range).
    # 
    # \return The number of rows.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \c ULMatrixRange instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: ULMatrixRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstULMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \c ULMatrixRange instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: ULMatrixRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstULMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c ULMatrixRange instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ULMatrixRange: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstULMatrixExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstULMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ULMatrixRange instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstULMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstULMatrixExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Sets the value of the element at proxy index (\a i, \a j) to \a v.
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __setitem__(ij: tuple, v: int) -> None: pass

    ##
    # \brief Adds the elements of the matrix range <em>r</em> to this range (via a temporary to handle aliasing).
    # 
    # \param r The source matrix range.
    # 
    # \return \a self.
    # 
    def __iadd__(r: ULMatrixRange) -> ULMatrixRange: pass

    ##
    # \brief Adds the elements of the matrix expression <em>e</em> to this matrix range (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstULMatrixExpression) -> ULMatrixRange: pass

    ##
    # \brief Subtracts the elements of the matrix range <em>r</em> from this range (via a temporary to handle aliasing).
    # 
    # \param r The source matrix range.
    # 
    # \return \a self.
    # 
    def __isub__(r: ULMatrixRange) -> ULMatrixRange: pass

    ##
    # \brief Subtracts the elements of the matrix expression <em>e</em> from this matrix range (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstULMatrixExpression) -> ULMatrixRange: pass

    ##
    # \brief Multiplies every element of this matrix range by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: int) -> ULMatrixRange: pass

    ##
    # \brief Divides every element of this matrix range by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: int) -> ULMatrixRange: pass

    ##
    # \brief Divides every element of this matrix range by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: int) -> ULMatrixRange: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)

    start1 = property(getStart1)

    start2 = property(getStart2)
