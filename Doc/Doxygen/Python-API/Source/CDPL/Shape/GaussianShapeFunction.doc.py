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
# \brief Function representation of a Gaussian shape, used to evaluate the shape's density, volume, surface area and related quantities at arbitrary 3D positions.
# 
# Internally the function maintains a list of Gaussian products (up to a configurable order) derived from the underlying Shape.GaussianShape. The list is built when the shape is supplied via setShape() (or one of the corresponding constructors).
# 
class GaussianShapeFunction(Boost.Python.instance):

    ##
    # \brief Default maximum order of the Gaussian-product expansion.
    # 
    DEF_MAX_PRODUCT_ORDER = 6

    ##
    # \brief Default distance cutoff for pruning negligible Gaussian-product contributions.
    # 
    DEF_DISTANCE_CUTOFF = 0.0

    ##
    # \brief Constructs the <tt>GaussianShapeFunction</tt> instance without an associated shape.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>GaussianShapeFunction</tt> instance associated with <em>shape</em>.
    # 
    # \param shape The Gaussian shape.
    # 
    def __init__(shape: GaussianShape) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>GaussianShapeFunction</tt> instance <em>func</em>.
    # 
    # \param func The <tt>GaussianShapeFunction</tt> to copy.
    # 
    def __init__(func: GaussianShapeFunction) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeFunction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeFunction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param func The other <tt>GaussianShapeFunction</tt> instance.
    # 
    # \return \a self
    # 
    def assign(func: GaussianShapeFunction) -> GaussianShapeFunction: pass

    ##
    # \brief Associates the function with the Gaussian shape <em>shape</em>.
    # 
    # \param shape The Gaussian shape.
    # 
    def setShape(shape: GaussianShape) -> None: pass

    ##
    # \brief Returns a reference to the associated Gaussian shape (or <tt>nullptr</tt> if none is associated).
    # 
    # \return A reference to the associated Gaussian shape.
    # 
    def getShape() -> GaussianShape: pass

    ##
    # \brief Sets the maximum order of the Gaussian-product expansion.
    # 
    # \param max_order The maximum order.
    # 
    def setMaxOrder(max_order: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum order of the Gaussian-product expansion.
    # 
    # \return The configured maximum order.
    # 
    def getMaxOrder() -> int: pass

    ##
    # \brief Sets the distance cutoff for pruning negligible Gaussian-product contributions.
    # 
    # \param cutoff The cutoff distance.
    # 
    def setDistanceCutoff(cutoff: float) -> None: pass

    ##
    # \brief Returns the currently configured distance cutoff.
    # 
    # \return The configured distance cutoff.
    # 
    def getDistanceCutoff() -> float: pass

    ##
    # \brief Resets the function by discarding the cached Gaussian-product expansion.
    # 
    def reset() -> None: pass

    ##
    # \brief Applies an affine transformation to the element positions of the associated shape.
    # 
    # \param xform The <em>4&times;4</em> transformation matrix.
    # 
    def transform(xform: Math.Matrix4D) -> None: pass

    ##
    # \brief Returns the 3D positions of all elements of the associated shape.
    # 
    # \param coords The output array of 3D positions.
    # 
    def getElementPositions(coords: Math.Vector3DArray) -> None: pass

    ##
    # \brief Returns the 3D position of the element at index <em>idx</em>.
    # 
    # \param idx The element index.
    # 
    # \return A reference to the element 3D position. 
    # 
    # \throw Base.IndexError if no shape is associated with this function or <em>idx</em> is not in the range [0, getShape()->getNumElements() - 1].
    # 
    def getElementPosition(idx: int) -> Math.Vector3D: pass

    ##
    # \brief Calculates the total volume enclosed by the Gaussian shape.
    # 
    # \return The volume.
    # 
    def calcVolume() -> float: pass

    ##
    # \brief Evaluates the Gaussian density of the shape at the 3D position <em>pos</em>.
    # 
    # \param pos The 3D position.
    # 
    # \return The Gaussian density value.
    # 
    def calcDensity(pos: Math.Vector3D) -> float: pass

    ##
    # \brief Calculates the total surface area of the Gaussian shape.
    # 
    # \return The total surface area.
    # 
    def calcSurfaceArea() -> float: pass

    ##
    # \brief Calculates the surface area contribution of the single element at index <em>elem_idx</em>.
    # 
    # \param elem_idx The element index.
    # 
    # \return The element surface area.
    # 
    def calcSurfaceArea(elem_idx: int) -> float: pass

    ##
    # \brief Calculates the centroid of the Gaussian shape.
    # 
    # \param ctr The output centroid position.
    # 
    def calcCentroid(ctr: Math.Vector3D) -> None: pass

    ##
    # \brief Calculates the quadrupole tensor of the Gaussian shape with respect to the reference point <em>ctr</em>.
    # 
    # \param ctr The reference point (typically the shape centroid).
    # \param quad_tensor The output <em>3&times;3</em> quadrupole tensor.
    # 
    def calcQuadrupoleTensor(ctr: Math.Vector3D, quad_tensor: Math.Matrix3D) -> None: pass

    objectID = property(getObjectID)

    shape = property(getShape, setShape)

    volume = property(calcVolume)

    surfaceArea = property(calcSurfaceArea)

    maxOrder = property(getMaxOrder, setMaxOrder)

    distCutoff = property(getDistanceCutoff, setDistanceCutoff)
