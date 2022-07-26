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
class DRegularGrid(DSpatialGrid, CDPL.Math.DRegularSpatialGrid):

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param grid 
    #
    def __init__(self: object, grid: DRegularGrid) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param data 
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(self: object, data: CDPL.Math.DGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param data 
    # \param s 
    #
    def __init__(self: object, data: CDPL.Math.DGrid, s: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(self: object, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param coords 
    #
    def getCoordinates(self: DRegularGrid, i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param coords 
    #
    def getCoordinates(self: DRegularGrid, i: int, coords: object) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularGrid instance \a e.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %DRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularGrid instance \a e.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %DRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularGrid instance \a e.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %DRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, e: object) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularGrid instance \a g.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param g The \e %DRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, g: CDPL.Math.DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize1(self: DRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize2(self: DRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize3(self: DRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def isEmpty(self: DRegularGrid) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(self: DRegularSpatialGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: DRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def toArray(self: DRegularSpatialGrid) -> object: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize(self: DRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param g 
    #
    def swap(self: DRegularSpatialGrid, g: CDPL.Math.DRegularSpatialGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(self: DRegularSpatialGrid, i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: DRegularSpatialGrid, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param ijk 
    # \return 
    #
    def __getitem__(self: DRegularSpatialGrid, ijk: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: DRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: DRegularGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: DRegularGrid, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param ijk 
    # \param v 
    #
    def __setitem__(self: DRegularSpatialGrid, ijk: tuple, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: DRegularSpatialGrid, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: DRegularGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def __len__(self: DRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def __call__(self: DRegularSpatialGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: DRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param g The \e %DRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DRegularSpatialGrid, g: CDPL.Math.DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %DRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DRegularSpatialGrid, e: CDPL.Math.ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param g The \e %DRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DRegularSpatialGrid, g: CDPL.Math.DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %DRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DRegularSpatialGrid, e: CDPL.Math.ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DRegularSpatialGrid) -> str: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def __pos__(self: DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DRegularGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %DRegularGrid instance holding the result of the addition.
    #
    def __add__(self: object, e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DRegularGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DRegularGrid instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DRegularGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %DRegularGrid instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DRegularGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %DRegularGrid instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place addend.
    # \param g Specifies the second addend.
    # \return The updated \e %DRegularGrid instance \a self.
    #
    def __iadd__(self: DRegularSpatialGrid, g: CDPL.Math.DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DRegularGrid instance \a self.
    #
    def __iadd__(self: DRegularSpatialGrid, e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place minuend.
    # \param g Specifies the subtrahend.
    # \return The updated \e %DRegularGrid instance \a self.
    #
    def __isub__(self: DRegularSpatialGrid, g: CDPL.Math.DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DRegularGrid instance \a self.
    #
    def __isub__(self: DRegularSpatialGrid, e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DRegularGrid instance \a self.
    #
    def __imul__(self: DRegularSpatialGrid, t: float) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DRegularGrid instance \a self.
    #
    def __idiv__(self: DRegularSpatialGrid, t: float) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DRegularSpatialGrid, t: float) -> CDPL.Math.DRegularSpatialGrid: pass

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
