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
# \brief A regular spatial grid storing double-precision floating-point values.
# 
class DRegularGrid(DSpatialGrid, Math.DRegularSpatialGrid):

    ##
    # \brief Initializes a copy of the \c %DRegularGrid instance \a grid.
    # \param grid The \c %DRegularGrid instance to copy.
    # 
    def __init__(grid: DRegularGrid) -> None: pass

    ##
    # \brief Constructs the grid with the specified anisotropic per-axis step sizes initialized to the supplied grid data.
    # 
    # \param data The grid data container.
    # \param xs The step size along the x-axis.
    # \param ys The step size along the y-axis.
    # \param zs The step size along the z-axis.
    # 
    def __init__(data: Math.DGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Constructs the grid with the isotropic step size <em>s</em> and the supplied grid data.
    # 
    # \param data The grid data container.
    # \param s The step size used on every axis.
    # 
    def __init__(data: Math.DGrid, s: float) -> None: pass

    ##
    # \brief Constructs an empty grid with the specified anisotropic per-axis step sizes.
    # 
    # \param xs The step size along the x-axis.
    # \param ys The step size along the y-axis.
    # \param zs The step size along the z-axis.
    # 
    def __init__(xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Constructs an empty grid with the specified isotropic step size <em>s</em> on all three axes.
    # 
    # \param s The step size used on every axis.
    # 
    def __init__(s: float) -> None: pass

    ##
    # \brief Writes the world space 3D position of the cell at (<em>i</em>, <em>j</em>, <em>k</em>) into <em>coords</em>.
    # 
    # \param i The zero-based cell index along the x-axis.
    # \param j The zero-based cell index along the y-axis.
    # \param k The zero-based cell index along the z-axis.
    # \param coords The output vector receiving the world space 3D position.
    # 
    def getCoordinates(i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief Outputs the world space 3D position of the cell with linear index <em>i</em> into <em>coords</em>.
    # 
    # \param i The zero-based linear cell index.
    # \param coords The output vector receiving the xyz-coordinates.
    # 
    def getCoordinates(i: int, coords: object) -> None: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to the underlying grid data without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: Math.ConstFGridExpression) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to the underlying grid data without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: Math.ConstDGridExpression) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to the underlying grid data without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: object) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DRegularSpatialGrid instance \a g.
    # \param g The \c %DRegularSpatialGrid instance to copy.
    # \return \a self
    # 
    def assign(g: Math.DRegularSpatialGrid) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Returns the number of cells along the x-axis.
    # 
    # \return The number of cells along the x-axis.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the number of cells along the y-axis.
    # 
    # \return The number of cells along the y-axis.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Returns the number of cells along the z-axis.
    # 
    # \return The number of cells along the z-axis.
    # 
    def getSize3() -> int: pass

    ##
    # \brief Tells whether the grid is empty (zero cells along any dimension).
    # 
    # \return <tt>True</tt> if the grid is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    def getElement(i: int, j: int, k: int) -> float: pass

    def getElement(i: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Returns the total number of cells of the grid.
    # 
    # \return The total cell count.
    # 
    def getSize() -> int: pass

    def swap(g: Math.DRegularSpatialGrid) -> None: pass

    def setElement(i: int, j: int, k: int, v: float) -> None: pass

    def setElement(i: int, v: float) -> None: pass

    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    def __getitem__(ijk: tuple) -> float: pass

    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    def __setitem__(ijk: tuple, v: float) -> None: pass

    def __setitem__(i: int, v: float) -> None: pass

    def __delitem__(key: Base.LookupKey) -> bool: pass

    def __len__() -> int: pass

    ##
    # \brief Returns a reference to the value of cell at (<em>i</em>, <em>j</em>, <em>k</em>).
    # 
    # \param i The zero-based cell index along the x-axis.
    # \param j The zero-based cell index along the y-axis.
    # \param k The zero-based cell index along the z-axis.
    # 
    # \return A reference to the cell value.
    # 
    def __call__(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Returns a reference to the value of the cell at the linear index <em>i</em>.
    # 
    # \param i The zero-based linear cell index.
    # 
    # \return A reference to the cell value.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param g The \c %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: Math.DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: Math.ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \c %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: Math.DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstDGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: Math.ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %DRegularGrid instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> Math.DRegularSpatialGrid: pass

    def __neg__() -> Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %Math.ConstDGridExpression instance holding the result of the addition.
    # 
    def __add__(e: Math.ConstDGridExpression) -> Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %DRegularGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: Math.ConstDGridExpression) -> Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %Math.ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %Math.ConstDGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %Math.ConstDGridExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> Math.ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %Math.ConstDGridExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> Math.ConstDGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param g Specifies the second addend.
    # \return The updated \c %Math.DRegularSpatialGrid instance \a self.
    # 
    def __iadd__(g: Math.DRegularSpatialGrid) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %Math.DRegularSpatialGrid instance \a self.
    # 
    def __iadd__(e: Math.ConstDGridExpression) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param g Specifies the subtrahend.
    # \return The updated \c %Math.DRegularSpatialGrid instance \a self.
    # 
    def __isub__(g: Math.DRegularSpatialGrid) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %Math.DRegularSpatialGrid instance \a self.
    # 
    def __isub__(e: Math.ConstDGridExpression) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %Math.DRegularSpatialGrid instance \a self.
    # 
    def __imul__(t: float) -> Math.DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %Math.DRegularSpatialGrid instance \a self.
    # 
    def __idiv__(t: float) -> Math.DRegularSpatialGrid: pass

    def __itruediv__(t: float) -> Math.DRegularSpatialGrid: pass

    def __getstate__() -> tuple: pass

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
