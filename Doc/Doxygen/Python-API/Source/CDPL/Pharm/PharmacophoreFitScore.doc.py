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
# \brief PharmacophoreFitScore.
# 
class PharmacophoreFitScore(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_FTR_MATCH_COUNT_WEIGHT = 1.0

    ##
    # \brief 
    #
    DEF_FTR_POS_MATCH_WEIGHT = 0.5

    ##
    # \brief 
    #
    DEF_FTR_GEOM_MATCH_WEIGHT = 0.4

    ##
    # \brief Initializes a copy of the \e %PharmacophoreFitScore instance \a score.
    # \param score The \e %PharmacophoreFitScore instance to copy.
    # 
    def __init__(score: PharmacophoreFitScore) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreFitScore instance.
    # \param query_mode 
    # \param match_cnt_weight 
    # \param pos_match_weight 
    # \param geom_match_weight 
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
    # \brief 
    # \return 
    #
    def getFeatureMatchCountWeight() -> float: pass

    ##
    # \brief 
    # \param weight 
    #
    def setFeatureMatchCountWeight(weight: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFeaturePositionMatchWeight() -> float: pass

    ##
    # \brief 
    # \param weight 
    #
    def setFeaturePositionMatchWeight(weight: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureGeometryMatchWeight() -> float: pass

    ##
    # \brief 
    # \param weight 
    #
    def setFeatureGeometryMatchWeight(weight: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def referenceFeaturesGrouped() -> bool: pass

    ##
    # \brief 
    # \param group 
    #
    def groupReferenceFeatures(group: bool) -> None: pass

    ##
    # \brief 
    # \param ref_ftrs 
    # \param algnd_ftrs 
    # \param xform 
    # \return 
    #
    def __call__(ref_ftrs: FeatureContainer, algnd_ftrs: FeatureContainer, xform: Math.Matrix4D) -> float: pass

    ##
    # \brief 
    # \param ref_ftrs 
    # \param mapping 
    # \return 
    #
    def __call__(ref_ftrs: FeatureContainer, mapping: SpatialFeatureMapping) -> float: pass

    objectID = property(getObjectID)

    featureMatchCountWeight = property(getFeatureMatchCountWeight, setFeatureMatchCountWeight)

    featurePositionMatchWeight = property(getFeaturePositionMatchWeight, setFeaturePositionMatchWeight)

    featureGeometryMatchWeight = property(getFeatureGeometryMatchWeight, setFeatureGeometryMatchWeight)

    referenceFeatureGrouping = property(referenceFeaturesGrouped, groupReferenceFeatures)
