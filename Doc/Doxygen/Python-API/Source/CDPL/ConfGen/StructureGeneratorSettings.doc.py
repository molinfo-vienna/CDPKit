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
# \brief Bundle of configuration parameters for ConfGen.StructureGenerator.
# 
class StructureGeneratorSettings(Boost.Python.instance):

    ##
    # \brief A static instance providing settings default values.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Constructs the <tt>StructureGeneratorSettings</tt> instance with default values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %StructureGeneratorSettings instance \a settings.
    # \param settings The \c %StructureGeneratorSettings instance to copy.
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
    # \brief Sets the structure-generation mode (see ConfGen.StructureGenerationMode).
    # 
    # \param mode The new generation mode.
    # 
    def setGenerationMode(mode: int) -> None: pass

    ##
    # \brief Returns the currently configured structure-generation mode.
    # 
    # \return The ConfGen.StructureGenerationMode identifier.
    # 
    def getGenerationMode() -> int: pass

    ##
    # \brief Specifies whether 3D coordinates should be generated from scratch (vs. starting from existing input coordinates).
    # 
    # \param generate <tt>True</tt> to generate coordinates from scratch, and <tt>False</tt> to keep existing input coordinates.
    # 
    def generateCoordinatesFromScratch(generate: bool) -> None: pass

    ##
    # \brief Tells whether 3D coordinates are generated from scratch.
    # 
    # \return <tt>True</tt> if coordinates are generated from scratch, and <tt>False</tt> otherwise.
    # 
    def generateCoordinatesFromScratch() -> bool: pass

    ##
    # \brief Specifies whether torsion-angle tolerance ranges are sampled during structure generation.
    # 
    # \param sample <tt>True</tt> to enable sampling, and <tt>False</tt> to disable it.
    # 
    def sampleAngleToleranceRanges(sample: bool) -> None: pass

    ##
    # \brief Tells whether torsion-angle tolerance ranges are sampled during structure generation.
    # 
    # \return <tt>True</tt> if sampling is enabled, and <tt>False</tt> otherwise.
    # 
    def sampleAngleToleranceRanges() -> bool: pass

    ##
    # \brief Sets the timeout for the structure-generation pipeline.
    # 
    # \param mil_secs The new timeout in milliseconds (<em>0</em> disables the timeout).
    # 
    def setTimeout(mil_secs: int) -> None: pass

    ##
    # \brief Returns the currently configured timeout in milliseconds.
    # 
    # \return The timeout in milliseconds.
    # 
    def getTimeout() -> int: pass

    ##
    # \brief Sets the MMFF94 force-field variant used for fragment-mode structure generation (see ForceField.MMFF94 variants).
    # 
    # \param type The new force-field type.
    # 
    def setFragmentModeForceFieldType(type: int) -> None: pass

    ##
    # \brief Returns the currently configured fragment-mode force-field type.
    # 
    # \return The force-field type identifier.
    # 
    def getFragmentModeForceFieldType() -> int: pass

    ##
    # \brief Sets the MMFF94 force-field variant used for distance-geometry-mode structure generation.
    # 
    # \param type The new force-field type.
    # 
    def setDGModeForceFieldType(type: int) -> None: pass

    ##
    # \brief Returns the currently configured DG-mode force-field type.
    # 
    # \return The force-field type identifier.
    # 
    def getDGModeForceFieldType() -> int: pass

    ##
    # \brief Specifies whether force-field parameterization should be strict (missing parameters cause failure).
    # 
    # \param strict <tt>True</tt> to enable strict parameterization, and <tt>False</tt> to tolerate missing parameters.
    # 
    def strictForceFieldParameterization(strict: bool) -> None: pass

    ##
    # \brief Tells whether force-field parameterization is strict.
    # 
    # \return <tt>True</tt> if strict parameterization is enabled, and <tt>False</tt> otherwise.
    # 
    def strictForceFieldParameterization() -> bool: pass

    ##
    # \brief Sets the dielectric constant used in the electrostatic-energy term.
    # 
    # \param de_const The new dielectric constant.
    # 
    def setDielectricConstant(de_const: float) -> None: pass

    ##
    # \brief Returns the currently configured dielectric constant.
    # 
    # \return The dielectric constant.
    # 
    def getDielectricConstant() -> float: pass

    ##
    # \brief 
    # \param dist_expo 
    #
    def setDistanceExponent(dist_expo: float) -> None: pass

    ##
    # \brief Returns the currently configured distance exponent.
    # 
    # \return The distance exponent.
    # 
    def getDistanceExponent() -> float: pass

    ##
    # \brief 
    # \param max_num 
    #
    def setMaxNumRefinementIterations(max_num: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum number of refinement iterations.
    # 
    # \return The maximum number of iterations.
    # 
    def getMaxNumRefinementIterations() -> int: pass

    ##
    # \brief Sets the convergence tolerance of the force-field-based coordinate refinement step.
    # 
    # \param tol The new refinement tolerance.
    # 
    def setRefinementTolerance(tol: float) -> None: pass

    ##
    # \brief Returns the currently configured refinement tolerance.
    # 
    # \return The refinement tolerance.
    # 
    def getRefinementTolerance() -> float: pass

    ##
    # \brief 
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(max_size: int) -> None: pass

    ##
    # \brief Returns the currently configured macrocycle rotor-bond-count threshold.
    # 
    # \return The threshold.
    # 
    def getMacrocycleRotorBondCountThreshold() -> int: pass

    ##
    # \brief Sets the maximum number of conformers sampled during structure generation.
    # 
    # \param max_num The new maximum number of sampled conformers.
    # 
    def setMaxNumSampledConformers(max_num: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum number of sampled conformers.
    # 
    # \return The maximum number of sampled conformers.
    # 
    def getMaxNumSampledConformers() -> int: pass

    ##
    # \brief Sets the cycle size for the convergence check of the structure-sampling loop.
    # 
    # \param size The new convergence-check cycle size.
    # 
    def setConvergenceCheckCycleSize(size: int) -> None: pass

    ##
    # \brief Returns the currently configured convergence-check cycle size.
    # 
    # \return The convergence-check cycle size.
    # 
    def getConvergenceCheckCycleSize() -> int: pass

    ##
    # \brief Returns the embedded fragment-build settings.
    # 
    # \return A reference to the fragment-build settings.
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
