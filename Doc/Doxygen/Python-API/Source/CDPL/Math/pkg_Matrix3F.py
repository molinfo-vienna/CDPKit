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
class Matrix3F(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param self The \e %Matrix3F instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param self The \e %Matrix3F instance to initialize.
    # \param v 
    #
    def __init__(self: object, v: float) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param self The \e %Matrix3F instance to initialize.
    # \param m 
    #
    def __init__(self: object, m: Matrix3F) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param arg1 The \e %Matrix3F instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param arg1 The \e %Matrix3F instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstDMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param arg1 The \e %Matrix3F instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstLMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param arg1 The \e %Matrix3F instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstULMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3F instance.
    # \param arg1 The \e %Matrix3F instance to initialize.
    # \param a 
    #
    def __init__(arg1: object, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param v 
    #
    def clear(self: Matrix3F, v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Matrix3F instance this method is called upon.
    #
    # Different Python \e %Matrix3F instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Matrix3F instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Matrix3F) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3F instance \a e.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param e The \e %Matrix3F instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Matrix3F, e: ConstFMatrixExpression) -> Matrix3F: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3F instance \a e.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param e The \e %Matrix3F instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Matrix3F, e: ConstDMatrixExpression) -> Matrix3F: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3F instance \a e.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param e The \e %Matrix3F instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Matrix3F, e: ConstLMatrixExpression) -> Matrix3F: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3F instance \a e.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param e The \e %Matrix3F instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Matrix3F, e: ConstULMatrixExpression) -> Matrix3F: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3F instance \a m.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param m The \e %Matrix3F instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Matrix3F, m: Matrix3F) -> Matrix3F: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3F instance \a a.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param a The \e %Matrix3F instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Matrix3F, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def getSize1(self: Matrix3F) -> int: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def getSize2(self: Matrix3F) -> int: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def isEmpty(self: Matrix3F) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: Matrix3F, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def toArray(self: Matrix3F) -> object: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param m 
    #
    def swap(self: Matrix3F, m: Matrix3F) -> None: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: Matrix3F, i: int, j: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: Matrix3F, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: Matrix3F, ij: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def __len__(self: Matrix3F) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param m The \e %Matrix3F instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Matrix3F, m: Matrix3F) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param e The \e %Matrix3F instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Matrix3F, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param m The \e %Matrix3F instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Matrix3F, m: Matrix3F) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param e The \e %Matrix3F instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Matrix3F, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Matrix3F instance.
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: Matrix3F) -> str: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def __pos__(self: Matrix3F) -> Matrix3F: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %Matrix3F instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %Matrix3F instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %Matrix3F instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %Matrix3F instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %Matrix3F instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %Matrix3F instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %Matrix3F instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %Matrix3F instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %Matrix3F instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %Matrix3F instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %Matrix3F instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %Matrix3F instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: Matrix3F, ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += m</tt>.
    # \param self The \e %Matrix3F instance acting as in-place addend.
    # \param m Specifies the second addend.
    # \return The updated \e %Matrix3F instance \a self.
    #
    def __iadd__(self: Matrix3F, m: Matrix3F) -> Matrix3F: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %Matrix3F instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %Matrix3F instance \a self.
    #
    def __iadd__(self: Matrix3F, e: ConstFMatrixExpression) -> Matrix3F: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= m</tt>.
    # \param self The \e %Matrix3F instance acting as in-place minuend.
    # \param m Specifies the subtrahend.
    # \return The updated \e %Matrix3F instance \a self.
    #
    def __isub__(self: Matrix3F, m: Matrix3F) -> Matrix3F: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %Matrix3F instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %Matrix3F instance \a self.
    #
    def __isub__(self: Matrix3F, e: ConstFMatrixExpression) -> Matrix3F: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %Matrix3F instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %Matrix3F instance \a self.
    #
    def __imul__(self: Matrix3F, t: float) -> Matrix3F: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %Matrix3F instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %Matrix3F instance \a self.
    #
    def __idiv__(self: Matrix3F, t: float) -> Matrix3F: pass

    ##
    # \brief 
    # \param self The \e %Matrix3F instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: Matrix3F, t: float) -> Matrix3F: pass

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
