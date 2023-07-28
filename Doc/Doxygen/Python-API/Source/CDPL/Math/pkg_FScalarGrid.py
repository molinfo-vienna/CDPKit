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
class FScalarGrid(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FScalarGrid instance.
    # \param self The \e %FScalarGrid instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FScalarGrid instance.
    # \param self The \e %FScalarGrid instance to initialize.
    # \param g 
    # 
    def __init__(g: FScalarGrid) -> None: pass

    ##
    # \brief Initializes the \e %FScalarGrid instance.
    # \param self The \e %FScalarGrid instance to initialize.
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
    # \param self The \e %FScalarGrid instance this method is called upon.
    # 
    # Different Python \e %FScalarGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FScalarGrid instances \e a and \e b reference different C++ objects. 
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
    # \brief 
    # \param g 
    # \return 
    #
    def assign(g: FScalarGrid) -> FScalarGrid: pass

    ##
    # \brief 
    # \param g 
    #
    def swap(g: FScalarGrid) -> None: pass

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
    # \param self The \e %FScalarGrid instance this method is called upon.
    # \param g The \e %FScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: FScalarGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FScalarGrid instance this method is called upon.
    # \param e The \e %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %FScalarGrid instance this method is called upon.
    # \param g The \e %FScalarGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: FScalarGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FScalarGrid instance this method is called upon.
    # \param e The \e %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FScalarGrid instance.
    # \param self The \e %FScalarGrid instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> FScalarGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FScalarGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstFGridExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FScalarGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FScalarGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FScalarGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstFGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FScalarGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstFGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> ConstFGridExpression: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
