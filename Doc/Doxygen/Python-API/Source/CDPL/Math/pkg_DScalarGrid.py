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
class DScalarGrid(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DScalarGrid instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DScalarGrid instance.
    # \param g 
    #
    def __init__(g: DScalarGrid) -> None: pass

    ##
    # \brief Initializes the \e %DScalarGrid instance.
    # \param m 
    # \param n 
    # \param o 
    # \param v 
    #
    def __init__(m: int, n: int, o: int, v: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param m 
    # \param n 
    # \param o 
    #
    def resize(m: int, n: int, o: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %DScalarGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DScalarGrid instances \e a and \e b reference different C++ objects. 
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
    def getSize3() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(i: int, j: int, k: int) -> float: pass

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
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DScalarGrid instance \a g.
    # \param g The \e %DScalarGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(g: DScalarGrid) -> DScalarGrid: pass

    ##
    # \brief 
    # \param g 
    #
    def swap(g: DScalarGrid) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def __call__(i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __call__(i: int) -> float: pass

    ##
    # \brief 
    # \param ijk 
    # \return 
    #
    def __getitem__(ijk: tuple) -> float: pass

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
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param g The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(g: DScalarGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(g: DScalarGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DScalarGrid instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DScalarGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %DScalarGrid instance holding the result of the addition.
    #
    def __add__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %DScalarGrid instance holding the result of the subtraction.
    #
    def __sub__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %DScalarGrid instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %DScalarGrid instance holding the result of the division.
    #
    def __div__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstDGridExpression: pass

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
    size3 = property(getSize3)
