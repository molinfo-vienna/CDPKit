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
class MMFF94DefaultStretchBendParameterTable(Boost.Python.instance):

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
        # \param term_atom1_pte_row 
        # \param ctr_atom_pte_row 
        # \param term_atom2_pte_row 
        # \param ijk_force_const 
        # \param kji_force_const 
        # 
        def __init__(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int, ijk_force_const: float, kji_force_const: float) -> None: pass

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
        def getTerminalAtom1PTERow() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getCenterAtomPTERow() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getTerminalAtom2PTERow() -> int: pass

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
        def __nonzero__() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __bool__() -> bool: pass

        objectID = property(getObjectID)

        termAtom1PTERow = property(getTerminalAtom1PTERow)

        ctrAtomPTERow = property(getCenterAtomPTERow)

        termAtom2PTERow = property(getTerminalAtom2PTERow)

        ijkForceConstant = property(getIJKForceConstant)

        kjiForceConstant = property(getKJIForceConstant)

    ##
    # \brief Initializes the \e %MMFF94DefaultStretchBendParameterTable instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94DefaultStretchBendParameterTable instance with a copy of the state of the \e %MMFF94DefaultStretchBendParameterTable instance \a table.
    # \param table The \e %MMFF94DefaultStretchBendParameterTable instance to copy.
    # 
    def __init__(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %MMFF94DefaultStretchBendParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94DefaultStretchBendParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param term_atom1_pte_row 
    # \param ctr_atom_pte_row 
    # \param term_atom2_pte_row 
    # \param ijk_force_const 
    # \param kji_force_const 
    #
    def addEntry(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief 
    # \param term_atom1_pte_row 
    # \param ctr_atom_pte_row 
    # \param term_atom2_pte_row 
    # \return 
    #
    def removeEntry(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int) -> bool: pass

    ##
    # \brief 
    # \param term_atom1_pte_row 
    # \param ctr_atom_pte_row 
    # \param term_atom2_pte_row 
    # \return 
    #
    def getEntry(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int) -> Entry: pass

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
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94DefaultStretchBendParameterTable instance \a table.
    # \param table The \e %MMFF94DefaultStretchBendParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94DefaultStretchBendParameterTable) -> MMFF94DefaultStretchBendParameterTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94DefaultStretchBendParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
