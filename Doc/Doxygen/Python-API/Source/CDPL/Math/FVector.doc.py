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
# \brief Unbounded dense vector holding floating-point values of type <tt>float</tt>.
# 
class FVector(Boost.Python.instance):

    ##
    # \brief Constructs an empty vector (size zero).
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the vector <em>v</em>.
    # 
    # \param v The vector to copy.
    # 
    def __init__(v: FVector) -> None: pass

    ##
    # \brief Constructs a vector of size <em>n</em> with default-initialized elements.
    # 
    # \param n The desired vector size.
    # 
    def __init__(n: int) -> None: pass

    ##
    # \brief Constructs a vector of size <em>n</em> with every element initialized to <em>v</em>.
    # 
    # \param n The desired vector size.
    # \param v The value used for element initialization.
    # 
    def __init__(n: int, v: float) -> None: pass

    ##
    # \brief Constructs the vector from the vector expression <em>e</em> (materializing the expression result).
    # 
    # \param e The vector expression to materialize.
    # 
    def __init__(e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Constructs the vector from the vector expression <em>e</em> (materializing the expression result).
    # 
    # \param e The vector expression to materialize.
    # 
    def __init__(e: ConstDVectorExpression) -> None: pass

    ##
    # \brief Constructs the vector from the vector expression <em>e</em> (materializing the expression result).
    # 
    # \param e The vector expression to materialize.
    # 
    def __init__(e: ConstLVectorExpression) -> None: pass

    ##
    # \brief Constructs the vector from the vector expression <em>e</em> (materializing the expression result).
    # 
    # \param e The vector expression to materialize.
    # 
    def __init__(e: ConstULVectorExpression) -> None: pass

    ##
    # \brief Constructs the vector from the \c numpy.ndarray object \a a.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Resizes the vector to <em>n</em> elements.
    # 
    # \param n The new element count.
    # \param v The fill value for newly added elements.
    # 
    def resize(n: int, v: float = 0.0) -> None: pass

    ##
    # \brief Sets every element of the vector to the value <em>v</em>.
    # 
    # \param v The fill value.
    # 
    def clear(v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> FVector: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> FVector: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> FVector: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> FVector: pass

    ##
    # \brief Copy-assigns the elements of <em>v</em> to this vector.
    # 
    # \param v The source vector.
    # 
    # \return \a self.
    # 
    def assign(v: FVector) -> FVector: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this vector.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Tells whether the vector is empty.
    # 
    # \return <tt>True</tt> if the vector contains no elements, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the current element count.
    # 
    # \return The number of elements.
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
    # \brief Converts the \c FVector instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this vector with those of <em>v</em>.
    # 
    # \param v The vector to swap with.
    # 
    def swap(v: FVector) -> None: pass

    ##
    # \brief Sets the value of the element at index \a i to \a v.
    # \param i The zero-based element index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \c FVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(v: FVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \c FVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(v: FVector) -> bool: pass

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
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the element at index <em>i</em>.
    # 
    # \param i The zero-based element index.
    # 
    # \return The value of the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the current element count.
    # 
    # \return The number of elements.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c FVector instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> FVector: pass

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
    # \return A \c FVector instance holding the result of the subtraction.
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
    # \brief Sets the value of the element at index \a i to \a v.
    # \param i The zero-based element index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Adds the contents of the vector <em>v</em> element-wise to this vector (no alias check needed).
    # 
    # \param v The source vector.
    # 
    # \return \a self.
    # 
    def __iadd__(v: FVector) -> FVector: pass

    ##
    # \brief Adds the vector expression <em>e</em> element-wise to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstFVectorExpression) -> FVector: pass

    ##
    # \brief Subtracts the contents of the vector <em>v</em> element-wise from this vector (no alias check needed).
    # 
    # \param v The source vector.
    # 
    # \return \a self.
    # 
    def __isub__(v: FVector) -> FVector: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> element-wise from this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstFVectorExpression) -> FVector: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> FVector: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> FVector: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> FVector: pass

    objectID = property(getObjectID)

    size = property(getSize)
