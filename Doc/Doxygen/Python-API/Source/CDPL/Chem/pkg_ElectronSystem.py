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
# \brief Describes an electron system of a molecule in terms of involved atoms and their electron contributions.
# 
class ElectronSystem(AtomContainer):

    ##
    # \brief Constructs an empty <tt>ElectronSystem</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ElectronSystem instance.
    # \param self The \e %ElectronSystem instance to initialize.
    # \param elec_sys 
    # 
    def __init__(elec_sys: ElectronSystem) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ElectronSystem instance this method is called upon.
    # 
    # Different Python \e %ElectronSystem instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ElectronSystem instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param elec_sys 
    # \return 
    #
    def assign(elec_sys: ElectronSystem) -> ElectronSystem: pass

    ##
    # \brief Extends the electron system by the specified atom and its electron contributions.
    # 
    # \param atom The atom to add.
    # \param elec_contrib The number of electrons contributed by the added atom.
    # 
    # \return <tt>True</tt> if the atom was not already involved in this electron system and <tt>False</tt>, otherwise. 
    # 
    # \note If the atom is already part of the system no changes will be made.
    # 
    def addAtom(atom: Atom, elec_contrib: int) -> bool: pass

    ##
    # \brief Adds the atoms and associated electron contributions in the electron system <em>elec_sys</em> to this system.
    # 
    # The method is equivalent to repeatedly calling addAtom() for each atom in <em>elec_sys</em>.
    # 
    # \param elec_sys The electron system to add.
    # 
    # \return <tt>True</tt> if the electron system was extended by atoms from <em>elec_sys</em> and <tt>False</tt>, otherwise.
    # 
    def addAtoms(elec_sys: ElectronSystem) -> bool: pass

    ##
    # \brief Removes the atom at the specified index.
    # 
    # \param idx The zero-based index of the atom to remove.
    # 
    # \throw Base.IndexError if the number of atoms is zero or <em>idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    def removeAtom(idx: int) -> None: pass

    ##
    # \brief Removes the specified atom.
    # 
    # \param atom The atom to remove.
    # 
    # \return <tt>True</tt> if the atom was part of the electron system and has been removed, and <tt>False</tt> otherwise.
    # 
    def removeAtom(atom: Atom) -> bool: pass

    ##
    # \brief Removes all atoms.
    # 
    def clear() -> None: pass

    ##
    # \brief Exchanges the state of this electron system with the state of the system <em>elec_sys</em>.
    # 
    # \param elec_sys The other <tt>ElectronSystem</tt> instance.
    # 
    def swap(elec_sys: ElectronSystem) -> None: pass

    ##
    # \brief Returns the total number of electrons contributed by the involved atoms.
    # 
    # \return The total electron count of this system.
    # 
    def getNumElectrons() -> int: pass

    ##
    # \brief Returns the number of electrons contributed by the specified atom.
    # 
    # \param atom The atom for which to return the contributed electron count.
    # 
    # \return The number of electrons contributed by the specified atom. 
    # 
    # \throw Base.ItemNotFound if the specified atom is not part of the electron system.
    # 
    def getElectronContrib(atom: Atom) -> int: pass

    ##
    # \brief Returns the number of electrons contributed by the specified atom.
    # 
    # \param atom The atom for which to return the contributed electron count.
    # 
    # \return The number of electrons contributed by the specified atom. 
    # 
    # \throw Base.ItemNotFound if the specified atom is not part of the electron system.
    # 
    def getElectronContrib(atom: int) -> int: pass

    ##
    # \brief Changes the number of electrons that are contributed by the specified atom.
    # 
    # \param atom The atom for which to update the electron contribution.
    # \param elec_contrib The number of electrons contributed by the specified atom.
    # 
    # \throw Base.ItemNotFound if the specified atom is not part of the electron system.
    # 
    def setElectronContrib(atom: Atom, elec_contrib: int) -> None: pass

    ##
    # \brief Changes the number of electrons that are contributed by the specified atom.
    # 
    # \param atom The atom for which to update the electron contribution.
    # \param elec_contrib The number of electrons contributed by the specified atom.
    # 
    # \throw Base.ItemNotFound if the specified atom is not part of the electron system.
    # 
    def setElectronContrib(atom: int, elec_contrib: int) -> None: pass

    ##
    # \brief Merges the atoms and associated electron contributions in the electron system <em>elec_sys</em> with this system.
    # 
    # For atoms that are present in both electron systems, the resulting electron contribution will be the sum of their contributions to the respective systems!
    # 
    # \param elec_sys The electron system to merge.
    # 
    def merge(elec_sys: ElectronSystem) -> None: pass

    ##
    # \brief Checks if the electron system shares at least one atom with the system <em>elec_sys</em>.
    # 
    # \param elec_sys The electron system to check for atom set intersection.
    # 
    # \return <tt>True</tt> if at least one atom in <em>elec_sys</em> is also part of this electron system and <tt>False</tt>, otherwise.
    # 
    def overlaps(elec_sys: ElectronSystem) -> bool: pass

    ##
    # \brief Checks if all atoms in the electron system <em>elec_sys</em> are also part of this electron system.
    # 
    # \param elec_sys The electron system to check for atom set containment.
    # 
    # \return <tt>True</tt> if all atoms in <em>elec_sys</em> are also part of this electron system and <tt>False</tt>, otherwise.
    # 
    def contains(elec_sys: ElectronSystem) -> bool: pass

    ##
    # \brief Checks if the atom sets of the electron systems do not intersect but are linked by at least one bond.
    # 
    # \param elec_sys The electron system to check.
    # \param bonds The set of available bonds.
    # 
    # \return <tt>True</tt> if the electron systems do not share any atoms but are linked by at least one bond and <tt>False</tt>, otherwise.
    # 
    def connected(elec_sys: ElectronSystem, bonds: BondContainer) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param self The \e %ElectronSystem instance this method is called upon.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Atom: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    objectID = property(getObjectID)

    numElectrons = property(getNumElectrons)
