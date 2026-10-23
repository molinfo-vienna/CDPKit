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
# \brief Quaternion expression that exposes a 4-element vector as a quaternion (component indices <em>0-3</em> map to <em>C1-C4</em>).
# 
class ConstLVectorQuaternionAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ConstLVectorQuaternionAdapter instance \a va.
    # \param va The \c ConstLVectorQuaternionAdapter instance to copy.
    # 
    def __init__(va: ConstLVectorQuaternionAdapter) -> None: pass

    ##
    # \brief Constructs the adapter wrapping the 4-element vector <em>v</em>.
    # 
    # \param v The 4-element vector to be viewed as a quaternion.
    # 
    def __init__(v: ConstLVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ConstLVectorQuaternionAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ConstLVectorQuaternionAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the real component <em>C1</em>.
    # 
    # \return The value of <em>C1</em>.
    # 
    def getC1() -> int: pass

    ##
    # \brief Returns the imaginary component <em>C2</em>.
    # 
    # \return The value of <em>C2</em>.
    # 
    def getC2() -> int: pass

    ##
    # \brief Returns the imaginary component <em>C3</em>.
    # 
    # \return The value of <em>C3</em>.
    # 
    def getC3() -> int: pass

    ##
    # \brief Returns the imaginary component <em>C4</em>.
    # 
    # \return The value of <em>C4</em>.
    # 
    def getC4() -> int: pass

    ##
    # \brief Converts the \c ConstLVectorQuaternionAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Returns the wrapped vector.
    # 
    # \return A reference to the wrapped vector closure.
    # 
    def getData() -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == va</tt>.
    # \param va The \c ConstLVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(va: ConstLVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == q</tt>.
    # \param q The \c ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != va</tt>.
    # \param va The \c ConstLVectorQuaternionAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(va: ConstLVectorQuaternionAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != q</tt>.
    # \param q The \c ConstLQuaternionExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(q: ConstLQuaternionExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c ConstLVectorQuaternionAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ConstLVectorQuaternionAdapter: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstLQuaternionExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + t</tt>.
    # \param t Specifies the second addend.
    # \return A \c ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>t + self</tt>.
    # \param t Specifies the first addend.
    # \return A \c ConstLQuaternionExpression instance holding the result of the addition.
    # 
    def __radd__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - t</tt>.
    # \param t Specifies the subtrahend.
    # \return A \c ConstLVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ConstLVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>t - self</tt>.
    # \param t Specifies the minuend.
    # \return A \c ConstLVectorQuaternionAdapter instance holding the result of the subtraction.
    # 
    def __rsub__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstLQuaternionExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // e</tt>.
    # \param e Specifies the divisor.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __div__(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstLQuaternionExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>t // self</tt>.
    # \param t Specifies the dividend.
    # \return A \c ConstLQuaternionExpression instance holding the result of the division.
    # 
    def __rdiv__(t: int) -> ConstLQuaternionExpression: pass

    objectID = property(getObjectID)

    data = property(getData)
