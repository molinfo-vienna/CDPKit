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
class ULQuaternionVectorAdapter(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULQuaternionVectorAdapter instance.
    # \param self The \e %ULQuaternionVectorAdapter instance to initialize.
    # \param a 
    #
    def __init__(self: object, a: ULQuaternionVectorAdapter) -> None: pass

    ##
    # \brief Initializes the \e %ULQuaternionVectorAdapter instance.
    # \param self The \e %ULQuaternionVectorAdapter instance to initialize.
    # \param e 
    #
    def __init__(self: object, e: ULQuaternionExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    #
    # Different Python \e %ULQuaternionVectorAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULQuaternionVectorAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ULQuaternionVectorAdapter) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULQuaternionVectorAdapter instance \a e.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param e The \e %ULQuaternionVectorAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULQuaternionVectorAdapter, e: ConstFVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULQuaternionVectorAdapter instance \a e.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param e The \e %ULQuaternionVectorAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULQuaternionVectorAdapter, e: ConstDVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULQuaternionVectorAdapter instance \a e.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param e The \e %ULQuaternionVectorAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULQuaternionVectorAdapter, e: ConstLVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULQuaternionVectorAdapter instance \a e.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param e The \e %ULQuaternionVectorAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULQuaternionVectorAdapter, e: ConstULVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULQuaternionVectorAdapter instance \a a.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param a The \e %ULQuaternionVectorAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULQuaternionVectorAdapter, a: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULQuaternionVectorAdapter instance \a a.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param a The \e %ULQuaternionVectorAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ULQuaternionVectorAdapter, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def isEmpty(self: ULQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def getSize(self: ULQuaternionVectorAdapter) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: ULQuaternionVectorAdapter, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def toArray(self: ULQuaternionVectorAdapter) -> object: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param a 
    #
    def swap(self: ULQuaternionVectorAdapter, a: ULQuaternionVectorAdapter) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: ULQuaternionVectorAdapter, i: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def getData(self: ULQuaternionVectorAdapter) -> ULQuaternionExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == a</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param a The \e %ULQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULQuaternionVectorAdapter, a: ULQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param e The \e %ULQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ULQuaternionVectorAdapter, e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != a</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param a The \e %ULQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULQuaternionVectorAdapter, a: ULQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param e The \e %ULQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ULQuaternionVectorAdapter, e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: ULQuaternionVectorAdapter, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: ULQuaternionVectorAdapter, i: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def __len__(self: ULQuaternionVectorAdapter) -> int: pass

    ##
    # \brief Returns a string representation of the \e %ULQuaternionVectorAdapter instance.
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ULQuaternionVectorAdapter) -> str: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def __pos__(self: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ULQuaternionVectorAdapter instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ULQuaternionVectorAdapter instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ULQuaternionVectorAdapter instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ULQuaternionVectorAdapter instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ULQuaternionVectorAdapter instance holding the result of the division.
    #
    def __div__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: ULQuaternionVectorAdapter, i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as in-place addend.
    # \param a Specifies the second addend.
    # \return The updated \e %ULQuaternionVectorAdapter instance \a self.
    #
    def __iadd__(self: ULQuaternionVectorAdapter, a: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %ULQuaternionVectorAdapter instance \a self.
    #
    def __iadd__(self: ULQuaternionVectorAdapter, e: ConstULVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as in-place minuend.
    # \param a Specifies the subtrahend.
    # \return The updated \e %ULQuaternionVectorAdapter instance \a self.
    #
    def __isub__(self: ULQuaternionVectorAdapter, a: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %ULQuaternionVectorAdapter instance \a self.
    #
    def __isub__(self: ULQuaternionVectorAdapter, e: ConstULVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %ULQuaternionVectorAdapter instance \a self.
    #
    def __imul__(self: ULQuaternionVectorAdapter, t: int) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %ULQuaternionVectorAdapter instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %ULQuaternionVectorAdapter instance \a self.
    #
    def __idiv__(self: ULQuaternionVectorAdapter, t: int) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief 
    # \param self The \e %ULQuaternionVectorAdapter instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: ULQuaternionVectorAdapter, t: int) -> ULQuaternionVectorAdapter: pass

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
