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
    # \param self The \e %GaussianShapeFunction instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeFunction instance.
    # \param self The \e %GaussianShapeFunction instance to initialize.
    # \param shape 
    #
    def __init__(self: object, shape: GaussianShape) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeFunction instance.
    # \param self The \e %GaussianShapeFunction instance to initialize.
    # \param func 
    #
    def __init__(self: object, func: GaussianShapeFunction) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    #
    # Different Python \e %GaussianShapeFunction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeFunction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeFunction) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShapeFunction instance \a func.
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param func The \e %GaussianShapeFunction instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: GaussianShapeFunction, func: GaussianShapeFunction) -> GaussianShapeFunction: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param shape 
    #
    def setShape(self: GaussianShapeFunction, shape: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \return 
    #
    def getShape(self: GaussianShapeFunction) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param max_order 
    #
    def setMaxOrder(self: GaussianShapeFunction, max_order: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \return 
    #
    def getMaxOrder(self: GaussianShapeFunction) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param cutoff 
    #
    def setDistanceCutoff(self: GaussianShapeFunction, cutoff: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \return 
    #
    def getDistanceCutoff(self: GaussianShapeFunction) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    #
    def reset(self: GaussianShapeFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param xform 
    #
    def transform(self: GaussianShapeFunction, xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param coords 
    #
    def getElementPositions(self: GaussianShapeFunction, coords: CDPL.Math.Vector3DArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElementPosition(self: GaussianShapeFunction, idx: int) -> CDPL.Math.Vector3D: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param pos 
    # \return 
    #
    def calcDensity(self: GaussianShapeFunction, pos: CDPL.Math.Vector3D) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \return 
    #
    def calcSurfaceArea(self: GaussianShapeFunction) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param elem_idx 
    # \return 
    #
    def calcSurfaceArea(self: GaussianShapeFunction, elem_idx: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param ctr 
    #
    def calcCentroid(self: GaussianShapeFunction, ctr: CDPL.Math.Vector3D) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeFunction instance this method is called upon.
    # \param ctr 
    # \param quad_tensor 
    #
    def calcQuadrupoleTensor(self: GaussianShapeFunction, ctr: CDPL.Math.Vector3D, quad_tensor: CDPL.Math.Matrix3D) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    shape = property(getShape, setShape)

    ##
    # \brief FIXME!
    #
    volume = property(getVolume)

    ##
    # \brief FIXME!
    #
    surfaceArea = property(getSurfaceArea)

    ##
    # \brief 
    #
    maxOrder = property(getMaxOrder, setMaxOrder)

    ##
    # \brief FIXME!
    #
    distCutoff = property(getDistCutoff, setDistCutoff)
