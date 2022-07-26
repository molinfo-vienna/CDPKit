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
    # \param self The \e %DScalarGrid instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DScalarGrid instance.
    # \param self The \e %DScalarGrid instance to initialize.
    # \param g 
    #
    def __init__(self: object, g: DScalarGrid) -> None: pass

    ##
    # \brief Initializes the \e %DScalarGrid instance.
    # \param self The \e %DScalarGrid instance to initialize.
    # \param m 
    # \param n 
    # \param o 
    # \param v 
    #
    def __init__(self: object, m: int, n: int, o: int, v: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param m 
    # \param n 
    # \param o 
    #
    def resize(self: DScalarGrid, m: int, n: int, o: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DScalarGrid instance this method is called upon.
    #
    # Different Python \e %DScalarGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DScalarGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DScalarGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def getSize1(self: DScalarGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def getSize2(self: DScalarGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def getSize3(self: DScalarGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def isEmpty(self: DScalarGrid) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(self: DScalarGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: DScalarGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def toArray(self: DScalarGrid) -> object: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def getSize(self: DScalarGrid) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DScalarGrid instance \a g.
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param g The \e %DScalarGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DScalarGrid, g: DScalarGrid) -> DScalarGrid: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param g 
    #
    def swap(self: DScalarGrid, g: DScalarGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def __call__(self: DScalarGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: DScalarGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param ijk 
    # \return 
    #
    def __getitem__(self: DScalarGrid, ijk: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: DScalarGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def __len__(self: DScalarGrid) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param g The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DScalarGrid, g: DScalarGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param e The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DScalarGrid, e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param g The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DScalarGrid, g: DScalarGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param e The \e %DScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DScalarGrid, e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DScalarGrid instance.
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DScalarGrid) -> str: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def __pos__(self: DScalarGrid) -> DScalarGrid: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DScalarGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %DScalarGrid instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DScalarGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DScalarGrid instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DScalarGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %DScalarGrid instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DScalarGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %DScalarGrid instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DScalarGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDGridExpression: pass

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
