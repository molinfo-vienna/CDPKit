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
class FragmentConformerGeneratorSettings(Boost.Python.instance):

    ##
    # \brief 
    #
    class FragmentSettings(Boost.Python.instance):

        ##
        # \brief Initializes the \e %FragmentSettings instance with a copy of the state of the \e %FragmentSettings instance \a settings.
        # \param settings The \e %FragmentSettings instance to copy.
        # 
        def __init__(settings: FragmentSettings) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %FragmentSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentSettings instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentSettings instance \a settings.
        # \param settings The \e %FragmentSettings instance to copy.
        # \return \a self
        # 
        def assign(settings: FragmentSettings) -> FragmentSettings: pass

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
        # \param min_num 
        #
        def setMinNumSampledConformers(min_num: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getMinNumSampledConformers() -> int: pass

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

        objectID = property(getObjectID)

        maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

        minNumSampledConformers = property(getMinNumSampledConformers, setMinNumSampledConformers)

        timeout = property(getTimeout, setTimeout)

        energyWindow = property(getEnergyWindow, setEnergyWindow)

        maxNumOutputConformers = property(getMaxNumOutputConformers, setMaxNumOutputConformers)

        minRMSD = property(getMinRMSD, setMinRMSD)

    ##
    # \brief 
    #
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief 
    #
    FAST = _HIDDEN_VALUE_

    ##
    # \brief 
    #
    THOROUGH = _HIDDEN_VALUE_

    ##
    # \brief Initializes the \e %FragmentConformerGeneratorSettings instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FragmentConformerGeneratorSettings instance with a copy of the state of the \e %FragmentConformerGeneratorSettings instance \a settings.
    # \param settings The \e %FragmentConformerGeneratorSettings instance to copy.
    # 
    def __init__(settings: FragmentConformerGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FragmentConformerGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentConformerGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentConformerGeneratorSettings instance \a settings.
    # \param settings The \e %FragmentConformerGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: FragmentConformerGeneratorSettings) -> FragmentConformerGeneratorSettings: pass

    ##
    # \brief 
    # \param preserve 
    #
    def preserveInputBondingGeometries(preserve: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def preserveInputBondingGeometries() -> bool: pass

    ##
    # \brief 
    # \param type 
    #
    def setForceFieldType(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getForceFieldType() -> int: pass

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
    # \param grad_norm 
    #
    def setRefinementStopGradient(grad_norm: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRefinementStopGradient() -> float: pass

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
    def getChainSettings() -> FragmentSettings: pass

    ##
    # \brief 
    # \return 
    #
    def getMacrocycleSettings() -> FragmentSettings: pass

    ##
    # \brief 
    # \return 
    #
    def getSmallRingSystemSettings() -> FragmentSettings: pass

    ##
    # \brief 
    # \param min_rmsd 
    #
    def setSmallRingSystemSamplingFactor(min_rmsd: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSmallRingSystemSamplingFactor() -> int: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    preserveInputBondingGeom = property(getPreserveInputBondingGeom, setPreserveInputBondingGeom)

    forceFieldType = property(getForceFieldType, setForceFieldType)

    ##
    # \brief FIXME!
    # \brief 
    #
    strictForceFieldParam = property(getStrictForceFieldParam, setStrictForceFieldParam)

    dielectricConstant = property(getDielectricConstant, setDielectricConstant)

    distanceExponent = property(getDistanceExponent, setDistanceExponent)

    maxNumRefinementIterations = property(getMaxNumRefinementIterations, setMaxNumRefinementIterations)

    ##
    # \brief FIXME!
    # \brief 
    #
    minimizationStopGradientNorm = property(getMinimizationStopGradientNorm, setMinimizationStopGradientNorm)

    ##
    # \brief FIXME!
    # \brief 
    #
    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThresh, setMacrocycleRotorBondCountThresh)

    chainSettings = property(getChainSettings)

    macrocycleSettings = property(getMacrocycleSettings)

    ##
    # \brief FIXME!
    # \brief 
    #
    smallRingSysSettings = property(getSmallRingSysSettings)

    ##
    # \brief FIXME!
    # \brief 
    #
    smallRingSysSamplingFactor = property(getSmallRingSysSamplingFactor, setSmallRingSysSamplingFactor)
