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
class DMatrixColumn(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DMatrixColumn instance.
    # \param self The \e %DMatrixColumn instance to initialize.
    # \param mc 
    #
    def __init__(self: object, mc: DMatrixColumn) -> None: pass

    ##
    # \brief Initializes the \e %DMatrixColumn instance.
    # \param self The \e %DMatrixColumn instance to initialize.
    # \param e 
    # \param i 
    #
    def __init__(self: object, e: DMatrixExpression, i: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def getIndex(self: DMatrixColumn) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    #
    # Different Python \e %DMatrixColumn instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DMatrixColumn instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DMatrixColumn) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMatrixColumn instance \a e.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param e The \e %DMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DMatrixColumn, e: ConstFVectorExpression) -> DMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMatrixColumn instance \a e.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param e The \e %DMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DMatrixColumn, e: ConstDVectorExpression) -> DMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMatrixColumn instance \a e.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param e The \e %DMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DMatrixColumn, e: ConstLVectorExpression) -> DMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMatrixColumn instance \a e.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param e The \e %DMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DMatrixColumn, e: ConstULVectorExpression) -> DMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMatrixColumn instance \a c.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param c The \e %DMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DMatrixColumn, c: DMatrixColumn) -> DMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMatrixColumn instance \a a.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param a The \e %DMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DMatrixColumn, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def isEmpty(self: DMatrixColumn) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def getSize(self: DMatrixColumn) -> int: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: DMatrixColumn, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def toArray(self: DMatrixColumn) -> object: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param c 
    #
    def swap(self: DMatrixColumn, c: DMatrixColumn) -> None: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: DMatrixColumn, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def getData(self: DMatrixColumn) -> DMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == c</tt>.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param c The \e %DMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DMatrixColumn, c: DMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param e The \e %DMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DMatrixColumn, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != c</tt>.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param c The \e %DMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DMatrixColumn, c: DMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param e The \e %DMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DMatrixColumn, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: DMatrixColumn, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: DMatrixColumn, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def __len__(self: DMatrixColumn) -> int: pass

    ##
    # \brief Returns a string representation of the \e %DMatrixColumn instance.
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DMatrixColumn) -> str: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def __pos__(self: DMatrixColumn) -> DMatrixColumn: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DMatrixColumn instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %DMatrixColumn instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DMatrixColumn instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DMatrixColumn instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DMatrixColumn instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %DMatrixColumn instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %DMatrixColumn instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %DMatrixColumn instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DMatrixColumn instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %DMatrixColumn instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: DMatrixColumn, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += c</tt>.
    # \param self The \e %DMatrixColumn instance acting as in-place addend.
    # \param c Specifies the second addend.
    # \return The updated \e %DMatrixColumn instance \a self.
    #
    def __iadd__(self: DMatrixColumn, c: DMatrixColumn) -> DMatrixColumn: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DMatrixColumn instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DMatrixColumn instance \a self.
    #
    def __iadd__(self: DMatrixColumn, e: ConstDVectorExpression) -> DMatrixColumn: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= c</tt>.
    # \param self The \e %DMatrixColumn instance acting as in-place minuend.
    # \param c Specifies the subtrahend.
    # \return The updated \e %DMatrixColumn instance \a self.
    #
    def __isub__(self: DMatrixColumn, c: DMatrixColumn) -> DMatrixColumn: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DMatrixColumn instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DMatrixColumn instance \a self.
    #
    def __isub__(self: DMatrixColumn, e: ConstDVectorExpression) -> DMatrixColumn: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DMatrixColumn instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DMatrixColumn instance \a self.
    #
    def __imul__(self: DMatrixColumn, t: float) -> DMatrixColumn: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DMatrixColumn instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DMatrixColumn instance \a self.
    #
    def __idiv__(self: DMatrixColumn, t: float) -> DMatrixColumn: pass

    ##
    # \brief 
    # \param self The \e %DMatrixColumn instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DMatrixColumn, t: float) -> DMatrixColumn: pass

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
