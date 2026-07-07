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
# \brief Bounded <em>4</em> element vector holding floating-point values of type <tt>double</tt>.
# 
class Vector4D(Boost.Python.instance):

    ##
    # \brief Constructs a zero-initialized <em>N</em> element vector.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the fixed-size vector <em>v</em>.
    # 
    # \param v The fixed-size vector to copy.
    # 
    def __init__(v: Vector4D) -> None: pass

    ##
    # \brief Constructs a copy of the fixed-size vector <em>v</em>.
    # 
    # \param v The fixed-size vector to copy.
    # 
    def __init__(v: float) -> None: pass

    ##
    # \brief Initializes the \c %Vector4D instance.
    # \param e 
    # 
    def __init__(e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Initializes the \c %Vector4D instance.
    # \param e 
    # 
    def __init__(e: ConstDVectorExpression) -> None: pass

    ##
    # \brief Initializes the \c %Vector4D instance.
    # \param e 
    # 
    def __init__(e: ConstLVectorExpression) -> None: pass

    ##
    # \brief Initializes the \c %Vector4D instance.
    # \param e 
    # 
    def __init__(e: ConstULVectorExpression) -> None: pass

    ##
    # \brief Initializes the \c %Vector4D instance.
    # \param a 
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Sets every element of the vector to the value <em>v</em>.
    # 
    # \param v The fill value.
    # 
    def clear(v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %Vector4D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Vector4D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this fixed-size vector without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFVectorExpression) -> Vector4D: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this fixed-size vector without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDVectorExpression) -> Vector4D: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this fixed-size vector without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLVectorExpression) -> Vector4D: pass

    ##
    # \brief Assigns the elements of the vector expression <em>e</em> to this fixed-size vector without intermediate temporary.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULVectorExpression) -> Vector4D: pass

    ##
    # \brief Copy-assigns the elements of <em>v</em> to this fixed-size vector.
    # 
    # \param v The source fixed-size vector.
    # 
    # \return \a self
    # 
    def assign(v: Vector4D) -> Vector4D: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Tells whether the vector is empty (<em>N</em> is zero).
    # 
    # \return <tt>True</tt> if <em>N</em> is zero, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the fixed element count <em>N</em>.
    # 
    # \return The element count.
    # 
    def getSize() -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getElement(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this fixed-size vector with those of <em>v</em>.
    # 
    # \param v The fixed-size vector to swap with.
    # 
    def swap(v: Vector4D) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \c %Vector4D instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(v: Vector4D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \c %Vector4D instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(v: Vector4D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns a reference to the element at index <em>i</em>.
    # 
    # \param i The zero-based element index.
    # 
    # \return A reference to the element. 
    # 
    # \throw Base.IndexError if <em>i</em> is out of range.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %Vector4D instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> Vector4D: pass

    ##
    # \brief 
    # \return 
    #
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
    # \return A \c %Vector4D instance holding the result of the subtraction.
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

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += v</tt>.
    # \param v Specifies the second addend.
    # \return The updated \c %Vector4D instance \a self.
    # 
    def __iadd__(v: Vector4D) -> Vector4D: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %Vector4D instance \a self.
    # 
    def __iadd__(e: ConstDVectorExpression) -> Vector4D: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= v</tt>.
    # \param v Specifies the subtrahend.
    # \return The updated \c %Vector4D instance \a self.
    # 
    def __isub__(v: Vector4D) -> Vector4D: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %Vector4D instance \a self.
    # 
    def __isub__(e: ConstDVectorExpression) -> Vector4D: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %Vector4D instance \a self.
    # 
    def __imul__(t: float) -> Vector4D: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %Vector4D instance \a self.
    # 
    def __idiv__(t: float) -> Vector4D: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> Vector4D: pass

    objectID = property(getObjectID)

    size = property(getSize)
