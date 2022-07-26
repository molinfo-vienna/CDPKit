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
class CommonConnectedSubstructureSearch(Boost.Python.instance):

    ##
    # \brief Initializes the \e %CommonConnectedSubstructureSearch instance.
    # \param self The \e %CommonConnectedSubstructureSearch instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %CommonConnectedSubstructureSearch instance.
    # \param self The \e %CommonConnectedSubstructureSearch instance to initialize.
    # \param query 
    #
    def __init__(self: object, query: MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    #
    # Different Python \e %CommonConnectedSubstructureSearch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CommonConnectedSubstructureSearch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: CommonConnectedSubstructureSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param target 
    # \return 
    #
    def mappingExists(self: CommonConnectedSubstructureSearch, target: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param target 
    # \return 
    #
    def findAllMappings(self: CommonConnectedSubstructureSearch, target: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param target 
    # \return 
    #
    def findMaxMappings(self: CommonConnectedSubstructureSearch, target: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \return 
    #
    def getNumMappings(self: CommonConnectedSubstructureSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getMapping(self: CommonConnectedSubstructureSearch, idx: int) -> AtomBondMapping: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param unique 
    #
    def uniqueMappingsOnly(self: CommonConnectedSubstructureSearch, unique: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \return 
    #
    def uniqueMappingsOnly(self: CommonConnectedSubstructureSearch) -> bool: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \return 
    #
    def getMaxNumMappings(self: CommonConnectedSubstructureSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param max_num_mappings 
    #
    def setMaxNumMappings(self: CommonConnectedSubstructureSearch, max_num_mappings: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \return 
    #
    def getMinSubstructureSize(self: CommonConnectedSubstructureSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param min_size 
    #
    def setMinSubstructureSize(self: CommonConnectedSubstructureSearch, min_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param query 
    #
    def setQuery(self: CommonConnectedSubstructureSearch, query: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: CommonConnectedSubstructureSearch, idx: int) -> AtomBondMapping: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \return 
    #
    def __len__(self: CommonConnectedSubstructureSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param arg1 
    # \return 
    #
    def __nonzero__(arg1: CommonConnectedSubstructureSearch, self: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param self The \e %CommonConnectedSubstructureSearch instance this method is called upon.
    # \param arg1 
    # \return 
    #
    def __bool__(arg1: CommonConnectedSubstructureSearch, self: MolecularGraph) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

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

    ##
    # \brief 
    #
    minSubstructureSize = property(getMinSubstructureSize, setMinSubstructureSize)
