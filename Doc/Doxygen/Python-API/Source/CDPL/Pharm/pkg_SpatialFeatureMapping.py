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
class SpatialFeatureMapping(FeatureMapping):

    ##
    # \brief Initializes the \e %SpatialFeatureMapping instance.
    # \param self The \e %SpatialFeatureMapping instance to initialize.
    # \param mapping 
    #
    def __init__(self: object, mapping: SpatialFeatureMapping) -> None: pass

    ##
    # \brief Initializes the \e %SpatialFeatureMapping instance.
    # \param self The \e %SpatialFeatureMapping instance to initialize.
    # \param query_mode 
    #
    def __init__(self: object, query_mode: bool = False) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    #
    # Different Python \e %SpatialFeatureMapping instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SpatialFeatureMapping instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SpatialFeatureMapping) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SpatialFeatureMapping instance \a mapping.
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param mapping The \e %SpatialFeatureMapping instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SpatialFeatureMapping, mapping: SpatialFeatureMapping) -> SpatialFeatureMapping: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param ref_ftrs 
    # \param aligned_ftrs 
    # \param xform 
    #
    def perceive(self: SpatialFeatureMapping, ref_ftrs: FeatureContainer, aligned_ftrs: FeatureContainer, xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param func 
    #
    def setTypeMatchFunction(self: SpatialFeatureMapping, func: BoolFeature2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \return 
    #
    def getTypeMatchFunction(self: SpatialFeatureMapping) -> BoolFeature2Functor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param func 
    #
    def setPositionMatchFunction(self: SpatialFeatureMapping, func: DoubleFeature2Matrix4DFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \return 
    #
    def getPositionMatchFunction(self: SpatialFeatureMapping) -> DoubleFeature2Matrix4DFunctor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param func 
    #
    def setGeometryMatchFunction(self: SpatialFeatureMapping, func: DoubleFeature2Matrix4DFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \return 
    #
    def getGeometryMatchFunction(self: SpatialFeatureMapping) -> DoubleFeature2Matrix4DFunctor: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param ref_ftr 
    # \param aligned_ftr 
    # \return 
    #
    def getPositionMatchScore(self: SpatialFeatureMapping, ref_ftr: Feature, aligned_ftr: Feature) -> float: pass

    ##
    # \brief 
    # \param self The \e %SpatialFeatureMapping instance this method is called upon.
    # \param ref_ftr 
    # \param aligned_ftr 
    # \return 
    #
    def getGeometryMatchScore(self: SpatialFeatureMapping, ref_ftr: Feature, aligned_ftr: Feature) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    typeMatchFunction = property(getTypeMatchFunction, setTypeMatchFunction)

    ##
    # \brief 
    #
    positionMatchFunction = property(getPositionMatchFunction, setPositionMatchFunction)

    ##
    # \brief 
    #
    geometryMatchFunction = property(getGeometryMatchFunction, setGeometryMatchFunction)
