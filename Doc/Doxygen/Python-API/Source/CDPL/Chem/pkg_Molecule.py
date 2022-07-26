#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
class Molecule(MolecularGraph):

    ##
    # \brief 
    #
    class AtomSequence(Boost.Python.instance):

        ##
        # \brief 
        # \param self The \e %AtomSequence instance this method is called upon.
        # \return 
        #
        def __len__(self: AtomSequence) -> int: pass

        ##
        # \brief 
        # \param self The \e %AtomSequence instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: AtomSequence, idx: int) -> Atom: pass

        ##
        # \brief 
        # \param self The \e %AtomSequence instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: AtomSequence, idx: int) -> None: pass

        ##
        # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
        # \param self The \e %AtomSequence instance this method is called upon.
        # \param atom The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(self: AtomSequence, atom: Atom) -> bool: pass

    ##
    # \brief 
    #
    class BondSequence(Boost.Python.instance):

        ##
        # \brief 
        # \param self The \e %BondSequence instance this method is called upon.
        # \return 
        #
        def __len__(self: BondSequence) -> int: pass

        ##
        # \brief 
        # \param self The \e %BondSequence instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: BondSequence, idx: int) -> Bond: pass

        ##
        # \brief 
        # \param self The \e %BondSequence instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: BondSequence, idx: int) -> None: pass

        ##
        # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
        # \param self The \e %BondSequence instance this method is called upon.
        # \param bond The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(self: BondSequence, bond: Bond) -> bool: pass

    ##
    # \brief Initializes the \e %Molecule instance.
    # \param self The \e %Molecule instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param num_atoms 
    #
    def reserveMemoryForAtoms(self: Molecule, num_atoms: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param num_bonds 
    #
    def reserveMemoryForBonds(self: Molecule, num_bonds: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    #
    def clear(self: Molecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def addAtom(self: Molecule) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param atom1_idx 
    # \param atom2_idx 
    # \return 
    #
    def addBond(self: Molecule, atom1_idx: int, atom2_idx: int) -> Bond: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param idx 
    #
    def removeAtom(self: Molecule, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param idx 
    #
    def removeBond(self: Molecule, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param mol 
    #
    def copy(self: Molecule, mol: Molecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param molgraph 
    #
    def copy(self: Molecule, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param mol 
    #
    def append(self: Molecule, mol: Molecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param molgraph 
    #
    def append(self: Molecule, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Molecule instance \a mol.
    # \param self The \e %Molecule instance this method is called upon.
    # \param mol The \e %Molecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Molecule, mol: Molecule) -> Molecule: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Molecule instance \a molgraph.
    # \param self The \e %Molecule instance this method is called upon.
    # \param molgraph The \e %Molecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Molecule, molgraph: MolecularGraph) -> Molecule: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def getAtoms(self: Molecule) -> AtomSequence: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def getBonds(self: Molecule) -> BondSequence: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getAtom(self: Molecule, idx: int) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param atom 
    # \return 
    #
    def containsAtom(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def containsAtom(arg1: Molecule, arg2: Atom) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param atom 
    # \return 
    #
    def getAtomIndex(self: AtomContainer, atom: Atom) -> int: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def getAtomIndex(arg1: Molecule, arg2: Atom) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def getNumAtoms(self: Molecule) -> int: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param func 
    #
    def orderAtoms(self: Molecule, func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getEntity(self: Molecule, idx: int) -> Entity3D: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def getNumEntities(self: Molecule) -> int: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getBond(self: Molecule, idx: int) -> Bond: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param bond 
    # \return 
    #
    def containsBond(self: BondContainer, bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def containsBond(arg1: Molecule, arg2: Bond) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param func 
    #
    def orderBonds(self: Molecule, func: BoolBond2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param bond 
    # \return 
    #
    def getBondIndex(self: BondContainer, bond: Bond) -> int: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def getBondIndex(arg1: Molecule, arg2: Bond) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def getNumBonds(self: Molecule) -> int: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: Molecule, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: Molecule, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: Molecule, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: Molecule, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    #
    def clearProperties(self: Molecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: Molecule, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param self The \e %Molecule instance acting as in-place addend.
    # \param mol Specifies the second addend.
    # \return The updated \e %Molecule instance \a self.
    #
    def __iadd__(self: Molecule, mol: Molecule) -> Molecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param self The \e %Molecule instance acting as in-place addend.
    # \param molgraph Specifies the second addend.
    # \return The updated \e %Molecule instance \a self.
    #
    def __iadd__(self: Molecule, molgraph: MolecularGraph) -> Molecule: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param self The \e %Molecule instance this method is called upon.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
    # \param self The \e %Molecule instance this method is called upon.
    # \param bond The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: BondContainer, bond: Bond) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Molecule instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Molecule, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: Molecule, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: Molecule, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Molecule instance this method is called upon.
    # \return 
    #
    def __len__(self: Molecule) -> int: pass

    ##
    # \brief 
    #
    atoms = property(getAtoms)

    ##
    # \brief 
    #
    bonds = property(getBonds)
