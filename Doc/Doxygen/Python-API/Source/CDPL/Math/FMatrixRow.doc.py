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
# \brief Vector expression proxy that views a single row of an underlying matrix.
# 
class FMatrixRow(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c FMatrixRow instance \a mr.
    # \param mr The \c FMatrixRow instance to copy.
    # 
    def __init__(mr: FMatrixRow) -> None: pass

    ##
    # \brief Constructs the row proxy viewing row <em>i</em> of <em>m</em>.
    # 
    # \param m The wrapped matrix.
    # \param i The zero-based row index to view.
    # 
    def __init__(m: FMatrixExpression, i: int) -> None: pass

    ##
    # \brief Returns the row index this proxy refers to within the wrapped matrix.
    # 
    # \return The zero-based row index.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FMatrixRow instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FMatrixRow instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> FMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> FMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> FMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> FMatrixRow: pass

    ##
    # \brief Copy-assigns the contents of <em>r</em> to this row (via a temporary to handle aliasing).
    # 
    # \param r The source row.
    # 
    # \return \a self.
    # 
    def assign(r: FMatrixRow) -> FMatrixRow: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this row.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> FMatrixRow: pass

    ##
    # \brief Tells whether the row is empty (the wrapped matrix has zero columns).
    # 
    # \return <tt>True</tt> if the wrapped matrix has zero columns, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the size of the row (number of columns of the wrapped matrix).
    # 
    # \return The number of columns.
    # 
    def getSize() -> int: pass

    ##
    # \brief Returns the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return The value of the element <tt>m(index, i)</tt>.
    # 
    def getElement(i: int) -> float: pass

    ##
    # \brief Converts the \c FMatrixRow instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this row with those of <em>r</em> (via element-wise swap of the underlying matrix elements).
    # 
    # \param r The row to swap with.
    # 
    def swap(r: FMatrixRow) -> None: pass

    ##
    # \brief Sets the value of the element at column \a i of the row to \a v.
    # \param i The zero-based column index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns the wrapped matrix.
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> FMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \c FMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: FMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \c FMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: FMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return The value of the element <tt>m(index, i)</tt>.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return The value of the element <tt>m(index, i)</tt>.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the size of the row (number of columns of the wrapped matrix).
    # 
    # \return The number of columns.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c FMatrixRow instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> FMatrixRow: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstFVectorExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstFVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c FMatrixRow instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFMatrixExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFVectorExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFVectorExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Sets the value of the element at column \a i of the row to \a v.
    # \param i The zero-based column index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Adds the elements of the matrix row <em>r</em> to this row (via a temporary to handle aliasing).
    # 
    # \param r The source matrix row.
    # 
    # \return \a self.
    # 
    def __iadd__(r: FMatrixRow) -> FMatrixRow: pass

    ##
    # \brief Adds the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstFVectorExpression) -> FMatrixRow: pass

    ##
    # \brief Subtracts the elements of the matrix row <em>r</em> from this row (via a temporary to handle aliasing).
    # 
    # \param r The source matrix row.
    # 
    # \return \a self.
    # 
    def __isub__(r: FMatrixRow) -> FMatrixRow: pass

    ##
    # \brief Subtracts the elements of the vector expression <em>e</em> from this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstFVectorExpression) -> FMatrixRow: pass

    ##
    # \brief Multiplies every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> FMatrixRow: pass

    ##
    # \brief Divides every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> FMatrixRow: pass

    ##
    # \brief Divides every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> FMatrixRow: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    index = property(getIndex)
