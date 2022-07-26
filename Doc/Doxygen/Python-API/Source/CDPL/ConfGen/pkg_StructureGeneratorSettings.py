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
class StructureGeneratorSettings(Boost.Python.instance):

    ##
    # \brief FIXME!
    #
    DEFAULT = _UNKNOWN_VALUE_

    ##
    # \brief Initializes the \e %StructureGeneratorSettings instance.
    # \param self The \e %StructureGeneratorSettings instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %StructureGeneratorSettings instance.
    # \param self The \e %StructureGeneratorSettings instance to initialize.
    # \param settings 
    #
    def __init__(self: object, settings: StructureGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    #
    # Different Python \e %StructureGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StructureGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %StructureGeneratorSettings instance \a settings.
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param settings The \e %StructureGeneratorSettings instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: StructureGeneratorSettings, settings: StructureGeneratorSettings) -> StructureGeneratorSettings: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param mode 
    #
    def setGenerationMode(self: StructureGeneratorSettings, mode: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getGenerationMode(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param generate 
    #
    def generateCoordinatesFromScratch(self: StructureGeneratorSettings, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def generateCoordinatesFromScratch(self: StructureGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param sample 
    #
    def sampleAngleToleranceRanges(self: StructureGeneratorSettings, sample: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def sampleAngleToleranceRanges(self: StructureGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param mil_secs 
    #
    def setTimeout(self: StructureGeneratorSettings, mil_secs: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getTimeout(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param type 
    #
    def setFragmentModeForceFieldType(self: StructureGeneratorSettings, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getFragmentModeForceFieldType(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param type 
    #
    def setDGModeForceFieldType(self: StructureGeneratorSettings, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDGModeForceFieldType(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param strict 
    #
    def strictForceFieldParameterization(self: StructureGeneratorSettings, strict: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def strictForceFieldParameterization(self: StructureGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param de_const 
    #
    def setDielectricConstant(self: StructureGeneratorSettings, de_const: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDielectricConstant(self: StructureGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param dist_expo 
    #
    def setDistanceExponent(self: StructureGeneratorSettings, dist_expo: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDistanceExponent(self: StructureGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumRefinementIterations(self: StructureGeneratorSettings, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumRefinementIterations(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param tol 
    #
    def setRefinementTolerance(self: StructureGeneratorSettings, tol: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getRefinementTolerance(self: StructureGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(self: StructureGeneratorSettings, max_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMacrocycleRotorBondCountThreshold(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumSampledConformers(self: StructureGeneratorSettings, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumSampledConformers(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \param size 
    #
    def setConvergenceCheckCycleSize(self: StructureGeneratorSettings, size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getConvergenceCheckCycleSize(self: StructureGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getFragmentBuildSettings(self: StructureGeneratorSettings) -> FragmentConformerGeneratorSettings: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    generationMode = property(getGenerationMode, setGenerationMode)

    ##
    # \brief FIXME!
    #
    genCoordsFromScratch = property(getGenCoordsFromScratch, setGenCoordsFromScratch)

    ##
    # \brief FIXME!
    #
    sampleAngleTolRanges = property(getSampleAngleTolRanges, setSampleAngleTolRanges)

    ##
    # \brief 
    #
    timeout = property(getTimeout, setTimeout)

    ##
    # \brief FIXME!
    #
    fragModeForceFieldType = property(getFragModeForceFieldType, setFragModeForceFieldType)

    ##
    # \brief FIXME!
    #
    dgModeForceFieldType = property(getDgModeForceFieldType, setDgModeForceFieldType)

    ##
    # \brief FIXME!
    #
    strictForceFieldParam = property(getStrictForceFieldParam, setStrictForceFieldParam)

    ##
    # \brief 
    #
    dielectricConstant = property(getDielectricConstant, setDielectricConstant)

    ##
    # \brief 
    #
    distanceExponent = property(getDistanceExponent, setDistanceExponent)

    ##
    # \brief 
    #
    maxNumRefinementIterations = property(getMaxNumRefinementIterations, setMaxNumRefinementIterations)

    ##
    # \brief 
    #
    refinementTolerance = property(getRefinementTolerance, setRefinementTolerance)

    ##
    # \brief FIXME!
    #
    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThresh, setMacrocycleRotorBondCountThresh)

    ##
    # \brief 
    #
    maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

    ##
    # \brief FIXME!
    #
    convCheckCycleSize = property(getConvCheckCycleSize, setConvCheckCycleSize)

    ##
    # \brief 
    #
    fragmentBuildSettings = property(getFragmentBuildSettings)
