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
# \brief Computes a topological alignment between two sets of arbitrary entities by performing a maximum common subgraph search on a entity pair compatibility graph.
# 
# The compatibility graph is built from the two stored entity sets: a node (<em>i</em>, <em>j</em>) is created for every pair of matching entities (checked by an optional entity match function that can be specified via method setEntityMatchFunction(); default behavior: always matching), and edges connect mutually compatible node pairs (decided by an optional entity pair match function that can be specified via setEntityPairMatchFunction(); default behavior: always compatible). Each call to nextAlignment() advances the underlying Bron-Kerbosch algorithm [\ref BKA] one maximal clique forward and reports the corresponding entity mapping between the first an second set. Via the method reset() a fresh search on the next nextAlignment() call can be enforced.
# 
class TopologicalEntity3DAlignment(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>TopologicalEntity3DAlignment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c TopologicalEntity3DAlignment instance \a alignment.
    # \param alignment The \c TopologicalEntity3DAlignment instance to copy.
    # 
    def __init__(alignment: TopologicalEntity3DAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c TopologicalEntity3DAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c TopologicalEntity3DAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function for restricting allowed entity mappings in the search for alignment solutions.
    # 
    # \param func The constraint check function.
    # 
    def setEntityMatchFunction(func: BoolEntity3D2Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for restricting allowed entity mappings.
    # 
    # \return The registered constraint check function.
    # 
    def getEntityMatchFunction() -> BoolEntity3D2Functor: pass

    ##
    # \brief Specifies a function for checking the compatibility of entity pairs in the search for alignment solutions.
    # 
    # \param func The constraint check function.
    # 
    # \note This function gets only called for pairs with already matching first and second entities.
    # 
    def setEntityPairMatchFunction(func: BoolEntity3D4Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for checking the compatibility of entity pairs.
    # 
    # \return The registered constraint check function.
    # 
    def getEntityPairMatchFunction() -> BoolEntity3D4Functor: pass

    ##
    # \brief Adds an entity to the specified set.
    # 
    # \param entity The entity to add.
    # \param first_set If <tt>True</tt>, the entity is added to the first set, if <tt>False</tt> to the second one.
    # 
    # \note Adding the same entity instance more than once has no effect.
    # 
    def addEntity(entity: Entity3D, first_set: bool) -> None: pass

    ##
    # \brief Removes all entities in the specified set.
    # 
    # \param first_set If <tt>True</tt>, the first set is cleared, if <tt>False</tt> the second one.
    # 
    def clearEntities(first_set: bool) -> None: pass

    ##
    # \brief Returns the number of entities in the specified set.
    # 
    # \param first_set If <tt>True</tt>, the size of first set is returned, if <tt>False</tt> the size of the second one.
    # 
    def getNumEntities(first_set: bool) -> int: pass

    ##
    # \brief Returns a list containing the entities in the specified set.
    # \param first_set If \c True, the entities in the first set are returned and if \c False, the entities in the second set.
    # \return A list containing the entities in the specified set.
    # 
    def getEntities(first_set: bool) -> object: pass

    ##
    # \brief Returns the stored entity at index <em>idx</em> in the specified set.
    # 
    # \param idx The zero-based index of the entity instance to return.
    # \param first_set <tt>True</tt>, if the entity to return is stored in the first set. <tt>False</tt>, if stored in the second set.
    # 
    # \return The entity stored at index <em>idx</em> in the specified set. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumEntities()).
    # 
    def getEntity(idx: int, first_set: bool) -> Entity3D: pass

    ##
    # \brief Discards the current alignment search state so that the next call to nextAlignment() restarts the compatibility graph search from scratch.
    # 
    def reset() -> None: pass

    ##
    # \brief Searches for the next alignment solution and stores the corresponding mapping of the entities in the first set to the entities in the second set in the map provided as an argument.
    # 
    # \param mapping The map where the entity mapping of the found alignment solution has to be stored.
    # 
    # \return <tt>True</tt> if a new alignment solution could be found, and <tt>False</tt> otherwise.
    # 
    def nextAlignment(mapping: Util.STPairArray) -> bool: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c TopologicalEntity3DAlignment instance \a alignment.
    # \param alignment The \c TopologicalEntity3DAlignment instance to copy.
    # \return \a self.
    # 
    def assign(alignment: TopologicalEntity3DAlignment) -> TopologicalEntity3DAlignment: pass

    objectID = property(getObjectID)

    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)
