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
# \brief Data structure for the storage and lookup of MMFF94 aromatic atom type definitions.
# 
# After the initial pattern-based typing has produced provisional atom types, this table is consulted to upgrade aromatic-ring atoms to their proper MMFF94 aromatic types based on atomic number, ring size, distance to the next heteroatom in the ring, and special-case flags for imidazolium-like cations and 5-ring anions.
# 
class MMFF94AromaticAtomTypeDefinitionTable(Boost.Python.instance):

    ##
    # \brief Data structure for the storage of values associated with a single table entry.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Constructs an <tt>Entry</tt> instance storing the given values.
        # 
        # \param old_type The symbolic provisional atom type assigned by initial typing.
        # \param aro_type The symbolic MMFF94 aromatic atom type to assign on a match.
        # \param atomic_no The atomic number required for the match.
        # \param ring_size The ring size required for the match.
        # \param het_atom_dist The required topological distance (along the ring) to the next heteroatom.
        # \param im_cation <tt>True</tt> to restrict the match to imidazolium-like cations.
        # \param n5_anion <tt>True</tt> to restrict the match to 5-ring anion centers.
        # 
        def __init__(old_type: str, aro_type: str, atomic_no: int, ring_size: int, het_atom_dist: int, im_cation: bool, n5_anion: bool) -> None: pass

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
        # \brief Returns the provisional (input) atom type of the entry.
        # 
        # \return A reference to the provisional atom type.
        # 
        def getOldAtomType() -> str: pass

        ##
        # \brief Returns the aromatic MMFF94 atom type assigned on a match.
        # 
        # \return A reference to the aromatic atom type.
        # 
        def getAromAtomType() -> str: pass

        ##
        # \brief Returns the atomic number required for a match.
        # 
        # \return The atomic number.
        # 
        def getAtomicNumber() -> int: pass

        ##
        # \brief Returns the ring size required for a match.
        # 
        # \return The ring size.
        # 
        def getRingSize() -> int: pass

        ##
        # \brief Returns the required topological distance (along the ring) to the next heteroatom.
        # 
        # \return The heteroatom distance.
        # 
        def getHeteroAtomDistance() -> int: pass

        ##
        # \brief Tells whether the match is restricted to imidazolium-like cations.
        # 
        # \return <tt>True</tt> if the match is restricted to imidazolium-like cations, and <tt>False</tt> otherwise.
        # 
        def isImidazoliumCation() -> bool: pass

        ##
        # \brief Tells whether the match is restricted to 5-ring anion centers.
        # 
        # \return <tt>True</tt> if the match is restricted to 5-ring anion centers, and <tt>False</tt> otherwise.
        # 
        def isN5RingAnion() -> bool: pass

        objectID = property(getObjectID)

        oldAtomType = property(getOldAtomType)

        aromAtomType = property(getAromAtomType)

        atomicNumber = property(getAtomicNumber)

        ringSize = property(getRingSize)

        heteroAtomDistance = property(getHeteroAtomDistance)

        imidazoliumCation = property(isImidazoliumCation)

        n5RingAnion = property(isN5RingAnion)

    ##
    # \brief Constructs an empty <tt>MMFF94AromaticAtomTypeDefinitionTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94AromaticAtomTypeDefinitionTable instance \a table.
    # \param table The \c %MMFF94AromaticAtomTypeDefinitionTable instance to copy.
    # 
    def __init__(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94AromaticAtomTypeDefinitionTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94AromaticAtomTypeDefinitionTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry to the table that stores the given values.
    # 
    # \param old_type The symbolic provisional atom type assigned by initial typing.
    # \param aro_type The symbolic MMFF94 aromatic atom type to assign on a match.
    # \param atomic_no The atomic number required for the match.
    # \param ring_size The ring size required for the match.
    # \param het_atom_dist The required topological distance (along the ring) to the next heteroatom.
    # \param im_cation <tt>True</tt> to restrict the match to imidazolium-like cations.
    # \param n5_anion <tt>True</tt> to restrict the match to 5-ring anion centers.
    # 
    def addEntry(old_type: str, aro_type: str, atomic_no: int, ring_size: int, het_atom_dist: int, im_cation: bool, n5_anion: bool) -> None: pass

    ##
    # \brief Removes the entry at index <em>idx</em>.
    # 
    # \param idx The zero-based entry index.
    # 
    # \throw Base.IndexError if the number of entries is zero or <em>idx</em> is not in the range [0, getNumEntries() - 1].
    # 
    def removeEntry(idx: int) -> None: pass

    ##
    # \brief Returns the entry at index <em>idx</em>.
    # 
    # \param idx The zero-based entry index.
    # 
    # \return A reference to the entry. 
    # 
    # \throw Base.IndexError if the number of entries is zero or <em>idx</em> is not in the range [0, getNumEntries() - 1].
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
    # \brief Loads the built-in default MMFF94 aromatic atom type definitions.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94AromaticAtomTypeDefinitionTable instance \a table.
    # \param table The \c %MMFF94AromaticAtomTypeDefinitionTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94AromaticAtomTypeDefinitionTable) -> MMFF94AromaticAtomTypeDefinitionTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> MMFF94AromaticAtomTypeDefinitionTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
