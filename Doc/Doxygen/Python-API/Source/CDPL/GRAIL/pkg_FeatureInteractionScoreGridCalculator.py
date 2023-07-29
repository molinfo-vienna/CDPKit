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
# \brief FeatureInteractionScoreGridCalculator.
# 
class FeatureInteractionScoreGridCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class MaxScoreFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %MaxScoreFunctor instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief 
        # \param scores 
        # \return 
        #
        def __call__(scores: Math.DVector) -> float: pass

    ##
    # \brief 
    #
    class ScoreSumFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %ScoreSumFunctor instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief 
        # \param scores 
        # \return 
        #
        def __call__(scores: Math.DVector) -> float: pass

    ##
    # \brief Initializes the \e %FeatureInteractionScoreGridCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FeatureInteractionScoreGridCalculator instance.
    # \param func 
    # 
    def __init__(func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief Initializes the \e %FeatureInteractionScoreGridCalculator instance.
    # \param scoring_func 
    # \param comb_func 
    # 
    def __init__(scoring_func: DoubleVector3DFeatureFunctor, comb_func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Initializes the \e %FeatureInteractionScoreGridCalculator instance.
    # \param calc 
    # 
    def __init__(calc: FeatureInteractionScoreGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FeatureInteractionScoreGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeatureInteractionScoreGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureInteractionScoreGridCalculator instance \a calc.
    # \param calc The \e %FeatureInteractionScoreGridCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: FeatureInteractionScoreGridCalculator) -> FeatureInteractionScoreGridCalculator: pass

    ##
    # \brief 
    # \param dist 
    #
    def setDistanceCutoff(dist: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDistanceCutoff() -> float: pass

    ##
    # \brief 
    # \param func 
    #
    def setScoringFunction(func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoringFunction() -> DoubleVector3DFeatureFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setScoreCombinationFunction(func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoreCombinationFunction() -> Math.DoubleDVectorFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setFeatureSelectionPredicate(func: Pharm.BoolFeatureFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureSelectionPredicate() -> Pharm.BoolFeatureFunctor: pass

    ##
    # \brief 
    # \param normalize 
    #
    def normalizeScores(normalize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def scoresNormalized() -> bool: pass

    ##
    # \brief 
    # \param tgt_ftrs 
    # \param grid 
    #
    def calculate(tgt_ftrs: Pharm.FeatureContainer, grid: Grid.DSpatialGrid) -> None: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    normScores = property(getNormScores, setNormScores)

    distanceCutoff = property(getDistanceCutoff, setDistanceCutoff)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    scoreCombinationFunction = property(getScoreCombinationFunction, setScoreCombinationFunction)

    featureSelectionPredicate = property(getFeatureSelectionPredicate, setFeatureSelectionPredicate)
