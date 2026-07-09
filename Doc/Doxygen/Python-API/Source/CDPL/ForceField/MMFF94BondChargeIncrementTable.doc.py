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
# \brief Data structure for the storage and lookup of MMFF94 bond charge increments.
# 
# The charge increment is applied to the first atom (and its negative to the second atom) when partitioning partial atomic charges along bonded pairs in the MMFF94 charge model.
# 
# \see [\ref MMFF94]
# 
class MMFF94BondChargeIncrementTable(Boost.Python.instance):

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
        # \brief Constructs an <tt>Entry</tt> for the given query values and charge increment.
        # 
        # \param bond_type_idx The MMFF94 bond type index.
        # \param atom1_type The numeric MMFF94 atom type of the first bonded atom.
        # \param atom2_type The numeric MMFF94 atom type of the second bonded atom.
        # \param bond_chg_inc The bond charge increment value.
        # 
        def __init__(bond_type_idx: int, atom1_type: int, atom2_type: int, bond_chg_inc: float) -> None: pass

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
        # \brief Returns the MMFF94 bond type index.
        # 
        # \return The bond type index.
        # 
        def getBondTypeIndex() -> int: pass

        ##
        # \brief Returns the numeric MMFF94 atom type of the first bonded atom.
        # 
        # \return The first atom's numeric MMFF94 type.
        # 
        def getAtom1Type() -> int: pass

        ##
        # \brief Returns the numeric MMFF94 atom type of the second bonded atom.
        # 
        # \return The second atom's numeric MMFF94 type.
        # 
        def getAtom2Type() -> int: pass

        ##
        # \brief Returns the bond charge increment.
        # 
        # \return The charge increment applied to the bonded atoms.
        # 
        def getChargeIncrement() -> float: pass

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

        bondTypeIndex = property(getBondTypeIndex)

        atom1Type = property(getAtom1Type)

        atom2Type = property(getAtom2Type)

        chargeIncrement = property(getChargeIncrement)

    ##
    # \brief Constructs an empty <tt>MMFF94BondChargeIncrementTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94BondChargeIncrementTable instance \a table.
    # \param table The \c %MMFF94BondChargeIncrementTable instance to copy.
    # 
    def __init__(table: MMFF94BondChargeIncrementTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94BondChargeIncrementTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94BondChargeIncrementTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry for the given query values and charge increment.
    # 
    # \param bond_type_idx The MMFF94 bond type index.
    # \param atom1_type The numeric MMFF94 atom type of the first bonded atom.
    # \param atom2_type The numeric MMFF94 atom type of the second bonded atom.
    # \param bond_chg_inc The bond charge increment value.
    # 
    def addEntry(bond_type_idx: int, atom1_type: int, atom2_type: int, bond_chg_inc: float) -> None: pass

    ##
    # \brief Removes the entry matching the specified query values.
    # 
    # \param bond_type_idx The MMFF94 bond type index.
    # \param atom1_type The numeric MMFF94 atom type of the first bonded atom.
    # \param atom2_type The numeric MMFF94 atom type of the second bonded atom.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(bond_type_idx: int, atom1_type: int, atom2_type: int) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \param arg2 
    # \param atom_type 
    # \return 
    #
    def getEntry(arg2: int, self: int, atom_type: int) -> Entry: pass

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
    # \brief Loads the built-in default MMFF94 bond charge increment entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94BondChargeIncrementTable instance \a table.
    # \param table The \c %MMFF94BondChargeIncrementTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94BondChargeIncrementTable) -> MMFF94BondChargeIncrementTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (<tt>None</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94BondChargeIncrementTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> MMFF94BondChargeIncrementTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
