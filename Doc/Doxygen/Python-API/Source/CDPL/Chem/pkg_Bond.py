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
class Bond(AtomContainer, CDPL.Base.PropertyContainer):

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
        # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
        # \param self The \e %AtomSequence instance this method is called upon.
        # \param atom The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(self: AtomSequence, atom: Atom) -> bool: pass

    ##
    # \brief Initializes the \e %Bond instance.
    # \param self The \e %Bond instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param arg1 
    # \param atom 
    # \return 
    #
    def getNeighbor(arg1: Bond, self: Bond, atom: Atom) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getBegin(self: Bond) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getEnd(self: Bond) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getMolecule(self: Bond) -> Molecule: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getIndex(self: Bond) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Bond instance \a bond.
    # \param self The \e %Bond instance this method is called upon.
    # \param bond The \e %Bond instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Bond, bond: Bond) -> Bond: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getAtoms(self: AtomContainer) -> object: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getAtom(self: Bond, idx: int) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param atom 
    # \return 
    #
    def containsAtom(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def containsAtom(arg1: Bond, arg2: Atom) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param atom 
    # \return 
    #
    def getAtomIndex(self: AtomContainer, atom: Atom) -> int: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def getAtomIndex(arg1: Bond, arg2: Atom) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getNumAtoms(self: Bond) -> int: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param func 
    #
    def orderAtoms(self: Bond, func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getEntity(self: Bond, idx: int) -> Entity3D: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def getNumEntities(self: Bond) -> int: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: Bond, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: Bond, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: Bond, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: Bond, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    #
    def clearProperties(self: Bond) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: Bond, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param self The \e %Bond instance this method is called upon.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: AtomContainer, atom: Atom) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Bond instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Bond, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: Bond, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: Bond, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Bond instance this method is called upon.
    # \return 
    #
    def __len__(self: Bond) -> int: pass

    ##
    # \brief 
    #
    begin = property(getBegin)

    ##
    # \brief 
    #
    end = property(getEnd)

    ##
    # \brief 
    #
    molecule = property(getMolecule)

    ##
    # \brief 
    #
    index = property(getIndex)

    ##
    # \brief 
    #
    atoms = property(getAtoms)
