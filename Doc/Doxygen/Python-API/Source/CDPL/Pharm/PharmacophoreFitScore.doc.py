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
# \brief Scoring functor that quantifies how well a candidate set of features fits a reference pharmacophore, combining feature-match count, per-feature position deviation and geometry-match contributions.
# 
class PharmacophoreFitScore(Boost.Python.instance):

    ##
    # \brief Default contribution weight of the matched-feature-count term.
    # 
    DEF_FTR_MATCH_COUNT_WEIGHT = 1.0

    ##
    # \brief Default contribution weight of the feature-position-deviation term.
    # 
    DEF_FTR_POS_MATCH_WEIGHT = 0.5

    ##
    # \brief Default contribution weight of the feature-geometry-match term.
    # 
    DEF_FTR_GEOM_MATCH_WEIGHT = 0.4

    ##
    # \brief Initializes a copy of the \c %PharmacophoreFitScore instance \a score.
    # \param score The \c %PharmacophoreFitScore instance to copy.
    # 
    def __init__(score: PharmacophoreFitScore) -> None: pass

    ##
    # \brief Constructs the <tt>PharmacophoreFitScore</tt> instance.
    # 
    # \param query_mode If <tt>True</tt>, the reference features are interpreted as a query pharmacophore (with mandatory/optional distinction); if <tt>False</tt>, no such distinction is made.
    # \param match_cnt_weight Weight of the matched-feature-count contribution.
    # \param pos_match_weight Weight of the feature-position-deviation contribution.
    # \param geom_match_weight Weight of the feature-geometry-match contribution.
    # 
    def __init__(query_mode: bool = False, match_cnt_weight: float = 1.0, pos_match_weight: float = 0.5, geom_match_weight: float = 0.4) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %PharmacophoreFitScore instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %PharmacophoreFitScore instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %PharmacophoreFitScore instance \a score.
    # \param score The \c %PharmacophoreFitScore instance to copy.
    # \return \a self
    # 
    def assign(score: PharmacophoreFitScore) -> PharmacophoreFitScore: pass

    ##
    # \brief Returns the currently configured weight of the matched-feature-count contribution.
    # 
    # \return The match-count weight.
    # 
    def getFeatureMatchCountWeight() -> float: pass

    ##
    # \brief Sets the weight of the matched-feature-count contribution.
    # 
    # \param weight The new match-count weight.
    # 
    def setFeatureMatchCountWeight(weight: float) -> None: pass

    ##
    # \brief Returns the currently configured weight of the feature-position-deviation contribution.
    # 
    # \return The position-match weight.
    # 
    def getFeaturePositionMatchWeight() -> float: pass

    ##
    # \brief Sets the weight of the feature-position-deviation contribution.
    # 
    # \param weight The new position-match weight.
    # 
    def setFeaturePositionMatchWeight(weight: float) -> None: pass

    ##
    # \brief Returns the currently configured weight of the feature-geometry-match contribution.
    # 
    # \return The geometry-match weight.
    # 
    def getFeatureGeometryMatchWeight() -> float: pass

    ##
    # \brief Sets the weight of the feature-geometry-match contribution.
    # 
    # \param weight The new geometry-match weight.
    # 
    def setFeatureGeometryMatchWeight(weight: float) -> None: pass

    ##
    # \brief Tells whether reference features are grouped before scoring.
    # 
    # \return <tt>True</tt> if reference-feature grouping is enabled, and <tt>False</tt> otherwise. 
    # 
    # \since 1.2
    # 
    def referenceFeaturesGrouped() -> bool: pass

    ##
    # \brief Specifies whether reference features should be grouped before scoring (groups share a common mandatory/optional status and contribute jointly to the score).
    # 
    # \param group <tt>True</tt> to enable reference-feature grouping, and <tt>False</tt> to score every feature individually.
    # 
    # \since 1.2
    # 
    def groupReferenceFeatures(group: bool) -> None: pass

    ##
    # \brief Computes the fit score of <em>algnd_ftrs</em> against <em>ref_ftrs</em> after applying the rigid-body transformation <em>xform</em>.
    # 
    # \param ref_ftrs The reference pharmacophore features.
    # \param algnd_ftrs The aligned candidate features.
    # \param xform The transformation applied to the aligned features before the comparison.
    # 
    # \return The pharmacophore fit score.
    # 
    def __call__(ref_ftrs: FeatureContainer, algnd_ftrs: FeatureContainer, xform: Math.Matrix4D) -> float: pass

    ##
    # \brief Computes the fit score from a pre-computed feature mapping.
    # 
    # \param ref_ftrs The reference pharmacophore features.
    # \param mapping The spatial feature mapping between reference and aligned features.
    # 
    # \return The pharmacophore fit score.
    # 
    def __call__(ref_ftrs: FeatureContainer, mapping: SpatialFeatureMapping) -> float: pass

    objectID = property(getObjectID)

    featureMatchCountWeight = property(getFeatureMatchCountWeight, setFeatureMatchCountWeight)

    featurePositionMatchWeight = property(getFeaturePositionMatchWeight, setFeaturePositionMatchWeight)

    featureGeometryMatchWeight = property(getFeatureGeometryMatchWeight, setFeatureGeometryMatchWeight)

    referenceFeatureGrouping = property(referenceFeaturesGrouped, groupReferenceFeatures)
