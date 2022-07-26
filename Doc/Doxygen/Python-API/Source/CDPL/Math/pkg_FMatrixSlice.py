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
class FMatrixSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FMatrixSlice instance.
    # \param self The \e %FMatrixSlice instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: FMatrixSlice) -> None: pass

    ##
    # \brief Initializes the \e %FMatrixSlice instance.
    # \param self The \e %FMatrixSlice instance to initialize.
    # \param e 
    # \param s1 
    # \param s2 
    #
    def __init__(self: object, e: FMatrixExpression, s1: ast.Slice, s2: ast.Slice) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStart1(self: FMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStart2(self: FMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStride1(self: FMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStride2(self: FMatrixSlice) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    #
    # Different Python \e %FMatrixSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FMatrixSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FMatrixSlice) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixSlice instance \a e.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param e The \e %FMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixSlice, e: ConstFMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixSlice instance \a e.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param e The \e %FMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixSlice, e: ConstDMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixSlice instance \a e.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param e The \e %FMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixSlice, e: ConstLMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixSlice instance \a e.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param e The \e %FMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixSlice, e: ConstULMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixSlice instance \a s.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param s The \e %FMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixSlice, s: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixSlice instance \a a.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param a The \e %FMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMatrixSlice, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getSize1(self: FMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getSize2(self: FMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FMatrixSlice) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: FMatrixSlice, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def toArray(self: FMatrixSlice) -> object: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param s 
    #
    def swap(self: FMatrixSlice, s: FMatrixSlice) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: FMatrixSlice, i: int, j: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def getData(self: FMatrixSlice) -> FMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: FMatrixSlice, i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: FMatrixSlice, ij: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def __len__(self: FMatrixSlice) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param s The \e %FMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FMatrixSlice, s: FMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param e The \e %FMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FMatrixSlice, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param s The \e %FMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FMatrixSlice, s: FMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param e The \e %FMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FMatrixSlice, e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FMatrixSlice instance.
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FMatrixSlice) -> str: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def __pos__(self: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FMatrixSlice instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FMatrixSlice instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FMatrixSlice instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FMatrixSlice instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FMatrixSlice instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FMatrixSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FMatrixSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %FMatrixSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FMatrixSlice instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FMatrixSlice instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: FMatrixSlice, ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param self The \e %FMatrixSlice instance acting as in-place addend.
    # \param s Specifies the second addend.
    # \return The updated \e %FMatrixSlice instance \a self.
    #
    def __iadd__(self: FMatrixSlice, s: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FMatrixSlice instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FMatrixSlice instance \a self.
    #
    def __iadd__(self: FMatrixSlice, e: ConstFMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param self The \e %FMatrixSlice instance acting as in-place minuend.
    # \param s Specifies the subtrahend.
    # \return The updated \e %FMatrixSlice instance \a self.
    #
    def __isub__(self: FMatrixSlice, s: FMatrixSlice) -> FMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FMatrixSlice instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FMatrixSlice instance \a self.
    #
    def __isub__(self: FMatrixSlice, e: ConstFMatrixExpression) -> FMatrixSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FMatrixSlice instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FMatrixSlice instance \a self.
    #
    def __imul__(self: FMatrixSlice, t: float) -> FMatrixSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FMatrixSlice instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FMatrixSlice instance \a self.
    #
    def __idiv__(self: FMatrixSlice, t: float) -> FMatrixSlice: pass

    ##
    # \brief 
    # \param self The \e %FMatrixSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FMatrixSlice, t: float) -> FMatrixSlice: pass

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

    ##
    # \brief 
    #
    start1 = property(getStart1)

    ##
    # \brief 
    #
    start2 = property(getStart2)

    ##
    # \brief 
    #
    stride1 = property(getStride1)

    ##
    # \brief 
    #
    stride2 = property(getStride2)
