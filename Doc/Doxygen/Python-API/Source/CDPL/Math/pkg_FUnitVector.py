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
class FUnitVector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FUnitVector instance.
    # \param self The \e %FUnitVector instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FUnitVector instance.
    # \param self The \e %FUnitVector instance to initialize.
    # \param v 
    #
    def __init__(self: object, v: FUnitVector) -> None: pass

    ##
    # \brief Initializes the \e %FUnitVector instance.
    # \param self The \e %FUnitVector instance to initialize.
    # \param n 
    # \param i 
    #
    def __init__(self: object, n: int, i: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param n 
    #
    def resize(self: FUnitVector, n: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param arg1 
    # \return 
    #
    def getIndex(arg1: FUnitVector) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FUnitVector instance this method is called upon.
    #
    # Different Python \e %FUnitVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FUnitVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FUnitVector) -> int: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FUnitVector) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return 
    #
    def getSize(self: FUnitVector) -> int: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: FUnitVector, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return 
    #
    def toArray(self: FUnitVector) -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FUnitVector instance \a v.
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param v The \e %FUnitVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FUnitVector, v: FUnitVector) -> FUnitVector: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param v 
    #
    def swap(self: FUnitVector, v: FUnitVector) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param v The \e %FUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FUnitVector, v: FUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param e The \e %FUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FUnitVector, e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param v The \e %FUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FUnitVector, v: FUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param e The \e %FUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FUnitVector, e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: FUnitVector, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: FUnitVector, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return 
    #
    def __len__(self: FUnitVector) -> int: pass

    ##
    # \brief Returns a string representation of the \e %FUnitVector instance.
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FUnitVector) -> str: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return 
    #
    def __pos__(self: FUnitVector) -> FUnitVector: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FUnitVector instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FUnitVector instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FUnitVector instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FUnitVector instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FUnitVector instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FUnitVector instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FUnitVector instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FUnitVector instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FUnitVector instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FUnitVector instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FUnitVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    #
    index = property(getIndex)

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)
