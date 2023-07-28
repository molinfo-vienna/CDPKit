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
class ConstDQuaternionExpression(Boost.Python.instance):

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # 
    # Different Python \e %ConstDQuaternionExpression instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ConstDQuaternionExpression instances \e a and \e b reference different C++ objects. 
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
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param e The \e %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param e The \e %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ConstDQuaternionExpression instance.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param self The \e %ConstDQuaternionExpression instance representing the first addend.
    # \param t Specifies the second addend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance representing the first addend.
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
    # \param self The \e %ConstDQuaternionExpression instance acting as minuend.
    # \param t Specifies the subtrahend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the subtraction.
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
    # \param self The \e %ConstDQuaternionExpression instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as multiplicand.
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
    # \param self The \e %ConstDQuaternionExpression instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as dividend.
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

    objectID = property(getObjectID)
