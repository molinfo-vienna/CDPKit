#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
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
    # \brief Initializes a copy of the \e %ULMatrixSlice instance \a s.
    # \param s The \e %ULMatrixSlice instance to copy.
    # 
    def __init__(s: ULMatrixSlice) -> None: pass

    ##
    # \brief Initializes the \e %ULMatrixSlice instance.
    # \param e 
    # \param s1 
    # \param s2 
    # 
    def __init__(e: ULMatrixExpression, s1: Slice, s2: Slice) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStart1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStart2() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStride1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStride2() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ULMatrixSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ULMatrixSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstFMatrixExpression instance \a e.
    # \param e The \c %ConstFMatrixExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstFMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstDMatrixExpression instance \a e.
    # \param e The \c %ConstDMatrixExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstDMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstLMatrixExpression instance \a e.
    # \param e The \c %ConstLMatrixExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstLMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstULMatrixExpression instance \a e.
    # \param e The \c %ConstULMatrixExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstULMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ULMatrixSlice instance \a s.
    # \param s The \c %ULMatrixSlice instance to copy.
    # \return \a self
    # 
    def assign(s: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
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
    def getElement(i: int, j: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param s 
    #
    def swap(s: ULMatrixSlice) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> ULMatrixExpression: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param ij 
    # \return 
    #
    def __getitem__(ij: tuple) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param s The \c %ULMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(s: ULMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstULMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param s The \c %ULMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(s: ULMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstULMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %ULMatrixSlice instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> ULMatrixSlice: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstULMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %ULMatrixSlice instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstULMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param ij 
    # \param v 
    #
    def __setitem__(ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param s Specifies the second addend.
    # \return The updated \c %ULMatrixSlice instance \a self.
    # 
    def __iadd__(s: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %ULMatrixSlice instance \a self.
    # 
    def __iadd__(e: ConstULMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param s Specifies the subtrahend.
    # \return The updated \c %ULMatrixSlice instance \a self.
    # 
    def __isub__(s: ULMatrixSlice) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %ULMatrixSlice instance \a self.
    # 
    def __isub__(e: ConstULMatrixExpression) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %ULMatrixSlice instance \a self.
    # 
    def __imul__(t: int) -> ULMatrixSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %ULMatrixSlice instance \a self.
    # 
    def __idiv__(t: int) -> ULMatrixSlice: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> ULMatrixSlice: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)

    start1 = property(getStart1)

    start2 = property(getStart2)

    stride1 = property(getStride1)

    stride2 = property(getStride2)
