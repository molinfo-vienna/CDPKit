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
# \brief Lookup table mapping (atomic-number 1, atomic-number 2) pairs to fallback MMFF94 bond-stretching parameters used when no atom-type-specific entry is available.
# 
class MMFF94BondStretchingRuleParameterTable(Boost.Python.instance):

    ##
    # \brief A single rule-based bond-stretching parameter record.
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
        # \brief Constructs an <tt>Entry</tt> for the given (atomic number 1, atomic number 2) pair.
        # 
        # \param atomic_no1 The atomic number of the first bonded atom.
        # \param atomic_no2 The atomic number of the second bonded atom.
        # \param force_const The bond-stretching force constant.
        # \param ref_length The reference bond length.
        # 
        def __init__(atomic_no1: int, atomic_no2: int, force_const: float, ref_length: float) -> None: pass

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
        # \brief Returns the atomic number of the first bonded atom.
        # 
        # \return The first atom's atomic number.
        # 
        def getAtomicNumber1() -> int: pass

        ##
        # \brief Returns the atomic number of the second bonded atom.
        # 
        # \return The second atom's atomic number.
        # 
        def getAtomicNumber2() -> int: pass

        ##
        # \brief Returns the bond-stretching force constant.
        # 
        # \return The force constant.
        # 
        def getForceConstant() -> float: pass

        ##
        # \brief Returns the reference bond length.
        # 
        # \return The reference bond length.
        # 
        def getReferenceLength() -> float: pass

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

        atomicNo1 = property(getAtomicNumber1)

        atomicNo2 = property(getAtomicNumber2)

        forceConstant = property(getForceConstant)

        referenceLength = property(getReferenceLength)

    ##
    # \brief Constructs an empty <tt>MMFF94BondStretchingRuleParameterTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94BondStretchingRuleParameterTable instance \a table.
    # \param table The \c %MMFF94BondStretchingRuleParameterTable instance to copy.
    # 
    def __init__(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94BondStretchingRuleParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94BondStretchingRuleParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds (or overwrites) the entry for the given (atomic number 1, atomic number 2) pair.
    # 
    # \param atomic_no1 The atomic number of the first bonded atom.
    # \param atomic_no2 The atomic number of the second bonded atom.
    # \param force_const The bond-stretching force constant.
    # \param ref_length The reference bond length.
    # 
    def addEntry(atomic_no1: int, atomic_no2: int, force_const: float, ref_length: float) -> None: pass

    ##
    # \brief Removes the entry for the given (atomic number 1, atomic number 2) pair.
    # 
    # \param atomic_no1 The atomic number of the first bonded atom.
    # \param atomic_no2 The atomic number of the second bonded atom.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(atomic_no1: int, atomic_no2: int) -> bool: pass

    ##
    # \brief Returns the entry for the given (atomic number 1, atomic number 2) pair.
    # 
    # \param atomic_no1 The atomic number of the first bonded atom.
    # \param atomic_no2 The atomic number of the second bonded atom.
    # 
    # \return A reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns <tt>False</tt>) if no match exists.
    # 
    def getEntry(atomic_no1: int, atomic_no2: int) -> Entry: pass

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
    # \brief Loads the built-in default bond-stretching rule parameter entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94BondStretchingRuleParameterTable instance \a table.
    # \param table The \c %MMFF94BondStretchingRuleParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94BondStretchingRuleParameterTable) -> MMFF94BondStretchingRuleParameterTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A reference to the default-table shared reference.
    # 
    @staticmethod
    def get(: ) -> MMFF94BondStretchingRuleParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
