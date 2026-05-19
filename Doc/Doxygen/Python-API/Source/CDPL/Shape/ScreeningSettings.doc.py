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
# \brief Bundle of configuration parameters for Shape.ScreeningProcessor.
# 
# The settings select the scoring function, the type of color (pharmacophore) features used, the screening mode (e.g. best-overall vs. best-per-query), the alignment-start strategy, and the parameters of the iterative overlap optimization.
# 
class ScreeningSettings(Boost.Python.instance):

    ##
    # \brief Specifies which alignment hits are reported by the screening processor.
    # 
    class ScreeningMode(Boost.Python.enum):

        ##
        # \brief Report only the single best-scoring alignment hit across all queries.
        # 
        BEST_OVERALL_MATCH = 0

        ##
        # \brief Report the best-scoring alignment hit per query molecule.
        # 
        BEST_MATCH_PER_QUERY = 1

        ##
        # \brief Report the best-scoring alignment hit per (query, query conformer) pair.
        # 
        BEST_MATCH_PER_QUERY_CONF = 2

    ##
    # \brief Specifies which kind of color (pharmacophore) features are used during shape alignment.
    # 
    class ColorFeatureType(Boost.Python.enum):

        ##
        # \brief Disable color features (shape-only alignment).
        # 
        NO_FEATURES = 0

        ##
        # \brief PHARMACOPHORE_EXL_CHARGES.
        #
        PHARMACOPHORE_EXL_CHARGES = 1

        ##
        # \brief Use pharmacophore features derived from perceived (implicit) charges.
        # 
        PHARMACOPHORE_IMP_CHARGES = 2

    ##
    # \brief Bitmask flags specifying the strategies used to seed alignment starting transformations.
    # 
    class AlignmentMode(Boost.Python.enum):

        ##
        # \brief Disable alignment entirely (overlap is computed in the input pose only).
        # 
        NO_ALIGNMENT = 0

        ##
        # \brief Place the aligned shape at the centroid of the reference shape.
        # 
        SHAPE_CENTROID = 1

        ##
        # \brief Seed alignments by superimposing pairs of atom centers.
        # 
        ATOM_CENTERS = 2

        ##
        # \brief Seed alignments by superimposing pairs of color (pharmacophore) feature centers.
        # 
        COLOR_FEATURE_CENTERS = 4

        ##
        # \brief Seed alignments with random rotations.
        # 
        RANDOM = 8

    ##
    # \brief A static instance with default-initialized values.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Sentinel value (NaN) used to disable the score cutoff.
    # 
    NO_CUTOFF = nan

    ##
    # \brief Constructs a <tt>ScreeningSettings</tt> instance with default values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %ScreeningSettings instance \a settings.
    # \param settings The \c %ScreeningSettings instance to copy.
    # 
    def __init__(settings: ScreeningSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ScreeningSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ScreeningSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ScreeningSettings instance \a settings.
    # \param settings The \c %ScreeningSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: ScreeningSettings) -> ScreeningSettings: pass

    ##
    # \brief Sets the scoring function used to rank alignment results.
    # 
    def setScoringFunction(func: DoubleAlignmentResultFunctor) -> None: pass

    ##
    # \brief Returns the currently configured scoring function.
    # 
    def getScoringFunction() -> DoubleAlignmentResultFunctor: pass

    ##
    # \brief Sets the minimum score below which alignment hits are discarded (or NO_CUTOFF).
    # 
    def setScoreCutoff(cutoff: float) -> None: pass

    ##
    # \brief Returns the currently configured score cutoff (or NO_CUTOFF).
    # 
    def getScoreCutoff() -> float: pass

    ##
    # \brief Sets the color feature type to use during alignment.
    # 
    def setColorFeatureType(type: ColorFeatureType) -> None: pass

    ##
    # \brief Returns the currently configured color feature type.
    # 
    def getColorFeatureType() -> ColorFeatureType: pass

    ##
    # \brief Sets the screening mode.
    # 
    def setScreeningMode(mode: ScreeningMode) -> None: pass

    ##
    # \brief Returns the currently configured screening mode.
    # 
    def getScreeningMode() -> ScreeningMode: pass

    ##
    # \brief Sets the alignment-mode bitmask (see AlignmentMode).
    # 
    def setAlignmentMode(mode: AlignmentMode) -> None: pass

    ##
    # \brief Returns the currently configured alignment-mode bitmask.
    # 
    def getAlignmentMode() -> AlignmentMode: pass

    ##
    # \brief Sets the number of random starting transformations when AlignmentMode.RANDOM is enabled.
    # 
    def setNumRandomStarts(num_starts: int) -> None: pass

    ##
    # \brief Returns the currently configured number of random starts.
    # 
    def getNumRandomStarts() -> int: pass

    ##
    # \brief Enables or disables the all-carbon mode (treats every heavy atom as carbon for shape generation).
    # 
    def allCarbonMode(all_c: bool) -> None: pass

    ##
    # \brief Tells whether the all-carbon mode is enabled.
    # 
    def allCarbonMode() -> bool: pass

    ##
    # \brief 
    # \param all_c 
    #
    def singleConformerSearch(all_c: bool) -> None: pass

    ##
    # \brief Tells whether only a single conformer of each molecule is considered.
    # 
    def singleConformerSearch() -> bool: pass

    ##
    # \brief Sets the maximum number of overlap-optimization iterations.
    # 
    def setMaxNumOptimizationIterations(max_iter: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum number of overlap-optimization iterations.
    # 
    def getMaxNumOptimizationIterations() -> int: pass

    ##
    # \brief Sets the gradient norm at which the overlap optimization is stopped.
    # 
    def setOptimizationStopGradient(grad_norm: float) -> None: pass

    ##
    # \brief Returns the currently configured overlap-optimization stop gradient.
    # 
    def getOptimizationStopGradient() -> float: pass

    ##
    # \brief Specifies whether the overlap shall be optimized iteratively after the initial alignment.
    # 
    def optimizeOverlap(optimize: bool) -> None: pass

    ##
    # \brief Tells whether the overlap is optimized iteratively.
    # 
    def optimizeOverlap() -> bool: pass

    ##
    # \brief Specifies whether the overlap optimization shall use a greedy strategy that stops at the first local maximum.
    # 
    def greedyOptimization(greedy: bool) -> None: pass

    ##
    # \brief Tells whether the overlap optimization uses a greedy strategy.
    # 
    def greedyOptimization() -> bool: pass

    objectID = property(getObjectID)

    scoringFunction = property(getScoringFunction, setScoringFunction)

    scoreCutoff = property(getScoreCutoff, setScoreCutoff)

    screeningMode = property(getScreeningMode, setScreeningMode)

    alignmentMode = property(getAlignmentMode, setAlignmentMode)

    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    allCarbon = property(allCarbonMode, allCarbonMode)

    singleConfSearch = property(singleConformerSearch, singleConformerSearch)

    colorFeatureType = property(getColorFeatureType, setColorFeatureType)

    maxNumOptIterations = property(getMaxNumOptimizationIterations, setMaxNumOptimizationIterations)

    optStopGradient = property(getOptimizationStopGradient, setOptimizationStopGradient)

    optOverlap = property(optimizeOverlap, optimizeOverlap)

    greedyOpt = property(greedyOptimization, greedyOptimization)
