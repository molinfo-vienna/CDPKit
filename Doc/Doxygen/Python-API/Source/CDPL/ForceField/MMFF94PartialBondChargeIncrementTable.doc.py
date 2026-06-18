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
# \brief Data structure for the storage and lookup of MMFF94 per-atom partial bond charge increment and formal charge adjustment factors.
# 
# \see [\ref MMFF94]
# 
class MMFF94PartialBondChargeIncrementTable(Boost.Python.instance):

    ##
    # \brief Data structure for the storage of values associated with a single table entry.
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
        # \brief Constructs an <tt>Entry</tt> instance storing the given values.
        # 
        # \param atom_type The numeric MMFF94 atom type.
        # \param part_bond_chg_inc The partial bond charge increment.
        # \param form_chg_adj_factor The formal charge adjustment factor.
        # 
        def __init__(atom_type: int, part_bond_chg_inc: float, form_chg_adj_factor: float) -> None: pass

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
        # \brief Returns the numeric MMFF94 atom type of the entry.
        # 
        # \return The numeric atom type.
        # 
        def getAtomType() -> int: pass

        ##
        # \brief Returns the partial bond charge increment.
        # 
        # \return The partial bond charge increment.
        # 
        def getPartialChargeIncrement() -> float: pass

        ##
        # \brief Returns the formal charge adjustment factor.
        # 
        # \return The formal charge adjustment factor.
        # 
        def getFormalChargeAdjustmentFactor() -> float: pass

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

        atomType = property(getAtomType)

        partialChargeIncrement = property(getPartialChargeIncrement)

        formalChargeAdjustmentFactor = property(getFormalChargeAdjustmentFactor)

    ##
    # \brief Constructs an empty <tt>MMFF94PartialBondChargeIncrementTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94PartialBondChargeIncrementTable instance \a table.
    # \param table The \c %MMFF94PartialBondChargeIncrementTable instance to copy.
    # 
    def __init__(table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94PartialBondChargeIncrementTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94PartialBondChargeIncrementTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry for the numeric MMFF94 atom type <em>atom_type</em> that stores the given parameter values.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # \param part_bond_chg_inc The partial bond charge increment.
    # \param form_chg_adj_factor The formal charge adjustment factor.
    # 
    def addEntry(atom_type: int, part_bond_chg_inc: float, form_chg_adj_factor: float) -> None: pass

    ##
    # \brief Removes the entry for the numeric MMFF94 atom type <em>atom_type</em>.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief Returns the entry for the numeric MMFF94 atom type <em>atom_type</em>.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # 
    # \return A reference to the matching entry or to an uninitialized entry if no matching entry exists.
    # 
    def getEntry(atom_type: int) -> Entry: pass

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
    # \brief Loads the built-in default MMFF94 partial bond charge increment and formal charge adjustment factors.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94PartialBondChargeIncrementTable instance \a table.
    # \param table The \c %MMFF94PartialBondChargeIncrementTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94PartialBondChargeIncrementTable) -> MMFF94PartialBondChargeIncrementTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> MMFF94PartialBondChargeIncrementTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
