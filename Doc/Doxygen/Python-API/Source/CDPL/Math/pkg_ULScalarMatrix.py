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
class ULScalarMatrix(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULScalarMatrix instance.
    # \param self The \e %ULScalarMatrix instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ULScalarMatrix instance.
    # \param self The \e %ULScalarMatrix instance to initialize.
    # \param m 
    #
    def __init__(self: object, m: ULScalarMatrix) -> None: pass

    ##
    # \brief Initializes the \e %ULScalarMatrix instance.
    # \param self The \e %ULScalarMatrix instance to initialize.
    # \param m 
    # \param n 
    # \param v 
    #
    def __init__(self: object, m: int, n: int, v: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param m 
    # \param n 
    #
    def resize(self: ULScalarMatrix, m: int, n: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    #
    # Different Python \e %ULScalarMatrix instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULScalarMatrix instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ULScalarMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def getSize1(self: ULScalarMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def getSize2(self: ULScalarMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def isEmpty(self: ULScalarMatrix) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: ULScalarMatrix, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def toArray(self: ULScalarMatrix) -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULScalarMatrix instance \a m.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param m The \e %ULScalarMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULScalarMatrix, m: ULScalarMatrix) -> ULScalarMatrix: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param m 
    #
    def swap(self: ULScalarMatrix, m: ULScalarMatrix) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: ULScalarMatrix, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: ULScalarMatrix, ij: tuple) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def __len__(self: ULScalarMatrix) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param m The \e %ULScalarMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULScalarMatrix, m: ULScalarMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param e The \e %ULScalarMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULScalarMatrix, e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param m The \e %ULScalarMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULScalarMatrix, m: ULScalarMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param e The \e %ULScalarMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULScalarMatrix, e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ULScalarMatrix instance.
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ULScalarMatrix) -> str: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def __pos__(self: ULScalarMatrix) -> ULScalarMatrix: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ULScalarMatrix instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ULScalarMatrix instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ULScalarMatrix instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ULScalarMatrix instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ULScalarMatrix instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ULScalarMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULScalarMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULScalarMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULScalarMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULScalarMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ULScalarMatrix instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ULScalarMatrix instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %ULScalarMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size1 = property(getSize1)

    ##
    # \brief 
    #
    size2 = property(getSize2)
