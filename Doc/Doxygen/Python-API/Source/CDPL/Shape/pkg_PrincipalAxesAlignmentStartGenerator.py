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
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %PrincipalAxesAlignmentStartGenerator instance.
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: PrincipalAxesAlignmentStartGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param thresh 
    #
    def setSymmetryThreshold(self: PrincipalAxesAlignmentStartGenerator, thresh: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def getSymmetryThreshold(self: PrincipalAxesAlignmentStartGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genShapeCenterStarts(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genShapeCenterStarts(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genColorCenterStarts(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genColorCenterStarts(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genNonColorCenterStarts(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genNonColorCenterStarts(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genRandomStarts(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genRandomStarts(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genForAlignedShapeCenters(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genForAlignedShapeCenters(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genForReferenceShapeCenters(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genForReferenceShapeCenters(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param generate 
    #
    def genForLargerShapeCenters(self: PrincipalAxesAlignmentStartGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def genForLargerShapeCenters(self: PrincipalAxesAlignmentStartGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param max_trans 
    #
    def setMaxRandomTranslation(self: PrincipalAxesAlignmentStartGenerator, max_trans: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def getMaxRandomTranslation(self: PrincipalAxesAlignmentStartGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param num_starts 
    #
    def setNumRandomStarts(self: PrincipalAxesAlignmentStartGenerator, num_starts: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def getNumRandomStarts(self: PrincipalAxesAlignmentStartGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param seed 
    #
    def setRandomSeed(self: PrincipalAxesAlignmentStartGenerator, seed: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PrincipalAxesAlignmentStartGenerator instance \a gen.
    # \param self The \e %PrincipalAxesAlignmentStartGenerator instance this method is called upon.
    # \param gen The \e %PrincipalAxesAlignmentStartGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: PrincipalAxesAlignmentStartGenerator, gen: PrincipalAxesAlignmentStartGenerator) -> PrincipalAxesAlignmentStartGenerator: pass

    ##
    # \brief 
    #
    symmetryThreshold = property(getSymmetryThreshold, setSymmetryThreshold)

    ##
    # \brief 
    #
    maxRandomTranslation = property(getMaxRandomTranslation, setMaxRandomTranslation)

    ##
    # \brief 
    #
    numRandomStarts = property(getNumRandomStarts, setNumRandomStarts)

    ##
    # \brief FIXME!
    #
    shapeCenterStarts = property(getShapeCenterStarts, setShapeCenterStarts)

    ##
    # \brief FIXME!
    #
    colorCenterStarts = property(getColorCenterStarts, setColorCenterStarts)

    ##
    # \brief FIXME!
    #
    nonColorCenterStarts = property(getNonColorCenterStarts, setNonColorCenterStarts)

    ##
    # \brief FIXME!
    #
    randomStarts = property(getRandomStarts, setRandomStarts)

    ##
    # \brief FIXME!
    #
    genForAlignedShapeCtrs = property(getGenForAlignedShapeCtrs, setGenForAlignedShapeCtrs)

    ##
    # \brief FIXME!
    #
    genForReferenceShapeCrs = property(getGenForReferenceShapeCrs, setGenForReferenceShapeCrs)

    ##
    # \brief FIXME!
    #
    genForLargerShapeCtrs = property(getGenForLargerShapeCtrs, setGenForLargerShapeCtrs)
