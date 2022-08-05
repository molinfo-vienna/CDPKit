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
class TorsionDriverSettings(Boost.Python.instance):

    ##
    # \brief FIXME!
    #
    DEFAULT = _UNKNOWN_VALUE_

    ##
    # \brief Initializes the \e %TorsionDriverSettings instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %TorsionDriverSettings instance.
    # \param settings 
    #
    def __init__(settings: TorsionDriverSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %TorsionDriverSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TorsionDriverSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TorsionDriverSettings instance \a settings.
    # \param settings The \e %TorsionDriverSettings instance to copy.
    # \return The assignment target \a self.
    #
    def assign(settings: TorsionDriverSettings) -> TorsionDriverSettings: pass

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
    # \param order 
    #
    def orderByEnergy(order: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def orderByEnergy() -> bool: pass

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
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    sampleHetAtomHydrogens = property(getSampleHetAtomHydrogens, setSampleHetAtomHydrogens)

    ##
    # \brief FIXME!
    #
    sampleAngleTolRanges = property(getSampleAngleTolRanges, setSampleAngleTolRanges)

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
    # \brief FIXME!
    #
    energyOrdered = property(getEnergyOrdered, setEnergyOrdered)

    ##
    # \brief 
    #
    energyWindow = property(getEnergyWindow, setEnergyWindow)

    ##
    # \brief 
    #
    maxPoolSize = property(getMaxPoolSize, setMaxPoolSize)
