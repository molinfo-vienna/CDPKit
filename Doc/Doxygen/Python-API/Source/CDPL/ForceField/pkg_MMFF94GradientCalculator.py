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
class MMFF94GradientCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94GradientCalculator instance.
    # \param self The \e %MMFF94GradientCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94GradientCalculator instance.
    # \param self The \e %MMFF94GradientCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: MMFF94GradientCalculator) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94GradientCalculator instance.
    # \param self The \e %MMFF94GradientCalculator instance to initialize.
    # \param ia_data 
    # \param num_atoms 
    #
    def __init__(self: object, ia_data: MMFF94InteractionData, num_atoms: int) -> None: pass

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
    def getObjectID(self: MMFF94GradientCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94GradientCalculator instance \a calculator.
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \param calculator The \e %MMFF94GradientCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94GradientCalculator, calculator: MMFF94GradientCalculator) -> MMFF94GradientCalculator: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \param types 
    #
    def setEnabledInteractionTypes(self: MMFF94GradientCalculator, types: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getEnabledInteractionTypes(self: MMFF94GradientCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \param ia_data 
    # \param num_atoms 
    #
    def setup(self: MMFF94GradientCalculator, ia_data: MMFF94InteractionData, num_atoms: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getTotalEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getBondStretchingEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getAngleBendingEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getStretchBendEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getOutOfPlaneBendingEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getTorsionEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getElectrostaticEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getVanDerWaalsEnergy(self: MMFF94GradientCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \param mask 
    #
    def setFixedAtomMask(self: MMFF94GradientCalculator, mask: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    #
    def resetFixedAtomMask(self: MMFF94GradientCalculator) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \return 
    #
    def getFixedAtomMask(self: MMFF94GradientCalculator) -> CDPL.Util.BitSet: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \param coords 
    # \return 
    #
    def __call__(self: MMFF94GradientCalculator, coords: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94GradientCalculator instance this method is called upon.
    # \param coords 
    # \param grad 
    # \return 
    #
    def __call__(self: MMFF94GradientCalculator, coords: CDPL.Math.Vector3DArray, grad: CDPL.Math.Vector3DArray) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    enabledInteractionTypes = property(getEnabledInteractionTypes, setEnabledInteractionTypes)

    ##
    # \brief 
    #
    totalEnergy = property(getTotalEnergy)

    ##
    # \brief 
    #
    bondStretchingEnergy = property(getBondStretchingEnergy)

    ##
    # \brief 
    #
    angleBendingEnergy = property(getAngleBendingEnergy)

    ##
    # \brief 
    #
    stretchBendEnergy = property(getStretchBendEnergy)

    ##
    # \brief 
    #
    outOfPlaneBendingEnergy = property(getOutOfPlaneBendingEnergy)

    ##
    # \brief 
    #
    torsionEnergy = property(getTorsionEnergy)

    ##
    # \brief 
    #
    electrostaticEnergy = property(getElectrostaticEnergy)

    ##
    # \brief 
    #
    vanDerWaalsEnergy = property(getVanDerWaalsEnergy)

    ##
    # \brief 
    #
    fixedAtomMask = property(getFixedAtomMask)
