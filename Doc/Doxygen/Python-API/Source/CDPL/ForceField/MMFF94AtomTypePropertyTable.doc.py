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
# \brief Data structure for the storage and lookup of structural and chemical property data associated with numeric MMFF94 atom types.
# 
# Each entry provides the corresponding atomic number, the standard neighbour count and valence, and flags describing pi lone pair character, aromaticity, linear bond angle geometry, and the ability to form multi bond or single bond patterns.
# 
# \see [\ref MMFF94]
# 
class MMFF94AtomTypePropertyTable(Boost.Python.instance):

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
        # \param atomic_no The atomic number of atoms of this type.
        # \param num_nbrs The standard number of explicit neighbour atoms.
        # \param valence The standard valence.
        # \param has_pi_lp <tt>True</tt> if the atom type carries a pi lone pair.
        # \param mltb_desig The MMFF94 multi bond designator.
        # \param is_arom <tt>True</tt> if the atom type is aromatic.
        # \param lin_bnd_ang <tt>True</tt> if the atom type forms linear bond angles.
        # \param has_mb_or_sb <tt>True</tt> if the atom type can form multi bond or single bond patterns.
        # 
        def __init__(atom_type: int, atomic_no: int, num_nbrs: int, valence: int, has_pi_lp: bool, mltb_desig: int, is_arom: bool, lin_bnd_ang: bool, has_mb_or_sb: bool) -> None: pass

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
        # \brief Returns the atomic number of atoms of this type.
        # 
        # \return The atomic number.
        # 
        def getAtomicNumber() -> int: pass

        ##
        # \brief Returns the standard number of explicit neighbour atoms.
        # 
        # \return The neighbour count.
        # 
        def getNumNeighbors() -> int: pass

        ##
        # \brief Returns the standard valence of atoms of this type.
        # 
        # \return The valence.
        # 
        def getValence() -> int: pass

        ##
        # \brief Tells whether the atom type carries a pi lone pair.
        # 
        # \return <tt>True</tt> if the atom type carries a pi lone pair, and <tt>False</tt> otherwise.
        # 
        def hasPiLonePair() -> bool: pass

        ##
        # \brief Returns the MMFF94 multi bond designator.
        # 
        # \return The multi bond designator.
        # 
        def getMultiBondDesignator() -> int: pass

        ##
        # \brief Tells whether the atom type is aromatic.
        # 
        # \return <tt>True</tt> if the atom type is aromatic, and <tt>False</tt> otherwise.
        # 
        def isAromaticAtomType() -> bool: pass

        ##
        # \brief Tells whether the atom type forms linear bond angles.
        # 
        # \return <tt>True</tt> if the atom type forms linear bond angles, and <tt>False</tt> otherwise.
        # 
        def formsLinearBondAngle() -> bool: pass

        ##
        # \brief Tells whether the atom type can form multi bond or single bond patterns.
        # 
        # \return <tt>True</tt> if such patterns are allowed, and <tt>False</tt> otherwise.
        # 
        def formsMultiOrSingleBonds() -> bool: pass

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

        atomicNumber = property(getAtomicNumber)

        numNeighbors = property(getNumNeighbors)

        valence = property(getValence)

        piLonePair = property(hasPiLonePair)

        multiBondDesignator = property(getMultiBondDesignator)

        aromAtomType = property(isAromaticAtomType)

        linearBondAngle = property(formsLinearBondAngle)

        multiOrSingleBonds = property(formsMultiOrSingleBonds)

    ##
    # \brief Constructs an empty <tt>MMFF94AtomTypePropertyTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94AtomTypePropertyTable instance \a table.
    # \param table The \c %MMFF94AtomTypePropertyTable instance to copy.
    # 
    def __init__(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94AtomTypePropertyTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94AtomTypePropertyTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry for the numeric MMFF94 atom type <em>atom_type</em> that stores the given property values.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # \param atomic_no The atomic number of atoms of this type.
    # \param num_nbrs The standard number of explicit neighbour atoms.
    # \param valence The standard valence.
    # \param has_pi_lp <tt>True</tt> if the atom type carries a pi lone pair.
    # \param mltb_desig The MMFF94 multi bond designator.
    # \param is_arom <tt>True</tt> if the atom type is aromatic.
    # \param lin_bnd_ang <tt>True</tt> if the atom type forms linear bond angles.
    # \param has_mb_or_sb <tt>True</tt> if the atom type can form multi bond or single bond patterns.
    # 
    def addEntry(atom_type: int, atomic_no: int, num_nbrs: int, valence: int, has_pi_lp: bool, mltb_desig: int, is_arom: bool, lin_bnd_ang: bool, has_mb_or_sb: bool) -> None: pass

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
    # \brief Loads the built-in default MMFF94 atom type property entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94AtomTypePropertyTable instance \a table.
    # \param table The \c %MMFF94AtomTypePropertyTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94AtomTypePropertyTable) -> MMFF94AtomTypePropertyTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> MMFF94AtomTypePropertyTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
