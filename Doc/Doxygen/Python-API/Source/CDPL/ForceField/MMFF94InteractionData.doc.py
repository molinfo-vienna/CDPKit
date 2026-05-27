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
# \brief Container holding the full set of MMFF94 interaction parameters for a molecular graph.
# 
# The class aggregates the seven per-interaction lists that together describe the energy expression of the MMFF94 force field (bond stretching, angle bending, stretch-bend coupling, out-of-plane bending, torsion, electrostatic and Van der Waals interactions). Instances are typically produced by ForceField.MMFF94InteractionParameterizer and consumed by ForceField.MMFF94EnergyCalculator or ForceField.MMFF94GradientCalculator.
# 
class MMFF94InteractionData(Boost.Python.instance):

    ##
    # \brief Initializes the \c %MMFF94InteractionData instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94InteractionData instance \a ia_data.
    # \param ia_data The \c %MMFF94InteractionData instance to copy.
    # 
    def __init__(ia_data: MMFF94InteractionData) -> None: pass

    ##
    # \brief Removes all stored interactions from every interaction list.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the list of MMFF94 bond-stretching interactions.
    # 
    # \return A reference to the bond-stretching interaction list.
    # 
    def getBondStretchingInteractions() -> MMFF94BondStretchingInteractionList: pass

    ##
    # \brief Returns the list of MMFF94 angle-bending interactions.
    # 
    # \return A reference to the angle-bending interaction list.
    # 
    def getAngleBendingInteractions() -> MMFF94AngleBendingInteractionList: pass

    ##
    # \brief Returns the list of MMFF94 stretch-bend interactions.
    # 
    # \return A reference to the stretch-bend interaction list.
    # 
    def getStretchBendInteractions() -> MMFF94StretchBendInteractionList: pass

    ##
    # \brief Returns the list of MMFF94 out-of-plane bending interactions.
    # 
    # \return A reference to the out-of-plane bending interaction list.
    # 
    def getOutOfPlaneBendingInteractions() -> MMFF94OutOfPlaneBendingInteractionList: pass

    ##
    # \brief Returns the list of MMFF94 torsion interactions.
    # 
    # \return A reference to the torsion interaction list.
    # 
    def getTorsionInteractions() -> MMFF94TorsionInteractionList: pass

    ##
    # \brief Returns the list of MMFF94 electrostatic interactions.
    # 
    # \return A reference to the electrostatic interaction list.
    # 
    def getElectrostaticInteractions() -> MMFF94ElectrostaticInteractionList: pass

    ##
    # \brief Returns the list of MMFF94 Van der Waals interactions.
    # 
    # \return A reference to the Van der Waals interaction list.
    # 
    def getVanDerWaalsInteractions() -> MMFF94VanDerWaalsInteractionList: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94InteractionData instance \a ia_data.
    # \param ia_data The \c %MMFF94InteractionData instance to copy.
    # \return \a self
    # 
    def assign(ia_data: MMFF94InteractionData) -> MMFF94InteractionData: pass

    ##
    # \brief Swaps the contents (all interaction lists) of this instance with <em>ia_data</em>.
    # 
    # \param ia_data The other interaction data instance.
    # 
    def swap(ia_data: MMFF94InteractionData) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94InteractionData instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94InteractionData instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    objectID = property(getObjectID)

    bondStretchingInteractions = property(getBondStretchingInteractions)

    angleBendingInteractions = property(getAngleBendingInteractions)

    stretchBendInteractions = property(getStretchBendInteractions)

    outOfPlaneBendingInteractions = property(getOutOfPlaneBendingInteractions)

    torsionInteractions = property(getTorsionInteractions)

    electrostaticInteractions = property(getElectrostaticInteractions)

    vanDerWaalsInteractions = property(getVanDerWaalsInteractions)
