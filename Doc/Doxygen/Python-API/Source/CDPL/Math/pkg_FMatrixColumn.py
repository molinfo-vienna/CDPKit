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
class FMatrixColumn(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FMatrixColumn instance.
    # \param mc 
    #
    def __init__(mc: FMatrixColumn) -> None: pass

    ##
    # \brief Initializes the \e %FMatrixColumn instance.
    # \param e 
    # \param i 
    #
    def __init__(e: FMatrixExpression, i: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %FMatrixColumn instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FMatrixColumn instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixColumn instance \a e.
    # \param e The \e %FMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFVectorExpression) -> FMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixColumn instance \a e.
    # \param e The \e %FMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDVectorExpression) -> FMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixColumn instance \a e.
    # \param e The \e %FMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLVectorExpression) -> FMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixColumn instance \a e.
    # \param e The \e %FMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULVectorExpression) -> FMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixColumn instance \a c.
    # \param c The \e %FMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(c: FMatrixColumn) -> FMatrixColumn: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixColumn instance \a a.
    # \param a The \e %FMatrixColumn instance to copy.
    # \return The assignment target \a self.
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getElement(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param c 
    #
    def swap(c: FMatrixColumn) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> FMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == c</tt>.
    # \param c The \e %FMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(c: FMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %FMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != c</tt>.
    # \param c The \e %FMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(c: FMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %FMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __call__(i: int) -> float: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \e %FMatrixColumn instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> FMatrixColumn: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %FMatrixColumn instance holding the result of the addition.
    #
    def __add__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %FMatrixColumn instance holding the result of the subtraction.
    #
    def __sub__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %FMatrixColumn instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %FMatrixColumn instance holding the result of the multiplication.
    #
    def __mul__(e: ConstFMatrixExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %FMatrixColumn instance holding the result of the division.
    #
    def __div__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += c</tt>.
    # \param c Specifies the second addend.
    # \return The updated \e %FMatrixColumn instance \a self.
    #
    def __iadd__(c: FMatrixColumn) -> FMatrixColumn: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %FMatrixColumn instance \a self.
    #
    def __iadd__(e: ConstFVectorExpression) -> FMatrixColumn: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= c</tt>.
    # \param c Specifies the subtrahend.
    # \return The updated \e %FMatrixColumn instance \a self.
    #
    def __isub__(c: FMatrixColumn) -> FMatrixColumn: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FMatrixColumn instance \a self.
    #
    def __isub__(e: ConstFVectorExpression) -> FMatrixColumn: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %FMatrixColumn instance \a self.
    #
    def __imul__(t: float) -> FMatrixColumn: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %FMatrixColumn instance \a self.
    #
    def __idiv__(t: float) -> FMatrixColumn: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FMatrixColumn: pass

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