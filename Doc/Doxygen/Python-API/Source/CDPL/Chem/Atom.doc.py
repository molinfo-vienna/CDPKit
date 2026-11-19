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
# \brief Abstract base class representing a chemical atom and its bonded neighborhood.
# 
# <tt>Atom</tt> combines the per-atom property storage inherited from Chem.Entity3D (and via it Base.PropertyContainer) with two adjacency views: a Chem.AtomContainer over the connected neighbor atoms and a Chem.BondContainer over the incident bonds, in matching order. Concrete implementation (Chem.BasicAtom) instances are created, owned and managed by a parent Chem.Molecule instance.
# 
class Atom(AtomContainer, BondContainer, Entity3D):

    ##
    # \brief Sequence of Chem.Atom objects.
    # 
    class AtomSequence(Boost.Python.instance):

        ##
        # \brief Returns the number of atoms.
        # 
        # \return The number of atoms.
        # 
        def __len__() -> int: pass

        ##
        # \brief Returns the atom at index <em>idx</em>.
        # 
        # \param idx The zero-based index of the atom to return.
        # 
        # \return The atom at the specified index. 
        # 
        # \throw Base.IndexError if <em>idx</em> is not in the range [0, \c len(self)).
        # 
        def __getitem__(idx: int) -> Atom: pass

        ##
        # \brief Tells whether the specified atom is part of the atom sequence.
        # 
        # \param atom The atom to look for.
        # 
        # \return <tt>True</tt> if <em>atom</em> is part of the sequence, and <tt>False</tt> otherwise.
        # 
        def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief Sequence of Chem.Bond objects.
    # 
    class BondSequence(Boost.Python.instance):

        ##
        # \brief Returns the number of bonds.
        # 
        # \return The number of bonds.
        # 
        def __len__() -> int: pass

        ##
        # \brief Returns the bond at index <em>idx</em>.
        # 
        # \param idx The zero-based index of the bond to return.
        # 
        # \return The bond at the specified index. 
        # 
        # \throw Base.IndexError if <em>idx</em> is not in the range [0, \c len(self)).
        # 
        def __getitem__(idx: int) -> Bond: pass

        ##
        # \brief Tells whether the specified bond is part of the bond sequence.
        # 
        # \param bond The bond to look for.
        # 
        # \return <tt>True</tt> if <em>bond</em> is part of the sequence, and <tt>False</tt> otherwise.
        # 
        def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Contructs the \c Atom instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the parent molecule.
    # 
    # \return The parent molecule.
    # 
    def getMolecule() -> Molecule: pass

    ##
    # \brief Returns the bond that connects this atom to the argument atom.
    # 
    # \param atom The adjacent atom for which to return the connecting bond.
    # 
    # \return The bond connecting this atom and the argument atom. 
    # 
    # \throw Base.ItemNotFound if the argument atom is not connected to this atom.
    # 
    def getBondToAtom(atom: Atom) -> Bond: pass

    ##
    # \brief Returns the bond that connects this atom to the argument atom.
    # 
    # \param atom The adjacent atom for which to return the connecting bond.
    # 
    # \return The bond that connects this atom to the argument atom, or <tt>None</tt> if the argument atom is not connected.
    # 
    def findBondToAtom(atom: Atom) -> Bond: pass

    ##
    # \brief Returns the index of the atom in its parent molecule.
    # 
    # \return The zero-based index of the atom.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Assignment operator that replaces the current set of properties with the properties of <em>atom</em>.
    # 
    # \param atom The atom whose properties get copied.
    # 
    # \return \a self.
    # 
    def assign(atom: Atom) -> Atom: pass

    ##
    # \brief Returns the associated atom sequence.
    # \return The associated atom sequence.
    # 
    def getAtoms() -> AtomSequence: pass

    ##
    # \brief Returns the associated bond sequence.
    # \return The associated bond sequence.
    # 
    def getBonds() -> BondSequence: pass

    ##
    # \brief Returns the connected atom at index <em>idx</em>.
    # 
    # \param idx The index of the atom to return.
    # 
    # \return The connected atom at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumAtoms()).
    # 
    # \note The order of connected atoms corresponds to the order of connecting bonds.
    # 
    def getAtom(idx: int) -> Atom: pass

    ##
    # \brief Tells whether this atom and the specified atom are connected by a bond.
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

    def orderAtoms(func: BoolAtom2Functor) -> None: pass

    def getEntity(idx: int) -> Entity3D: pass

    def getNumEntities() -> int: pass

    ##
    # \brief Returns the incident bond at index <em>idx</em>.
    # 
    # \param idx The index of the incident bond to return.
    # 
    # \return The incident bond at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumBonds()).
    # 
    # \note The order of incident bonds corresponds to the order of the connected atoms.
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
    # \brief Returns the value of the property specified by <em>key</em>.
    # 
    # If an entry for the specified property exists, the stored value will be returned. Otherwise a Base.ItemNotFound exception will be thrown.
    # 
    # \param key The key of the property value to return.
    # 
    # 
    # \return The stored property value. 
    # 
    # \throw Base.ItemNotFound if an entry for the requested property value does not exist.
    # 
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief Tells whether or not a value has been assigned to the property specified by <em>key</em>.
    # 
    # \param key The key of the property.
    # 
    # \return <tt>True</tt> if a value has been assigned to the specified property, and <tt>False</tt> otherwise.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Tells whether the specified bond is part of the bond sequence.
    # 
    # \param bond The bond to look for.
    # 
    # \return <tt>True</tt> if <em>bond</em> is part of the sequence, and <tt>False</tt> otherwise.
    # 
    def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Tells whether the specified atom is part of the atom sequence.
    # 
    # \param atom The atom to look for.
    # 
    # \return <tt>True</tt> if <em>atom</em> is part of the sequence, and <tt>False</tt> otherwise.
    # 
    def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief Sets the value of the property specified by <em>key</em> to <em>val</em>.
    # 
    # If <em>val</em> is of type Base.Any and empty, i.e. the method Base.Any.isEmpty() returns <tt>True</tt>, and a property entry for <em>key</em> exists, the entry gets erased (equivalent to removeProperty() with <em>key</em> as argument).
    # 
    # \param key The key of the property value to assign or remove.
    # \param val The value of the property.
    # 
    def __setitem__(key: Base.LookupKey, val: Base.Any) -> None: pass

    ##
    # \brief Removes the entry for the property specified by <em>key</em>.
    # 
    # \param key The key of the property entry to remove.
    # 
    # \return <tt>True</tt> if an entry for <em>key</em> could be found and was removed, and <tt>False</tt> otherwise.
    # 
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the number of property entries.
    # 
    # \return The number of property entries.
    # 
    def __len__() -> int: pass

    molecule = property(getMolecule)

    index = property(getIndex)

    atoms = property(getAtoms)

    bonds = property(getBonds)
