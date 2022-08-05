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
class DHomogenousCoordsAdapter(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DHomogenousCoordsAdapter instance.
    # \param a 
    #
    def __init__(a: DHomogenousCoordsAdapter) -> None: pass

    ##
    # \brief Initializes the \e %DHomogenousCoordsAdapter instance.
    # \param e 
    #
    def __init__(e: DVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %DHomogenousCoordsAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DHomogenousCoordsAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DHomogenousCoordsAdapter instance \a e.
    # \param e The \e %DHomogenousCoordsAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DHomogenousCoordsAdapter instance \a e.
    # \param e The \e %DHomogenousCoordsAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DHomogenousCoordsAdapter instance \a e.
    # \param e The \e %DHomogenousCoordsAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DHomogenousCoordsAdapter instance \a e.
    # \param e The \e %DHomogenousCoordsAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DHomogenousCoordsAdapter instance \a r.
    # \param r The \e %DHomogenousCoordsAdapter instance to copy.
    # \return The assignment target \a self.
    #
    def assign(r: DHomogenousCoordsAdapter) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DHomogenousCoordsAdapter instance \a a.
    # \param a The \e %DHomogenousCoordsAdapter instance to copy.
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
    # \param r 
    #
    def swap(r: DHomogenousCoordsAdapter) -> None: pass

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
    def getData() -> DVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \e %DHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(r: DHomogenousCoordsAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %DHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \e %DHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(r: DHomogenousCoordsAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %DHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstDVectorExpression) -> bool: pass

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
    # \brief Returns a string representation of the \e %DHomogenousCoordsAdapter instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DHomogenousCoordsAdapter: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %DHomogenousCoordsAdapter instance holding the result of the addition.
    #
    def __add__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %DHomogenousCoordsAdapter instance holding the result of the subtraction.
    #
    def __sub__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %DHomogenousCoordsAdapter instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %DHomogenousCoordsAdapter instance holding the result of the multiplication.
    #
    def __mul__(e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %DHomogenousCoordsAdapter instance holding the result of the division.
    #
    def __div__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param a Specifies the second addend.
    # \return The updated \e %DHomogenousCoordsAdapter instance \a self.
    #
    def __iadd__(a: DHomogenousCoordsAdapter) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %DHomogenousCoordsAdapter instance \a self.
    #
    def __iadd__(e: ConstDVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param a Specifies the subtrahend.
    # \return The updated \e %DHomogenousCoordsAdapter instance \a self.
    #
    def __isub__(a: DHomogenousCoordsAdapter) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DHomogenousCoordsAdapter instance \a self.
    #
    def __isub__(e: ConstDVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %DHomogenousCoordsAdapter instance \a self.
    #
    def __imul__(t: float) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %DHomogenousCoordsAdapter instance \a self.
    #
    def __idiv__(t: float) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> DHomogenousCoordsAdapter: pass

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
