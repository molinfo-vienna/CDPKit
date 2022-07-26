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
class FVectorRange(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FVectorRange instance.
    # \param self The \e %FVectorRange instance to initialize.
    # \param r 
    #
    def __init__(self: object, r: FVectorRange) -> None: pass

    ##
    # \brief Initializes the \e %FVectorRange instance.
    # \param self The \e %FVectorRange instance to initialize.
    # \param e 
    # \param r 
    #
    def __init__(self: object, e: FVectorExpression, r: Range) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def getStart(self: FVectorRange) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FVectorRange instance this method is called upon.
    #
    # Different Python \e %FVectorRange instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FVectorRange instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FVectorRange) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorRange instance \a e.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param e The \e %FVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorRange, e: ConstFVectorExpression) -> FVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorRange instance \a e.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param e The \e %FVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorRange, e: ConstDVectorExpression) -> FVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorRange instance \a e.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param e The \e %FVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorRange, e: ConstLVectorExpression) -> FVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorRange instance \a e.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param e The \e %FVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorRange, e: ConstULVectorExpression) -> FVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorRange instance \a r.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param r The \e %FVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorRange, r: FVectorRange) -> FVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorRange instance \a a.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param a The \e %FVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorRange, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FVectorRange) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def getSize(self: FVectorRange) -> int: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: FVectorRange, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def toArray(self: FVectorRange) -> object: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param r 
    #
    def swap(self: FVectorRange, r: FVectorRange) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: FVectorRange, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def getData(self: FVectorRange) -> FVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param r The \e %FVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FVectorRange, r: FVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param e The \e %FVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FVectorRange, e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param r The \e %FVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FVectorRange, r: FVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param e The \e %FVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FVectorRange, e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: FVectorRange, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: FVectorRange, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def __len__(self: FVectorRange) -> int: pass

    ##
    # \brief Returns a string representation of the \e %FVectorRange instance.
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FVectorRange) -> str: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def __pos__(self: FVectorRange) -> FVectorRange: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FVectorRange instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FVectorRange instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FVectorRange instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FVectorRange instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FVectorRange instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FVectorRange instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FVectorRange instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FVectorRange instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FVectorRange instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FVectorRange instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: FVectorRange, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += r</tt>.
    # \param self The \e %FVectorRange instance acting as in-place addend.
    # \param r Specifies the second addend.
    # \return The updated \e %FVectorRange instance \a self.
    #
    def __iadd__(self: FVectorRange, r: FVectorRange) -> FVectorRange: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FVectorRange instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FVectorRange instance \a self.
    #
    def __iadd__(self: FVectorRange, e: ConstFVectorExpression) -> FVectorRange: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= r</tt>.
    # \param self The \e %FVectorRange instance acting as in-place minuend.
    # \param r Specifies the subtrahend.
    # \return The updated \e %FVectorRange instance \a self.
    #
    def __isub__(self: FVectorRange, r: FVectorRange) -> FVectorRange: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FVectorRange instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FVectorRange instance \a self.
    #
    def __isub__(self: FVectorRange, e: ConstFVectorExpression) -> FVectorRange: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FVectorRange instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FVectorRange instance \a self.
    #
    def __imul__(self: FVectorRange, t: float) -> FVectorRange: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FVectorRange instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FVectorRange instance \a self.
    #
    def __idiv__(self: FVectorRange, t: float) -> FVectorRange: pass

    ##
    # \brief 
    # \param self The \e %FVectorRange instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FVectorRange, t: float) -> FVectorRange: pass

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
    start = property(getStart)
