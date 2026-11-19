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
# \brief Abstract base class representing a chemical bond between two atoms (represented by Chem.Atom instances).
# 
# <tt>Bond</tt> combines the per-bond property storage inherited from Base.PropertyContainer with a fixed-size (always two atoms) Chem.AtomContainer interface that yields the bond's begin and end atoms. Concrete implementation (Chem.BasicBond) instances are created, owned and managed by a parent Chem.Molecule instance.
# 
class Bond(AtomContainer, Base.PropertyContainer):

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
    # \brief Contructs the \c Bond instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the connected neighbor of the argument atom.
    # 
    # \param atom The atom for which to return the connected neighbor atom.
    # 
    # \return The connected neighbor of the argument atom. 
    # 
    # \throw Base.ItemNotFound if the bond is not incident to the specified atom.
    # 
    def getNeighbor(atom: Atom) -> Atom: pass

    ##
    # \brief Returns the start atom of the bond.
    # 
    # Equivalent to calling <tt>getAtom(0)</tt>.
    # 
    # \return The start atom of the bond.
    # 
    def getBegin() -> Atom: pass

    ##
    # \brief Returns the end atom of the bond.
    # 
    # Equivalent to calling <tt>getAtom(1)</tt>.
    # 
    # \return The end atom of the bond.
    # 
    def getEnd() -> Atom: pass

    ##
    # \brief Returns the parent molecule.
    # 
    # \return The parent molecule.
    # 
    def getMolecule() -> Molecule: pass

    ##
    # \brief Returns the index of the bond in its parent molecule.
    # 
    # \return The zero-based index of the bond.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Assignment operator that replaces the current set of properties with the properties of <em>bond</em>.
    # 
    # \param bond The bond whose properties get copied.
    # 
    # \return \a self.
    # 
    def assign(bond: Bond) -> Bond: pass

    ##
    # \brief Returns the associated atom sequence.
    # \return The associated atom sequence.
    # 
    def getAtoms() -> AtomSequence: pass

    ##
    # \brief Returns the atom at index <em>idx</em>.
    # 
    # The index <em>0</em> specifies the start atom (see getBegin() const) and <em>1</em> the end atom of the bond (see getEnd() const).
    # 
    # \param idx The index of the atom to return.
    # 
    # \return The atom at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, 1].
    # 
    def getAtom(idx: int) -> Atom: pass

    ##
    # \brief Tells whether the bond is incident to the specified atom.
    # 
    # \param atom The atom to check.
    # 
    # \return <tt>True</tt> if the bond is incident to the specified atom, and <tt>False</tt> otherwise.
    # 
    def containsAtom(atom: Atom) -> bool: pass

    ##
    # \brief Returns the index of the specified atom.
    # 
    # If the specified atom is the start atom of the bond, the index <em>0</em> is returned. For the end atom of the bond, the value <em>1</em> will be returned.
    # 
    # \param atom The atom for which to return the index.
    # 
    # \return The zero-based index of the specified atom. 
    # 
    # \throw Base.ItemNotFound if the bond is not incident to the specified atom.
    # 
    def getAtomIndex(atom: Atom) -> int: pass

    ##
    # \brief Returns the number of atoms connected by the bond.
    # 
    # Since a bond connects exactly two atoms, the return value is always <em>2</em>.
    # 
    # \return The number of atoms connected by the bond (always <em>2</em>).
    # 
    def getNumAtoms() -> int: pass

    def orderAtoms(func: BoolAtom2Functor) -> None: pass

    def getEntity(idx: int) -> Entity3D: pass

    def getNumEntities() -> int: pass

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

    begin = property(getBegin)

    end = property(getEnd)

    molecule = property(getMolecule)

    index = property(getIndex)

    atoms = property(getAtoms)
