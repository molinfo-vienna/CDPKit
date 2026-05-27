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
# \brief Bundle of configuration parameters for systematic conformer enumeration via class ConfGen.TorsionDriver.
# 
class TorsionDriverSettings(Boost.Python.instance):

    ##
    # \brief A static instance providing configuration parameter default values.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Constructs the <tt>TorsionDriverSettings</tt> instance with default configuration parameter values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %TorsionDriverSettings instance \a settings.
    # \param settings The \c %TorsionDriverSettings instance to copy.
    # 
    def __init__(settings: TorsionDriverSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TorsionDriverSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TorsionDriverSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TorsionDriverSettings instance \a settings.
    # \param settings The \c %TorsionDriverSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: TorsionDriverSettings) -> TorsionDriverSettings: pass

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
    # \brief Specifies whether the generated conformers shall be sorted by ascending energy.
    # 
    # \param order If <tt>True</tt>, the output conformers are sorted by energy.
    # 
    def orderByEnergy(order: bool) -> None: pass

    ##
    # \brief Tells whether the generated conformers are sorted by ascending energy.
    # 
    # \return <tt>True</tt> if conformer energy ordering is enabled, and <tt>False</tt> otherwise.
    # 
    def orderByEnergy() -> bool: pass

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
    # \brief Sets the force field type used to score the generated conformers.
    # 
    # \param type One of the ConfGen.ForceFieldType values.
    # 
    def setForceFieldType(type: int) -> None: pass

    ##
    # \brief Returns the force field type used to score the generated conformers.
    # 
    # \return One of the ConfGen.ForceFieldType values.
    # 
    def getForceFieldType() -> int: pass

    ##
    # \brief Specifies whether strict MMFF94 parameterization is required.
    # 
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a failure. Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
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

    objectID = property(getObjectID)

    sampleHetAtomHydrogens = property(sampleHeteroAtomHydrogens, sampleHeteroAtomHydrogens)

    sampleAngleTolRanges = property(sampleAngleToleranceRanges, sampleAngleToleranceRanges)

    forceFieldType = property(getForceFieldType, setForceFieldType)

    strictForceFieldParam = property(strictForceFieldParameterization, strictForceFieldParameterization)

    dielectricConstant = property(getDielectricConstant, setDielectricConstant)

    distanceExponent = property(getDistanceExponent, setDistanceExponent)

    energyOrdered = property(orderByEnergy, orderByEnergy)

    energyWindow = property(getEnergyWindow, setEnergyWindow)

    maxPoolSize = property(getMaxPoolSize, setMaxPoolSize)
