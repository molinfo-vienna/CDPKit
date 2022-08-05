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
class ReactionSubstructureSearch(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ReactionSubstructureSearch instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ReactionSubstructureSearch instance.
    # \param query 
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
    # \brief 
    # \param target 
    # \return 
    #
    def mappingExists(target: Reaction) -> bool: pass

    ##
    # \brief 
    # \param target 
    # \return 
    #
    def findMappings(target: Reaction) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getNumMappings() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getMapping(idx: int) -> AtomBondMapping: pass

    ##
    # \brief 
    # \param unique 
    #
    def uniqueMappingsOnly(unique: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def uniqueMappingsOnly() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumMappings() -> int: pass

    ##
    # \brief 
    # \param max_num_mappings 
    #
    def setMaxNumMappings(max_num_mappings: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEnabledReactionRoles() -> int: pass

    ##
    # \brief 
    # \param roles 
    #
    def setEnabledReactionRoles(roles: int) -> None: pass

    ##
    # \brief 
    # \param query 
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

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    enabledReactionRoles = property(getEnabledReactionRoles, setEnabledReactionRoles)

    ##
    # \brief 
    #
    numMappings = property(getNumMappings)

    ##
    # \brief FIXME!
    #
    uniqueMappings = property(getUniqueMappings, setUniqueMappings)

    ##
    # \brief 
    #
    maxNumMappings = property(getMaxNumMappings, setMaxNumMappings)
