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
class PrincipalAxesAlignmentStartGenerator(GaussianShapeAlignmentStartGenerator):

    ##
    # \brief 
    #
    DEF_SYMMETRY_THRESHOLD = 0.15

    ##
    # \brief 
    #
    DEF_NUM_RANDOM_STARTS = 4

    ##
    # \brief 
    #
    DEF_MAX_RANDOM_TRANSLATION = 2.0

    ##
    # \brief Initializes the \e %PrincipalAxesAlignmentStartGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %PrincipalAxesAlignmentStartGenerator instance with a copy of the state of the \e %PrincipalAxesAlignmentStartGenerator instance \a gen.
    # \param gen The \e %PrincipalAxesAlignmentStartGenerator instance to copy.
    # 
    def __init__(gen: PrincipalAxesAlignmentStartGenerator) -> None: pass

    ##
    # \brief 
    # \param thresh 
    #
    def setSymmetryThreshold(thresh: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSymmetryThreshold() -> float: pass

    ##
    # \brief 
    # \param generate 
    #
    def genShapeCenterStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genShapeCenterStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genColorCenterStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genNonColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genNonColorCenterStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genRandomStarts(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genRandomStarts() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genForAlignedShapeCenters(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genForAlignedShapeCenters() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genForReferenceShapeCenters(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genForReferenceShapeCenters() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def genForLargerShapeCenters(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def genForLargerShapeCenters() -> bool: pass

    ##
    # \brief 
    # \param max_trans 
    #
    def setMaxRandomTranslation(max_trans: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxRandomTranslation() -> float: pass

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
    # \param seed 
    #
    def setRandomSeed(seed: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PrincipalAxesAlignmentStartGenerator instance \a gen.
    # \param gen The \e %PrincipalAxesAlignmentStartGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: PrincipalAxesAlignmentStartGenerator) -> PrincipalAxesAlignmentStartGenerator: pass

    symmetryThreshold = property(getSymmetryThreshold, setSymmetryThreshold)

    maxRandomTranslation = property(getMaxRandomTranslation, setMaxRandomTranslation)

    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    shapeCenterStarts = property(genShapeCenterStarts, genShapeCenterStarts)

    colorCenterStarts = property(genColorCenterStarts, genColorCenterStarts)

    nonColorCenterStarts = property(genNonColorCenterStarts, genNonColorCenterStarts)

    randomStarts = property(getNumRandomStarts, setNumRandomStarts)

    genForAlignedShapeCtrs = property(genForAlignedShapeCenters, genForAlignedShapeCenters)

    genForReferenceShapeCrs = property(genForReferenceShapeCenters, genForReferenceShapeCenters)

    genForLargerShapeCtrs = property(genForLargerShapeCenters, genForLargerShapeCenters)
