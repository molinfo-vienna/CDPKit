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
class AutomorphismGroupSearch(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AutomorphismGroupSearch instance.
    # \param self The \e %AutomorphismGroupSearch instance to initialize.
    # \param atom_flags 
    # \param bond_flags 
    #
    def __init__(self: object, atom_flags: int = 12702, bond_flags: int = 30) -> None: pass

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
    def getObjectID(self: AutomorphismGroupSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param flags 
    #
    def setAtomPropertyFlags(self: AutomorphismGroupSearch, flags: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def getAtomPropertyFlags(self: AutomorphismGroupSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param flags 
    #
    def setBondPropertyFlags(self: AutomorphismGroupSearch, flags: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def getBondPropertyFlags(self: AutomorphismGroupSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param include 
    #
    def includeIdentityMapping(self: AutomorphismGroupSearch, include: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def identityMappingIncluded(self: AutomorphismGroupSearch) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def findMappings(self: AutomorphismGroupSearch, molgraph: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    #
    def stopSearch(self: AutomorphismGroupSearch) -> None: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def getNumMappings(self: AutomorphismGroupSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getMapping(self: AutomorphismGroupSearch, idx: int) -> AtomBondMapping: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def getMaxNumMappings(self: AutomorphismGroupSearch) -> int: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param max_num_mappings 
    #
    def setMaxNumMappings(self: AutomorphismGroupSearch, max_num_mappings: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param func 
    #
    def setFoundMappingCallback(self: AutomorphismGroupSearch, func: BoolMolecularGraphAtomBondMappingFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def getFoundMappingCallback(self: AutomorphismGroupSearch) -> BoolMolecularGraphAtomBondMappingFunctor: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: AutomorphismGroupSearch, idx: int) -> AtomBondMapping: pass

    ##
    # \brief 
    # \param self The \e %AutomorphismGroupSearch instance this method is called upon.
    # \return 
    #
    def __len__(self: AutomorphismGroupSearch) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    atomPropertyFlags = property(getAtomPropertyFlags, setAtomPropertyFlags)

    ##
    # \brief 
    #
    bondPropertyFlags = property(getBondPropertyFlags, setBondPropertyFlags)

    ##
    # \brief FIXME!
    #
    incIdentityMapping = property(getIncIdentityMapping, setIncIdentityMapping)

    ##
    # \brief 
    #
    numMappings = property(getNumMappings)

    ##
    # \brief 
    #
    maxNumMappings = property(getMaxNumMappings, setMaxNumMappings)

    ##
    # \brief 
    #
    foundMappingCallback = property(getFoundMappingCallback, setFoundMappingCallback)
