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
class SpatialFeatureAlignment(Boost.Python.instance):

    ##
    # \brief Initializes the \c %SpatialFeatureAlignment instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %SpatialFeatureAlignment instance \a alignment.
    # \param alignment The \c %SpatialFeatureAlignment instance to copy.
    # 
    def __init__(alignment: SpatialFeatureAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %SpatialFeatureAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %SpatialFeatureAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def setEntityMatchFunction(func: BoolFeature2Functor) -> None: pass

    def getEntityMatchFunction() -> BoolFeature2Functor: pass

    def setEntityPairMatchFunction(func: BoolFeature4Functor) -> None: pass

    def getEntityPairMatchFunction() -> BoolFeature4Functor: pass

    def setTopAlignmentConstraintFunction(func: Chem.BoolSTPairArrayFunctor) -> None: pass

    def getTopAlignmentConstraintFunction() -> Chem.BoolSTPairArrayFunctor: pass

    def setEntity3DCoordinatesFunction(func: Feature3DCoordinatesFunction) -> None: pass

    def getEntity3DCoordinatesFunction() -> Feature3DCoordinatesFunction: pass

    def setEntityWeightFunction(func: DoubleFeatureFunctor) -> None: pass

    def getEntityWeightFunction() -> DoubleFeatureFunctor: pass

    def performExhaustiveSearch(exhaustive: bool) -> None: pass

    def exhaustiveSearchPerformed() -> bool: pass

    def addEntity(entity: Feature, first_set: bool) -> None: pass

    def clearEntities(first_set: bool) -> None: pass

    def getNumEntities(first_set: bool) -> int: pass

    def getEntities(first_set: bool) -> object: pass

    def getEntity(idx: int, first_set: bool) -> Feature: pass

    def setMinTopologicalMappingSize(min_size: int) -> None: pass

    def getMinTopologicalMappingSize() -> int: pass

    def reset() -> None: pass

    def nextAlignment() -> bool: pass

    def getTransform() -> Math.Matrix4D: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %SpatialFeatureAlignment instance \a alignment.
    # \param alignment The \c %SpatialFeatureAlignment instance to copy.
    # \return \a self
    # 
    def assign(alignment: SpatialFeatureAlignment) -> SpatialFeatureAlignment: pass

    def getTopologicalMapping() -> Util.STPairArray: pass

    objectID = property(getObjectID)

    topMapping = property(getTopologicalMapping)

    minTopologicalMappingSize = property(getMinTopologicalMappingSize, setMinTopologicalMappingSize)

    exhaustiveSearch = property(exhaustiveSearchPerformed, performExhaustiveSearch)

    transform = property(getTransform)

    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)

    topAlignmentConstraintFunction = property(getTopAlignmentConstraintFunction, setTopAlignmentConstraintFunction)

    entityCoordsFunction = property(getEntity3DCoordinatesFunction, setEntity3DCoordinatesFunction)

    entityWeightFunction = property(getEntityWeightFunction, setEntityWeightFunction)
