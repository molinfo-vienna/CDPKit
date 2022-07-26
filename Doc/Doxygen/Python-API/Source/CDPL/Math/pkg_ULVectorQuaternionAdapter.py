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
class ULVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULVectorQuaternionAdapter instance.
    # \param self The \e %ULVectorQuaternionAdapter instance to initialize.
    # \param a 
    #
    def __init__(self: object, a: ULVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Initializes the \e %ULVectorQuaternionAdapter instance.
    # \param self The \e %ULVectorQuaternionAdapter instance to initialize.
    # \param e 
    #
    def __init__(self: object, e: ULVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    #
    # Different Python \e %ULVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ULVectorQuaternionAdapter) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorQuaternionAdapter instance \a e.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param e The \e %ULVectorQuaternionAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorQuaternionAdapter, e: ConstFQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorQuaternionAdapter instance \a e.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param e The \e %ULVectorQuaternionAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorQuaternionAdapter, e: ConstDQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorQuaternionAdapter instance \a e.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param e The \e %ULVectorQuaternionAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorQuaternionAdapter, e: ConstLQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorQuaternionAdapter instance \a e.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param e The \e %ULVectorQuaternionAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorQuaternionAdapter, e: ConstULQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorQuaternionAdapter instance \a a.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param a The \e %ULVectorQuaternionAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def getC1(self: ULVectorQuaternionAdapter) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def getC2(self: ULVectorQuaternionAdapter) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def getC3(self: ULVectorQuaternionAdapter) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def getC4(self: ULVectorQuaternionAdapter) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def toArray(self: ULVectorQuaternionAdapter) -> object: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param a 
    #
    def swap(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param v 
    #
    def setC1(self: ULVectorQuaternionAdapter, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param v 
    #
    def setC2(self: ULVectorQuaternionAdapter, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param v 
    #
    def setC3(self: ULVectorQuaternionAdapter, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param v 
    #
    def setC4(self: ULVectorQuaternionAdapter, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    #
    def set(self: ULVectorQuaternionAdapter, c1: int = 0, c2: int = 0, c3: int = 0, c4: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def getData(self: ULVectorQuaternionAdapter) -> ULVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == a</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param a The \e %ULVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param q The \e %ULVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != a</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param a The \e %ULVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param q The \e %ULVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ULVectorQuaternionAdapter instance.
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ULVectorQuaternionAdapter) -> str: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def __pos__(self: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance representing the first addend.
    # \param t Specifies the second addend.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the addition.
    #
    def __add__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __radd__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as minuend.
    # \param t Specifies the subtrahend.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the subtraction.
    #
    def __sub__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rsub__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as dividend.
    # \param e Specifies the divisor.
    # \return A \e %ULVectorQuaternionAdapter instance holding the result of the division.
    #
    def __div__(self: object, e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rdiv__(self: object, t: int) -> ConstULQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place addend.
    # \param t Specifies the second addend.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __iadd__(self: ULVectorQuaternionAdapter, t: int) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place addend.
    # \param a Specifies the second addend.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __iadd__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __iadd__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place minuend.
    # \param t Specifies the subtrahend.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __isub__(self: ULVectorQuaternionAdapter, t: int) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place minuend.
    # \param a Specifies the subtrahend.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __isub__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __isub__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __imul__(self: ULVectorQuaternionAdapter, t: int) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= a</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place multiplicand.
    # \param a Specifies the multiplier.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __imul__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __imul__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __idiv__(self: ULVectorQuaternionAdapter, t: int) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= a</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place dividend.
    # \param a Specifies the divisor.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __idiv__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %ULVectorQuaternionAdapter instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %ULVectorQuaternionAdapter instance \a self.
    #
    def __idiv__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: ULVectorQuaternionAdapter, t: int) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param a 
    # \return 
    #
    def __itruediv__(self: ULVectorQuaternionAdapter, a: ULVectorQuaternionAdapter) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULVectorQuaternionAdapter instance this method is called upon.
    # \param q 
    # \return 
    #
    def __itruediv__(self: ULVectorQuaternionAdapter, q: ConstULQuaternionExpression) -> ULVectorQuaternionAdapter: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    data = property(getData)
