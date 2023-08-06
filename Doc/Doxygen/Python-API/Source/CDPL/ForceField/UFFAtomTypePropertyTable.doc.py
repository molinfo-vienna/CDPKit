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
# \brief 
#
class UFFAtomTypePropertyTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param atom_type 
        # \param atom_type_sym 
        # \param atomic_no 
        # \param bond_rad 
        # \param bond_ang 
        # \param vdw_dist 
        # \param vdw_energy 
        # \param vdw_scale 
        # \param eff_charge 
        # 
        def __init__(atom_type: int, atom_type_sym: str, atomic_no: int, bond_rad: float, bond_ang: float, vdw_dist: float, vdw_energy: float, vdw_scale: float, eff_charge: float) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomType() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomicNumber() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomTypeSymbol() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getBondRadius() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getBondAngle() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getVdWDistance() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getVdWEnergy() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getVdWScale() -> float: pass

        ##
        # \brief 
        # \return 
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
    # \brief Initializes the \e %UFFAtomTypePropertyTable instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %UFFAtomTypePropertyTable instance with a copy of the state of the \e %UFFAtomTypePropertyTable instance \a table.
    # \param table The \e %UFFAtomTypePropertyTable instance to copy.
    # 
    def __init__(table: UFFAtomTypePropertyTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %UFFAtomTypePropertyTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %UFFAtomTypePropertyTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param atom_type 
    # \param atom_type_sym 
    # \param atomic_no 
    # \param bond_rad 
    # \param bond_ang 
    # \param vdw_dist 
    # \param vdw_energy 
    # \param vdw_scale 
    # \param eff_charge 
    #
    def addEntry(atom_type: int, atom_type_sym: str, atomic_no: int, bond_rad: float, bond_ang: float, vdw_dist: float, vdw_energy: float, vdw_scale: float, eff_charge: float) -> None: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def getEntry(atom_type: int) -> Entry: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %UFFAtomTypePropertyTable instance \a table.
    # \param table The \e %UFFAtomTypePropertyTable instance to copy.
    # \return \a self
    # 
    def assign(table: UFFAtomTypePropertyTable) -> UFFAtomTypePropertyTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: UFFAtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> UFFAtomTypePropertyTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
