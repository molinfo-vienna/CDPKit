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
# \brief Data structure for the storage and lookup of heavy-to-hydrogen symbolic MMFF94 atom type mappings.
# 
class MMFF94HeavyToHydrogenAtomTypeMap(Boost.Python.instance):

    ##
    # \brief The type of the map entries.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \c %Entry instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes a copy of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \c %Entry instance.
        # \param parent_type 
        # \param h_atom_type 
        # 
        def __init__(parent_type: str, h_atom_type: str) -> None: pass

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
        # \brief 
        # \return 
        #
        def getParentAtomType() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getHydrogenAtomType() -> str: pass

        objectID = property(getObjectID)

        parentAtomType = property(getParentAtomType)

        hydrogenAtomType = property(getHydrogenAtomType)

    ##
    # \brief Constructs an empty <tt>MMFF94HeavyToHydrogenAtomTypeMap</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94HeavyToHydrogenAtomTypeMap instance \a map.
    # \param map The \c %MMFF94HeavyToHydrogenAtomTypeMap instance to copy.
    # 
    def __init__(map: MMFF94HeavyToHydrogenAtomTypeMap) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94HeavyToHydrogenAtomTypeMap instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94HeavyToHydrogenAtomTypeMap instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param parent_type 
    # \param h_atom_type 
    #
    def addEntry(parent_type: str, h_atom_type: str) -> None: pass

    ##
    # \brief Removes the mapping for the symbolic MMFF94 heavy atom type <em>parent_type</em>.
    # 
    # \param parent_type The symbolic MMFF94 type of the heavy parent atom.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(parent_type: str) -> bool: pass

    ##
    # \brief Returns the symbolic MMFF94 hydrogen type associated with the heavy atom type <em>parent_type</em>.
    # 
    # \param parent_type The symbolic MMFF94 type of the heavy parent atom.
    # 
    # \return A reference to the symbolic hydrogen type, or to an empty string if no mapping exists.
    # 
    def getEntry(parent_type: str) -> object: pass

    ##
    # \brief Removes all entries from the map.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of mappings stored in the map.
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
    # \brief Loads the built-in default MMFF94 heavy-to-hydrogen symbolic atom type mappings.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94HeavyToHydrogenAtomTypeMap instance \a map.
    # \param map The \c %MMFF94HeavyToHydrogenAtomTypeMap instance to copy.
    # \return \a self
    # 
    def assign(map: MMFF94HeavyToHydrogenAtomTypeMap) -> MMFF94HeavyToHydrogenAtomTypeMap: pass

    ##
    # \brief Replaces the process-wide default map by <em>map</em>.
    # 
    # \param map The new default map (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(map: MMFF94HeavyToHydrogenAtomTypeMap) -> None: pass

    ##
    # \brief Returns the process-wide default map (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> MMFF94HeavyToHydrogenAtomTypeMap: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
