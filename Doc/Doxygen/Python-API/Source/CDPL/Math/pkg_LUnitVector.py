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
class LUnitVector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LUnitVector instance.
    # \param self The \e %LUnitVector instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %LUnitVector instance.
    # \param self The \e %LUnitVector instance to initialize.
    # \param v 
    #
    def __init__(self: object, v: LUnitVector) -> None: pass

    ##
    # \brief Initializes the \e %LUnitVector instance.
    # \param self The \e %LUnitVector instance to initialize.
    # \param n 
    # \param i 
    #
    def __init__(self: object, n: int, i: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param n 
    #
    def resize(self: LUnitVector, n: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param arg1 
    # \return 
    #
    def getIndex(arg1: LUnitVector) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LUnitVector instance this method is called upon.
    #
    # Different Python \e %LUnitVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LUnitVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: LUnitVector) -> int: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return 
    #
    def isEmpty(self: LUnitVector) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return 
    #
    def getSize(self: LUnitVector) -> int: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: LUnitVector, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return 
    #
    def toArray(self: LUnitVector) -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LUnitVector instance \a v.
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param v The \e %LUnitVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LUnitVector, v: LUnitVector) -> LUnitVector: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param v 
    #
    def swap(self: LUnitVector, v: LUnitVector) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param v The \e %LUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LUnitVector, v: LUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param e The \e %LUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LUnitVector, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param v The \e %LUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LUnitVector, v: LUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param e The \e %LUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LUnitVector, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: LUnitVector, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: LUnitVector, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return 
    #
    def __len__(self: LUnitVector) -> int: pass

    ##
    # \brief Returns a string representation of the \e %LUnitVector instance.
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: LUnitVector) -> str: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return 
    #
    def __pos__(self: LUnitVector) -> LUnitVector: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LUnitVector instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %LUnitVector instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LUnitVector instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LUnitVector instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LUnitVector instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %LUnitVector instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LUnitVector instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LUnitVector instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LUnitVector instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %LUnitVector instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LUnitVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstLVectorExpression: pass

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
