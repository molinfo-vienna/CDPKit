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
    # \param self The \e %MMFF94StretchBendInteraction instance to initialize.
    # \param iactn 
    #
    def __init__(self: object, iactn: MMFF94StretchBendInteraction) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94StretchBendInteraction instance.
    # \param self The \e %MMFF94StretchBendInteraction instance to initialize.
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
    def __init__(self: object, term_atom1_idx: int, ctr_atom_idx: int, term_atom2_idx: int, sb_type_idx: int, ref_angle: float, ref_length1: float, ref_length2: float, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getTerminalAtom1Index(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getTerminalAtom2Index(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getCenterAtomIndex(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getAtom1Index(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getAtom2Index(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getAtom3Index(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getStretchBendTypeIndex(self: MMFF94StretchBendInteraction) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getIJKForceConstant(self: MMFF94StretchBendInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getKJIForceConstant(self: MMFF94StretchBendInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getReferenceAngle(self: MMFF94StretchBendInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \param angle 
    #
    def setReferenceAngle(self: MMFF94StretchBendInteraction, angle: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getReferenceLength1(self: MMFF94StretchBendInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \param length 
    #
    def setReferenceLength1(self: MMFF94StretchBendInteraction, length: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \return 
    #
    def getReferenceLength2(self: MMFF94StretchBendInteraction) -> float: pass

    ##
    # \brief 
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \param length 
    #
    def setReferenceLength2(self: MMFF94StretchBendInteraction, length: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94StretchBendInteraction instance \a iactn.
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    # \param iactn The \e %MMFF94StretchBendInteraction instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94StretchBendInteraction, iactn: MMFF94StretchBendInteraction) -> MMFF94StretchBendInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94StretchBendInteraction instance this method is called upon.
    #
    # Different Python \e %MMFF94StretchBendInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94StretchBendInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94StretchBendInteraction) -> int: pass

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
