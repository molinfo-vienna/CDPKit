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
# \brief Fragment.
# 
class Fragment(MolecularGraph):

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
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

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
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
        # \param bond The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Constructs an empty <tt>Fragment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>Fragment</tt> instance <em>frag</em>.
    # 
    # \param frag The other <tt>Fragment</tt> instance to copy.
    # 
    def __init__(frag: Fragment) -> None: pass

    ##
    # \brief Constructs a <tt>Fragment</tt> instance storing the atoms, bonds and properties of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms, bonds and properties to store.
    # 
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by the atoms, bonds and properties of the fragment <em>frag</em>.
    # 
    # \param frag The fragment to copy.
    # 
    # \return \a self
    # 
    def assign(frag: Fragment) -> Fragment: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by the atoms, bonds and properties of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms, bonds and properties to copy.
    # 
    # \return \a self
    # 
    def assign(molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief Extends the fragment by the specified atom.
    # 
    # \param atom The atom to add.
    # 
    # \return <tt>True</tt> if the atom was not already a part of the fragment, and <tt>False</tt> otherwise.
    # 
    def addAtom(atom: Atom) -> bool: pass

    ##
    # \brief Removes the atom at the specified index.
    # 
    # If the specified atom is connected to any other atoms of the fragment, the connecting bonds will also be removed.
    # 
    # \param idx The zero-based index of the atom to remove.
    # 
    # \throw Base.IndexError if the number of atoms is zero or <em>idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    def removeAtom(idx: int) -> None: pass

    ##
    # \brief Removes the specified atom.
    # 
    # If the specified atom is connected to any other atoms of the fragment, the connecting bonds will also be removed.
    # 
    # \param atom The atom to remove.
    # 
    # \return <tt>True</tt> if the atom was part of the fragment and has been removed, and <tt>False</tt> otherwise.
    # 
    def removeAtom(atom: Atom) -> bool: pass

    ##
    # \brief Extends the fragment by the specified bond.
    # 
    # If the atoms of the bond are not already part of the fragment, they will be added automatically.
    # 
    # \param bond The bond to add.
    # 
    # \return <tt>True</tt> if the bond was not already a part of the fragment, and <tt>False</tt> otherwise.
    # 
    def addBond(bond: Bond) -> bool: pass

    ##
    # \brief Removes the bond at the specified index.
    # 
    # \param idx The zero-based index of the bond to remove.
    # 
    # \throw Base.IndexError if the number of bonds is zero or <em>idx</em> is not in the range [0, getNumBonds() - 1].
    # 
    def removeBond(idx: int) -> None: pass

    ##
    # \brief Removes the specified bond.
    # 
    # \param bond The bond to remove.
    # 
    # \return <tt>True</tt> if the bond was removed, and <tt>False</tt> otherwise.
    # 
    def removeBond(bond: Bond) -> bool: pass

    ##
    # \brief Removes all atoms and bonds.
    # 
    def clear() -> None: pass

    ##
    # \brief Exchanges the atoms, bonds and properties of this fragment with the atoms, bonds and properties of the fragment <em>frag</em>.
    # 
    # \param frag The fragment the atoms, bonds and properties get exchanged with.
    # 
    def swap(frag: Fragment) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtoms() -> AtomSequence: pass

    ##
    # \brief 
    # \return 
    #
    def getBonds() -> BondSequence: pass

    ##
    # \brief 
    # \param num_atoms 
    #
    def reserveMemoryForAtoms(num_atoms: int) -> None: pass

    ##
    # \brief 
    # \param num_bonds 
    #
    def reserveMemoryForBonds(num_bonds: int) -> None: pass

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

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param molgraph Specifies the second addend.
    # \return The updated \c %Fragment instance \a self.
    # 
    def __iadd__(molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= molgraph</tt>.
    # \param molgraph Specifies the subtrahend.
    # \return The updated \c %Fragment instance \a self.
    # 
    def __isub__(molgraph: MolecularGraph) -> Fragment: pass

    atoms = property(getAtoms)

    bonds = property(getBonds)
