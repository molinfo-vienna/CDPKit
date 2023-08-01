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
# \brief An unbounded dense grid holding floating point values of type <tt>double</tt>.
# 
class DGrid(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DGrid instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DGrid instance with a copy of the state of the \e %DGrid instance \a g.
    # \param g The \e %DGrid instance to copy.
    # 
    def __init__(g: DGrid) -> None: pass

    ##
    # \brief Initializes the \e %DGrid instance.
    # \param m 
    # \param n 
    # \param o 
    # 
    def __init__(m: int, n: int, o: int) -> None: pass

    ##
    # \brief Initializes the \e %DGrid instance.
    # \param m 
    # \param n 
    # \param o 
    # \param v 
    # 
    def __init__(m: int, n: int, o: int, v: float) -> None: pass

    ##
    # \brief Initializes the \e %DGrid instance.
    # \param e 
    # 
    def __init__(e: ConstFGridExpression) -> None: pass

    ##
    # \brief Initializes the \e %DGrid instance.
    # \param e 
    # 
    def __init__(e: ConstDGridExpression) -> None: pass

    ##
    # \brief Initializes the \e %DGrid instance.
    # \param e 
    # 
    def __init__(e: object) -> None: pass

    ##
    # \brief 
    # \param m 
    # \param n 
    # \param o 
    # \param preserve 
    # \param v 
    #
    def resize(m: int, n: int, o: int, preserve: bool = True, v: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def clear(v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %DGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstFGridExpression instance \a e.
    # \param e The \e %ConstFGridExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstFGridExpression) -> DGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstDGridExpression instance \a e.
    # \param e The \e %ConstDGridExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstDGridExpression) -> DGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %object instance \a e.
    # \param e The \e %object instance to copy.
    # \return \a self
    # 
    def assign(e: object) -> DGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGrid instance \a g.
    # \param g The \e %DGrid instance to copy.
    # \return \a self
    # 
    def assign(g: DGrid) -> DGrid: pass

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
    #
    def swap(g: DGrid) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: float) -> None: pass

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
    # \param g The \e %DGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: DGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \e %DGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: DGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DGrid instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> DGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %ConstDGridExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %DGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %ConstDGridExpression instance holding the result of the division.
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
    # \param ijk 
    # \param v 
    #
    def __setitem__(ijk: tuple, v: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param g Specifies the second addend.
    # \return The updated \e %DGrid instance \a self.
    # 
    def __iadd__(g: DGrid) -> DGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %DGrid instance \a self.
    # 
    def __iadd__(e: ConstDGridExpression) -> DGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param g Specifies the subtrahend.
    # \return The updated \e %DGrid instance \a self.
    # 
    def __isub__(g: DGrid) -> DGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DGrid instance \a self.
    # 
    def __isub__(e: ConstDGridExpression) -> DGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %DGrid instance \a self.
    # 
    def __imul__(t: float) -> DGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %DGrid instance \a self.
    # 
    def __idiv__(t: float) -> DGrid: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> DGrid: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
