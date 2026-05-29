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
# \brief Lookup table mapping (terminal-atom-1 type, center-atom type, terminal-atom-2 type, out-of-plane-atom type) quadruples to MMFF94 out-of-plane bending force constants.
# 
# The table maintains separate process-wide defaults per MMFF94 parameter set (see Util.MMFF94ParameterSet).
# 
class MMFF94OutOfPlaneBendingParameterTable(Boost.Python.instance):

    ##
    # \brief A single out-of-plane bending parameter record.
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
        # \brief Constructs an <tt>Entry</tt> for the given (terminal-atom 1, center atom, terminal-atom 2, out-of-plane atom) quadruple.
        # 
        # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
        # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
        # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
        # \param oop_atom_type The numeric MMFF94 atom type of the out-of-plane atom.
        # \param force_const The out-of-plane bending force constant.
        # 
        def __init__(term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int, oop_atom_type: int, force_const: float) -> None: pass

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
        # \brief Returns the numeric MMFF94 atom type of the first terminal atom.
        # 
        # \return The first terminal atom's numeric MMFF94 type.
        # 
        def getTerminalAtom1Type() -> int: pass

        ##
        # \brief Returns the numeric MMFF94 atom type of the center atom.
        # 
        # \return The center atom's numeric MMFF94 type.
        # 
        def getCenterAtomType() -> int: pass

        ##
        # \brief Returns the numeric MMFF94 atom type of the second terminal atom.
        # 
        # \return The second terminal atom's numeric MMFF94 type.
        # 
        def getTerminalAtom2Type() -> int: pass

        ##
        # \brief Returns the numeric MMFF94 atom type of the out-of-plane atom.
        # 
        # \return The out-of-plane atom's numeric MMFF94 type.
        # 
        def getOutOfPlaneAtomType() -> int: pass

        ##
        # \brief Returns the out-of-plane bending force constant.
        # 
        # \return The force constant.
        # 
        def getForceConstant() -> float: pass

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

        termAtom1Type = property(getTerminalAtom1Type)

        ctrAtomType = property(getCenterAtomType)

        termAtom2Type = property(getTerminalAtom2Type)

        oopAtomType = property(getOutOfPlaneAtomType)

        forceConstant = property(getForceConstant)

    ##
    # \brief Constructs an empty <tt>MMFF94OutOfPlaneBendingParameterTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94OutOfPlaneBendingParameterTable instance \a table.
    # \param table The \c %MMFF94OutOfPlaneBendingParameterTable instance to copy.
    # 
    def __init__(table: MMFF94OutOfPlaneBendingParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94OutOfPlaneBendingParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94OutOfPlaneBendingParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds (or overwrites) the entry for the given (terminal-atom 1, center atom, terminal-atom 2, out-of-plane atom) quadruple.
    # 
    # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
    # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
    # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
    # \param oop_atom_type The numeric MMFF94 atom type of the out-of-plane atom.
    # \param force_const The out-of-plane bending force constant.
    # 
    def addEntry(term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int, oop_atom_type: int, force_const: float) -> None: pass

    ##
    # \brief Removes the entry for the given (terminal-atom 1, center atom, terminal-atom 2, out-of-plane atom) quadruple.
    # 
    # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
    # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
    # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
    # \param oop_atom_type The numeric MMFF94 atom type of the out-of-plane atom.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int, oop_atom_type: int) -> bool: pass

    ##
    # \brief Returns the entry for the given (terminal-atom 1, center atom, terminal-atom 2, out-of-plane atom) quadruple.
    # 
    # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
    # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
    # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
    # \param oop_atom_type The numeric MMFF94 atom type of the out-of-plane atom.
    # 
    # \return A reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns <tt>False</tt>) if no match exists.
    # 
    def getEntry(term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int, oop_atom_type: int) -> Entry: pass

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
    # \brief Loads the built-in default out-of-plane bending parameter entries for the specified MMFF94 parameter set.
    # 
    # \param param_set The Util.MMFF94ParameterSet identifier selecting which built-in defaults to load.
    # 
    def loadDefaults(param_set: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94OutOfPlaneBendingParameterTable instance \a table.
    # \param table The \c %MMFF94OutOfPlaneBendingParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94OutOfPlaneBendingParameterTable) -> MMFF94OutOfPlaneBendingParameterTable: pass

    ##
    # \brief Replaces the process-wide default table for <em>param_set</em> by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # \param param_set The Util.MMFF94ParameterSet identifier selecting which default slot to replace.
    # 
    @staticmethod
    def set(table: MMFF94OutOfPlaneBendingParameterTable, param_set: int) -> None: pass

    ##
    # \brief Returns the process-wide default table for <em>param_set</em> (lazily initialized on first call).
    # 
    # \param param_set The Util.MMFF94ParameterSet identifier selecting which default slot to return.
    # 
    # \return A reference to the selected default-table shared reference.
    # 
    @staticmethod
    def get(param_set: int) -> MMFF94OutOfPlaneBendingParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
