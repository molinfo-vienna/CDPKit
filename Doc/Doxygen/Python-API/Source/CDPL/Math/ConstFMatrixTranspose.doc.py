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
class ConstFMatrixTranspose(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %ConstFMatrixTranspose instance \a mt.
    # \param mt The \c %ConstFMatrixTranspose instance to copy.
    # 
    def __init__(mt: ConstFMatrixTranspose) -> None: pass

    ##
    # \brief Initializes the \c %ConstFMatrixTranspose instance.
    # \param e 
    # 
    def __init__(e: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ConstFMatrixTranspose instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ConstFMatrixTranspose instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

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
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> ConstFMatrixExpression: pass

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
    # \param mt The \c %ConstFMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(mt: ConstFMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstFMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mt</tt>.
    # \param mt The \c %ConstFMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(mt: ConstFMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstFMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %ConstFMatrixTranspose instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> ConstFMatrixTranspose: pass

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
    # \return A \c %ConstFMatrixTranspose instance holding the result of the subtraction.
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
    # \brief Divides every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __div__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Divides every element of the wrapped matrix by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __truediv__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFMatrixExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)
