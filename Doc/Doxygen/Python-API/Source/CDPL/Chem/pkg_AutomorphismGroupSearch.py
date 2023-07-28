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
# \brief AutomorphismGroupSearch.
# 
class AutomorphismGroupSearch(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a <tt>AutomorphismGroupSearch</tt> instance.
    # 
    def __init__(atom_flags: int = 12702, bond_flags: int = 30) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # 
    # Different Python \e %AutomorphismGroupSearch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AutomorphismGroupSearch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param flags 
    #
    def setAtomPropertyFlags(flags: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomPropertyFlags() -> int: pass

    ##
    # \brief 
    # \param flags 
    #
    def setBondPropertyFlags(flags: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBondPropertyFlags() -> int: pass

    ##
    # \brief 
    # \param include 
    #
    def includeIdentityMapping(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def identityMappingIncluded() -> bool: pass

    ##
    # \brief Searches for the possible atom/bond mappings in the automorphism group of the given molecular graph.
    # 
    # The method will store all found mappings up to the maximum number of recorded mappings specified by setMaxNumMappings().
    # 
    # \param molgraph The molecular graph that has to be searched for automorphisms.
    # 
    # \return <tt>True</tt> if any mappings of the specified molecular graph have been found, and <tt>False</tt> otherwise. 
    # 
    # \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be discarded.
    # 
    def findMappings(molgraph: MolecularGraph) -> bool: pass

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
    # In a call to findMappings() the automorphism search will terminate as soon as the specified maximum number of stored atom/bond mappings has been reached. A previously set limit on the number of mappings can be disabled by providing zero for the value of <em>max_num_mappings</em>.
    # 
    # \param max_num_mappings The maximum number of atom/bond mappings to store.
    # 
    # \note By default, no limit is imposed on the number of stored mappings.
    # 
    def setMaxNumMappings(max_num_mappings: int) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setFoundMappingCallback(func: BoolMolecularGraphAtomBondMappingFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFoundMappingCallback() -> BoolMolecularGraphAtomBondMappingFunctor: pass

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

    objectID = property(getObjectID)

    atomPropertyFlags = property(getAtomPropertyFlags, setAtomPropertyFlags)

    bondPropertyFlags = property(getBondPropertyFlags, setBondPropertyFlags)

    ##
    # \brief FIXME!
    # \brief 
    #
    incIdentityMapping = property(getIncIdentityMapping, setIncIdentityMapping)

    numMappings = property(getNumMappings)

    maxNumMappings = property(getMaxNumMappings, setMaxNumMappings)

    foundMappingCallback = property(getFoundMappingCallback, setFoundMappingCallback)
