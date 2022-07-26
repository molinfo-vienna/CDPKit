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
class LMatrix(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param self The \e %LMatrix instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param self The \e %LMatrix instance to initialize.
    # \param m 
    #
    def __init__(self: object, m: LMatrix) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param self The \e %LMatrix instance to initialize.
    # \param m 
    # \param n 
    #
    def __init__(self: object, m: int, n: int) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param self The \e %LMatrix instance to initialize.
    # \param m 
    # \param n 
    # \param v 
    #
    def __init__(self: object, m: int, n: int, v: int) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param arg1 The \e %LMatrix instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param arg1 The \e %LMatrix instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstDMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param arg1 The \e %LMatrix instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstLMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param arg1 The \e %LMatrix instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstULMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %LMatrix instance.
    # \param arg1 The \e %LMatrix instance to initialize.
    # \param a 
    #
    def __init__(arg1: object, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param m 
    # \param n 
    # \param preserve 
    # \param v 
    #
    def resize(self: LMatrix, m: int, n: int, preserve: bool = True, v: int = 0) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param v 
    #
    def clear(self: LMatrix, v: int = 0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LMatrix instance this method is called upon.
    #
    # Different Python \e %LMatrix instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LMatrix instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: LMatrix) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrix instance \a e.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param e The \e %LMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrix, e: ConstFMatrixExpression) -> LMatrix: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrix instance \a e.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param e The \e %LMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrix, e: ConstDMatrixExpression) -> LMatrix: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrix instance \a e.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param e The \e %LMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrix, e: ConstLMatrixExpression) -> LMatrix: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrix instance \a e.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param e The \e %LMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrix, e: ConstULMatrixExpression) -> LMatrix: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrix instance \a m.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param m The \e %LMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrix, m: LMatrix) -> LMatrix: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrix instance \a a.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param a The \e %LMatrix instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrix, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def getSize1(self: LMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def getSize2(self: LMatrix) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def isEmpty(self: LMatrix) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: LMatrix, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def toArray(self: LMatrix) -> object: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param m 
    #
    def swap(self: LMatrix, m: LMatrix) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: LMatrix, i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: LMatrix, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: LMatrix, ij: tuple) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def __len__(self: LMatrix) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param m The \e %LMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LMatrix, m: LMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param e The \e %LMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LMatrix, e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param m The \e %LMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LMatrix, m: LMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %LMatrix instance this method is called upon.
    # \param e The \e %LMatrix instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LMatrix, e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LMatrix instance.
    # \param self The \e %LMatrix instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: LMatrix) -> str: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def __pos__(self: LMatrix) -> LMatrix: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LMatrix instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %LMatrix instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LMatrix instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LMatrix instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LMatrix instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %LMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LMatrix instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LMatrix instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %LMatrix instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: LMatrix, ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += m</tt>.
    # \param self The \e %LMatrix instance acting as in-place addend.
    # \param m Specifies the second addend.
    # \return The updated \e %LMatrix instance \a self.
    #
    def __iadd__(self: LMatrix, m: LMatrix) -> LMatrix: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LMatrix instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LMatrix instance \a self.
    #
    def __iadd__(self: LMatrix, e: ConstLMatrixExpression) -> LMatrix: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= m</tt>.
    # \param self The \e %LMatrix instance acting as in-place minuend.
    # \param m Specifies the subtrahend.
    # \return The updated \e %LMatrix instance \a self.
    #
    def __isub__(self: LMatrix, m: LMatrix) -> LMatrix: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LMatrix instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LMatrix instance \a self.
    #
    def __isub__(self: LMatrix, e: ConstLMatrixExpression) -> LMatrix: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LMatrix instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LMatrix instance \a self.
    #
    def __imul__(self: LMatrix, t: int) -> LMatrix: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LMatrix instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LMatrix instance \a self.
    #
    def __idiv__(self: LMatrix, t: int) -> LMatrix: pass

    ##
    # \brief 
    # \param self The \e %LMatrix instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: LMatrix, t: int) -> LMatrix: pass

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
