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
# \brief Bond.
# 
class Bond(AtomContainer, Base.PropertyContainer):

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
    # \brief Initializes the \e %Bond instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief 
    # \param arg1 
    # \param atom 
    # \return 
    #
    def getNeighbor(self: Bond, atom: Atom) -> Atom: pass

    ##
    # \brief Returns a reference to the start atom of the bond.
    # 
    # \return A reference to the start atom of the bond.
    # 
    def getBegin() -> Atom: pass

    ##
    # \brief Returns a reference to the end atom of the bond.
    # 
    # \return A reference to the end atom of the bond.
    # 
    def getEnd() -> Atom: pass

    ##
    # \brief Returns a reference to the parent molecule.
    # 
    # \return A reference to the parent molecule.
    # 
    def getMolecule() -> Molecule: pass

    ##
    # \brief Returns the index of the bond in its parent molecule.
    # 
    # \return The zero-based index of the bond.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Assignment operator that replaces the current set of properties with the properties of <em>bond</em>;.
    # 
    # \param bond The bond whose properties get copied.
    # 
    # \return \a self
    # 
    def assign(bond: Bond) -> Bond: pass

    ##
    # \brief 
    # \return 
    #
    def getAtoms() -> object: pass

    ##
    # \brief Returns a reference to the atom at index <em>idx</em>.
    # 
    # The index <em>0</em> specifies the start atom (see getBegin() const) and <em>1</em> the end atom of the bond (see getEnd() const).
    # 
    # \param idx The index of the atom to return.
    # 
    # \return A reference to the atom at index <em>idx</em>. 
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
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(atom: Atom) -> bool: pass

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

    begin = property(getBegin)

    end = property(getEnd)

    molecule = property(getMolecule)

    index = property(getIndex)

    atoms = property(getAtoms)
