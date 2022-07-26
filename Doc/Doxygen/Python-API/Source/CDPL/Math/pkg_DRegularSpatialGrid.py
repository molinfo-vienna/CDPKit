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
class DRegularSpatialGrid(Boost.Python.instance):

    ##
    # \brief 
    #
    class DataMode(Boost.Python.enum):

        ##
        # \brief CELL.
        #
        CELL = 0

        ##
        # \brief POINT.
        #
        POINT = 1

    ##
    # \brief Initializes the \e %DRegularSpatialGrid instance.
    # \param self The \e %DRegularSpatialGrid instance to initialize.
    # \param grid 
    #
    def __init__(self: object, grid: DRegularSpatialGrid) -> None: pass

    ##
    # \brief Initializes the \e %DRegularSpatialGrid instance.
    # \param self The \e %DRegularSpatialGrid instance to initialize.
    # \param data 
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(self: object, data: DGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularSpatialGrid instance.
    # \param self The \e %DRegularSpatialGrid instance to initialize.
    # \param data 
    # \param s 
    #
    def __init__(self: object, data: DGrid, s: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularSpatialGrid instance.
    # \param self The \e %DRegularSpatialGrid instance to initialize.
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(self: object, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %DRegularSpatialGrid instance.
    # \param self The \e %DRegularSpatialGrid instance to initialize.
    # \param s 
    #
    def __init__(self: object, s: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param m 
    # \param n 
    # \param o 
    # \param preserve 
    # \param v 
    #
    def resize(self: DRegularSpatialGrid, m: int, n: int, o: int, preserve: bool = True, v: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param v 
    #
    def clear(self: DRegularSpatialGrid, v: float = 0.0) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getDataMode(self: DRegularSpatialGrid) -> DataMode: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param mode 
    #
    def setDataMode(self: DRegularSpatialGrid, mode: DataMode) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getXExtent(self: DRegularSpatialGrid) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getYExtent(self: DRegularSpatialGrid) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getZExtent(self: DRegularSpatialGrid) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getXStepSize(self: DRegularSpatialGrid) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getYStepSize(self: DRegularSpatialGrid) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getZStepSize(self: DRegularSpatialGrid) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param xs 
    #
    def setXStepSize(self: DRegularSpatialGrid, xs: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param ys 
    #
    def setYStepSize(self: DRegularSpatialGrid, ys: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param zs 
    #
    def setZStepSize(self: DRegularSpatialGrid, zs: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getData(self: DRegularSpatialGrid) -> DGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param xform 
    #
    def setCoordinatesTransform(self: DRegularSpatialGrid, xform: Matrix4D) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getCoordinatesTransform(self: DRegularSpatialGrid) -> Matrix4D: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param coords 
    #
    def getCoordinates(self: DRegularSpatialGrid, i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param coords 
    #
    def getCoordinates(self: DRegularSpatialGrid, i: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param coords 
    #
    def getLocalCoordinates(self: DRegularSpatialGrid, i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param world_coords 
    # \param local_coords 
    #
    def getLocalCoordinates(self: DRegularSpatialGrid, world_coords: Vector3D, local_coords: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: Vector3F) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: Vector3D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: Vector3L) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: Vector3UL) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsPoint(self: DRegularSpatialGrid, pos: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: Vector3F) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: Vector3D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: Vector3L) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: Vector3UL) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \return 
    #
    def containsLocalPoint(self: DRegularSpatialGrid, pos: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: Vector3F, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: ConstFVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: Vector3D, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: ConstDVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: Vector3L, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: ConstLVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: Vector3UL, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getContainingCell(self: DRegularSpatialGrid, pos: ConstULVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: Vector3F, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: ConstFVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: Vector3D, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: ConstDVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: Vector3L, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: ConstLVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: Vector3UL, indices: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(self: DRegularSpatialGrid, pos: ConstULVectorExpression, indices: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    #
    # Different Python \e %DRegularSpatialGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DRegularSpatialGrid instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DRegularSpatialGrid) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularSpatialGrid instance \a e.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param e The \e %DRegularSpatialGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, e: ConstFGridExpression) -> DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularSpatialGrid instance \a e.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param e The \e %DRegularSpatialGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, e: ConstDGridExpression) -> DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularSpatialGrid instance \a e.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param e The \e %DRegularSpatialGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, e: object) -> DRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DRegularSpatialGrid instance \a g.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param g The \e %DRegularSpatialGrid instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DRegularSpatialGrid, g: DRegularSpatialGrid) -> DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getSize1(self: DRegularSpatialGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getSize2(self: DRegularSpatialGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getSize3(self: DRegularSpatialGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def isEmpty(self: DRegularSpatialGrid) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def getElement(self: DRegularSpatialGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: DRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def toArray(self: DRegularSpatialGrid) -> object: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def getSize(self: DRegularSpatialGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param g 
    #
    def swap(self: DRegularSpatialGrid, g: DRegularSpatialGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(self: DRegularSpatialGrid, i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def setElement(self: DRegularSpatialGrid, i: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \return 
    #
    def __call__(self: DRegularSpatialGrid, i: int, j: int, k: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: DRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param ijk 
    # \return 
    #
    def __getitem__(self: DRegularSpatialGrid, ijk: tuple) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: DRegularSpatialGrid, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def __len__(self: DRegularSpatialGrid) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == g</tt>.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param g The \e %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DRegularSpatialGrid, g: DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param e The \e %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DRegularSpatialGrid, e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param g The \e %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DRegularSpatialGrid, g: DRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param e The \e %DRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DRegularSpatialGrid, e: ConstDGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %DRegularSpatialGrid instance.
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DRegularSpatialGrid) -> str: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def __pos__(self: DRegularSpatialGrid) -> DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %DRegularSpatialGrid instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %DRegularSpatialGrid instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %DRegularSpatialGrid instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDGridExpression) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %DRegularSpatialGrid instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %DRegularSpatialGrid instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param ijk 
    # \param v 
    #
    def __setitem__(self: DRegularSpatialGrid, ijk: tuple, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param i 
    # \param v 
    #
    def __setitem__(self: DRegularSpatialGrid, i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += g</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as in-place addend.
    # \param g Specifies the second addend.
    # \return The updated \e %DRegularSpatialGrid instance \a self.
    #
    def __iadd__(self: DRegularSpatialGrid, g: DRegularSpatialGrid) -> DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DRegularSpatialGrid instance \a self.
    #
    def __iadd__(self: DRegularSpatialGrid, e: ConstDGridExpression) -> DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as in-place minuend.
    # \param g Specifies the subtrahend.
    # \return The updated \e %DRegularSpatialGrid instance \a self.
    #
    def __isub__(self: DRegularSpatialGrid, g: DRegularSpatialGrid) -> DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DRegularSpatialGrid instance \a self.
    #
    def __isub__(self: DRegularSpatialGrid, e: ConstDGridExpression) -> DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DRegularSpatialGrid instance \a self.
    #
    def __imul__(self: DRegularSpatialGrid, t: float) -> DRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DRegularSpatialGrid instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DRegularSpatialGrid instance \a self.
    #
    def __idiv__(self: DRegularSpatialGrid, t: float) -> DRegularSpatialGrid: pass

    ##
    # \brief 
    # \param self The \e %DRegularSpatialGrid instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DRegularSpatialGrid, t: float) -> DRegularSpatialGrid: pass

    ##
    # \brief 
    #
    data = property(getData)

    ##
    # \brief FIXME!
    #
    coordsTransform = property(getCoordsTransform, setCoordsTransform)

    ##
    # \brief 
    #
    dataMode = property(getDataMode, setDataMode)

    ##
    # \brief 
    #
    xStepSize = property(getXStepSize, setXStepSize)

    ##
    # \brief 
    #
    yStepSize = property(getYStepSize, setYStepSize)

    ##
    # \brief 
    #
    zStepSize = property(getZStepSize, setZStepSize)

    ##
    # \brief 
    #
    xExtent = property(getXExtent)

    ##
    # \brief 
    #
    yExtent = property(getYExtent)

    ##
    # \brief 
    #
    zExtent = property(getZExtent)

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
