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
# \brief Bundle of configuration parameters for ConfGen.FragmentConformerGenerator.
# 
class FragmentConformerGeneratorSettings(Boost.Python.instance):

    ##
    # \brief Per-fragment-class settings (separate parameters for chain, small-ring and macrocycle fragments).
    # 
    class FragmentSettings(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %FragmentSettings instance \a settings.
        # \param settings The \c %FragmentSettings instance to copy.
        # 
        def __init__(settings: FragmentSettings) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %FragmentSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentSettings instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentSettings instance \a settings.
        # \param settings The \c %FragmentSettings instance to copy.
        # \return \a self
        # 
        def assign(settings: FragmentSettings) -> FragmentSettings: pass

        ##
        # \brief Sets the maximum number of trial conformers sampled per fragment.
        # 
        # \param max_num The new sampled-conformer limit.
        # 
        def setMaxNumSampledConformers(max_num: int) -> None: pass

        ##
        # \brief Returns the maximum number of trial conformers sampled per fragment.
        # 
        # \return The sampled-conformer limit.
        # 
        def getMaxNumSampledConformers() -> int: pass

        ##
        # \brief Sets the minimum number of trial conformers sampled per fragment before convergence is tested.
        # 
        # \param min_num The new minimum sampled-conformer count.
        # 
        def setMinNumSampledConformers(min_num: int) -> None: pass

        ##
        # \brief Returns the minimum number of trial conformers sampled per fragment.
        # 
        # \return The minimum sampled-conformer count.
        # 
        def getMinNumSampledConformers() -> int: pass

        ##
        # \brief Sets the per-fragment wall-clock processing time limit.
        # 
        # \param mil_secs The new time limit in milliseconds (zero disables the limit).
        # 
        def setTimeout(mil_secs: int) -> None: pass

        ##
        # \brief Returns the per-fragment wall-clock processing time limit.
        # 
        # \return The time limit in milliseconds (zero if disabled).
        # 
        def getTimeout() -> int: pass

        ##
        # \brief Sets the energy-window size (in kcal/mol) above the fragment-conformer minimum within which fragment conformers are kept.
        # 
        # \param win_size The new energy-window size in kcal/mol.
        # 
        def setEnergyWindow(win_size: float) -> None: pass

        ##
        # \brief Returns the per-fragment energy-window size.
        # 
        # \return The energy-window size in kcal/mol.
        # 
        def getEnergyWindow() -> float: pass

        ##
        # \brief Sets the maximum number of output conformers per fragment.
        # 
        # \param max_num The new output-conformer limit.
        # 
        def setMaxNumOutputConformers(max_num: int) -> None: pass

        ##
        # \brief Returns the maximum number of output conformers per fragment.
        # 
        # \return The output-conformer limit.
        # 
        def getMaxNumOutputConformers() -> int: pass

        ##
        # \brief Sets the minimum pairwise heavy-atom RMSD that fragment conformers in the output set must keep.
        # 
        # \param min_rmsd The new minimum RMSD threshold (in &Aring;).
        # 
        def setMinRMSD(min_rmsd: float) -> None: pass

        ##
        # \brief Returns the minimum RMSD threshold used to filter fragment conformers.
        # 
        # \return The minimum RMSD threshold (in &Aring;).
        # 
        def getMinRMSD() -> float: pass

        objectID = property(getObjectID)

        maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

        minNumSampledConformers = property(getMinNumSampledConformers, setMinNumSampledConformers)

        timeout = property(getTimeout, setTimeout)

        energyWindow = property(getEnergyWindow, setEnergyWindow)

        maxNumOutputConformers = property(getMaxNumOutputConformers, setMaxNumOutputConformers)

        minRMSD = property(getMinRMSD, setMinRMSD)

    ##
    # \brief A static instance providing settings default values.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief A static instance preconfigured for fast (less thorough) conformer generation.
    # 
    FAST = _HIDDEN_VALUE_

    ##
    # \brief A static instance preconfigured for thorough (slower) conformer generation.
    # 
    THOROUGH = _HIDDEN_VALUE_

    ##
    # \brief Constructs the settings instance with default values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %FragmentConformerGeneratorSettings instance \a settings.
    # \param settings The \c %FragmentConformerGeneratorSettings instance to copy.
    # 
    def __init__(settings: FragmentConformerGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentConformerGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentConformerGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentConformerGeneratorSettings instance \a settings.
    # \param settings The \c %FragmentConformerGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: FragmentConformerGeneratorSettings) -> FragmentConformerGeneratorSettings: pass

    ##
    # \brief Specifies whether the bonding geometries (bond lengths and angles) of the input fragment shall be preserved.
    # 
    # \param preserve If <tt>True</tt>, the bonding geometry of the input is reused; otherwise it is rebuilt.
    # 
    def preserveInputBondingGeometries(preserve: bool) -> None: pass

    ##
    # \brief Tells whether the bonding geometries of the input fragment are preserved.
    # 
    # \return <tt>True</tt> if the input bonding geometry is reused, and <tt>False</tt> otherwise.
    # 
    def preserveInputBondingGeometries() -> bool: pass

    ##
    # \brief Sets the force-field type used for fragment-conformer minimization.
    # 
    # \param type One of the ConfGen.ForceFieldType values.
    # 
    def setForceFieldType(type: int) -> None: pass

    ##
    # \brief Returns the force-field type used for fragment-conformer minimization.
    # 
    # \return One of the ConfGen.ForceFieldType values.
    # 
    def getForceFieldType() -> int: pass

    ##
    # \brief Specifies whether strict MMFF94 parameterization is required.
    # 
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a failure; if <tt>False</tt>, fallback parameters are used.
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
    # \brief 
    # \param max_num 
    #
    def setMaxNumRefinementIterations(max_num: int) -> None: pass

    ##
    # \brief Returns the maximum number of MMFF94 energy-minimization iterations per fragment conformer.
    # 
    # \return The iteration limit (zero if refinement is disabled).
    # 
    def getMaxNumRefinementIterations() -> int: pass

    ##
    # \brief Sets the gradient-norm threshold at which fragment-conformer refinement is considered converged.
    # 
    # \param grad_norm The new stop-gradient threshold.
    # 
    def setRefinementStopGradient(grad_norm: float) -> None: pass

    ##
    # \brief Returns the gradient-norm threshold used to terminate refinement.
    # 
    # \return The stop-gradient threshold.
    # 
    def getRefinementStopGradient() -> float: pass

    ##
    # \brief 
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(max_size: int) -> None: pass

    ##
    # \brief Returns the macrocycle rotatable-bond count threshold.
    # 
    # \return The threshold.
    # 
    def getMacrocycleRotorBondCountThreshold() -> int: pass

    ##
    # \brief Returns a reference to the per-fragment-class settings used for chain fragments.
    # 
    # \return A reference to the chain-fragment settings.
    # 
    def getChainSettings() -> FragmentSettings: pass

    ##
    # \brief Returns a reference to the per-fragment-class settings used for macrocyclic ring systems.
    # 
    # \return A reference to the macrocycle settings.
    # 
    def getMacrocycleSettings() -> FragmentSettings: pass

    ##
    # \brief Returns a reference to the per-fragment-class settings used for small ring systems.
    # 
    # \return A reference to the small-ring-system settings.
    # 
    def getSmallRingSystemSettings() -> FragmentSettings: pass

    ##
    # \brief 
    # \param min_rmsd 
    #
    def setSmallRingSystemSamplingFactor(min_rmsd: int) -> None: pass

    ##
    # \brief Returns the multiplicative factor scaling the sampling effort for small ring systems.
    # 
    # \return The sampling-effort multiplier.
    # 
    def getSmallRingSystemSamplingFactor() -> int: pass

    objectID = property(getObjectID)

    preserveInputBondingGeom = property(preserveInputBondingGeometries, preserveInputBondingGeometries)

    forceFieldType = property(getForceFieldType, setForceFieldType)

    strictForceFieldParam = property(strictForceFieldParameterization, strictForceFieldParameterization)

    dielectricConstant = property(getDielectricConstant, setDielectricConstant)

    distanceExponent = property(getDistanceExponent, setDistanceExponent)

    maxNumRefinementIterations = property(getMaxNumRefinementIterations, setMaxNumRefinementIterations)

    refinementStopGradient = property(getRefinementStopGradient, setRefinementStopGradient)

    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThreshold, setMacrocycleRotorBondCountThreshold)

    chainSettings = property(getChainSettings)

    macrocycleSettings = property(getMacrocycleSettings)

    smallRingSysSettings = property(getSmallRingSystemSettings)

    smallRingSysSamplingFactor = property(getSmallRingSystemSamplingFactor, setSmallRingSystemSamplingFactor)
