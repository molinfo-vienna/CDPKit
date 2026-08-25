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
    # \brief Constructs the quaternion with the supplied component values (omitted components default to the value-initialized ValueType).
    # 
    # \param c1 The real component.
    # \param c2 The first imaginary component.
    # \param c3 The second imaginary component.
    # \param c4 The third imaginary component.
    # 
    def __init__(c1: float, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Initializes the \c %DQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstFQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %DQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstDQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %DQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstLQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %DQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstULQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %DQuaternion instance.
    # \param a 
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Copy-assigns the components of <em>q</em> to this quaternion.
    # 
    # \param q The source quaternion.
    # 
    # \return \a self
    # 
    def assign(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Returns a reference to the real component <em>C1</em>.
    # 
    # \return A reference to <em>C1</em>.
    # 
    def getC1() -> float: pass

    ##
    # \brief Returns a reference to the imaginary component <em>C2</em>.
    # 
    # \return A reference to <em>C2</em>.
    # 
    def getC2() -> float: pass

    ##
    # \brief Returns a reference to the imaginary component <em>C3</em>.
    # 
    # \return A reference to <em>C3</em>.
    # 
    def getC3() -> float: pass

    ##
    # \brief Returns a reference to the imaginary component <em>C4</em>.
    # 
    # \return A reference to <em>C4</em>.
    # 
    def getC4() -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the four components of this quaternion with those of <em>q</em>.
    # 
    # \param q The quaternion to swap with.
    # 
    def swap(q: DQuaternion) -> None: pass

    def setC1(v: float) -> None: pass

    def setC2(v: float) -> None: pass

    def setC3(v: float) -> None: pass

    def setC4(v: float) -> None: pass

    ##
    # \brief Sets the four quaternion components to the supplied values (omitted arguments default to the value-initialized ValueType).
    # 
    # \param c1 The new real component.
    # \param c2 The new first imaginary component.
    # \param c3 The new second imaginary component.
    # \param c4 The new third imaginary component.
    # 
    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c %DQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: DQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c %DQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: DQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %DQuaternion instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> DQuaternion: pass

    def __neg__() -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    def __radd__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c %DQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %DQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    def __rsub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDQuaternionExpression: pass

    def __rdiv__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param t Specifies the second addend.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __iadd__(t: float) -> DQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __iadd__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __iadd__(q: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param t Specifies the subtrahend.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __isub__(t: float) -> DQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __isub__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __isub__(q: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __imul__(t: float) -> DQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __imul__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __imul__(q: ConstDQuaternionExpression) -> DQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __idiv__(t: float) -> DQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __idiv__(q: DQuaternion) -> DQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c %DQuaternion instance \a self.
    # 
    def __idiv__(q: ConstDQuaternionExpression) -> DQuaternion: pass

    def __itruediv__(t: float) -> DQuaternion: pass

    def __itruediv__(q: DQuaternion) -> DQuaternion: pass

    def __itruediv__(q: ConstDQuaternionExpression) -> DQuaternion: pass

    objectID = property(getObjectID)
