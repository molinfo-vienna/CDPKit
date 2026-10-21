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
class ConstFVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ConstFVectorQuaternionAdapter instance \a a.
    # \param a The \c ConstFVectorQuaternionAdapter instance to copy.
    # 
    def __init__(a: ConstFVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Contructs the \c ConstFVectorQuaternionAdapter instance.
    # \param e 
    # 
    def __init__(e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ConstFVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ConstFVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getC1() -> float: pass

    def getC2() -> float: pass

    def getC3() -> float: pass

    def getC4() -> float: pass

    ##
    # \brief Converts the \c ConstFVectorQuaternionAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    def getData() -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == qa</tt>.
    # \param qa The \c ConstFVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(qa: ConstFVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstFQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstFQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != qa</tt>.
    # \param qa The \c ConstFVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(qa: ConstFVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstFQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstFQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c ConstFVectorQuaternionAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ConstFVectorQuaternionAdapter: pass

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

    ##
    # \brief Returns the result of the addition operation <tt>t + self</tt>.
    # \param t Specifies the first addend.
    # \return A \c ConstFQuaternionExpression instance holding the result of the addition.
    # 
    def __radd__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c ConstFVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(t: float) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ConstFVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>t - self</tt>.
    # \param t Specifies the minuend.
    # \return A \c ConstFVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
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

    ##
    # \brief Returns the result of the division operation <tt>t // self</tt>.
    # \param t Specifies the dividend.
    # \return A \c ConstFQuaternionExpression instance holding the result of the division.
    # 
    def __rdiv__(t: float) -> ConstFQuaternionExpression: pass

    objectID = property(getObjectID)

    data = property(getData)
