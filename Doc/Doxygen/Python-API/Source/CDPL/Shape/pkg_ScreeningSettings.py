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
    # \brief 
    #
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief 
    #
    NO_CUTOFF = nan

    ##
    # \brief Initializes the \e %ScreeningSettings instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ScreeningSettings instance.
    # \param settings 
    # 
    def __init__(settings: ScreeningSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %ScreeningSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ScreeningSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ScreeningSettings instance \a settings.
    # \param settings The \e %ScreeningSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: ScreeningSettings) -> ScreeningSettings: pass

    ##
    # \brief 
    # \param func 
    #
    def setScoringFunction(func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoringFunction() -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief 
    # \param cutoff 
    #
    def setScoreCutoff(cutoff: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoreCutoff() -> float: pass

    ##
    # \brief 
    # \param type 
    #
    def setColorFeatureType(type: ColorFeatureType) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getColorFeatureType() -> ColorFeatureType: pass

    ##
    # \brief 
    # \param mode 
    #
    def setScreeningMode(mode: ScreeningMode) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScreeningMode() -> ScreeningMode: pass

    ##
    # \brief 
    # \param mode 
    #
    def setAlignmentMode(mode: AlignmentMode) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAlignmentMode() -> AlignmentMode: pass

    ##
    # \brief 
    # \param num_starts 
    #
    def setNumRandomStarts(num_starts: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumRandomStarts() -> int: pass

    ##
    # \brief 
    # \param all_c 
    #
    def allCarbonMode(all_c: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def allCarbonMode() -> bool: pass

    ##
    # \brief 
    # \param all_c 
    #
    def singleConformerSearch(all_c: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def singleConformerSearch() -> bool: pass

    ##
    # \brief 
    # \param max_iter 
    #
    def setMaxNumOptimizationIterations(max_iter: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumOptimizationIterations() -> int: pass

    ##
    # \brief 
    # \param grad_norm 
    #
    def setOptimizationStopGradient(grad_norm: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getOptimizationStopGradient() -> float: pass

    ##
    # \brief 
    # \param optimize 
    #
    def optimizeOverlap(optimize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def optimizeOverlap() -> bool: pass

    ##
    # \brief 
    # \param greedy 
    #
    def greedyOptimization(greedy: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def greedyOptimization() -> bool: pass

    objectID = property(getObjectID)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    scoreCutoff = property(getScoreCutoff, setScoreCutoff)

    screeningMode = property(getScreeningMode, setScreeningMode)

    alignmentMode = property(getAlignmentMode, setAlignmentMode)

    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    ##
    # \brief FIXME!
    # \brief 
    #
    allCarbon = property(getAllCarbon, setAllCarbon)

    ##
    # \brief FIXME!
    # \brief 
    #
    singleConfSearch = property(getSingleConfSearch, setSingleConfSearch)

    colorFeatureType = property(getColorFeatureType, setColorFeatureType)

    ##
    # \brief FIXME!
    # \brief 
    #
    maxNumOptIterations = property(getMaxNumOptIterations, setMaxNumOptIterations)

    ##
    # \brief FIXME!
    # \brief 
    #
    optStopGradient = property(getOptStopGradient, setOptStopGradient)

    ##
    # \brief FIXME!
    # \brief 
    #
    optOverlap = property(getOptOverlap, setOptOverlap)

    ##
    # \brief FIXME!
    # \brief 
    #
    greedyOpt = property(getGreedyOpt, setGreedyOpt)
