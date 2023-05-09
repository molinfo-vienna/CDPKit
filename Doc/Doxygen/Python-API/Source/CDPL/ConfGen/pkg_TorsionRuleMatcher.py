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
# \brief 
#
class TorsionRuleMatcher(Boost.Python.instance):

    ##
    # \brief Initializes the \e %TorsionRuleMatcher instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %TorsionRuleMatcher instance.
    # \param lib 
    #
    def __init__(lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param unique 
    #
    def findUniqueMappingsOnly(unique: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def findUniqueMappingsOnly() -> bool: pass

    ##
    # \brief 
    # \param all 
    #
    def findAllRuleMappings(all: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def findAllRuleMappings() -> bool: pass

    ##
    # \brief 
    # \param stop 
    #
    def stopAtFirstMatchingRule(stop: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def stopAtFirstMatchingRule() -> bool: pass

    ##
    # \brief 
    # \param lib 
    #
    def setTorsionLibrary(lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionLibrary() -> TorsionLibrary: pass

    ##
    # \brief 
    # \return 
    #
    def getNumMatches() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getMatch(idx: int) -> TorsionRuleMatch: pass

    ##
    # \brief 
    # \param bond 
    # \param molgraph 
    # \param append 
    # \return 
    #
    def findMatches(bond: CDPL.Chem.Bond, molgraph: CDPL.Chem.MolecularGraph, append: bool = False) -> bool: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %TorsionRuleMatcher instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TorsionRuleMatcher instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> TorsionRuleMatch: pass

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
    numMatches = property(getNumMatches)

    ##
    # \brief FIXME!
    #
    uniqueMappingsOnly = property(getUniqueMappingsOnly, setUniqueMappingsOnly)

    ##
    # \brief FIXME!
    #
    allRuleMappings = property(getAllRuleMappings, setAllRuleMappings)

    ##
    # \brief FIXME!
    #
    onlyFirstMatchingRule = property(getOnlyFirstMatchingRule, setOnlyFirstMatchingRule)

    ##
    # \brief 
    #
    torsionLibrary = property(getTorsionLibrary, setTorsionLibrary)
