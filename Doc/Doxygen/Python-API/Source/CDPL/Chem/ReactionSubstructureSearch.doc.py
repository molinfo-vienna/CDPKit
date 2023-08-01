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
# \brief ReactionSubstructureSearch.
# 
class ReactionSubstructureSearch(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a <tt>ReactionSubstructureSearch</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs and initializes a <tt>ReactionSubstructureSearch</tt> instance for the specified query reaction pattern.
    # 
    # \param query The query reaction.
    # 
    def __init__(query: Reaction) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %ReactionSubstructureSearch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ReactionSubstructureSearch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Tells whether the query reaction pattern matches the specified target reaction.
    # 
    # The method does not store any atom/bond mappings between the query and target reaction - it just tells if a complete mapping of the query is possible. If you need access to the atom/bond mappings, use findMappings() instead.
    # 
    # \param target The reaction that has to be searched for a match of the query reaction pattern.
    # 
    # \return <tt>True</tt> if the query pattern matches the target reaction, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be discarded.
    # 
    def mappingExists(target: Reaction) -> bool: pass

    ##
    # \brief Searches for all possible atom/bond between the query reaction pattern and the specified target reaction.
    # 
    # The method will store all found atom/bond mapping solutions up to the maximum number of recorded mappings specified by setMaxNumMappings(). If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)), any duplicates of previously found mappings will be discarded.
    # 
    # \param target The reaction that has to be searched for matches of the query reaction pattern.
    # 
    # \return <tt>True</tt> if the query pattern can be mapped to the specified target reaction, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be discarded.
    # 
    def findMappings(target: Reaction) -> bool: pass

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
    # A mapping of the query pattern to the target reaction is considered to be unique if it differs from all previously found mappings by at least one atom or bond. If the <em>unique</em> argument is <tt>True</tt> and a newly discovered mapping covers the same atoms and bonds of the target (including all permutations) as a mapping that was found earlier in the search process, it is considered as a duplicate and will be discarded.
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
    # In a call to findMappings() the reaction substructure search will terminate as soon as the specified maximum number of stored atom/bond mappings has been reached. A previously set limit on the number of mappings can be disabled by providing zero for the value of <em>max_num_mappings</em>.
    # 
    # \param max_num_mappings The maximum number of atom/bond mappings to store.
    # 
    # \note By default, no limit is imposed on the number of stored mappings.
    # 
    def setMaxNumMappings(max_num_mappings: int) -> None: pass

    ##
    # \brief Tells which reaction component roles are considered in the search for matching reaction substructures.
    # 
    # \return A bitmask specifying the considered reaction component roles. 
    # 
    # \see setEnabledReactionRoles(), Chem.ReactionRole
    # 
    def getEnabledReactionRoles() -> int: pass

    ##
    # \brief Allows the reaction role specific exclusion of query and target components from the search for matching reaction substructures.
    # 
    # The <em>roles</em> argument is a bitwise OR combination of the flags defined in namespace Chem.ReactionRole. When the flag for a particular reaction role is missing in the provided bitmask, then all reaction components with this role assignment (both in the query and target reaction) will be simply ignored during the reaction substructure search. This has the same effect as 'removing' the affected components from the query and target reaction prior to starting the search and adding them again afterwards.
    # 
    # \param roles A bitmask specifying the non-excluded reaction component roles.
    # 
    # \note By default, all types of reaction components are considered.
    # 
    def setEnabledReactionRoles(roles: int) -> None: pass

    ##
    # \brief Allows to specify a new query reaction pattern.
    # 
    # \param query Specifies the reaction pattern to search for.
    # 
    def setQuery(query: Reaction) -> None: pass

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
    def __nonzero__(self: Reaction) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __bool__(self: Reaction) -> bool: pass

    objectID = property(getObjectID)

    enabledReactionRoles = property(getEnabledReactionRoles, setEnabledReactionRoles)

    numMappings = property(getNumMappings)

    ##
    # \brief FIXME!
    # \brief 
    #
    uniqueMappings = property(getUniqueMappings, setUniqueMappings)

    maxNumMappings = property(getMaxNumMappings, setMaxNumMappings)
