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
class GaussianShapeFunction(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MAX_PRODUCT_ORDER = 6

    ##
    # \brief 
    #
    DEF_DISTANCE_CUTOFF = 0.0

    ##
    # \brief Initializes the \e %GaussianShapeFunction instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeFunction instance.
    # \param shape 
    # 
    def __init__(shape: GaussianShape) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeFunction instance with a copy of the state of the \e %GaussianShapeFunction instance \a func.
    # \param func The \e %GaussianShapeFunction instance to copy.
    # 
    def __init__(func: GaussianShapeFunction) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %GaussianShapeFunction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeFunction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShapeFunction instance \a func.
    # \param func The \e %GaussianShapeFunction instance to copy.
    # \return \a self
    # 
    def assign(func: GaussianShapeFunction) -> GaussianShapeFunction: pass

    ##
    # \brief 
    # \param shape 
    #
    def setShape(shape: GaussianShape) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getShape() -> GaussianShape: pass

    ##
    # \brief 
    # \param max_order 
    #
    def setMaxOrder(max_order: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxOrder() -> int: pass

    ##
    # \brief 
    # \param cutoff 
    #
    def setDistanceCutoff(cutoff: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDistanceCutoff() -> float: pass

    ##
    # \brief 
    #
    def reset() -> None: pass

    ##
    # \brief 
    # \param xform 
    #
    def transform(xform: Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param coords 
    #
    def getElementPositions(coords: Math.Vector3DArray) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getElementPosition(idx: int) -> Math.Vector3D: pass

    ##
    # \brief 
    # \param pos 
    # \return 
    #
    def calcDensity(pos: Math.Vector3D) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def calcSurfaceArea() -> float: pass

    ##
    # \brief 
    # \param elem_idx 
    # \return 
    #
    def calcSurfaceArea(elem_idx: int) -> float: pass

    ##
    # \brief 
    # \param ctr 
    #
    def calcCentroid(ctr: Math.Vector3D) -> None: pass

    ##
    # \brief 
    # \param ctr 
    # \param quad_tensor 
    #
    def calcQuadrupoleTensor(ctr: Math.Vector3D, quad_tensor: Math.Matrix3D) -> None: pass

    objectID = property(getObjectID)

    shape = property(getShape, setShape)

    ##
    # \brief FIXME!
    # \brief 
    #
    volume = property(getVolume)

    ##
    # \brief FIXME!
    # \brief 
    #
    surfaceArea = property(getSurfaceArea)

    maxOrder = property(getMaxOrder, setMaxOrder)

    ##
    # \brief FIXME!
    # \brief 
    #
    distCutoff = property(getDistCutoff, setDistCutoff)
