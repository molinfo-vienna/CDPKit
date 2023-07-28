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
# \brief SubstructureSearch.
# 
# \see [\ref VFLIB2]
# 
class SubstructureSearch(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a <tt>SubstructureSearch</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs and initializes a <tt>SubstructureSearch</tt> instance for the specified query structure.
    # 
    # \param query A molecular graph that represents the query structure.
    # 
    def __init__(query: MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SubstructureSearch instance this method is called upon.
    # 
    # Different Python \e %SubstructureSearch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SubstructureSearch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setAtomMatchExpressionFunction(func: AtomMatchExpressionPtrAtomFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setBondMatchExpressionFunction(func: BondMatchExpressionPtrBondFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setMolecularGraphMatchExpressionFunction(func: MolGraphMatchExpressionPtrMolGraphFunctor) -> None: pass

    ##
    # \brief Tells whether the query structure matches a substructure of the specified target molecular graph.
    # 
    # The method does not store any atom/bond mappings between the query and target structure - it just tells if a complete mapping of the query is possible. If you need access to the atom/bond mappings, use findMappings() instead.
    # 
    # \param target The molecular graph that has to be searched for a match of the query structure.
    # 
    # \return <tt>True</tt> if the query matches a substructure of the target molecular graph, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be discarded.
    # 
    def mappingExists(target: MolecularGraph) -> bool: pass

    ##
    # \brief Searches for all possible atom/bond mappings of the query structure to substructures of the specified target molecular graph.
    # 
    # The method will store all found subgraph mapping solutions up to the maximum number of recorded mappings specified by setMaxNumMappings(). If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)), any duplicates of previously found mappings will be discarded.
    # 
    # \param target The molecular graph that has to be searched for matches of the query structure.
    # 
    # \return <tt>True</tt> if the query matches at least one substructure of the specified target molecular graph, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be discarded.
    # 
    def findMappings(target: MolecularGraph) -> bool: pass

    ##
    # \brief 
    #
    def stopSearch() -> None: pass

    ##
    # \brief Returns the number of atom/bond mappings that were recorded in the last call to findMappings().
    # 
    # \return The number of atom/bond mappings that were recorded in the last call to findMappings().
    # 
    def getNumMappings() -> int: pass

    ##
    # \brief Returns a reference to the stored atom/bond mapping object at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the atom/bond mapping object to return.
    # 
    # \return A reference to the atom/bond mapping object at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if no mappings are available or <em>idx</em> is not in the range [0, getNumMappings() - 1].
    # 
    def getMapping(idx: int) -> AtomBondMapping: pass

    ##
    # \brief Allows to specify whether or not to store only unique atom/bond mappings.
    # 
    # A mapping of the query pattern to a substructure of the target molecular graph is considered to be unique if it differs from all previously found mappings by at least one atom or bond. If the <em>unique</em> argument is <tt>True</tt>, and a newly discovered mapping covers the same atoms and bonds of the target (including all permutations) as a mapping that was found earlier in the search process, it is considered as a duplicate and will be discarded.
    # 
    # \param unique If <tt>True</tt>, only unique mappings will be stored, and all found mappings otherwise.
    # 
    # \note By default, duplicate mappings are not discarded.
    # 
    def uniqueMappingsOnly(unique: bool) -> None: pass

    ##
    # \brief Tells whether duplicate atom/bond mappings are discarded.
    # 
    # \return <tt>True</tt> if duplicate mappings are discarded, and <tt>False</tt> otherwise. 
    # 
    # \see uniqueMappingsOnly(bool unique)
    # 
    def uniqueMappingsOnly() -> bool: pass

    ##
    # \brief Returns the specified limit on the number of stored atom/bond mappings.
    # 
    # \return The specified maximum number of stored atom/bond mappings. 
    # 
    # \see setMaxNumMappings(), findMappings()
    # 
    def getMaxNumMappings() -> int: pass

    ##
    # \brief Allows to specify a limit on the number of stored atom/bond mappings.
    # 
    # In a call to findMappings() the substructure search will terminate as soon as the specified maximum number of stored atom/bond mappings has been reached. A previously set limit on the number of mappings can be disabled by providing zero for the value of <em>max_num_mappings</em>.
    # 
    # \param max_num_mappings The maximum number of atom/bond mappings to store.
    # 
    # \note By default, no limit is imposed on the number of stored mappings.
    # 
    def setMaxNumMappings(max_num_mappings: int) -> None: pass

    ##
    # \brief Clears all previously defined query to target atom mapping constraints.
    # 
    # \see addAtomMappingConstraint()
    # 
    def clearAtomMappingConstraints() -> None: pass

    ##
    # \brief Adds a constraint on the allowed mappings between query and target structure atoms.
    # 
    # By default, an atom of the query structure is free to match any suitable target structure atom. When this method gets called for a particular query/target atom pair (specified by <em>query_atom_idx</em> and <em>target_atom_idx</em>), future substructure searches will find only those subgraph mapping solutions (if any) where the given query atom maps to the specified target structure atom. Multiple calls to addMappingConstraint() for the same query atom have an additive effect and allow to restrict the valid query atom mappings not only to a single but also a larger set of target structure atoms.
    # 
    # \param query_atom_idx The index of the query structure atom.
    # \param target_atom_idx The index of the target structure atom that has to be matched by the query atom.
    # 
    def addAtomMappingConstraint(query_atom_idx: int, target_atom_idx: int) -> None: pass

    ##
    # \brief Clears all previously defined query to target bond mapping constraints.
    # 
    # \see addBondMappingConstraint()
    # 
    def clearBondMappingConstraints() -> None: pass

    ##
    # \brief Adds a constraint on the allowed mappings between query and target structure bonds.
    # 
    # By default, a bond of the query structure is free to match any suitable target structure bond. When this method gets called for a particular query/target bond pair (specified by <em>query_bond_idx</em> and <em>target_bond_idx</em>), future substructure searches will find only those subgraph mapping solutions (if any) where the given query bond maps to the specified target structure bond. Multiple calls to addMappingConstraint() for the same query bond have an additive effect and allow to restrict the valid query bond mappings not only to a single but also a larger set of target structure bonds.
    # 
    # \param query_bond_idx The index of the query structure bond.
    # \param target_bond_idx The index of the target structure bond that has to be matched by the query bond.
    # 
    def addBondMappingConstraint(query_bond_idx: int, target_bond_idx: int) -> None: pass

    ##
    # \brief Allows to specify a new query structure.
    # 
    # \param query A molecular graph that represents the query structure.
    # 
    def setQuery(query: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> AtomBondMapping: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __nonzero__(self: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __bool__(self: MolecularGraph) -> bool: pass

    objectID = property(getObjectID)

    numMappings = property(getNumMappings)

    ##
    # \brief FIXME!
    # \brief 
    #
    uniqueMappings = property(getUniqueMappings, setUniqueMappings)

    maxNumMappings = property(getMaxNumMappings, setMaxNumMappings)
