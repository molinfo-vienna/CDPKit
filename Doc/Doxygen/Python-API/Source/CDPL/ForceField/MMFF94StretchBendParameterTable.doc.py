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
# \brief Data structure for the storage and lookup of MMFF94 stretch-bend interaction parameters.
# 
# Two directional force constants are stored per entry: <tt>IJK</tt> couples the bond <em>i-j</em> to the angle <em>i-j-k</em>, and <tt>KJI</tt> couples the bond <em>j-k</em> to the same angle.
# 
class MMFF94StretchBendParameterTable(Boost.Python.instance):

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
        # \brief Constructs an <tt>Entry</tt> instance storing the given query and parameter values.
        # 
        # \param sb_type_idx The MMFF94 stretch-bend type index.
        # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
        # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
        # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
        # \param ijk_force_const The IJK stretch-bend force constant.
        # \param kji_force_const The KJI stretch-bend force constant.
        # 
        def __init__(sb_type_idx: int, term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int, ijk_force_const: float, kji_force_const: float) -> None: pass

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
        # \brief Returns the MMFF94 stretch-bend type index.
        # 
        # \return The stretch-bend type index.
        # 
        def getStretchBendTypeIndex() -> int: pass

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
        # \brief Returns the IJK stretch-bend force constant (couples bond <em>i-j</em> to angle <em>i-j-k</em>).
        # 
        # \return The IJK force constant.
        # 
        def getIJKForceConstant() -> float: pass

        ##
        # \brief Returns the KJI stretch-bend force constant (couples bond <em>j-k</em> to angle <em>i-j-k</em>).
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

        stretchBendTypeIndex = property(getStretchBendTypeIndex)

        termAtom1Type = property(getTerminalAtom1Type)

        ctrAtomType = property(getCenterAtomType)

        termAtom2Type = property(getTerminalAtom2Type)

        ijkForceConstant = property(getIJKForceConstant)

        kjiForceConstant = property(getKJIForceConstant)

    ##
    # \brief Constructs an empty <tt>MMFF94StretchBendParameterTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94StretchBendParameterTable instance \a table.
    # \param table The \c %MMFF94StretchBendParameterTable instance to copy.
    # 
    def __init__(table: MMFF94StretchBendParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94StretchBendParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94StretchBendParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry for the given query and parameter values.
    # 
    # \param sb_type_idx The MMFF94 stretch-bend type index.
    # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
    # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
    # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
    # \param ijk_force_const The IJK stretch-bend force constant.
    # \param kji_force_const The KJI stretch-bend force constant.
    # 
    def addEntry(sb_type_idx: int, term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief Removes the entry matching the specified query values.
    # 
    # \param sb_type_idx The MMFF94 stretch-bend type index.
    # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
    # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
    # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(sb_type_idx: int, term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int) -> bool: pass

    ##
    # \brief Returns a reference to the entry matching the specified query values.
    # 
    # \param sb_type_idx The MMFF94 stretch-bend type index.
    # \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
    # \param ctr_atom_type The numeric MMFF94 atom type of the center atom.
    # \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
    # 
    # \return A reference to the matching entry or to an uninitialized entry if no matching entry exists.
    # 
    def getEntry(sb_type_idx: int, term_atom1_type: int, ctr_atom_type: int, term_atom2_type: int) -> Entry: pass

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
    # \brief Loads the built-in default MMFF94 stretch-bend parameter entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94StretchBendParameterTable instance \a table.
    # \param table The \c %MMFF94StretchBendParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94StretchBendParameterTable) -> MMFF94StretchBendParameterTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94StretchBendParameterTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> MMFF94StretchBendParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
