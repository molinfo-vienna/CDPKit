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
# \brief Pharm.FeatureMapping specialization that perceives a reference-to-aligned feature mapping based on type, position and geometry compatibility under a given transformation, caching per-pair position and geometry match scores for later retrieval.
# 
class SpatialFeatureMapping(FeatureMapping):

    ##
    # \brief Initializes a copy of the \c %SpatialFeatureMapping instance \a mapping.
    # \param mapping The \c %SpatialFeatureMapping instance to copy.
    # 
    def __init__(mapping: SpatialFeatureMapping) -> None: pass

    ##
    # \brief Constructs a <tt>SpatialFeatureMapping</tt> instance.
    # 
    # \param query_mode If <tt>True</tt>, the reference feature container is interpreted as a query feature container and some of the set default functions will operate in a special query mode.
    # 
    def __init__(query_mode: bool = False) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %SpatialFeatureMapping instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %SpatialFeatureMapping instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %SpatialFeatureMapping instance \a mapping.
    # \param mapping The \c %SpatialFeatureMapping instance to copy.
    # \return \a self
    # 
    def assign(mapping: SpatialFeatureMapping) -> SpatialFeatureMapping: pass

    ##
    # \brief Computes the spatial feature mapping between the reference and aligned feature containers after applying <em>xform</em> to the aligned features, populating this mapping and the per-pair score caches.
    # 
    # \param ref_ftrs The reference feature container.
    # \param aligned_ftrs The aligned feature container.
    # \param xform The transformation applied to the aligned features before the mapping is perceived.
    # 
    def perceive(ref_ftrs: FeatureContainer, aligned_ftrs: FeatureContainer, xform: Math.Matrix4D) -> None: pass

    ##
    # \brief Specifies a function for testing the type compatibility of features.
    # 
    # \param func The type compatibility test function.
    # 
    def setTypeMatchFunction(func: BoolFeature2Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for testing the type compatibility of the features.
    # 
    # \return The registered type compatibility test function.
    # 
    def getTypeMatchFunction() -> BoolFeature2Functor: pass

    ##
    # \brief Specifies a function for checking the proximity of mapped feature positions.
    # 
    # \param func The position proximity test function.
    # 
    def setPositionMatchFunction(func: DoubleFeature2Matrix4DFunctor) -> None: pass

    ##
    # \brief Returns the function that was registered for checking the proximity of mapped feature positions.
    # 
    # \return The registered position proximity test function.
    # 
    def getPositionMatchFunction() -> DoubleFeature2Matrix4DFunctor: pass

    ##
    # \brief Specifies a function for checking the match of mapped feature geometries.
    # 
    # \param func The feature geometry match test function.
    # 
    def setGeometryMatchFunction(func: DoubleFeature2Matrix4DFunctor) -> None: pass

    ##
    # \brief Returns the function that was registered for checking the match of mapped feature geometries.
    # 
    # \return The registered geometry match test function.
    # 
    def getGeometryMatchFunction() -> DoubleFeature2Matrix4DFunctor: pass

    ##
    # \brief Returns the position-match score cached for the (<em>ref_ftr</em>, <em>aligned_ftr</em>) pair by the last perceive() call.
    # 
    # \param ref_ftr The reference feature.
    # \param aligned_ftr The aligned feature.
    # 
    # \return The cached position-match score (or zero if no entry exists for the pair).
    # 
    def getPositionMatchScore(ref_ftr: Feature, aligned_ftr: Feature) -> float: pass

    ##
    # \brief Returns the geometry-match score cached for the (<em>ref_ftr</em>, <em>aligned_ftr</em>) pair by the last perceive() call.
    # 
    # \param ref_ftr The reference feature.
    # \param aligned_ftr The aligned feature.
    # 
    # \return The cached geometry-match score (or zero if no entry exists for the pair).
    # 
    def getGeometryMatchScore(ref_ftr: Feature, aligned_ftr: Feature) -> float: pass

    objectID = property(getObjectID)

    typeMatchFunction = property(getTypeMatchFunction, setTypeMatchFunction)

    positionMatchFunction = property(getPositionMatchFunction, setPositionMatchFunction)

    geometryMatchFunction = property(getGeometryMatchFunction, setGeometryMatchFunction)
