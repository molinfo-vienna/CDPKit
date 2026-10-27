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
# \brief A memory-efficient pure-real quaternion with component values of type <tt>float</tt>.
# 
class FRealQuaternion(Boost.Python.instance):

    ##
    # \brief Constructs a zero-valued real quaternion (<em>C1</em> = 0).
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the real quaternion <em>q</em> (possibly converting the component type).
    # 
    # \param q The real quaternion to copy.
    # 
    def __init__(q: FRealQuaternion) -> None: pass

    ##
    # \brief Constructs the real quaternion with the supplied real component.
    # 
    # \param r The real component value.
    # 
    def __init__(r: float) -> None: pass

    ##
    # \brief Assigns the scalar <em>r</em> to the real component.
    # 
    # \param r The scalar value.
    # 
    # \return \a self.
    # 
    def set(r: float = 0.0) -> FRealQuaternion: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FRealQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FRealQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the real component <em>C1</em>.
    # 
    # \return The value of <em>C1</em>.
    # 
    def getC1() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C2</em> (always zero for a real quaternion).
    # 
    # \return The zero element.
    # 
    def getC2() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C3</em> (always zero for a real quaternion).
    # 
    # \return The zero element.
    # 
    def getC3() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C4</em> (always zero for a real quaternion).
    # 
    # \return The zero element.
    # 
    def getC4() -> float: pass

    ##
    # \brief Converts the \c FRealQuaternion instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Assigns the real component from <em>q</em> (possibly converting the component type).
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def assign(q: FRealQuaternion) -> FRealQuaternion: pass

    ##
    # \brief Swaps the real component value with <em>q</em>.
    # 
    # \param q The real quaternion to swap with.
    # 
    def swap(q: FRealQuaternion) -> None: pass

    ##
    # \brief Adds the scalar <em>t</em> to the real component.
    # 
    # \param t The scalar addend.
    # 
    # \return \a self.
    # 
    def __iadd__(t: float) -> FRealQuaternion: pass

    ##
    # \brief Adds the real component of <em>q</em> to this quaternion's real component.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __iadd__(q: object) -> FRealQuaternion: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from the real component.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self.
    # 
    def __isub__(t: float) -> FRealQuaternion: pass

    ##
    # \brief Subtracts the real component of <em>q</em> from this quaternion's real component.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __isub__(q: object) -> FRealQuaternion: pass

    ##
    # \brief Multiplies the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> FRealQuaternion: pass

    ##
    # \brief Multiplies the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __imul__(q: object) -> FRealQuaternion: pass

    ##
    # \brief Divides the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> FRealQuaternion: pass

    ##
    # \brief Divides the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __idiv__(q: object) -> FRealQuaternion: pass

    ##
    # \brief Divides the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> FRealQuaternion: pass

    ##
    # \brief Divides the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __itruediv__(q: object) -> FRealQuaternion: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c FRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: FRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstFQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstFQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c FRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: FRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstFQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstFQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c FRealQuaternion instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> FRealQuaternion: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstFQuaternionExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c ConstFQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstFQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>t + self</tt>.
    # \param t Specifies the first addend.
    # \return A \c ConstFQuaternionExpression instance holding the result of the addition.
    # 
    def __radd__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c FRealQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c FRealQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>t - self</tt>.
    # \param t Specifies the minuend.
    # \return A \c FRealQuaternion instance holding the result of the subtraction.
    # 
    def __rsub__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstFQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstFQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstFQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c ConstFQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstFQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>t // self</tt>.
    # \param t Specifies the dividend.
    # \return A \c ConstFQuaternionExpression instance holding the result of the division.
    # 
    def __rdiv__(t: float) -> ConstFQuaternionExpression: pass

    objectID = property(getObjectID)
