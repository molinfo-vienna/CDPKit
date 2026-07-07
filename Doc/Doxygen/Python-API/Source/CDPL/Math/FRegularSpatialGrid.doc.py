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
# \brief Unbounded dense regular grid storing floating-point values of type <tt>float</tt>.
# 
class FRegularSpatialGrid(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %FRegularSpatialGrid instance \a grid.
    # \param grid The \c %FRegularSpatialGrid instance to copy.
    # 
    def __init__(grid: FRegularSpatialGrid) -> None: pass

    ##
    # \brief Constructs the grid with anisotropic per-axis step sizes initialized to the supplied grid data.
    # 
    # \param data The grid data container.
    # \param xs The step size along the x-axis.
    # \param ys The step size along the y-axis.
    # \param zs The step size along the z-axis.
    # 
    def __init__(data: FGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Constructs the grid with isotropic step size <em>s</em> and the supplied grid data.
    # 
    # \param data The grid data container.
    # \param s The step size used on every axis.
    # 
    def __init__(data: FGrid, s: float) -> None: pass

    ##
    # \brief Constructs an empty grid with anisotropic per-axis step sizes.
    # 
    # \param xs The step size along the x-axis.
    # \param ys The step size along the y-axis.
    # \param zs The step size along the z-axis.
    # 
    def __init__(xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Constructs an empty grid with isotropic step size <em>s</em> on all three axes.
    # 
    # \param s The step size used on every axis.
    # 
    def __init__(s: float) -> None: pass

    ##
    # \brief Resizes the grid to <em>m&times;n&times;o</em> cells.
    # 
    # \param m The new size in the first dimension.
    # \param n The new size in the second dimension.
    # \param o The new size in the third dimension.
    # \param preserve If <tt>True</tt>, existing cell values are kept where the indices remain valid. If <tt>False</tt>, all cells are set to <em>v</em>.
    # \param v The fill value used for newly added cells (and for all cells if <em>preserve</em> is <tt>False</tt>).
    # 
    def resize(m: int, n: int, o: int, preserve: bool = True, v: float = 0.0) -> None: pass

    ##
    # \brief Sets every cell of the grid to the value <em>v</em>.
    # 
    # \param v The fill value.
    # 
    def clear(v: float = 0.0) -> None: pass

    ##
    # \brief Returns the spatial extent of the grid along the x-axis ( \f$ (\mathrm{size}_1 - 1) \cdot \mathrm{xStep} \f$ for non-empty grids).
    # 
    # \return The x-axis extent.
    # 
    def getXExtent() -> float: pass

    ##
    # \brief Returns the spatial extent of the grid along the y-axis.
    # 
    # \return The y-axis extent.
    # 
    def getYExtent() -> float: pass

    ##
    # \brief Returns the spatial extent of the grid along the z-axis.
    # 
    # \return The z-axis extent.
    # 
    def getZExtent() -> float: pass

    ##
    # \brief Returns the per-cell step size along the x-axis.
    # 
    # \return The x-axis step size.
    # 
    def getXStepSize() -> float: pass

    ##
    # \brief Returns the per-cell step size along the y-axis.
    # 
    # \return The y-axis step size.
    # 
    def getYStepSize() -> float: pass

    ##
    # \brief Returns the per-cell step size along the z-axis.
    # 
    # \return The z-axis step size.
    # 
    def getZStepSize() -> float: pass

    ##
    # \brief Sets the per-cell step size along the x-axis to <em>xs</em>.
    # 
    # \param xs The new x-axis step size.
    # 
    def setXStepSize(xs: float) -> None: pass

    ##
    # \brief Sets the per-cell step size along the y-axis to <em>ys</em>.
    # 
    # \param ys The new y-axis step size.
    # 
    def setYStepSize(ys: float) -> None: pass

    ##
    # \brief Sets the per-cell step size along the z-axis to <em>zs</em>.
    # 
    # \param zs The new z-axis step size.
    # 
    def setZStepSize(zs: float) -> None: pass

    ##
    # \brief Returns a mutable reference to the underlying grid data container.
    # 
    # \return A mutable reference to the grid data.
    # 
    def getData() -> FGrid: pass

    ##
    # \brief Sets the cell-index to world-coordinate transformation to <em>xform</em> and caches its inverse.
    # 
    # \param xform The new transformation.
    # 
    # \throw Base.CalculationFailed if the transformation cannot be inverted (only when math checks are enabled).
    # 
    def setCoordinatesTransform(xform: Matrix4F) -> None: pass

    ##
    # \brief Returns the coordinate transformation mapping cell-index coordinates to world coordinates.
    # 
    # \return A reference to the transformation matrix.
    # 
    def getCoordinatesTransform() -> Matrix4F: pass

    ##
    # \brief Writes the world-space 3D position of the cell at (<em>i</em>, <em>j</em>, <em>k</em>) into <em>coords</em>.
    # 
    # \param i The first dimension cell index.
    # \param j The second dimension cell index.
    # \param k The third dimension cell index.
    # \param coords The output vector receiving the X/Y/Z position.
    # 
    def getCoordinates(i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief Writes the world-space 3D position of the cell with linear index <em>i</em> into <em>coords</em>.
    # 
    # \param i The zero-based linear cell index.
    # \param coords The output vector receiving the X/Y/Z position.
    # 
    def getCoordinates(i: int, coords: object) -> None: pass

    ##
    # \brief Writes the local-space 3D position of the cell at (<em>i</em>, <em>j</em>, <em>k</em>) into <em>coords</em>.
    # 
    # Local coordinates are centered at the grid origin (the cell-center cell-index coordinate system before applying the world-space transformation).
    # 
    # \param i The first dimension cell index.
    # \param j The second dimension cell index.
    # \param k The third dimension cell index.
    # \param coords The output vector receiving the local X/Y/Z position.
    # 
    def getLocalCoordinates(i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief Transforms the world-space point <em>world_coords</em> into the grid's local coordinate frame and stores the result in <em>local_coords</em>.
    # 
    # \param world_coords The input world-space 3D position.
    # \param local_coords The output vector receiving the local-frame 3D position.
    # 
    def getLocalCoordinates(world_coords: Vector3F, local_coords: object) -> None: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: Vector3F) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: Vector3D) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: Vector3L) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: Vector3UL) -> bool: pass

    ##
    # \brief Tells whether the world-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The world-space 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pos: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: Vector3F) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: Vector3D) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: Vector3L) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: Vector3UL) -> bool: pass

    ##
    # \brief Tells whether the local-space point <em>pos</em> lies within the grid bounds.
    # 
    # \param pos The local-frame 3D position to test.
    # 
    # \return <tt>True</tt> if <em>pos</em> is inside the grid, and <tt>False</tt> otherwise.
    # 
    def containsLocalPoint(pos: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: Vector3F, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: ConstFVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: Vector3D, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: ConstDVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: Vector3L, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: ConstLVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: Vector3UL, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the world-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The world-space 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getContainingCell(pos: ConstULVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: Vector3F, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: ConstFVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: Vector3D, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: ConstDVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: Vector3L, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: ConstLVectorExpression, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: Vector3UL, indices: object) -> None: pass

    ##
    # \brief Writes the (i, j, k) cell indices of the cell containing the local-space point <em>pos</em> into <em>indices</em>.
    # 
    # \param pos The local-frame 3D position.
    # \param indices The output vector receiving the three cell indices.
    # 
    def getLocalContainingCell(pos: ConstULVectorExpression, indices: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FRegularSpatialGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FRegularSpatialGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to the underlying grid data without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to the underlying grid data without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to the underlying grid data without intermediate temporary.
    # 
    # \param e The source grid expression.
    # 
    # \return \a self
    # 
    def assign(e: object) -> FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FRegularSpatialGrid instance \a g.
    # \param g The \c %FRegularSpatialGrid instance to copy.
    # \return \a self
    # 
    def assign(g: FRegularSpatialGrid) -> FRegularSpatialGrid: pass

    ##
    # \brief Returns the size of the grid along the first dimension.
    # 
    # \return The size in the first dimension.
    # 
    def getSize1() -> int: pass

    ##
    # \brief Returns the size of the grid along the second dimension.
    # 
    # \return The size in the second dimension.
    # 
    def getSize2() -> int: pass

    ##
    # \brief Returns the size of the grid along the third dimension.
    # 
    # \return The size in the third dimension.
    # 
    def getSize3() -> int: pass

    ##
    # \brief Tells whether the grid is empty (zero cells along any dimension).
    # 
    # \return <tt>True</tt> if the grid is empty, and <tt>False</tt> otherwise.
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
    # \brief Returns the total number of cells of the grid.
    # 
    # \return The total cell count.
    # 
    def getSize() -> int: pass

    ##
    # \brief 
    # \param g 
    #
    def swap(g: FRegularSpatialGrid) -> None: pass

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
    # \brief Returns a reference to the cell at the (<em>i</em>, <em>j</em>, <em>k</em>) position.
    # 
    # \param i The zero-based first dimension index.
    # \param j The zero-based second dimension index.
    # \param k The zero-based third dimension index.
    # 
    # \return A reference to the cell value.
    # 
    def __call__(i: int, j: int, k: int) -> float: pass

    ##
    # \brief Returns a reference to the cell at the linear index <em>i</em>.
    # 
    # \param i The zero-based linear cell index.
    # 
    # \return A reference to the cell value.
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
    # \param g The \c %FRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(g: FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \c %FRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(g: FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %FRegularSpatialGrid instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> FRegularSpatialGrid: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstFGridExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %FRegularSpatialGrid instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstFGridExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstFGridExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstFGridExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstFGridExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFGridExpression: pass

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
    # \return The updated \c %FRegularSpatialGrid instance \a self.
    # 
    def __iadd__(g: FRegularSpatialGrid) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %FRegularSpatialGrid instance \a self.
    # 
    def __iadd__(e: ConstFGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param g Specifies the subtrahend.
    # \return The updated \c %FRegularSpatialGrid instance \a self.
    # 
    def __isub__(g: FRegularSpatialGrid) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %FRegularSpatialGrid instance \a self.
    # 
    def __isub__(e: ConstFGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %FRegularSpatialGrid instance \a self.
    # 
    def __imul__(t: float) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %FRegularSpatialGrid instance \a self.
    # 
    def __idiv__(t: float) -> FRegularSpatialGrid: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FRegularSpatialGrid: pass

    data = property(getData)

    coordsTransform = property(getCoordinatesTransform, setCoordinatesTransform)

    xStepSize = property(getXStepSize, setXStepSize)

    yStepSize = property(getYStepSize, setYStepSize)

    zStepSize = property(getZStepSize, setZStepSize)

    xExtent = property(getXExtent)

    yExtent = property(getYExtent)

    zExtent = property(getZExtent)

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    size3 = property(getSize3)
