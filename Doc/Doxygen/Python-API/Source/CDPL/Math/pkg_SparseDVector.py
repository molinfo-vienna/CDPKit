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
class SparseDVector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param self The \e %SparseDVector instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param self The \e %SparseDVector instance to initialize.
    # \param v 
    #
    def __init__(self: object, v: SparseDVector) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param self The \e %SparseDVector instance to initialize.
    # \param n 
    #
    def __init__(self: object, n: int) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param arg1 The \e %SparseDVector instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param arg1 The \e %SparseDVector instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstDVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param arg1 The \e %SparseDVector instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstLVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param arg1 The \e %SparseDVector instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstULVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseDVector instance.
    # \param arg1 The \e %SparseDVector instance to initialize.
    # \param a 
    #
    def __init__(arg1: object, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param n 
    #
    def resize(self: SparseDVector, n: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    #
    def clear(self: SparseDVector) -> None: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def getNumElements(self: SparseDVector) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SparseDVector instance this method is called upon.
    #
    # Different Python \e %SparseDVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SparseDVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SparseDVector) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseDVector instance \a e.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param e The \e %SparseDVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SparseDVector, e: ConstFVectorExpression) -> SparseDVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseDVector instance \a e.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param e The \e %SparseDVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SparseDVector, e: ConstDVectorExpression) -> SparseDVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseDVector instance \a e.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param e The \e %SparseDVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SparseDVector, e: ConstLVectorExpression) -> SparseDVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseDVector instance \a e.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param e The \e %SparseDVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SparseDVector, e: ConstULVectorExpression) -> SparseDVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseDVector instance \a v.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param v The \e %SparseDVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SparseDVector, v: SparseDVector) -> SparseDVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseDVector instance \a a.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param a The \e %SparseDVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SparseDVector, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def isEmpty(self: SparseDVector) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def getSize(self: SparseDVector) -> int: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: SparseDVector, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def toArray(self: SparseDVector) -> object: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param v 
    #
    def swap(self: SparseDVector, v: SparseDVector) -> None: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: SparseDVector, i: int, v: float) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param v The \e %SparseDVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: SparseDVector, v: SparseDVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param e The \e %SparseDVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: SparseDVector, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param v The \e %SparseDVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: SparseDVector, v: SparseDVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param e The \e %SparseDVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: SparseDVector, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: SparseDVector, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: SparseDVector, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def __len__(self: SparseDVector) -> int: pass

    ##
    # \brief Returns a string representation of the \e %SparseDVector instance.
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: SparseDVector) -> str: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def __pos__(self: SparseDVector) -> SparseDVector: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %SparseDVector instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %SparseDVector instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %SparseDVector instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %SparseDVector instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %SparseDVector instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %SparseDVector instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %SparseDVector instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %SparseDVector instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %SparseDVector instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %SparseDVector instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: SparseDVector, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += v</tt>.
    # \param self The \e %SparseDVector instance acting as in-place addend.
    # \param v Specifies the second addend.
    # \return The updated \e %SparseDVector instance \a self.
    #
    def __iadd__(self: SparseDVector, v: SparseDVector) -> SparseDVector: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %SparseDVector instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %SparseDVector instance \a self.
    #
    def __iadd__(self: SparseDVector, e: ConstDVectorExpression) -> SparseDVector: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= v</tt>.
    # \param self The \e %SparseDVector instance acting as in-place minuend.
    # \param v Specifies the subtrahend.
    # \return The updated \e %SparseDVector instance \a self.
    #
    def __isub__(self: SparseDVector, v: SparseDVector) -> SparseDVector: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %SparseDVector instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %SparseDVector instance \a self.
    #
    def __isub__(self: SparseDVector, e: ConstDVectorExpression) -> SparseDVector: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %SparseDVector instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %SparseDVector instance \a self.
    #
    def __imul__(self: SparseDVector, t: float) -> SparseDVector: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %SparseDVector instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %SparseDVector instance \a self.
    #
    def __idiv__(self: SparseDVector, t: float) -> SparseDVector: pass

    ##
    # \brief 
    # \param self The \e %SparseDVector instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: SparseDVector, t: float) -> SparseDVector: pass

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
    numElements = property(getNumElements)
