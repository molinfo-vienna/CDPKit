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
class ScreeningSettings(Boost.Python.instance):

    ##
    # \brief 
    #
    class ScreeningMode(Boost.Python.enum):

        ##
        # \brief BEST_OVERALL_MATCH.
        #
        BEST_OVERALL_MATCH = 0

        ##
        # \brief BEST_MATCH_PER_QUERY.
        #
        BEST_MATCH_PER_QUERY = 1

        ##
        # \brief BEST_MATCH_PER_QUERY_CONF.
        #
        BEST_MATCH_PER_QUERY_CONF = 2

    ##
    # \brief 
    #
    class ColorFeatureType(Boost.Python.enum):

        ##
        # \brief NO_FEATURES.
        #
        NO_FEATURES = 0

        ##
        # \brief PHARMACOPHORE_EXL_CHARGES.
        #
        PHARMACOPHORE_EXL_CHARGES = 1

        ##
        # \brief PHARMACOPHORE_IMP_CHARGES.
        #
        PHARMACOPHORE_IMP_CHARGES = 2

    ##
    # \brief 
    #
    class AlignmentMode(Boost.Python.enum):

        ##
        # \brief NO_ALIGNMENT.
        #
        NO_ALIGNMENT = 0

        ##
        # \brief SHAPE_CENTROID.
        #
        SHAPE_CENTROID = 1

        ##
        # \brief ATOM_CENTERS.
        #
        ATOM_CENTERS = 2

        ##
        # \brief COLOR_FEATURE_CENTERS.
        #
        COLOR_FEATURE_CENTERS = 4

        ##
        # \brief RANDOM.
        #
        RANDOM = 8

    ##
    # \brief FIXME!
    #
    DEFAULT = _UNKNOWN_VALUE_

    ##
    # \brief 
    #
    NO_CUTOFF = nan

    ##
    # \brief Initializes the \e %ScreeningSettings instance.
    # \param self The \e %ScreeningSettings instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ScreeningSettings instance.
    # \param self The \e %ScreeningSettings instance to initialize.
    # \param settings 
    #
    def __init__(self: object, settings: ScreeningSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ScreeningSettings instance this method is called upon.
    #
    # Different Python \e %ScreeningSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ScreeningSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ScreeningSettings) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ScreeningSettings instance \a settings.
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param settings The \e %ScreeningSettings instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ScreeningSettings, settings: ScreeningSettings) -> ScreeningSettings: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param func 
    #
    def setScoringFunction(self: ScreeningSettings, func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getScoringFunction(self: ScreeningSettings) -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param cutoff 
    #
    def setScoreCutoff(self: ScreeningSettings, cutoff: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getScoreCutoff(self: ScreeningSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param type 
    #
    def setColorFeatureType(self: ScreeningSettings, type: ColorFeatureType) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getColorFeatureType(self: ScreeningSettings) -> ColorFeatureType: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param mode 
    #
    def setScreeningMode(self: ScreeningSettings, mode: ScreeningMode) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getScreeningMode(self: ScreeningSettings) -> ScreeningMode: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param mode 
    #
    def setAlignmentMode(self: ScreeningSettings, mode: AlignmentMode) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getAlignmentMode(self: ScreeningSettings) -> AlignmentMode: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param num_starts 
    #
    def setNumRandomStarts(self: ScreeningSettings, num_starts: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getNumRandomStarts(self: ScreeningSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param all_c 
    #
    def allCarbonMode(self: ScreeningSettings, all_c: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def allCarbonMode(self: ScreeningSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param all_c 
    #
    def singleConformerSearch(self: ScreeningSettings, all_c: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def singleConformerSearch(self: ScreeningSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param max_iter 
    #
    def setMaxNumOptimizationIterations(self: ScreeningSettings, max_iter: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumOptimizationIterations(self: ScreeningSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param grad_norm 
    #
    def setOptimizationStopGradient(self: ScreeningSettings, grad_norm: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def getOptimizationStopGradient(self: ScreeningSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param optimize 
    #
    def optimizeOverlap(self: ScreeningSettings, optimize: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def optimizeOverlap(self: ScreeningSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \param greedy 
    #
    def greedyOptimization(self: ScreeningSettings, greedy: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningSettings instance this method is called upon.
    # \return 
    #
    def greedyOptimization(self: ScreeningSettings) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    scoringFunction = property(getScoringFunction, setScoringFunction)

    ##
    # \brief 
    #
    scoreCutoff = property(getScoreCutoff, setScoreCutoff)

    ##
    # \brief 
    #
    screeningMode = property(getScreeningMode, setScreeningMode)

    ##
    # \brief 
    #
    alignmentMode = property(getAlignmentMode, setAlignmentMode)

    ##
    # \brief 
    #
    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    ##
    # \brief FIXME!
    #
    allCarbon = property(getAllCarbon, setAllCarbon)

    ##
    # \brief FIXME!
    #
    singleConfSearch = property(getSingleConfSearch, setSingleConfSearch)

    ##
    # \brief 
    #
    colorFeatureType = property(getColorFeatureType, setColorFeatureType)

    ##
    # \brief FIXME!
    #
    maxNumOptIterations = property(getMaxNumOptIterations, setMaxNumOptIterations)

    ##
    # \brief FIXME!
    #
    optStopGradient = property(getOptStopGradient, setOptStopGradient)

    ##
    # \brief FIXME!
    #
    optOverlap = property(getOptOverlap, setOptOverlap)

    ##
    # \brief FIXME!
    #
    greedyOpt = property(getGreedyOpt, setGreedyOpt)
