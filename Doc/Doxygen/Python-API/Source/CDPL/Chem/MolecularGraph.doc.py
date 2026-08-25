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
# \brief Abstract base class for data structures that represent chemical structures as molecular graphs.
# 
# Vertices (= atoms) of the molecular graph are represented by Chem.Atom instances and edges (= bonds) by Chem.Bond instances. Read-only access to the Chem.Atom and Chem.Bond objects is enabled by corresponding methods inherited from Chem.AtomContainer and Chem.BondContainer, respectively. Molecular graph properties can be stored/retrieved via methods provided by the Base.PropertyContainer base class. Deep copies of the molecular graph are created by the pure virtual clone() method which needs to be implemented by concrete subclasses (e.g. Chem.BasicMolecule, Chem.Fragment) of <tt>MolecularGraph</tt>.
# 
class MolecularGraph(AtomContainer, BondContainer, Base.PropertyContainer):

    ##
    # \brief 
    #
    class AtomSequence(Boost.Python.instance):

        def __len__() -> int: pass

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

        def __len__() -> int: pass

        def __getitem__(idx: int) -> Bond: pass

        ##
        # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
        # \param bond The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Initializes the \c %MolecularGraph instance.
    # 
    def __init__() -> None: pass

    def getAtoms() -> AtomSequence: pass

    def getBonds() -> BondSequence: pass

    ##
    # \brief Creates a deep copy of the molecular graph.
    # 
    # \return A smart reference to the copy of the molecular graph.
    # 
    def clone() -> MolecularGraph: pass

    def getAtom(idx: int) -> Atom: pass

    def containsAtom(atom: Atom) -> bool: pass

    def getAtomIndex(atom: Atom) -> int: pass

    def getNumAtoms() -> int: pass

    def orderAtoms(func: BoolAtom2Functor) -> None: pass

    def getEntity(idx: int) -> Entity3D: pass

    def getNumEntities() -> int: pass

    def getBond(idx: int) -> Bond: pass

    def containsBond(bond: Bond) -> bool: pass

    def orderBonds(func: BoolBond2Functor) -> None: pass

    def getBondIndex(bond: Bond) -> int: pass

    def getNumBonds() -> int: pass

    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
    # \param bond The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(atom: Atom) -> bool: pass

    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    def __delitem__(key: Base.LookupKey) -> bool: pass

    def __len__() -> int: pass

    atoms = property(getAtoms)

    bonds = property(getBonds)
