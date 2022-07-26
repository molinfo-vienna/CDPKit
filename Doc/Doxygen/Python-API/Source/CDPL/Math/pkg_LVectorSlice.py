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
class LVectorSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LVectorSlice instance.
    # \param self The \e %LVectorSlice instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: LVectorSlice) -> None: pass

    ##
    # \brief Initializes the \e %LVectorSlice instance.
    # \param self The \e %LVectorSlice instance to initialize.
    # \param e 
    # \param s 
    #
    def __init__(self: object, e: LVectorExpression, s: ast.Slice) -> None: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def getStart(self: LVectorSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def getStride(self: LVectorSlice) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LVectorSlice instance this method is called upon.
    #
    # Different Python \e %LVectorSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LVectorSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: LVectorSlice) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LVectorSlice instance \a e.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param e The \e %LVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LVectorSlice, e: ConstFVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LVectorSlice instance \a e.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param e The \e %LVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LVectorSlice, e: ConstDVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LVectorSlice instance \a e.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param e The \e %LVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LVectorSlice, e: ConstLVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LVectorSlice instance \a e.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param e The \e %LVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LVectorSlice, e: ConstULVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LVectorSlice instance \a s.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param s The \e %LVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LVectorSlice, s: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LVectorSlice instance \a a.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param a The \e %LVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LVectorSlice, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def isEmpty(self: LVectorSlice) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def getSize(self: LVectorSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: LVectorSlice, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def toArray(self: LVectorSlice) -> object: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param s 
    #
    def swap(self: LVectorSlice, s: LVectorSlice) -> None: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: LVectorSlice, i: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def getData(self: LVectorSlice) -> LVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param s The \e %LVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LVectorSlice, s: LVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param e The \e %LVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LVectorSlice, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param s The \e %LVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LVectorSlice, s: LVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param e The \e %LVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LVectorSlice, e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: LVectorSlice, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: LVectorSlice, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def __len__(self: LVectorSlice) -> int: pass

    ##
    # \brief Returns a string representation of the \e %LVectorSlice instance.
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: LVectorSlice) -> str: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def __pos__(self: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LVectorSlice instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %LVectorSlice instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LVectorSlice instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LVectorSlice instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LVectorSlice instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %LVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LVectorSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %LVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LVectorSlice instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %LVectorSlice instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: LVectorSlice, i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param self The \e %LVectorSlice instance acting as in-place addend.
    # \param s Specifies the second addend.
    # \return The updated \e %LVectorSlice instance \a self.
    #
    def __iadd__(self: LVectorSlice, s: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LVectorSlice instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LVectorSlice instance \a self.
    #
    def __iadd__(self: LVectorSlice, e: ConstLVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param self The \e %LVectorSlice instance acting as in-place minuend.
    # \param s Specifies the subtrahend.
    # \return The updated \e %LVectorSlice instance \a self.
    #
    def __isub__(self: LVectorSlice, s: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LVectorSlice instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LVectorSlice instance \a self.
    #
    def __isub__(self: LVectorSlice, e: ConstLVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LVectorSlice instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LVectorSlice instance \a self.
    #
    def __imul__(self: LVectorSlice, t: int) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LVectorSlice instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LVectorSlice instance \a self.
    #
    def __idiv__(self: LVectorSlice, t: int) -> LVectorSlice: pass

    ##
    # \brief 
    # \param self The \e %LVectorSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: LVectorSlice, t: int) -> LVectorSlice: pass

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
