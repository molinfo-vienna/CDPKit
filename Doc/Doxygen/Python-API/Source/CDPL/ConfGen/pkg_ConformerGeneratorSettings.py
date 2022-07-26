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
class ConformerGeneratorSettings(Boost.Python.instance):

    ##
    # \brief FIXME!
    #
    DEFAULT = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    SMALL_SET_DIVERSE = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    MEDIUM_SET_DIVERSE = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    LARGE_SET_DIVERSE = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    SMALL_SET_DENSE = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    MEDIUM_SET_DENSE = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    LARGE_SET_DENSE = _UNKNOWN_VALUE_

    ##
    # \brief Initializes the \e %ConformerGeneratorSettings instance.
    # \param self The \e %ConformerGeneratorSettings instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ConformerGeneratorSettings instance.
    # \param self The \e %ConformerGeneratorSettings instance to initialize.
    # \param settings 
    #
    def __init__(self: object, settings: ConformerGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    #
    # Different Python \e %ConformerGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ConformerGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConformerGeneratorSettings instance \a settings.
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param settings The \e %ConformerGeneratorSettings instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ConformerGeneratorSettings, settings: ConformerGeneratorSettings) -> ConformerGeneratorSettings: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param mode 
    #
    def setSamplingMode(self: ConformerGeneratorSettings, mode: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getSamplingMode(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param sample 
    #
    def sampleHeteroAtomHydrogens(self: ConformerGeneratorSettings, sample: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def sampleHeteroAtomHydrogens(self: ConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param sample 
    #
    def sampleAngleToleranceRanges(self: ConformerGeneratorSettings, sample: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def sampleAngleToleranceRanges(self: ConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param enumerate 
    #
    def enumerateRings(self: ConformerGeneratorSettings, enumerate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def enumerateRings(self: ConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param mode 
    #
    def setNitrogenEnumerationMode(self: ConformerGeneratorSettings, mode: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getNitrogenEnumerationMode(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param generate 
    #
    def generateCoordinatesFromScratch(self: ConformerGeneratorSettings, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def generateCoordinatesFromScratch(self: ConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param include 
    #
    def includeInputCoordinates(self: ConformerGeneratorSettings, include: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def includeInputCoordinates(self: ConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param win_size 
    #
    def setEnergyWindow(self: ConformerGeneratorSettings, win_size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getEnergyWindow(self: ConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param max_size 
    #
    def setMaxPoolSize(self: ConformerGeneratorSettings, max_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxPoolSize(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param mil_secs 
    #
    def setTimeout(self: ConformerGeneratorSettings, mil_secs: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getTimeout(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param type 
    #
    def setForceFieldTypeSystematic(self: ConformerGeneratorSettings, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getForceFieldTypeSystematic(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param type 
    #
    def setForceFieldTypeStochastic(self: ConformerGeneratorSettings, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getForceFieldTypeStochastic(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param strict 
    #
    def strictForceFieldParameterization(self: ConformerGeneratorSettings, strict: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def strictForceFieldParameterization(self: ConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param de_const 
    #
    def setDielectricConstant(self: ConformerGeneratorSettings, de_const: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDielectricConstant(self: ConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param dist_expo 
    #
    def setDistanceExponent(self: ConformerGeneratorSettings, dist_expo: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDistanceExponent(self: ConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumOutputConformers(self: ConformerGeneratorSettings, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumOutputConformers(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param min_rmsd 
    #
    def setMinRMSD(self: ConformerGeneratorSettings, min_rmsd: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMinRMSD(self: ConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumRefinementIterations(self: ConformerGeneratorSettings, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumRefinementIterations(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param tol 
    #
    def setRefinementStopGradient(self: ConformerGeneratorSettings, tol: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getRefinementTolerance(self: ConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumSampledConformers(self: ConformerGeneratorSettings, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumSampledConformers(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param size 
    #
    def setConvergenceCheckCycleSize(self: ConformerGeneratorSettings, size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getConvergenceCheckCycleSize(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(self: ConformerGeneratorSettings, max_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMacrocycleRotorBondCountThreshold(self: ConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getFragmentBuildSettings(self: ConformerGeneratorSettings) -> FragmentConformerGeneratorSettings: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    samplingMode = property(getSamplingMode, setSamplingMode)

    ##
    # \brief FIXME!
    #
    sampleHetAtomHydrogens = property(getSampleHetAtomHydrogens, setSampleHetAtomHydrogens)

    ##
    # \brief FIXME!
    #
    sampleAngleTolRanges = property(getSampleAngleTolRanges, setSampleAngleTolRanges)

    ##
    # \brief FIXME!
    #
    enumRings = property(getEnumRings, setEnumRings)

    ##
    # \brief FIXME!
    #
    nitrogenEnumMode = property(getNitrogenEnumMode, setNitrogenEnumMode)

    ##
    # \brief FIXME!
    #
    genCoordsFromScratch = property(getGenCoordsFromScratch, setGenCoordsFromScratch)

    ##
    # \brief FIXME!
    #
    includeInputCoords = property(getIncludeInputCoords, setIncludeInputCoords)

    ##
    # \brief 
    #
    energyWindow = property(getEnergyWindow, setEnergyWindow)

    ##
    # \brief 
    #
    maxPoolSize = property(getMaxPoolSize, setMaxPoolSize)

    ##
    # \brief 
    #
    timeout = property(getTimeout, setTimeout)

    ##
    # \brief 
    #
    forceFieldTypeSystematic = property(getForceFieldTypeSystematic, setForceFieldTypeSystematic)

    ##
    # \brief 
    #
    forceFieldTypeStochastic = property(getForceFieldTypeStochastic, setForceFieldTypeStochastic)

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
    maxNumOutputConformers = property(getMaxNumOutputConformers, setMaxNumOutputConformers)

    ##
    # \brief 
    #
    minRMSD = property(getMinRMSD, setMinRMSD)

    ##
    # \brief 
    #
    maxNumRefinementIterations = property(getMaxNumRefinementIterations, setMaxNumRefinementIterations)

    ##
    # \brief 
    #
    refinementTolerance = property(getRefinementTolerance, setRefinementTolerance)

    ##
    # \brief 
    #
    maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

    ##
    # \brief FIXME!
    #
    convCheckCycleSize = property(getConvCheckCycleSize, setConvCheckCycleSize)

    ##
    # \brief FIXME!
    #
    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThresh, setMacrocycleRotorBondCountThresh)

    ##
    # \brief 
    #
    fragmentBuildSettings = property(getFragmentBuildSettings)
