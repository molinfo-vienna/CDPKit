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
class DRotationMatrix(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DRotationMatrix instance.
    # \param self The \e %DRotationMatrix instance to initialize.
    # \param m 
    # 
    def __init__(m: DRotationMatrix) -> None: pass

    ##
    # \brief Initializes the \e %DRotationMatrix instance.
    # \param self The \e %DRotationMatrix instance to initialize.
    # \param n 
    # \param w 
    # \param ux 
    # \param uy 
    # \param uz 
    # 
    def __init__(n: int, w: float, ux: float, uy: float, uz: float) -> None: pass

    ##
    # \brief 
    # \param w 
    # \param ux 
    # \param uy 
    # \param uz 
    #
    def set(w: float, ux: float, uy: float, uz: float) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # 
    # Different Python \e %DRotationMatrix instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DRotationMatrix instances \e a and \e b reference different C++ objects. 
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
    def getSize1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getSize2() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(i: int, j: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRotationMatrix instance \a m.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # \param m The \e %DRotationMatrix instance to copy.
    # \return \a self
    # 
    def assign(m: DRotationMatrix) -> DRotationMatrix: pass

    ##
    # \brief 
    # \param m 
    #
    def swap(m: DRotationMatrix) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param ij 
    # \return 
    #
    def __getitem__(ij: tuple) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # \param m The \e %DRotationMatrix instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(m: DRotationMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # \param e The \e %ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # \param m The \e %DRotationMatrix instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(m: DRotationMatrix) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # \param e The \e %ConstDMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DRotationMatrix instance.
    # \param self The \e %DRotationMatrix instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DRotationMatrix: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DRotationMatrix instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstDMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DRotationMatrix instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DRotationMatrix instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DRotationMatrix instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %DRotationMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstDMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %DRotationMatrix instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DRotationMatrix instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstDMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstDMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstDMatrixExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)
