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
# \brief Lookup table mapping (terminal-atom-1 PTE row, center-atom PTE row, terminal-atom-2 PTE row) triples to fallback MMFF94 stretch-bend coupling force constants used when no atom type-specific entry is available.
# 
# The PTE row of an atom is the row index in the periodic table of the elements. Two directional force constants are stored per entry (<tt>IJK</tt> and <tt>KJI</tt>) — see Util.MMFF94StretchBendParameterTable for the coupling semantics.
# 
class MMFF94DefaultStretchBendParameterTable(Boost.Python.instance):

    ##
    # \brief A single PTE-row-based default stretch-bend parameter record.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Constructs an empty (uninitialized) <tt>Entry</tt> instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes a copy of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Constructs an <tt>Entry</tt> for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
        # 
        # \param term_atom1_pte_row The PTE row of the first terminal atom.
        # \param ctr_atom_pte_row The PTE row of the center atom.
        # \param term_atom2_pte_row The PTE row of the second terminal atom.
        # \param ijk_force_const The IJK stretch-bend force constant.
        # \param kji_force_const The KJI stretch-bend force constant.
        # 
        def __init__(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int, ijk_force_const: float, kji_force_const: float) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief Returns the PTE row of the first terminal atom.
        # 
        # \return The first terminal atom's PTE row.
        # 
        def getTerminalAtom1PTERow() -> int: pass

        ##
        # \brief Returns the PTE row of the center atom.
        # 
        # \return The center atom's PTE row.
        # 
        def getCenterAtomPTERow() -> int: pass

        ##
        # \brief Returns the PTE row of the second terminal atom.
        # 
        # \return The second terminal atom's PTE row.
        # 
        def getTerminalAtom2PTERow() -> int: pass

        ##
        # \brief Returns the IJK stretch-bend force constant.
        # 
        # \return The IJK force constant.
        # 
        def getIJKForceConstant() -> float: pass

        ##
        # \brief Returns the KJI stretch-bend force constant.
        # 
        # \return The KJI force constant.
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
    # \brief Constructs an empty <tt>MMFF94DefaultStretchBendParameterTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94DefaultStretchBendParameterTable instance \a table.
    # \param table The \c %MMFF94DefaultStretchBendParameterTable instance to copy.
    # 
    def __init__(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94DefaultStretchBendParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94DefaultStretchBendParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds (or overwrites) the entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
    # 
    # \param term_atom1_pte_row The PTE row of the first terminal atom.
    # \param ctr_atom_pte_row The PTE row of the center atom.
    # \param term_atom2_pte_row The PTE row of the second terminal atom.
    # \param ijk_force_const The IJK stretch-bend force constant.
    # \param kji_force_const The KJI stretch-bend force constant.
    # 
    def addEntry(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief Removes the entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
    # 
    # \param term_atom1_pte_row The PTE row of the first terminal atom.
    # \param ctr_atom_pte_row The PTE row of the center atom.
    # \param term_atom2_pte_row The PTE row of the second terminal atom.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int) -> bool: pass

    ##
    # \brief Returns the entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
    # 
    # \param term_atom1_pte_row The PTE row of the first terminal atom.
    # \param ctr_atom_pte_row The PTE row of the center atom.
    # \param term_atom2_pte_row The PTE row of the second terminal atom.
    # 
    # \return A reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns <tt>False</tt>) if no match exists.
    # 
    def getEntry(term_atom1_pte_row: int, ctr_atom_pte_row: int, term_atom2_pte_row: int) -> Entry: pass

    ##
    # \brief Removes all entries from the table.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of entries in the table.
    # 
    # \return The entry count.
    # 
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief Loads table entries from the input stream <em>is</em>.
    # 
    # \param is The input stream to read from.
    # 
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief Loads the built-in default stretch-bend fallback entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94DefaultStretchBendParameterTable instance \a table.
    # \param table The \c %MMFF94DefaultStretchBendParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94DefaultStretchBendParameterTable) -> MMFF94DefaultStretchBendParameterTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A reference to the default table shared reference.
    # 
    @staticmethod
    def get(: ) -> MMFF94DefaultStretchBendParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
