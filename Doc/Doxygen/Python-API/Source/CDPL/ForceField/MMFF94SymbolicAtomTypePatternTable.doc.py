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
# \brief Data structure storing <em>SMARTS</em> substructure patterns used to assign symbolic MMFF94 atom types during atom typing.
# 
# Each entry pairs a pattern with the symbolic MMFF94 type to assign on a match. Patterns marked as fallback are only considered after no non-fallback pattern matches.
# 
# \see [\ref MMFF94]
# 
class MMFF94SymbolicAtomTypePatternTable(Boost.Python.instance):

    ##
    # \brief A single atom type pattern record.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Constructs an <tt>Entry</tt> pairing the pattern <em>ptn</em> with the symbolic type <em>sym_type</em>.
        # 
        # \param ptn The substructure pattern.
        # \param sym_type The symbolic MMFF94 atom type to assign on a match.
        # \param fallback <tt>True</tt> if the pattern is only to be tried after all non-fallback patterns failed.
        # 
        def __init__(ptn: Chem.MolecularGraph, sym_type: str, fallback: bool) -> None: pass

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
        # \brief Returns the substructure pattern.
        # 
        # \return A reference to the pattern shared reference.
        # 
        def getPattern() -> Chem.MolecularGraph: pass

        ##
        # \brief Returns the symbolic MMFF94 atom type assigned on a match.
        # 
        # \return A reference to the symbolic atom type.
        # 
        def getSymbolicType() -> str: pass

        ##
        # \brief Tells whether the pattern is a fallback pattern.
        # 
        # \return <tt>True</tt> if the pattern is a fallback pattern, and <tt>False</tt> otherwise.
        # 
        def isFallbackType() -> bool: pass

        objectID = property(getObjectID)

        symbolicType = property(getSymbolicType)

        pattern = property(getPattern)

        fallbackType = property(isFallbackType)

    ##
    # \brief Constructs an empty <tt>MMFF94SymbolicAtomTypePatternTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94SymbolicAtomTypePatternTable instance \a table.
    # \param table The \c %MMFF94SymbolicAtomTypePatternTable instance to copy.
    # 
    def __init__(table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94SymbolicAtomTypePatternTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94SymbolicAtomTypePatternTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Appends a new pattern entry to the table.
    # 
    # \param ptn The substructure pattern.
    # \param sym_type The symbolic MMFF94 atom type to assign on a match.
    # \param fallback <tt>True</tt> if the pattern is only to be tried after all non-fallback patterns failed.
    # 
    def addEntry(ptn: Chem.MolecularGraph, sym_type: str, fallback: bool) -> None: pass

    ##
    # \brief Removes the entry at the zero-based index <em>idx</em>.
    # 
    # \param idx The zero-based entry index.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumEntries()).
    # 
    def removeEntry(idx: int) -> None: pass

    ##
    # \brief Returns the entry at the zero-based index <em>idx</em>.
    # 
    # \param idx The zero-based entry index.
    # 
    # \return A reference to the entry. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumEntries()).
    # 
    def getEntry(idx: int) -> Entry: pass

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
    # \brief Loads the built-in default MMFF94 atom type patterns.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94SymbolicAtomTypePatternTable instance \a table.
    # \param table The \c %MMFF94SymbolicAtomTypePatternTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94SymbolicAtomTypePatternTable) -> MMFF94SymbolicAtomTypePatternTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94SymbolicAtomTypePatternTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A reference to the default table shared reference.
    # 
    @staticmethod
    def get(: ) -> MMFF94SymbolicAtomTypePatternTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
