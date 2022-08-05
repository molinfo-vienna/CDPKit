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
    # \param mapping 
    #
    def __init__(mapping: SpatialFeatureMapping) -> None: pass

    ##
    # \brief Initializes the \e %SpatialFeatureMapping instance.
    # \param query_mode 
    #
    def __init__(query_mode: bool = False) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %SpatialFeatureMapping instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SpatialFeatureMapping instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SpatialFeatureMapping instance \a mapping.
    # \param mapping The \e %SpatialFeatureMapping instance to copy.
    # \return The assignment target \a self.
    #
    def assign(mapping: SpatialFeatureMapping) -> SpatialFeatureMapping: pass

    ##
    # \brief 
    # \param ref_ftrs 
    # \param aligned_ftrs 
    # \param xform 
    #
    def perceive(ref_ftrs: FeatureContainer, aligned_ftrs: FeatureContainer, xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setTypeMatchFunction(func: BoolFeature2Functor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTypeMatchFunction() -> BoolFeature2Functor: pass

    ##
    # \brief 
    # \param func 
    #
    def setPositionMatchFunction(func: DoubleFeature2Matrix4DFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPositionMatchFunction() -> DoubleFeature2Matrix4DFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setGeometryMatchFunction(func: DoubleFeature2Matrix4DFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGeometryMatchFunction() -> DoubleFeature2Matrix4DFunctor: pass

    ##
    # \brief 
    # \param ref_ftr 
    # \param aligned_ftr 
    # \return 
    #
    def getPositionMatchScore(ref_ftr: Feature, aligned_ftr: Feature) -> float: pass

    ##
    # \brief 
    # \param ref_ftr 
    # \param aligned_ftr 
    # \return 
    #
    def getGeometryMatchScore(ref_ftr: Feature, aligned_ftr: Feature) -> float: pass

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
