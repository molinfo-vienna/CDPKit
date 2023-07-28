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
# \brief MaxCommonAtomSubstructureSearch.
# 
# \see [\ref MCASA]
# 
class MaxCommonAtomSubstructureSearch(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a <tt>MaxCommonAtomSubstructureSearch</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs and initializes a <tt>MaxCommonAtomSubstructureSearch</tt> instance for the specified query structure.
    # 
    # \param query A molecular graph that represents the query structure.
    # 
    def __init__(query: MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MaxCommonAtomSubstructureSearch instance this method is called upon.
    # 
    # Different Python \e %MaxCommonAtomSubstructureSearch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MaxCommonAtomSubstructureSearch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Searches for a common substructure between the query and the specified target molecular graph.
    # 
    # The method does not store any atom/bond mappings between query and target substructures - it just tells if a valid common substructure mapping solution involving at least getMinSubstructureSize() atoms could be found. If you need access to the atom/bond mappings, use findAllMappings() or findMaxBondMappings() instead.
    # 
    # \param target The molecular graph that has to be searched for a substructure in common with the query.
    # 
    # \return <tt>True</tt> if a common substructure of at least the minimum accepted size could be found, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findAllMappings() or findMaxMappings() will be discarded.
    # 
    def mappingExists(target: MolecularGraph) -> bool: pass

    ##
    # \brief Searches for all atom/bond mappings of query subgraphs to substructures of the specified target molecular graph with a maximum atom count.
    # 
    # The method will store all maximum-sized (in number of atoms) common substructure mapping solutions involving at least getMinSubstructureSize() atoms up to the maximum number of recorded mappings specified by setMaxNumMappings(). If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)), any duplicates of previously found mappings will be discarded.
    # 
    # \param target The molecular graph that has to be searched for all maximum-sized substructures in common with the query.
    # 
    # \return <tt>True</tt> if common substructures of at least the minimum accepted size were found, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findAllMappings() or findMaxBondMappings() will be discarded.
    # 
    def findAllMappings(target: MolecularGraph) -> bool: pass

    ##
    # \brief Searches for all atom/bond mappings of query subgraphs to substructures of the specified target molecular graph with a maximum atom and bond count.
    # 
    # The method will store all maximum-sized (both in number of atoms and bonds) common substructure mapping solutions involving at least getMinSubstructureSize() atoms up to the maximum number of recorded mappings specified by setMaxNumMappings(). If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)), any duplicates of previously found mappings will be discarded.
    # 
    # \param target The molecular graph that has to be searched for all maximum-sized substructures in common with the query.
    # 
    # \return <tt>True</tt> if common substructures of at least the minimum accepted size were found, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findAllMappings() or findMaxBondMappings() will be discarded.
    # 
    def findMaxBondMappings(target: MolecularGraph) -> bool: pass

    ##
    # \brief Returns the number of atom/bond mappings that were recorded in the last search for common substructures.
    # 
    # \return The number of atom/bond mappings that were recorded in the last search for common substructures. 
    # 
    # \see findAllMappings(), findMaxBondMappings()
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
    # The mapping of a query pattern subgraph to a substructure of the target molecular graph is considered to be unique if it differs from all previously found mappings by at least one atom or bond. If the <em>unique</em> argument is <tt>True</tt>, and a newly discovered mapping covers the same atoms and bonds of the target (including all permutations) as a mapping that was found earlier in the search process, it is considered as a duplicate and will be discarded.
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
    # In a call to findAllMappings() or findMaxBondMappings() the common substructure search will terminate as soon as the specified maximum number of stored atom/bond mappings has been reached. A previously set limit on the number of mappings can be disabled by providing zero for the value of <em>max_num_mappings</em>.
    # 
    # \param max_num_mappings The maximum number of atom/bond mappings to store.
    # 
    # \note By default, no limit is imposed on the number of stored mappings.
    # 
    def setMaxNumMappings(max_num_mappings: int) -> None: pass

    ##
    # \brief Returns the minimum accepted common substructure size.
    # 
    # \return The minimum accepted common substructure size in number of atoms. 
    # 
    # \see setMinSubstructureSize()
    # 
    def getMinSubstructureSize() -> int: pass

    ##
    # \brief Allows to specify the minimum accepted common substructure size.
    # 
    # Any found common substructures which cover less than <em>min_size</em> atoms are not accepted as a valid solution and will be discarded.
    # 
    # \param min_size The minimum accepted common substructure size in number of atoms.
    # 
    # \note By default, the minimum common substructure size is set to zero.
    # 
    def setMinSubstructureSize(min_size: int) -> None: pass

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

    minSubstructureSize = property(getMinSubstructureSize, setMinSubstructureSize)
