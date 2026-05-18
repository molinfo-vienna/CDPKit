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
# \brief Calculator that fills a spatial grid with per-cell feature-interaction scores against a set of target pharmacophore features.
# 
# For each grid cell, the configured scoring function is evaluated against every target feature within the configured cutoff distance and the resulting scores are combined into a single cell value via a user-supplied combination function (defaulting to a sum). The set of considered target features can be filtered by a feature-selection predicate.
# 
class FeatureInteractionScoreGridCalculator(Boost.Python.instance):

    ##
    # \brief Score-combination functor returning the maximum (infinity norm) of the per-feature scores.
    # 
    class MaxScoreFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \c %MaxScoreFunctor instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief 
        # \param scores 
        # \return 
        #
        def __call__(scores: Math.DVector) -> float: pass

    ##
    # \brief Score-combination functor returning the sum of the per-feature scores.
    # 
    class ScoreSumFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \c %ScoreSumFunctor instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief 
        # \param scores 
        # \return 
        #
        def __call__(scores: Math.DVector) -> float: pass

    ##
    # \brief Constructs the <tt>FeatureInteractionScoreGridCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>FeatureInteractionScoreGridCalculator</tt> instance with the given scoring function.
    # 
    # \param func The scoring function.
    # 
    def __init__(func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief Constructs the <tt>FeatureInteractionScoreGridCalculator</tt> instance with the given scoring and score-combination functions.
    # 
    # \param scoring_func The scoring function.
    # \param comb_func The function used to combine per-feature scores.
    # 
    def __init__(scoring_func: DoubleVector3DFeatureFunctor, comb_func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>FeatureInteractionScoreGridCalculator</tt> instance <em>calc</em>.
    # 
    # \param calc The <tt>FeatureInteractionScoreGridCalculator</tt> to copy.
    # 
    def __init__(calc: FeatureInteractionScoreGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FeatureInteractionScoreGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FeatureInteractionScoreGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param calc The other <tt>FeatureInteractionScoreGridCalculator</tt> instance.
    # 
    # \return \a self
    # 
    def assign(calc: FeatureInteractionScoreGridCalculator) -> FeatureInteractionScoreGridCalculator: pass

    ##
    # \brief Sets the cutoff distance beyond which target features are not considered.
    # 
    # \param dist The cutoff distance.
    # 
    def setDistanceCutoff(dist: float) -> None: pass

    ##
    # \brief Returns the currently configured cutoff distance.
    # 
    # \return The configured cutoff distance.
    # 
    def getDistanceCutoff() -> float: pass

    ##
    # \brief Sets the scoring function used to score the interaction between a grid cell and a target feature.
    # 
    # \param func The scoring function.
    # 
    def setScoringFunction(func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief Returns the currently configured scoring function.
    # 
    # \return The configured scoring function.
    # 
    def getScoringFunction() -> DoubleVector3DFeatureFunctor: pass

    ##
    # \brief Sets the function used to combine per-feature scores into a single grid cell value.
    # 
    # \param func The score-combination function.
    # 
    def setScoreCombinationFunction(func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Returns the currently configured score-combination function.
    # 
    # \return The configured score-combination function.
    # 
    def getScoreCombinationFunction() -> Math.DoubleDVectorFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setFeatureSelectionPredicate(func: Pharm.BoolFeatureFunctor) -> None: pass

    ##
    # \brief Returns the currently configured feature-selection predicate.
    # 
    # \return The configured feature-selection predicate.
    # 
    def getFeatureSelectionPredicate() -> Pharm.BoolFeatureFunctor: pass

    ##
    # \brief Enables or disables normalization of the combined per-cell scores to the range [0, 1].
    # 
    # \param normalize If <tt>True</tt>, the combined scores are normalized.
    # 
    def normalizeScores(normalize: bool) -> None: pass

    ##
    # \brief Tells whether the combined per-cell scores are normalized.
    # 
    # \return <tt>True</tt> if the combined scores are normalized, and <tt>False</tt> otherwise.
    # 
    def scoresNormalized() -> bool: pass

    ##
    # \brief Calculates the feature-interaction score at each cell of <em>grid</em> against <em>tgt_ftrs</em>.
    # 
    # \param tgt_ftrs The container with the target features.
    # \param grid The output grid populated with per-cell scores.
    # 
    def calculate(tgt_ftrs: Pharm.FeatureContainer, grid: Grid.DSpatialGrid) -> None: pass

    objectID = property(getObjectID)

    normScores = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)

    distanceCutoff = property(getDistanceCutoff, setDistanceCutoff)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    scoreCombinationFunction = property(getScoreCombinationFunction, setScoreCombinationFunction)

    featureSelectionPredicate = property(getFeatureSelectionPredicate, setFeatureSelectionPredicate)
