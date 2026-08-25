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
class ConstDMatrixColumn(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %ConstDMatrixColumn instance \a c.
    # \param c The \c %ConstDMatrixColumn instance to copy.
    # 
    def __init__(c: ConstDMatrixColumn) -> None: pass

    ##
    # \brief Initializes the \c %ConstDMatrixColumn instance.
    # \param e 
    # \param i 
    # 
    def __init__(e: ConstDMatrixExpression, i: int) -> None: pass

    ##
    # \brief Returns the column index this proxy refers to within the wrapped matrix.
    # 
    # \return The zero-based column index.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ConstDMatrixColumn instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ConstDMatrixColumn instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

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

    def getElement(i: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Returns a reference to the wrapped matrix (via its stored closure).
    # 
    # \return A reference to the wrapped matrix closure.
    # 
    def getData() -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == c</tt>.
    # \param c The \c %ConstDMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(c: ConstDMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != c</tt>.
    # \param c The \c %ConstDMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(c: ConstDMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns a reference to the element at row <em>i</em> of the column.
    # 
    # \param i The zero-based row index.
    # 
    # \return A reference to the underlying element <tt>m(i, index)</tt>.
    # 
    def __call__(i: int) -> float: pass

    def __getitem__(i: int) -> float: pass

    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %ConstDMatrixColumn instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> ConstDMatrixColumn: pass

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
    # \return A \c %ConstDMatrixColumn instance holding the result of the subtraction.
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

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    index = property(getIndex)
