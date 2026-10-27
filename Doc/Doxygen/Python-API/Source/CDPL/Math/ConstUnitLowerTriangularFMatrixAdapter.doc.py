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
# \brief Matrix expression that exposes only the <em>lower</em> triangular part of an underlying matrix <em>M</em> with the diagonal elements set to one.
# 
class ConstUnitLowerTriangularFMatrixAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ConstUnitLowerTriangularFMatrixAdapter instance \a ta.
    # \param ta The \c ConstUnitLowerTriangularFMatrixAdapter instance to copy.
    # 
    def __init__(ta: ConstUnitLowerTriangularFMatrixAdapter) -> None: pass

    ##
    # \brief Constructs the adapter wrapping <em>m</em>.
    # 
    # \param m The matrix to be viewed through the <em>unit lower</em> triangular policy.
    # 
    def __init__(m: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ConstUnitLowerTriangularFMatrixAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ConstUnitLowerTriangularFMatrixAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the number of rows of the wrapped matrix.
    # 
    # \return The row count.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the number of columns of the wrapped matrix.
    # 
    # \return The column count.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Tells whether the wrapped matrix is empty (zero rows or zero columns).
    # 
    # \return <tt>True</tt> if the wrapped matrix is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the value of element (<em>i</em>, <em>j</em>) as seen through the <em>unit lower</em> triangular policy (off-policy entries return the appropriate fill value: zero or one).
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The element value as defined by the <em>unit lower</em> triangular-view policy.
    # 
    def getElement(i: int, j: int) -> float: pass

    ##
    # \brief Converts the \c ConstUnitLowerTriangularFMatrixAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Returns the wrapped matrix.
    # 
    # \return The wrapped matrix.
    # 
    def getData() -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the value of element (<em>i</em>, <em>j</em>) as seen through the <em>unit lower</em> triangular policy (off-policy entries return the appropriate fill value: zero or one).
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The element value as defined by the <em>unit lower</em> triangular-view policy.
    # 
    def __call__(i: int, j: int) -> float: pass

    ##
    # \brief Returns the value of element (<em>i</em>, <em>j</em>) as seen through the <em>unit lower</em> triangular policy (off-policy entries return the appropriate fill value: zero or one).
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The element value as defined by the <em>unit lower</em> triangular-view policy.
    # 
    def __getitem__(ij: tuple) -> float: pass

    ##
    # \brief Returns the number of rows of the wrapped matrix.
    # 
    # \return The row count.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == ta</tt>.
    # \param ta The \c ConstUnitLowerTriangularFMatrixAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(ta: ConstUnitLowerTriangularFMatrixAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstFMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != ta</tt>.
    # \param ta The \c ConstUnitLowerTriangularFMatrixAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(ta: ConstUnitLowerTriangularFMatrixAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstFMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c ConstUnitLowerTriangularFMatrixAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ConstUnitLowerTriangularFMatrixAdapter: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstFMatrixExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstFMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ConstUnitLowerTriangularFMatrixAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFMatrixExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstFMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFMatrixExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)
