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
# \brief RegularGrid.
# 
class DRegularGrid(DSpatialGrid, CDPL.Math.DRegularSpatialGrid):

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param grid 
    # 
    def __init__(grid: DRegularGrid) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param data 
    # \param xs 
    # \param ys 
    # \param zs 
    # 
    def __init__(data: CDPL.Math.DGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param data 
    # \param s 
    # 
    def __init__(data: CDPL.Math.DGrid, s: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param xs 
    # \param ys 
    # \param zs 
    # 
    def __init__(xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance to initialize.
    # \param s 
    # 
    def __init__(s: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \param coords 
    #
    def getCoordinates(i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param coords 
    #
    def getCoordinates(i: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: object) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param g 
    # \return 
    #
    def assign(g: CDPL.Math.DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

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
    def swap(g: CDPL.Math.DRegularSpatialGrid) -> None: pass

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
    # \param key 
    # \return 
    #
    def __getitem__(key: CDPL.Base.LookupKey) -> CDPL.Base.Any: pass

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
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: CDPL.Base.LookupKey, value: CDPL.Base.Any) -> None: pass

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
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

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
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param g The \e %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: CDPL.Math.DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: CDPL.Math.ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param g The \e %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: CDPL.Math.DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \param e The \e %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: CDPL.Math.ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DRegularGrid instance.
    # \param self The \e %DRegularGrid instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DRegularGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %CDPL.Math.ConstDGridExpression instance holding the result of the addition.
    # 
    def __add__(e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DRegularGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DRegularGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DRegularGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %CDPL.Math.ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DRegularGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %CDPL.Math.ConstDGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> CDPL.Math.ConstDGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place addend.
    # \param g Specifies the second addend.
    # \return The updated \e %CDPL.Math.DRegularSpatialGrid instance \a self.
    # 
    def __iadd__(g: CDPL.Math.DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %CDPL.Math.DRegularSpatialGrid instance \a self.
    # 
    def __iadd__(e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place minuend.
    # \param g Specifies the subtrahend.
    # \return The updated \e %CDPL.Math.DRegularSpatialGrid instance \a self.
    # 
    def __isub__(g: CDPL.Math.DRegularSpatialGrid) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %CDPL.Math.DRegularSpatialGrid instance \a self.
    # 
    def __isub__(e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %CDPL.Math.DRegularSpatialGrid instance \a self.
    # 
    def __imul__(t: float) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DRegularGrid instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %CDPL.Math.DRegularSpatialGrid instance \a self.
    # 
    def __idiv__(t: float) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> CDPL.Math.DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __getstate__() -> tuple: pass

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
