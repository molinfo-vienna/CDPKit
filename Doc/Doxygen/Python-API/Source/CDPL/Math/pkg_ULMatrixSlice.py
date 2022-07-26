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
class ULMatrixSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULMatrixSlice instance.
    # \param self The \e %ULMatrixSlice instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: ULMatrixSlice) -> None: pass

    ##
    # \brief Initializes the \e %ULMatrixSlice instance.
    # \param self The \e %ULMatrixSlice instance to initialize.
    # \param e 
    # \param s1 
    # \param s2 
    #
    def __init__(self: object, e: ULMatrixExpression, s1: ast.Slice, s2: ast.Slice) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStart1(self: ULMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStart2(self: ULMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStride1(self: ULMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getStride2(self: ULMatrixSlice) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    #
    # Different Python \e %ULMatrixSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULMatrixSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ULMatrixSlice) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULMatrixSlice instance \a e.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param e The \e %ULMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULMatrixSlice, e: ConstFMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULMatrixSlice instance \a e.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param e The \e %ULMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULMatrixSlice, e: ConstDMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULMatrixSlice instance \a e.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param e The \e %ULMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULMatrixSlice, e: ConstLMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULMatrixSlice instance \a e.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param e The \e %ULMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULMatrixSlice, e: ConstULMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULMatrixSlice instance \a s.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param s The \e %ULMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULMatrixSlice, s: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULMatrixSlice instance \a a.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param a The \e %ULMatrixSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULMatrixSlice, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getSize1(self: ULMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getSize2(self: ULMatrixSlice) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def isEmpty(self: ULMatrixSlice) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(self: ULMatrixSlice, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def toArray(self: ULMatrixSlice) -> object: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param s 
    #
    def swap(self: ULMatrixSlice, s: ULMatrixSlice) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: ULMatrixSlice, i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def getData(self: ULMatrixSlice) -> ULMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(self: ULMatrixSlice, i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param ij 
    # \return 
    #
    def __getitem__(self: ULMatrixSlice, ij: tuple) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def __len__(self: ULMatrixSlice) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param s The \e %ULMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULMatrixSlice, s: ULMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param e The \e %ULMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULMatrixSlice, e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param s The \e %ULMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULMatrixSlice, s: ULMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param e The \e %ULMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULMatrixSlice, e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ULMatrixSlice instance.
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ULMatrixSlice) -> str: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def __pos__(self: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ULMatrixSlice instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ULMatrixSlice instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ULMatrixSlice instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ULMatrixSlice instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ULMatrixSlice instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ULMatrixSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULMatrixSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULMatrixSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULMatrixSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULMatrixSlice instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ULMatrixSlice instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ULMatrixSlice instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: ULMatrixSlice, ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param self The \e %ULMatrixSlice instance acting as in-place addend.
    # \param s Specifies the second addend.
    # \return The updated \e %ULMatrixSlice instance \a self.
    #
    def __iadd__(self: ULMatrixSlice, s: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %ULMatrixSlice instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %ULMatrixSlice instance \a self.
    #
    def __iadd__(self: ULMatrixSlice, e: ConstULMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param self The \e %ULMatrixSlice instance acting as in-place minuend.
    # \param s Specifies the subtrahend.
    # \return The updated \e %ULMatrixSlice instance \a self.
    #
    def __isub__(self: ULMatrixSlice, s: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %ULMatrixSlice instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %ULMatrixSlice instance \a self.
    #
    def __isub__(self: ULMatrixSlice, e: ConstULMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %ULMatrixSlice instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %ULMatrixSlice instance \a self.
    #
    def __imul__(self: ULMatrixSlice, t: int) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %ULMatrixSlice instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %ULMatrixSlice instance \a self.
    #
    def __idiv__(self: ULMatrixSlice, t: int) -> ULMatrixSlice: pass

    ##
    # \brief 
    # \param self The \e %ULMatrixSlice instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: ULMatrixSlice, t: int) -> ULMatrixSlice: pass

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
