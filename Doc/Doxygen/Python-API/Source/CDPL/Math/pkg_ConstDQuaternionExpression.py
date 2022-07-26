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
    def getObjectID(self: ConstDQuaternionExpression) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def getC1(self: ConstDQuaternionExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def getC2(self: ConstDQuaternionExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def getC3(self: ConstDQuaternionExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def getC4(self: ConstDQuaternionExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def toArray(self: ConstDQuaternionExpression) -> object: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param e The \e %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ConstDQuaternionExpression, e: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param e The \e %ConstDQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ConstDQuaternionExpression, e: ConstDQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ConstDQuaternionExpression instance.
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ConstDQuaternionExpression) -> str: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def __pos__(self: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param self The \e %ConstDQuaternionExpression instance representing the first addend.
    # \param t Specifies the second addend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the addition.
    #
    def __add__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __radd__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as minuend.
    # \param t Specifies the subtrahend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the subtraction.
    #
    def __sub__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rsub__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / e</tt>.
    # \param self The \e %ConstDQuaternionExpression instance acting as dividend.
    # \param e Specifies the divisor.
    # \return A \e %ConstDQuaternionExpression instance holding the result of the division.
    #
    def __div__(self: object, e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rdiv__(self: object, t: float) -> ConstDQuaternionExpression: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
