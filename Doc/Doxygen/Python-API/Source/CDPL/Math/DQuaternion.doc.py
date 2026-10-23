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
# \brief General 4-component quaternion with component values of type <tt>double</tt>.
# 
class DQuaternion(Boost.Python.instance):

    ##
    # \brief Constructs an uninitialized quaternion.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the quaternion <em>q</em>.
    # 
    # \param q The quaternion to copy.
    # 
    def __init__(q: DQuaternion) -> None: pass

    ##
    # \brief Constructs the quaternion with the supplied component values.
    # 
    # \param c1 The real component.
    # \param c2 The first imaginary component.
    # \param c3 The second imaginary component.
    # \param c4 The third imaginary component.
    # 
    def __init__(c1: float, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Constructs the quaternion from the quaternion expression <em>e</em>.
    # 
    # \param e The quaternion expression to materialize.
    # 
    def __init__(e: ConstFQuaternionExpression) -> None: pass

    ##
    # \brief Constructs the quaternion from the quaternion expression <em>e</em>.
    # 
    # \param e The quaternion expression to materialize.
    # 
    def __init__(e: ConstDQuaternionExpression) -> None: pass

    ##
    # \brief Constructs the quaternion from the quaternion expression <em>e</em>.
    # 
    # \param e The quaternion expression to materialize.
    # 
    def __init__(e: ConstLQuaternionExpression) -> None: pass

    ##
    # \brief Constructs the quaternion from the quaternion expression <em>e</em>.
    # 
    # \param e The quaternion expression to materialize.
    # 
    def __init__(e: ConstULQuaternionExpression) -> None: pass

    ##
    # \brief Constructs the quaternion from the \c numpy.ndarray object \a a.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion (via a temporary to handle aliasing).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion (via a temporary to handle aliasing).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion (via a temporary to handle aliasing).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion (via a temporary to handle aliasing).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Copy-assigns the components of <em>q</em> to this quaternion.
    # 
    # \param q The source quaternion.
    # 
    # \return \a self.
    # 
    def assign(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this quaternion.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Returns the real component <em>C1</em>.
    # 
    # \return The value of <em>C1</em>.
    # 
    def getC1() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C2</em>.
    # 
    # \return The value of <em>C2</em>.
    # 
    def getC2() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C3</em>.
    # 
    # \return The value of <em>C3</em>.
    # 
    def getC3() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C4</em>.
    # 
    # \return The value of <em>C4</em>.
    # 
    def getC4() -> float: pass

    ##
    # \brief Converts the \c DQuaternion instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the four components of this quaternion with those of <em>q</em>.
    # 
    # \param q The quaternion to swap with.
    # 
    def swap(q: DQuaternion) -> None: pass

    ##
    # \brief Sets the value of the real component \e C1 to \a v.
    # \param v The new value of the real component \e C1.
    # 
    def setC1(v: float) -> None: pass

    ##
    # \brief Sets the value of the imaginary component \e C2 to \a v.
    # \param v The new value of the imaginary component \e C2.
    # 
    def setC2(v: float) -> None: pass

    ##
    # \brief Sets the value of the imaginary component \e C3 to \a v.
    # \param v The new value of the imaginary component \e C3.
    # 
    def setC3(v: float) -> None: pass

    ##
    # \brief Sets the value of the imaginary component \e C4 to \a v.
    # \param v The new value of the imaginary component \e C4.
    # 
    def setC4(v: float) -> None: pass

    ##
    # \brief Sets the four quaternion components to the supplied values.
    # 
    # \param c1 The new real component.
    # \param c2 The new first imaginary component.
    # \param c3 The new second imaginary component.
    # \param c4 The new third imaginary component.
    # 
    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c DQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: DQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c DQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: DQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c DQuaternion instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DQuaternion: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstDQuaternionExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c ConstDQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstDQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>t + self</tt>.
    # \param t Specifies the first addend.
    # \return A \c ConstDQuaternionExpression instance holding the result of the addition.
    # 
    def __radd__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c DQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c DQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>t - self</tt>.
    # \param t Specifies the minuend.
    # \return A \c DQuaternion instance holding the result of the subtraction.
    # 
    def __rsub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>t // self</tt>.
    # \param t Specifies the dividend.
    # \return A \c ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __rdiv__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Adds the scalar <em>t</em> to the real component.
    # 
    # \param t The scalar addend.
    # 
    # \return \a self.
    # 
    def __iadd__(t: float) -> DQuaternion: pass

    ##
    # \brief Adds the quaternion <em>q</em> to this quaternion (via a temporary to handle aliasing).
    # 
    # \param q The source quaternion.
    # 
    # \return \a self.
    # 
    def __iadd__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Adds the quaternion expression <em>e</em> to this quaternion (via a temporary to handle aliasing).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from the real component.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self.
    # 
    def __isub__(t: float) -> DQuaternion: pass

    ##
    # \brief Subtracts the quaternion <em>q</em> from this quaternion (via a temporary to handle aliasing).
    # 
    # \param q The source quaternion.
    # 
    # \return \a self.
    # 
    def __isub__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Subtracts the quaternion expression <em>e</em> from this quaternion (via a temporary to handle aliasing).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Multiplies every component by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DQuaternion: pass

    ##
    # \brief Right-multiplies this quaternion by the quaternion <em>q</em> (Hamilton product, via a temporary).
    # 
    # \param q The right-hand quaternion.
    # 
    # \return \a self.
    # 
    def __imul__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Right-multiplies this quaternion by the quaternion expression <em>e</em> (Hamilton product, via a temporary).
    # 
    # \param e The right-hand quaternion expression.
    # 
    # \return \a self.
    # 
    def __imul__(e: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Divides every component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DQuaternion: pass

    ##
    # \brief Right-divides this quaternion by the quaternion <em>q</em> (Hamilton-product inverse, via a temporary).
    # 
    # \param q The right-hand quaternion.
    # 
    # \return \a self.
    # 
    def __idiv__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Right-divides this quaternion by the quaternion expression <em>e</em> (Hamilton-product inverse, via a temporary).
    # 
    # \param e The right-hand quaternion expression.
    # 
    # \return \a self.
    # 
    def __idiv__(e: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Divides every component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DQuaternion: pass

    ##
    # \brief Right-divides this quaternion by the quaternion <em>q</em> (Hamilton-product inverse, via a temporary).
    # 
    # \param q The right-hand quaternion.
    # 
    # \return \a self.
    # 
    def __itruediv__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Right-divides this quaternion by the quaternion expression <em>e</em> (Hamilton-product inverse, via a temporary).
    # 
    # \param e The right-hand quaternion expression.
    # 
    # \return \a self.
    # 
    def __itruediv__(e: ConstDQuaternionExpression) -> DQuaternion: pass

    objectID = property(getObjectID)
