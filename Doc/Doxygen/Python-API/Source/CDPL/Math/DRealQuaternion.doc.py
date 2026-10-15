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
# \brief A memory-efficient pure-real quaternion with component values of type <tt>double</tt>.
# 
class DRealQuaternion(Boost.Python.instance):

    ##
    # \brief Constructs a zero-valued real quaternion (<em>C1</em> = 0).
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the real quaternion <em>q</em> (possibly converting the component type).
    # 
    # \param q The real quaternion to copy.
    # 
    def __init__(q: DRealQuaternion) -> None: pass

    ##
    # \brief Constructs the real quaternion with the supplied real component.
    # 
    # \param r The real component value.
    # 
    def __init__(r: float) -> None: pass

    def set(r: float = 0.0) -> DRealQuaternion: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DRealQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DRealQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the real component <em>C1</em>.
    # 
    # \return A reference to <em>C1</em>.
    # 
    def getC1() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C2</em> (always zero for a real quaternion).
    # 
    # \return A reference to the zero element.
    # 
    def getC2() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C3</em> (always zero for a real quaternion).
    # 
    # \return A reference to the zero element.
    # 
    def getC3() -> float: pass

    ##
    # \brief Returns the imaginary component <em>C4</em> (always zero for a real quaternion).
    # 
    # \return A reference to the zero element.
    # 
    def getC4() -> float: pass

    ##
    # \brief Converts the \c DRealQuaternion instance into a corresponding \e NumPy array.
    # \return The generated \e NumPy array.
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
    def assign(q: DRealQuaternion) -> DRealQuaternion: pass

    ##
    # \brief Swaps the real component value with <em>q</em>.
    # 
    # \param q The real quaternion to swap with.
    # 
    def swap(q: DRealQuaternion) -> None: pass

    ##
    # \brief Adds the scalar <em>t</em> to the real component.
    # 
    # \param t The scalar addend.
    # 
    # \return \a self.
    # 
    def __iadd__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Adds the real component of <em>q</em> to this quaternion's real component.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __iadd__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from the real component.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self.
    # 
    def __isub__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Subtracts the real component of <em>q</em> from this quaternion's real component.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __isub__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Multiplies the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Multiplies the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __imul__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Divides the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Divides the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __idiv__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Divides the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Divides the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __itruediv__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: DRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: DRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c DRealQuaternion instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DRealQuaternion: pass

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

    def __radd__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c DRealQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c DRealQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

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

    def __rdiv__(t: float) -> ConstDQuaternionExpression: pass

    objectID = property(getObjectID)
