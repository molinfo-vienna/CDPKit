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
# \brief Mutable view adapter that exposes the transpose of a matrix <em>M</em> as a matrix expression ( \f$ (i, j) \to M(j, i) \f$).
# 
class DMatrixTranspose(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c DMatrixTranspose instance \a mt.
    # \param mt The \c DMatrixTranspose instance to copy.
    # 
    def __init__(mt: DMatrixTranspose) -> None: pass

    ##
    # \brief Constructs the transpose view proxy referring to <em>m</em>.
    # 
    # \param m The wrapped matrix.
    # 
    def __init__(m: DMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DMatrixTranspose instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DMatrixTranspose instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view (writes the transpose into the wrapped matrix).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view (writes the transpose into the wrapped matrix).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view (writes the transpose into the wrapped matrix).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view (writes the transpose into the wrapped matrix).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the wrapped matrix from <em>mt's</em> wrapped matrix (possibly differing types).
    # 
    # \param mt The source transpose view.
    # 
    # \return \a self.
    # 
    def assign(mt: DMatrixTranspose) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the contents of the 2D \c numpy.ndarray object \a a to this transpose view.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Returns the number of rows of the transpose view (= number of columns of the wrapped matrix).
    # 
    # \return The number of rows.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the number of columns of the transpose view (= number of rows of the wrapped matrix).
    # 
    # \return The number of columns.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Tells whether the view is empty (the wrapped matrix has zero rows or zero columns).
    # 
    # \return <tt>True</tt> if the wrapped matrix is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the wrapped matrix's element at (<em>j</em>, <em>i</em>).
    # 
    # \param i The zero-based row index in the transposed view.
    # \param j The zero-based column index in the transposed view.
    # 
    # \return A reference to <tt>m(j, i)</tt>.
    # 
    def getElement(i: int, j: int) -> float: pass

    ##
    # \brief Converts the \c DMatrixTranspose instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the underlying matrices of the two transpose views.
    # 
    # \param mt The transpose view to swap with.
    # 
    def swap(mt: DMatrixTranspose) -> None: pass

    ##
    # \brief Sets the value of the wrapped matrix's element at (\a j, \a i) to \a v.
    # \param i The zero-based row index in the transposed view.
    # \param j The zero-based column index in the transposed view.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief Returns the wrapped matrix.
    # 
    # \return The wrapped matrix.
    # 
    def getData() -> DMatrixExpression: pass

    ##
    # \brief Returns the wrapped matrix's element at (<em>j</em>, <em>i</em>).
    # 
    # \param i The zero-based row index in the transposed view.
    # \param j The zero-based column index in the transposed view.
    # 
    # \return A reference to <tt>m(j, i)</tt>.
    # 
    def __call__(i: int, j: int) -> float: pass

    ##
    # \brief Returns the wrapped matrix's element at (<em>j</em>, <em>i</em>).
    # 
    # \param i The zero-based row index in the transposed view.
    # \param j The zero-based column index in the transposed view.
    # 
    # \return A reference to <tt>m(j, i)</tt>.
    # 
    def __getitem__(ij: tuple) -> float: pass

    ##
    # \brief Returns the number of rows of the transpose view (= number of columns of the wrapped matrix).
    # 
    # \return The number of rows.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == mt</tt>.
    # \param mt The \c DMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(mt: DMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mt</tt>.
    # \param mt The \c DMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(mt: DMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c DMatrixTranspose instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DMatrixTranspose: pass

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
    # \return A \c DMatrixTranspose instance holding the result of the subtraction.
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

    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Adds the matrix transpose <em>mt</em> to this transpose view.
    # 
    # \param mt The source matrix transpose.
    # 
    # \return \a self.
    # 
    def __iadd__(mt: DMatrixTranspose) -> DMatrixTranspose: pass

    ##
    # \brief Adds the matrix expression <em>e</em> to this transpose view.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Subtracts the matrix transpose <em>mt</em> from this transpose view.
    # 
    # \param mt The source matrix transpose.
    # 
    # \return \a self.
    # 
    def __isub__(mt: DMatrixTranspose) -> DMatrixTranspose: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> from this transpose view.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Multiplies every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DMatrixTranspose: pass

    ##
    # \brief Divides every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DMatrixTranspose: pass

    ##
    # \brief Divides every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DMatrixTranspose: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)
