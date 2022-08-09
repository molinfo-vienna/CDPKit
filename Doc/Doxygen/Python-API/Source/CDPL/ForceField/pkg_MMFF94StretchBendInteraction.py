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
class MMFF94StretchBendInteraction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94StretchBendInteraction instance.
    # \param iactn 
    #
    def __init__(iactn: MMFF94StretchBendInteraction) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94StretchBendInteraction instance.
    # \param term_atom1_idx 
    # \param ctr_atom_idx 
    # \param term_atom2_idx 
    # \param sb_type_idx 
    # \param ref_angle 
    # \param ref_length1 
    # \param ref_length2 
    # \param ijk_force_const 
    # \param kji_force_const 
    #
    def __init__(term_atom1_idx: int, ctr_atom_idx: int, term_atom2_idx: int, sb_type_idx: int, ref_angle: float, ref_length1: float, ref_length2: float, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTerminalAtom1Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getTerminalAtom2Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getCenterAtomIndex() -> int: pass

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
    def getAtom3Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStretchBendTypeIndex() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getIJKForceConstant() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getKJIForceConstant() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceAngle() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setReferenceAngle(angle: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceLength1() -> float: pass

    ##
    # \brief 
    # \param length 
    #
    def setReferenceLength1(length: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getReferenceLength2() -> float: pass

    ##
    # \brief 
    # \param length 
    #
    def setReferenceLength2(length: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94StretchBendInteraction instance \a iactn.
    # \param iactn The \e %MMFF94StretchBendInteraction instance to copy.
    # \return The assignment target \a self.
    #
    def assign(iactn: MMFF94StretchBendInteraction) -> MMFF94StretchBendInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %MMFF94StretchBendInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94StretchBendInteraction instances \e a and \e b reference different C++ objects. 
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
    # \brief FIXME!
    #
    termAtom1Index = property(getTermAtom1Index)

    ##
    # \brief FIXME!
    #
    termAtom2Index = property(getTermAtom2Index)

    ##
    # \brief FIXME!
    #
    ctrAtomIndex = property(getCtrAtomIndex)

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
    atom3Index = property(getAtom3Index)

    ##
    # \brief 
    #
    stretchBendTypeIndex = property(getStretchBendTypeIndex)

    ##
    # \brief 
    #
    referenceAngle = property(getReferenceAngle, setReferenceAngle)

    ##
    # \brief 
    #
    referenceLength1 = property(getReferenceLength1, setReferenceLength1)

    ##
    # \brief 
    #
    referenceLength2 = property(getReferenceLength2, setReferenceLength2)

    ##
    # \brief FIXME!
    #
    ijkForceConstant = property(getIjkForceConstant)

    ##
    # \brief FIXME!
    #
    kjiForceConstant = property(getKjiForceConstant)