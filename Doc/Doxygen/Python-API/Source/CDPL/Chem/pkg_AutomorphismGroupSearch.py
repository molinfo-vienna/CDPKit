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
    # \param atom_flags 
    # \param bond_flags 
    #
    def __init__(atom_flags: int = 12702, bond_flags: int = 30) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
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
    # \brief 
    # \param molgraph 
    # \return 
    #
    def findMappings(molgraph: MolecularGraph) -> bool: pass

    ##
    # \brief 
    #
    def stopSearch() -> None: pass

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
