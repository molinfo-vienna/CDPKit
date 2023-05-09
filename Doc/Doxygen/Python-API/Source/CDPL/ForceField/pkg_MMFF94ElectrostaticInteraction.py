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
class MMFF94ElectrostaticInteraction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94ElectrostaticInteraction instance.
    # \param iactn 
    #
    def __init__(iactn: MMFF94ElectrostaticInteraction) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94ElectrostaticInteraction instance.
    # \param atom1_idx 
    # \param atom2_idx 
    # \param atom1_chg 
    # \param atom2_chg 
    # \param scale_fact 
    # \param de_const 
    # \param dist_expo 
    #
    def __init__(atom1_idx: int, atom2_idx: int, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom1Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom2Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom1Charge() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom2Charge() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getScalingFactor() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getDielectricConstant() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getDistanceExponent() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94ElectrostaticInteraction instance \a iactn.
    # \param iactn The \e %MMFF94ElectrostaticInteraction instance to copy.
    # \return \a self
    #
    def assign(iactn: MMFF94ElectrostaticInteraction) -> MMFF94ElectrostaticInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %MMFF94ElectrostaticInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94ElectrostaticInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    atom1Index = property(getAtom1Index)

    ##
    # \brief 
    #
    atom2Index = property(getAtom2Index)

    ##
    # \brief 
    #
    atom1Charge = property(getAtom1Charge)

    ##
    # \brief 
    #
    atom2Charge = property(getAtom2Charge)

    ##
    # \brief 
    #
    scalingFactor = property(getScalingFactor)

    ##
    # \brief 
    #
    dielectricConstant = property(getDielectricConstant)

    ##
    # \brief 
    #
    distanceExponent = property(getDistanceExponent)
