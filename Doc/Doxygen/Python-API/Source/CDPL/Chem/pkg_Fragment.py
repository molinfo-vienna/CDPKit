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
    # \brief Initializes the \e %Fragment instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Fragment instance.
    # \param frag 
    #
    def __init__(frag: Fragment) -> None: pass

    ##
    # \brief Initializes the \e %Fragment instance.
    # \param molgraph 
    #
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Fragment instance \a frag.
    # \param frag The \e %Fragment instance to copy.
    # \return \a self
    #
    def assign(frag: Fragment) -> Fragment: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MolecularGraph instance \a molgraph.
    # \param molgraph The \e %MolecularGraph instance to copy.
    # \return \a self
    #
    def assign(molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def addAtom(atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeAtom(idx: int) -> None: pass

    ##
    # \brief 
    # \param atom 
    # \return 
    #
    def removeAtom(atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param bond 
    # \return 
    #
    def addBond(bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeBond(idx: int) -> None: pass

    ##
    # \brief 
    # \param bond 
    # \return 
    #
    def removeBond(bond: Bond) -> bool: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param frag 
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

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param molgraph Specifies the second addend.
    # \return The updated \e %Fragment instance \a self.
    #
    def __iadd__(molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= molgraph</tt>.
    # \param molgraph Specifies the subtrahend.
    # \return The updated \e %Fragment instance \a self.
    #
    def __isub__(molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief 
    #
    atoms = property(getAtoms)

    ##
    # \brief 
    #
    bonds = property(getBonds)
