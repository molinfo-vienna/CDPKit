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
class FGrid(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param self The \e %FGrid instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param self The \e %FGrid instance to initialize.
    # \param g 
    #
    def __init__(self: object, g: FGrid) -> None: pass

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param self The \e %FGrid instance to initialize.
    # \param m 
    # \param n 
    # \param o 
    #
    def __init__(self: object, m: int, n: int, o: int) -> None: pass

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param self The \e %FGrid instance to initialize.
    # \param m 
    # \param n 
    # \param o 
    # \param v 
    #
    def __init__(self: object, m: int, n: int, o: int, v: float) -> None: pass

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param arg1 The \e %FGrid instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstFGridExpression) -> None: pass

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param arg1 The \e %FGrid instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: ConstDGridExpression) -> None: pass

    ##
    # \brief Initializes the \e %FGrid instance.
    # \param arg1 The \e %FGrid instance to initialize.
    # \param e 
    #
    def __init__(arg1: object, e: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param m 
    # \param n 
    # \param o 
    # \param preserve 
    # \param v 
    #
    def resize(self: FGrid, m: int, n: int, o: int, preserve: bool = True, v: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param v 
    #
    def clear(self: FGrid, v: float = 0.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FGrid instance this method is called upon.
    #
    # Different Python \e %FGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FGrid) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FGrid instance \a e.
    # \param self The \e %FGrid instance this method is called upon.
    # \param e The \e %FGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FGrid, e: ConstFGridExpression) -> FGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FGrid instance \a e.
    # \param self The \e %FGrid instance this method is called upon.
    # \param e The \e %FGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FGrid, e: ConstDGridExpression) -> FGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FGrid instance \a e.
    # \param self The \e %FGrid instance this method is called upon.
    # \param e The \e %FGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FGrid, e: object) -> FGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FGrid instance \a g.
    # \param self The \e %FGrid instance this method is called upon.
    # \param g The \e %FGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FGrid, g: FGrid) -> FGrid: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def getSize1(self: FGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def getSize2(self: FGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def getSize3(self: FGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FGrid) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(self: FGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: FGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def toArray(self: FGrid) -> object: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def getSize(self: FGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param g 
    #
    def swap(self: FGrid, g: FGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(self: FGrid, i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: FGrid, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def __call__(self: FGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: FGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param ijk 
    # \return 
    #
    def __getitem__(self: FGrid, ijk: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: FGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def __len__(self: FGrid) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param self The \e %FGrid instance this method is called upon.
    # \param g The \e %FGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FGrid, g: FGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FGrid instance this method is called upon.
    # \param e The \e %FGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FGrid, e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %FGrid instance this method is called upon.
    # \param g The \e %FGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FGrid, g: FGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FGrid instance this method is called upon.
    # \param e The \e %FGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FGrid, e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FGrid instance.
    # \param self The \e %FGrid instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FGrid) -> str: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def __pos__(self: FGrid) -> FGrid: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FGrid instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FGrid instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FGrid instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FGrid instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstFGridExpression: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstFGridExpression: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstFGridExpression: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param ijk 
    # \param v 
    #
    def __setitem__(self: FGrid, ijk: tuple, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: FGrid, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param self The \e %FGrid instance acting as in-place addend.
    # \param g Specifies the second addend.
    # \return The updated \e %FGrid instance \a self.
    #
    def __iadd__(self: FGrid, g: FGrid) -> FGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FGrid instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FGrid instance \a self.
    #
    def __iadd__(self: FGrid, e: ConstFGridExpression) -> FGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param self The \e %FGrid instance acting as in-place minuend.
    # \param g Specifies the subtrahend.
    # \return The updated \e %FGrid instance \a self.
    #
    def __isub__(self: FGrid, g: FGrid) -> FGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FGrid instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FGrid instance \a self.
    #
    def __isub__(self: FGrid, e: ConstFGridExpression) -> FGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FGrid instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FGrid instance \a self.
    #
    def __imul__(self: FGrid, t: float) -> FGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FGrid instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FGrid instance \a self.
    #
    def __idiv__(self: FGrid, t: float) -> FGrid: pass

    ##
    # \brief 
    # \param self The \e %FGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FGrid, t: float) -> FGrid: pass

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
