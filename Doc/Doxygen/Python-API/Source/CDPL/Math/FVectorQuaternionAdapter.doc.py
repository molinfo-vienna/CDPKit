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
class FVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c FVectorQuaternionAdapter instance \a a.
    # \param a The \c FVectorQuaternionAdapter instance to copy.
    # 
    def __init__(a: FVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Contructs the \c FVectorQuaternionAdapter instance.
    # \param e 
    # 
    def __init__(e: FVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c ConstFQuaternionExpression instance \a e.
    # \param e The \c ConstFQuaternionExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstFQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c ConstDQuaternionExpression instance \a e.
    # \param e The \c ConstDQuaternionExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstDQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c ConstLQuaternionExpression instance \a e.
    # \param e The \c ConstLQuaternionExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstLQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c ConstULQuaternionExpression instance \a e.
    # \param e The \c ConstULQuaternionExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstULQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c FVectorQuaternionAdapter instance \a a.
    # \param a The \c FVectorQuaternionAdapter instance to copy.
    # \return \a self
    # 
    def assign(a: FVectorQuaternionAdapter) -> FVectorQuaternionAdapter: pass

    def getC1() -> float: pass

    def getC2() -> float: pass

    def getC3() -> float: pass

    def getC4() -> float: pass

    ##
    # \brief Converts the \c FVectorQuaternionAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    def swap(a: FVectorQuaternionAdapter) -> None: pass

    def setC1(v: float) -> None: pass

    def setC2(v: float) -> None: pass

    def setC3(v: float) -> None: pass

    def setC4(v: float) -> None: pass

    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    def getData() -> FVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == a</tt>.
    # \param a The \c FVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(a: FVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstFQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstFQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != a</tt>.
    # \param a The \c FVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(a: FVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstFQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstFQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c FVectorQuaternionAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> FVectorQuaternionAdapter: pass

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

    def __radd__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c FVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c FVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

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

    def __rdiv__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param t Specifies the second addend.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __iadd__(t: float) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param a Specifies the second addend.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __iadd__(a: FVectorQuaternionAdapter) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __iadd__(q: ConstFQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param t Specifies the subtrahend.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __isub__(t: float) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param a Specifies the subtrahend.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __isub__(a: FVectorQuaternionAdapter) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __isub__(q: ConstFQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __imul__(t: float) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= a</tt>.
    # \param a Specifies the multiplier.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __imul__(a: FVectorQuaternionAdapter) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __imul__(q: ConstFQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self //= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __idiv__(t: float) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self //= a</tt>.
    # \param a Specifies the divisor.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __idiv__(a: FVectorQuaternionAdapter) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self //= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __idiv__(q: ConstFQuaternionExpression) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Returns the result of the in-place \e true division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __itruediv__(t: float) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Returns the result of the in-place \e true division operation <tt>self /= a</tt>.
    # \param a Specifies the divisor.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __itruediv__(a: FVectorQuaternionAdapter) -> FVectorQuaternionAdapter: pass

    ##
    # \brief Returns the result of the in-place \e true division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \c FVectorQuaternionAdapter instance \a self.
    # 
    def __itruediv__(q: ConstFQuaternionExpression) -> FVectorQuaternionAdapter: pass

    objectID = property(getObjectID)

    data = property(getData)
