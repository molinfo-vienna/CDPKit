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
class DUnitVector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DUnitVector instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %DUnitVector instance \a v.
    # \param v The \e %DUnitVector instance to copy.
    # 
    def __init__(v: DUnitVector) -> None: pass

    ##
    # \brief Initializes the \e %DUnitVector instance.
    # \param n 
    # \param i 
    # 
    def __init__(n: int, i: int) -> None: pass

    ##
    # \brief 
    # \param n 
    #
    def resize(n: int) -> None: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def getIndex() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DUnitVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DUnitVector instances \e a and \e b reference different C++ objects. 
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
    def getElement(i: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DUnitVector instance \a v.
    # \param v The \c %DUnitVector instance to copy.
    # \return \a self
    # 
    def assign(v: DUnitVector) -> DUnitVector: pass

    ##
    # \brief 
    # \param v 
    #
    def swap(v: DUnitVector) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \c %DUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(v: DUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \c %DUnitVector instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(v: DUnitVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDVectorExpression instance to be compared with.
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
    # \brief Returns a string representation of the \e %DUnitVector instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DUnitVector: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstDVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %DUnitVector instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstDVectorExpression instance holding the result of the division.
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

    index = property(getIndex)

    objectID = property(getObjectID)

    size = property(getSize)
