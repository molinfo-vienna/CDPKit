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
class FragmentConformerGeneratorSettings(Boost.Python.instance):

    ##
    # \brief 
    #
    class FragmentSettings(Boost.Python.instance):

        ##
        # \brief Initializes the \e %FragmentSettings instance.
        # \param arg1 The \e %FragmentSettings instance to initialize.
        #
        def __init__(arg1: object) -> None: pass

        ##
        # \brief Initializes the \e %FragmentSettings instance.
        # \param self The \e %FragmentSettings instance to initialize.
        # \param settings 
        #
        def __init__(self: object, settings: FragmentSettings) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %FragmentSettings instance this method is called upon.
        #
        # Different Python \e %FragmentSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentSettings instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: FragmentSettings) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentSettings instance \a settings.
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param settings The \e %FragmentSettings instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: FragmentSettings, settings: FragmentSettings) -> FragmentSettings: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param max_num 
        #
        def setMaxNumSampledConformers(self: FragmentSettings, max_num: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \return 
        #
        def getMaxNumSampledConformers(self: FragmentSettings) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param min_num 
        #
        def setMinNumSampledConformers(self: FragmentSettings, min_num: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \return 
        #
        def getMinNumSampledConformers(self: FragmentSettings) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param mil_secs 
        #
        def setTimeout(self: FragmentSettings, mil_secs: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \return 
        #
        def getTimeout(self: FragmentSettings) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param win_size 
        #
        def setEnergyWindow(self: FragmentSettings, win_size: float) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \return 
        #
        def getEnergyWindow(self: FragmentSettings) -> float: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param max_num 
        #
        def setMaxNumOutputConformers(self: FragmentSettings, max_num: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \return 
        #
        def getMaxNumOutputConformers(self: FragmentSettings) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \param min_rmsd 
        #
        def setMinRMSD(self: FragmentSettings, min_rmsd: float) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentSettings instance this method is called upon.
        # \return 
        #
        def getMinRMSD(self: FragmentSettings) -> float: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        maxNumSampledConformers = property(getMaxNumSampledConformers, setMaxNumSampledConformers)

        ##
        # \brief 
        #
        minNumSampledConformers = property(getMinNumSampledConformers, setMinNumSampledConformers)

        ##
        # \brief 
        #
        timeout = property(getTimeout, setTimeout)

        ##
        # \brief 
        #
        energyWindow = property(getEnergyWindow, setEnergyWindow)

        ##
        # \brief 
        #
        maxNumOutputConformers = property(getMaxNumOutputConformers, setMaxNumOutputConformers)

        ##
        # \brief 
        #
        minRMSD = property(getMinRMSD, setMinRMSD)

    ##
    # \brief FIXME!
    #
    DEFAULT = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    FAST = _UNKNOWN_VALUE_

    ##
    # \brief FIXME!
    #
    THOROUGH = _UNKNOWN_VALUE_

    ##
    # \brief Initializes the \e %FragmentConformerGeneratorSettings instance.
    # \param self The \e %FragmentConformerGeneratorSettings instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FragmentConformerGeneratorSettings instance.
    # \param self The \e %FragmentConformerGeneratorSettings instance to initialize.
    # \param settings 
    #
    def __init__(self: object, settings: FragmentConformerGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    #
    # Different Python \e %FragmentConformerGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentConformerGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FragmentConformerGeneratorSettings) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentConformerGeneratorSettings instance \a settings.
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param settings The \e %FragmentConformerGeneratorSettings instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FragmentConformerGeneratorSettings, settings: FragmentConformerGeneratorSettings) -> FragmentConformerGeneratorSettings: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param preserve 
    #
    def preserveInputBondingGeometries(self: FragmentConformerGeneratorSettings, preserve: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def preserveInputBondingGeometries(self: FragmentConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param type 
    #
    def setForceFieldType(self: FragmentConformerGeneratorSettings, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getForceFieldType(self: FragmentConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param strict 
    #
    def strictForceFieldParameterization(self: FragmentConformerGeneratorSettings, strict: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def strictForceFieldParameterization(self: FragmentConformerGeneratorSettings) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param de_const 
    #
    def setDielectricConstant(self: FragmentConformerGeneratorSettings, de_const: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDielectricConstant(self: FragmentConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param dist_expo 
    #
    def setDistanceExponent(self: FragmentConformerGeneratorSettings, dist_expo: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getDistanceExponent(self: FragmentConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumRefinementIterations(self: FragmentConformerGeneratorSettings, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMaxNumRefinementIterations(self: FragmentConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param grad_norm 
    #
    def setRefinementStopGradient(self: FragmentConformerGeneratorSettings, grad_norm: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getRefinementStopGradient(self: FragmentConformerGeneratorSettings) -> float: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param max_size 
    #
    def setMacrocycleRotorBondCountThreshold(self: FragmentConformerGeneratorSettings, max_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMacrocycleRotorBondCountThreshold(self: FragmentConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getChainSettings(self: FragmentConformerGeneratorSettings) -> FragmentSettings: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getMacrocycleSettings(self: FragmentConformerGeneratorSettings) -> FragmentSettings: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getSmallRingSystemSettings(self: FragmentConformerGeneratorSettings) -> FragmentSettings: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \param min_rmsd 
    #
    def setSmallRingSystemSamplingFactor(self: FragmentConformerGeneratorSettings, min_rmsd: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentConformerGeneratorSettings instance this method is called upon.
    # \return 
    #
    def getSmallRingSystemSamplingFactor(self: FragmentConformerGeneratorSettings) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    preserveInputBondingGeom = property(getPreserveInputBondingGeom, setPreserveInputBondingGeom)

    ##
    # \brief 
    #
    forceFieldType = property(getForceFieldType, setForceFieldType)

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
    # \brief FIXME!
    #
    minimizationStopGradientNorm = property(getMinimizationStopGradientNorm, setMinimizationStopGradientNorm)

    ##
    # \brief FIXME!
    #
    macrocycleRotorBondCountThresh = property(getMacrocycleRotorBondCountThresh, setMacrocycleRotorBondCountThresh)

    ##
    # \brief 
    #
    chainSettings = property(getChainSettings)

    ##
    # \brief 
    #
    macrocycleSettings = property(getMacrocycleSettings)

    ##
    # \brief FIXME!
    #
    smallRingSysSettings = property(getSmallRingSysSettings)

    ##
    # \brief FIXME!
    #
    smallRingSysSamplingFactor = property(getSmallRingSysSamplingFactor, setSmallRingSysSamplingFactor)
