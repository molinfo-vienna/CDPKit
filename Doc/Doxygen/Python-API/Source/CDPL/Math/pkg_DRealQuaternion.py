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
class DRealQuaternion(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DRealQuaternion instance.
    # \param self The \e %DRealQuaternion instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DRealQuaternion instance.
    # \param self The \e %DRealQuaternion instance to initialize.
    # \param q 
    #
    def __init__(self: object, q: DRealQuaternion) -> None: pass

    ##
    # \brief Initializes the \e %DRealQuaternion instance.
    # \param self The \e %DRealQuaternion instance to initialize.
    # \param r 
    #
    def __init__(self: object, r: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param r 
    # \return 
    #
    def set(self: DRealQuaternion, r: float = 0.0) -> DRealQuaternion: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    #
    # Different Python \e %DRealQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DRealQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DRealQuaternion) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC1(self: DRealQuaternion) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC2(self: DRealQuaternion) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC3(self: DRealQuaternion) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def getC4(self: DRealQuaternion) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def toArray(self: DRealQuaternion) -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRealQuaternion instance \a q.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q The \e %DRealQuaternion instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRealQuaternion, q: DRealQuaternion) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q 
    #
    def swap(self: DRealQuaternion, q: DRealQuaternion) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place addend.
    # \param t Specifies the second addend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __iadd__(self: DRealQuaternion, t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __iadd__(self: DRealQuaternion, q: object) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place minuend.
    # \param t Specifies the subtrahend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __isub__(self: DRealQuaternion, t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __isub__(self: DRealQuaternion, q: object) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __imul__(self: DRealQuaternion, t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __imul__(self: DRealQuaternion, q: object) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __idiv__(self: DRealQuaternion, t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %DRealQuaternion instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __idiv__(self: DRealQuaternion, q: object) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DRealQuaternion, t: float) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q 
    # \return 
    #
    def __itruediv__(self: DRealQuaternion, q: object) -> DRealQuaternion: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DRealQuaternion, q: DRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DRealQuaternion, q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DRealQuaternion, q: DRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DRealQuaternion, q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DRealQuaternion instance.
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DRealQuaternion) -> str: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def __pos__(self: DRealQuaternion) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param self The \e %DRealQuaternion instance representing the first addend.
    # \param t Specifies the second addend.
    # \return A \e %DRealQuaternion instance holding the result of the addition.
    #
    def __add__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DRealQuaternion instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %DRealQuaternion instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __radd__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param self The \e %DRealQuaternion instance acting as minuend.
    # \param t Specifies the subtrahend.
    # \return A \e %DRealQuaternion instance holding the result of the subtraction.
    #
    def __sub__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DRealQuaternion instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DRealQuaternion instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rsub__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DRealQuaternion instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %DRealQuaternion instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %DRealQuaternion instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %DRealQuaternion instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DRealQuaternion instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %DRealQuaternion instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param self The \e %DRealQuaternion instance acting as dividend.
    # \param e Specifies the divisor.
    # \return A \e %DRealQuaternion instance holding the result of the division.
    #
    def __div__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DRealQuaternion instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rdiv__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
