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
# \brief Lookup table mapping each primary numeric MMFF94 atom type to the ordered list of fallback numeric atom types used when looking up missing interaction parameters.
# 
class MMFF94PrimaryToParameterAtomTypeMap(Boost.Python.instance):

    ##
    # \brief A single primary-to-parameter atom-type-map record.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Number of parameter atom types stored per entry.
        # 
        NUM_TYPES = 4

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
        # \brief Initializes the \c %Entry instance.
        # \param atom_type 
        # \param param_types 
        # 
        def __init__(atom_type: int, param_types: object) -> None: pass

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
        # \brief Returns the primary numeric MMFF94 atom type of the entry.
        # 
        # \return The primary atom type.
        # 
        def getAtomType() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getParameterAtomTypes() -> object: pass

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

        paramAtomTypes = property(getParameterAtomTypes)

    ##
    # \brief Constructs an empty <tt>MMFF94PrimaryToParameterAtomTypeMap</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94PrimaryToParameterAtomTypeMap instance \a map.
    # \param map The \c %MMFF94PrimaryToParameterAtomTypeMap instance to copy.
    # 
    def __init__(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94PrimaryToParameterAtomTypeMap instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94PrimaryToParameterAtomTypeMap instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds (or overwrites) the entry for the primary atom type <em>atom_type</em>.
    # 
    # \param atom_type The primary numeric MMFF94 atom type.
    # \param param_types A length-<tt>Entry.NUM_TYPES</tt> array of fallback parameter atom types.
    # 
    def addEntry(atom_type: int, param_types: object) -> None: pass

    ##
    # \brief Removes the entry for the primary atom type <em>atom_type</em>.
    # 
    # \param atom_type The primary numeric MMFF94 atom type.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief Returns the entry for the primary atom type <em>atom_type</em>.
    # 
    # \param atom_type The primary numeric MMFF94 atom type.
    # 
    # \return A reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns <tt>False</tt>) if no match exists.
    # 
    def getEntry(atom_type: int) -> Entry: pass

    ##
    # \brief Removes all entries from the map.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of entries stored in the map.
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
    # \brief Loads map entries from the input stream <em>is</em>.
    # 
    # \param is The input stream to read from.
    # 
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief Loads the built-in default primary-to-parameter atom-type mappings.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94PrimaryToParameterAtomTypeMap instance \a map.
    # \param map The \c %MMFF94PrimaryToParameterAtomTypeMap instance to copy.
    # \return \a self
    # 
    def assign(map: MMFF94PrimaryToParameterAtomTypeMap) -> MMFF94PrimaryToParameterAtomTypeMap: pass

    ##
    # \brief 
    # \param map 
    #
    @staticmethod
    def set(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Returns the process-wide default map (lazily initialized on first call).
    # 
    # \return A reference to the default-map shared reference.
    # 
    @staticmethod
    def get(: ) -> MMFF94PrimaryToParameterAtomTypeMap: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
