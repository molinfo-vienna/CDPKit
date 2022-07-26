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
class FVectorSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FVectorSlice instance.
    # \param self The \e %FVectorSlice instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: FVectorSlice) -> None: pass

    ##
    # \brief Initializes the \e %FVectorSlice instance.
    # \param self The \e %FVectorSlice instance to initialize.
    # \param e 
    # \param s 
    #
    def __init__(self: object, e: FVectorExpression, s: ast.Slice) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def getStart(self: FVectorSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def getStride(self: FVectorSlice) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FVectorSlice instance this method is called upon.
    #
    # Different Python \e %FVectorSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FVectorSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FVectorSlice) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorSlice instance \a e.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param e The \e %FVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorSlice, e: ConstFVectorExpression) -> FVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorSlice instance \a e.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param e The \e %FVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorSlice, e: ConstDVectorExpression) -> FVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorSlice instance \a e.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param e The \e %FVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorSlice, e: ConstLVectorExpression) -> FVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorSlice instance \a e.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param e The \e %FVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorSlice, e: ConstULVectorExpression) -> FVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorSlice instance \a s.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param s The \e %FVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorSlice, s: FVectorSlice) -> FVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FVectorSlice instance \a a.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param a The \e %FVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FVectorSlice, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FVectorSlice) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def getSize(self: FVectorSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: FVectorSlice, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def toArray(self: FVectorSlice) -> object: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param s 
    #
    def swap(self: FVectorSlice, s: FVectorSlice) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: FVectorSlice, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def getData(self: FVectorSlice) -> FVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param s The \e %FVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FVectorSlice, s: FVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param e The \e %FVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FVectorSlice, e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param s The \e %FVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FVectorSlice, s: FVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param e The \e %FVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FVectorSlice, e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: FVectorSlice, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: FVectorSlice, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def __len__(self: FVectorSlice) -> int: pass

    ##
    # \brief Returns a string representation of the \e %FVectorSlice instance.
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FVectorSlice) -> str: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def __pos__(self: FVectorSlice) -> FVectorSlice: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FVectorSlice instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FVectorSlice instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FVectorSlice instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FVectorSlice instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FVectorSlice instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FVectorSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FVectorSlice instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FVectorSlice instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: FVectorSlice, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param self The \e %FVectorSlice instance acting as in-place addend.
    # \param s Specifies the second addend.
    # \return The updated \e %FVectorSlice instance \a self.
    #
    def __iadd__(self: FVectorSlice, s: FVectorSlice) -> FVectorSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FVectorSlice instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FVectorSlice instance \a self.
    #
    def __iadd__(self: FVectorSlice, e: ConstFVectorExpression) -> FVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param self The \e %FVectorSlice instance acting as in-place minuend.
    # \param s Specifies the subtrahend.
    # \return The updated \e %FVectorSlice instance \a self.
    #
    def __isub__(self: FVectorSlice, s: FVectorSlice) -> FVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FVectorSlice instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FVectorSlice instance \a self.
    #
    def __isub__(self: FVectorSlice, e: ConstFVectorExpression) -> FVectorSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FVectorSlice instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FVectorSlice instance \a self.
    #
    def __imul__(self: FVectorSlice, t: float) -> FVectorSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FVectorSlice instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FVectorSlice instance \a self.
    #
    def __idiv__(self: FVectorSlice, t: float) -> FVectorSlice: pass

    ##
    # \brief 
    # \param self The \e %FVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FVectorSlice, t: float) -> FVectorSlice: pass

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

    ##
    # \brief 
    #
    stride = property(getStride)
