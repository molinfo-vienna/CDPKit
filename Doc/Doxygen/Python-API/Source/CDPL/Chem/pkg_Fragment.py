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
class Fragment(MolecularGraph):

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
    # \brief Initializes the \e %Fragment instance.
    # \param self The \e %Fragment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Fragment instance.
    # \param self The \e %Fragment instance to initialize.
    # \param frag 
    #
    def __init__(self: object, frag: Fragment) -> None: pass

    ##
    # \brief Initializes the \e %Fragment instance.
    # \param self The \e %Fragment instance to initialize.
    # \param molgraph 
    #
    def __init__(self: object, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Fragment instance \a frag.
    # \param self The \e %Fragment instance this method is called upon.
    # \param frag The \e %Fragment instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Fragment, frag: Fragment) -> Fragment: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Fragment instance \a molgraph.
    # \param self The \e %Fragment instance this method is called upon.
    # \param molgraph The \e %Fragment instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Fragment, molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param atom 
    # \return 
    #
    def addAtom(self: Fragment, atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param idx 
    #
    def removeAtom(self: Fragment, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param atom 
    # \return 
    #
    def removeAtom(self: Fragment, atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param bond 
    # \return 
    #
    def addBond(self: Fragment, bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param idx 
    #
    def removeBond(self: Fragment, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param bond 
    # \return 
    #
    def removeBond(self: Fragment, bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    #
    def clear(self: Fragment) -> None: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param frag 
    #
    def swap(self: Fragment, frag: Fragment) -> None: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \return 
    #
    def getAtoms(self: Fragment) -> AtomSequence: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \return 
    #
    def getBonds(self: Fragment) -> BondSequence: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param num_atoms 
    #
    def reserveMemoryForAtoms(self: Fragment, num_atoms: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param num_bonds 
    #
    def reserveMemoryForBonds(self: Fragment, num_bonds: int) -> None: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param self The \e %Fragment instance this method is called upon.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
    # \param self The \e %Fragment instance this method is called upon.
    # \param bond The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: BondContainer, bond: Bond) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Fragment instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Fragment, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: Fragment, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: Fragment, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Fragment instance this method is called upon.
    # \return 
    #
    def __len__(self: Fragment) -> int: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param self The \e %Fragment instance acting as in-place addend.
    # \param molgraph Specifies the second addend.
    # \return The updated \e %Fragment instance \a self.
    #
    def __iadd__(self: Fragment, molgraph: MolecularGraph) -> Fragment: pass

    ##
    # \brief 
    #
    atoms = property(getAtoms)

    ##
    # \brief 
    #
    bonds = property(getBonds)
