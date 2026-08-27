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
class DMatrixRow(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %DMatrixRow instance \a mr.
    # \param mr The \c %DMatrixRow instance to copy.
    # 
    def __init__(mr: DMatrixRow) -> None: pass

    ##
    # \brief Initializes the \c %DMatrixRow instance.
    # \param e 
    # \param i 
    # 
    def __init__(e: DMatrixExpression, i: int) -> None: pass

    ##
    # \brief Returns the row index this proxy refers to within the wrapped matrix.
    # 
    # \return The zero-based row index.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DMatrixRow instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DMatrixRow instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFVectorExpression) -> DMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDVectorExpression) -> DMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLVectorExpression) -> DMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULVectorExpression) -> DMatrixRow: pass

    ##
    # \brief Copy-assigns the contents of <em>r</em> to this row (via a temporary to handle aliasing).
    # 
    # \param r The source row.
    # 
    # \return \a self
    # 
    def assign(r: DMatrixRow) -> DMatrixRow: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

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

    def getElement(i: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this row with those of <em>r</em> (via element-wise swap of the underlying matrix elements).
    # 
    # \param r The row to swap with.
    # 
    def swap(r: DMatrixRow) -> None: pass

    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> DMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \c %DMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: DMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \c %DMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: DMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns a reference to the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return A reference to the underlying element <tt>m(index, i)</tt>.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns a reference to the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return A reference to the underlying element.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the size of the row (number of columns of the wrapped matrix).
    # 
    # \return The number of columns.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %DMatrixRow instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> DMatrixRow: pass

    def __neg__() -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstDVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %DMatrixRow instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDVectorExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDVectorExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDVectorExpression: pass

    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += r</tt>.
    # \param r Specifies the second addend.
    # \return The updated \c %DMatrixRow instance \a self.
    # 
    def __iadd__(r: DMatrixRow) -> DMatrixRow: pass

    ##
    # \brief Adds the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def __iadd__(e: ConstDVectorExpression) -> DMatrixRow: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= r</tt>.
    # \param r Specifies the subtrahend.
    # \return The updated \c %DMatrixRow instance \a self.
    # 
    def __isub__(r: DMatrixRow) -> DMatrixRow: pass

    ##
    # \brief Subtracts the elements of the vector expression <em>e</em> from this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def __isub__(e: ConstDVectorExpression) -> DMatrixRow: pass

    ##
    # \brief Multiplies every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: float) -> DMatrixRow: pass

    ##
    # \brief Divides every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __idiv__(t: float) -> DMatrixRow: pass

    def __itruediv__(t: float) -> DMatrixRow: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    index = property(getIndex)
