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
# \brief Atom.
# 
class Atom(AtomContainer, BondContainer, Entity3D):

    ##
    # \brief 
    #
    class AtomSequence(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Atom: pass

        ##
        # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
        # \param atom The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief 
    #
    class BondSequence(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Bond: pass

        ##
        # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
        # \param bond The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Initializes the \e %Atom instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the parent molecule.
    # 
    # \return A reference to the parent molecule.
    # 
    def getMolecule() -> Molecule: pass

    ##
    # \brief Returns a reference to the Chem.Bond object that connects this atom to the argument atom.
    # 
    # \param atom The adjacent atom for which to return the connecting bond.
    # 
    # \return A reference to the Chem.Bond object connecting this atom and the argument atom. 
    # 
    # \throw Base.ItemNotFound if the argument atom is not connected to this atom.
    # 
    def getBondToAtom(atom: Atom) -> Bond: pass

    ##
    # \brief Returns a reference to the Chem.Bond object that connects this atom to the argument atom.
    # 
    # \param atom The adjacent atom for which to return a reference to the connecting bond.
    # 
    # \return A reference to the Chem.Bond object that connects this atom to the argument atom, or <em>None</em> if the argument atom is not connected.
    # 
    def findBondToAtom(atom: Atom) -> Bond: pass

    ##
    # \brief Returns the index of the atom in its parent molecule.
    # 
    # \return The zero-based index of the atom.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Assignment operator that replaces the current set of properties with the properties of <em>atom</em>;.
    # 
    # \param atom The atom whose properties get copied.
    # 
    # \return \a self
    # 
    def assign(atom: Atom) -> Atom: pass

    ##
    # \brief 
    # \return 
    #
    def getAtoms() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getBonds() -> object: pass

    ##
    # \brief Returns a reference to the connected atom at index <em>idx</em>.
    # 
    # \param idx The index of the atom to return.
    # 
    # \return A reference to the connected atom at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    # \note The order of connected atoms corresponds to the order of connecting bonds.
    # 
    def getAtom(idx: int) -> Atom: pass

    ##
    # \brief Tells whether this atom and the argument atom are connected by a bond.
    # 
    # \param atom The atom to test for adjacency.
    # 
    # \return <tt>True</tt> if the argument atom is connected to this atom, and <tt>False</tt> otherwise.
    # 
    def containsAtom(atom: Atom) -> bool: pass

    ##
    # \brief Returns the index of the specified connected atom.
    # 
    # \param atom The connected atom for which to return the index.
    # 
    # \return The zero-based index of the specified atom. 
    # 
    # \throw Base.ItemNotFound if the specified atom is not connected to this atom.
    # 
    def getAtomIndex(atom: Atom) -> int: pass

    ##
    # \brief Returns the number of connected atoms.
    # 
    # Equivalent to getNumBonds().
    # 
    # \return The number of connected atoms.
    # 
    def getNumAtoms() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def orderAtoms(func: ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getEntity(idx: int) -> Entity3D: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntities() -> int: pass

    ##
    # \brief Returns a reference to the incident bond at index <em>idx</em>.
    # 
    # \param idx The index of the incident bond to return.
    # 
    # \return A reference to the incident bond at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumBonds() - 1].
    # 
    # \note The order of incident bonds corresponds to the order of connected atoms.
    # 
    def getBond(idx: int) -> Bond: pass

    ##
    # \brief Tells whether the specified bond is incident to this atom.
    # 
    # \param bond The bond to test for incidence.
    # 
    # \return <tt>True</tt> if the argument bond is incident to this atom, and <tt>False</tt> otherwise.
    # 
    def containsBond(bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param func 
    #
    def orderBonds(func: BoolBond2Functor) -> None: pass

    ##
    # \brief Returns the index of the specified incident bond.
    # 
    # \param bond The bond for which to return the index.
    # 
    # \return The zero-based index of the specified bond. 
    # 
    # \throw Base.ItemNotFound if the specified bond is not incident to this atom.
    # 
    def getBondIndex(bond: Bond) -> int: pass

    ##
    # \brief Returns the number of incident bonds.
    # 
    # Equivalent to getNumAtoms().
    # 
    # \return The number of incident bonds.
    # 
    def getNumBonds() -> int: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
    # \param bond The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    molecule = property(getMolecule)

    index = property(getIndex)

    atoms = property(getAtoms)

    bonds = property(getBonds)
