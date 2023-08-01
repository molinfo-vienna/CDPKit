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
class MMFF94TorsionParameterTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param tor_type_idx 
        # \param term_atom1_type 
        # \param ctr_atom1_type 
        # \param ctr_atom2_type 
        # \param term_atom2_type 
        # \param tor_param1 
        # \param tor_param2 
        # \param tor_param3 
        # 
        def __init__(tor_type_idx: int, term_atom1_type: int, ctr_atom1_type: int, ctr_atom2_type: int, term_atom2_type: int, tor_param1: float, tor_param2: float, tor_param3: float) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getTorsionTypeIndex() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getTerminalAtom1Type() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getCenterAtom1Type() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getCenterAtom2Type() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getTerminalAtom2Type() -> int: pass

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
        # \return 
        #
        def __nonzero__() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __bool__() -> bool: pass

        objectID = property(getObjectID)

        ##
        # \brief FIXME!
        # \brief 
        #
        torTypeIndex = property(getTorTypeIndex)

        ##
        # \brief FIXME!
        # \brief 
        #
        termAtom1Type = property(getTermAtom1Type)

        ##
        # \brief FIXME!
        # \brief 
        #
        ctrAtom1Type = property(getCtrAtom1Type)

        ##
        # \brief FIXME!
        # \brief 
        #
        ctrAtom2Type = property(getCtrAtom2Type)

        ##
        # \brief FIXME!
        # \brief 
        #
        termAtom2Type = property(getTermAtom2Type)

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

    ##
    # \brief Initializes the \e %MMFF94TorsionParameterTable instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94TorsionParameterTable instance with a copy of the state of the \e %MMFF94TorsionParameterTable instance \a table.
    # \param table The \e %MMFF94TorsionParameterTable instance to copy.
    # 
    def __init__(table: MMFF94TorsionParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %MMFF94TorsionParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94TorsionParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param tor_type_idx 
    # \param term_atom1_type 
    # \param ctr_atom1_type 
    # \param ctr_atom2_type 
    # \param term_atom2_type 
    # \param tor_param1 
    # \param tor_param2 
    # \param tor_param3 
    #
    def addEntry(tor_type_idx: int, term_atom1_type: int, ctr_atom1_type: int, ctr_atom2_type: int, term_atom2_type: int, tor_param1: float, tor_param2: float, tor_param3: float) -> None: pass

    ##
    # \brief 
    # \param tor_type_idx 
    # \param term_atom1_type 
    # \param ctr_atom1_type 
    # \param ctr_atom2_type 
    # \param term_atom2_type 
    # \return 
    #
    def removeEntry(tor_type_idx: int, term_atom1_type: int, ctr_atom1_type: int, ctr_atom2_type: int, term_atom2_type: int) -> bool: pass

    ##
    # \brief 
    # \param tor_type_idx 
    # \param term_atom1_type 
    # \param ctr_atom1_type 
    # \param ctr_atom2_type 
    # \param term_atom2_type 
    # \return 
    #
    def getEntry(tor_type_idx: int, term_atom1_type: int, ctr_atom1_type: int, ctr_atom2_type: int, term_atom2_type: int) -> Entry: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief 
    # \param is 
    #
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief 
    # \param param_set 
    #
    def loadDefaults(param_set: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94TorsionParameterTable instance \a table.
    # \param table The \e %MMFF94TorsionParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94TorsionParameterTable) -> MMFF94TorsionParameterTable: pass

    ##
    # \brief 
    # \param table 
    # \param param_set 
    #
    @staticmethod
    def set(table: MMFF94TorsionParameterTable, param_set: int) -> None: pass

    ##
    # \brief 
    # \param param_set 
    # \return 
    #
    @staticmethod
    def get(param_set: int) -> MMFF94TorsionParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
