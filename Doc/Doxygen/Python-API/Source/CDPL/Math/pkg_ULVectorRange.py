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
class ULVectorRange(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULVectorRange instance.
    # \param self The \e %ULVectorRange instance to initialize.
    # \param r 
    #
    def __init__(self: object, r: ULVectorRange) -> None: pass

    ##
    # \brief Initializes the \e %ULVectorRange instance.
    # \param self The \e %ULVectorRange instance to initialize.
    # \param e 
    # \param r 
    #
    def __init__(self: object, e: ULVectorExpression, r: Range) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def getStart(self: ULVectorRange) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ULVectorRange instance this method is called upon.
    #
    # Different Python \e %ULVectorRange instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULVectorRange instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ULVectorRange) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorRange instance \a e.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param e The \e %ULVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorRange, e: ConstFVectorExpression) -> ULVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorRange instance \a e.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param e The \e %ULVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorRange, e: ConstDVectorExpression) -> ULVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorRange instance \a e.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param e The \e %ULVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorRange, e: ConstLVectorExpression) -> ULVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorRange instance \a e.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param e The \e %ULVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorRange, e: ConstULVectorExpression) -> ULVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorRange instance \a r.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param r The \e %ULVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorRange, r: ULVectorRange) -> ULVectorRange: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorRange instance \a a.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param a The \e %ULVectorRange instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULVectorRange, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def isEmpty(self: ULVectorRange) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def getSize(self: ULVectorRange) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: ULVectorRange, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def toArray(self: ULVectorRange) -> object: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param r 
    #
    def swap(self: ULVectorRange, r: ULVectorRange) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: ULVectorRange, i: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def getData(self: ULVectorRange) -> ULVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param r The \e %ULVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULVectorRange, r: ULVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param e The \e %ULVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULVectorRange, e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param r The \e %ULVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULVectorRange, r: ULVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param e The \e %ULVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULVectorRange, e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: ULVectorRange, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: ULVectorRange, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def __len__(self: ULVectorRange) -> int: pass

    ##
    # \brief Returns a string representation of the \e %ULVectorRange instance.
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ULVectorRange) -> str: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def __pos__(self: ULVectorRange) -> ULVectorRange: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ULVectorRange instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ULVectorRange instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ULVectorRange instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ULVectorRange instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ULVectorRange instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ULVectorRange instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULVectorRange instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULVectorRange instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ULVectorRange instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ULVectorRange instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: ULVectorRange, i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += r</tt>.
    # \param self The \e %ULVectorRange instance acting as in-place addend.
    # \param r Specifies the second addend.
    # \return The updated \e %ULVectorRange instance \a self.
    #
    def __iadd__(self: ULVectorRange, r: ULVectorRange) -> ULVectorRange: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %ULVectorRange instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %ULVectorRange instance \a self.
    #
    def __iadd__(self: ULVectorRange, e: ConstULVectorExpression) -> ULVectorRange: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= r</tt>.
    # \param self The \e %ULVectorRange instance acting as in-place minuend.
    # \param r Specifies the subtrahend.
    # \return The updated \e %ULVectorRange instance \a self.
    #
    def __isub__(self: ULVectorRange, r: ULVectorRange) -> ULVectorRange: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %ULVectorRange instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %ULVectorRange instance \a self.
    #
    def __isub__(self: ULVectorRange, e: ConstULVectorExpression) -> ULVectorRange: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %ULVectorRange instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %ULVectorRange instance \a self.
    #
    def __imul__(self: ULVectorRange, t: int) -> ULVectorRange: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %ULVectorRange instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %ULVectorRange instance \a self.
    #
    def __idiv__(self: ULVectorRange, t: int) -> ULVectorRange: pass

    ##
    # \brief 
    # \param self The \e %ULVectorRange instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: ULVectorRange, t: int) -> ULVectorRange: pass

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
