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
# \brief Vector expression proxy that views a single column of an underlying matrix.
# 
class ULMatrixColumn(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ULMatrixColumn instance \a mc.
    # \param mc The \c ULMatrixColumn instance to copy.
    # 
    def __init__(mc: ULMatrixColumn) -> None: pass

    ##
    # \brief Constructs the column proxy viewing column <em>i</em> of <em>m</em>.
    # 
    # \param m The wrapped matrix.
    # \param i The zero-based column index to view.
    # 
    def __init__(m: ULMatrixExpression, i: int) -> None: pass

    ##
    # \brief Returns the column index this proxy refers to within the wrapped matrix.
    # 
    # \return The zero-based column index.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ULMatrixColumn instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ULMatrixColumn instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this column (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> ULMatrixColumn: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this column (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> ULMatrixColumn: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this column (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> ULMatrixColumn: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this column (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> ULMatrixColumn: pass

    ##
    # \brief Copy-assigns the contents of <em>c</em> to this column (via a temporary to handle aliasing).
    # 
    # \param c The source column.
    # 
    # \return \a self.
    # 
    def assign(c: ULMatrixColumn) -> ULMatrixColumn: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this column.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> ULMatrixColumn: pass

    ##
    # \brief Tells whether the column is empty (the wrapped matrix has zero rows).
    # 
    # \return <tt>True</tt> if the wrapped matrix has zero rows, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the size of the column (number of rows of the wrapped matrix).
    # 
    # \return The number of rows.
    # 
    def getSize() -> int: pass

    ##
    # \brief Returns the element at row <em>i</em> of the column.
    # 
    # \param i The zero-based row index.
    # 
    # \return The value of the element <tt>m(i, index)</tt>.
    # 
    def getElement(i: int) -> int: pass

    ##
    # \brief Converts the \c ULMatrixColumn instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this column with those of <em>c</em> (via element-wise swap of the underlying matrix elements).
    # 
    # \param c The column to swap with.
    # 
    def swap(c: ULMatrixColumn) -> None: pass

    ##
    # \brief Sets the value of the element at row \a i of the column to \a v.
    # \param i The zero-based row index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Returns the wrapped matrix.
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> ULMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == c</tt>.
    # \param c The \c ULMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(c: ULMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != c</tt>.
    # \param c The \c ULMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(c: ULMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the element at row <em>i</em> of the column.
    # 
    # \param i The zero-based row index.
    # 
    # \return The value of the element <tt>m(i, index)</tt>.
    # 
    def __call__(i: int) -> int: pass

    ##
    # \brief Returns the element at row <em>i</em> of the column.
    # 
    # \param i The zero-based row index.
    # 
    # \return The value of the element <tt>m(i, index)</tt>.
    # 
    def __getitem__(i: int) -> int: pass

    ##
    # \brief Returns the size of the column (number of rows of the wrapped matrix).
    # 
    # \return The number of rows.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c ULMatrixColumn instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ULMatrixColumn: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstULVectorExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstULVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ULMatrixColumn instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstULVectorExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstULVectorExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Sets the value of the element at row \a i of the column to \a v.
    # \param i The zero-based row index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Adds the elements of the matrix column <em>c</em> to this column (via a temporary to handle aliasing).
    # 
    # \param c The source matrix column.
    # 
    # \return \a self.
    # 
    def __iadd__(c: ULMatrixColumn) -> ULMatrixColumn: pass

    ##
    # \brief Adds the elements of the vector expression <em>e</em> to this column (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstULVectorExpression) -> ULMatrixColumn: pass

    ##
    # \brief Subtracts the elements of the matrix column <em>c</em> from this column (via a temporary to handle aliasing).
    # 
    # \param c The source matrix column.
    # 
    # \return \a self.
    # 
    def __isub__(c: ULMatrixColumn) -> ULMatrixColumn: pass

    ##
    # \brief Subtracts the elements of the vector expression <em>e</em> from this column (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstULVectorExpression) -> ULMatrixColumn: pass

    ##
    # \brief Multiplies every element of this column by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: int) -> ULMatrixColumn: pass

    ##
    # \brief Divides every element of this column by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: int) -> ULMatrixColumn: pass

    ##
    # \brief Divides every element of this column by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: int) -> ULMatrixColumn: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    index = property(getIndex)
