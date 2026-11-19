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
# Vertices (= atoms) of the molecular graph are represented by Chem.Atom instances and edges (= bonds) by Chem.Bond instances. Read-only access to the Chem.Atom and Chem.Bond instances is enabled by corresponding methods inherited from Chem.AtomContainer and Chem.BondContainer, respectively. Molecular graph properties can be stored/retrieved via methods provided by the Base.PropertyContainer base class. Deep copies of the molecular graph are created by the pure virtual clone() method which needs to be implemented by concrete subclasses (e.g. Chem.BasicMolecule, Chem.Fragment) of <tt>MolecularGraph</tt>.
# 
class MolecularGraph(AtomContainer, BondContainer, Base.PropertyContainer):

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
    # \brief Contructs the \c MolecularGraph instance.
    # 
    def __init__() -> None: pass

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
    # \brief Creates a deep copy of the molecular graph.
    # 
    # \return The copy of the molecular graph.
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

    atoms = property(getAtoms)

    bonds = property(getBonds)
