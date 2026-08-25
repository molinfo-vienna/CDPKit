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
# \brief General 4-component quaternion with component values of type <tt>unsigned long</tt>.
# 
class ULQuaternion(Boost.Python.instance):

    ##
    # \brief Constructs an uninitialized quaternion.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the quaternion <em>q</em>.
    # 
    # \param q The quaternion to copy.
    # 
    def __init__(q: ULQuaternion) -> None: pass

    ##
    # \brief Constructs the quaternion with the supplied component values (omitted components default to the value-initialized ValueType).
    # 
    # \param c1 The real component.
    # \param c2 The first imaginary component.
    # \param c3 The second imaginary component.
    # \param c4 The third imaginary component.
    # 
    def __init__(c1: int, c2: int = 0, c3: int = 0, c4: int = 0) -> None: pass

    ##
    # \brief Initializes the \c %ULQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstFQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %ULQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstDQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %ULQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstLQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %ULQuaternion instance.
    # \param e 
    # 
    def __init__(e: ConstULQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \c %ULQuaternion instance.
    # \param a 
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ULQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ULQuaternion instances \e a and \e b reference different C++ objects. 
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
    def assign(e: ConstFQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this quaternion without intermediate temporary.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Copy-assigns the components of <em>q</em> to this quaternion.
    # 
    # \param q The source quaternion.
    # 
    # \return \a self
    # 
    def assign(q: ULQuaternion) -> ULQuaternion: pass

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
    def getC1() -> int: pass

    ##
    # \brief Returns a reference to the imaginary component <em>C2</em>.
    # 
    # \return A reference to <em>C2</em>.
    # 
    def getC2() -> int: pass

    ##
    # \brief Returns a reference to the imaginary component <em>C3</em>.
    # 
    # \return A reference to <em>C3</em>.
    # 
    def getC3() -> int: pass

    ##
    # \brief Returns a reference to the imaginary component <em>C4</em>.
    # 
    # \return A reference to <em>C4</em>.
    # 
    def getC4() -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the four components of this quaternion with those of <em>q</em>.
    # 
    # \param q The quaternion to swap with.
    # 
    def swap(q: ULQuaternion) -> None: pass

    def setC1(v: int) -> None: pass

    def setC2(v: int) -> None: pass

    def setC3(v: int) -> None: pass

    def setC4(v: int) -> None: pass

    ##
    # \brief Sets the four quaternion components to the supplied values (omitted arguments default to the value-initialized ValueType).
    # 
    # \param c1 The new real component.
    # \param c2 The new first imaginary component.
    # \param c3 The new second imaginary component.
    # \param c4 The new third imaginary component.
    # 
    def set(c1: int = 0, c2: int = 0, c3: int = 0, c4: int = 0) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c %ULQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ULQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c %ConstULQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstULQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c %ULQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ULQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c %ConstULQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstULQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %ULQuaternion instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> ULQuaternion: pass

    def __neg__() -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    def __radd__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c %ULQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %ULQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    def __rsub__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstULQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstULQuaternionExpression: pass

    def __rdiv__(t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param t Specifies the second addend.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __iadd__(t: int) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __iadd__(q: ULQuaternion) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __iadd__(q: ConstULQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param t Specifies the subtrahend.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __isub__(t: int) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __isub__(q: ULQuaternion) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __isub__(q: ConstULQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __imul__(t: int) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __imul__(q: ULQuaternion) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __imul__(q: ConstULQuaternionExpression) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __idiv__(t: int) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __idiv__(q: ULQuaternion) -> ULQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c %ULQuaternion instance \a self.
    # 
    def __idiv__(q: ConstULQuaternionExpression) -> ULQuaternion: pass

    def __itruediv__(t: int) -> ULQuaternion: pass

    def __itruediv__(q: ULQuaternion) -> ULQuaternion: pass

    def __itruediv__(q: ConstULQuaternionExpression) -> ULQuaternion: pass

    objectID = property(getObjectID)
