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
class MMFF94GradientCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94GradientCalculator instance.
    # \param self The \e %MMFF94GradientCalculator instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94GradientCalculator instance.
    # \param self The \e %MMFF94GradientCalculator instance to initialize.
    # \param calc 
    # 
    def __init__(calc: MMFF94GradientCalculator) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94GradientCalculator instance.
    # \param self The \e %MMFF94GradientCalculator instance to initialize.
    # \param ia_data 
    # \param num_atoms 
    # 
    def __init__(ia_data: MMFF94InteractionData, num_atoms: int) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # 
    # Different Python \e %MMFF94GradientCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94GradientCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param calc 
    # \return 
    #
    def assign(calc: MMFF94GradientCalculator) -> MMFF94GradientCalculator: pass

    ##
    # \brief 
    # \param types 
    #
    def setEnabledInteractionTypes(types: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEnabledInteractionTypes() -> int: pass

    ##
    # \brief 
    # \param ia_data 
    # \param num_atoms 
    #
    def setup(ia_data: MMFF94InteractionData, num_atoms: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTotalEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getBondStretchingEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getAngleBendingEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getStretchBendEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getOutOfPlaneBendingEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getElectrostaticEnergy() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getVanDerWaalsEnergy() -> float: pass

    ##
    # \brief 
    # \param mask 
    #
    def setFixedAtomMask(mask: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief 
    #
    def resetFixedAtomMask() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFixedAtomMask() -> CDPL.Util.BitSet: pass

    ##
    # \brief 
    # \param coords 
    # \return 
    #
    def __call__(coords: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \param coords 
    # \param grad 
    # \return 
    #
    def __call__(coords: CDPL.Math.Vector3DArray, grad: CDPL.Math.Vector3DArray) -> float: pass

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

    fixedAtomMask = property(getFixedAtomMask)
