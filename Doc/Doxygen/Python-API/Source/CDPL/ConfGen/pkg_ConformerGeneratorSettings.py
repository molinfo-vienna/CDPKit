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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ConformerGeneratorSettings instance.
    # \param settings 
    #
    def __init__(settings: ConformerGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ConformerGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ConformerGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ConformerGeneratorSettings instance \a settings.
    # \param settings The \e %ConformerGeneratorSettings instance to copy.
    # \return \a self
    #
    def assign(settings: ConformerGeneratorSettings) -> ConformerGeneratorSettings: pass

    ##
    # \brief 
    # \param mode 
    #
    def setSamplingMode(mode: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSamplingMode() -> int: pass

    ##
    # \brief 
    # \param sample 
    #
    def sampleHeteroAtomHydrogens(sample: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def sampleHeteroAtomHydrogens() -> bool: pass

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
    # \param enumerate 
    #
    def enumerateRings(enumerate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def enumerateRings() -> bool: pass

    ##
    # \brief 
    # \param mode 
    #
    def setNitrogenEnumerationMode(mode: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNitrogenEnumerationMode() -> int: pass

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
    # \param include 
    #
    def includeInputCoordinates(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def includeInputCoordinates() -> bool: pass

    ##
    # \brief 
    # \param win_size 
    #
    def setEnergyWindow(win_size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEnergyWindow() -> float: pass

    ##
    # \brief 
    # \param max_size 
    #
    def setMaxPoolSize(max_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxPoolSize() -> int: pass

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
    def setForceFieldTypeSystematic(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getForceFieldTypeSystematic() -> int: pass

    ##
    # \brief 
    # \param type 
    #
    def setForceFieldTypeStochastic(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getForceFieldTypeStochastic() -> int: pass

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
    def setMaxNumOutputConformers(max_num: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumOutputConformers() -> int: pass

    ##
    # \brief 
    # \param min_rmsd 
    #
    def setMinRMSD(min_rmsd: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinRMSD() -> float: pass

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
    def setRefinementStopGradient(tol: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRefinementTolerance() -> float: pass

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
    # \return 
    #
    def getFragmentBuildSettings() -> FragmentConformerGeneratorSettings: pass

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
