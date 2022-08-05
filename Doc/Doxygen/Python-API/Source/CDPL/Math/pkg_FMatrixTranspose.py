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
class FMatrixTranspose(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FMatrixTranspose instance.
    # \param mt 
    #
    def __init__(mt: FMatrixTranspose) -> None: pass

    ##
    # \brief Initializes the \e %FMatrixTranspose instance.
    # \param e 
    #
    def __init__(e: FMatrixExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %FMatrixTranspose instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FMatrixTranspose instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a e.
    # \param e The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a mt.
    # \param mt The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(mt: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixTranspose instance \a a.
    # \param a The \e %FMatrixTranspose instance to copy.
    # \return The assignment target \a self.
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSize1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getSize2() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(i: int, j: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param mt 
    #
    def swap(mt: FMatrixTranspose) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> FMatrixExpression: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(i: int, j: int) -> float: pass

    ##
    # \brief 
    # \param ij 
    # \return 
    #
    def __getitem__(ij: tuple) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == mt</tt>.
    # \param mt The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(mt: FMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mt</tt>.
    # \param mt The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(mt: FMatrixTranspose) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %FMatrixTranspose instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstFMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FMatrixTranspose instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> FMatrixTranspose: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %FMatrixTranspose instance holding the result of the addition.
    #
    def __add__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %FMatrixTranspose instance holding the result of the subtraction.
    #
    def __sub__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %FMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixTranspose instance holding the result of the multiplication.
    #
    def __mul__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %FMatrixTranspose instance holding the result of the division.
    #
    def __div__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstFMatrixExpression: pass

    ##
    # \brief 
    # \param ij 
    # \param v 
    #
    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mt</tt>.
    # \param mt Specifies the second addend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __iadd__(mt: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __iadd__(e: ConstFMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= mt</tt>.
    # \param mt Specifies the subtrahend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __isub__(mt: FMatrixTranspose) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __isub__(e: ConstFMatrixExpression) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __imul__(t: float) -> FMatrixTranspose: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %FMatrixTranspose instance \a self.
    #
    def __idiv__(t: float) -> FMatrixTranspose: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FMatrixTranspose: pass

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
