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
class InteractionScoreGridCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class MaxScoreFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %MaxScoreFunctor instance.
        # \param self The \e %MaxScoreFunctor instance to initialize.
        #
        def __init__(self: object) -> None: pass

        ##
        # \brief 
        # \param self The \e %MaxScoreFunctor instance this method is called upon.
        # \param scores 
        # \return 
        #
        def __call__(self: MaxScoreFunctor, scores: CDPL.Math.DVector) -> float: pass

    ##
    # \brief 
    #
    class ScoreSumFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %ScoreSumFunctor instance.
        # \param self The \e %ScoreSumFunctor instance to initialize.
        #
        def __init__(self: object) -> None: pass

        ##
        # \brief 
        # \param self The \e %ScoreSumFunctor instance this method is called upon.
        # \param scores 
        # \return 
        #
        def __call__(self: ScoreSumFunctor, scores: CDPL.Math.DVector) -> float: pass

    ##
    # \brief Initializes the \e %InteractionScoreGridCalculator instance.
    # \param self The \e %InteractionScoreGridCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %InteractionScoreGridCalculator instance.
    # \param self The \e %InteractionScoreGridCalculator instance to initialize.
    # \param func 
    #
    def __init__(self: object, func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief Initializes the \e %InteractionScoreGridCalculator instance.
    # \param self The \e %InteractionScoreGridCalculator instance to initialize.
    # \param scoring_func 
    # \param comb_func 
    #
    def __init__(self: object, scoring_func: DoubleVector3DFeatureFunctor, comb_func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Initializes the \e %InteractionScoreGridCalculator instance.
    # \param self The \e %InteractionScoreGridCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: InteractionScoreGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    #
    # Different Python \e %InteractionScoreGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %InteractionScoreGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: InteractionScoreGridCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %InteractionScoreGridCalculator instance \a calculator.
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param calculator The \e %InteractionScoreGridCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: InteractionScoreGridCalculator, calculator: InteractionScoreGridCalculator) -> InteractionScoreGridCalculator: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param dist 
    #
    def setDistanceCutoff(self: InteractionScoreGridCalculator, dist: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \return 
    #
    def getDistanceCutoff(self: InteractionScoreGridCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param func 
    #
    def setScoringFunction(self: InteractionScoreGridCalculator, func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \return 
    #
    def getScoringFunction(self: InteractionScoreGridCalculator) -> DoubleVector3DFeatureFunctor: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param func 
    #
    def setScoreCombinationFunction(self: InteractionScoreGridCalculator, func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \return 
    #
    def getScoreCombinationFunction(self: InteractionScoreGridCalculator) -> CDPL.Math.DoubleDVectorFunctor: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param normalize 
    #
    def normalizeScores(self: InteractionScoreGridCalculator, normalize: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \return 
    #
    def scoresNormalized(self: InteractionScoreGridCalculator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param features 
    # \param grid 
    #
    def calculate(self: InteractionScoreGridCalculator, features: FeatureContainer, grid: CDPL.Grid.DSpatialGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionScoreGridCalculator instance this method is called upon.
    # \param features 
    # \param grid 
    # \param tgt_ftr_pred 
    #
    def calculate(self: InteractionScoreGridCalculator, features: FeatureContainer, grid: CDPL.Grid.DSpatialGrid, tgt_ftr_pred: BoolFeatureFunctor) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    normalizedScores = property(getNormalizedScores, setNormalizedScores)

    ##
    # \brief 
    #
    distanceCutoff = property(getDistanceCutoff, setDistanceCutoff)

    ##
    # \brief 
    #
    scoringFunction = property(getScoringFunction, setScoringFunction)

    ##
    # \brief 
    #
    scoreCombinationFunction = property(getScoreCombinationFunction, setScoreCombinationFunction)
