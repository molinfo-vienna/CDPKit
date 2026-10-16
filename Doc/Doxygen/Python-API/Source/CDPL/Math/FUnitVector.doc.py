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
# \brief Memory-efficient immutable unit vector with element values of type <tt>float</tt>.
# 
class FUnitVector(Boost.Python.instance):

    ##
    # \brief Constructs an empty unit vector (size zero, index zero).
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the unit vector <em>v</em>.
    # 
    # \param v The unit vector to copy.
    # 
    def __init__(v: FUnitVector) -> None: pass

    ##
    # \brief Constructs a unit vector of size <em>n</em> with the <em>1</em> element at index <em>i</em>.
    # 
    # \param n The element count.
    # \param i The zero-based index of the non-zero element.
    # 
    def __init__(n: int, i: int) -> None: pass

    ##
    # \brief Resizes the logical element count to <em>n</em>.
    # 
    # \param n The new element count.
    # 
    def resize(n: int) -> None: pass

    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FUnitVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FUnitVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Tells whether the vector has zero logical size.
    # 
    # \return <tt>True</tt> if the logical size is zero, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the logical element count.
    # 
    # \return The element count.
    # 
    def getSize() -> int: pass

    ##
    # \brief Returns the element at index <em>i</em>.
    # 
    # \param i The zero-based element index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def getElement(i: int) -> float: pass

    ##
    # \brief Converts the \c FUnitVector instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Copy-assigns the size and unit index from <em>v</em>.
    # 
    # \param v The source unit vector.
    # 
    # \return \a self.
    # 
    def assign(v: FUnitVector) -> FUnitVector: pass

    ##
    # \brief Swaps the size and unit index with <em>v</em>.
    # 
    # \param v The unit vector to swap with.
    # 
    def swap(v: FUnitVector) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \c FUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(v: FUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \c FUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(v: FUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the element at index <em>i</em>.
    # 
    # \param i The zero-based element index.
    # 
    # \return A reference to either <em>1</em> (if <em>i</em> equals the unit index) or <em>0</em>. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the element at index <em>i</em>.
    # 
    # \param i The zero-based element index.
    # 
    # \return A reference to either <em>1</em> (if <em>i</em> equals the unit index) or <em>0</em>. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the logical element count.
    # 
    # \return The element count.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c FUnitVector instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> FUnitVector: pass

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
    # \return A \c FUnitVector instance holding the result of the subtraction.
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

    index = property(getIndex)

    objectID = property(getObjectID)

    size = property(getSize)
