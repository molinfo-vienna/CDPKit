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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DRealQuaternion instance.
    # \param q 
    #
    def __init__(q: DRealQuaternion) -> None: pass

    ##
    # \brief Initializes the \e %DRealQuaternion instance.
    # \param r 
    #
    def __init__(r: float) -> None: pass

    ##
    # \brief 
    # \param r 
    # \return 
    #
    def set(r: float = 0.0) -> DRealQuaternion: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %DRealQuaternion instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DRealQuaternion instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRealQuaternion instance \a q.
    # \param q The \e %DRealQuaternion instance to copy.
    # \return The assignment target \a self.
    #
    def assign(q: DRealQuaternion) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param q 
    #
    def swap(q: DRealQuaternion) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param t Specifies the second addend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __iadd__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __iadd__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param t Specifies the subtrahend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __isub__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __isub__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __imul__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __imul__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __idiv__(t: float) -> DRealQuaternion: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \e %DRealQuaternion instance \a self.
    #
    def __idiv__(q: object) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> DRealQuaternion: pass

    ##
    # \brief 
    # \param q 
    # \return 
    #
    def __itruediv__(q: object) -> DRealQuaternion: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(q: DRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(q: DRealQuaternion) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \e %DRealQuaternion instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(q: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DRealQuaternion instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DRealQuaternion: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \e %DRealQuaternion instance holding the result of the addition.
    #
    def __add__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %DRealQuaternion instance holding the result of the addition.
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
    # \return A \e %DRealQuaternion instance holding the result of the subtraction.
    #
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %DRealQuaternion instance holding the result of the subtraction.
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
    # \return A \e %DRealQuaternion instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %DRealQuaternion instance holding the result of the multiplication.
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
    # \return A \e %DRealQuaternion instance holding the result of the division.
    #
    def __div__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param e Specifies the divisor.
    # \return A \e %DRealQuaternion instance holding the result of the division.
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
    # \brief 
    #
    objectID = property(getObjectID)
