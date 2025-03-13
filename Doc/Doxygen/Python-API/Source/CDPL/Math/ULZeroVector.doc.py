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
class ULZeroVector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ULZeroVector instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %ULZeroVector instance \a v.
    # \param v The \e %ULZeroVector instance to copy.
    # 
    def __init__(v: ULZeroVector) -> None: pass

    ##
    # \brief Initializes the \e %ULZeroVector instance.
    # \param n 
    # 
    def __init__(n: int) -> None: pass

    ##
    # \brief 
    # \param n 
    #
    def resize(n: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ULZeroVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ULZeroVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ULZeroVector instance \a v.
    # \param v The \c %ULZeroVector instance to copy.
    # \return \a self
    # 
    def assign(v: ULZeroVector) -> ULZeroVector: pass

    ##
    # \brief 
    # \param v 
    #
    def swap(v: ULZeroVector) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \c %ULZeroVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(v: ULZeroVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \c %ULZeroVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(v: ULZeroVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstULVectorExpression instance to be compared with.
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
    # \brief Returns a string representation of the \e %ULZeroVector instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> ULZeroVector: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstULVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %ULZeroVector instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstULVectorExpression instance holding the result of the division.
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

    objectID = property(getObjectID)

    size = property(getSize)
