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
    # \brief Initializes a copy of the \c %DMatrixTranspose instance \a mt.
    # \param mt The \c %DMatrixTranspose instance to copy.
    # 
    def __init__(mt: DMatrixTranspose) -> None: pass

    ##
    # \brief Initializes the \c %DMatrixTranspose instance.
    # \param e 
    # 
    def __init__(e: DMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DMatrixTranspose instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DMatrixTranspose instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this transpose view without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Assigns the wrapped matrix from <em>mt's</em> wrapped matrix (possibly differing types).
    # 
    # \param mt The source transpose view.
    # 
    # \return \a self
    # 
    def assign(mt: DMatrixTranspose) -> DMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
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

    def getElement(i: int, j: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the underlying matrices of the two transpose views.
    # 
    # \param mt The transpose view to swap with.
    # 
    def swap(mt: DMatrixTranspose) -> None: pass

    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> DMatrixExpression: pass

    ##
    # \brief Returns a reference to the wrapped matrix's element at (<em>j</em>, <em>i</em>).
    # 
    # \param i The zero-based row index in the transposed view.
    # \param j The zero-based column index in the transposed view.
    # 
    # \return A reference to <tt>m(j, i)</tt>.
    # 
    def __call__(i: int, j: int) -> float: pass

    def __getitem__(ij: tuple) -> float: pass

    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == mt</tt>.
    # \param mt The \c %DMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(mt: DMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mt</tt>.
    # \param mt The \c %DMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(mt: DMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %DMatrixTranspose instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> DMatrixTranspose: pass

    def __neg__() -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstDMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %DMatrixTranspose instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Divides every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __div__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Divides every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __truediv__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDMatrixExpression: pass

    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mt</tt>.
    # \param mt Specifies the second addend.
    # \return The updated \c %DMatrixTranspose instance \a self.
    # 
    def __iadd__(mt: DMatrixTranspose) -> DMatrixTranspose: pass

    ##
    # \brief Adds the matrix expression <em>e</em> to this transpose view.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def __iadd__(e: ConstDMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= mt</tt>.
    # \param mt Specifies the subtrahend.
    # \return The updated \c %DMatrixTranspose instance \a self.
    # 
    def __isub__(mt: DMatrixTranspose) -> DMatrixTranspose: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> from this transpose view.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def __isub__(e: ConstDMatrixExpression) -> DMatrixTranspose: pass

    ##
    # \brief Multiplies every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: float) -> DMatrixTranspose: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %DMatrixTranspose instance \a self.
    # 
    def __idiv__(t: float) -> DMatrixTranspose: pass

    def __itruediv__(t: float) -> DMatrixTranspose: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)
