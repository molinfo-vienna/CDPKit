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
class FRegularSpatialGrid(Boost.Python.instance):

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
    # \brief Initializes the \e %FRegularSpatialGrid instance.
    # \param grid 
    #
    def __init__(grid: FRegularSpatialGrid) -> None: pass

    ##
    # \brief Initializes the \e %FRegularSpatialGrid instance.
    # \param data 
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(data: FGrid, xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularSpatialGrid instance.
    # \param data 
    # \param s 
    #
    def __init__(data: FGrid, s: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularSpatialGrid instance.
    # \param xs 
    # \param ys 
    # \param zs 
    #
    def __init__(xs: float, ys: float, zs: float) -> None: pass

    ##
    # \brief Initializes the \e %FRegularSpatialGrid instance.
    # \param s 
    #
    def __init__(s: float) -> None: pass

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
    # \brief 
    # \return 
    #
    def getDataMode() -> DataMode: pass

    ##
    # \brief 
    # \param mode 
    #
    def setDataMode(mode: DataMode) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getXExtent() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getYExtent() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getZExtent() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getXStepSize() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getYStepSize() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getZStepSize() -> float: pass

    ##
    # \brief 
    # \param xs 
    #
    def setXStepSize(xs: float) -> None: pass

    ##
    # \brief 
    # \param ys 
    #
    def setYStepSize(ys: float) -> None: pass

    ##
    # \brief 
    # \param zs 
    #
    def setZStepSize(zs: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> FGrid: pass

    ##
    # \brief 
    # \param xform 
    #
    def setCoordinatesTransform(xform: Matrix4F) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCoordinatesTransform() -> Matrix4F: pass

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
    # \param i 
    # \param j 
    # \param k 
    # \param coords 
    #
    def getLocalCoordinates(i: int, j: int, k: int, coords: object) -> None: pass

    ##
    # \brief 
    # \param world_coords 
    # \param local_coords 
    #
    def getLocalCoordinates(world_coords: Vector3F, local_coords: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: Vector3F) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: Vector3D) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: Vector3L) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: Vector3UL) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsPoint(pos: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: Vector3F) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: ConstFVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: Vector3D) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: Vector3L) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: Vector3UL) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def containsLocalPoint(pos: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: Vector3F, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: ConstFVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: Vector3D, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: ConstDVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: Vector3L, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: ConstLVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: Vector3UL, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getContainingCell(pos: ConstULVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: Vector3F, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: ConstFVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: Vector3D, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: ConstDVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: Vector3L, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: ConstLVectorExpression, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: Vector3UL, indices: object) -> None: pass

    ##
    # \brief 
    # \param pos 
    # \param indices 
    #
    def getLocalContainingCell(pos: ConstULVectorExpression, indices: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %FRegularSpatialGrid instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FRegularSpatialGrid instances \e a and \e b reference different C++ objects. 
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
    def assign(e: ConstFGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConstDGridExpression instance \a e.
    # \param e The \e %ConstDGridExpression instance to copy.
    # \return \a self
    #
    def assign(e: ConstDGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %object instance \a e.
    # \param e The \e %object instance to copy.
    # \return \a self
    #
    def assign(e: object) -> FRegularSpatialGrid: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FRegularSpatialGrid instance \a g.
    # \param g The \e %FRegularSpatialGrid instance to copy.
    # \return \a self
    #
    def assign(g: FRegularSpatialGrid) -> FRegularSpatialGrid: pass

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
    # \param g The \e %FRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(g: FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != g</tt>.
    # \param g The \e %FRegularSpatialGrid instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(g: FRegularSpatialGrid) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %ConstFGridExpression instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstFGridExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %FRegularSpatialGrid instance.
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
    # \return A \e %ConstFGridExpression instance holding the result of the addition.
    #
    def __add__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %FRegularSpatialGrid instance holding the result of the subtraction.
    #
    def __sub__(e: ConstFGridExpression) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %ConstFGridExpression instance holding the result of the multiplication.
    #
    def __mul__(t: float) -> ConstFGridExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
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
    # \return The updated \e %FRegularSpatialGrid instance \a self.
    #
    def __iadd__(g: FRegularSpatialGrid) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %FRegularSpatialGrid instance \a self.
    #
    def __iadd__(e: ConstFGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= g</tt>.
    # \param g Specifies the subtrahend.
    # \return The updated \e %FRegularSpatialGrid instance \a self.
    #
    def __isub__(g: FRegularSpatialGrid) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FRegularSpatialGrid instance \a self.
    #
    def __isub__(e: ConstFGridExpression) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %FRegularSpatialGrid instance \a self.
    #
    def __imul__(t: float) -> FRegularSpatialGrid: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %FRegularSpatialGrid instance \a self.
    #
    def __idiv__(t: float) -> FRegularSpatialGrid: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FRegularSpatialGrid: pass

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
