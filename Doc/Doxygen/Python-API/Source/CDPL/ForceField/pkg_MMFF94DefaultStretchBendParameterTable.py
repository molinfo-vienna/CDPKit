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
class MMFF94DefaultStretchBendParameterTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        #
        def __init__(self: object) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        #
        def __init__(self: object, entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param term_atom1_pte_row 
        # \param ctr_atom_pte_row 
        # \param term_atom2_pte_row 
        # \param ijk_force_const 
        # \param kji_force_const 
        #
        def __init__(self: object, term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int, ijk_force_const: float, kji_force_const: float) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Entry instance this method is called upon.
        #
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: Entry) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param self The \e %Entry instance this method is called upon.
        # \param entry The \e %Entry instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Entry, entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getTerminalAtom1PTERow(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getCenterAtomPTERow(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getTerminalAtom2PTERow(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getIJKForceConstant(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getKJIForceConstant(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def __nonzero__(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def __bool__(self: Entry) -> bool: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief FIXME!
        #
        termAtom1PTERow = property(getTermAtom1PTERow)

        ##
        # \brief FIXME!
        #
        ctrAtomPTERow = property(getCtrAtomPTERow)

        ##
        # \brief FIXME!
        #
        termAtom2PTERow = property(getTermAtom2PTERow)

        ##
        # \brief FIXME!
        #
        ijkForceConstant = property(getIjkForceConstant)

        ##
        # \brief FIXME!
        #
        kjiForceConstant = property(getKjiForceConstant)

    ##
    # \brief Initializes the \e %MMFF94DefaultStretchBendParameterTable instance.
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94DefaultStretchBendParameterTable instance.
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance to initialize.
    # \param table 
    #
    def __init__(self: object, table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    #
    # Different Python \e %MMFF94DefaultStretchBendParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94DefaultStretchBendParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94DefaultStretchBendParameterTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \param term_atom1_pte_row 
    # \param ctr_atom_pte_row 
    # \param term_atom2_pte_row 
    # \param ijk_force_const 
    # \param kji_force_const 
    #
    def addEntry(self: MMFF94DefaultStretchBendParameterTable, term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \param term_atom1_pte_row 
    # \param ctr_atom_pte_row 
    # \param term_atom2_pte_row 
    # \return 
    #
    def removeEntry(self: MMFF94DefaultStretchBendParameterTable, term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \param term_atom1_pte_row 
    # \param ctr_atom_pte_row 
    # \param term_atom2_pte_row 
    # \return 
    #
    def getEntry(self: MMFF94DefaultStretchBendParameterTable, term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    #
    def clear(self: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: MMFF94DefaultStretchBendParameterTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \return 
    #
    def getEntries(self: MMFF94DefaultStretchBendParameterTable) -> list: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \param is 
    #
    def load(self: MMFF94DefaultStretchBendParameterTable, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    #
    def loadDefaults(self: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94DefaultStretchBendParameterTable instance \a table.
    # \param self The \e %MMFF94DefaultStretchBendParameterTable instance this method is called upon.
    # \param table The \e %MMFF94DefaultStretchBendParameterTable instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94DefaultStretchBendParameterTable, table: MMFF94DefaultStretchBendParameterTable) -> MMFF94DefaultStretchBendParameterTable: pass

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

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numEntries = property(getNumEntries)

    ##
    # \brief 
    #
    entries = property(getEntries)
