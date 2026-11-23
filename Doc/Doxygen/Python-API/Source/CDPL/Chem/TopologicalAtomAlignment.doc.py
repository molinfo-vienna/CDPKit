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
# \brief Computes a topological alignment between two sets of arbitrary atoms by performing a maximum common subgraph search on a atom pair compatibility graph.
# 
# The compatibility graph is built from the two stored atom sets: a node (<em>i</em>, <em>j</em>) is created for every pair of matching atoms (checked by an optional atom match function that can be specified via method setEntityMatchFunction(); default behavior: always matching), and edges connect mutually compatible node pairs (decided by an optional atom pair match function that can be specified via setEntityPairMatchFunction(); default behavior: always compatible). Each call to nextAlignment() advances the underlying Bron-Kerbosch algorithm [\ref BKA] one maximal clique forward and reports the corresponding atom mapping between the first an second set. Via the method reset() a fresh search on the next nextAlignment() call can be enforced.
# 
class TopologicalAtomAlignment(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>TopologicalAtomAlignment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c TopologicalAtomAlignment instance \a alignment.
    # \param alignment The \c TopologicalAtomAlignment instance to copy.
    # 
    def __init__(alignment: TopologicalAtomAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c TopologicalAtomAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c TopologicalAtomAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function for restricting allowed atom mappings in the search for alignment solutions.
    # 
    # \param func The constraint check function.
    # 
    def setEntityMatchFunction(func: BoolAtom2Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for restricting allowed atom mappings.
    # 
    # \return The registered constraint check function.
    # 
    def getEntityMatchFunction() -> BoolAtom2Functor: pass

    ##
    # \brief Specifies a function for checking the compatibility of atom pairs in the search for alignment solutions.
    # 
    # \param func The constraint check function.
    # 
    # \note This function gets only called for pairs with already matching first and second atoms.
    # 
    def setEntityPairMatchFunction(func: BoolAtom4Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for checking the compatibility of atom pairs.
    # 
    # \return The registered constraint check function.
    # 
    def getEntityPairMatchFunction() -> BoolAtom4Functor: pass

    ##
    # \brief Adds an atom to the specified set.
    # 
    # \param entity The atom to add.
    # \param first_set If <tt>True</tt>, the atom is added to the first set, if <tt>False</tt> to the second one.
    # 
    # \note Adding the same atom instance more than once has no effect.
    # 
    def addEntity(entity: Atom, first_set: bool) -> None: pass

    ##
    # \brief Removes all atoms in the specified set.
    # 
    # \param first_set If <tt>True</tt>, the first set is cleared, if <tt>False</tt> the second one.
    # 
    def clearEntities(first_set: bool) -> None: pass

    ##
    # \brief Returns the number of atoms in the specified set.
    # 
    # \param first_set If <tt>True</tt>, the size of first set is returned, if <tt>False</tt> the size of the second one.
    # 
    def getNumEntities(first_set: bool) -> int: pass

    ##
    # \brief Returns a list containing the atoms in the specified set.
    # \param first_set If \c True, the atoms in the first set are returned and if \c False, the atoms in the second set.
    # \return A list containing the atoms in the specified set.
    # 
    def getEntities(first_set: bool) -> object: pass

    ##
    # \brief Returns the stored atom at index <em>idx</em> in the specified set.
    # 
    # \param idx The zero-based index of the atom instance to return.
    # \param first_set <tt>True</tt>, if the atom to return is stored in the first set. <tt>False</tt>, if stored in the second set.
    # 
    # \return The atom stored at index <em>idx</em> in the specified set. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumEntities()).
    # 
    def getEntity(idx: int, first_set: bool) -> Atom: pass

    ##
    # \brief Discards the current alignment search state so that the next call to nextAlignment() restarts the compatibility graph search from scratch.
    # 
    def reset() -> None: pass

    ##
    # \brief Searches for the next alignment solution and stores the corresponding mapping of the atoms in the first set to the atoms in the second set in the map provided as an argument.
    # 
    # \param mapping The map where the atom mapping of the found alignment solution has to be stored.
    # 
    # \return <tt>True</tt> if a new alignment solution could be found, and <tt>False</tt> otherwise.
    # 
    def nextAlignment(mapping: Util.STPairArray) -> bool: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c TopologicalAtomAlignment instance \a alignment.
    # \param alignment The \c TopologicalAtomAlignment instance to copy.
    # \return \a self.
    # 
    def assign(alignment: TopologicalAtomAlignment) -> TopologicalAtomAlignment: pass

    objectID = property(getObjectID)

    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)
