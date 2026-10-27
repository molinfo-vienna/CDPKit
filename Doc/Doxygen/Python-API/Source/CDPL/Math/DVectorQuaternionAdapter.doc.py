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
# \brief Quaternion expression that exposes a 4-element vector as a quaternion (component indices <em>0-3</em> map to <em>C1-C4</em>).
# 
class DVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c DVectorQuaternionAdapter instance \a va.
    # \param va The \c DVectorQuaternionAdapter instance to copy.
    # 
    def __init__(va: DVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Constructs the adapter wrapping the 4-element vector <em>v</em>.
    # 
    # \param v The 4-element vector to be viewed as a quaternion.
    # 
    def __init__(v: DVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the quaternion expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this view.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Copies the components of <em>va</em> into this view (writing through to the wrapped vector).
    # 
    # \param va The source adapter.
    # 
    # \return \a self.
    # 
    def assign(va: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

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
    # \brief Converts the \c DVectorQuaternionAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the components of this view with those of <em>va</em>.
    # 
    # \param va The adapter to swap with.
    # 
    def swap(va: DVectorQuaternionAdapter) -> None: pass

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
    # \brief Assigns the four supplied component values to this view (writing through to the wrapped vector).
    # 
    # \param c1 The <em>C1</em> component value.
    # \param c2 The <em>C2</em> component value.
    # \param c3 The <em>C3</em> component value.
    # \param c4 The <em>C4</em> component value.
    # 
    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Returns the wrapped vector.
    # 
    # \return The wrapped vector closure.
    # 
    def getData() -> DVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == va</tt>.
    # \param va The \c DVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(va: DVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != va</tt>.
    # \param va The \c DVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(va: DVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c DVectorQuaternionAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DVectorQuaternionAdapter: pass

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
    # \return A \c DVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c DVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>t - self</tt>.
    # \param t Specifies the minuend.
    # \return A \c DVectorQuaternionAdapter instance holding the result of the subtraction.
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
    # \brief Adds the scalar <em>t</em> to component <em>C1</em> of this view.
    # 
    # \param t The scalar summand.
    # 
    # \return \a self.
    # 
    def __iadd__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Adds the vector adapter <em>va</em> componentwise to this view.
    # 
    # \param va The vector adapter to add.
    # 
    # \return \a self.
    # 
    def __iadd__(va: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Adds the quaternion expression <em>e</em> componentwise to this view.
    # 
    # \param e The quaternion expression to add.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from component <em>C1</em> of this view.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self.
    # 
    def __isub__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Subtracts the vector adapter <em>va</em> componentwise from this view.
    # 
    # \param va The vector adapter to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(va: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Subtracts the quaternion expression <em>e</em> componentwise from this view.
    # 
    # \param e The quaternion expression to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Multiplies every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Multiplies this view by the vector adapter <em>va</em> (Hamilton-product semantics).
    # 
    # \param va The vector adapter to multiply by.
    # 
    # \return \a self.
    # 
    def __imul__(va: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Multiplies this view by the quaternion expression <em>e</em> (Hamilton-product semantics).
    # 
    # \param e The quaternion expression to multiply by.
    # 
    # \return \a self.
    # 
    def __imul__(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Divides every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Divides this view by the vector adapter <em>va</em> (Hamilton-quotient semantics).
    # 
    # \param va The vector adapter to divide by.
    # 
    # \return \a self.
    # 
    def __idiv__(va: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Divides this view by the quaternion expression <em>e</em> (Hamilton-quotient semantics).
    # 
    # \param e The quaternion expression to divide by.
    # 
    # \return \a self.
    # 
    def __idiv__(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Divides every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Divides this view by the vector adapter <em>va</em> (Hamilton-quotient semantics).
    # 
    # \param va The vector adapter to divide by.
    # 
    # \return \a self.
    # 
    def __itruediv__(va: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Divides this view by the quaternion expression <em>e</em> (Hamilton-quotient semantics).
    # 
    # \param e The quaternion expression to divide by.
    # 
    # \return \a self.
    # 
    def __itruediv__(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    objectID = property(getObjectID)

    data = property(getData)
