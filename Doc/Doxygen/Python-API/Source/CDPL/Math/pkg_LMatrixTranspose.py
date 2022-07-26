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
class LMatrixTranspose(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LMatrixTranspose instance.
    # \param self The \e %LMatrixTranspose instance to initialize.
    # \param mt 
    #
    def __init__(self: object, mt: LMatrixTranspose) -> None: pass

    ##
    # \brief Initializes the \e %LMatrixTranspose instance.
    # \param self The \e %LMatrixTranspose instance to initialize.
    # \param e 
    #
    def __init__(self: object, e: LMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    #
    # Different Python \e %LMatrixTranspose instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LMatrixTranspose instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: LMatrixTranspose) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixTranspose instance \a e.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param e The \e %LMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixTranspose, e: ConstFMatrixExpression) -> LMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixTranspose instance \a e.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param e The \e %LMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixTranspose, e: ConstDMatrixExpression) -> LMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixTranspose instance \a e.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param e The \e %LMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixTranspose, e: ConstLMatrixExpression) -> LMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixTranspose instance \a e.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param e The \e %LMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixTranspose, e: ConstULMatrixExpression) -> LMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixTranspose instance \a mt.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param mt The \e %LMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixTranspose, mt: LMatrixTranspose) -> LMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixTranspose instance \a a.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param a The \e %LMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixTranspose, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def getSize1(self: LMatrixTranspose) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def getSize2(self: LMatrixTranspose) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def isEmpty(self: LMatrixTranspose) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: LMatrixTranspose, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def toArray(self: LMatrixTranspose) -> object: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param mt 
    #
    def swap(self: LMatrixTranspose, mt: LMatrixTranspose) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: LMatrixTranspose, i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def getData(self: LMatrixTranspose) -> LMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: LMatrixTranspose, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: LMatrixTranspose, ij: tuple) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def __len__(self: LMatrixTranspose) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == mt</tt>.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param mt The \e %LMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LMatrixTranspose, mt: LMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param e The \e %LMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LMatrixTranspose, e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mt</tt>.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param mt The \e %LMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LMatrixTranspose, mt: LMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param e The \e %LMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LMatrixTranspose, e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LMatrixTranspose instance.
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: LMatrixTranspose) -> str: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def __pos__(self: LMatrixTranspose) -> LMatrixTranspose: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LMatrixTranspose instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %LMatrixTranspose instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LMatrixTranspose instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LMatrixTranspose instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LMatrixTranspose instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %LMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrixTranspose instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrixTranspose instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LMatrixTranspose instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %LMatrixTranspose instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: LMatrixTranspose, ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mt</tt>.
    # \param self The \e %LMatrixTranspose instance acting as in-place addend.
    # \param mt Specifies the second addend.
    # \return The updated \e %LMatrixTranspose instance \a self.
    #
    def __iadd__(self: LMatrixTranspose, mt: LMatrixTranspose) -> LMatrixTranspose: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LMatrixTranspose instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LMatrixTranspose instance \a self.
    #
    def __iadd__(self: LMatrixTranspose, e: ConstLMatrixExpression) -> LMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= mt</tt>.
    # \param self The \e %LMatrixTranspose instance acting as in-place minuend.
    # \param mt Specifies the subtrahend.
    # \return The updated \e %LMatrixTranspose instance \a self.
    #
    def __isub__(self: LMatrixTranspose, mt: LMatrixTranspose) -> LMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LMatrixTranspose instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LMatrixTranspose instance \a self.
    #
    def __isub__(self: LMatrixTranspose, e: ConstLMatrixExpression) -> LMatrixTranspose: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LMatrixTranspose instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LMatrixTranspose instance \a self.
    #
    def __imul__(self: LMatrixTranspose, t: int) -> LMatrixTranspose: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LMatrixTranspose instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LMatrixTranspose instance \a self.
    #
    def __idiv__(self: LMatrixTranspose, t: int) -> LMatrixTranspose: pass

    ##
    # \brief 
    # \param self The \e %LMatrixTranspose instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: LMatrixTranspose, t: int) -> LMatrixTranspose: pass

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
