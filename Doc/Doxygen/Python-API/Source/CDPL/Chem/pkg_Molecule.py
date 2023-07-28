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
# \brief Molecule.
# 
class Molecule(MolecularGraph):

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
        # \param self The \e %AtomSequence instance this method is called upon.
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
        # \param self The \e %BondSequence instance this method is called upon.
        # \param bond The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Initializes the \e %Molecule instance.
    # \param self The \e %Molecule instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Reserves memory for <em>num_atoms</em> atoms.
    # 
    # Allows implementors to speed up the creation of molecules with a known large number of atoms.
    # 
    # \param num_atoms The expected number of atoms for which memory shall be allocated in advance.
    # 
    def reserveMemoryForAtoms(num_atoms: int) -> None: pass

    ##
    # \brief Reserves memory for <em>num_bonds</em> bonds.
    # 
    # Allows implementors to speed up the creation of molecules with a known large number of bonds.
    # 
    # \param num_bonds The expected number of bonds for which memory shall be allocated in advance.
    # 
    def reserveMemoryForBonds(num_bonds: int) -> None: pass

    ##
    # \brief Removes all atoms and bonds and clears all properties of the molecule.
    # 
    def clear() -> None: pass

    ##
    # \brief Creates a new atom and adds it to the molecule.
    # 
    # Note that this method does not create any bonds - the returned atom is always unconnected.
    # 
    # \return A reference to the newly created atom.
    # 
    def addAtom() -> Atom: pass

    ##
    # \brief Creates a new or returns an already existing bond between the atoms specified by <em>atom1_idx</em> and <em>atom2_idx</em>.
    # 
    # If a bond between the specified atoms already exists, then the existing bond will be returned. If a bond does not yet exist, a new bond will be created. The atom specified by <em>atom1_idx</em> becomes the start atom and the atom specified by <em>atom2_idx</em> the end atom of the newly created bond.
    # 
    # \param atom1_idx The zero-based index of the first atom of the bond.
    # \param atom2_idx The zero-based index of the second atom of the bond.
    # 
    # \return A reference to the newly created or already existing bond between the specified atoms. 
    # 
    # \throw Base.IndexError if the number of atoms is zero or <em>atom1_idx</em> and/or <em>atom2_idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    def addBond(atom1_idx: int, atom2_idx: int) -> Bond: pass

    ##
    # \brief Removes the atom at the specified index.
    # 
    # If the specified atom is connected to any other atoms of the molecule, the connecting bonds will also be removed.
    # 
    # \param idx The index of the atom to remove.
    # 
    # \throw Base.IndexError if the number of atoms is zero or <em>idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    def removeAtom(idx: int) -> None: pass

    ##
    # \brief Removes the bond at the specified index.
    # 
    # \param idx The zero-based index of the bond to remove.
    # 
    # \throw Base.IndexError if the number of bonds is zero or <em>idx</em> is not in the range [0, getNumBonds() - 1].
    # 
    def removeBond(idx: int) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecule <em>mol</em>.
    # 
    # \param mol The molecule to copy.
    # 
    def copy(mol: Molecule) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms, bonds and properties to copy.
    # 
    def copy(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the molecule <em>mol</em>.
    # 
    # \param mol The molecule providing the atoms and bonds to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(mol: Molecule) -> None: pass

    ##
    # \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms and bonds to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Removes atoms and bonds referenced by the molecular graph <em>molgraph</em> that are part of this <tt>Molecule</tt> instance.
    # 
    # \param molgraph The Chem.MolecularGraph instance specifying the atoms and bonds to remove.
    # 
    # \note Does not affect any properties if <tt>this != &molgraph</tt>.
    # 
    def remove(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecule <em>mol</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param mol The molecule to copy.
    # 
    # \return \a self
    # 
    def assign(mol: Molecule) -> Molecule: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecular graph <em>molgraph</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms and bonds to copy.
    # 
    # \return \a self
    # 
    def assign(molgraph: MolecularGraph) -> Molecule: pass

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
    # \brief Returns a reference to the atom at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the atom to return.
    # 
    # \return A reference to the atom at the specified index. 
    # 
    # \throw Base.IndexError if the number of atoms is zero or <em>idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    def getAtom(idx: int) -> Atom: pass

    ##
    # \brief Tells whether the specified atom is part of this molecule.
    # 
    # \param atom The atom to look for.
    # 
    # \return <tt>True</tt> if <em>atom</em> is part of the molecule, and <tt>False</tt> otherwise.
    # 
    def containsAtom(atom: Atom) -> bool: pass

    ##
    # \brief Returns the index of the specified atom.
    # 
    # \param atom The atom for which to return the index.
    # 
    # \return The zero-based index of the specified atom. 
    # 
    # \throw Base.ItemNotFound if the specified atom is not part of the molecule.
    # 
    def getAtomIndex(atom: Atom) -> int: pass

    ##
    # \brief Returns the number of explicit atoms.
    # 
    # \return The number of explicit atoms.
    # 
    def getNumAtoms() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def orderAtoms(func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

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
    # \brief Returns a reference to the bond at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the bond to return.
    # 
    # \return A reference to the bond at the specified index. 
    # 
    # \throw Base.IndexError if the number of bonds is zero or <em>idx</em> is not in the range [0, getNumBonds() - 1].
    # 
    def getBond(idx: int) -> Bond: pass

    ##
    # \brief Tells whether the specified bond is part of this molecule.
    # 
    # \param bond The bond to look for.
    # 
    # \return <tt>True</tt> if <em>bond</em> is part of the molecule, and <tt>False</tt> otherwise.
    # 
    def containsBond(bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param func 
    #
    def orderBonds(func: BoolBond2Functor) -> None: pass

    ##
    # \brief Returns the index of the specified bond.
    # 
    # \param bond The bond for which to return the index.
    # 
    # \return The zero-based index of the specified bond. 
    # 
    # \throw Base.ItemNotFound if the specified bond is not part of the molecule.
    # 
    def getBondIndex(bond: Bond) -> int: pass

    ##
    # \brief Returns the number of explicit bonds.
    # 
    # \return The number of explicit bonds.
    # 
    def getNumBonds() -> int: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __getstate__() -> tuple: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param self The \e %Molecule instance acting as in-place addend.
    # \param mol Specifies the second addend.
    # \return The updated \e %Molecule instance \a self.
    # 
    def __iadd__(mol: Molecule) -> Molecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param self The \e %Molecule instance acting as in-place addend.
    # \param molgraph Specifies the second addend.
    # \return The updated \e %Molecule instance \a self.
    # 
    def __iadd__(molgraph: MolecularGraph) -> Molecule: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= molgraph</tt>.
    # \param self The \e %Molecule instance acting as in-place minuend.
    # \param molgraph Specifies the subtrahend.
    # \return The updated \e %Molecule instance \a self.
    # 
    def __isub__(molgraph: MolecularGraph) -> Molecule: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param self The \e %Molecule instance this method is called upon.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
    # \param self The \e %Molecule instance this method is called upon.
    # \param bond The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Molecule instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: CDPL.Base.LookupKey) -> CDPL.Base.Any: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: CDPL.Base.LookupKey, value: CDPL.Base.Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    atoms = property(getAtoms)

    bonds = property(getBonds)
