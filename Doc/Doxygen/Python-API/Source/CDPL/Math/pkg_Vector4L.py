#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class Vector4L(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param self The \e %Vector4L instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param self The \e %Vector4L instance to initialize.
    # \param v 
    #
    def __init__(self: object, v: Vector4L) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param self The \e %Vector4L instance to initialize.
    # \param v 
    #
    def __init__(self: object, v: int) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param arg1 The \e %Vector4L instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param arg1 The \e %Vector4L instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstDVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param arg1 The \e %Vector4L instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstLVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param arg1 The \e %Vector4L instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstULVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector4L instance.
    # \param arg1 The \e %Vector4L instance to initialize.
    # \param a 
    #
    def __init__(arg1: object, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param v 
    #
    def clear(self: Vector4L, v: int = 0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Vector4L instance this method is called upon.
    #
    # Different Python \e %Vector4L instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Vector4L instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Vector4L) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector4L instance \a e.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param e The \e %Vector4L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Vector4L, e: ConstFVectorExpression) -> Vector4L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector4L instance \a e.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param e The \e %Vector4L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Vector4L, e: ConstDVectorExpression) -> Vector4L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector4L instance \a e.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param e The \e %Vector4L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Vector4L, e: ConstLVectorExpression) -> Vector4L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector4L instance \a e.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param e The \e %Vector4L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Vector4L, e: ConstULVectorExpression) -> Vector4L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector4L instance \a v.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param v The \e %Vector4L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Vector4L, v: Vector4L) -> Vector4L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Vector4L instance \a a.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param a The \e %Vector4L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Vector4L, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \return 
    #
    def isEmpty(self: Vector4L) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \return 
    #
    def getSize(self: Vector4L) -> int: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: Vector4L, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \return 
    #
    def toArray(self: Vector4L) -> object: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param v 
    #
    def swap(self: Vector4L, v: Vector4L) -> None: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: Vector4L, i: int, v: int) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param v The \e %Vector4L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Vector4L, v: Vector4L) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param e The \e %Vector4L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Vector4L, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param v The \e %Vector4L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Vector4L, v: Vector4L) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %Vector4L instance this method is called upon.
    # \param e The \e %Vector4L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Vector4L, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: Vector4L, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: Vector4L, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \return 
    #
    def __len__(self: Vector4L) -> int: pass

    ##
    # \brief Returns a string representation of the \e %Vector4L instance.
    # \param self The \e %Vector4L instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: Vector4L) -> str: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \return 
    #
    def __pos__(self: Vector4L) -> Vector4L: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %Vector4L instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %Vector4L instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %Vector4L instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %Vector4L instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %Vector4L instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %Vector4L instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %Vector4L instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %Vector4L instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %Vector4L instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %Vector4L instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: Vector4L, i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += v</tt>.
    # \param self The \e %Vector4L instance acting as in-place addend.
    # \param v Specifies the second addend.
    # \return The updated \e %Vector4L instance \a self.
    #
    def __iadd__(self: Vector4L, v: Vector4L) -> Vector4L: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %Vector4L instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %Vector4L instance \a self.
    #
    def __iadd__(self: Vector4L, e: ConstLVectorExpression) -> Vector4L: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= v</tt>.
    # \param self The \e %Vector4L instance acting as in-place minuend.
    # \param v Specifies the subtrahend.
    # \return The updated \e %Vector4L instance \a self.
    #
    def __isub__(self: Vector4L, v: Vector4L) -> Vector4L: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %Vector4L instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %Vector4L instance \a self.
    #
    def __isub__(self: Vector4L, e: ConstLVectorExpression) -> Vector4L: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %Vector4L instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %Vector4L instance \a self.
    #
    def __imul__(self: Vector4L, t: int) -> Vector4L: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %Vector4L instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %Vector4L instance \a self.
    #
    def __idiv__(self: Vector4L, t: int) -> Vector4L: pass

    ##
    # \brief 
    # \param self The \e %Vector4L instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: Vector4L, t: int) -> Vector4L: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
