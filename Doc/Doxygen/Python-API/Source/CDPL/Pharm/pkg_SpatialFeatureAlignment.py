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
class SpatialFeatureAlignment(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SpatialFeatureAlignment instance.
    # \param self The \e %SpatialFeatureAlignment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SpatialFeatureAlignment instance.
    # \param self The \e %SpatialFeatureAlignment instance to initialize.
    # \param alignment 
    #
    def __init__(self: object, alignment: SpatialFeatureAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    #
    # Different Python \e %SpatialFeatureAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SpatialFeatureAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SpatialFeatureAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityMatchFunction(self: SpatialFeatureAlignment, func: BoolFeature2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getEntityMatchFunction(self: SpatialFeatureAlignment) -> BoolFeature2Functor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityPairMatchFunction(self: SpatialFeatureAlignment, func: BoolFeature4Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getEntityPairMatchFunction(self: SpatialFeatureAlignment) -> BoolFeature4Functor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param func 
    #
    def setTopAlignmentConstraintFunction(self: SpatialFeatureAlignment, func: CDPL.Chem.BoolSTPairArrayFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getTopAlignmentConstraintFunction(self: SpatialFeatureAlignment) -> CDPL.Chem.BoolSTPairArrayFunctor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param func 
    #
    def setEntity3DCoordinatesFunction(self: SpatialFeatureAlignment, func: Feature3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getEntity3DCoordinatesFunction(self: SpatialFeatureAlignment) -> Feature3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityWeightFunction(self: SpatialFeatureAlignment, func: DoubleFeatureFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getEntityWeightFunction(self: SpatialFeatureAlignment) -> DoubleFeatureFunctor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param entity 
    # \param first_set 
    #
    def addEntity(self: SpatialFeatureAlignment, entity: Feature, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param first_set 
    #
    def clearEntities(self: SpatialFeatureAlignment, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param first_set 
    # \return 
    #
    def getNumEntities(self: SpatialFeatureAlignment, first_set: bool) -> int: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param first_set 
    # \return 
    #
    def getEntities(self: SpatialFeatureAlignment, first_set: bool) -> object: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param idx 
    # \param first_set 
    # \return 
    #
    def getEntity(self: SpatialFeatureAlignment, idx: int, first_set: bool) -> Feature: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param min_size 
    #
    def setMinTopologicalMappingSize(self: SpatialFeatureAlignment, min_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getMinTopologicalMappingSize(self: SpatialFeatureAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param reset 
    #
    def reset(reset: SpatialFeatureAlignment) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def nextAlignment(self: SpatialFeatureAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getTransform(self: SpatialFeatureAlignment) -> CDPL.Math.Matrix4D: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SpatialFeatureAlignment instance \a alignment.
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \param alignment The \e %SpatialFeatureAlignment instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SpatialFeatureAlignment, alignment: SpatialFeatureAlignment) -> SpatialFeatureAlignment: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureAlignment instance this method is called upon.
    # \return 
    #
    def getTopologicalMapping(self: SpatialFeatureAlignment) -> CDPL.Util.STPairArray: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    topMapping = property(getTopMapping)

    ##
    # \brief 
    #
    minTopologicalMappingSize = property(getMinTopologicalMappingSize, setMinTopologicalMappingSize)

    ##
    # \brief 
    #
    transform = property(getTransform)

    ##
    # \brief 
    #
    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    ##
    # \brief 
    #
    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)

    ##
    # \brief 
    #
    topAlignmentConstraintFunction = property(getTopAlignmentConstraintFunction, setTopAlignmentConstraintFunction)

    ##
    # \brief 
    #
    entity3DCoordinatesFunction = property(getEntity3DCoordinatesFunction, setEntity3DCoordinatesFunction)

    ##
    # \brief 
    #
    entityWeightFunction = property(getEntityWeightFunction, setEntityWeightFunction)
