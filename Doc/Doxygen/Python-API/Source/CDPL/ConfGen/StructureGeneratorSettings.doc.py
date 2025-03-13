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
class StructureGeneratorSettings(Boost.Python.instance):

    ##
    # \brief 
    #
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Initializes the \e %StructureGeneratorSettings instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %StructureGeneratorSettings instance \a settings.
    # \param settings The \e %StructureGeneratorSettings instance to copy.
    # 
    def __init__(settings: StructureGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %StructureGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StructureGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %StructureGeneratorSettings instance \a settings.
    # \param settings The \c %StructureGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: StructureGeneratorSettings) -> StructureGeneratorSettings: pass

    ##
    # \brief 
    # \param mode 
    #
    def setGenerationMode(mode: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGenerationMode() -> int: pass

    ##
    # \brief 
    # \param generate 
    #
    def generateCoordinatesFromScratch(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def generateCoordinatesFromScratch() -> bool: pass

    ##
    # \brief 
    # \param sample 
    #
    def sampleAngleToleranceRanges(sample: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def sampleAngleToleranceRanges() -> bool: pass

    ##
    # \brief 
    # \param mil_secs 
    #
    def setTimeout(mil_secs: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTimeout() -> int: pass

    ##
    # \brief 
    # \param type 
    #
    def setFragmentModeForceFieldType(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFragmentModeForceFieldType() -> int: pass

    ##
    # \brief 
    # \param type 
    #
    def setDGModeForceFieldType(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDGModeForceFieldType() -> int: pass

    ##
    # \brief 
    # \param strict 
    #
    def strictForceFieldParameterization(strict: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def strictForceFieldParameterization() -> bool: pass

    ##
    # \brief 
    # \param de_const 
    #
    def setDielectricConstant(de_const: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDielectricConstant() -> float: pass

    ##
    # \brief 
    # \param dist_expo 
    #
    def setDistanceExponent(dist_expo: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDistanceExponent() -> float: pass

    ##
    # \brief 
    # \param max_num 
    #
    def setMaxNumRefinementIterations(max_num: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumRefinementIterations() -> int: pass

    ##
    # \brief 
    # \param tol 
    #
    def setRefinementTolerance(tol: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRefinementTolerance() -> float: pass

    ##
    # \brief 
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(max_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMacrocycleRotorBondCountThreshold() -> int: pass

    ##
    # \brief 
    # \param max_num 
    #
    def setMaxNumSampledConformers(max_num: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumSampledConformers() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setConvergenceCheckCycleSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getConvergenceCheckCycleSize() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getFragmentBuildSettings() -> FragmentConformerGeneratorSettings: pass

    objectID = property(getObjectID)

    generationMode = property(getGenerationMode, setGenerationMode)

    genCoordsFromScratch = property(generateCoordinatesFromScratch, generateCoordinatesFromScratch)

    sampleAngleTolRanges = property(sampleAngleToleranceRanges, sampleAngleToleranceRanges)

    timeout = property(getTimeout, setTimeout)

    fragModeForceFieldType = property(getFragmentModeForceFieldType, setFragmentModeForceFieldType)

    dgModeForceFieldType = property(getDGModeForceFieldType, setDGModeForceFieldType)

    strictForceFieldParam = property(strictForceFieldParameterization, strictForceFieldParameterization)

    dielectricConstant = property(getDielectricConstant, setDielectricConstant)

    distanceExponent = property(getDistanceExponent, setDistanceExponent)

    maxNumRefinementIterations = property(getMaxNumRefinementIterations, setMaxNumRefinementIterations)

    refinementTolerance = property(getRefinementTolerance, setRefinementTolerance)

    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThreshold, setMacrocycleRotorBondCountThreshold)

    maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

    convCheckCycleSize = property(getConvergenceCheckCycleSize, setConvergenceCheckCycleSize)

    fragmentBuildSettings = property(getFragmentBuildSettings)
