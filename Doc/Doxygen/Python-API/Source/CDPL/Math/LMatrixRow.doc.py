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
class LMatrixRow(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %LMatrixRow instance \a mr.
    # \param mr The \c %LMatrixRow instance to copy.
    # 
    def __init__(mr: LMatrixRow) -> None: pass

    ##
    # \brief Initializes the \c %LMatrixRow instance.
    # \param e 
    # \param i 
    # 
    def __init__(e: LMatrixExpression, i: int) -> None: pass

    ##
    # \brief Returns the row index this proxy refers to within the wrapped matrix.
    # 
    # \return The zero-based row index.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %LMatrixRow instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %LMatrixRow instances \e a and \e b reference different C++ objects. 
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
    def assign(e: ConstFVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this row without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Copy-assigns the contents of <em>r</em> to this row (via a temporary to handle aliasing).
    # 
    # \param r The source row.
    # 
    # \return \a self
    # 
    def assign(r: LMatrixRow) -> LMatrixRow: pass

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

    def getElement(i: int) -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this row with those of <em>r</em> (via element-wise swap of the underlying matrix elements).
    # 
    # \param r The row to swap with.
    # 
    def swap(r: LMatrixRow) -> None: pass

    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> LMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \c %LMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: LMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstLVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \c %LMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: LMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstLVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns a reference to the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return A reference to the underlying element <tt>m(index, i)</tt>.
    # 
    def __call__(i: int) -> int: pass

    ##
    # \brief Returns a reference to the element at column <em>i</em> of the row.
    # 
    # \param i The zero-based column index.
    # 
    # \return A reference to the underlying element.
    # 
    def __getitem__(i: int) -> int: pass

    ##
    # \brief Returns the size of the row (number of columns of the wrapped matrix).
    # 
    # \return The number of columns.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %LMatrixRow instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> LMatrixRow: pass

    def __neg__() -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstLVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %LMatrixRow instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Divides every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __div__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Divides every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __truediv__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLVectorExpression: pass

    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += r</tt>.
    # \param r Specifies the second addend.
    # \return The updated \c %LMatrixRow instance \a self.
    # 
    def __iadd__(r: LMatrixRow) -> LMatrixRow: pass

    ##
    # \brief Adds the elements of the vector expression <em>e</em> to this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def __iadd__(e: ConstLVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= r</tt>.
    # \param r Specifies the subtrahend.
    # \return The updated \c %LMatrixRow instance \a self.
    # 
    def __isub__(r: LMatrixRow) -> LMatrixRow: pass

    ##
    # \brief Subtracts the elements of the vector expression <em>e</em> from this row (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def __isub__(e: ConstLVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Multiplies every element of this row by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: int) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %LMatrixRow instance \a self.
    # 
    def __idiv__(t: int) -> LMatrixRow: pass

    def __itruediv__(t: int) -> LMatrixRow: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    index = property(getIndex)
