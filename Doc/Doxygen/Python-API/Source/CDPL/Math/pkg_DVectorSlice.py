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
class DVectorSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DVectorSlice instance.
    # \param self The \e %DVectorSlice instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: DVectorSlice) -> None: pass

    ##
    # \brief Initializes the \e %DVectorSlice instance.
    # \param self The \e %DVectorSlice instance to initialize.
    # \param e 
    # \param s 
    #
    def __init__(self: object, e: DVectorExpression, s: ast.Slice) -> None: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def getStart(self: DVectorSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def getStride(self: DVectorSlice) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DVectorSlice instance this method is called upon.
    #
    # Different Python \e %DVectorSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DVectorSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DVectorSlice) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorSlice instance \a e.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param e The \e %DVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DVectorSlice, e: ConstFVectorExpression) -> DVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorSlice instance \a e.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param e The \e %DVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DVectorSlice, e: ConstDVectorExpression) -> DVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorSlice instance \a e.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param e The \e %DVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DVectorSlice, e: ConstLVectorExpression) -> DVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorSlice instance \a e.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param e The \e %DVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DVectorSlice, e: ConstULVectorExpression) -> DVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorSlice instance \a s.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param s The \e %DVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DVectorSlice, s: DVectorSlice) -> DVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DVectorSlice instance \a a.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param a The \e %DVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DVectorSlice, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def isEmpty(self: DVectorSlice) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def getSize(self: DVectorSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: DVectorSlice, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def toArray(self: DVectorSlice) -> object: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param s 
    #
    def swap(self: DVectorSlice, s: DVectorSlice) -> None: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: DVectorSlice, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def getData(self: DVectorSlice) -> DVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param s The \e %DVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DVectorSlice, s: DVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param e The \e %DVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DVectorSlice, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param s The \e %DVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DVectorSlice, s: DVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param e The \e %DVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DVectorSlice, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: DVectorSlice, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: DVectorSlice, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def __len__(self: DVectorSlice) -> int: pass

    ##
    # \brief Returns a string representation of the \e %DVectorSlice instance.
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DVectorSlice) -> str: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def __pos__(self: DVectorSlice) -> DVectorSlice: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DVectorSlice instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %DVectorSlice instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DVectorSlice instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DVectorSlice instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DVectorSlice instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %DVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %DVectorSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %DVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DVectorSlice instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %DVectorSlice instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: DVectorSlice, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param self The \e %DVectorSlice instance acting as in-place addend.
    # \param s Specifies the second addend.
    # \return The updated \e %DVectorSlice instance \a self.
    #
    def __iadd__(self: DVectorSlice, s: DVectorSlice) -> DVectorSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DVectorSlice instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DVectorSlice instance \a self.
    #
    def __iadd__(self: DVectorSlice, e: ConstDVectorExpression) -> DVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param self The \e %DVectorSlice instance acting as in-place minuend.
    # \param s Specifies the subtrahend.
    # \return The updated \e %DVectorSlice instance \a self.
    #
    def __isub__(self: DVectorSlice, s: DVectorSlice) -> DVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DVectorSlice instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DVectorSlice instance \a self.
    #
    def __isub__(self: DVectorSlice, e: ConstDVectorExpression) -> DVectorSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DVectorSlice instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DVectorSlice instance \a self.
    #
    def __imul__(self: DVectorSlice, t: float) -> DVectorSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DVectorSlice instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DVectorSlice instance \a self.
    #
    def __idiv__(self: DVectorSlice, t: float) -> DVectorSlice: pass

    ##
    # \brief 
    # \param self The \e %DVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DVectorSlice, t: float) -> DVectorSlice: pass

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
