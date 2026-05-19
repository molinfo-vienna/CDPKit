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
# \brief Generator that produces alignment starting transformations by aligning the principal axes of the aligned shape to those of the reference shape.
# 
# Starting transformations can be derived from any combination of (a) the shape centroid, (b) shape element (atom) centers, (c) color (pharmacophore) feature centers, and (d) random rotations applied to translated centers. The exact combination of starts is configured via the various <tt>gen*</tt> setter methods.
# 
class PrincipalAxesAlignmentStartGenerator(GaussianShapeAlignmentStartGenerator):

    ##
    # \brief Default relative threshold for treating two principal moments as equal.
    # 
    DEF_SYMMETRY_THRESHOLD = 0.15

    ##
    # \brief Default number of random starting transformations.
    # 
    DEF_NUM_RANDOM_STARTS = 4

    ##
    # \brief Default maximum random translation magnitude applied to random starts.
    # 
    DEF_MAX_RANDOM_TRANSLATION = 2.0

    ##
    # \brief Constructs the <tt>PrincipalAxesAlignmentStartGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %PrincipalAxesAlignmentStartGenerator instance \a gen.
    # \param gen The \c %PrincipalAxesAlignmentStartGenerator instance to copy.
    # 
    def __init__(gen: PrincipalAxesAlignmentStartGenerator) -> None: pass

    ##
    # \brief Sets the relative threshold for treating two principal moments as equal.
    # 
    # \param thresh The new symmetry threshold.
    # 
    def setSymmetryThreshold(thresh: float) -> None: pass

    ##
    # \brief Returns the currently configured symmetry threshold.
    # 
    # \return The symmetry threshold.
    # 
    def getSymmetryThreshold() -> float: pass

    ##
    # \brief Enables or disables the generation of a starting transformation at the shape centroid.
    # 
    # \param generate <tt>True</tt> to enable the shape-centroid start, and <tt>False</tt> to disable it.
    # 
    def genShapeCenterStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether a starting transformation at the shape centroid is generated.
    # 
    # \return <tt>True</tt> if a shape-centroid start is generated, and <tt>False</tt> otherwise.
    # 
    def genShapeCenterStarts() -> bool: pass

    ##
    # \brief Enables or disables the generation of starting transformations at color (pharmacophore) feature centers.
    # 
    # \param generate <tt>True</tt> to enable the color-center starts, and <tt>False</tt> to disable them.
    # 
    def genColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether starting transformations at color (pharmacophore) feature centers are generated.
    # 
    # \return <tt>True</tt> if color-center starts are generated, and <tt>False</tt> otherwise.
    # 
    def genColorCenterStarts() -> bool: pass

    ##
    # \brief Enables or disables the generation of starting transformations at non-color (shape) element centers.
    # 
    # \param generate <tt>True</tt> to enable the non-color-center starts, and <tt>False</tt> to disable them.
    # 
    def genNonColorCenterStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether starting transformations at non-color (shape) element centers are generated.
    # 
    # \return <tt>True</tt> if non-color-center starts are generated, and <tt>False</tt> otherwise.
    # 
    def genNonColorCenterStarts() -> bool: pass

    ##
    # \brief Enables or disables the generation of random starting transformations.
    # 
    # \param generate <tt>True</tt> to enable the random starts, and <tt>False</tt> to disable them.
    # 
    def genRandomStarts(generate: bool) -> None: pass

    ##
    # \brief Tells whether random starting transformations are generated.
    # 
    # \return <tt>True</tt> if random starts are generated, and <tt>False</tt> otherwise.
    # 
    def genRandomStarts() -> bool: pass

    ##
    # \brief Specifies whether element-/color-center starts shall be generated for centers of the aligned shape.
    # 
    # \param generate <tt>True</tt> to consider aligned-shape centers, and <tt>False</tt> to ignore them.
    # 
    def genForAlignedShapeCenters(generate: bool) -> None: pass

    ##
    # \brief Tells whether element-/color-center starts are generated for centers of the aligned shape.
    # 
    # \return <tt>True</tt> if aligned-shape centers are considered, and <tt>False</tt> otherwise.
    # 
    def genForAlignedShapeCenters() -> bool: pass

    ##
    # \brief Specifies whether element-/color-center starts shall be generated for centers of the reference shape.
    # 
    # \param generate <tt>True</tt> to consider reference-shape centers, and <tt>False</tt> to ignore them.
    # 
    def genForReferenceShapeCenters(generate: bool) -> None: pass

    ##
    # \brief Tells whether element-/color-center starts are generated for centers of the reference shape.
    # 
    # \return <tt>True</tt> if reference-shape centers are considered, and <tt>False</tt> otherwise.
    # 
    def genForReferenceShapeCenters() -> bool: pass

    ##
    # \brief Specifies whether element-/color-center starts shall be generated for centers of the shape with more elements (instead of both shapes).
    # 
    # \param generate <tt>True</tt> to use only the centers of the larger shape, and <tt>False</tt> to use the centers of all configured shapes.
    # 
    def genForLargerShapeCenters(generate: bool) -> None: pass

    ##
    # \brief Tells whether element-/color-center starts are generated for centers of the shape with more elements (instead of both shapes).
    # 
    # \return <tt>True</tt> if only the centers of the larger shape are used, and <tt>False</tt> otherwise.
    # 
    def genForLargerShapeCenters() -> bool: pass

    ##
    # \brief Sets the maximum random translation magnitude applied to random starts.
    # 
    # \param max_trans The new maximum random translation magnitude.
    # 
    def setMaxRandomTranslation(max_trans: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum random translation.
    # 
    # \return The maximum random translation magnitude.
    # 
    def getMaxRandomTranslation() -> float: pass

    ##
    # \brief Sets the number of random starting transformations.
    # 
    # \param num_starts The new number of random starts.
    # 
    def setNumRandomStarts(num_starts: int) -> None: pass

    ##
    # \brief Returns the currently configured number of random starts.
    # 
    # \return The number of random starts.
    # 
    def getNumRandomStarts() -> int: pass

    ##
    # \brief Sets the seed used by the random number generator that produces the random starts.
    # 
    # \param seed The new random seed.
    # 
    def setRandomSeed(seed: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %PrincipalAxesAlignmentStartGenerator instance \a gen.
    # \param gen The \c %PrincipalAxesAlignmentStartGenerator instance to copy.
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
