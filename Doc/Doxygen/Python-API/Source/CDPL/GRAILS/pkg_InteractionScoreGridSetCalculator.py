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
class InteractionScoreGridSetCalculator(Boost.Python.instance):

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %InteractionScoreGridSetCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %InteractionScoreGridSetCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %InteractionScoreGridSetCalculator instance \a calculator.
    # \param calculator The \e %InteractionScoreGridSetCalculator instance to copy.
    # \return \a self
    #
    def assign(calculator: InteractionScoreGridSetCalculator) -> InteractionScoreGridSetCalculator: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \param func 
    #
    def setScoringFunction(ftr_type: int, tgt_ftr_type: int, func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    #
    def removeScoringFunction(ftr_type: int, tgt_ftr_type: int) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \return 
    #
    def getScoringFunction(ftr_type: int, tgt_ftr_type: int) -> DoubleVector3DFeatureFunctor: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \param enable 
    #
    def enableInteraction(ftr_type: int, tgt_ftr_type: int, enable: bool) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \return 
    #
    def isInteractionEnabled(ftr_type: int, tgt_ftr_type: int) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \param arg2 
    # \return 
    #
    def clearEnabledInteractions(arg2: int, self: int) -> bool: pass

    ##
    # \brief 
    # \param func 
    #
    def setScoreCombinationFunction(func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoreCombinationFunction() -> CDPL.Math.DoubleDVectorFunctor: pass

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
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    normalizedScores = property(getNormalizedScores, setNormalizedScores)

    ##
    # \brief 
    #
    scoreCombinationFunction = property(getScoreCombinationFunction, setScoreCombinationFunction)
