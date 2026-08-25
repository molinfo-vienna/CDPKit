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
class ConstLMatrixSlice(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %ConstLMatrixSlice instance \a s.
    # \param s The \c %ConstLMatrixSlice instance to copy.
    # 
    def __init__(s: ConstLMatrixSlice) -> None: pass

    ##
    # \brief Initializes the \c %ConstLMatrixSlice instance.
    # \param e 
    # \param s1 
    # \param s2 
    # 
    def __init__(e: ConstLMatrixExpression, s1: Slice, s2: Slice) -> None: pass

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
    # Different Python \c %ConstLMatrixSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ConstLMatrixSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

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

    def getElement(i: int, j: int) -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> ConstLMatrixExpression: pass

    ##
    # \brief Returns a reference to the element at proxy index (<em>i</em>, <em>j</em>).
    # 
    # \param i The zero-based proxy row index.
    # \param j The zero-based proxy column index.
    # 
    # \return A reference to the underlying element <tt>m(s1(i), s2(j))</tt>.
    # 
    def __call__(i: int, j: int) -> int: pass

    def __getitem__(ij: tuple) -> int: pass

    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param s The \c %ConstLMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(s: ConstLMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstLMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param s The \c %ConstLMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(s: ConstLMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstLMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %ConstLMatrixSlice instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> ConstLMatrixSlice: pass

    def __neg__() -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstLMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %ConstLMatrixSlice instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstLMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstLMatrixExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLMatrixExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)

    start1 = property(getStart1)

    start2 = property(getStart2)

    stride1 = property(getStride1)

    stride2 = property(getStride2)
