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
class ULRealQuaternion(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULRealQuaternion instance.
    # \param self The \e %ULRealQuaternion instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ULRealQuaternion instance.
    # \param self The \e %ULRealQuaternion instance to initialize.
    # \param q 
    #
    def __init__(self: object, q: ULRealQuaternion) -> None: pass

    ##
    # \brief Initializes the \e %ULRealQuaternion instance.
    # \param self The \e %ULRealQuaternion instance to initialize.
    # \param r 
    #
    def __init__(self: object, r: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param r 
    # \return 
    #
    def set(self: ULRealQuaternion, r: int = 0) -> ULRealQuaternion: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    #
    # Different Python \e %ULRealQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULRealQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ULRealQuaternion) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC1(self: ULRealQuaternion) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC2(self: ULRealQuaternion) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC3(self: ULRealQuaternion) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC4(self: ULRealQuaternion) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def toArray(self: ULRealQuaternion) -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULRealQuaternion instance \a q.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q The \e %ULRealQuaternion instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULRealQuaternion, q: ULRealQuaternion) -> ULRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q 
    #
    def swap(self: ULRealQuaternion, q: ULRealQuaternion) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place addend.
    # \param t Specifies the second addend.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __iadd__(self: ULRealQuaternion, t: int) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __iadd__(self: ULRealQuaternion, q: object) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place minuend.
    # \param t Specifies the subtrahend.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __isub__(self: ULRealQuaternion, t: int) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __isub__(self: ULRealQuaternion, q: object) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __imul__(self: ULRealQuaternion, t: int) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __imul__(self: ULRealQuaternion, q: object) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __idiv__(self: ULRealQuaternion, t: int) -> ULRealQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %ULRealQuaternion instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %ULRealQuaternion instance \a self.
    #
    def __idiv__(self: ULRealQuaternion, q: object) -> ULRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: ULRealQuaternion, t: int) -> ULRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q 
    # \return 
    #
    def __itruediv__(self: ULRealQuaternion, q: object) -> ULRealQuaternion: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q The \e %ULRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULRealQuaternion, q: ULRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q The \e %ULRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULRealQuaternion, q: ConstULQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q The \e %ULRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULRealQuaternion, q: ULRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param q The \e %ULRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULRealQuaternion, q: ConstULQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ULRealQuaternion instance.
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ULRealQuaternion) -> str: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def __pos__(self: ULRealQuaternion) -> ULRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param self The \e %ULRealQuaternion instance representing the first addend.
    # \param t Specifies the second addend.
    # \return A \e %ULRealQuaternion instance holding the result of the addition.
    #
    def __add__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ULRealQuaternion instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ULRealQuaternion instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __radd__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as minuend.
    # \param t Specifies the subtrahend.
    # \return A \e %ULRealQuaternion instance holding the result of the subtraction.
    #
    def __sub__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ULRealQuaternion instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ULRealQuaternion instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rsub__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ULRealQuaternion instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULRealQuaternion instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULRealQuaternion instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ULRealQuaternion instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ULRealQuaternion instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param self The \e %ULRealQuaternion instance acting as dividend.
    # \param e Specifies the divisor.
    # \return A \e %ULRealQuaternion instance holding the result of the division.
    #
    def __div__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rdiv__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
