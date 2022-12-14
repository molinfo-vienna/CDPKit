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
class DVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DVectorQuaternionAdapter instance.
    # \param a 
    #
    def __init__(a: DVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Initializes the \e %DVectorQuaternionAdapter instance.
    # \param e 
    #
    def __init__(e: DVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %DVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstFQuaternionExpression instance \a e.
    # \param e The \e %ConstFQuaternionExpression instance to copy.
    # \return \a self
    #
    def assign(e: ConstFQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstDQuaternionExpression instance \a e.
    # \param e The \e %ConstDQuaternionExpression instance to copy.
    # \return \a self
    #
    def assign(e: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstLQuaternionExpression instance \a e.
    # \param e The \e %ConstLQuaternionExpression instance to copy.
    # \return \a self
    #
    def assign(e: ConstLQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstULQuaternionExpression instance \a e.
    # \param e The \e %ConstULQuaternionExpression instance to copy.
    # \return \a self
    #
    def assign(e: ConstULQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorQuaternionAdapter instance \a a.
    # \param a The \e %DVectorQuaternionAdapter instance to copy.
    # \return \a self
    #
    def assign(a: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \return 
    #
    def getC1() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getC2() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getC3() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getC4() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param a 
    #
    def swap(a: DVectorQuaternionAdapter) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC1(v: float) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC2(v: float) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC3(v: float) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC4(v: float) -> None: pass

    ##
    # \brief 
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    #
    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> DVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == a</tt>.
    # \param a The \e %DVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(a: DVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \e %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != a</tt>.
    # \param a The \e %DVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(a: DVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \e %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DVectorQuaternionAdapter instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the addition.
    #
    def __add__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the addition.
    #
    def __add__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __radd__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \e %DVectorQuaternionAdapter instance holding the result of the subtraction.
    #
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %DVectorQuaternionAdapter instance holding the result of the subtraction.
    #
    def __sub__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rsub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the multiplication.
    #
    def __mul__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the division.
    #
    def __div__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param e Specifies the divisor.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the division.
    #
    def __div__(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rdiv__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param t Specifies the second addend.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __iadd__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param a Specifies the second addend.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __iadd__(a: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __iadd__(q: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param t Specifies the subtrahend.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __isub__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param a Specifies the subtrahend.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __isub__(a: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __isub__(q: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __imul__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= a</tt>.
    # \param a Specifies the multiplier.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __imul__(a: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __imul__(q: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __idiv__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= a</tt>.
    # \param a Specifies the divisor.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __idiv__(a: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \e %DVectorQuaternionAdapter instance \a self.
    #
    def __idiv__(q: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> DVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param a 
    # \return 
    #
    def __itruediv__(a: DVectorQuaternionAdapter) -> DVectorQuaternionAdapter: pass

    ##
    # \brief 
    # \param q 
    # \return 
    #
    def __itruediv__(q: ConstDQuaternionExpression) -> DVectorQuaternionAdapter: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    data = property(getData)
