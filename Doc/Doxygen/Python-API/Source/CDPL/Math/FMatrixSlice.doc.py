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
# \brief Matrix expression proxy that views a strided rectangular slice of an underlying matrix.
# 
class FMatrixSlice(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %FMatrixSlice instance \a s.
    # \param s The \c %FMatrixSlice instance to copy.
    # 
    def __init__(s: FMatrixSlice) -> None: pass

    ##
    # \brief Initializes the \c %FMatrixSlice instance.
    # \param e 
    # \param s1 
    # \param s2 
    # 
    def __init__(e: FMatrixExpression, s1: Slice, s2: Slice) -> None: pass

    ##
    # \brief Returns the row slice's start index in the wrapped matrix.
    # 
    # \return The start row index.
    # 
    def getStart1() -> int: pass

    ##
    # \brief Returns the column slice's start index in the wrapped matrix.
    # 
    # \return The start column index.
    # 
    def getStart2() -> int: pass

    ##
    # \brief Returns the row slice's stride in the wrapped matrix.
    # 
    # \return The row stride.
    # 
    def getStride1() -> int: pass

    ##
    # \brief Returns the column slice's stride in the wrapped matrix.
    # 
    # \return The column stride.
    # 
    def getStride2() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FMatrixSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FMatrixSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix slice without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix slice without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix slice without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Assigns the elements of the matrix expression <em>e</em> to this matrix slice without intermediate temporary.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Copy-assigns the contents of <em>s</em> to this matrix slice (via a temporary to handle aliasing).
    # 
    # \param s The source matrix slice.
    # 
    # \return \a self
    # 
    def assign(s: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Returns the number of rows in the proxy (size of the row slice).
    # 
    # \return The number of rows.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the number of columns in the proxy (size of the column slice).
    # 
    # \return The number of columns.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Tells whether the proxy is empty (either slice has size zero).
    # 
    # \return <tt>True</tt> if either slice has zero size, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    def getElement(i: int, j: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this matrix slice with those of <em>s</em> (via element-wise swap of the underlying matrix elements).
    # 
    # \param s The matrix slice to swap with.
    # 
    def swap(s: FMatrixSlice) -> None: pass

    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> FMatrixExpression: pass

    ##
    # \brief Returns a reference to the element at proxy index (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # 
    # \return A reference to the underlying element <tt>m(s1(i), s2(j))</tt>.
    # 
    def __call__(i: int, j: int) -> float: pass

    def __getitem__(ij: tuple) -> float: pass

    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param s The \c %FMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(s: FMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstFMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param s The \c %FMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(s: FMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstFMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %FMatrixSlice instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> FMatrixSlice: pass

    def __neg__() -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstFMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %FMatrixSlice instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstFMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstFMatrixExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFMatrixExpression: pass

    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param s Specifies the second addend.
    # \return The updated \c %FMatrixSlice instance \a self.
    # 
    def __iadd__(s: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief Adds the elements of the matrix expression <em>e</em> to this matrix slice (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def __iadd__(e: ConstFMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param s Specifies the subtrahend.
    # \return The updated \c %FMatrixSlice instance \a self.
    # 
    def __isub__(s: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief Subtracts the elements of the matrix expression <em>e</em> from this matrix slice (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self
    # 
    def __isub__(e: ConstFMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Multiplies every element of this matrix slice by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: float) -> FMatrixSlice: pass

    ##
    # \brief Divides every element of this matrix slice by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __idiv__(t: float) -> FMatrixSlice: pass

    def __itruediv__(t: float) -> FMatrixSlice: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)

    start1 = property(getStart1)

    start2 = property(getStart2)

    stride1 = property(getStride1)

    stride2 = property(getStride2)
