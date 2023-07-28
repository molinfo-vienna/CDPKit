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
# \brief 
#
class LQuaternion(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param self The \e %LQuaternion instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param self The \e %LQuaternion instance to initialize.
    # \param q 
    # 
    def __init__(q: LQuaternion) -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param self The \e %LQuaternion instance to initialize.
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    # 
    def __init__(c1: int, c2: int = 0, c3: int = 0, c4: int = 0) -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param arg1 The \e %LQuaternion instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstFQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param arg1 The \e %LQuaternion instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstDQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param arg1 The \e %LQuaternion instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstLQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param arg1 The \e %LQuaternion instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstULQuaternionExpression) -> None: pass

    ##
    # \brief Initializes the \e %LQuaternion instance.
    # \param arg1 The \e %LQuaternion instance to initialize.
    # \param a 
    # 
    def __init__(a: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LQuaternion instance this method is called upon.
    # 
    # Different Python \e %LQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstFQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstDQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstLQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstULQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief 
    # \param q 
    # \return 
    #
    def assign(q: LQuaternion) -> LQuaternion: pass

    ##
    # \brief 
    # \param a 
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getC1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getC2() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getC3() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getC4() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param q 
    #
    def swap(q: LQuaternion) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC1(v: int) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC2(v: int) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC3(v: int) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC4(v: int) -> None: pass

    ##
    # \brief 
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    #
    def set(c1: int = 0, c2: int = 0, c3: int = 0, c4: int = 0) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %LQuaternion instance this method is called upon.
    # \param q The \e %LQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: LQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param self The \e %LQuaternion instance this method is called upon.
    # \param q The \e %ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %LQuaternion instance this method is called upon.
    # \param q The \e %LQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: LQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param self The \e %LQuaternion instance this method is called upon.
    # \param q The \e %ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LQuaternion instance.
    # \param self The \e %LQuaternion instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> LQuaternion: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param self The \e %LQuaternion instance representing the first addend.
    # \param t Specifies the second addend.
    # \return A \e %ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LQuaternion instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __radd__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param self The \e %LQuaternion instance acting as minuend.
    # \param t Specifies the subtrahend.
    # \return A \e %LQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LQuaternion instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LQuaternion instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rsub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LQuaternion instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LQuaternion instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LQuaternion instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param self The \e %LQuaternion instance acting as dividend.
    # \param e Specifies the divisor.
    # \return A \e %ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rdiv__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param self The \e %LQuaternion instance acting as in-place addend.
    # \param t Specifies the second addend.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __iadd__(t: int) -> LQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __iadd__(q: LQuaternion) -> LQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __iadd__(q: ConstLQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param self The \e %LQuaternion instance acting as in-place minuend.
    # \param t Specifies the subtrahend.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __isub__(t: int) -> LQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __isub__(q: LQuaternion) -> LQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __isub__(q: ConstLQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LQuaternion instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __imul__(t: int) -> LQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __imul__(q: LQuaternion) -> LQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __imul__(q: ConstLQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LQuaternion instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __idiv__(t: int) -> LQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __idiv__(q: LQuaternion) -> LQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %LQuaternion instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %LQuaternion instance \a self.
    # 
    def __idiv__(q: ConstLQuaternionExpression) -> LQuaternion: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> LQuaternion: pass

    ##
    # \brief 
    # \param q 
    # \return 
    #
    def __itruediv__(q: LQuaternion) -> LQuaternion: pass

    ##
    # \brief 
    # \param q 
    # \return 
    #
    def __itruediv__(q: ConstLQuaternionExpression) -> LQuaternion: pass

    objectID = property(getObjectID)
