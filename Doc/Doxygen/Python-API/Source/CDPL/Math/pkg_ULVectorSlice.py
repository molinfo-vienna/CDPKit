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
class ULVectorSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULVectorSlice instance.
    # \param s 
    #
    def __init__(s: ULVectorSlice) -> None: pass

    ##
    # \brief Initializes the \e %ULVectorSlice instance.
    # \param e 
    # \param s 
    #
    def __init__(e: ULVectorExpression, s: ast.Slice) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStart() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStride() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ULVectorSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ULVectorSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorSlice instance \a e.
    # \param e The \e %ULVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFVectorExpression) -> ULVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorSlice instance \a e.
    # \param e The \e %ULVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDVectorExpression) -> ULVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorSlice instance \a e.
    # \param e The \e %ULVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLVectorExpression) -> ULVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorSlice instance \a e.
    # \param e The \e %ULVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULVectorExpression) -> ULVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorSlice instance \a s.
    # \param s The \e %ULVectorSlice instance to copy.
    # \return The assignment target \a self.
    #
    def assign(s: ULVectorSlice) -> ULVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ULVectorSlice instance \a a.
    # \param a The \e %ULVectorSlice instance to copy.
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
    def getElement(i: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param s 
    #
    def swap(s: ULVectorSlice) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> ULVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param s The \e %ULVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(s: ULVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %ULVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param s The \e %ULVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(s: ULVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %ULVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __call__(i: int) -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \e %ULVectorSlice instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> ULVectorSlice: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %ULVectorSlice instance holding the result of the addition.
    #
    def __add__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %ULVectorSlice instance holding the result of the subtraction.
    #
    def __sub__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %ULVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %ULVectorSlice instance holding the result of the multiplication.
    #
    def __mul__(e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %ULVectorSlice instance holding the result of the division.
    #
    def __div__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param s Specifies the second addend.
    # \return The updated \e %ULVectorSlice instance \a self.
    #
    def __iadd__(s: ULVectorSlice) -> ULVectorSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %ULVectorSlice instance \a self.
    #
    def __iadd__(e: ConstULVectorExpression) -> ULVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param s Specifies the subtrahend.
    # \return The updated \e %ULVectorSlice instance \a self.
    #
    def __isub__(s: ULVectorSlice) -> ULVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %ULVectorSlice instance \a self.
    #
    def __isub__(e: ConstULVectorExpression) -> ULVectorSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %ULVectorSlice instance \a self.
    #
    def __imul__(t: int) -> ULVectorSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %ULVectorSlice instance \a self.
    #
    def __idiv__(t: int) -> ULVectorSlice: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> ULVectorSlice: pass

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
