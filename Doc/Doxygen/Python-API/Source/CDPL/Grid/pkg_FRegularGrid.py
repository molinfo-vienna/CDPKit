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
class FRegularGrid(FSpatialGrid, CDPL.Math.FRegularSpatialGrid):

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param grid 
    #
    def __init__(grid: FRegularGrid) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param data 
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(data: CDPL.Math.FGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param data 
    # \param s 
    #
    def __init__(data: CDPL.Math.FGrid, s: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularGrid instance.
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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstFGridExpression instance \a e.
    # \param e The \e %ConstFGridExpression instance to copy.
    # \return \a self
    #
    def assign(e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstDGridExpression instance \a e.
    # \param e The \e %ConstDGridExpression instance to copy.
    # \return \a self
    #
    def assign(e: CDPL.Math.ConstDGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %object instance \a e.
    # \param e The \e %object instance to copy.
    # \return \a self
    #
    def assign(e: object) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularSpatialGrid instance \a g.
    # \param g The \e %FRegularSpatialGrid instance to copy.
    # \return \a self
    #
    def assign(g: CDPL.Math.FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

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
    def swap(g: CDPL.Math.FRegularSpatialGrid) -> None: pass

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
    # \param g The \e %FRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(g: CDPL.Math.FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: CDPL.Math.ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \e %FRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(g: CDPL.Math.FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: CDPL.Math.ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FRegularGrid instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %CDPL.Math.ConstFGridExpression instance holding the result of the addition.
    #
    def __add__(e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %FRegularGrid instance holding the result of the subtraction.
    #
    def __sub__(e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %CDPL.Math.ConstFGridExpression instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %CDPL.Math.ConstFGridExpression instance holding the result of the division.
    #
    def __div__(t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: float) -> CDPL.Math.ConstFGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param g Specifies the second addend.
    # \return The updated \e %CDPL.Math.FRegularSpatialGrid instance \a self.
    #
    def __iadd__(g: CDPL.Math.FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %CDPL.Math.FRegularSpatialGrid instance \a self.
    #
    def __iadd__(e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param g Specifies the subtrahend.
    # \return The updated \e %CDPL.Math.FRegularSpatialGrid instance \a self.
    #
    def __isub__(g: CDPL.Math.FRegularSpatialGrid) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %CDPL.Math.FRegularSpatialGrid instance \a self.
    #
    def __isub__(e: CDPL.Math.ConstFGridExpression) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %CDPL.Math.FRegularSpatialGrid instance \a self.
    #
    def __imul__(t: float) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %CDPL.Math.FRegularSpatialGrid instance \a self.
    #
    def __idiv__(t: float) -> CDPL.Math.FRegularSpatialGrid: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> CDPL.Math.FRegularSpatialGrid: pass

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
