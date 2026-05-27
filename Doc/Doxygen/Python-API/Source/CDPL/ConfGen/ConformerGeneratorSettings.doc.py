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
# \brief Bundle of configuration parameters for conformer ensemble generation via class ConfGen.ConformerGenerator.
# 
class ConformerGeneratorSettings(Boost.Python.instance):

    ##
    # \brief Instance providing configuration parameter default values.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Preset producing a small, diversity-optimized conformer ensemble.
    # 
    SMALL_SET_DIVERSE = _HIDDEN_VALUE_

    ##
    # \brief Preset producing a medium-sized, diversity-optimized conformer ensemble.
    # 
    MEDIUM_SET_DIVERSE = _HIDDEN_VALUE_

    ##
    # \brief Preset producing a large, diversity-optimized conformer ensemble.
    # 
    LARGE_SET_DIVERSE = _HIDDEN_VALUE_

    ##
    # \brief Preset producing a small, dense conformer ensemble (tight RMSD threshold).
    # 
    SMALL_SET_DENSE = _HIDDEN_VALUE_

    ##
    # \brief Preset producing a medium-sized, dense conformer ensemble (tight RMSD threshold).
    # 
    MEDIUM_SET_DENSE = _HIDDEN_VALUE_

    ##
    # \brief Preset producing a large, dense conformer ensemble (tight RMSD threshold).
    # 
    LARGE_SET_DENSE = _HIDDEN_VALUE_

    ##
    # \brief Constructs the <tt>ConformerGeneratorSettings</tt> instance with default configuration parameter values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %ConformerGeneratorSettings instance \a settings.
    # \param settings The \c %ConformerGeneratorSettings instance to copy.
    # 
    def __init__(settings: ConformerGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ConformerGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ConformerGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConformerGeneratorSettings instance \a settings.
    # \param settings The \c %ConformerGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: ConformerGeneratorSettings) -> ConformerGeneratorSettings: pass

    ##
    # \brief Specifies the conformer-sampling strategy to use.
    # 
    # \param mode One of the ConfGen.ConformerSamplingMode values.
    # 
    def setSamplingMode(mode: int) -> None: pass

    ##
    # \brief Returns the currently configured conformer-sampling strategy.
    # 
    # \return One of the ConfGen.ConformerSamplingMode values.
    # 
    def getSamplingMode() -> int: pass

    ##
    # \brief Specifies whether torsions of heteroatom hydrogen rotors shall be sampled.
    # 
    # \param sample If <tt>True</tt>, such torsions are sampled.
    # 
    def sampleHeteroAtomHydrogens(sample: bool) -> None: pass

    ##
    # \brief Tells whether torsions of heteroatom hydrogen rotors are sampled.
    # 
    # \return <tt>True</tt> if sampling is enabled, and <tt>False</tt> otherwise.
    # 
    def sampleHeteroAtomHydrogens() -> bool: pass

    ##
    # \brief Specifies whether additional torsion samples within the tolerance ranges defined by the torsion library entries shall be generated.
    # 
    # \param sample If <tt>True</tt>, tolerance-range sampling is enabled.
    # 
    def sampleAngleToleranceRanges(sample: bool) -> None: pass

    ##
    # \brief Tells whether tolerance-range sampling is enabled.
    # 
    # \return <tt>True</tt> if tolerance-range sampling is enabled, and <tt>False</tt> otherwise.
    # 
    def sampleAngleToleranceRanges() -> bool: pass

    ##
    # \brief Specifies whether ring conformations shall be enumerated.
    # 
    # \param enumerate If <tt>True</tt>, ring conformations are enumerated.
    # 
    def enumerateRings(enumerate: bool) -> None: pass

    ##
    # \brief Tells whether ring conformations are enumerated.
    # 
    # \return <tt>True</tt> if ring conformations are enumerated, and <tt>False</tt> otherwise.
    # 
    def enumerateRings() -> bool: pass

    ##
    # \brief Sets the enumeration mode for stereogenic nitrogen centers.
    # 
    # \param mode One of the ConfGen.NitrogenEnumerationMode values.
    # 
    def setNitrogenEnumerationMode(mode: int) -> None: pass

    ##
    # \brief Returns the currently configured nitrogen enumeration mode.
    # 
    # \return One of the ConfGen.NitrogenEnumerationMode values.
    # 
    def getNitrogenEnumerationMode() -> int: pass

    ##
    # \brief Specifies whether 3D coordinates shall be generated from scratch (ignoring any 3D input).
    # 
    # \param generate If <tt>True</tt>, 3D coordinates are always generated from scratch.
    # 
    def generateCoordinatesFromScratch(generate: bool) -> None: pass

    ##
    # \brief Tells whether 3D coordinates are generated from scratch.
    # 
    # \return <tt>True</tt> if 3D coordinates are always regenerated, and <tt>False</tt> otherwise.
    # 
    def generateCoordinatesFromScratch() -> bool: pass

    ##
    # \brief Specifies whether the input conformation shall be included in the output conformer ensemble.
    # 
    # \param include If <tt>True</tt>, the input coordinates become part of the output ensemble.
    # 
    def includeInputCoordinates(include: bool) -> None: pass

    ##
    # \brief Tells whether the input coordinates are included in the output conformer ensemble.
    # 
    # \return <tt>True</tt> if the input coordinates are included, and <tt>False</tt> otherwise.
    # 
    def includeInputCoordinates() -> bool: pass

    ##
    # \brief Sets the energy window size (in kcal/mol) above the found global minimum within which conformers are kept.
    # 
    # \param win_size The new energy window size in kcal/mol.
    # 
    def setEnergyWindow(win_size: float) -> None: pass

    ##
    # \brief Returns the configured energy window size.
    # 
    # \return The energy window size in kcal/mol.
    # 
    def getEnergyWindow() -> float: pass

    ##
    # \brief Returns the energy window size that applies for molecules with <em>num_rot_bonds</em> rotatable bonds.
    # 
    # If a rotatable bond-specific range was registered via addEnergyWindowRange(), the matching value is returned; otherwise the global window from getEnergyWindow() is used.
    # 
    # \param num_rot_bonds The rotatable bond count.
    # 
    # \return The energy window size in kcal/mol. 
    # 
    # \since 1.1
    # 
    def getEnergyWindow(num_rot_bonds: int) -> float: pass

    ##
    # \brief Removes all registered rotatable bond count-dependent energy window overrides.
    # 
    # \since 1.1
    # 
    def clearEnergyWindowRanges() -> None: pass

    ##
    # \brief Registers an energy window override that applies up to and including <em>num_rot_bonds</em> rotatable bonds.
    # 
    # \param num_rot_bonds The upper-bound rotatable bond count to which <em>win_size</em> applies.
    # \param win_size The energy window size (in kcal/mol).
    # 
    # \since 1.1
    # 
    def addEnergyWindowRange(num_rot_bonds: int, win_size: float) -> None: pass

    ##
    # \brief Sets the maximum number of conformers to keep in the internal candidate pool.
    # 
    # \param max_size The new maximum pool size.
    # 
    def setMaxPoolSize(max_size: int) -> None: pass

    ##
    # \brief Returns the maximum number of conformers kept in the internal candidate pool.
    # 
    # \return The maximum pool size.
    # 
    def getMaxPoolSize() -> int: pass

    ##
    # \brief Sets the upper limit on the number of rotatable bonds an input molecule may have to be processed.
    # 
    # \param max_count The new rotatable bond count limit (<em>-1</em> disables the limit).
    # 
    # \since 1.1
    # 
    def setMaxRotatableBondCount(max_count: int) -> None: pass

    ##
    # \brief Returns the rotatable bond count limit above which input molecules are rejected.
    # 
    # \return The rotatable bond count limit (<em>-1</em> disables the limit). 
    # 
    # \since 1.1
    # 
    def getMaxRotatableBondCount() -> int: pass

    ##
    # \brief Sets the maximum allowed wall clock processing time per molecule.
    # 
    # \param mil_secs The new time limit in milliseconds (zero disables the limit).
    # 
    def setTimeout(mil_secs: int) -> None: pass

    ##
    # \brief Returns the configured per-molecule wall clock time limit.
    # 
    # \return The time limit in milliseconds (zero if disabled).
    # 
    def getTimeout() -> int: pass

    ##
    # \brief Sets the force field type used by the systematic sampling pipeline.
    # 
    # \param type One of the ConfGen.ForceFieldType values.
    # 
    def setForceFieldTypeSystematic(type: int) -> None: pass

    ##
    # \brief Returns the force field type used by the systematic sampling pipeline.
    # 
    # \return One of the ConfGen.ForceFieldType values.
    # 
    def getForceFieldTypeSystematic() -> int: pass

    ##
    # \brief Sets the force field type used by the stochastic sampling pipeline.
    # 
    # \param type One of the ConfGen.ForceFieldType values.
    # 
    def setForceFieldTypeStochastic(type: int) -> None: pass

    ##
    # \brief Returns the force field type used by the stochastic sampling pipeline.
    # 
    # \return One of the ConfGen.ForceFieldType values.
    # 
    def getForceFieldTypeStochastic() -> int: pass

    ##
    # \brief Specifies whether strict MMFF94 parameterization is required.
    # 
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a generation failure. Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
    # 
    def strictForceFieldParameterization(strict: bool) -> None: pass

    ##
    # \brief Tells whether strict MMFF94 parameterization is required.
    # 
    # \return <tt>True</tt> if strict parameterization is required, and <tt>False</tt> otherwise.
    # 
    def strictForceFieldParameterization() -> bool: pass

    ##
    # \brief Sets the dielectric constant used by the MMFF94 electrostatic interactions.
    # 
    # \param de_const The new dielectric constant.
    # 
    def setDielectricConstant(de_const: float) -> None: pass

    ##
    # \brief Returns the dielectric constant used by the MMFF94 electrostatic interactions.
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
    # \brief Returns the exponent of the MMFF94 distance-dependent electrostatic term.
    # 
    # \return The distance exponent.
    # 
    def getDistanceExponent() -> float: pass

    ##
    # \brief Sets the maximum number of output conformers per molecule.
    # 
    # \param max_num The new output conformer count limit.
    # 
    def setMaxNumOutputConformers(max_num: int) -> None: pass

    ##
    # \brief Returns the configured maximum number of output conformers.
    # 
    # \return The output conformer count limit.
    # 
    def getMaxNumOutputConformers() -> int: pass

    ##
    # \brief Returns the maximum number of output conformers that applies for molecules with <em>num_rot_bonds</em> rotatable bonds.
    # 
    # If a rotatable bond-specific range was registered via addMaxNumOutputConformersRange(), the matching value is returned; otherwise the global limit from getMaxNumOutputConformers() is used.
    # 
    # \param num_rot_bonds The rotatable bond count.
    # 
    # \return The output conformer limit. 
    # 
    # \since 1.1
    # 
    def getMaxNumOutputConformers(num_rot_bonds: int) -> int: pass

    ##
    # \brief Removes all registered rotatable bond count-dependent output conformer overrides.
    # 
    # \since 1.1
    # 
    def clearMaxNumOutputConformersRanges() -> None: pass

    ##
    # \brief Registers an output conformer limit override that applies up to and including <em>num_rot_bonds</em> rotatable bonds.
    # 
    # \param num_rot_bonds The upper-bound rotatable bond count to which <em>max_num</em> applies.
    # \param max_num The output conformer limit used for matching molecules.
    # 
    # \since 1.1
    # 
    def addMaxNumOutputConformersRange(num_rot_bonds: int, max_num: int) -> None: pass

    ##
    # \brief Sets the minimum pairwise heavy-atom RMSD that conformers in the output ensemble must keep.
    # 
    # \param min_rmsd The new minimum RMSD threshold (in &Aring;).
    # 
    def setMinRMSD(min_rmsd: float) -> None: pass

    ##
    # \brief Returns the globally configured minimum RMSD threshold.
    # 
    # \return The minimum RMSD threshold (in &Aring;).
    # 
    def getMinRMSD() -> float: pass

    ##
    # \brief Returns the minimum RMSD threshold that applies for molecules with <em>num_rot_bonds</em> rotatable bonds.
    # 
    # If a rotatable bond-specific range was registered via addMinRMSDRange(), the matching value is returned; otherwise the global threshold from getMinRMSD() is used.
    # 
    # \param num_rot_bonds The rotatable bond count.
    # 
    # \return The minimum RMSD threshold (in &Aring;). 
    # 
    # \since 1.1
    # 
    def getMinRMSD(num_rot_bonds: int) -> float: pass

    ##
    # \brief Removes all registered rotatable bond count-dependent minimum RMSD overrides.
    # 
    # \since 1.1
    # 
    def clearMinRMSDRanges() -> None: pass

    ##
    # \brief Registers a minimum RMSD override that applies up to and including <em>num_rot_bonds</em> rotatable bonds.
    # 
    # \param num_rot_bonds The upper-bound rotatable bond count to which <em>min_rmsd</em> applies.
    # \param min_rmsd The minimum RMSD threshold used for matching molecules.
    # 
    # \since 1.1
    # 
    def addMinRMSDRange(num_rot_bonds: int, min_rmsd: float) -> None: pass

    ##
    # \brief 
    # \param max_num 
    #
    def setMaxNumRefinementIterations(max_num: int) -> None: pass

    ##
    # \brief Returns the maximum number of MMFF94 energy minimization iterations per conformer.
    # 
    # \return The iteration limit (zero if refinement is disabled).
    # 
    def getMaxNumRefinementIterations() -> int: pass

    ##
    # \brief 
    # \param tol 
    #
    def setRefinementStopGradient(tol: float) -> None: pass

    ##
    # \brief Returns the convergence tolerance of the MMFF94 energy minimization step.
    # 
    # \return The convergence tolerance.
    # 
    def getRefinementTolerance() -> float: pass

    ##
    # \brief Sets the upper bound on the number of trial conformations produced by the stochastic sampler.
    # 
    # \param max_num The new sampled conformer limit.
    # 
    def setMaxNumSampledConformers(max_num: int) -> None: pass

    ##
    # \brief Returns the upper bound on the number of trial conformations produced by the stochastic sampler.
    # 
    # \return The sampled conformer limit.
    # 
    def getMaxNumSampledConformers() -> int: pass

    ##
    # \brief Sets the cycle size (in trial conformations) at which the stochastic sampler tests for convergence.
    # 
    # \param size The new convergence check cycle size.
    # 
    def setConvergenceCheckCycleSize(size: int) -> None: pass

    ##
    # \brief Returns the cycle size at which the stochastic sampler tests for convergence.
    # 
    # \return The convergence check cycle size.
    # 
    def getConvergenceCheckCycleSize() -> int: pass

    ##
    # \brief 
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(max_size: int) -> None: pass

    ##
    # \brief Returns the flexible macrocycle rotatable bond count threshold.
    # 
    # \return The threshold.
    # 
    def getMacrocycleRotorBondCountThreshold() -> int: pass

    ##
    # \brief Returns a reference to the nested fragment conformer build settings.
    # 
    # \return A reference to the build settings.
    # 
    def getFragmentBuildSettings() -> FragmentConformerGeneratorSettings: pass

    objectID = property(getObjectID)

    samplingMode = property(getSamplingMode, setSamplingMode)

    sampleHetAtomHydrogens = property(sampleHeteroAtomHydrogens, sampleHeteroAtomHydrogens)

    sampleAngleTolRanges = property(sampleAngleToleranceRanges, sampleAngleToleranceRanges)

    enumRings = property(enumerateRings, enumerateRings)

    nitrogenEnumMode = property(getNitrogenEnumerationMode, setNitrogenEnumerationMode)

    genCoordsFromScratch = property(generateCoordinatesFromScratch, generateCoordinatesFromScratch)

    includeInputCoords = property(includeInputCoordinates, includeInputCoordinates)

    energyWindow = property(getEnergyWindow, setEnergyWindow)

    maxPoolSize = property(getMaxPoolSize, setMaxPoolSize)

    maxRotatableBondCount = property(getMaxRotatableBondCount, setMaxRotatableBondCount)

    timeout = property(getTimeout, setTimeout)

    forceFieldTypeSystematic = property(getForceFieldTypeSystematic, setForceFieldTypeSystematic)

    forceFieldTypeStochastic = property(getForceFieldTypeStochastic, setForceFieldTypeStochastic)

    strictForceFieldParam = property(strictForceFieldParameterization, strictForceFieldParameterization)

    dielectricConstant = property(getDielectricConstant, setDielectricConstant)

    distanceExponent = property(getDistanceExponent, setDistanceExponent)

    maxNumOutputConformers = property(getMaxNumOutputConformers, setMaxNumOutputConformers)

    minRMSD = property(getMinRMSD, setMinRMSD)

    maxNumRefinementIterations = property(getMaxNumRefinementIterations, setMaxNumRefinementIterations)

    refinementTolerance = property(getRefinementTolerance, setRefinementTolerance)

    maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

    convCheckCycleSize = property(getConvergenceCheckCycleSize, setConvergenceCheckCycleSize)

    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThreshold, setMacrocycleRotorBondCountThreshold)

    fragmentBuildSettings = property(getFragmentBuildSettings)
