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
# \brief Represents the outcome of mathematical expressions/operations that result in a 3D grid.
# 
class ConstFGridExpression(Boost.Python.instance):

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ConstFGridExpression instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ConstFGridExpression instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the first-axis size.
    # 
    # \return The size along the first axis.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the second-axis size.
    # 
    # \return The size along the second axis.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Returns the third-axis size.
    # 
    # \return The size along the third axis.
    # 
    def getSize3() -> int: pass

    ##
    # \brief Tells whether the grid is empty.
    # 
    # \return <tt>True</tt> if the underlying storage holds no elements, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def getElement(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Converts the \c ConstFGridExpression instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __call__(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Returns the element at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __getitem__(ijk: tuple) -> float: pass

    ##
    # \brief Returns the total element count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
    # 
    # \return The total number of elements.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c ConstFGridExpression instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstFGridExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstFGridExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ConstFGridExpression instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstFGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFGridExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstFGridExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFGridExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
