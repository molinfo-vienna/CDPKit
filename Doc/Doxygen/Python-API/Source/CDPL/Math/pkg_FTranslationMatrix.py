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
class FTranslationMatrix(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FTranslationMatrix instance.
    # \param self The \e %FTranslationMatrix instance to initialize.
    # \param m 
    #
    def __init__(self: object, m: FTranslationMatrix) -> None: pass

    ##
    # \brief Initializes the \e %FTranslationMatrix instance.
    # \param self The \e %FTranslationMatrix instance to initialize.
    # \param n 
    # \param tx 
    # \param ty 
    # \param tz 
    #
    def __init__(self: object, n: int, tx: float = 0.0, ty: float = 0.0, tz: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param tx 
    # \param ty 
    # \param tz 
    #
    def set(self: FTranslationMatrix, tx: float = 0.0, ty: float = 0.0, tz: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param arg1 
    # \param n 
    #
    def resize(arg1: FTranslationMatrix, n: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    #
    # Different Python \e %FTranslationMatrix instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FTranslationMatrix instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FTranslationMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def getSize1(self: FTranslationMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def getSize2(self: FTranslationMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FTranslationMatrix) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: FTranslationMatrix, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def toArray(self: FTranslationMatrix) -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FTranslationMatrix instance \a m.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param m The \e %FTranslationMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FTranslationMatrix, m: FTranslationMatrix) -> FTranslationMatrix: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param m 
    #
    def swap(self: FTranslationMatrix, m: FTranslationMatrix) -> None: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: FTranslationMatrix, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: FTranslationMatrix, ij: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def __len__(self: FTranslationMatrix) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param m The \e %FTranslationMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FTranslationMatrix, m: FTranslationMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param e The \e %FTranslationMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FTranslationMatrix, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param m The \e %FTranslationMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FTranslationMatrix, m: FTranslationMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param e The \e %FTranslationMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FTranslationMatrix, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FTranslationMatrix instance.
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FTranslationMatrix) -> str: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def __pos__(self: FTranslationMatrix) -> FTranslationMatrix: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FTranslationMatrix instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FTranslationMatrix instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FTranslationMatrix instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FTranslationMatrix instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FTranslationMatrix instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FTranslationMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FTranslationMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FTranslationMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FTranslationMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FTranslationMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FTranslationMatrix instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FTranslationMatrix instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FTranslationMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFMatrixExpression: pass

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
