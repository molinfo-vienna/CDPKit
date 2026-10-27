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
# \brief Memory-efficient immutable matrix where all elements have the same value of type <tt>long</tt>.
# 
class LScalarMatrix(Boost.Python.instance):

    ##
    # \brief Constructs an empty scalar matrix.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the scalar matrix <em>m</em>.
    # 
    # \param m The scalar matrix to copy.
    # 
    def __init__(m: LScalarMatrix) -> None: pass

    ##
    # \brief Constructs a scalar matrix of size <em>m&times;n</em> in which every entry equals <em>v</em>.
    # 
    # \param m The number of rows.
    # \param n The number of columns.
    # \param v The common entry value.
    # 
    def __init__(m: int, n: int, v: int = 0) -> None: pass

    ##
    # \brief Resizes the dimensions to <em>m&times;n</em>.
    # 
    # \param m The new row count.
    # \param n The new column count.
    # 
    def resize(m: int, n: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c LScalarMatrix instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c LScalarMatrix instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the logical number of rows.
    # 
    # \return The number of rows.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the logical number of columns.
    # 
    # \return The number of columns.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Tells whether the matrix is empty.
    # 
    # \return <tt>True</tt> if either dimension is zero, and <tt>False</tt> otherwise.
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
    def getElement(i: int, j: int) -> int: pass

    ##
    # \brief Converts the \c LScalarMatrix instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Copy-assigns the dimensions and common value from <em>m</em>.
    # 
    # \param m The source scalar matrix.
    # 
    # \return \a self.
    # 
    def assign(m: LScalarMatrix) -> LScalarMatrix: pass

    ##
    # \brief Swaps the dimensions and common value with <em>m</em>.
    # 
    # \param m The scalar matrix to swap with.
    # 
    def swap(m: LScalarMatrix) -> None: pass

    ##
    # \brief Returns the common entry value.
    # 
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # 
    # \return The common entry value. 
    # 
    # \throw Base.IndexError if either index is out of range.
    # 
    def __call__(i: int, j: int) -> int: pass

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
    def __getitem__(ij: tuple) -> int: pass

    ##
    # \brief Returns the number of rows.
    # 
    # \return The number of rows.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param m The \c LScalarMatrix instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(m: LScalarMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstLMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param m The \c LScalarMatrix instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(m: LScalarMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstLMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c LScalarMatrix instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> LScalarMatrix: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstLMatrixExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstLMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c LScalarMatrix instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstLMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstLMatrixExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLMatrixExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)
