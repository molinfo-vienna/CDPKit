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
class FMatrixTranspose(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FMatrixTranspose instance.
    # \param self The \e %FMatrixTranspose instance to initialize.
    # \param mt 
    #
    def __init__(self: object, mt: FMatrixTranspose) -> None: pass

    ##
    # \brief Initializes the \e %FMatrixTranspose instance.
    # \param self The \e %FMatrixTranspose instance to initialize.
    # \param e 
    #
    def __init__(self: object, e: FMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    #
    # Different Python \e %FMatrixTranspose instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FMatrixTranspose instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FMatrixTranspose) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixTranspose, e: ConstFMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixTranspose, e: ConstDMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixTranspose, e: ConstLMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixTranspose, e: ConstULMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a mt.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param mt The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixTranspose, mt: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a a.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param a The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixTranspose, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def getSize1(self: FMatrixTranspose) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def getSize2(self: FMatrixTranspose) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FMatrixTranspose) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: FMatrixTranspose, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def toArray(self: FMatrixTranspose) -> object: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param mt 
    #
    def swap(self: FMatrixTranspose, mt: FMatrixTranspose) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: FMatrixTranspose, i: int, j: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def getData(self: FMatrixTranspose) -> FMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: FMatrixTranspose, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: FMatrixTranspose, ij: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def __len__(self: FMatrixTranspose) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == mt</tt>.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param mt The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FMatrixTranspose, mt: FMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param e The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FMatrixTranspose, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mt</tt>.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param mt The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FMatrixTranspose, mt: FMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param e The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FMatrixTranspose, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FMatrixTranspose instance.
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FMatrixTranspose) -> str: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def __pos__(self: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FMatrixTranspose instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FMatrixTranspose instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FMatrixTranspose instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FMatrixTranspose instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FMatrixTranspose instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FMatrixTranspose instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FMatrixTranspose instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FMatrixTranspose instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FMatrixTranspose instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: FMatrixTranspose, ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mt</tt>.
    # \param self The \e %FMatrixTranspose instance acting as in-place addend.
    # \param mt Specifies the second addend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __iadd__(self: FMatrixTranspose, mt: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FMatrixTranspose instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __iadd__(self: FMatrixTranspose, e: ConstFMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= mt</tt>.
    # \param self The \e %FMatrixTranspose instance acting as in-place minuend.
    # \param mt Specifies the subtrahend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __isub__(self: FMatrixTranspose, mt: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FMatrixTranspose instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __isub__(self: FMatrixTranspose, e: ConstFMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FMatrixTranspose instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __imul__(self: FMatrixTranspose, t: float) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FMatrixTranspose instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __idiv__(self: FMatrixTranspose, t: float) -> FMatrixTranspose: pass

    ##
    # \brief 
    # \param self The \e %FMatrixTranspose instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FMatrixTranspose, t: float) -> FMatrixTranspose: pass

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

    ##
    # \brief 
    #
    data = property(getData)
