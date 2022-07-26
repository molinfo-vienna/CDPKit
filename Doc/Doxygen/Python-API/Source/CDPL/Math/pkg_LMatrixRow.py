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
class LMatrixRow(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LMatrixRow instance.
    # \param self The \e %LMatrixRow instance to initialize.
    # \param mr 
    #
    def __init__(self: object, mr: LMatrixRow) -> None: pass

    ##
    # \brief Initializes the \e %LMatrixRow instance.
    # \param self The \e %LMatrixRow instance to initialize.
    # \param e 
    # \param i 
    #
    def __init__(self: object, e: LMatrixExpression, i: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def getIndex(self: LMatrixRow) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LMatrixRow instance this method is called upon.
    #
    # Different Python \e %LMatrixRow instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LMatrixRow instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: LMatrixRow) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixRow instance \a e.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param e The \e %LMatrixRow instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixRow, e: ConstFVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixRow instance \a e.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param e The \e %LMatrixRow instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixRow, e: ConstDVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixRow instance \a e.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param e The \e %LMatrixRow instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixRow, e: ConstLVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixRow instance \a e.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param e The \e %LMatrixRow instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixRow, e: ConstULVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixRow instance \a r.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param r The \e %LMatrixRow instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixRow, r: LMatrixRow) -> LMatrixRow: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixRow instance \a a.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param a The \e %LMatrixRow instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixRow, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def isEmpty(self: LMatrixRow) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def getSize(self: LMatrixRow) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: LMatrixRow, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def toArray(self: LMatrixRow) -> object: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param r 
    #
    def swap(self: LMatrixRow, r: LMatrixRow) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: LMatrixRow, i: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def getData(self: LMatrixRow) -> LMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param r The \e %LMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LMatrixRow, r: LMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param e The \e %LMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LMatrixRow, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param r The \e %LMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LMatrixRow, r: LMatrixRow) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param e The \e %LMatrixRow instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LMatrixRow, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: LMatrixRow, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: LMatrixRow, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def __len__(self: LMatrixRow) -> int: pass

    ##
    # \brief Returns a string representation of the \e %LMatrixRow instance.
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: LMatrixRow) -> str: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def __pos__(self: LMatrixRow) -> LMatrixRow: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LMatrixRow instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %LMatrixRow instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LMatrixRow instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LMatrixRow instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LMatrixRow instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %LMatrixRow instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrixRow instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LMatrixRow instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LMatrixRow instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %LMatrixRow instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: LMatrixRow, i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += r</tt>.
    # \param self The \e %LMatrixRow instance acting as in-place addend.
    # \param r Specifies the second addend.
    # \return The updated \e %LMatrixRow instance \a self.
    #
    def __iadd__(self: LMatrixRow, r: LMatrixRow) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LMatrixRow instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LMatrixRow instance \a self.
    #
    def __iadd__(self: LMatrixRow, e: ConstLVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= r</tt>.
    # \param self The \e %LMatrixRow instance acting as in-place minuend.
    # \param r Specifies the subtrahend.
    # \return The updated \e %LMatrixRow instance \a self.
    #
    def __isub__(self: LMatrixRow, r: LMatrixRow) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LMatrixRow instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LMatrixRow instance \a self.
    #
    def __isub__(self: LMatrixRow, e: ConstLVectorExpression) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LMatrixRow instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LMatrixRow instance \a self.
    #
    def __imul__(self: LMatrixRow, t: int) -> LMatrixRow: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LMatrixRow instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LMatrixRow instance \a self.
    #
    def __idiv__(self: LMatrixRow, t: int) -> LMatrixRow: pass

    ##
    # \brief 
    # \param self The \e %LMatrixRow instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: LMatrixRow, t: int) -> LMatrixRow: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)

    ##
    # \brief 
    #
    data = property(getData)

    ##
    # \brief 
    #
    index = property(getIndex)
