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
# \brief Quaternion expression that exposes a 4-element vector as a quaternion (component indices 0-3 map to C1-C4).
# 
class LVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %LVectorQuaternionAdapter instance \a a.
    # \param a The \c %LVectorQuaternionAdapter instance to copy.
    # 
    def __init__(a: LVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Initializes the \c %LVectorQuaternionAdapter instance.
    # \param e 
    # 
    def __init__(e: LVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %LVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %LVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Copies the components of <em>a</em> into this view (writing through to the wrapped vector).
    # 
    # \param a The source adapter.
    # 
    # \return \a self
    # 
    def assign(a: LVectorQuaternionAdapter) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Returns a reference to component C1.
    # 
    # \return A reference to C1.
    # 
    def getC1() -> int: pass

    ##
    # \brief Returns a reference to component C2.
    # 
    # \return A reference to C2.
    # 
    def getC2() -> int: pass

    ##
    # \brief Returns a reference to component C3.
    # 
    # \return A reference to C3.
    # 
    def getC3() -> int: pass

    ##
    # \brief Returns a reference to component C4.
    # 
    # \return A reference to C4.
    # 
    def getC4() -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the components of this view with those of <em>a</em>.
    # 
    # \param a The adapter to swap with.
    # 
    def swap(a: LVectorQuaternionAdapter) -> None: pass

    def setC1(v: int) -> None: pass

    def setC2(v: int) -> None: pass

    def setC3(v: int) -> None: pass

    def setC4(v: int) -> None: pass

    ##
    # \brief Assigns the four supplied component values to this view (writing through to the wrapped vector).
    # 
    # \param c1 The C1 component value.
    # \param c2 The C2 component value.
    # \param c3 The C3 component value.
    # \param c4 The C4 component value.
    # 
    def set(c1: int = 0, c2: int = 0, c3: int = 0, c4: int = 0) -> None: pass

    ##
    # \brief Returns a reference to the wrapped vector (via its stored closure).
    # 
    # \return A reference to the wrapped vector closure.
    # 
    def getData() -> LVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == a</tt>.
    # \param a The \c %LVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(a: LVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c %ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != a</tt>.
    # \param a The \c %LVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(a: LVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c %ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %LVectorQuaternionAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> LVectorQuaternionAdapter: pass

    def __neg__() -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    def __radd__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c %LVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %LVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    def __rsub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstLQuaternionExpression: pass

    def __rdiv__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Adds the scalar <em>t</em> to component C1 of this view.
    # 
    # \param t The scalar summand.
    # 
    # \return \a self
    # 
    def __iadd__(t: int) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param a Specifies the second addend.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __iadd__(a: LVectorQuaternionAdapter) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __iadd__(q: ConstLQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from component C1 of this view.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self
    # 
    def __isub__(t: int) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param a Specifies the subtrahend.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __isub__(a: LVectorQuaternionAdapter) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __isub__(q: ConstLQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Multiplies every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: int) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= a</tt>.
    # \param a Specifies the multiplier.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __imul__(a: LVectorQuaternionAdapter) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __imul__(q: ConstLQuaternionExpression) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Divides every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __idiv__(t: int) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= a</tt>.
    # \param a Specifies the divisor.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __idiv__(a: LVectorQuaternionAdapter) -> LVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c %LVectorQuaternionAdapter instance \a self.
    # 
    def __idiv__(q: ConstLQuaternionExpression) -> LVectorQuaternionAdapter: pass

    def __itruediv__(t: int) -> LVectorQuaternionAdapter: pass

    def __itruediv__(a: LVectorQuaternionAdapter) -> LVectorQuaternionAdapter: pass

    def __itruediv__(q: ConstLQuaternionExpression) -> LVectorQuaternionAdapter: pass

    objectID = property(getObjectID)

    data = property(getData)
