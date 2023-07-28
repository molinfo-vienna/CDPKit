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
class MMFF94TorsionInteraction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94TorsionInteraction instance.
    # \param self The \e %MMFF94TorsionInteraction instance to initialize.
    # \param iactn 
    # 
    def __init__(iactn: MMFF94TorsionInteraction) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94TorsionInteraction instance.
    # \param self The \e %MMFF94TorsionInteraction instance to initialize.
    # \param term_atom1_idx 
    # \param ctr_atom1_idx 
    # \param ctr_atom2_idx 
    # \param term_atom2_idx 
    # \param tor_type_idx 
    # \param tor_param1 
    # \param tor_param2 
    # \param tor_param3 
    # 
    def __init__(term_atom1_idx: int, ctr_atom1_idx: int, ctr_atom2_idx: int, term_atom2_idx: int, tor_type_idx: int, tor_param1: float, tor_param2: float, tor_param3: float) -> None: pass

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
    def getCenterAtom1Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getCenterAtom2Index() -> int: pass

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
    def getAtom4Index() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionTypeIndex() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionParameter1() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionParameter2() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionParameter3() -> float: pass

    ##
    # \brief 
    # \param iactn 
    # \return 
    #
    def assign(iactn: MMFF94TorsionInteraction) -> MMFF94TorsionInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94TorsionInteraction instance this method is called upon.
    # 
    # Different Python \e %MMFF94TorsionInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94TorsionInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    termAtom1Index = property(getTermAtom1Index)

    ##
    # \brief FIXME!
    # \brief 
    #
    termAtom2Index = property(getTermAtom2Index)

    ##
    # \brief FIXME!
    # \brief 
    #
    ctrAtom1Index = property(getCtrAtom1Index)

    ##
    # \brief FIXME!
    # \brief 
    #
    ctrAtom2Index = property(getCtrAtom2Index)

    atom1Index = property(getAtom1Index)

    atom2Index = property(getAtom2Index)

    atom3Index = property(getAtom3Index)

    atom4Index = property(getAtom4Index)

    torsionTypeIndex = property(getTorsionTypeIndex)

    ##
    # \brief FIXME!
    # \brief 
    #
    torsionParam1 = property(getTorsionParam1)

    ##
    # \brief FIXME!
    # \brief 
    #
    torsionParam2 = property(getTorsionParam2)

    ##
    # \brief FIXME!
    # \brief 
    #
    torsionParam3 = property(getTorsionParam3)
