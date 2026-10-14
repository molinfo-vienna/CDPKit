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
# \brief A memory-efficient pure-real quaternion with component values of type <tt>long</tt>.
# 
class LRealQuaternion(Boost.Python.instance):

    ##
    # \brief Constructs a zero-valued real quaternion (<em>C1</em> = 0).
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the real quaternion <em>q</em> (possibly converting the component type).
    # 
    # \param q The real quaternion to copy.
    # 
    def __init__(q: LRealQuaternion) -> None: pass

    ##
    # \brief Constructs the real quaternion with the supplied real component.
    # 
    # \param r The real component value.
    # 
    def __init__(r: int) -> None: pass

    def set(r: int = 0) -> LRealQuaternion: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c LRealQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c LRealQuaternion instances \e a and \e b reference different C++ objects. 
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
    def getC1() -> int: pass

    ##
    # \brief Returns the imaginary component <em>C2</em> (always zero for a real quaternion).
    # 
    # \return A reference to the zero element.
    # 
    def getC2() -> int: pass

    ##
    # \brief Returns the imaginary component <em>C3</em> (always zero for a real quaternion).
    # 
    # \return A reference to the zero element.
    # 
    def getC3() -> int: pass

    ##
    # \brief Returns the imaginary component <em>C4</em> (always zero for a real quaternion).
    # 
    # \return A reference to the zero element.
    # 
    def getC4() -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Assigns the real component from <em>q</em> without intermediate temporary.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def assign(q: LRealQuaternion) -> LRealQuaternion: pass

    ##
    # \brief Swaps the real component value with <em>q</em>.
    # 
    # \param q The real quaternion to swap with.
    # 
    def swap(q: LRealQuaternion) -> None: pass

    ##
    # \brief Adds the scalar <em>t</em> to the real component.
    # 
    # \param t The scalar addend.
    # 
    # \return \a self.
    # 
    def __iadd__(t: int) -> LRealQuaternion: pass

    ##
    # \brief Adds the real component of <em>q</em> to this quaternion's real component.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __iadd__(q: object) -> LRealQuaternion: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from the real component.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self.
    # 
    def __isub__(t: int) -> LRealQuaternion: pass

    ##
    # \brief Subtracts the real component of <em>q</em> from this quaternion's real component.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __isub__(q: object) -> LRealQuaternion: pass

    ##
    # \brief Multiplies the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: int) -> LRealQuaternion: pass

    ##
    # \brief Multiplies the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __imul__(q: object) -> LRealQuaternion: pass

    ##
    # \brief Divides the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: int) -> LRealQuaternion: pass

    ##
    # \brief Divides the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __idiv__(q: object) -> LRealQuaternion: pass

    ##
    # \brief Divides the real component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: int) -> LRealQuaternion: pass

    ##
    # \brief Divides the real component by the real component of <em>q</em>.
    # 
    # \param q The source real quaternion.
    # 
    # \return \a self.
    # 
    def __itruediv__(q: object) -> LRealQuaternion: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c LRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: LRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c LRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: LRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c LRealQuaternion instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> LRealQuaternion: pass

    ##
    # \brief Negates each element and returns the result.
    # \return A \c ConstLQuaternionExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    def __radd__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c LRealQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c LRealQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    def __rsub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstLQuaternionExpression: pass

    def __rdiv__(t: int) -> ConstLQuaternionExpression: pass

    objectID = property(getObjectID)
