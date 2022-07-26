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
class FRegularGrid(FSpatialGrid, CDPL.Math.FRegularSpatialGrid):

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param self The \e %FRegularGrid instance to initialize.
    # \param grid 
    #
    def __init__(self: object, grid: FRegularGrid) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param self The \e %FRegularGrid instance to initialize.
    # \param data 
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(self: object, data: CDPL.Math.FGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param self The \e %FRegularGrid instance to initialize.
    # \param data 
    # \param s 
    #
    def __init__(self: object, data: CDPL.Math.FGrid, s: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param self The \e %FRegularGrid instance to initialize.
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(self: object, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param self The \e %FRegularGrid instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param coords 
    #
    def getCoordinates(self: FRegularGrid, i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param coords 
    #
    def getCoordinates(self: FRegularGrid, i: int, coords: object) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularGrid instance \a e.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param e The \e %FRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FRegularSpatialGrid, e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularGrid instance \a e.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param e The \e %FRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FRegularSpatialGrid, e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularGrid instance \a e.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param e The \e %FRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FRegularSpatialGrid, e: object) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularGrid instance \a g.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param g The \e %FRegularGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FRegularSpatialGrid, g: CDPL.Math.FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize1(self: FRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize2(self: FRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize3(self: FRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def isEmpty(self: FRegularGrid) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(self: FRegularSpatialGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: FRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def toArray(self: FRegularSpatialGrid) -> object: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def getSize(self: FRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param g 
    #
    def swap(self: FRegularSpatialGrid, g: CDPL.Math.FRegularSpatialGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(self: FRegularSpatialGrid, i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: FRegularSpatialGrid, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param ijk 
    # \return 
    #
    def __getitem__(self: FRegularSpatialGrid, ijk: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: FRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: FRegularGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: FRegularGrid, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param ijk 
    # \param v 
    #
    def __setitem__(self: FRegularSpatialGrid, ijk: tuple, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: FRegularSpatialGrid, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: FRegularGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def __len__(self: FRegularGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def __call__(self: FRegularSpatialGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: FRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param g The \e %FRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FRegularSpatialGrid, g: CDPL.Math.FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param e The \e %FRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: FRegularSpatialGrid, e: CDPL.Math.ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param g The \e %FRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FRegularSpatialGrid, g: CDPL.Math.FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param e The \e %FRegularGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: FRegularSpatialGrid, e: CDPL.Math.ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FRegularGrid instance.
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: FRegularSpatialGrid) -> str: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def __pos__(self: FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %FRegularGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %FRegularGrid instance holding the result of the addition.
    #
    def __add__(self: object, e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %FRegularGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %FRegularGrid instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %FRegularGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %FRegularGrid instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %FRegularGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %FRegularGrid instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param self The \e %FRegularGrid instance acting as in-place addend.
    # \param g Specifies the second addend.
    # \return The updated \e %FRegularGrid instance \a self.
    #
    def __iadd__(self: FRegularSpatialGrid, g: CDPL.Math.FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FRegularGrid instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FRegularGrid instance \a self.
    #
    def __iadd__(self: FRegularSpatialGrid, e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param self The \e %FRegularGrid instance acting as in-place minuend.
    # \param g Specifies the subtrahend.
    # \return The updated \e %FRegularGrid instance \a self.
    #
    def __isub__(self: FRegularSpatialGrid, g: CDPL.Math.FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FRegularGrid instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FRegularGrid instance \a self.
    #
    def __isub__(self: FRegularSpatialGrid, e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FRegularGrid instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FRegularGrid instance \a self.
    #
    def __imul__(self: FRegularSpatialGrid, t: float) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FRegularGrid instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FRegularGrid instance \a self.
    #
    def __idiv__(self: FRegularSpatialGrid, t: float) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %FRegularGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FRegularSpatialGrid, t: float) -> CDPL.Math.FRegularSpatialGrid: pass

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
