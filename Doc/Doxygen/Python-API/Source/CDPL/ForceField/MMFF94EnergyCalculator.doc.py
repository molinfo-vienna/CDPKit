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
# \brief Calculates the total MMFF94 force field energy for a set of atom 3D coordinates.
# 
# The calculator takes a ForceField.MMFF94InteractionData instance (typically produced by ForceField.MMFF94InteractionParameterizer) and computes the bond-stretching, angle-bending, stretch-bend, out-of-plane bending, torsion, electrostatic and Van der Waals energy contributions for a supplied set of atom 3D coordinates. The per-component energies are retained and made available via the dedicated accessors, the calculated sum is returned by __call__() and getTotalEnergy().
# 
class MMFF94EnergyCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the calculator without an associated ForceField.MMFF94InteractionData instance.
    # 
    # __call__() will return zero until setup() has been called.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94EnergyCalculator instance \a calc.
    # \param calc The \c %MMFF94EnergyCalculator instance to copy.
    # 
    def __init__(calc: MMFF94EnergyCalculator) -> None: pass

    ##
    # \brief Constructs the calculator and associates it with the supplied ForceField.MMFF94InteractionData instance.
    # 
    # \param ia_data The MMFF94 interaction data to use for energy calculation.
    # 
    def __init__(ia_data: MMFF94InteractionData) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94EnergyCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94EnergyCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94EnergyCalculator instance \a calc.
    # \param calc The \c %MMFF94EnergyCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: MMFF94EnergyCalculator) -> MMFF94EnergyCalculator: pass

    ##
    # \brief Enables/disables specific MMFF94 interaction-type contributions.
    # 
    # \param types Bitwise-OR combination of ForceField.InteractionType flags.
    # 
    # \note Only enabled contributions are evaluated.
    # 
    def setEnabledInteractionTypes(types: int) -> None: pass

    ##
    # \brief Returns the currently enabled interaction-type contributions.
    # 
    # \return The bitwise-OR combination of ForceField.InteractionType flags.
    # 
    def getEnabledInteractionTypes() -> int: pass

    ##
    # \brief Associates the calculator with the supplied ForceField.MMFF94InteractionData instance.
    # 
    # \param ia_data The new MMFF94 interaction data to use for energy calculation.
    # 
    def setup(ia_data: MMFF94InteractionData) -> None: pass

    ##
    # \brief Returns the total MMFF94 energy computed by the most recent __call__() call.
    # 
    # \return A reference to the total energy.
    # 
    def getTotalEnergy() -> float: pass

    ##
    # \brief Returns the bond-stretching energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the bond-stretching energy.
    # 
    def getBondStretchingEnergy() -> float: pass

    ##
    # \brief Returns the angle-bending energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the angle-bending energy.
    # 
    def getAngleBendingEnergy() -> float: pass

    ##
    # \brief Returns the stretch-bend coupling energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the stretch-bend energy.
    # 
    def getStretchBendEnergy() -> float: pass

    ##
    # \brief Returns the out-of-plane bending energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the out-of-plane bending energy.
    # 
    def getOutOfPlaneBendingEnergy() -> float: pass

    ##
    # \brief Returns the torsion energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the torsion energy.
    # 
    def getTorsionEnergy() -> float: pass

    ##
    # \brief Returns the electrostatic energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the electrostatic energy.
    # 
    def getElectrostaticEnergy() -> float: pass

    ##
    # \brief Returns the Van der Waals energy contribution computed by the most recent __call__() call.
    # 
    # \return A reference to the Van der Waals energy.
    # 
    def getVanDerWaalsEnergy() -> float: pass

    ##
    # \brief Computes the total MMFF94 energy of the conformation specified by <em>coords</em>.
    # 
    # The per-component energies are stored internally and can be retrieved via the dedicated accessors.
    # 
    # \param coords The atom 3D coordinates.
    # 
    # \return A reference to the computed total energy.
    # 
    def __call__(coords: Math.Vector3DArray) -> float: pass

    objectID = property(getObjectID)

    enabledInteractionTypes = property(getEnabledInteractionTypes, setEnabledInteractionTypes)

    totalEnergy = property(getTotalEnergy)

    bondStretchingEnergy = property(getBondStretchingEnergy)

    angleBendingEnergy = property(getAngleBendingEnergy)

    stretchBendEnergy = property(getStretchBendEnergy)

    outOfPlaneBendingEnergy = property(getOutOfPlaneBendingEnergy)

    torsionEnergy = property(getTorsionEnergy)

    electrostaticEnergy = property(getElectrostaticEnergy)

    vanDerWaalsEnergy = property(getVanDerWaalsEnergy)
