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
# \brief Data structure for the storage and lookup of various properties associated with numeric UFF atom types.
# 
# Each entry provides the natural bond radius and bond angle of the atom type, its Van der Waals parameters (well distance, well depth, and scaling factor), and the effective atomic charge used by the UFF electrostatic terms.
# 
# \see [\ref UFF]
# 
class UFFAtomTypePropertyTable(Boost.Python.instance):

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
        # \param atom_type The numeric UFF atom type.
        # \param atom_type_sym The UFF atom type symbol.
        # \param atomic_no The atomic number of atoms of this type.
        # \param bond_rad The natural bond radius.
        # \param bond_ang The natural bond angle.
        # \param vdw_dist The Van der Waals distance parameter (well distance).
        # \param vdw_energy The Van der Waals energy parameter (well depth).
        # \param vdw_scale The Van der Waals scaling factor.
        # \param eff_charge The effective atomic charge used by the UFF electrostatic terms.
        # 
        def __init__(atom_type: int, atom_type_sym: str, atomic_no: int, bond_rad: float, bond_ang: float, vdw_dist: float, vdw_energy: float, vdw_scale: float, eff_charge: float) -> None: pass

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
        # \brief Returns the numeric UFF atom type of the entry.
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
        # \brief Returns the UFF atom type symbol.
        # 
        # \return A reference to the atom type symbol.
        # 
        def getAtomTypeSymbol() -> str: pass

        ##
        # \brief Returns the natural bond radius of the atom type.
        # 
        # \return The bond radius.
        # 
        def getBondRadius() -> float: pass

        ##
        # \brief Returns the natural bond angle of the atom type.
        # 
        # \return The bond angle.
        # 
        def getBondAngle() -> float: pass

        ##
        # \brief Returns the Van der Waals well distance of the atom type.
        # 
        # \return The Van der Waals distance parameter.
        # 
        def getVdWDistance() -> float: pass

        ##
        # \brief Returns the Van der Waals well depth of the atom type.
        # 
        # \return The Van der Waals energy parameter.
        # 
        def getVdWEnergy() -> float: pass

        ##
        # \brief Returns the Van der Waals scaling factor of the atom type.
        # 
        # \return The Van der Waals scaling factor.
        # 
        def getVdWScale() -> float: pass

        ##
        # \brief Returns the effective atomic charge used by the UFF electrostatic terms.
        # 
        # \return The effective atomic charge.
        # 
        def getEffectiveCharge() -> float: pass

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

        atomTypeSymbol = property(getAtomTypeSymbol)

        bondRadius = property(getBondRadius)

        bondAngle = property(getBondAngle)

        vdwDistance = property(getVdWDistance)

        vdwEnergy = property(getVdWEnergy)

        vdwScale = property(getVdWScale)

        effectiveCharge = property(getEffectiveCharge)

    ##
    # \brief Constructs an empty <tt>UFFAtomTypePropertyTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %UFFAtomTypePropertyTable instance \a table.
    # \param table The \c %UFFAtomTypePropertyTable instance to copy.
    # 
    def __init__(table: UFFAtomTypePropertyTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %UFFAtomTypePropertyTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %UFFAtomTypePropertyTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry for the numeric UFF atom type <em>atom_type</em> that stores the given property values.
    # 
    # \param atom_type The numeric UFF atom type.
    # \param atom_type_sym The UFF atom type symbol.
    # \param atomic_no The atomic number of atoms of this type.
    # \param bond_rad The natural bond radius.
    # \param bond_ang The natural bond angle.
    # \param vdw_dist The Van der Waals distance parameter (well distance).
    # \param vdw_energy The Van der Waals energy parameter (well depth).
    # \param vdw_scale The Van der Waals scaling factor.
    # \param eff_charge The effective atomic charge used by the UFF electrostatic terms.
    # 
    def addEntry(atom_type: int, atom_type_sym: str, atomic_no: int, bond_rad: float, bond_ang: float, vdw_dist: float, vdw_energy: float, vdw_scale: float, eff_charge: float) -> None: pass

    ##
    # \brief Removes the entry for the numeric UFF atom type <em>atom_type</em>.
    # 
    # \param atom_type The numeric UFF atom type.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief Returns the entry for the numeric UFF atom type <em>atom_type</em>.
    # 
    # \param atom_type The numeric UFF atom type.
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
    # \brief Loads the built-in default UFF atom type property entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %UFFAtomTypePropertyTable instance \a table.
    # \param table The \c %UFFAtomTypePropertyTable instance to copy.
    # \return \a self
    # 
    def assign(table: UFFAtomTypePropertyTable) -> UFFAtomTypePropertyTable: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: UFFAtomTypePropertyTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
    # 
    @staticmethod
    def get(: ) -> UFFAtomTypePropertyTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
