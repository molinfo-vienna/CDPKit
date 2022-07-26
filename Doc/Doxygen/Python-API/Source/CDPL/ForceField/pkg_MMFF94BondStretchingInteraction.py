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
class MMFF94BondStretchingInteraction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94BondStretchingInteraction instance.
    # \param self The \e %MMFF94BondStretchingInteraction instance to initialize.
    # \param iactn 
    #
    def __init__(self: object, iactn: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94BondStretchingInteraction instance.
    # \param self The \e %MMFF94BondStretchingInteraction instance to initialize.
    # \param atom1_idx 
    # \param atom2_idx 
    # \param bond_type_idx 
    # \param force_const 
    # \param ref_length 
    #
    def __init__(self: object, atom1_idx: int, atom2_idx: int, bond_type_idx: int, force_const: float, ref_length: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \return 
    #
    def getAtom1Index(self: MMFF94BondStretchingInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \return 
    #
    def getAtom2Index(self: MMFF94BondStretchingInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \return 
    #
    def getBondTypeIndex(self: MMFF94BondStretchingInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \return 
    #
    def getForceConstant(self: MMFF94BondStretchingInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \return 
    #
    def getReferenceLength(self: MMFF94BondStretchingInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \param length 
    #
    def setReferenceLength(self: MMFF94BondStretchingInteraction, length: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94BondStretchingInteraction instance \a iactn.
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    # \param iactn The \e %MMFF94BondStretchingInteraction instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94BondStretchingInteraction, iactn: MMFF94BondStretchingInteraction) -> MMFF94BondStretchingInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94BondStretchingInteraction instance this method is called upon.
    #
    # Different Python \e %MMFF94BondStretchingInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94BondStretchingInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94BondStretchingInteraction) -> int: pass

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
    bondTypeIndex = property(getBondTypeIndex)

    ##
    # \brief 
    #
    forceConstant = property(getForceConstant)

    ##
    # \brief 
    #
    referenceLength = property(getReferenceLength, setReferenceLength)
