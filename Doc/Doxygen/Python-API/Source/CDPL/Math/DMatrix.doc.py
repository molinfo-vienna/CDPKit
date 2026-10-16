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
# \brief Unbounded dense matrix holding floating-point values of type <tt>double</tt>..
# 
class DMatrix(Boost.Python.instance):

    ##
    # \brief Constructs an empty matrix (zero rows and zero columns).
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the matrix <em>m</em>.
    # 
    # \param m The matrix to copy.
    # 
    def __init__(m: DMatrix) -> None: pass

    ##
    # \brief Constructs an <em>m&times;n</em> matrix with default-initialized elements.
    # 
    # \param m The number of rows.
    # \param n The number of columns.
    # 
    def __init__(m: int, n: int) -> None: pass

    ##
    # \brief Constructs an <em>m&times;n</em> matrix with every element initialized to <em>v</em>.
    # 
    # \param m The number of rows.
    # \param n The number of columns.
    # \param v The value used for element initialization.
    # 
    def __init__(m: int, n: int, v: float) -> None: pass

    ##
    # \brief Constructs the matrix from the matrix expression <em>e</em> (materializing the expression result).
    # 
    # \param e The matrix expression to materialize.
    # 
    def __init__(e: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Constructs the matrix from the matrix expression <em>e</em> (materializing the expression result).
    # 
    # \param e The matrix expression to materialize.
    # 
    def __init__(e: ConstDMatrixExpression) -> None: pass

    ##
    # \brief Constructs the matrix from the matrix expression <em>e</em> (materializing the expression result).
    # 
    # \param e The matrix expression to materialize.
    # 
    def __init__(e: ConstLMatrixExpression) -> None: pass

    ##
    # \brief Constructs the matrix from the matrix expression <em>e</em> (materializing the expression result).
    # 
    # \param e The matrix expression to materialize.
    # 
    def __init__(e: ConstULMatrixExpression) -> None: pass

    ##
    # \brief Constructs the matrix from the 2D \c numpy.ndarray object \a a.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Resizes the matrix to <em>m&times;n</em> elements.
    # 
    # \param m The new row count.
    # \param n The new column count.
    # \param preserve If <tt>True</tt>, existing element values at indices that remain valid are kept. If <tt>False</tt>, all elements are set to <em>v</em>.
    # \param v The fill value for newly added elements (or for all elements when <em>preserve</em> is <tt>False</tt>).
    # 
    def resize(m: int, n: int, preserve: bool = True, v: float = 0.0) -> None: pass

    ##
    # \brief Sets every element of the matrix to the value <em>v</em>.
    # 
    # \param v The fill value.
    # 
    def clear(v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DMatrix instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DMatrix instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFMatrixExpression) -> DMatrix: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDMatrixExpression) -> DMatrix: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLMatrixExpression) -> DMatrix: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULMatrixExpression) -> DMatrix: pass

    ##
    # \brief Copy-assigns the contents of <em>m</em> to this matrix.
    # 
    # \param m The source matrix.
    # 
    # \return \a self.
    # 
    def assign(m: DMatrix) -> DMatrix: pass

    ##
    # \brief Assigns the contents of the 2D \c numpy.ndarray object \a a to this matrix.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> DMatrix: pass

    ##
    # \brief Returns the number of rows.
    # 
    # \return The number of rows.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the number of columns.
    # 
    # \return The number of columns.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Tells whether the matrix is empty.
    # 
    # \return <tt>True</tt> if the underlying storage holds no elements, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if either index is out of range.
    # 
    def getElement(i: int, j: int) -> float: pass

    ##
    # \brief Converts the \c DMatrix instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this matrix with those of <em>m</em>.
    # 
    # \param m The matrix to swap with.
    # 
    def swap(m: DMatrix) -> None: pass

    ##
    # \brief Sets the value of the element (\a i, \a j) to \a v.
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if either index is out of range.
    # 
    def __call__(i: int, j: int) -> float: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if either index is out of range.
    # 
    def __getitem__(ij: tuple) -> float: pass

    ##
    # \brief Returns the number of rows.
    # 
    # \return The number of rows.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param m The \c DMatrix instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(m: DMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param m The \c DMatrix instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(m: DMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c DMatrix instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DMatrix: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstDMatrixExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstDMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c DMatrix instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDMatrixExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Sets the value of the element (\a i, \a j) to \a v.
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Adds the contents of the matrix <em>m</em> element-wise to this matrix (no alias check needed).
    # 
    # \param m The source matrix.
    # 
    # \return \a self.
    # 
    def __iadd__(m: DMatrix) -> DMatrix: pass

    ##
    # \brief Adds the matrix expression <em>e</em> element-wise to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDMatrixExpression) -> DMatrix: pass

    ##
    # \brief Subtracts the contents of the matrix <em>m</em> element-wise from this matrix (no alias check needed).
    # 
    # \param m The source matrix.
    # 
    # \return \a self.
    # 
    def __isub__(m: DMatrix) -> DMatrix: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> element-wise from this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDMatrixExpression) -> DMatrix: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DMatrix: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DMatrix: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DMatrix: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)
